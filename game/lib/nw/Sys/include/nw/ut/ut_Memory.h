#ifndef NW_UT_MEMORY_H_
#define NW_UT_MEMORY_H_

#include <nw/ut/ut_RuntimeTypeInfo.h>

namespace nw { namespace ut {

class IAllocator
{
public:
    NW_UT_RUNTIME_TYPEINFO_ROOT();

    virtual ~IAllocator()
    {
    }

    virtual void* Alloc(size_t size, u32 alignment) = 0;
    virtual void  Free(void* memory) = 0;
};

} } // namespace nw::ut

#endif // NW_UT_MEMORY_H_
