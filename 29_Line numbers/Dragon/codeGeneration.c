#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "codeGeneration.h"
#include "treeList.h"
#include "registerStack.h"
#include "util.h"
#include "y.tab.h"

/*
    COMPILER INFORMATION
        %esi -> function return value register
        %eax -> division register
        %edx -> division register

        Diagram of runtime stack according to this compiler:
            HIGH MEMORY (each scope has a size of a multiple of 16 bytes. scanf requires this)
                instruction reference address (1 word -> 4 bytes)
                old base pointer (1 word)
                first local variable declared (X words)
                last local variable declared
                static parent address (1 word)
                temporary registers (NUM_TEMP_REGISTERS words)
                temp variables (Y words)
                last argument to called subprogram (Z words)
                first argument to called subprogram (static parent base pointer)
            LOW MEMORY

        Note: When calling a new subprogram. The first argument set 
        is the base pointer address of the static parent. 
*/

/*
    ARGUMENT_1_OFFSET = 
            8 bytes (64 bits) for instruction pointer
            + 8 bytes (64 bits) * 4 registers saved for subprogam call
            + 8 bytes (64 bits) of space for the first argument which is the static
                parent base pointer.
            = 48
*/
#define ARGUMENT_1_OFFSET 48

// ************ REGISTER INFORMATION *****************
#define FOUR_REG_SIZE 32 // The size of 4 64-bit registers in bytes.
#define NUM_REGS_AVAL 3  // The starting number of registers available.

// ************ STACK FRAME TEMPS OFFSETS *****************
// All measured in bytes.
#define TEMP_DIVISION_OFFSET 4
#define TEMP_FUNCTION_OFFSET 8
#define TEMP_PROCEDURE_OFFSET 12

// ************ REGISTER STRINGS *****************
#define RBP "%rbp"
#define RAX "%rax"
#define EAX "%eax"
#define EDI "%edi"
#define ESI "%esi"
#define ECX "%ecx"
#define EBX "%ebx"

// ************ SUBPROGRAM FLAGS *****************
unsigned int NO_FUNCTION_RETURN = 0x1;
unsigned int NO_SIDE_EFFECTS = 0x2;

// ************ PROTOTYPES *****************
int getExpressionType(scope_t *curScope, tree_t *exprTree);
int countDigits(int branchStringCounter);
void genExpression(FILE *outFile, tree_t *root, scope_t *topScope, short isLeftMost);
void genStatement(FILE *outFile, tree_t *root, scope_t *topScope);

// ************ GLOBAL VARIABLES *****************
RegisterStack *registerStack = NULL;
int branchStringCounter = 0;
short numRegistersAvail = 3;
short tempStackTop = 0;

extern int yyerror(char *);

// ************ CONSTANT ASSEMBLY STRINGS *****************
/* Top of assembly file */
char *topHeader = "\t.text\n\t.section\t.rodata\n.LC0:\n\t.string\t\"%d\\n\"\n\t.text\n\t.globl\tmain\n\t.type\tmain, @function\n.LC1:\n\t.string\t\"%d\"\n\t.text\n\t.globl\tmain\n\t.type\tmain, @function\n";

/* Assembly for creating functions/procedures. */
char *funcProcCodeBegin = "\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n";
char *funcProcCodeEnd = "\tleave\n\tret\n";
char *procedureEndInfo = "\n\t.globl\tmain\n\t.type\tmain, @function\n";

/* Code for printf assembly. */
char *printfEndCode = ", %esi\n\tleaq\t.LC0(%rip), %rdi\n\tmovl\t$0, %eax\n\tcall\tprintf\n";

/* Code for scanf assembly. */
char *scanfEndCode = ", %rax\n\tmovq\t%rax, %rsi\n\tleaq\t.LC1(%rip), %rdi\n\tmovl\t$0, %eax\n\tcall\t__isoc99_scanf@PLT\n";

/* Assembly for MAIN */
char *firstPartMainAsm = "main:\n\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n\tmovl\t$0, %eax\n";
// Needs "call  boo"
char *secondPartMainAsm = "\tmovl\t$0, %eax\n\tleave\n\tret\n";
char *mainInfoAsm = ".main:\n\t.size\tmain, .-main\n\t.ident\t\"GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0\"\n\t.section\t.note.GNU-stack,\"\",@progbits\n";

// ************ FUNCTIONS FOR CODE GENERATION *****************

/*
    Register stack is setup with only 3 registers.
*/
void setupRegisterStack()
{
    registerStack = pushRegisterString(NULL, EDI);
    registerStack = pushRegisterString(registerStack, ECX);
    registerStack = pushRegisterString(registerStack, EBX);
}

void freeRegisters()
{
    freeRegisterStack(registerStack);
}

/*
    Prints the assembly headers to outFile. Look at topHeader.
*/
void genCodePrintHeader(FILE *outFile)
{
    fputs(topHeader, outFile);
}

/*
    Lowers the stack pointer to allow room for variables, temps, etc.
*/
void lowerStackPointer(FILE *outFile, int curScopeSize)
{
    fputs("\tsubq\t$", outFile);
    char strOffset[8]; // Dangerous but rare for offset to have >8 characters.
    fputs(my_itoa(curScopeSize, strOffset), outFile);
    fputs(", %rsp # lowering the stack pointer.\n", outFile);
}

/*
    Prints to offsetString a string of format: frameOffset(baseReg).
*/
void getVarOffsetString(int frameOffset, char *baseReg, char *offsetString)
{
    if (frameOffset > 0)
    {
        sprintf(offsetString, "-%d(%s)", frameOffset, baseReg);
    }
    else
    {
        sprintf(offsetString, "%d(%s)", -frameOffset, baseReg);
    }
}

