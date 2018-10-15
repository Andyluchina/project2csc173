#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define FAILED NULL

typedef struct Node *TREE;

struct Node {
    char* label;
    TREE leftmostChild, rightSibling;
};

char* nextTerminal;
TREE parseTree;

TREE E();
TREE T();
TREE TT();
TREE F();
TREE FT();
TREE N();
TREE D();
TREE NT();

void printTree(TREE root);
void printTreeRecursively(TREE root, int indent);
int IsCharDigit(char c);

TREE makeNodeE(TREE T, TREE TT);

TREE makeNodeT(TREE F, TREE FT);

TREE makeNodeTT(char* x, TREE T, TREE TT);

TREE makeNodeF(char* x, TREE E, char* x2);

TREE makeNodeFN(TREE N);

TREE makeNodeFT(char* x, TREE F, TREE FT);

TREE makeNodeN(TREE D, TREE NT);

TREE makeNodeNT(TREE N);

TREE makeNodeD(char* x);

TREE makeNodeChar(char* x);


int main(int argc, char* args[]) {
    nextTerminal = "32+4";
    parseTree = E();
    printTree(parseTree);
    TREE test = makeNodeChar("x");
    printTree (test);
}

TREE makeNodeE(TREE T, TREE TT){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label = "<E>";

    root->leftmostChild = T;
    T->rightSibling = TT;
    return root;
}

TREE makeNodeT(TREE F, TREE FT){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label = "<T>";

    root->leftmostChild = F;
    F->rightSibling = FT;
    return root;
}

TREE makeNodeTT(char* x, TREE T, TREE TT){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label = "<TT>";

    TREE leftmostChild = makeNodeChar(x);
    root->leftmostChild = leftmostChild;
    leftmostChild->rightSibling = T;
    leftmostChild->leftmostChild = NULL;
    T->rightSibling = TT;
    return root;
}

TREE makeNodeF(char* x, TREE E, char* x2){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label ="<F>";

    TREE leftmostChild = makeNodeChar(x);
    leftmostChild->rightSibling = E;
    E->rightSibling= makeNodeChar(x2);
    return root;
}

TREE makeNodeFN(TREE N){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label="<F>";

    root->leftmostChild = N;
    return root;
}

TREE makeNodeFT(char* x, TREE F, TREE FT){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label = "<FT>";

    TREE leftmostChild = makeNodeChar(x);
    leftmostChild->rightSibling = F;

    root->leftmostChild = leftmostChild;
    F->rightSibling = FT;
    return root;
}

TREE makeNodeN(TREE D, TREE NT){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label = "<N>";

    root->leftmostChild = D;
    D->rightSibling = NT;
    return root;
}

TREE makeNodeNT(TREE N){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label ="<NT>";

    root->leftmostChild = N;
    return root;
}

TREE makeNodeD(char* x){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label ="<D>";

    root->leftmostChild = makeNodeChar(x);
    return root;
}

TREE makeNodeEmpty(char* label){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label = label;

    root->leftmostChild = makeNodeChar("e");
    root->rightSibling = NULL;
    return root;
}


TREE makeNodeChar(char* x){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));


    root->label = x;
    printf("reach");
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}


TREE E() {
    TREE Tr, TTr;

    Tr = T();
    printf("reach");

    TTr = TT();

    return makeNodeE(Tr, TTr);
}

TREE T() {
    TREE F1, FT1;
    F1 = F();

    FT1 = FT();

    return makeNodeT(F1, FT1);
}

TREE TT() {
    TREE T1, TT1;

    if(*nextTerminal == '+'){
        nextTerminal++;
        T1 = T();
        TT1 = TT();
        return makeNodeTT("+", T1, TT1);
    }
    if(*nextTerminal == '-'){
        nextTerminal++;
        T1 = T();
        TT1 = TT();
        return makeNodeTT("-", T1, TT1);
    }
    else { //EMPTY STRING
        return makeNodeEmpty("<TT>");
    }
}

TREE FT(){
    TREE F1, FT1;

    if(*nextTerminal == '*'){
        nextTerminal++;
        F1 = F();
        FT1 = FT();
        return makeNodeFT("*", F1, FT1);
    }
    if(*nextTerminal == '/'){
        nextTerminal++;
        F1 = F();
        FT1 = FT();
        return makeNodeFT("/", F1, FT1);
    }
    else { //EMPTY STRING
        return makeNodeEmpty("<FT>");
    }
}
TREE F(){
    TREE T1;
    if (*nextTerminal== '('){
        nextTerminal++;
        T1 = E();
        if (*nextTerminal== ')'){
            nextTerminal++;
            return makeNodeF("(", T1, ")");
        }
        else{
            return FAILED;
        }
    }
    else{

        T1 = N();
        return makeNodeFN(T1);
    }
}

TREE N(){
    TREE D1, NT1;
    D1 = D();
    NT1 = NT();
    return makeNodeN(D1, NT1);
}

TREE NT(){
    TREE t1;
    if(IsCharDigit(*nextTerminal) == 1){
        t1 = N();
        return makeNodeNT(t1);
    }
    else{
        return makeNodeEmpty("<NT>");
    }

}

TREE D(){
    TREE D1;
    if(*nextTerminal == '0'){
        D1 = makeNodeD("0");
        nextTerminal ++;
        return D1;
    }
    if(*nextTerminal == '1'){
        D1 = makeNodeD("1");
        nextTerminal ++;
        return D1;
    }
    if(*nextTerminal == '2'){
        D1 = makeNodeD("2");
        nextTerminal ++;
        return D1;
    }
    if(*nextTerminal == '3'){
        D1 = makeNodeD("3");
        nextTerminal ++;
        return D1;
    }
    if(*nextTerminal == '4'){
        D1 = makeNodeD("4");
        nextTerminal ++;
        return D1;
    }
    if(*nextTerminal == '5'){
        D1 = makeNodeD("5");
        nextTerminal ++;
        return D1;
    }
    if(*nextTerminal == '6'){
        D1 = makeNodeD("6");
        nextTerminal ++;
        return D1;
    }
    if(*nextTerminal == '7'){
        D1 = makeNodeD("7");
        nextTerminal ++;
        return D1;
    }
    if(*nextTerminal == '8'){
        D1 = makeNodeD("8");
        nextTerminal ++;
        return D1;
    }
    if(*nextTerminal == '9'){
        D1 = makeNodeD("9");
        nextTerminal ++;
        return D1;
    }
    else{
        *nextTerminal = 100;
        return FAILED;
    }
}


int IsCharDigit(char c) {
    if ((c >= '0') && (c <= '9')){
        return 1;
    }
    return 0;
}

void printTree(TREE root){
    printTreeRecursively(root, 0);
}

void printTreeRecursively(TREE root, int indent){
    char* label;
    //label = (char*) malloc((indent+5)*sizeof(char));
    label = root->label;
    for(int i = 0; i<indent-1; i++){
        printf(" ");
    }
    printf("%s", label);
    printf("\n");
    if(root->leftmostChild!=NULL){
        printTreeRecursively(root->leftmostChild, indent + 4);
    }
    if(root->rightSibling!=NULL){
        printTreeRecursively(root->rightSibling, indent);
    }

    free(label);
}