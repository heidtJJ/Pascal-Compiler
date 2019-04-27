#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "node.h"
#include "scope.h"
#include "treeList.h"
#include "y.tab.h"

extern int yyerror( char*);
extern unsigned int NO_FUNCTION_RETURN;
extern unsigned int NO_SIDE_EFFECTS;

/*
    Given flags, return if the NO_SIDE_EFFECTS bit
    is not set.
*/
int hasSideEffects(int flags){
    if(!(flags & NO_SIDE_EFFECTS)){
        return 1;
    }
    return 0;
}

/*
    Given flags, return if the NO_FUNCTION_RETURN bit
    is set.
*/
int hasNoReturnStmt(int flags){
    if(flags & NO_FUNCTION_RETURN){
        return 1;
    }
    return 0;
}

/*
    Prints a variable number of spaces to 
    stderr.
*/
void print_spaces(int numSpaces){
    for(int i = 0; i < numSpaces; ++i){
        fprintf(stderr, " ");
    }
}

/*
    Classic max function :)
*/
int max(int a, int b) {
    return a > b ? a : b;
}

/*
    Finds the maximum number of arguments for a function
    or procedure in a tree_t. maxNumArguments is dereferenced
    to change its value.
*/
void findMaxNumArgsUtil(tree_t* root, int* maxNumArguments){
    if(root == NULL){
        return;
    }
    else if(root->type == PROCEDURE_CALL || root->type == FUNCTION_CALL
            && root->rightChild != NULL){
        TreeList* arguments = root->rightChild->attribute.listVal;
        if(arguments->listLength > *maxNumArguments){
            *maxNumArguments = arguments->listLength;
        }
    }
    findMaxNumArgsUtil(root->leftChild, maxNumArguments);
    findMaxNumArgsUtil(root->rightChild, maxNumArguments);
}

/*
    Uses findMaxNumArgsUtil to find the maximum number of 
    arguments for a procedure or function in a list of
    statments.
*/
void findMaxNumArguments(TreeList* expressionList, int* maxNumArguments){
    if(!expressionList){
        return;
    }
    TreeList* curExpr = expressionList;
    while(curExpr != NULL){
        tree_t* curTree = curExpr->statementTree;
        assert(curTree != NULL);
        findMaxNumArgsUtil(curTree, maxNumArguments);
        curExpr = curExpr->next;
    }
}

int validateID(scope_t* curScope, tree_t* exprTree){
    node_t* nodeMatch = exprTree->attribute.nval;
    if(!nodeMatch){
        fprintf(stderr, "%s %d\n", nodeMatch->name, nodeMatch->nodeType);
        yyerror("ID error in getExpressionType");
    }
    else if(nodeMatch->nodeType == VAR){
        return nodeMatch->data.varInfo.type;
    }
    else if(nodeMatch->nodeType == FUNCTION){
        tree_print(exprTree);
        char* functionName = nodeMatch->name;
        if(curScope->scopeOwner->name != NULL){
            if(strcmp(functionName, curScope->scopeOwner->name)){
                // functionName is different than scopeOwner name.
                fprintf(stderr, "STR1 %s   STR2 %s\n", functionName, curScope->scopeOwner->name);
                yyerror("ID functionName is different than scopeOwner name in getExpressionType");
            }
        }
        else{
            yyerror("ID scopeOwner name == NULL in getExpressionType");
        }
        return nodeMatch->data.functionInfo.returnType;
    }
    else{
        assert(nodeMatch->nodeType == PROCEDURE);
        yyerror("PROCEDURE ID error in getExpressionType");
    }
}

