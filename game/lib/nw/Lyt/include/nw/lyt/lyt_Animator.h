#ifndef NW_LYT_ANIMATOR_H_
#define NW_LYT_ANIMATOR_H_

#include <nw/lyt/lyt_Types.h>

namespace nw { namespace lyt {

class Animator
{
public:
    enum PlayType
    {
        PLAYTYPE_ONESHOT,
        PLAYTYPE_LOOP,
        PLAYTYPE_ROUNDTRIP
    };
};

} } // namespace nw::lyt

#endif // NW_LYT_ANIMATOR_H_
