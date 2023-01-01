#include "Stack.h"

FILE* LogStack = StartLog();

void StackCtor(stk* stk, size_t capacity)
{
    if (stk == NULL) StackCheck(stk);

    stk->size = 0;
    stk->capacity = (capacity == 0 ? BASE_CAPACITY: capacity);
    stk->buf = (void*)calloc(stk->capacity * sizeof(Elem_t) + 2 * SIZE_CANNARY, sizeof(char));
    stk->data = (Elem_t*)((char*)stk->buf + SIZE_CANNARY);

#if CANNARY_GUARD
    LEFT_CANNARY(stk)   = CANNARY;
    RIGHT_CANNARY(stk)  = CANNARY;
    stk->left_cannary   = CANNARY;
    stk->right_cannary  = CANNARY;
#endif

    StackPoison(stk);

    StackCheck(stk);
}


void Push(stk* stk, Elem_t val)
{
    if (stk->err) return;
    StackCheck(stk);

    StackResize(stk, UP);

    stk->data[stk->size++] = val;

    StackCheck(stk);
}

Elem_t Pop(stk* stk)
{
    if (stk->err) return 0;
    StackCheck(stk)0;

    Elem_t value = stk->data[--stk->size];
    stk->data[stk->size] = POISON;

    StackResize(stk, DOWN);

    StackCheck(stk)0;
    return value;
}

void StackDtor(stk* stk)
{

    stk->data = (Elem_t*)DESTRUCT_DATA;
    stk->size = DESTRUCT_SIZE;
    stk->capacity = DESTRUCT_CAPACITY;
    free(stk->buf);
}

void StackResize(stk* stk, ResizeMode mode)
{
    StackCheck(stk);

    size_t NewCapacity = 0;

    if (mode == UP)
    {
        if ((long)stk->size < (long)(stk->capacity-1))
            return;
        else 
            NewCapacity = (stk->capacity == 0 ? BASE_CAPACITY: stk->capacity*2);
    }

    if (mode == DOWN)
    {
        if (((long)stk->size < (long)(stk->capacity / 4)) & ((long)stk->size > (long)BASE_CAPACITY))
            NewCapacity = stk->capacity / 2;
        else 
            return;
    }

    stk->buf = (void*)realloc((char*)stk->buf, NewCapacity * sizeof(Elem_t) + SIZE_CANNARY * 2);
    stk->data = (Elem_t*)((char*)stk->buf + SIZE_CANNARY);
    stk->capacity = NewCapacity;

#if CANNARY_GUARD
    RIGHT_CANNARY(stk) = CANNARY;
#endif
    
    StackPoison(stk);

    StackCheck(stk);
}