/*
    Prints to offsetString a string of format: -%baseRegOffset(%baseReg, %indexOffset, 4).
*/
void getArrayOffsetString(int frameOffset, char *baseReg, char *indexOffsetReg, char *arrayOffsetString)
{
    indexOffsetReg[1] = 'r';
    if (frameOffset > 0)
    {
        sprintf(arrayOffsetString, "-%d(%s, %s, 4)", frameOffset, baseReg, indexOffsetReg);
    }
    else
    {
        sprintf(arrayOffsetString, "%d(%s, %s, 4)", frameOffset, baseReg, indexOffsetReg);
    }
    indexOffsetReg[1] = 'e';
}

/*
    Outputs code to help the mov commands given two arguments.
*/
void movHelper(FILE *outFile, char *arg1, char *arg2)
{
    fputs(arg1, outFile);
    fputs(", ", outFile);
    fputs(arg2, outFile);
    fputs("\n", outFile);
}

/*
    Outputs code to outFile to movq a value in arg1 to arg2.
*/
void genMovqCode(FILE *outFile, char *arg1, char *arg2)
{
    fputs("\tmovq\t", outFile);
    movHelper(outFile, arg1, arg2);
}

/*
    Outputs code to outFile to movl a value in arg1 to arg2.
*/
void genMovlCode(FILE *outFile, char *arg1, char *arg2)
{
    fputs("\tmovl\t", outFile);
    movHelper(outFile, arg1, arg2);
}

/*
    "Chases" an identifier to its correct scope/stack-frame.
*/
void chaseId(FILE *outFile, node_t *idNode, scope_t *topScope)
{
    short firstPass = 1;
    while (scope_search(topScope, idNode->name) == NULL)
    {
        if (firstPass)
        {
            // Move the static parent base pointer to %rax on the first pass.
            char staticParentOffset[12];
            getVarOffsetString(topScope->staticParentOffset, RBP, staticParentOffset);
            genMovqCode(outFile, staticParentOffset, RAX);
        }
        else
        {
            genMovqCode(outFile, "(%rax)", RAX);
        }
        topScope = topScope->next;
        firstPass = 0;
    }
}

/*
    Outputs code to put the value in idNode into %eax. This variable
    could be outside of the current scope. If it is, then %rax must 
    chase the variable to its scope.

    FOR ARRAYS, the first index is at the bottom of the allocated 
    space in memory. Diagram:

    high memory
        x-1th index, AND the frameOffset value for array of size x
        ...
        second index
        first index (frameOffset + x + firstIndexValue*4)
    low memory
*/
void getIdOffset(FILE *outFile, node_t *idNode, char *offsetString, char *indexOffset, scope_t *topScope)
{
    // If the requested variable is the return value of a
    // function, return the 'return value' register %esi.
    if (idNode->name == topScope->scopeOwner->name)
    {
        sprintf(offsetString, "%%esi");
        return;
    }

    // Check if variable is in current scope.
    if (scope_search(topScope, idNode->name) != NULL)
    {
        // Variable is in current scope.
        // Get the offset for the variable or start index of the array.
        getVarOffsetString(idNode->frameOffset, RBP, offsetString);

        if (idNode->data.varInfo.isArray)
        {
            // Find the offset for the index.
            int size = (idNode->data.varInfo.end - idNode->data.varInfo.start) * 4;
            int firstIdxOffset = idNode->frameOffset + size + idNode->data.varInfo.start * 4;
            getArrayOffsetString(firstIdxOffset, RBP, indexOffset, offsetString);
        }
        else
        {
            getVarOffsetString(idNode->frameOffset, RBP, offsetString);
        }
    }
    else
    {
        // Variable is in a different scope.
        chaseId(outFile, idNode, topScope);
        if (idNode->data.varInfo.isArray)
        {
            int size = (idNode->data.varInfo.end - idNode->data.varInfo.start) * 4;
            int firstIdxOffset = size + idNode->frameOffset + idNode->data.varInfo.start * 4;
            getArrayOffsetString(firstIdxOffset, RBP, indexOffset, offsetString);
        }
        else
        {
            getVarOffsetString(idNode->frameOffset, RAX, offsetString);
        }
    }
}

/*
    Outputs the x86 code to outFile to begin a procedure or function.
    Loads arguments into local variables!
*/
void genCodePrintProcBegin(FILE *outFile, scope_t *topScope)
{
    // Output subprogram name and begining code.
    fputs(getCodeName(topScope->scopeOwner), outFile);
    fputs(":\n", outFile);
    fputs(funcProcCodeBegin, outFile);

    // Lower stack pointer for current scope on runtime stack.
    lowerStackPointer(outFile, topScope->curScopeSize);

    // Load arguments in previous scope to local variables on runtime stack.
    node_t *scopeOwner = topScope->scopeOwner;
    node_t *curArgument = NULL;
    if (scopeOwner->nodeType == FUNCTION)
    {
        curArgument = scopeOwner->data.functionInfo.arguments;
    }
    else
    {
        curArgument = scopeOwner->data.procedureInfo.arguments;
    }

    // This value holds the offset above the base
    // pointer for the last/ending argument.
    int curVarOffset = ARGUMENT_1_OFFSET;

    // String for the argument location in previous stack frame.
    char argOffsetString[12];
    // Load the static parent base pointer into this stack frame as arg.
    getVarOffsetString(-curVarOffset, RBP, argOffsetString);

    // String for the local variable location for current stack frame.
    char localOffsetString[12];
    // Put the location of the offset for static parent in localOffsetString.
    getVarOffsetString(topScope->staticParentOffset, RBP, localOffsetString);

    // Move the static base pointer into position.
    genMovqCode(outFile, argOffsetString, RAX);
    genMovqCode(outFile, RAX, localOffsetString);

    // Give room for 64 bits of space for static parent base pointer.
    curVarOffset += 2 * sizeof(int);

    // Iterate through rest of arguments putting them as locals in stack frame.
    while (curArgument != NULL)
    {
        if (isArrayNode(curArgument))
        {
            int startIndex = curArgument->data.varInfo.start;
            int endIndex = curArgument->data.varInfo.end;
            int size = endIndex - startIndex + 1;

            for (int index = 0; index < size; ++index)
            {
                // Create string for the argument from previous scope.
                getVarOffsetString(-curVarOffset, RBP, argOffsetString);

                // Create string for the variable in current scope.
                getVarOffsetString(curArgument->frameOffset + index * sizeof(int), RBP, localOffsetString);

                // Output code for moving argument to local variable.
                genMovlCode(outFile, argOffsetString, EAX);
                genMovlCode(outFile, EAX, localOffsetString);

                // Increase offset for next argument.
                curVarOffset += sizeof(int);
            }
            curArgument = curArgument->next;
        }
        else
        {
            // Create string for the argument from previous scope.
            getVarOffsetString(-curVarOffset, RBP, argOffsetString);

            // Create string for the variable in current scope.
            getVarOffsetString(curArgument->frameOffset, RBP, localOffsetString);

            // Output code for moving argument to local variable.
            genMovlCode(outFile, argOffsetString, EAX);
            genMovlCode(outFile, EAX, localOffsetString);

            // Increase offset for next argument.
            curVarOffset += sizeof(int);
            curArgument = curArgument->next;
        }
    }
}

