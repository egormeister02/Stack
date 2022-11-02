#include "Stack.h"

FILE* LogFile = StartLog();

int main()
{
    
    struct stk st;
    StackCtor(&st, 0);
    
    
    Push(&st, 10);
    Push(&st, 20);
    
    
    Pop(&st); 
    
    StackDump(&st);
    StackDtor(&st);
    FinishLog();
    
    //printf("%0x\n", DESTRUCT);
}