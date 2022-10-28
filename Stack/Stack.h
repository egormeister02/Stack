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



typedef int Elem_t;

enum ResizeMode 
{
    UP = 0,
    DOWN = 1
};

struct stk
{
    Elem_t* data = NULL;
    long size = 0;
    size_t capacity = 0;
};

const size_t DESTRUCT_DATA = 0x66DEAD66;
const long DESTRUCT_SIZE = 0x66DEAD66;
const size_t DESTRUCT_CAPACITY = 0x66DEAD66;
const size_t BASE_CAPACITY = 10;

void StackCtor(stk*, size_t);

void Push(stk*, int);

Elem_t Pop(stk*);

void StackResize(stk*, ResizeMode);

void StackDtor(stk*);

int StackCheckFunc(stk, const char*, char*, int, const char*);

void StackDumpFunc(stk*, size_t, const char , const char);
