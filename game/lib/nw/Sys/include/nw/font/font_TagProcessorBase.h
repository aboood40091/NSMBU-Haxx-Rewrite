#ifndef NW_FONT_TAGPROCESSORBASE_H_
#define NW_FONT_TAGPROCESSORBASE_H_

#include <nw/ut/ut_Rect.h>
#include <nw/ut/ut_RuntimeTypeInfo.h>

namespace nw { namespace font {

template <typename CharType>
struct PrintContext;

template <typename CharType>
class TagProcessorBase
{
public:
    NW_UT_RUNTIME_TYPEINFO_ROOT();

    typedef PrintContext<CharType> ContextType;

    enum Operation
    {
        OPERATION_DEFAULT,
        OPERATION_NO_CHAR_SPACE,
        OPERATION_CHAR_SPACE,
        OPERATION_NEXT_LINE,
        OPERATION_END_DRAW,
        NUM_OF_OPERATION
    };

    TagProcessorBase();
    virtual ~TagProcessorBase();

    virtual Operation Process(u16 code, ContextType* pContext);
    virtual Operation CalcRect(ut::Rect* pRect, u16 code, ContextType* pContext);

private:
    void ProcessLinefeed(ContextType* pContext);
    void ProcessTab(ContextType* pContext);
};

} } // namespace nw::font

#endif // NW_FONT_TAGPROCESSORBASE_H_
