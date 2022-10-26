#include "Stack.h"

void StackCtor(stk* st)
{
    ASSERT(st != NULL);

    st->size = 0;
    st->capacity = 100;
    st->data = (Elem_t*)calloc(st->capacity, sizeof(Elem_t));

    StackCheck(*st);
}

void Push(stk* st, int x)
{
    ASSERT(st != NULL);
    StackCheck(*st);

    st->data[st->size++] = x;

    StackCheck(*st);
}

Elem_t Pop(stk* st)
{
    ASSERT(st != NULL);
    StackCheck(*st);

    Elem_t value = st->data[--st->size];

    StackCheck(*st);
    return value;
}

void StackDtor(stk* st)
{
    ASSERT(st != NULL);
    StackCheck(*st);

    st->data = (Elem_t*)DESTRUCT;
    st->size = DESTRUCT;
    st->capacity = DESTRUCT;
}

int StackCheckFunc(stk st,const char* name, char* file, int line, const char* func)
{
    if ((st.data == (Elem_t*)DESTRUCT) || (st.size == DESTRUCT) || (st.capacity == DESTRUCT))
    {                                           
    fprintf(stdout, "Error in: %s is destructed:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n",                            
            name, file, line, func);  
    abort();
    }
    else if (st.data == NULL)
    {                                           
    fprintf(stdout, "Error in %s.data == NULL:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n",                            
            name, file, line, func);  
    abort();
    }
    else if (st.size < 0)
    {                                           
    fprintf(stdout, "Error in %s.size < 0:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n",                            
            name, file, line, func);  
    abort();
    }
    else if (st.size >= st.capacity)
    {                                           
    fprintf(stdout, "Error in %s.size >= st.capacity:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n",                            
            name, file, line, func);  
    abort();
    }
}