/*
    Outputs code to end an x86 subprogram.
*/
void genCodePrintProcEnd(FILE *outFile, char *procName)
{
    fputs(funcProcCodeEnd, outFile);
    fputs(".", outFile);
    fputs(procName, outFile);
    fputs(":\n\t.size\t", outFile);
    fputs(procName, outFile);
    fputs(", .-", outFile);
    fputs(procName, outFile);
    fputs(procedureEndInfo, outFile);
}

/*
    Outputs code for the main function of a program.
*/
void genCodePrintMain(FILE *outFile, char *mainProcName)
{
    assert(outFile != NULL);
    fputs(firstPartMainAsm, outFile);
    fputs("\tcall\t", outFile);
    fputs(mainProcName, outFile);
    fputs("\n", outFile);
    fputs(secondPartMainAsm, outFile);
    fputs(mainInfoAsm, outFile);
}

/*
    Returns the filename for a programId. fileName must be freed
    later. Filename extension is ".s"
*/
char *getFileName(char *programId)
{
    int fileNameLen = strlen(programId) + 2; // +2 for .s
    char *fileName = (char *)malloc(fileNameLen * sizeof(char));

    strcpy(fileName, programId);

    fileName[fileNameLen - 2] = '.';
    fileName[fileNameLen - 1] = 's';
    fileName[fileNameLen] = '\0';

    return fileName;
}

/*
    Raise the stack pointer a variable amount (in bytes).
*/
void genRaiseStackPointer(FILE *outFile, int amountInBytes)
{
    fputs("\taddq\t$", outFile);
    char strOffset[8]; // Dangerous but rare for offset to have >8 characters.
    fputs(my_itoa(amountInBytes, strOffset), outFile);
    fputs(", %rsp # raising the stack pointer.\n", outFile);
}

/*
    Generates the code to push a location on to the stack
    frame (which also raises the stack pointer).
*/
void genPushqCode(FILE *outFile, char *locationToPush)
{
    fputs("\tpushq\t", outFile);
    fputs(locationToPush, outFile);
    fputs("\n", outFile);
}

/*
    Outputs code to outFile for printing the value in stackLocation.
*/
void genPrintfCode(FILE *outFile, scope_t *topScope, char *stackLocation)
{
    // Current return value in temporary location.
    // Location wont be overwritten.
    char tempLocation[12];
    getVarOffsetString(topScope->tempsAddress, RBP, tempLocation);
    genMovlCode(outFile, ESI, tempLocation);

    fputs("\tmovl\t", outFile);
    fputs(stackLocation, outFile);
    fputs(printfEndCode, outFile);
    fputs("\n", outFile);

    // Restore %esi.
    genMovlCode(outFile, tempLocation, ESI);
}

/*
    Outputs code to outFile for reading the value in stackLocation.
*/
void genReadCode(FILE *outFile, char *stackLocation)
{
    fputs("\tleaq\t", outFile);
    fputs(stackLocation, outFile);
    fputs(scanfEndCode, outFile);
}

void pushAllRegisters(FILE *outFile)
{
    // Stack size must always be a multiple of 16 as
    // needed by scanf.
    genPushqCode(outFile, "%rdi"); // Will be dummy.
    genPushqCode(outFile, "%rdi");
    genPushqCode(outFile, "%rcx");
    genPushqCode(outFile, "%rbx");
}

void restoreAllRegisters(FILE *outFile)
{
    genMovqCode(outFile, "0(%rsp)", "%rbx");
    genMovqCode(outFile, "4(%rsp)", "%rcx");
    genMovqCode(outFile, "8(%rsp)", "%rdi");
    genRaiseStackPointer(outFile, FOUR_REG_SIZE);
}

/*
    Translates the value of the leaf into a string readable by x86 code.
*/
void getLeafString(FILE *outFile, tree_t *leaf, char *leafString, scope_t *topScope)
{
    assert(leaf->label == 0 || leaf->label == 1);
    if (leaf->type == INUM)
    {
        sprintf(leafString, "$%d", leaf->attribute.ival);
    }
    else if (leaf->type == RNUM)
    {
        assert(0); // Real numbers are not supported yet.
    }
    else if (leaf->type == ID)
    {
        node_t *idNode = leaf->attribute.nval;
        if (scope_search(topScope, idNode->name) != NULL)
        {
            // This variable is in the current scope.
            getVarOffsetString(idNode->frameOffset, RBP, leafString);
        }
        else
        {
            // This variable is in a different scope. Must start chasing.
            getIdOffset(outFile, leaf->attribute.nval, leafString, NULL, topScope);
        }
    }
    else
    {
        fprintf(stderr, "leaf->type %d\n", leaf->type);
        assert(0);
    }
    return;
}

