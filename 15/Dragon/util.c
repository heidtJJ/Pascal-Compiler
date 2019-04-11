#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "node.h"
#include "scope.h"
#include "y.tab.h"

extern int yyerror( char*);
extern unsigned int NO_FUNCTION_RETURN;
extern unsigned int NO_SIDE_EFFECTS;

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
    else if(exprTree->type == ADDOP || exprTree->type == MULOP){
        int leftType = getExpressionType(curScope, exprTree->leftChild);
        if(exprTree->rightChild){
            int rightType = getExpressionType(curScope, exprTree->rightChild);
            if(leftType == rightType){
                return rightType;
            }
            else{
                fprintf(stderr, "OP|MULOPPP  %d   %d\n", leftType, rightType);
                yyerror("ADDOP|MULOP error in getExpressionType");
            }
        }
        else{
            return leftType;
        }
    }
    else if(exprTree->type == ID){
        node_t* nodeMatch = exprTree->attribute.nval;
        if(!nodeMatch){
            fprintf(stderr, "%s %d\n", nodeMatch->name, nodeMatch->nodeType);
            yyerror("ID error in getExpressionType");
        }
        else if(nodeMatch->nodeType == VAR){
            return nodeMatch->data.varInfo.type;
        }
        else if(nodeMatch->nodeType == FUNCTION){
            char* functionName = nodeMatch->name;
            if(curScope->scopeOwner->name != NULL){
                if(strcmp(functionName, curScope->scopeOwner->name)){
                    // functionName is different than scopeOwner name.
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

void validateStatement(scope_t* curScope, tree_t* exprTree, int* flags){
    if(exprTree == NULL){

    }
    else if(exprTree->type == COMPOUND_STATEMENT){
        validateStatement(curScope, exprTree->leftChild, flags);
    }
    else if(exprTree->type == ASSIGNOP){
        if(!exprTree->leftChild || !exprTree->rightChild){
            yyerror("Invalid ASSIGNOP in validateStatement");
        }
        
        // Left child is variable. Right child is expression
        int leftExpressionType = getExpressionType(curScope, exprTree->leftChild);
        int rightExpressionType = getExpressionType(curScope, exprTree->rightChild);
        if(leftExpressionType != rightExpressionType){
            fprintf(stderr, "leftExpressionType %d  rightExpressionType %d\n", leftExpressionType, rightExpressionType);
            yyerror("ASSIGNOP error in validateStatement");
        }

        char* variableName;
        if(exprTree->leftChild->type == ARRAY_ACCESS){
            variableName = exprTree->leftChild->leftChild->attribute.nval->name; 
        }
        else{
            variableName = exprTree->leftChild->attribute.nval->name; 
            fprintf(stderr, "In validateStatement %s %s %X\n", variableName, curScope->scopeOwner->name, *flags);
            fprintf(stderr, "LOL %d \n", !strcmp(variableName, curScope->scopeOwner->name));
            // Check for function return statement.
            if(curScope->scopeOwner->name != NULL){
                if(!strcmp(variableName, curScope->scopeOwner->name)){
                    *flags = *flags & ~NO_FUNCTION_RETURN;
                    fprintf(stderr, "In validateStatement function returns %X\n", *flags);
                    /*fprintf(stderr, "In validateStatement returns %X\n", hasSideEffects(*flags));*/
                    return;// Dont want current statement to trigger a side effect.
                }
            }
        }
        // Check for side effect.
        if(scope_search(curScope, variableName) == NULL){
            // Changing variable outside of cur scope in this statement.
            *flags = *flags & ~NO_SIDE_EFFECTS;
            fprintf(stderr, "In validateStatement %s are side effects %X\n\n", curScope->scopeOwner->name, *flags);
         }        
    }
    else if(exprTree->type == PROCEDURE_CALL){
        // Procedure call is already validated for arguments. Must check side effects.
        node_t* procedureNode = exprTree->leftChild->attribute.nval;
        if(procedureNode == NULL || procedureNode->nodeType != PROCEDURE){
            fprintf(stderr, "procedureNode->nodeType = %d\n", procedureNode->nodeType);
            yyerror("PROCEDURE_CALL error in validateStatement");
        }
        if(procedureNode->data.procedureInfo.hasSideEffects){
            *flags = *flags & ~NO_SIDE_EFFECTS;
        }
    }
    else if(exprTree->type == SEMICOLON){
        // SEMICOLON seperates two statements
        validateStatement(curScope, exprTree->leftChild, flags);
        validateStatement(curScope, exprTree->rightChild, flags);
    }
    else if(exprTree->type == WHILE){
        // SEMICOLON seperates two statements
        int expressionReturnType = getExpressionType(curScope, exprTree->leftChild);
        if(expressionReturnType != BOOLEAN){
            yyerror("WHILE expressionReturnType error in validateStatement");
        }
        validateStatement(curScope, exprTree->rightChild, flags);
    }
    else if(exprTree->type == IF){
        int expressionReturnType = getExpressionType(curScope, exprTree->leftChild);
        if(expressionReturnType != BOOLEAN){
            yyerror("IF expressionReturnType error in validateStatement");
        }
        validateStatement(curScope, exprTree->rightChild, flags);
    }
    else if(exprTree->type == THEN){
        validateStatement(curScope, exprTree->leftChild, flags);
        validateStatement(curScope, exprTree->rightChild, flags);
    }
    else if(exprTree->type == FOR){
        // Left Child is ASSIGNOP tree. Right child is TO tree
        if(!exprTree->leftChild){
            yyerror("FOR leftChild expressionReturnType error in validateStatement");
        }
        if(!exprTree->rightChild){
            yyerror("FOR rightChild expressionReturnType error in validateStatement");
        }
        tree_t* assignOpTree = exprTree->leftChild;
        validateStatement(curScope, exprTree->rightChild->rightChild, flags);
    } 
    else if(exprTree->type == DO){
        tree_t* doStatement = exprTree->leftChild;
        if(!doStatement){
            yyerror("FOR leftChild expressionReturnType error in validateStatement");
        }
        validateStatement(curScope, doStatement, flags);
    } 
    else if(exprTree->type == WRITE){
        tree_t* writeExpression = exprTree->leftChild;
        if(!writeExpression){
            yyerror("FOR leftChild expressionReturnType error in validateStatement");
        }
        /* Validate Expression */
        int expressionType = getExpressionType(curScope, writeExpression);
    } 
    else if(exprTree->type == READ){
        tree_t* readExpression = exprTree->leftChild;
        if(!readExpression){
            yyerror("FOR leftChild expressionReturnType error in validateStatement");
        }
        int expressionType = getExpressionType(curScope, readExpression);
    } 
    else{
        fprintf(stderr, "exprTree->type %d\n", exprTree->type);
        yyerror("NOTHING IN validateStatement");
    }
}

void validateArguments(node_t* expectedArgs, node_t* actualArgs){
    if(expectedArgs == NULL && actualArgs == NULL){
        return;
    }
    if(expectedArgs == NULL || actualArgs == NULL){
        yyerror("Invalid argument length error in validateArguments");
    }
    /*fprintf(stderr, "expectedArgs %d     actualArgs %d\n", expectedArgs, actualArgs);*/

    if(expectedArgs->data.varInfo.type != actualArgs->data.varInfo.type){
        yyerror("Invalid argument input error in validateArguments");
    }
    validateArguments(expectedArgs->next, actualArgs->next);
}

void convertToNameListUtil(node_t** head, node_t** cur, tree_t* root){
    if(root == NULL){
        return;
    }
    convertToNameListUtil(head, cur, root->rightChild);
    if(root->type == ID){
        if((*head) == NULL){
            *head = *cur = insertVarNode(*head, NOT_SET, root->attribute.nval->name);
        }
        else{
            *cur = insertVarNode(*cur, NOT_SET, root->attribute.nval->name);
        }
    }
    else if(root->type == COMMA){

    }
    else{
        yyerror("Error in convertToNameListUtil");
    }
    convertToNameListUtil(head, cur, root->leftChild);
}

/* Convert to a linked list of argument names (strings)*/
node_t* convertToNameList(tree_t* parameterTree){
    node_t* head = NULL;
    node_t* cur = NULL;

    convertToNameListUtil(&head, &cur, parameterTree);
    return head;
}

node_t* reverseList(node_t* top){
    if(top == NULL){
        return NULL;
    }
    node_t* prev = NULL;
    node_t* cur = top;
    node_t* next = top->next;
    while(next != NULL){
        cur->next = prev;
        prev = cur;
        cur = next;
        next = next->next;
    }
    return cur;
}

int hasSideEffects(int flags){
    if(!(flags & NO_SIDE_EFFECTS)){
        return 1;
    }
    return 0;
}
int hasNoReturnStmt(int flags){
    if(flags & NO_FUNCTION_RETURN){
        return 1;
    }
    return 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}
