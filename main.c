
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define FAILED NULL

typedef struct Node *TREE;


struct Node {
    char* label;
    TREE leftmostChild, rightSibling;
};

struct Stack{
    char* stack;
    int top;
};

struct Stack* createStack(){
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    s->stack = (char*)malloc(sizeof(char*));
    s->top = -1;
    return s;
}

void push(struct Stack* s, char c){
    s->top++;
    s->stack[s->top] = c;
}

char pop(struct Stack* s){
    char temp = s->stack[s->top];
    s->stack[s->top]= -1;
    s->top--;
    return temp;
}

char peek(struct Stack* s){
   return s->stack[s->top];
}

int isEmpty(struct Stack* s){
    if(s->top == -1){
        return 1;
    }
    return 0;
}

//not sure if free method is correct
void free_Stack(struct Stack* s){
    free(s);
}

char* nextTerminal;
TREE parseTree;
char** parseTable;
int numTerminals;

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

void parseTable_free(char** parseTable) {
    for (int i = 0; i < numTerminals; i++)
    {
        free(parseTable[i]);
    }
    free(parseTable);
    parseTable = NULL;
}

char** makeParseTable(char* input){
    char** temp;
    int duplicateCharacters = 0;
    for(int i = 0; (unsigned) i < strlen(input) - 1; i++){
        for(int j = i + 1; (unsigned) j < strlen(input); j++){
            char first = input[i];
            char second = input[j];
//            printf("first: %c second: %c\n", first, second);

            if(first == second && i != j){
                duplicateCharacters++; //may be a possible problem if input is all same number (i.e. 333 makes tempCols = 0)
            }
        }
    }
    numTerminals = strlen(input)-duplicateCharacters;
    temp = (char**)malloc(8*sizeof(char*)); //allocates 8 syntactic cateogries
    printf("tempRows: %d ", 8);
    for(int i=0; i<sizeof(input); i++){
        temp[i] = (char*)malloc(numTerminals*sizeof(input)); //allocates # of cols by the length of the input aka Non-terminals
    }
    printf("tempCols: %d\n", numTerminals);

    //finished allocating memory for the parseTable
    //need to fill in explicit parse table;

//    char**parseTable;
//    parseTable = (char**) malloc(sizeof(char*));
    return temp;
}

//IF THE INPUT IS NOT WELL-FORMED, THE PARSER SHOULD PRINT AN APPROPRIATE MESSAGE AND RESUME PROCESSING AT THE NEXT LINE OF INPUT
//(I.E. SKIP TO THE NEXT NEW LINE)

int main(int argc, char* args[]) {
//    struct Stack* s = createStack();
//    printf("s.top: %d\n", s->top);
//    push(s, 'f');
//    printf("s.top: %d\n", s->top);
//    push(s, 'a');
//    printf("s.top: %d\n", s->top);
//    printf("pop: %c s.top: %d\n", pop(s), s->top);
//    printf("peek: %c\n", peek(s));
//    printf("isEmpty: %d\n", isEmpty(s));
//    printf("pop: %c s.top: %d\n", pop(s), s->top);
//    printf("s->top: %d\n", s->top);
//    printf("isEmpty: %d\n", isEmpty(s));
//    free_Stack(s);

    char input[256] = "";
    while (strcmp(input, "quit") != 0) {
        printf("Enter an expression to construct a parse tree using a recursive-descent parser (\"quit\" to quit):");
        //scanf can't read spaces... 32+4 works but 32 + 4 will fail because it tests "32", "+", and "4" separately with 32 and 4 working but failing on +
        //but this is ok(?) because 32 + 4 doesn't work with this code
        //however 32 + 4+32 will work...
        scanf("%s", input); //depreciated but added ability to use depreciated functions
        if(strcmp(input, "quit") == 0){
            break;
        }
        nextTerminal = input; //doesn't work with empty string or spaces

        //what does nextTerminal++ do?

//        printf("nextTerminal: %s \n", nextTerminal);
        parseTable = makeParseTable(input);
        parseTree = E();
        if (*nextTerminal == '\0') {
            printTree(parseTree);
        } else {
            printf("FAILED!\n");
        }
        free(parseTree);
        free(parseTable);
    }
    return 0;
}






