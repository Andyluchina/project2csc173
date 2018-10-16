
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "stack.h"
#define FAILED NULL

typedef struct Node *TREE;


struct Node {
    char* label;
    TREE leftmostChild, rightSibling;
};

char* nextTerminal;
char currentCategory;
TREE parseTree;
char* parseTable[8][17];
int numTerminals; //might not need

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

char lookAhead(char* input){
    return input[1];
}

void makeParseTable(){
    //0: 0-9
    //1: "+"
    //2: "-"
    //3: "*"
    //4: "/"
    //5: "$"
    //6: "("
    //7: ")"

    parseTable[0][0] = "RT"; //written in reverse so push in order of char(0), char(1)
    parseTable[0][1] = "RT";
    parseTable[0][2] = "RT";
    parseTable[0][3] = "RT";
    parseTable[0][4] = "RT";
    parseTable[0][5] = "RT";
    parseTable[0][6] = "RT";
    parseTable[0][7] = "RT";
    parseTable[0][8] = "RT";
    parseTable[0][9] = "RT";
    parseTable[0][10] = "K"; //K is error
    parseTable[0][11] = "K";
    parseTable[0][12] = "K";
    parseTable[0][13] = "K";
    parseTable[0][14] = "K";
    parseTable[0][15] = "RT";
    parseTable[0][16] = "K";

    parseTable[1][0] = "K"; //"P" (meaning pop) is equivalent to epsilon
    parseTable[1][1] = "K";
    parseTable[1][2] = "K";
    parseTable[1][3] = "K";
    parseTable[1][4] = "K";
    parseTable[1][5] = "K";
    parseTable[1][6] = "K";
    parseTable[1][7] = "K";
    parseTable[1][8] = "K";
    parseTable[1][9] = "K";
    parseTable[1][10] = "+RT";
    parseTable[1][11] = "-RT";
    parseTable[1][12] = "K";
    parseTable[1][13] = "K";
    parseTable[1][14] = "P"; //not sure how to represent this yet
    parseTable[1][15] = "K";
    parseTable[1][16] = "P";

    parseTable[2][0] = "YF"; //0-9
    parseTable[2][1] = "YF";
    parseTable[2][2] = "YF";
    parseTable[2][3] = "YF";
    parseTable[2][4] = "YF";
    parseTable[2][5] = "YF";
    parseTable[2][6] = "YF";
    parseTable[2][7] = "YF";
    parseTable[2][8] = "YF";
    parseTable[2][9] = "YF";
    parseTable[2][10] = "K"; //+
    parseTable[2][11] = "K"; //-
    parseTable[2][12] = "K"; //*
    parseTable[2][13] = "K"; // /
    parseTable[2][14] = "K"; // $
    parseTable[2][15] = "YF"; // (
    parseTable[2][16] = "K"; // )

    parseTable[3][0] = "K";
    parseTable[3][1] = "K";
    parseTable[3][2] = "K";
    parseTable[3][3] = "K";
    parseTable[3][4] = "K";
    parseTable[3][5] = "K";
    parseTable[3][6] = "K";
    parseTable[3][7] = "K";
    parseTable[3][8] = "K";
    parseTable[3][9] = "K";
    parseTable[3][10] = "P";
    parseTable[3][11] = "P";
    parseTable[3][12] = "*YF";
    parseTable[3][13] = "/YF";
    parseTable[3][14] = "K";
    parseTable[3][15] = "K";
    parseTable[3][16] = "K";

    parseTable[4][0] = "N"; //0-9
    parseTable[4][1] = "N";
    parseTable[4][2] = "N";
    parseTable[4][3] = "N";
    parseTable[4][4] = "N";
    parseTable[4][5] = "N";
    parseTable[4][6] = "N";
    parseTable[4][7] = "N";
    parseTable[4][8] = "N";
    parseTable[4][9] = "N";
    parseTable[4][10] = "K"; //+
    parseTable[4][11] = "K"; //-
    parseTable[4][12] = "K"; //*
    parseTable[4][13] = "K"; // /
    parseTable[4][14] = "K"; // $
    parseTable[4][15] = ")E("; // ( //<N> OR (<E>) NOT SURE YET HOW TO REPRESENT
    parseTable[4][16] = "K"; // )

    parseTable[5][0] = "MD"; //0-9
    parseTable[5][1] = "MD";
    parseTable[5][2] = "MD";
    parseTable[5][3] = "MD";
    parseTable[5][4] = "MD";
    parseTable[5][5] = "MD";
    parseTable[5][6] = "MD";
    parseTable[5][7] = "MD";
    parseTable[5][8] = "MD";
    parseTable[5][9] = "MD";
    parseTable[5][10] = "K"; //+
    parseTable[5][11] = "K"; //-
    parseTable[5][12] = "K"; //*
    parseTable[5][13] = "K"; // /
    parseTable[5][14] = "K"; // $
    parseTable[5][15] = "K"; // (
    parseTable[5][16] = "K"; // )

    parseTable[6][0] = "N"; //0-9
    parseTable[6][1] = "N";
    parseTable[6][2] = "N";
    parseTable[6][3] = "N";
    parseTable[6][4] = "N";
    parseTable[6][5] = "N";
    parseTable[6][6] = "N";
    parseTable[6][7] = "N";
    parseTable[6][8] = "N";
    parseTable[6][9] = "N";
    parseTable[6][10] = "K"; //+
    parseTable[6][11] = "K"; //-
    parseTable[6][12] = "P"; //*
    parseTable[6][13] = "P"; // /
    parseTable[6][14] = "K"; // $
    parseTable[6][15] = "K"; // (
    parseTable[6][16] = "K"; // )

    parseTable[7][0] = "0"; //0-9
    parseTable[7][1] = "1";
    parseTable[7][2] = "2";
    parseTable[7][3] = "3";
    parseTable[7][4] = "4";
    parseTable[7][5] = "5";
    parseTable[7][6] = "6";
    parseTable[7][7] = "7";
    parseTable[7][8] = "8";
    parseTable[7][9] = "9";
    parseTable[7][10] = "K"; //+
    parseTable[7][11] = "K"; //-
    parseTable[7][12] = "K"; //*
    parseTable[7][13] = "K"; // /
    parseTable[7][14] = "K"; // $
    parseTable[7][15] = "K"; // (
    parseTable[7][16] = "K"; // )

//    int duplicateCharacters = 0;
//    for(int i = 0; (unsigned) i < strlen(input) - 1; i++){
//        for(int j = i + 1; (unsigned) j < strlen(input); j++){
//            char first = input[i];
//            char second = input[j];
////            printf("first: %c second: %c\n", first, second);
//
//            if(first == second && i != j){
//                duplicateCharacters++; //may be a possible problem if input is all same number (i.e. 333 makes tempCols = 0)
//            }
//        }
//    }


//    numTerminals = 8;
//    temp = (char**)malloc(8*sizeof(char*)); //allocates 8 syntactic cateogries
//    printf("tempRows: %d ", 8);
//    for(int i=0; i<sizeof(input); i++){
//        temp[i] = (char*)malloc(numTerminals*sizeof(input)); //allocates # of cols by the length of the input aka Non-terminals
//    }
//    printf("tempCols: %d\n", numTerminals);


    //finished allocating memory for the parseTable
    //need to fill in explicit parse table;

//    char**parseTable;
//    parseTable = (char**) malloc(sizeof(char*));

}

