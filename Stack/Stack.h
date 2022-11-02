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

#define StackDump(Stack) \
    StackDumpFunc(Stack, #Stack, __FILE__, __LINE__, __PRETTY_FUNCTION__, StackCheck(Stack))

#define POISON POISON_INT


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
const char NAME_LOG_FILE[] = "log.txt";
const size_t BASE_CAPACITY = 10;
const int POISON_INT = 0xDEAD;
const int POISON_CHAR = 0xFF;
const int POISON_LONG = 0xAADEADAA;
const int POISON_FLOAT = 0xFFDEADFF;
const int POISON_DOUBLE = 0xDDDEADDD;
const int MAX_SIZE_STR = 40;


void StackCtor(stk*, size_t);

void Push(stk*, int);

Elem_t Pop(stk*);

void StackResize(stk*, ResizeMode);

void StackDtor(stk*);

StackCodeError StackCheckFunc(const stk* st,const char name[MAX_SIZE_STR], const char file[MAX_SIZE_STR], int line, const char func[MAX_SIZE_STR]);

FILE* StartLog(void);

void FinishLog();

void StackDumpFunc(const stk* stk, const char StackName[MAX_SIZE_STR], const char file[MAX_SIZE_STR], size_t line, const char func[MAX_SIZE_STR], const StackCodeError err);

void PrintError(StackCodeError);

void StackPoison(stk*);
