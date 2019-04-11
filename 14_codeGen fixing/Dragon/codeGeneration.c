#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "codeGeneration.h"
#include "y.tab.h"


void labelTree(tree_t* root){
    if(root == NULL){
        return;
    }
    else if(root->leftChild == NULL || root->rightChild == NULL){
        // We are at a leaf. This shouldn't happen.
        //fprintf(stderr, "root->leftChild %d   root->rightChild %d\n", root->leftChild, (int)root->rightChild);
        assert(0);
    }
    
    tree_t* leftChild = root->leftChild;
    tree_t* rightChild = root->rightChild;

    // Take care of left subtree.
    if(hasLeftLeaf(root)){
        leftChild->label = 1;
    }
    else{
        labelTree(leftChild);
    }

    // Take care of right subtree.
    if(hasRightLeaf(root)){
        rightChild->label = 0;
    }
    else{
        labelTree(rightChild);
    }
    
    // Label root node.
    if(leftChild->label == rightChild->label){
        root->label = rightChild->label+1;
    }
    else{
        root->label = leftChild->label > rightChild->label ? leftChild->label : rightChild->label;
    }
}
