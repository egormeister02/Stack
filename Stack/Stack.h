#include <stdio.h>
#include <stdlib.h>


#define ASSERT(condition)                                   \
if (!(condition)){                                           \
    fprintf(stderr, "Error in %s:\n"                          \
                    "FILE: %s\n"                               \
                    "LINE: %d\n"                                \
                    "FUNCTION: %s\n",                            \
           #condition, __FILE__, __LINE__, __PRETTY_FUNCTION__);  \
    abort();}

#define StackCheck(Stack) \
    StackCheckFunc(Stack, #Stack, __FILE__, __LINE__, __PRETTY_FUNCTION__)

#define DESTRUCT 0x66DEAD66

typedef int Elem_t;

struct stk
{
    Elem_t* data = NULL;
    long size = 0;
    long capacity = 0;
};

void StackCtor(stk*);

void Push(stk*, int);

Elem_t Pop(stk*);

void StackDtor(stk*);

int StackCheckFunc(stk, const char*, char*, int, const char*);