/*
    Labels the expression tree to prepare it for 
    genExpression (gen_code).
*/
void labelTree(tree_t *root, short isLeftMost)
{
    // For now, assume no functions or NOT.
    if (root == NULL)
    {
        assert(0);
        return;
    }
    // Leaf case should only happen when no operators.
    else if (isLeaf(root))
    {
        root->label = 1;
        return;
    }
    // NOT case should make current node have child's label
    else if (root->type == NOT)
    {
        labelTree(root->leftChild, isLeftMost);
        root->label = root->leftChild->label;
        return;
    }
    // For function call, label is the max label of the expression arguments.
    else if (root->type == FUNCTION_CALL)
    {
        // Retrieve the argument list for this function.
        TreeList *curArgument = root->rightChild->attribute.listVal;
        int maxLabel = isLeftMost;
        while (curArgument != NULL)
        {
            // Retrieve the expression tree from this argument.
            tree_t *curArgumentExpr = curArgument->statementTree;
            labelTree(curArgumentExpr, isLeftMost);
            // Update the max label based on label of expression tree.
            maxLabel = max(curArgumentExpr->label, maxLabel);
            curArgument = curArgument->next;
        }
        root->label = maxLabel;
    }
    else if (root->type == ARRAY_ACCESS)
    {
        labelTree(root->rightChild, isLeftMost);
        root->label = root->rightChild->label;
    }
    else
    {
        // Handle left child.
        if (hasLeftLeaf(root))
        {
            root->leftChild->label = 1;
        }
        else
        {
            labelTree(root->leftChild, 1);
        }
        // Handle right child.
        if (hasRightLeaf(root))
        {
            root->rightChild->label = 0;
        }
        else
        {
            labelTree(root->rightChild, 0);
        }
        int leftChildLabel = root->leftChild->label;
        int rightChildLabel = root->rightChild->label;
        // Handle root.
        if (leftChildLabel == rightChildLabel)
        {
            root->label = leftChildLabel + 1;
        }
        else
        {
            root->label = max(leftChildLabel, rightChildLabel);
        }
    }
}

/*
    Outputs code to outFile for starting a procedure or 
    function. Arguments are put into position, the base
    pointer for the static parent is set (as an argument),
    and the next function is called. 
*/
void startSubprogram(FILE *outFile, tree_t *root, scope_t *topScope)
{
    // Retrieve argument list from tree node.
    TreeList *curArgument = NULL;
    if (root->rightChild != NULL)
    {
        assert(root->rightChild->type == ARGS);
        curArgument = root->rightChild->attribute.listVal;
    }

    // Initialize the offset from the base pointer to the first
    // argument position. The offset is a positive number and
    // above the base pointer in memory.
    int basePointerOffset = topScope->curScopeSize;

    // Move the correct static parent base pointer location
    // as the first argument.
    char staticParentLocation[12];
    if (scope_search(topScope, root->leftChild->attribute.nval->name) != NULL)
    {
        // Calling subprogram is the static parent. Pass current base pointer.
        sprintf(staticParentLocation, "%s", RBP);
    }
    else
    {
        // Calling subprogram shares the static parent.
        getVarOffsetString(topScope->staticParentOffset, RBP, staticParentLocation);
    }

    // Execute the move from the static parent base pointer location
    // to the called subprogram.
    char argLocation[12];
    getVarOffsetString(basePointerOffset, RBP, argLocation);
    genMovqCode(outFile, staticParentLocation, RAX);
    genMovqCode(outFile, RAX, argLocation);
    basePointerOffset -= 2 * sizeof(int);

    // String location for the argument on the stack frame.
    while (curArgument != NULL)
    {
        tree_t *argument = curArgument->statementTree;
        if (isArray(argument))
        {
            node_t *arrayNode = argument->attribute.nval;
            int startIndex = arrayNode->data.varInfo.start;
            int endIndex = arrayNode->data.varInfo.end;
            int size = endIndex - startIndex + 1;

            for (int index = endIndex; index >= startIndex; --index)
            {
                char indexString[12];
                sprintf(indexString, "$%d", index);
                genMovlCode(outFile, indexString, registerStack->registerName);

                // Get string for the index location to move.
                char arrayIndexLocation[32];
                getIdOffset(outFile, arrayNode, arrayIndexLocation, registerStack->registerName, topScope);

                // Get location in string format for this argument.
                char argLocation[12];
                getVarOffsetString(basePointerOffset, RBP, argLocation);

                // Move the array index value into the argument position.
                genMovlCode(outFile, arrayIndexLocation, EAX);
                genMovlCode(outFile, EAX, argLocation);

                basePointerOffset -= sizeof(int);
            }
        }
        else
        {
            // Setup expression tree for evaluation.
            labelTree(argument, 1);
            // Generate code for expression.
            genExpression(outFile, argument, topScope, 1);
            // Expression return value is now in top register.

            // Get location in string format for this argument.
            char argLocation[12];
            getVarOffsetString(basePointerOffset, RBP, argLocation);
            // Move the expression return value into the argument position.
            genMovlCode(outFile, registerStack->registerName, EAX);
            genMovlCode(outFile, EAX, argLocation);
            // Increase base pointer and move to next argument.
            basePointerOffset -= sizeof(int);
        }
        curArgument = curArgument->next;
    }
    // Save values of registers before subprogram call.
    pushAllRegisters(outFile);

    // Call subprogram.
    fputs("\tcall\t", outFile);
    fputs(getCodeName(root->leftChild->attribute.nval), outFile);
    fputs("\n", outFile);

    scope_print(topScope);

    // Restore values of registers after subprogram call.
    restoreAllRegisters(outFile);
}

