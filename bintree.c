//
//  bintree.c
//  AVL_Tree
//
//  Created by Michael Strommer on 02.07.21.
//  Cloned by Salma Abou El-Ezz on 11.07.21.

#include "bintree.h"
#define _CRT_SECURE_NO_WARNINGS

binTree *t_init(){
    binTree *tmp = (binTree *)malloc(sizeof(binTree));
    tmp->root = NULL;
    tmp->size = 0;
    return tmp;
}

// TODO: double pointer einführen oder über return Werte lösen

node *insertNode(node *start, int key, const char *data){           // Knoten einfuegen
    node *newNode;
    if (start == NULL) {
        newNode = (node *) malloc(sizeof(node));
        if (newNode != NULL) {
            newNode->data = (char*) malloc(strlen(data)+1);             // *newNode.data
            strcpy(newNode->data, data);                        
            newNode->key = key;
            newNode->right = newNode->left = NULL;                      // !!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        return newNode;
    }
    if (key < start->key) {
        newNode = insertNode(start->left, key, data);
        if (start->left == NULL)
            start->left = newNode;
        //insert(newNode, key, data);
    } else {
        newNode = insertNode(start->right, key, data);
        if (start->right == NULL)
            start->right = newNode;
        //insert(newNode, key, data);
    }
    
    // TODO: Schritte 1-3
    // 1. Balancefaktor für den "start" Knoten mit Hilfe von treeDepth berechnen                
    // 2. Überprüfung der Lastigkeit
    // 3. Ausführung der einzelnen Rotationen
    
    // as long as unbalanced
    while (treeDepth(newNode) != 0 || treeDepth(newNode) != 1 || treeDepth(newNode) != -1){                            
       // tree unbalanced: left-left 
        if ((treeDepth(newNode -> left) > treeDepth(newNode -> right)) && (treeDepth(newNode -> left -> left) > treeDepth(newNode -> left -> right))) {     
            rotateLL(newNode, key, data);
        }
        // tree unbalanced: left-right 
        else if ((treeDepth(newNode->left) > treeDepth(newNode->right)) && (treeDepth(newNode->left->left) < treeDepth(newNode->left->right))) {
            rotateLR(newNode, key, data);
        }
        // tree unbalanced: right-left 
        else if ((treeDepth(newNode->left) < treeDepth(newNode->right)) && (treeDepth(newNode->left->left) > treeDepth(newNode->left->right))) {
            rotateRL(newNode, key, data);
        }
        // tree unbalanced: right-right 
        else if ((treeDepth(newNode->left) < treeDepth(newNode->right)) && (treeDepth(newNode->left->left) < treeDepth(newNode->left->right))) {
            rotateRR(newNode, key, data);
        }

        return newNode;
    }

    return newNode;
}

node *insert(binTree *t, int key, const char *data){
    node *newNode;
    newNode = insertNode(t->root, key, data);
    if (t->root == NULL) t->root = newNode;
    if (newNode != NULL) t->size++;

    return newNode;
}

int maximum(int a, int b){
    if (a > b) 
        return a;  

    else 
        return b;       
}

int treeDepth(node *start){
    if (start == NULL) {
        return 0;
    }
    else {
        return 1 +  maximum(treeDepth(start->left), treeDepth(start->right));
    }
}

// TODO: Implementierung Rotationen
// rotateLL
node* rotateLL(node* start, int key, const char* data) {           // Knoten einfuegen
    node* temp = (node*)malloc(sizeof(node));
    strcpy(temp->data, data);
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;

    node* nextNode = start->left;
    temp = start;
    start = nextNode;
    start->right = temp;
}
// rotateRL
node* rotateRL(node* start, int key, const char* data) {           // Knoten einfuegen
    node* temp = (node*)malloc(sizeof(node));
    strcpy(temp->data, data);
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;
    
    node* middleNode = start->right;
    temp = start->right->left;
    start->right->right = middleNode;
    start->right = temp;
    start->right->left = NULL;
    rotateLL(start, key, data);

}
// rotateRR
node* rotateRR(node* start, int key, const char* data) {           // Knoten einfuegen
    node* temp = (node*)malloc(sizeof(node));
    strcpy(temp->data, data);
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;

    node* nextNode = start->right;
    temp = start;
    start = nextNode;
    start->left = temp;
}
// rotateLR
node* rotateLR(node* start, int key, const char* data) {           // Knoten einfuegen
    node* temp = (node*)malloc(sizeof(node));
    strcpy(temp->data, data);
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;

    node* middleNode = start->left;
    temp = start->left->right;
    start->left->left = middleNode;
    start->left = temp;
    start->left->right = NULL;
    rotateLL(start, key, data);
}
