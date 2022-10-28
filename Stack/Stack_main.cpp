#include "Stack.h"

int main()
{
    size_t a = 0;
    stk st = {};
    StackCtor(&st, 0);
    printf("%d  %d\n",st.capacity, st.size);
    
    
    Push(&st, 10);
    printf("%d  %d\n",st.capacity, st.size);
    
    Pop(&st);
    printf("%d  %d\n",st.capacity, st.size);
    Pop(&st);
    printf("%d  %d\n",st.capacity, st.size);
    /*
    for (int i = 0; i < 21; i++) {
        Pop(&st);
        printf("%d  %d\n",st.capacity, st.size);
    }
    */
    StackDtor(&st);
    //printf("%0x\n", DESTRUCT);
}