StackCodeError StackCheckFunc(const stk* st,const char name[MAX_SIZE_STR], 
                              const char file[MAX_SIZE_STR], int line, const char func[MAX_SIZE_STR])
{
    if (st == NULL)
    {                                           
    fprintf(stdout, "Error in: %s is NULL:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_NULL);
    //FinishLog();
    return STACK_NULL;
    }
    
    else if ((st->data == (Elem_t*)DESTRUCT_DATA) || (st->size == DESTRUCT_SIZE) || (st->capacity == DESTRUCT_CAPACITY))
    {                                           
    fprintf(stdout, "Error in: %s is destructed:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_DESTRUCT);
    //FinishLog();
    return STACK_DESTRUCT;
    }
#if CANNARY_GUARD
    else if (st->left_cannary != CANNARY)
    {                                           
    fprintf(stdout, "Error in %s: dead left cannary:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_STRUCT_LEFT_CANN);
    //FinishLog();
    return STACK_LEFT_CANN;
    }
    else if (st->right_cannary != CANNARY)
    {                                           
    fprintf(stdout, "Error in %s: dead right cannary:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_STRUCT_RIGHT_CANN);
    //FinishLog();
    return STACK_RIGHT_CANN;
    }
    else if (LEFT_CANNARY(st) != CANNARY)
    {                                           
    fprintf(stdout, "Error in %s: dead left cannary:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_LEFT_CANN);
    //FinishLog();
    return STACK_LEFT_CANN;
    }
    else if (RIGHT_CANNARY(st) != CANNARY)
    {                                           
    fprintf(stdout, "Error in %s: dead right cannary:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_RIGHT_CANN);
    //FinishLog();
    return STACK_RIGHT_CANN;
    }
#endif
    else if (st->buf == NULL)
    {                                           
    fprintf(stdout, "Error in %s->buf == NULL:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_DATA_NULL);
    //FinishLog();
    return STACK_DATA_NULL;
    }
    else if ((long)st->size < 0)
    {                                           
    fprintf(stdout, "Error in %s->size < 0:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_SIZE_LESS_0);
    //FinishLog();
    return STACK_SIZE_LESS_0;
    }
    else if ((long)st->size >= (long)st->capacity)
    {                                           
    fprintf(stdout, "Error in %s->size >= st.capacity:\n"                          
                    "FILE: %s\n"                               
                    "LINE: %d\n"                                
                    "FUNCTION: %s\n"
                    "StackDump!!!\n",                            
            name, file, line, func);  
    StackDumpFunc(st, name, file, line, func, STACK_SIZE_MORE_CAPACITY);
    //FinishLog();
    return STACK_SIZE_MORE_CAPACITY;
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
    fprintf(LogStack, "\n------------------------------Finish Logging-------------------------------\n");
    fclose (LogStack);
    LogStack = NULL;
}

void StackDumpFunc(const stk* stk, const char StackName[MAX_SIZE_STR], const char file[MAX_SIZE_STR],
                   size_t line, const char func[MAX_SIZE_STR], const StackCodeError err)
{   
    fprintf(LogStack, "\n----------------------------------StackDump----------------------------------\n");
   
    if (err == STACK_NULL)
    {
        PrintError(err);
        fprintf(LogStack, "pointer of %s is NULL\n", StackName);
        fprintf(LogStack, "Called at %s at %s(%llu)\n", file, func, line);
        return;
    }

    fprintf(LogStack, "Called at %s at %s(%llu)\n", file, func, line);
    
    PrintError(err);

#if CANNARY_GUARD
    fprintf(LogStack, "\n    CANNARY = %llX\n\n", CANNARY);
#endif
    
    fprintf(LogStack, "{\n    ---------------------------------------\n");

#if CANNARY_GUARD
    fprintf(LogStack, "    left struct cannary  = %llX\n\n", stk->left_cannary);
#endif

    fprintf(LogStack, "    data pointer         = %p\n", stk->data);    
    fprintf(LogStack, "    size                 = %llu\n", stk->size);
    fprintf(LogStack, "    capacity             = %llu\n", stk->capacity); 

#if CANNARY_GUARD
    fprintf(LogStack, "\n    right struct cannary = %llX\n", stk->right_cannary);
#endif

    fprintf(LogStack, "    ---------------------------------------\n\n");

    if ((err == STACK_DATA_NULL) || (err == STACK_DESTRUCT))     
        return;
    else
    {
        fprintf(LogStack, "    {\n");

#if CANNARY_GUARD
    fprintf(LogStack, "    LEFT_CANNARY = %llX\n\n", LEFT_CANNARY(stk));
#endif

    
        char* comment;
        for (size_t index = 0; index < stk->capacity; index++)
        {
            fprintf(LogStack, "\t");
            fprintf(LogStack, (index < stk->size) ? "*" : " ");
            fprintf(LogStack, "[%llu] = ", index);
            comment = (char*)(stk->data[index] == POISON ? "(POISON)": "");
            fprintf(LogStack, "%lf %s", stk->data[index], comment);

            fprintf(LogStack, "\n");
        }

#if CANNARY_GUARD
    fprintf(LogStack, "\n    RIGHT_CANNARY = %llX\n", RIGHT_CANNARY(stk));
#endif        
        fprintf(LogStack, "    }\n");
    }

    fprintf(LogStack, "}\n");
    fprintf(LogStack, "\n---------------------------------------------------------------------------\n");
}

void PrintError(const StackCodeError err)
{
    switch (err)
    {
    case STACK_NULL:
        fprintf(LogStack, "!!!__STACK POINTER == NULL__!!!\n ");
        break;
    case STACK_OK:
        fprintf(LogStack, "Stack is OK\n");
        break;
    case STACK_DESTRUCT:
        fprintf(LogStack, "!!!__STACK IS DESTRUCTED__!!!\n");
        break;
    case STACK_DATA_NULL:
        fprintf(LogStack, "!!!__STACK_BUF == NULL__!!!\n ");
        break;
    case STACK_SIZE_LESS_0:
        fprintf(LogStack, "!!!__STACK_SIZE < 0__!!!\n");
        break;
    case STACK_SIZE_MORE_CAPACITY:
        fprintf(LogStack, "!!!__STACK_SIZE > STACK_CAPACITY__!!!\n");
        break;
    case STACK_LEFT_CANN:
        fprintf(LogStack, "!!!__LEFT CANNARY DEAD__!!!\n");
        break;
    case STACK_RIGHT_CANN:
        fprintf(LogStack, "!!!__RIGHT CANNARY DEAD__!!!\n");
        break;
    case STACK_STRUCT_LEFT_CANN:
        fprintf(LogStack, "!!!__LEFT STRUCT CANNARY DEAD__!!!\n");
        break;
    case STACK_STRUCT_RIGHT_CANN:
        fprintf(LogStack, "!!!__RIGHT STRUCT CANNARY DEAD__!!!\n");
        break;
    
    default: break;
    }
}

void StackPoison(stk* stk)
{
    StackCheck(stk);
    for (int i = (long)stk->size; i < (long)stk->capacity; i++)
        stk->data[i] = POISON;
}