/*
    Prints the associated operator with operatorRoot to operatorString.
    This currenly ONLY works with INTEGERS
*/
void getOperatorString(tree_t *operatorRoot, char *operatorString)
{
    assert(operatorRoot->type == MULOP || operatorRoot->type == ADDOP || operatorRoot->type == RELOP);
    if (operatorRoot->attribute.opval == PLUS)
    {
        sprintf(operatorString, "addl");
    }
    else if (operatorRoot->attribute.opval == MINUS)
    {
        sprintf(operatorString, "subl");
    }
    else if (operatorRoot->attribute.opval == STAR)
    {
        sprintf(operatorString, "imull");
    }
    else if (operatorRoot->attribute.opval == SLASH)
    {
        sprintf(operatorString, "idivl");
    }
    else if (operatorRoot->attribute.opval == AND)
    {
        sprintf(operatorString, "andl");
    }
    else if (operatorRoot->attribute.opval == OR)
    {
        sprintf(operatorString, "orl");
    }
    else
    {
        fprintf(stderr, "operatorRoot->type %d\n", operatorRoot->type);
        fprintf(stderr, "operatorRoot->attribute.opval %d\n", operatorRoot->attribute.opval);
        assert(0);
    }
}

/*
    Outputs the code to compare two values. Values can be in
    memory or a register.
*/
void printCompareCode(FILE *outFile, char *arg1, char *arg2)
{
    fputs("\tcmpl\t", outFile);
    fputs(arg1, outFile);
    fputs(", ", outFile);
    fputs(arg2, outFile);
    fputs("\n", outFile);
}

/*
Prints the x86 assembly code for a relative operation (boolean 1 or 0).
*/
void printRelopCode(FILE *outFile, tree_t *operatorRoot, char *arg1, RegisterStack *reg)
{
    // Print the code to setup operation.
    printCompareCode(outFile, arg1, reg->registerName);
    fputs("\t", outFile);
    
    // Print specific operation command.
    switch (operatorRoot->attribute.opval)
    {
    case EQ:
        fputs("setz", outFile);
        break;
    case NE:
        fputs("setne", outFile);
        break;
    case LT:
        fputs("setl", outFile);
        break;
    case LE:
        fputs("setle", outFile);
        break;
    case GT:
        fputs("setg", outFile);
        break;
    case GE:
        fputs("setge", outFile);
        break;
    default:
        assert(0);
    }
    fputs("\t%al\n\tmovzbl\t%al, ", outFile);
    fputs(reg->registerName, outFile);
    fputs("\n", outFile);
}

/*
    Generates the x86 code to divide the value in reg by the value in arg1.
*/
void genDivisionCode(FILE *outFile, scope_t *topScope, char *arg1, RegisterStack *reg)
{
    // Create string for the offset for the division temp location.
    char tempLocation[12];
    getVarOffsetString(topScope->tempsAddress + TEMP_DIVISION_OFFSET, RBP, tempLocation);
    genMovlCode(outFile, arg1, EAX);
    genMovlCode(outFile, EAX, tempLocation);

    // Move value in reg to the division register, %eax.
    genMovlCode(outFile, reg->registerName, EAX);
    fputs("\tcltd\n", outFile);

    // Output division code.
    fputs("\tidivl\t", outFile);
    fputs(tempLocation, outFile);
    fputs("\n", outFile);
}

/*
    Writes to code for an operator with two operands. Division is 
    handled differently than other operators in x86.
*/
void writeOperatorCode(FILE *outFile, scope_t *topScope, tree_t *operatorRoot, char *arg1, RegisterStack *reg)
{
    if (operatorRoot->attribute.opval == SLASH)
    {
        genDivisionCode(outFile, topScope, arg1, reg);
        // Move result to top of registerStack.
        genMovlCode(outFile, EAX, reg->registerName);
    }
    else if (operatorRoot->attribute.opval == MOD)
    {
        genDivisionCode(outFile, topScope, arg1, reg);
        // Move result to top of registerStack.
        genMovlCode(outFile, "%edx", reg->registerName);
    }
    else if (operatorRoot->type == RELOP)
    {
        printRelopCode(outFile, operatorRoot, arg1, reg);
        // Return value is in reg.
    }
    else
    {
        // Create a string for the operator to be applied.
        char operatorString[12];
        getOperatorString(operatorRoot, operatorString);

        // Output the code to execute the operator on the operands.
        fputs("\t", outFile);
        fputs(operatorString, outFile);
        fputs("\t", outFile);
        fputs(arg1, outFile);
        fputs(", ", outFile);
        fputs(reg->registerName, outFile);
        fputs("\n", outFile);
    }
}

