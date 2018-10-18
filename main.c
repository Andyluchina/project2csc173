
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

//
// Created by Andy on 10/15/2018.
// Refactored header file: a working stack! you are welcome!

struct Stack2
{
    int top;
    unsigned capacity;
    TREE* TreeArray;
};

// function to create a stack2 of given capacity. It initializes size of 
// stack2 as 0 
struct Stack2* createStack2(unsigned capacity)
{
    struct Stack2* stack2 = (struct Stack2*) malloc(sizeof(struct Stack2));
    stack2->capacity = capacity;
    stack2->top = -1;
    stack2->TreeArray = (TREE*) malloc(stack2->capacity * sizeof(TREE));
    return stack2;
}

// stack2 is empty when top is equal to -1 
int isEmpty2(struct Stack2* stack2)
{   return stack2->top == -1;  }

// Function to add an item to stack2.  It increases top by 1 
void push2(struct Stack2* stack2, TREE item)
{
    stack2->TreeArray[++stack2->top] = item;
}

// Function to remove an item from stack2.  It decreases top by 1 
TREE pop2(struct Stack2* stack2)
{
    return stack2->TreeArray[stack2->top--];
}
int size2(struct Stack2* s2){
    return s2->top;
}

#ifndef PROJECT2CSC173_STACK_H
#define PROJECT2CSC173_STACK_H

#endif //PROJECT2CSC173_STACK_H

char* nextTerminal;
TREE parseTree;
char* parseTable[8][17];

TREE E();
TREE T();
TREE TT();
TREE F();
TREE FT();
TREE N();
TREE D();
TREE NT();

void freeTree(TREE node);

void printTree(TREE root);
void printTreeRecursively(TREE root, int indent);
int IsCharDigit(char c);


TREE makeNodeE(TREE T, TREE TT);

TREE makeNodeEmpty(char* label);

TREE makeNodeT(TREE F, TREE FT);

TREE makeNodeTT(char* x, TREE T, TREE TT);

TREE makeNodeF(char* x, TREE E, char* x2);

TREE makeNodeFN(TREE N);

TREE makeNodeFT(char* x, TREE F, TREE FT);

TREE makeNodeN(TREE D, TREE NT);

TREE makeNodeNT(TREE N);

TREE makeNodeD(char* x);

TREE makeNodeChar(char* x);

//PART THREE DECLARATIONS
char* concat(const char*, const char*);
void parseN(TREE root);
void stripParenthesis(TREE root);
double evalE(TREE root);
double Fhandler(TREE root);
double Thandler(TREE root);
double EvaluateParseTree(TREE root);


