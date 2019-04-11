#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "node.h"
#include "scope.h"
#include "y.tab.h"

extern int yyerror( char*);

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
                return exprTree->type;
            }
            else{
                yyerror("ADDOP|MULOP error in getExpressionType");
            }
        }
        else{
            return leftType;
        }
    }
    else if(exprTree->type == ID){
        node_t* nodeMatch = scope_search_all(curScope, exprTree->attribute.sval->name);
        if(!nodeMatch){
            yyerror("ID error in getExpressionType");
        }
        return nodeMatch->data.varInfo.type;
    }
    else if(exprTree->type == FUNCTION_CALL){
        node_t* nodeMatch = scope_search_all(curScope, exprTree->attribute.sval->name);        
        if(!nodeMatch){
            yyerror("FUNCTION_CALL error in getExpressionType");
        }
        return nodeMatch->data.functionInfo.returnType;
    }
    else if(exprTree->type == ARRAY_ACCESS){
        
        // Left node is id, right node is another expression (must be forced to be integer).
        char* arrayId;

        int rightChildType = getExpressionType(curScope, exprTree->rightChild);
        if(rightChildType != INTEGER){
            yyerror("ARRAY_ACCESS NOT INTEGER error in getExpressionType");
        }

        if(!exprTree->leftChild){
            yyerror("ARRAY_ACCESS leftChild error in getExpressionType");
        }
        arrayId = exprTree->leftChild->attribute.sval->name;
        node_t* nodeMatch = scope_search_all(curScope, arrayId);
        if(!nodeMatch){
            yyerror("ARRAY_ACCESS ID error in getExpressionType");
        }
        else{
            if(nodeMatch->data.type != ARRAY){
                yyerror("ARRAY_ACCESS NOT ARRAY error in getExpressionType");
            }
            else{
                return nodeMatch->data.arrayInfo.type;
            }
        }
    }
    else if(exprTree->type == INUM){        
        return INTEGER;
    }
    else if(exprTree->type == RNUM){
        return REAL;
    }    
    else if(exprTree->type == ENTRY_TYPE){
        fprintf(stderr, "GOOO BULSS\n\n%d\n",  exprTree->attribute.sval->data.type);
        return exprTree->attribute.sval->data.type;
    }
    else{
        fprintf(stderr, "\n%d\n\n\n",exprTree->type);
        yyerror("else error in getExpressionType");
    }
}

void validateStatement(scope_t* curScope, tree_t* exprTree){
    if(exprTree == NULL){
        return;
    }
    if(exprTree->type == ASSIGNOP){
        // Left child is variable. Right child is expression
        if(getExpressionType(curScope, exprTree->leftChild) 
            != getExpressionType(curScope, exprTree->rightChild)){
            yyerror("ASSIGNOP error in validateStatement");
        }
    }
    else if(exprTree->type == PROCEDURE_CALL){
        // Procedure call is already validated
    }
    else if(exprTree->type == SEMICOLON){
        // SEMICOLON seperates two statements
        validateStatement(curScope, exprTree->leftChild);
        validateStatement(curScope, exprTree->rightChild);
    }
    else if(exprTree->type == WHILE){
        // SEMICOLON seperates two statements
        int expressionReturnType = getExpressionType(curScope, exprTree->leftChild);
        if(expressionReturnType != BOOLEAN){
            yyerror("WHILE expressionReturnType error in validateStatement");
        }
        validateStatement(curScope, exprTree->rightChild);
    }
    else if(exprTree->type == IF){
        int expressionReturnType = getExpressionType(curScope, exprTree->leftChild);
        if(expressionReturnType != BOOLEAN){
            yyerror("IF expressionReturnType error in validateStatement");
        }
        validateStatement(curScope, exprTree->rightChild);
    }
    else if(exprTree->type == THEN){
        validateStatement(curScope, exprTree->leftChild);
        validateStatement(curScope, exprTree->rightChild);
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
        validateStatement(curScope, exprTree->rightChild->rightChild);
    }    
    
    
}

void validateArguments(node_t* expectedArgs, node_t* actualArgs){
    if(expectedArgs == NULL && actualArgs == NULL){
        return;
    }
    if(expectedArgs == NULL || actualArgs == NULL){
        yyerror("Invalid argument length error in validateArguments");
    }

    if(expectedArgs->data.varInfo.type != actualArgs->data.type){
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
            *head = *cur = insertVarNode(*head, NOT_SET, root->attribute.sval->name);
        }
        else{
            *cur = insertVarNode(*cur, NOT_SET, root->attribute.sval->name);
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

node_t* copyArguments(node_t* oldArgs){
    if(oldArgs == NULL){
        return NULL;
    }
    node_t* copiedArgs = NULL;
    while(oldArgs != NULL){
        if(oldArgs->nodeType == VAR){
            copiedArgs = insertVarNode(copiedArgs, oldArgs->data.varInfo.type, oldArgs->name);
        }
        else if(oldArgs->nodeType == ARRAY){
            copiedArgs = insertArrayNode(copiedArgs, oldArgs->data.arrayInfo.type, 
                            oldArgs->name, oldArgs->data.arrayInfo.dimension);
        }
        oldArgs = oldArgs->next;
    }
    return reverseList(copiedArgs);
}