/*
    Tree is assumed to be already labeled. This is the gen_code algorithm.
*/
void genExpression(FILE *outFile, tree_t *root, scope_t *topScope, short isLeftMost)
{
    // Leaf case.
    if (isLeaf(root))
    {
        // Check for leftMost leaf.
        if (isLeftMost)
        {
            char name[12];
            getLeafString(outFile, root, name, topScope);
            genMovlCode(outFile, name, registerStack->registerName);
        }
    }
    // Non-Leaf cases.
    else if (root->type == FUNCTION_CALL)
    {
        // Put the current return value esi into a temporary location.
        fputs("\t# Putting current return value to temporary location before function call.\n", outFile);
        char tempLocation[12];
        getVarOffsetString(topScope->tempsAddress + TEMP_FUNCTION_OFFSET, RBP, tempLocation);
        genMovlCode(outFile, ESI, tempLocation);

        // Call function.
        startSubprogram(outFile, root, topScope);

        // Return value is now in %esi.
        genMovlCode(outFile, ESI, registerStack->registerName);

        // Restore %esi value.
        fputs("\t# Restoring current return value to temporary location after function call.\n", outFile);
        genMovlCode(outFile, tempLocation, ESI);
    }
    else if (root->type == NOT)
    {
        // In boolean expressions, values should either be 1 or 0.
        // So, we can just xor the value with 1 to flip the bit.

        // First retrieve the boolean result of the left child.
        genExpression(outFile, root->leftChild, topScope, isLeftMost);

        fputs("\txor\t$1, ", outFile);
        fputs(registerStack->registerName, outFile);
        fputs("\n", outFile);
        // Result now sits on top of register stack.
    }
    else if (root->type == ARRAY_ACCESS)
    {
        // mktree(ARRAY_ACCESS, mkid(arrayNode), $3);
        node_t *idNode = root->leftChild->attribute.nval;
        tree_t *indexExpressionTree = root->rightChild;

        // Put array access index into top register.
        genExpression(outFile, indexExpressionTree, topScope, 1);

        // Example: address of array E in rdx, i in rcx
        // movl %eax (%rdx, %rcx, 4)
        // movl frameOffset(%baseReg, %indexOffset, 4) regTop
        char arrayIndexLocation[24];
        getIdOffset(outFile, idNode, arrayIndexLocation, registerStack->registerName, topScope);
        genMovlCode(outFile, arrayIndexLocation, registerStack->registerName);
    }
    else
    {
        assert(root->type == RELOP || root->type == ADDOP || root->type == MULOP);

        // Root is an operator.
        int leftChildType = getExpressionType(topScope, root->leftChild);
        assert(leftChildType == INTEGER); // For now
        tree_t *leftChild = root->leftChild;
        tree_t *rightChild = root->rightChild;
        if (rightChild->label == 0)
        {
            // CASE 1
            genExpression(outFile, leftChild, topScope, 1);
            char name[12];
            getLeafString(outFile, rightChild, name, topScope);

            writeOperatorCode(outFile, topScope, root, name, registerStack);
        }
        else if (1 < leftChild->label && leftChild->label < rightChild->label && leftChild->label < numRegistersAvail)
        {
            // CASE 2

            registerStack = swapRegisterStack(registerStack);
            genExpression(outFile, rightChild, topScope, 0);
            RegisterStack *poppedReg = popRegister(&registerStack);
            numRegistersAvail--;

            genExpression(outFile, leftChild, topScope, 1);
            writeOperatorCode(outFile, topScope, root, poppedReg->registerName, registerStack);

            registerStack = pushRegister(registerStack, poppedReg);
            registerStack = swapRegisterStack(registerStack);
            numRegistersAvail++;
        }
        else if (1 <= rightChild->label && rightChild->label <= leftChild->label && rightChild->label < numRegistersAvail)
        {
            // CASE 3

            genExpression(outFile, leftChild, topScope, 1);

            RegisterStack *poppedReg = popRegister(&registerStack);
            numRegistersAvail--;

            genExpression(outFile, rightChild, topScope, 0);
            writeOperatorCode(outFile, topScope, root, registerStack->registerName, poppedReg);
            registerStack = pushRegister(registerStack, poppedReg);
            numRegistersAvail++;
        }
        else
        {
            // CASE 4

            // gencode(right tree (n2))
            genExpression(outFile, rightChild, topScope, 0);

            // T = pop(Tstack)
            if (tempStackTop >= NUM_TEMP_REGISTERS)
            {
                yyerror("All x86 and temporary registers were used.");
            }
            int poppedIndex = tempStackTop++;

            // load top(Rstack), T
            char tempLocation[24];
            getVarOffsetString(topScope->tempRegisterOffsets[poppedIndex], RBP, tempLocation);
            genMovlCode(outFile, registerStack->registerName, tempLocation);

            // gencode(left tree(n1))
            genExpression(outFile, leftChild, topScope, 1);

            // print op T, top(RSTACK)
            writeOperatorCode(outFile, topScope, root, tempLocation, registerStack);

            // push(TSTACK, T)
            tempStackTop--;
        }
    }
}

/*
    Returns the name for a valid next branch string.
*/
char *getBranchString(int count)
{
    // 2 for .L, and 1 for \0 (from sprintf).
    int branchStringSize = 2 + countDigits(branchStringCounter);

    // +1 for \0
    char *branchString = (char *)malloc((branchStringSize + 1) * sizeof(char));
    sprintf(branchString, ".L%d", count);

    branchString[branchStringSize] = '\0';
    return branchString;
}

void genForBranching(FILE *outFile, tree_t *root, scope_t *topScope)
{
    assert(root->type == FOR);

    // $$ = mktree(FOR, mktree(ASSIGNOP, $2, $4), mktree(TO, $6, mktree(DO, $8, NULL)));
    // Retrieve the tree leaf for the variable to be checked.
    tree_t *variableTree = root->leftChild->leftChild;
    tree_t *boundTree = root->rightChild->leftChild;
    tree_t *statementTree = root->rightChild->rightChild->leftChild;

    // Perform the assignment on the variable.
    labelTree(variableTree, 1);
    genStatement(outFile, root->leftChild, topScope);

    char *stmtBranchString = getBranchString(branchStringCounter++);
    char *boolBranchString = getBranchString(branchStringCounter++);

    // Jump to the condition check.
    fputs("\tjmp\t", outFile);
    fputs(boolBranchString, outFile);
    fputs("\n", outFile);

    // Set branch for the statement.
    fputs(stmtBranchString, outFile);
    fputs(":\n", outFile);

    // Generate statement code.
    genStatement(outFile, statementTree, topScope);

    // Perform a +1 to the variable.
    tree_t *add1Tree = mktree(ASSIGNOP, variableTree, mkop(ADDOP, PLUS, variableTree, mkinum(1)));
    labelTree(add1Tree, 1);
    genStatement(outFile, add1Tree, topScope);
    free(add1Tree->rightChild->rightChild);
    free(add1Tree->rightChild);
    free(add1Tree);

    // Set branch for the condition check.
    fputs(boolBranchString, outFile);
    fputs(":\n", outFile);
    // Generate code to check the condition.
    tree_t *lessThanEqTree = mkop(RELOP, LE, variableTree, boundTree);
    labelTree(lessThanEqTree, 1);
    genExpression(outFile, lessThanEqTree, topScope, 1);
    free(lessThanEqTree);

    // Compare the result of the expression with 1 (true).
    printCompareCode(outFile, "$1", registerStack->registerName);
    fputs("\tje\t", outFile);
    fputs(stmtBranchString, outFile);
    fputs("\n", outFile);

    // Deallocate strings.
    free(stmtBranchString);
    free(boolBranchString);
}

