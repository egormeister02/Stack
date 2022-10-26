#include "Stack.h"


int main()
{
    stk st = {};
    StackCtor(&st);
    Push(&st, 10);
    Push(&st, 20);
    st.size = -1;
    Push(&st, 30);
    printf("%d\n",Pop(&st));
    
    StackDtor(&st);
    //printf("%0x\n", DESTRUCT);
}