TREE makeNodeE(TREE T, TREE TT){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label = "<E>";

    root->leftmostChild = T;
    root->rightSibling = NULL;
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
    leftmostChild->rightSibling = T;
    leftmostChild->leftmostChild = NULL;

    root->leftmostChild = leftmostChild;
    root->rightSibling = NULL;

    T->rightSibling = TT;
    return root;
}

TREE makeNodeF(char* x, TREE E, char* x2){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label ="<F>";

    TREE leftmostChild = makeNodeChar(x);
    leftmostChild->rightSibling = E;
    root->leftmostChild = leftmostChild;

    E->rightSibling= makeNodeChar(x2);

    return root;
}

TREE makeNodeFN(TREE N){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label="<F>";

    root->leftmostChild = N;
    root->rightSibling = NULL;
    return root;
}

TREE makeNodeFT(char* x, TREE F, TREE FT){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label = "<FT>";

    TREE leftmostChild = makeNodeChar(x);
    leftmostChild->rightSibling = F;
    leftmostChild->leftmostChild = NULL;

    root->leftmostChild = leftmostChild;
    root->rightSibling = NULL;
    F->rightSibling = FT;
    return root;
}

TREE makeNodeN(TREE D, TREE NT){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label = "<N>";

    root->leftmostChild = D;
    root->rightSibling = NULL;

    D->rightSibling = NT;

    return root;
}

TREE makeNodeNT(TREE N){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));
    root->label ="<NT>";

    root->leftmostChild = N;
    root->rightSibling = NULL;
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
    TREE root = (TREE) malloc(sizeof(struct Node));
    root->label = label;

    root->leftmostChild = makeNodeChar("e");
    root->rightSibling = NULL;
    return root;
}


TREE makeNodeChar(char* x){
    TREE root;
    root = (TREE) malloc(sizeof(struct Node));


    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}


TREE E() {
    TREE T1, TT1;

    T1 = T();

    if(T1==NULL){
        return FAILED;
    }

    TT1 = TT();
    if(TT1==NULL){
        return FAILED;
    }

    return makeNodeE(T1, TT1);
}

TREE T() {
    TREE F1, FT1;
    F1 = F();
    if(F1==NULL){
        return FAILED;
    }

    FT1 = FT();
    if(FT1==NULL){
        return FAILED;
    }

    return makeNodeT(F1, FT1);
}

TREE TT() {
    TREE T1, TT1;

    if(*nextTerminal == '+'){
        nextTerminal++;
        T1 = T();
        if(T1==NULL){
            return FAILED;
        }
        TT1 = TT();
        if(TT1==NULL){
            return FAILED;
        }
        return makeNodeTT("+", T1, TT1);
    }
    if(*nextTerminal == '-'){
        nextTerminal++;
        T1 = T();
        TT1 = TT();
        if(T1==NULL){
            return FAILED;
        }
        if(TT1==NULL){
            return FAILED;
        }

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
        if(F1==NULL){
            return FAILED;
        }

        FT1 = FT();
        if(FT1==NULL){
            return FAILED;
        }
        return makeNodeFT("*", F1, FT1);
    }
    if(*nextTerminal == '/'){
        nextTerminal++;
        F1 = F();
        if(FT==NULL){
            return FAILED;
        }
        FT1 = FT();
        if(FT1==NULL){
            return FAILED;
        }
        return makeNodeFT("/", F1, FT1);
    }
    else { //EMPTY STRING
        return makeNodeEmpty("<FT>");
    }
}
TREE F(){
    TREE T1;

    if (*nextTerminal == '('){
        nextTerminal++;
        T1 = E();
        if(T1 == NULL){
            return FAILED;
        }
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
        if(T1 == NULL){
            return FAILED;
        }

        return makeNodeFN(T1);
    }
}

TREE N(){
    TREE D1, NT1;
    D1 = D();
    if(D1 == NULL){
        return FAILED;
    }
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
        printTreeRecursively(root->leftmostChild, indent + 3);
    }
    if(root->rightSibling!=NULL){
        printTreeRecursively(root->rightSibling, indent);
    }
}