/*
    Branching is used for executing while statements.
    This function generates the code for those.
*/
void genWhileBranching(FILE *outFile, tree_t *root, scope_t *topScope)
{
    assert(root->type == WHILE);

    // Left side is boolean expression
    tree_t *booleanTree = root->leftChild;
    // Right side is a statement to do while true.
    tree_t *statementTree = root->rightChild;

    // Setup expression tree for code generation.
    labelTree(booleanTree, 1);
    char *stmtBranchString = getBranchString(branchStringCounter++);
    char *boolBranchString = getBranchString(branchStringCounter++);

    // Jump to the condition check.
    fputs("\tjmp\t", outFile);
    fputs(boolBranchString, outFile);
    fputs("\n", outFile);

    // Set branch for the statement.
    fputs(stmtBranchString, outFile);
    fputs(":\n", outFile);

    // Generate statement code.
    genStatement(outFile, statementTree, topScope);

    // Set branch for the condition check.
    fputs(boolBranchString, outFile);
    fputs(":\n", outFile);
    genExpression(outFile, booleanTree, topScope, 1);
    // Compare the result of the expression with 1 (true).
    printCompareCode(outFile, "$1", registerStack->registerName);
    fputs("\tje\t", outFile);
    fputs(stmtBranchString, outFile);
    fputs("\n", outFile);

    // Deallocate strings.
    free(stmtBranchString);
    free(boolBranchString);
}

/*
    Branching is used for executing if-then-else statements.
    This function generates the code for those.
*/
void genIfBranching(FILE *outFile, tree_t *root, scope_t *topScope)
{
    assert(root->type == THEN);

    // If expression returned 0, jump to another location. Else continue.
    printCompareCode(outFile, "$0", registerStack->registerName);
    // If rightChild is NULL, there is no else statement.
    if (root->rightChild == NULL)
    {
        // Get string for the jump location.
        char *branchString = getBranchString(branchStringCounter++);

        // Generate branching code.
        fputs("\tje\t", outFile);
        fputs(branchString, outFile);
        fputs("\n", outFile);
        genStatement(outFile, root->leftChild, topScope);
        fputs(branchString, outFile);
        fputs(":\n", outFile);

        // Deallocate the branchString.
        free(branchString);
    }
    else
    {
        // There is an else.
        char *elseBranchString = getBranchString(branchStringCounter++);
        char *endBranchString = getBranchString(branchStringCounter++);
        // Generate branching code.
        fputs("\tje\t", outFile);
        fputs(elseBranchString, outFile);
        fputs("\n", outFile);

        // Generate then statements.
        genStatement(outFile, root->leftChild, topScope);

        // Jump to end of else statement.
        fputs("\tjmp\t", outFile);
        fputs(endBranchString, outFile);
        fputs("\n", outFile);

        // Indicate the location of the else statement.
        fputs(elseBranchString, outFile);
        fputs(":\n", outFile);

        // Generate else statement.
        genStatement(outFile, root->rightChild, topScope);

        // Indicate the end of branching location.
        fputs(endBranchString, outFile);
        fputs(":\n", outFile);

        // Deallocate.
        free(elseBranchString);
        free(endBranchString);
    }
}

/*
    Generates the code for executing statements.
*/
void genStatement(FILE *outFile, tree_t *root, scope_t *topScope)
{
    if (root == NULL)
    {
        return;
    }
    else if (root->type == PROCEDURE_CALL)
    {
        // Put the current return value esi into a temporary location.
        fputs("\t# Putting current return value to temporary location before expression.\n", outFile);
        char tempLocation[12];
        getVarOffsetString(topScope->tempsAddress + TEMP_PROCEDURE_OFFSET, RBP, tempLocation);
        genMovlCode(outFile, ESI, tempLocation);

        startSubprogram(outFile, root, topScope);

        // Restore %esi value.
        fputs("\t# Restoring current return value to temporary location after expression.\n", outFile);
        genMovlCode(outFile, tempLocation, ESI);
    }
    else if (root->type == IF)
    {
        // Left side is boolean expression
        tree_t *exprTree = root->leftChild;

        // Setup expression tree for code generation.
        labelTree(exprTree, 1);
        // Evaulate the expression.
        genExpression(outFile, exprTree, topScope, 1);
        // Expression return value is now in top register.

        // Write the branching statements.
        genIfBranching(outFile, root->rightChild, topScope);
    }
    else if (root->type == ASSIGNOP)
    {
        tree_t *exprTree = root->rightChild;
        tree_t *varTree = root->leftChild;

        // Setup expression tree for code generation.
        labelTree(exprTree, 1);
        genExpression(outFile, exprTree, topScope, 1);
        // Expression return value is now in top register.

        // Check if the variable is an ID or array.
        node_t *idNode;
        if (varTree->type == ID)
        {
            idNode = varTree->attribute.nval;
            if (idNode->nodeType == FUNCTION)
            {
                // This sets up the "return" statement for functions.
                genMovlCode(outFile, registerStack->registerName, ESI);
            }
            else
            {
                // Sets the value of a variable. Could be in another scope (another stack frame).
                assert(idNode->frameOffset > 0);
                char strOffset[12]; // Could be dangerous but rare for offset >12 characters.
                getIdOffset(outFile, idNode, strOffset, NULL, topScope);
                genMovlCode(outFile, registerStack->registerName, strOffset);
            }
        }
        else
        {
            // From pc.y --> mktree(ARRAY_ACCESS, mkid(arrayNode), $3);

            node_t *idNode = varTree->leftChild->attribute.nval;

            // Move the expression result to a temporary location
            // on the runtime stack.
            char exprResultLocation[12];
            getVarOffsetString(topScope->tempsAddress + 20, RBP, exprResultLocation);
            genMovlCode(outFile, registerStack->registerName, exprResultLocation);

            tree_t *indexExpressionTree = varTree->rightChild;

            // Put array access index into top register.
            labelTree(indexExpressionTree, 1);
            genExpression(outFile, indexExpressionTree, topScope, 1);

            // Example: address of array E in rdx, i in rcx
            // movl %eax (%rdx, %rcx, 4)
            // movl frameOffset(%baseReg, %indexOffset, 4) regTop
            char arrayIndexLocation[24];
            getIdOffset(outFile, idNode, arrayIndexLocation, registerStack->registerName, topScope);
            genMovlCode(outFile, exprResultLocation, registerStack->next->registerName);

            genMovlCode(outFile, registerStack->next->registerName, arrayIndexLocation);
        }
    }
    else if (root->type == WHILE)
    {
        // Create the x86 flow for a while loop.
        genWhileBranching(outFile, root, topScope);
    }
    else if (root->type == FOR)
    {
        // FOR variable ASSIGNOP expression TO expression DO statement
        genForBranching(outFile, root, topScope);
    }
    else if (root->type == WRITE)
    {
        tree_t *exprTree = root->leftChild;

        // Setup expression tree for code generation.
        labelTree(exprTree, 1);

        // Execute code generation.
        genExpression(outFile, exprTree, topScope, 1);
        // Value to print is now in the top register.
        genPrintfCode(outFile, topScope, registerStack->registerName);
    }
    else if (root->type == READ)
    {
        tree_t *idTree = root->leftChild;

        // Create a string for the location to put user input into.
        char varLocation[12];
        getIdOffset(outFile, idTree->attribute.nval, varLocation, NULL, topScope);
        genReadCode(outFile, varLocation);
    }
    else if (root->type == COMPOUND_STATEMENT)
    {
        // Iterate through the list of statements outputting code for each.
        TreeList *statementList = root->leftChild->attribute.listVal;
        while (statementList)
        {
            genStatement(outFile, statementList->statementTree, topScope);
            statementList = statementList->next;
        }
    }
    else
    {
        fprintf(stderr, "root->type %d\n", root->type);
        yyerror("root->type error in genStatement\n");
    }
}

