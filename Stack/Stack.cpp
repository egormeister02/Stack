#include "Stack.h"

void StackCtor(stk* st, size_t capacity)
{
    ASSERT(st != NULL);

    st->size = 0;
    st->capacity = (capacity == 0 ? BASE_CAPACITY: capacity);
    st->data = (Elem_t*)calloc(st->capacity, sizeof(Elem_t));

    StackCheck(*st);
}

void Push(stk* st, int x)
{
    ASSERT(st != NULL);
    StackCheck(*st);

    StackResize(st, UP);

    st->data[st->size++] = x;

    StackResize(st, UP);

    StackCheck(*st);
}

Elem_t Pop(stk* st)
{
    ASSERT(st != NULL);
    ASSERT(st->size > 0);
    StackCheck(*st);

    Elem_t value = st->data[--st->size];

    StackResize(st, DOWN);

    StackCheck(*st);
    return value;
}

void StackDtor(stk* st)
{
    ASSERT(st != NULL);
    StackCheck(*st);

    st->data = (Elem_t*)DESTRUCT_DATA;
    st->size = DESTRUCT_SIZE;
    st->capacity = DESTRUCT_CAPACITY;
}

void StackResize(stk* st, ResizeMode mode)
{
    ASSERT(st != NULL);
    StackCheck(*st);

    size_t NewCapacity = 0;

    if (mode == UP)
    {
        if (st->size < st->capacity-1)
            return;
        else 
            NewCapacity = (st->capacity == 0 ? BASE_CAPACITY: st->capacity*2);
    }

    if (mode == DOWN)
    {
        if ((st->size < st->capacity / 4) & (st->size > BASE_CAPACITY))
            NewCapacity = st->capacity / 2;
        else 
            return;
    }

    if ((st->size == 0) & (mode == UP))
    {
        st->data = (Elem_t*)calloc(BASE_CAPACITY, sizeof(Elem_t));
        ASSERT(st->data != NULL);
    }
        
    else
        st->data = (Elem_t*)realloc((char*)st->data, NewCapacity * sizeof(Elem_t));

    st->capacity = NewCapacity;

    StackCheck(*st);
}

int StackCheckFunc(stk st,const char* name, char* file, int line, const char* func)
{
    if ((st.data == (Elem_t*)DESTRUCT_DATA) || (st.size == DESTRUCT_SIZE) || (st.capacity == DESTRUCT_CAPACITY))
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

