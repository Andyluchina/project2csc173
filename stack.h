//
// Created by Andy on 10/15/2018.
// Refactored header file: a working stack! you are welcome!
struct Stack{
    char* stack;
    int top;
};

struct Stack* createStack(){
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack) * 100);
    s->stack = (char*)malloc(sizeof(char) * 100);
    s->top = -1;
    return s;
};

void push(struct Stack* s, char* c){
    s->top++;
    s->stack[s->top] = *c;
};

char pop(struct Stack* s){
    char temp = s->stack[s->top];
    s->stack[s->top]= -1;
    s->top--;
    return temp;
};

char peek(struct Stack* s){
    return s->stack[s->top];
};

int isEmpty(struct Stack* s){
    if(s->top == -1){
        return 1;
    }
    return 0;
};

int size(struct Stack* s){
    return s->top;
}

//not sure if free method is correct
void free_Stack(struct Stack* s){
    free(s);
};



#ifndef PROJECT2CSC173_STACK_H
#define PROJECT2CSC173_STACK_H

#endif //PROJECT2CSC173_STACK_H