/*
    Returns 1 if the compoundStmtTree has side effects. Generates code based
    on the compoundStmtTree. This is the main code generation function.
*/
short genCode(FILE *outFile, tree_t *compoundStmtTree, scope_t *topScope, short subContainsSideEffects)
{
    assert(compoundStmtTree->type == COMPOUND_STATEMENT);

    // Retrieve the scopeOwner for reference.
    node_t *scopeOwner = topScope->scopeOwner;

    // Add space to scope for the offset for the static parent.
    addVariableToScope(topScope, sizeof(int));
    topScope->staticParentOffset = addVariableToScope(topScope, sizeof(int));

    // Add space and create offsets for temporary registers on stack frame.
    setTemporaryRegisters(topScope);

    // Add space to scope for temp variables. Allocate for 6 temp variables
    topScope->tempsAddress = addVariableToScope(topScope, 6 * sizeof(int));

    // An additional 64-bit (2 bytes) argument is needed to pass the static
    // parent base pointer to the subprogram called next.

    addVariableToScope(topScope, 2 * sizeof(int));

    // Retrieve statement list for semantics and code gen.
    TreeList *statementList = compoundStmtTree->leftChild->attribute.listVal;

    // Find the space needed for passing arguments to a subprogram.
    int maxNumArguments = 0;
    findMaxNumArguments(statementList, &maxNumArguments);
    addVariableToScope(topScope, maxNumArguments);

    // Do code generation
    genCodePrintProcBegin(outFile, topScope);

    if (statementList)
    {
        // Setup flags to check for side effects.
        int flags = NO_SIDE_EFFECTS;
        if (scopeOwner->nodeType == FUNCTION)
        {
            flags = flags | NO_FUNCTION_RETURN;
        }

        TreeList *curStmt = statementList;
        while (curStmt != NULL)
        {
            validateStatement(topScope, curStmt->statementTree, &flags);
            // Output code for the statement
            genStatement(outFile, curStmt->statementTree, topScope);
            // Move to next statement (frees the current statement).
            curStmt = popStatement(curStmt);
        }

        short containsSideEffects = hasSideEffects(flags);
        if (scopeOwner->nodeType == FUNCTION)
        {
            // Check if the flags indicate side effects or no return statement.
            if (hasNoReturnStmt(flags))
            {
                yyerror("Function return has no return statement in subprogram_declaration\n");
            }
            if (containsSideEffects)
            {
                yyerror("Function return has SIDE EFFECT in subprogram_declaration\n");
            }
        }
        else
        { // scopeOwner->nodeType == PROCEDURE
            assert(scopeOwner->nodeType == PROCEDURE);
            scopeOwner->data.procedureInfo.hasSideEffects =
                scopeOwner->data.procedureInfo.hasSideEffects || containsSideEffects;
        }

        node_t *subpgmHeadNode = topScope->scopeOwner;
        short cpndStmtSideEffects = hasSideEffects(flags);
        if (subpgmHeadNode->nodeType == FUNCTION && (subContainsSideEffects || cpndStmtSideEffects))
        {
            // No side effects allowed in function compound_statement or subprogram_declarations.
            fprintf(stderr, "In function name %s\n", subpgmHeadNode->name);
            yyerror("subprogram_declarations contain side effects in subprogram_declaration\n");
        }
        subContainsSideEffects = subContainsSideEffects || cpndStmtSideEffects;
    }

    // Output code for footers of a subprogram
    genCodePrintProcEnd(outFile, getCodeName(topScope->scopeOwner));
    return subContainsSideEffects;
}