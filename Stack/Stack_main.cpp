#include "Stack.h"

FILE* LogFile = StartLog();

int main()
{
    size_t a = 0;
    stk st = {};
    StackCtor(&st, 0);
    printf("%d  %d\n",st.capacity, st.size);
    
    Push(&st, 10);
    printf("%d  %d\n",st.capacity, st.size);
    st.size = -1;
    Pop(&st);
    printf("%d  %d\n",st.capacity, st.size);
    FinishLog();
    /*
    for (int i = 0; i < 21; i++) {
        Pop(&st);
        printf("%d  %d\n",st.capacity, st.size);
    }
    */
    StackDtor(&st);
    
    //printf("%0x\n", DESTRUCT);
}