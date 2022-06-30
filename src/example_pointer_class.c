#include "example_pointer_class.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "infinityplugin.h"
#include "core.h"

// -------------------------------------------------------------------
/*
    *  sealed class ExamplePointerClass : pointer {
 *      static proto ExamplePointerClass Create(string indata);
*      proto external void Destroy();
*      proto external int GetAccessCount();
*  }
*
*/

typedef struct example_pointer_class  {
    char* in_data;
    int access_count;
} ExamplePointerClass;


// this is crashing probably because it's not returning a type
FunctionResult* ExamplePointerClass_Create(FunctionContext* arg, FunctionResult* result)
{
    // get "string" argument value
    char* arg1 =  GetArgument(arg, 0);
    
    // construct our pointer
    ExamplePointerClass* ptr = (ExamplePointerClass*)malloc(sizeof(ExamplePointerClass));
    if(!ptr) {
        g_pCore->Print(LVL_ERROR, "Failed to allocate memory for new example pointer class");
        return result;
    }
    memset(ptr,0,sizeof(ExamplePointerClass));
    
    // fill pointer with data
    if(arg1)
    {
        int size = strlen(arg1)+1;
        ptr->in_data = malloc(size);
        strcpy(ptr->in_data, arg1);
    }
    
    // set return value to our pointer
    SetResult(result, &ptr, sizeof(ExamplePointerClass*));
    
    return result;
}
FunctionResult* ExamplePointerClass_Destroy(FunctionContext* arg, FunctionResult* result)
{
    ExamplePointerClass* ptr = GetArgument(arg, 0); // "external" functions provide class pointer in first argument
    
    g_pCore->Print(LVL_INFO, "Destroying example pointer class @ 0x%p.", ptr);
    
    if(!ptr) return result;
    if(ptr->in_data)
    {
        free((void*)ptr->in_data);
    }
    free(ptr);
    
    //NOTE: you can not set the input object to NULL. It is not an `out` capable value!
    // SetArgument(arg,0,0); // NULL the input argument?
    
    return result;
}
FunctionResult* ExamplePointerClass_GetAccessCount(FunctionContext* arg, FunctionResult* result)
{
    ExamplePointerClass* ptr = GetArgument(arg, 0);
    
    g_pCore->Print(LVL_INFO, "Getting count of example pointer class @ 0x%p.", ptr);
    
    if(!ptr) return result;
    
    g_pCore->Print(LVL_INFO, "Count: %d.", ptr->access_count);
    
    SetResult(result, (void*)&ptr->access_count, sizeof(int));
    
    ptr->access_count++;
    return result;
}
FunctionResult* ExamplePointerClass_PrintTest(FunctionContext* arg, FunctionResult* result)
{
    g_pCore->Print(LVL_INFO, "THIS CAME FROM NATIVE CODE");
    return result;
}
FunctionResult* ExamplePointerClass_ArgSetTest(FunctionContext* ctx, FunctionResult* res)
{
    // extern args start at 1
    // push int into arg[1] value buffer
    
    int new_value = 1337;
    SetArgument(ctx, 1, (void*)&new_value, sizeof(int));
    
    return res;
}


void Register_ExamplePointerClass(InfinityCore* pCore)
{
    g_pCore->Print(LVL_INFO, "Registering example pointer class.");
    
    ScriptClass* pClass = pCore- >RegisterClass("ExamplePointerClass");
    pCore->RegisterFunction(pClass, "Create", &ExamplePointerClass_Create);
    pCore->RegisterFunction(pClass, "Destroy", &ExamplePointerClass_Destroy);
    pCore->RegisterFunction(pClass, "GetAccessCount", &ExamplePointerClass_GetAccessCount);
    pCore->RegisterFunction(pClass, "PrintTest", &ExamplePointerClass_PrintTest);
    pCore->RegisterFunction(pClass, "ArgSetTest", &ExamplePointerClass_ArgSetTest);
}