void makeParseTable(){ //FUNCTION TO MAKE PARSE TABLE
    parseTable[0][0] = "ZRT"; //written in reverse so push in order of char(0), char(1)
    parseTable[0][1] = "ZRT";
    parseTable[0][2] = "ZRT";
    parseTable[0][3] = "ZRT";
    parseTable[0][4] = "ZRT";
    parseTable[0][5] = "ZRT";
    parseTable[0][6] = "ZRT";
    parseTable[0][7] = "ZRT";
    parseTable[0][8] = "ZRT";
    parseTable[0][9] = "ZRT";
    parseTable[0][10] = "K"; //K is error
    parseTable[0][11] = "K";
    parseTable[0][12] = "K";
    parseTable[0][13] = "K";
    parseTable[0][14] = "K";
    parseTable[0][15] = "ZRT";
    parseTable[0][16] = "K";

    parseTable[1][0] = "QP"; //"QP" (meaning pop) is equivalent to epsilon
    parseTable[1][1] = "QP";
    parseTable[1][2] = "QP";
    parseTable[1][3] = "QP";
    parseTable[1][4] = "QP";
    parseTable[1][5] = "QP";
    parseTable[1][6] = "QP";
    parseTable[1][7] = "QP";
    parseTable[1][8] = "QP";
    parseTable[1][9] = "QP";
    parseTable[1][10] = "XRT+";
    parseTable[1][11] = "XRT-";
    parseTable[1][12] = "QP";
    parseTable[1][13] = "QP";
    parseTable[1][14] = "QP"; //not sure how to represent this yet
    parseTable[1][15] = "QP";
    parseTable[1][16] = "QP";

    parseTable[2][0] = "CYF"; //0-9
    parseTable[2][1] = "CYF";
    parseTable[2][2] = "CYF";
    parseTable[2][3] = "CYF";
    parseTable[2][4] = "CYF";
    parseTable[2][5] = "CYF";
    parseTable[2][6] = "CYF";
    parseTable[2][7] = "CYF";
    parseTable[2][8] = "CYF";
    parseTable[2][9] = "CYF";
    parseTable[2][10] = "K"; //+
    parseTable[2][11] = "K"; //-
    parseTable[2][12] = "K"; //*
    parseTable[2][13] = "K"; // /
    parseTable[2][14] = "K"; // $
    parseTable[2][15] = "CYF"; // (
    parseTable[2][16] = "K"; // )

    parseTable[3][0] = "LP";
    parseTable[3][1] = "LP";
    parseTable[3][2] = "LP";
    parseTable[3][3] = "LP";
    parseTable[3][4] = "LP";
    parseTable[3][5] = "LP";
    parseTable[3][6] = "LP";
    parseTable[3][7] = "LP";
    parseTable[3][8] = "LP";
    parseTable[3][9] = "LP";
    parseTable[3][10] = "LP";
    parseTable[3][11] = "LP";
    parseTable[3][12] = "VYF*";
    parseTable[3][13] = "VYF/";
    parseTable[3][14] = "LP";
    parseTable[3][15] = "LP";
    parseTable[3][16] = "LP";

    parseTable[4][0] = "BN"; //0-9
    parseTable[4][1] = "BN";
    parseTable[4][2] = "BN";
    parseTable[4][3] = "BN";
    parseTable[4][4] = "BN";
    parseTable[4][5] = "BN";
    parseTable[4][6] = "BN";
    parseTable[4][7] = "BN";
    parseTable[4][8] = "BN";
    parseTable[4][9] = "BN";
    parseTable[4][10] = "K"; //+
    parseTable[4][11] = "K"; //-
    parseTable[4][12] = "K"; //*
    parseTable[4][13] = "K"; // /
    parseTable[4][14] = "K"; // $
    parseTable[4][15] = "H)E("; // ( //<N> OR (<E>) NOT SURE YET HOW TO REPRESENT
    parseTable[4][16] = "K"; // )

    parseTable[5][0] = "JMD"; //0-9
    parseTable[5][1] = "JMD";
    parseTable[5][2] = "JMD";
    parseTable[5][3] = "JMD";
    parseTable[5][4] = "JMD";
    parseTable[5][5] = "JMD";
    parseTable[5][6] = "JMD";
    parseTable[5][7] = "JMD";
    parseTable[5][8] = "JMD";
    parseTable[5][9] = "JMD";
    parseTable[5][10] = "K"; //+
    parseTable[5][11] = "K"; //-
    parseTable[5][12] = "K"; //*
    parseTable[5][13] = "K"; // /
    parseTable[5][14] = "K"; // $
    parseTable[5][15] = "K"; // (
    parseTable[5][16] = "K"; // )

    parseTable[6][0] = "ON"; //0-9
    parseTable[6][1] = "ON";
    parseTable[6][2] = "ON";
    parseTable[6][3] = "ON";
    parseTable[6][4] = "ON";
    parseTable[6][5] = "ON";
    parseTable[6][6] = "ON";
    parseTable[6][7] = "ON";
    parseTable[6][8] = "ON";
    parseTable[6][9] = "ON";
    parseTable[6][10] = "SP"; //+
    parseTable[6][11] = "SP"; //-
    parseTable[6][12] = "SP"; //*
    parseTable[6][13] = "SP"; // /
    parseTable[6][14] = "SP"; // $
    parseTable[6][15] = "SP"; // (
    parseTable[6][16] = "SP"; // )

    parseTable[7][0] = "U0"; //0-9
    parseTable[7][1] = "U1";
    parseTable[7][2] = "U2";
    parseTable[7][3] = "U3";
    parseTable[7][4] = "U4";
    parseTable[7][5] = "U5";
    parseTable[7][6] = "U6";
    parseTable[7][7] = "U7";
    parseTable[7][8] = "U8";
    parseTable[7][9] = "U9";
    parseTable[7][10] = "K"; //+
    parseTable[7][11] = "K"; //-
    parseTable[7][12] = "K"; //*
    parseTable[7][13] = "K"; // /
    parseTable[7][14] = "K"; // $
    parseTable[7][15] = "K"; // (
    parseTable[7][16] = "K"; // )
}