char* getProduction(char* character, char* category){
    printf("GP character: %c category: %c\n", *character, *category);
    if(*category == 'E'){ //<E>
        if(*character == '0' || *character == '1' || *character == '2' || *character == '3' || *character == '4' || *character == '5'
           || *character == '6' || *character == '7' || *character == '8' || *character == '9'){
            return parseTable[0][0];
        }
        if(*character == '+'){
            return parseTable[0][10];
        }
        if(*character == '-'){
            return parseTable[0][11];
        }
        if(*character == '*'){
            return parseTable[0][12];
        }
        if(*character == '/'){
            return parseTable[0][13];
        }
        if(*character == '$'){
            return parseTable[0][14];
        }
        if(*character == '('){
            return parseTable[0][15];
        }
        if(*character == ')'){
            return parseTable[0][16];
        }
    }
    if(*category == 'R'){ //<TT>
        if(*character == '0' || *character == '1' || *character == '2' || *character == '3' || *character == '4' || *character == '5'
           || *character == '6' || *character == '7' || *character == '8' || *character == '9'){
            return parseTable[1][0];
        }
        if(*character == '+'){
            return parseTable[1][10];
        }
        if(*character == '-'){
            return parseTable[1][11];
        }
        if(*character == '*'){
            return parseTable[1][12];
        }
        if(*character == '/'){
            return parseTable[1][13];
        }
        if(*character == '$'){
            return parseTable[1][14];
        }
        if(*character == '('){
            return parseTable[1][15];
        }
        if(*character == ')'){
            return parseTable[1][16];
        }
    }
    if(*category == 'T'){ //<T>
        if(*character == '0' || *character == '1' || *character == '2' || *character == '3' || *character == '4' || *character == '5'
           || *character == '6' || *character == '7' || *character == '8' || *character == '9'){
            return parseTable[2][0];
        }
        if(*character == '+'){
            return parseTable[2][10];
        }
        if(*character == '-'){
            return parseTable[2][11];
        }
        if(*character == '*'){
            return parseTable[2][12];
        }
        if(*character == '/'){
            return parseTable[2][13];
        }
        if(*character == '$'){
            return parseTable[2][14];
        }
        if(*character == '('){
            return parseTable[2][15];
        }
        if(*character == ')'){
            return parseTable[2][16];
        }
    }
    if(*category == 'Y'){ //<FT>
        if(*character == '0' || *character == '1' || *character == '2' || *character == '3' || *character == '4' || *character == '5'
           || *character == '6' || *character == '7' || *character == '8' || *character == '9'){
            return parseTable[3][0];
        }
        if(*character == '+'){
            return parseTable[3][10];
        }
        if(*character == '-'){
            return parseTable[3][11];
        }
        if(*character == '*'){
            return parseTable[3][12];
        }
        if(*character == '/'){
            return parseTable[3][13];
        }
        if(*character == '$'){
            return parseTable[3][14];
        }
        if(*character == '('){
            return parseTable[3][15];
        }
        if(*character == ')'){
            return parseTable[3][16];
        }
    }
    if(*category == 'F'){ //<F>
        if(*character == '0' || *character == '1' || *character == '2' || *character == '3' || *character == '4' || *character == '5'
           || *character == '6' || *character == '7' || *character == '8' || *character == '9'){
            return parseTable[4][0];
        }
        if(*character == '+'){
            return parseTable[4][10];
        }
        if(*character == '-'){
            return parseTable[4][11];
        }
        if(*character == '*'){
            return parseTable[4][12];
        }
        if(*character == '/'){
            return parseTable[4][13];
        }
        if(*character == '$'){
            return parseTable[4][14];
        }
        if(*character == '('){
            return parseTable[4][15];
        }
        if(*character == ')'){
            return parseTable[4][16];
        }
    }
    if(*category == 'N'){ //<N>
        if(*character == '0' || *character == '1' || *character == '2' || *character == '3' || *character == '4' || *character == '5'
           || *character == '6' || *character == '7' || *character == '8' || *character == '9'){
            return parseTable[5][0];
        }
        if(*character == '+'){
            return parseTable[5][10];
        }
        if(*character == '-'){
            return parseTable[5][11];
        }
        if(*character == '*'){
            return parseTable[5][12];
        }
        if(*character == '/'){
            return parseTable[5][13];
        }
        if(*character == '$'){
            return parseTable[5][14];
        }
        if(*character == '('){
            return parseTable[5][15];
        }
        if(*character == ')'){
            return parseTable[5][16];
        }
    }
    if(*category == 'M'){ //<NT>
        if(*character == '0' || *character == '1' || *character == '2' || *character == '3' || *character == '4' || *character == '5'
           || *character == '6' || *character == '7' || *character == '8' || *character == '9'){
            return parseTable[6][0];
        }
        if(*character == '+'){
            return parseTable[6][10];
        }
        if(*character == '-'){
            return parseTable[6][11];
        }
        if(*character == '*'){
            return parseTable[6][12];
        }
        if(*character == '/'){
            return parseTable[6][13];
        }
        if(*character == '$'){
            return parseTable[6][14];
        }
        if(*character == '('){
            return parseTable[6][15];
        }
        if(*character == ')'){
            return parseTable[6][16];
        }
    }
    if(*category == 'D'){ //<D>
        if(*character == '0'){
            return parseTable[7][0];
        }
        if(*character == '1'){
            return parseTable[7][1];
        }
        if(*character == '2'){
            return parseTable[7][2];
        }
        if(*character == '3'){
            return parseTable[7][3];
        }
        if(*character == '4'){
            return parseTable[7][4];
        }
        if(*character == '5'){
            return parseTable[7][5];
        }
        if(*character == '6'){
            return parseTable[7][6];
        }
        if(*character == '7'){
            return parseTable[7][7];
        }
        if(*character == '8'){
            return parseTable[7][8];
        }
        if(*character == '9'){
            return parseTable[7][9];
        }
        if(*character == '+'){
            return parseTable[7][10];
        }
        if(*character == '-'){
            return parseTable[7][11];
        }
        if(*character == '*'){
            return parseTable[7][12];
        }
        if(*character == '/'){
            return parseTable[7][13];
        }
        if(*character == '$'){
            return parseTable[7][14];
        }
        if(*character == '('){
            return parseTable[7][15];
        }
        if(*character == ')'){
            return parseTable[7][16];
        }
    }
    return "false";
}

