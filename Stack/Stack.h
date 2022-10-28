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

//const char* NAME_LOG_FILE = "log.txt";

typedef int Elem_t;
extern FILE* LogFile;

struct stk
{
    Elem_t* data = NULL;
    long size = 0;
    size_t capacity = 0;
};

enum ResizeMode 
{
    UP = 0,
    DOWN = 1
};

enum StackCodeError
{
    STACK_OK                 = 0,
    STACK_DESTRUCT           = 1,
    STACK_DATA_NULL          = 2,
    STACK_SIZE_LESS_0        = 3,
    STACK_SIZE_MORE_CAPACITY = 4
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

FILE* StartLog(void);

void FinishLog();

void StackDumpFunc(stk*, const char*, const char* , size_t, const char*, StackCodeError);

void PrintError(StackCodeError);
