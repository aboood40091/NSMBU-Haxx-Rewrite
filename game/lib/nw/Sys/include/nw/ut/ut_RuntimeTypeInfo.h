#ifndef NW_UT_RUNTIMETYPEINFO_H_
#define NW_UT_RUNTIMETYPEINFO_H_

#include <nw/types.h>

namespace nw { namespace ut {

#define NW_UT_RUNTIME_TYPEINFO_ROOT()                                           \
    static const nw::ut::internal::RuntimeTypeInfo* GetRuntimeTypeInfoStatic()  \
    {                                                                           \
        static const nw::ut::internal::RuntimeTypeInfo s_TypeInfo(NULL);        \
        return &s_TypeInfo;                                                     \
    }                                                                           \
    virtual const nw::ut::internal::RuntimeTypeInfo* GetRuntimeTypeInfo() const \
    {                                                                           \
        return GetRuntimeTypeInfoStatic();                                      \
    }

#define NW_UT_RUNTIME_TYPEINFO(base)                                                                    \
    static const nw::ut::internal::RuntimeTypeInfo* GetRuntimeTypeInfoStatic()                          \
    {                                                                                                   \
        static const nw::ut::internal::RuntimeTypeInfo s_TypeInfo(base::GetRuntimeTypeInfoStatic());    \
        return &s_TypeInfo;                                                                             \
    }                                                                                                   \
    virtual const nw::ut::internal::RuntimeTypeInfo* GetRuntimeTypeInfo() const                         \
    {                                                                                                   \
        return GetRuntimeTypeInfoStatic();                                                              \
    }


namespace internal {

struct RuntimeTypeInfo
{
    const RuntimeTypeInfo*  m_ParentTypeInfo;

    explicit RuntimeTypeInfo(const RuntimeTypeInfo* parent)
        : m_ParentTypeInfo(parent)
    {
    }

    bool IsDerivedFrom(const RuntimeTypeInfo* s_TypeInfo) const
    {
        const RuntimeTypeInfo* self = this;
        while (self)
        {
            if (self == s_TypeInfo)
                return true;

            self = self->m_ParentTypeInfo;
        }
        return false;
    }
};

} // namespace internal

} } // namespace nw::ut

#endif // NW_UT_RUNTIMETYPEINFO_H_
