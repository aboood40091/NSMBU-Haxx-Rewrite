#ifndef NW_LYT_TEXTBOX_H_
#define NW_LYT_TEXTBOX_H_

#include <nw/types.h>

// Silent VSCode
typedef wchar_t char16;

namespace nw { namespace font {

template <typename CharType>
class TagProcessorBase;

} } // namespace nw::font

namespace nw { namespace lyt {

class TextBox
{
public:
    typedef font::TagProcessorBase<char16> TagProcessor;
};

} } // namespace nw::lyt

#endif // NW_LYT_TEXTBOX_H_
