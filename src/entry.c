#include "infinityplugin.h"

#include "example_pointer_class.h"

#include "core.h" // provides extern for other c files to access g_pCore

#if defined(_WIN64)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility ("default")))
#endif

InfinityCore* g_pCore = 0;

// ---------------------------------------------------------------------

EXPORT void OnPluginLoad(InfinityCore* pCore)
{
    g_pCore = pCore;
    
    g_pCore->Print(LVL_INFO, "Loading example plugin...");
    
    // register all classes
    Register_ExamplePointerClass(pCore);
    
    g_pCore->Print(LVL_INFO, "Example plugin loaded.");
}