char* getProduction(const char* character, const char* category){
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


int isTerminalChar(char next){
    if(next == '0' || next == '1' || next == '2' || next == '3' || next == '4' || next == '5' || next == '6' || next == '7'
       || next == '8' || next == '9' || next == '+' || next == '-' || next == '*' || next == '/' || next == '(' || next == ')' || next == '$') {
        return 1234567890;
    }

    return 0;
}

TREE tableDrivenParser(){
    struct Stack* s = createStack();
    struct Stack2* s2 = createStack2(30);
    char current = nextTerminal[0];


    push(s, "$"); //$ is end marker
    push(s, "E"); //<E>


    while(!isEmpty(s) || strlen(nextTerminal) > 0){
        current = *nextTerminal;
        char popped = pop(s);

        if(popped == '$'){

        }
        else if((isTerminalChar(popped)) == 1234567890){
            //FOR EACH ADD IF STATEMENT AND PUSH
            if(popped == '0'){
                push2(s2, makeNodeChar("0"));
            }
            else if(popped == '1'){
                push2(s2, makeNodeChar("1"));
            }
            else if(popped == '2'){
                push2(s2, makeNodeChar("2"));
            }
            else if(popped == '3'){
                push2(s2, makeNodeChar("3"));
            }
            else if(popped == '4'){
                push2(s2, makeNodeChar("4"));
            }
            else if(popped == '5'){
                push2(s2, makeNodeChar("5"));
            }
            else if(popped == '6'){
                push2(s2, makeNodeChar("6"));
            }
            else if(popped == '7'){
                push2(s2, makeNodeChar("7"));
            }
            else if(popped == '8'){
                push2(s2, makeNodeChar("8"));
            }
            else if(popped == '9'){
                push2(s2, makeNodeChar("9"));
            }
            else if(popped == '('){
                push2(s2, makeNodeChar("("));
            }
            else if(popped == ')'){
                push2(s2, makeNodeChar(")"));
            }
            else if(popped == '+'){
                push2(s2, makeNodeChar("+"));
            }
            else if(popped == '-'){
                push2(s2, makeNodeChar("-"));
            }
            else if(popped == '/'){
                push2(s2, makeNodeChar("/"));
            }
            else if(popped == '*'){
                push2(s2, makeNodeChar("*"));
            }
        }

        if (current == '$' && popped == '$') { //IF WE DID IT
            nextTerminal++;
            return pop2(s2);
        }
        else if((isTerminalChar(popped)) == 1234567890 ){ //IF THE POPPED IS A TERMINAL
            if(popped == current){
                nextTerminal++;
            }
            else{
                return NULL;
            }
        }

            //IF THE POPPED IS ACTION CHARACTER IS POPPED FOR CREATING THE PARSE TREE
        else if(popped =='U'){ //<D> production
            TREE numTree = pop2(s2);
            char*num = numTree->label;
            TREE t = makeNodeD(num);
            push2(s2, t);
        }
        else if(popped == 'Z'){ //THIS IS <E>
            TREE TT = pop2(s2);
            TREE T = pop2(s2);
            TREE pop = makeNodeE(T, TT);
            push2(s2, pop);
        }
        else if(popped =='X'){ //THIS IS <TT>

            TREE TT = pop2(s2);
            TREE T = pop2(s2);
            TREE cha = pop2(s2);
            char* x =  cha->label;
            TREE pop = makeNodeTT(x, T, TT);
            push2(s2, pop);
        }
        else if(popped =='Q'){ //THIS IS <TT> with epsilon
            push2(s2, makeNodeEmpty("<TT>"));
        }
        else if(popped =='C'){ // This is <T>
            TREE FT = pop2(s2);
            TREE F = pop2(s2);
            TREE pop= makeNodeT(F,FT);
            push2(s2, pop);
        }
        else if(popped =='V'){ // This is <FT>

            TREE TT = pop2(s2);
            TREE T = pop2(s2);
            TREE cha = pop2(s2);
            char* x =  cha->label;
            TREE pop = makeNodeFT(x, T, TT);
            push2(s2, pop);
        }
        else if(popped =='L'){ //This is <FT> with epsilon production
            // TREE po= pop2(s2);
            // printTree(po);
            push2(s2, makeNodeEmpty("<FT>"));
        }
        else if(popped =='B'){ //This is <F> with <N> prodcution
            TREE n = pop2(s2);
            push2(s2, makeNodeFN(n));
        }
        else if(popped =='H'){ //This is <F> with (E) production
            TREE cha = pop2(s2);
            char* right =  cha->label;
            TREE E = pop2(s2);
            TREE cha2 = pop2(s2);
            char* left =  cha2->label;
            TREE pop = makeNodeF(left, E, right);
            push2(s2, pop);
        }
        else if(popped == 'J'){ // <N> production
            TREE NT = pop2(s2);
            TREE D = pop2(s2);
            push2(s2, makeNodeN(D, NT));
        }
        else if(popped =='O'){ // <NT> production
            TREE N = pop2(s2);
            push2(s2, makeNodeNT(N));
        }
        else if(popped =='S'){ //<NT> epsilon prduction
            push2(s2, makeNodeEmpty("<NT>"));
        }

        else { //IF THE POPPED IS A SYNTACTIC CATEGORY
            char* currentProduction = getProduction(&current, &popped);
            if( strcmp(currentProduction, "K") ==0){
                return NULL;
            }
            if (strcmp(currentProduction, "false") != 0) {
                for (int i = 0; (unsigned) i < strlen(currentProduction); i++) {
                    if (currentProduction[i] == 'K') { //means that it is an error
                        return NULL;
                    } else if (currentProduction[i] == 'P') {//should be equal to an empty string
                    } else {
                        push(s, &currentProduction[i]);
                    }

                }

            } else {
                free_Stack(s);
                free(s2->TreeArray);
                free(s2);
                break;
            }
        }
    }

    return NULL;

}

void expr(){
    char input[256] = "";
    char input2[256] = "";
    while (strcmp(input, "quit") != 0) {
        printf("Enter an expression to construct a parse tree using a recursive-descent parser (\"quit\" to quit):");
        scanf("%s", input); //depreciated but added ability to use depreciated functions
        strcpy(input2, input);
        if(strcmp(input, "quit") == 0){
            break;
        }
        nextTerminal = strcat(input, "");

        parseTree = E();

        if (*nextTerminal == '\0' && parseTree != NULL) {
            printTree(parseTree);
            printf("THE TREE ANSWER: %f \n", EvaluateParseTree(parseTree));

        } else {
            printf("FAILED!\n");
        }


        printf("Constructing a parse tree using the input, %s, for a TABLE-DRIVEN PARSER\n", input2);

        nextTerminal = strcat(input2, "$"); //doesn't work with empty string or spaces
        makeParseTable();
        TREE parseTree2 = tableDrivenParser();
        if (*nextTerminal == '\0' && parseTree2 != NULL) {
            printTree(parseTree2);
            printf("THE TREE ANSWER: %f \n", EvaluateParseTree(parseTree2));
        } else {
            printf("FAILED!\n");
        }

    }


}


int main(int argc, char* args[]) {
    expr();
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
    root->rightSibling = NULL;

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
    leftmostChild->leftmostChild = NULL;

    root->leftmostChild = leftmostChild;
    root->rightSibling = NULL;

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
    root->rightSibling = NULL;
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
        if(T1==NULL){
            return FAILED;
        }
        TT1 = TT();
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
        if(F1==NULL){
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
    if(NT1 == NULL){
        return FAILED;
    }

    return makeNodeN(D1, NT1);
}

TREE NT(){
    TREE t1;
    if(IsCharDigit(*nextTerminal) == 1){
        t1 = N();
        if(t1 == NULL){
            return FAILED;
        }
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

int good=0;
//this is part3
double EvaluateParseTree(TREE root){
    good=0;
    parseN(root);
    stripParenthesis(root);
    return evalE(root);
}


double evalE(TREE root){
    return Thandler(root->leftmostChild);
}

double Fhandler(TREE root){
    if(strcmp(root->rightSibling->leftmostChild->label,"e")==0){
        //don't have a sign
        if(strcmp(root->leftmostChild->label,"<E>")==0){
            return evalE(root->leftmostChild);
        }else{
            return atof(root->leftmostChild->label);
        }
    }else{
        //have a sign
        if(strcmp(root->leftmostChild->label,"<E>")==0){
            if(strcmp(root->rightSibling->leftmostChild->label,"*")==0){
                //*
                return evalE(root->leftmostChild) * Fhandler(root->rightSibling->leftmostChild->rightSibling);
            }else{
                //going to be /
                return evalE(root->leftmostChild) / Fhandler(root->rightSibling->leftmostChild->rightSibling);
            }
        }else{
            if(strcmp(root->rightSibling->leftmostChild->label,"*")==0){
                //*
                return atof(root->leftmostChild->label) * Fhandler(root->rightSibling->leftmostChild->rightSibling);
            }else{
                //going to be /
                return atof(root->leftmostChild->label) / Fhandler(root->rightSibling->leftmostChild->rightSibling);
            }
        }
    }
}



double Thandler(TREE root){
//            if(strcmp(root->rightSibling->leftmostChild->label,"+")==0){
//                //going to be +
//                return  Fhandler(root->leftmostChild) + Thandler(root->rightSibling->leftmostChild->rightSibling);
//            }else {
//                //going to be -
//                if(strcmp(root->rightSibling->leftmostChild->rightSibling->rightSibling->leftmostChild->label, "-")){
//                    root->rightSibling->leftmostChild->rightSibling->rightSibling->leftmostChild->label="+";
//                }else if(strcmp(root->rightSibling->leftmostChild->rightSibling->rightSibling->leftmostChild->label, "+")){
//                    root->rightSibling->leftmostChild->rightSibling->rightSibling->leftmostChild->label="-";
//                }
//                return Fhandler(root->leftmostChild) - Thandler(root->rightSibling->leftmostChild->rightSibling);
//
//
//            }
//
//    }//
    if(strcmp(root->rightSibling->leftmostChild->label,"e")==0){
       return Fhandler(root->leftmostChild);
    }
        double result = Fhandler(root->leftmostChild);
        while(strcmp(root->rightSibling->leftmostChild->label, "e")!=0){
            if(strcmp(root->rightSibling->leftmostChild->label, "+")==0){
                result +=Fhandler(root->rightSibling->leftmostChild->rightSibling->leftmostChild);
            }else{
                result-=Fhandler(root->rightSibling->leftmostChild->rightSibling->leftmostChild);
            }
            root=root->rightSibling->leftmostChild->rightSibling;

        }
        return result;
}




char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char* Nhandler(TREE root){
    if(strcmp(root->leftmostChild->rightSibling->leftmostChild->label,"e")==0){
        return root->leftmostChild->leftmostChild->label;
    }else{
        return concat(root->leftmostChild->leftmostChild->label, Nhandler(root->leftmostChild->rightSibling->leftmostChild));
    }
}

void rNhandler(TREE child){
    child->label=Nhandler(child);
    child->leftmostChild=NULL;
    child->rightSibling=NULL;
}

void parseN(TREE root){
    if(!root){
        return;
    }
    if(strcmp(root->label, "<N>")==0) {
        rNhandler(root);
    }

    if(root->leftmostChild!=NULL){
        parseN(root->leftmostChild);
    }
    if(root->rightSibling!=NULL){
        parseN(root->rightSibling);
    }

}

void stripParenthesis(TREE root){
    if(!root){
        return;
    }
    if(strcmp(root->label, "<F>")==0) {
        if(strcmp(root->leftmostChild->label, "(")==0){
            // root->leftmostChild->rightSibling->rightSibling==NULL;
            root->leftmostChild=root->leftmostChild->rightSibling;
            root->leftmostChild->rightSibling=NULL;
        }
    }

    if(root->leftmostChild!=NULL){
        stripParenthesis(root->leftmostChild);
    }
    if(root->rightSibling!=NULL){
        stripParenthesis(root->rightSibling);
    }
}

//this is part3

void printTree(TREE root){
    printTreeRecursively(root, 0);
}

void printTreeRecursively(TREE root, int indent){
    char* label;
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
}
void freeTree(TREE node){
    if (node != NULL) {
        freeTree(node->rightSibling);
        freeTree(node->leftmostChild);
        free(node->label);
        free(node);
    }
}