int isTerminal(char* next){
    if((strcmp(next, "0") == 0) || (strcmp(next, "1")) == 0 || (strcmp(next, "2")) == 0 || (strcmp(next, "3")) == 0 ||
       (strcmp(next, "4")) == 0 || (strcmp(next, "5")) == 0 || (strcmp(next, "6")) == 0 || (strcmp(next, "7")) == 0 || (strcmp(next, "8")) == 0
       || (strcmp(next, "9")) == 0 || (strcmp(next, "+")) == 0 || (strcmp(next, "-")) == 0 || (strcmp(next, "*")) == 0 || (strcmp(next, "/")) == 0
       || (strcmp(next, "(")) == 0 || (strcmp(next, ")")) == 0) {
        return 1234567890;
    }
    return 0;
}

int isTerminalChar(char next){
    if(next == '0' || next == '1' || next == '2' || next == '3' || next == '4' || next == '5' || next == '6' || next == '7'
       || next == '8' || next == '9' || next == '+' || next == '-' || next == '*' || next == '/' || next == '(' || next == ')'){
        return 1234567890;
    }

    return 0;
}


//currently infinitely loops because <D> maps to <D>... need to map each to an individual number
TREE tableDrivenParser(char* input){
    struct Stack* s = createStack();
    push(s, "$"); //$ is end marker
    printf("pushed $\n");
    push(s, "E"); //<E>
    printf("pushed E\n");


    while(!isEmpty(s) && strlen(input) > 0){
        printf("strlen(input): %d, input: %s\n", strlen(input), input);

        char popped = pop(s);
        char current = input[0];
        char next = lookAhead(input);



        printf("popped: %c stackSize: %d current: %c next: %c\n", popped, size(s), current, next);
        char* currentProduction = getProduction(&current, &popped);;


        if(strcmp(currentProduction, "false") != 0){
            for(int i = 0; (unsigned) i < strlen(currentProduction); i++){
                if(currentProduction[i] == 'K'){ //means that it is an error
                    break;
                    //possible return NULL;
                }else if(currentProduction[i] == '$'){//should mean end of stack
                    char pop$ = pop(s);
                    printf("popping $: %c\n", pop$);
                }else if(currentProduction[i] == 'P') {//should be equal to an empty string
                    printf("currentProduction[i]: %c\n", currentProduction[i]);
                    char losingChar = pop(s); //I think in this method it pops too much if condition must check if its P and not a category
                    printf("popping without pushing: %c\n", losingChar);
                }else if(isTerminal(&currentProduction[i]) == 1234567890){
                    printf("currentProduction: %s\n", currentProduction);
                    push(s, &currentProduction[i]);
                    printf("pushing Terminal: %s\n", &currentProduction[i]);
                    if(current == currentProduction[i]){
                        printf("current == popped\n");
                        pop(s);
                    }
                    input++;

                }else{
                    push(s, &currentProduction[i]);
                    printf("pushing: %s\n", &currentProduction[i]);
                    printf("stack Size: %d\n", size(s));
                }

            }

        }else{
            printf("NOT A VALID ENTRY\n");
            break;
        }

        printf("strlen2(input): %d, input: %s\n\n", strlen(input), input);
    }
    printf("END WHILE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


//        char* nextProduction = getProduction(next, popped);


    printf("-----------------------------------------------------\n");
    return NULL;

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

//    struct Stack *stack = createStack();
//    push(stack, 'c');
//    printf("%c\n", pop(stack));
//    free_Stack(stack);

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
        makeParseTable();
        //parseTree = E();
        parseTree = tableDrivenParser(input);
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

//make the leaf
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