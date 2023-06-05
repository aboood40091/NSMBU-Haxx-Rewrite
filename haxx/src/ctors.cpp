#include <basis/seadTypes.h>

#include <dynamic_libs/gx2_functions.h>
#include <dynamic_libs/os_functions.h>
#include <dynamic_libs/zlib_functions.h>

#include <log.h>

typedef void (*InitFunc)();
extern "C" InitFunc _ctors[];

OsSpecifics osSpecifics;

extern "C"
{

extern u32 BLOSDynLoad_Acquire;
extern u32 BOSDynLoad_FindExport;

}

static inline uintptr_t AddrExtractFromInst(const u32* p_instruction)
{
    uintptr_t ret = *p_instruction & 0x03FFFFFCu;

    if (!(*p_instruction & 2))
    {
        // sign extend offset
        if (ret & 0x02000000u)
           ret |= 0xFE000000u;

        // make relative
        ret += (uintptr_t)p_instruction;
    }

    return ret;
}

void callCtors()
{
    static bool initialized = false;
    if (initialized)
        return;

    initialized = true;
    for (s32 i = 0; _ctors[i]; i++)
        (*_ctors[i])();

    // Time to set addr_OSDynLoad_Acquire
    // and addr_OSDynLoad_FindExport
    OS_SPECIFICS->addr_OSDynLoad_Acquire    = AddrExtractFromInst(&BLOSDynLoad_Acquire);
    OS_SPECIFICS->addr_OSDynLoad_FindExport = AddrExtractFromInst(&BOSDynLoad_FindExport);

    // Init the libraries you need here
    InitOSFunctionPointers();
    InitGX2FunctionPointers();
    InitZlibFunctionPointers();

    LOG("OSDynLoad_Acquire address: 0x%08X\n", OS_SPECIFICS->addr_OSDynLoad_Acquire);
    LOG("OSDynLoad_FindExport address: 0x%08X\n", OS_SPECIFICS->addr_OSDynLoad_FindExport);
}
