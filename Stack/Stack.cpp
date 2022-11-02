#include "Stack.h"

void StackCtor(stk* st, size_t capacity)
{
    ASSERT(st != NULL);

    st->size = 0;
    st->capacity = (capacity == 0 ? BASE_CAPACITY: capacity);
    st->data = (Elem_t*)calloc(st->capacity, sizeof(Elem_t));
    StackPoison(st);

    StackCheck(st);
}


void Push(stk* st, int x)
{
    ASSERT(st != NULL);
    StackCheck(st);

    StackResize(st, UP);

    st->data[st->size++] = x;

    StackCheck(st);
}

Elem_t Pop(stk* st)
{
    ASSERT(st != NULL);
    StackCheck(st);

    Elem_t value = st->data[--st->size];
    st->data[st->size] = POISON;

    StackResize(st, DOWN);

    StackCheck(st);
    return value;
}

void StackDtor(stk* st)
{
    ASSERT(st != NULL);
    StackCheck(st);

    st->data = (Elem_t*)DESTRUCT_DATA;
    st->size = DESTRUCT_SIZE;
    st->capacity = DESTRUCT_CAPACITY;
}

void StackResize(stk* st, ResizeMode mode)
{
    ASSERT(st != NULL);
    StackCheck(st);

    size_t NewCapacity = 0;

    if (mode == UP)
    {
        if (st->size < (long)st->capacity-1)
            return;
        else 
            NewCapacity = (st->capacity == 0 ? BASE_CAPACITY: st->capacity*2);
    }

    if (mode == DOWN)
    {
        if ((st->size < (long)(st->capacity / 4)) & (st->size > (long)BASE_CAPACITY))
            NewCapacity = st->capacity / 2;
        else 
            return;
    }

    st->data = (Elem_t*)realloc((char*)st->data, NewCapacity * sizeof(Elem_t));

    st->capacity = NewCapacity;
    StackPoison(st);

    StackCheck(st);
}

StackCodeError StackCheckFunc(const stk* st,const char name[MAX_SIZE_STR], const char file[MAX_SIZE_STR], int line, const char func[MAX_SIZE_STR])
{
    if ((st->data == (Elem_t*)DESTRUCT_DATA) || (st->size == DESTRUCT_SIZE) || (st->capacity == DESTRUCT_CAPACITY))
    {                                           
    fprintf(stdout, "Error in: %s is destructed:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_DESTRUCT);
    FinishLog();
    abort();
    }
    else if (st->data == NULL)
    {                                           
    fprintf(stdout, "Error in %s->data == NULL:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_DATA_NULL);
    FinishLog();
    abort();
    }
    else if (st->size < 0)
    {                                           
    fprintf(stdout, "Error in %s->size < 0:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_SIZE_LESS_0);
    FinishLog();
    abort();
    }
    else if (st->size >= (long)st->capacity)
    {                                           
    fprintf(stdout, "Error in %s->size >= st.capacity:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_SIZE_MORE_CAPACITY);
    FinishLog();
    abort();
    }
    return STACK_OK;
}


FILE* StartLog(void)
{
    FILE* logfile = fopen(NAME_LOG_FILE, "w");
    fprintf(logfile, "--------------------------------Start Logging--------------------------------\n");
    return logfile;
}

void FinishLog(void)
{
    fprintf(LogFile, "\n------------------------------Finish Logging-------------------------------\n");
    fclose (LogFile);
    LogFile = NULL;
}

void StackDumpFunc(const stk* stk, const char StackName[MAX_SIZE_STR], const char file[MAX_SIZE_STR], size_t line, const char func[MAX_SIZE_STR], const StackCodeError err)
{   
    fprintf(LogFile, "\n----------------------------------StackDump----------------------------------\n");
   
    if (stk == NULL)
    {
        fprintf(LogFile, "pointer of %s is null\n", StackName);
        fprintf(LogFile, "Called at %s at %s(%u)\n", file, func, line);
        return;
    }

    fprintf(LogFile, "Called at %s at %s(%u)\n", file, func, line);
    
    PrintError(err);
    
    fprintf(LogFile, "{\n");

    fprintf(LogFile, "    data pointer = %p\n", stk->data);
    
    if ((err == STACK_DATA_NULL) || (err == STACK_DESTRUCT))
    {        
        fprintf(LogFile, "    size         = %lx\n", stk->size);
        fprintf(LogFile, "    capacity     = %lx\n", stk->capacity);

    }
    else
    {
        fprintf(LogFile, "    size         = %ld\n", stk->size);
        fprintf(LogFile, "    capacity     = %lu\n", stk->capacity);

        fprintf(LogFile, "    {\n");
        char* comment;
        for (long index = 0; index < (long)stk->capacity; index++)
        {
            fprintf(LogFile, "\t");
            fprintf(LogFile, (index < stk->size) ? "*" : " ");
            fprintf(LogFile, "[%lu] = ", index);
            comment = (char*)(stk->data[index] == POISON ? "(POISON)": "");
            fprintf(LogFile, "%d %s", stk->data[index], comment);

            fprintf(LogFile, "\n");
        }
        fprintf(LogFile, "    }\n");
    }

    fprintf(LogFile, "}\n");
    fprintf(LogFile, "\n---------------------------------------------------------------------------\n");

}

void PrintError(StackCodeError err)
{
    switch (err)
    {
    case STACK_OK:
        fprintf(LogFile, "Stack is OK\n");
        break;
    case STACK_DESTRUCT:
        fprintf(LogFile, "!!!__STACK IS DESTRUCTED__!!!\n");
        break;
    case STACK_DATA_NULL:
        fprintf(LogFile, "!!!__STACK_DATA == NULL__!!!\n ");
        break;
    case STACK_SIZE_LESS_0:
        fprintf(LogFile, "!!!__STACK_SIZE < 0__!!!\n");
        break;
    case STACK_SIZE_MORE_CAPACITY:
        fprintf(LogFile, "!!!__STACK_SIZE > STACK_CAPACITY__!!!\n");
        break;
    }
}

void StackPoison(stk* st)
{
    for (int i = st->size; i < (long)st->capacity; i++)
        st->data[i] = POISON;
}