/*
    Returns the return type of an expression tree. ALSO
    validates the expression while evaluating the type.

*/
int getExpressionType(scope_t* curScope, tree_t* exprTree){
    if(exprTree == NULL){
        yyerror("NULL error in getExpressionType");
    }

    if(exprTree->type == RELOP){
        // Return should be boolean
        if(getExpressionType(curScope, exprTree->leftChild) 
            == getExpressionType(curScope, exprTree->rightChild)){
            return BOOLEAN;
        }
        else{
            yyerror("RELOP error in getExpressionType");
        }
    }
    else if(exprTree->type == ADDOP){
        // There may not always be a right child with ADDOPs.
        int leftType = getExpressionType(curScope, exprTree->leftChild);
        if(exprTree->rightChild){
            int rightType = getExpressionType(curScope, exprTree->rightChild);
            // Make sure that the types match.
            if(leftType == rightType){
                return rightType;
            }
            else{
                yyerror("ADDOP error in getExpressionType");
            }
        }
        else{
            return leftType;
        }
    }
    else if(exprTree->type == MULOP){
        // Retrieve the types of the children.
        int leftType = getExpressionType(curScope, exprTree->leftChild);
        int rightType = getExpressionType(curScope, exprTree->rightChild);
        if(leftType == rightType){
            return rightType;
        }
        else{
            fprintf(stderr, "MULOPPP  %d   %d\n", leftType, rightType);
            yyerror("MULOP error in getExpressionType");
        }
    }
    else if(exprTree->type == ID){
        return validateID(curScope, exprTree);
    }
    else if(exprTree->type == FUNCTION_CALL){
        node_t* nodeMatch = scope_search_all(curScope, exprTree->leftChild->attribute.nval->name);        
        if(!nodeMatch){
            yyerror("FUNCTION_CALL error in getExpressionType");
        }
        return nodeMatch->data.functionInfo.returnType;
    }
    else if(exprTree->type == ARRAY_ACCESS){
        /* Left node is arrray id, rightChild is the indexing value (must be forced to be integer). */
        int rightChildType = getExpressionType(curScope, exprTree->rightChild);
        if(rightChildType != INTEGER){
            yyerror("ARRAY_ACCESS index NOT INTEGER error in getExpressionType");
        }
        if(!exprTree->leftChild){
            yyerror("ARRAY_ACCESS leftChild error in getExpressionType");
        }

        node_t* arrayNode = exprTree->leftChild->attribute.nval;
        if(!arrayNode){
            yyerror("ARRAY_ACCESS ID error in getExpressionType");
        }
        else{
            if(arrayNode->nodeType != VAR || arrayNode->data.varInfo.isArray == NOT_ARRAY){
                yyerror("ARRAY_ACCESS NOT ARRAY error in getExpressionType");
            }
            else{
                return arrayNode->data.varInfo.type;
            }
        }
    }
    else if(exprTree->type == INUM){        
        return INTEGER;
    }
    else if(exprTree->type == RNUM){
        return REAL;
    }    
    else{
        yyerror("else error in getExpressionType");
    }
}

