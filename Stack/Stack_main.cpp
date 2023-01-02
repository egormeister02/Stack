#include "Stack.h"

int main()
{
    
    
    if (LogStack == NULL)
        printf("no logstack");
    
    stk* stk = NULL;
    struct stk st;
    StackCtor(&st, 0);
    stk = &st;
    
    for (int i = 0; i < 111; i++){
    Push(stk, 10);}


//LEFT_CANNARY(stk) = 0;
Push(stk, 10);
Push(stk, 10);
Push(stk, 10);
     //StackDump(stk);

   StackDump(stk);
    StackDtor(stk);
    FinishLog();
     
    //printf("%0x\n", DESTRUCT);
}