/*
    Given a statement tree, validate all aspects of the statement
    according to the grammar. Remember, getExpressionType also 
    validates each expression.
*/
void validateStatement(scope_t* curScope, tree_t* stmtTree, int* flags){
    if(stmtTree == NULL){
        return;
    }
    // Retrieve the children of the statement tree.
    tree_t* leftChild = stmtTree->leftChild;
    tree_t* rightChild = stmtTree->rightChild;

    // Check for all types of statements.
    if(stmtTree->type == COMPOUND_STATEMENT){
        validateStatement(curScope, leftChild, flags);
    }
    else if(stmtTree->type == ASSIGNOP){
        if(!leftChild || !rightChild){
            yyerror("Invalid ASSIGNOP in validateStatement");
        }
        
        // Left child is variable. Right child is expression. Validate both.
        int leftExpressionType = getExpressionType(curScope, leftChild);
        int rightExpressionType = getExpressionType(curScope, rightChild);
        if(leftExpressionType != rightExpressionType){
            fprintf(stderr, "leftExpressionType %d  rightExpressionType %d\n", leftExpressionType, rightExpressionType);
            yyerror("ASSIGNOP error in validateStatement");
        }

        char* variableName;
        if(leftChild->type == ARRAY_ACCESS){
            variableName = leftChild->leftChild->attribute.nval->name; 
        }
        else{
            variableName = leftChild->attribute.nval->name; 
            // Check for function return statement.
            if(curScope->scopeOwner->name != NULL){
                if(!strcmp(variableName, curScope->scopeOwner->name)){
                    // The current function has a return statement.
                    *flags = *flags & ~NO_FUNCTION_RETURN;
                    // Dont want current statement to trigger a side effect so return.
                    return;
                }
            }
        }
        // Check for side effect.
        if(scope_search(curScope, variableName) == NULL){
            // Changing variable outside of scope in this 
            // statement. Indicate this in flags.
            *flags = *flags & ~NO_SIDE_EFFECTS;
            fprintf(stderr, "In validateStatement %s are side effects %X\n\n", curScope->scopeOwner->name, *flags);
         }        
    }
    else if(stmtTree->type == PROCEDURE_CALL){
        // Procedure call is already validated for arguments. Must check side effects.
        node_t* procedureNode = leftChild->attribute.nval;
        if(procedureNode == NULL || procedureNode->nodeType != PROCEDURE){
            yyerror("PROCEDURE_CALL error in validateStatement");
        }
        if(procedureNode->data.procedureInfo.hasSideEffects){
            // Side effects do occured in this called procedure.
            *flags = *flags & ~NO_SIDE_EFFECTS;
        }
    }
    else if(stmtTree->type == SEMICOLON){
        // SEMICOLON seperates two statements
        validateStatement(curScope, leftChild, flags);
        validateStatement(curScope, rightChild, flags);
    }
    else if(stmtTree->type == WHILE){
        // SEMICOLON seperates two statements
        int expressionReturnType = getExpressionType(curScope, leftChild);
        if(expressionReturnType != BOOLEAN){
            yyerror("WHILE expressionReturnType error in validateStatement");
        }
        validateStatement(curScope, rightChild, flags);
    }
    else if(stmtTree->type == IF){
        int expressionReturnType = getExpressionType(curScope, leftChild);
        if(expressionReturnType != BOOLEAN){
            yyerror("IF expressionReturnType error in validateStatement");
        }
        validateStatement(curScope, rightChild, flags);
    }
    else if(stmtTree->type == THEN){
        // Left child is the then statement.
        validateStatement(curScope, leftChild, flags);
        // Right child is the else statement.
        validateStatement(curScope, rightChild, flags);
    }
    else if(stmtTree->type == FOR){
        // Left Child is ASSIGNOP tree. Right child is TO tree
        if(!leftChild){
            yyerror("FOR leftChild expressionReturnType error in validateStatement");
        }
        if(!rightChild){
            yyerror("FOR rightChild expressionReturnType error in validateStatement");
        }
        tree_t* assignOpTree = leftChild;
        validateStatement(curScope, rightChild->rightChild, flags);
    } 
    else if(stmtTree->type == DO){
        tree_t* doStatement = leftChild;
        if(!doStatement){
            yyerror("FOR leftChild expressionReturnType error in validateStatement");
        }
        // Validate the do statement.
        validateStatement(curScope, doStatement, flags);
    } 
    else if(stmtTree->type == WRITE){
        tree_t* writeExpression = leftChild;
        if(!writeExpression){
            yyerror("FOR leftChild expressionReturnType error in validateStatement");
        }
        // Validate the write expression.
        int expressionType = getExpressionType(curScope, writeExpression);
    } 
    else if(stmtTree->type == READ){
        tree_t* readExpression = leftChild;
        if(!readExpression){
            yyerror("FOR leftChild expressionReturnType error in validateStatement");
        }
        // Validate the read expression.
        int expressionType = getExpressionType(curScope, readExpression);
    } 
    else{
        fprintf(stderr, "stmtTree->type %d\n", stmtTree->type);
        yyerror("NOTHING IN validateStatement");
    }
}

/*
    Validate the actual arguments according to the expected
    arguements. Validate the length and argument types. 
*/
void validateArguments(scope_t* top_scope, node_t* expectedArgsList, TreeList* actualArgsList){
    if(expectedArgsList == NULL && actualArgsList == NULL){
        return;
    }
    if(expectedArgsList == NULL || actualArgsList == NULL){
        yyerror("Invalid argument length error in validateArguments");
    }
    int expectedArgType = expectedArgsList->data.varInfo.type;
    int actualArgType = getExpressionType(top_scope, actualArgsList->statementTree);

    if(expectedArgType != actualArgType){
        yyerror("Invalid argument input error in validateArguments");
    }
    // Recurse to validate the next argument.
    validateArguments(top_scope, expectedArgsList->next, actualArgsList->next);
}