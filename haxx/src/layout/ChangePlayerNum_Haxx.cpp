#include <layout/ChangePlayerNum_Haxx.h>

SEAD_SINGLETON_DISPOSER_IMPL(ChangePlayerNumHaxx)

ChangePlayerNum* ChangePlayerNumHaxx::createInstance_()
{
    return createInstance(nullptr);
}

void ChangePlayerNumHaxx::resetPlayerCharacter_(u32 _this, s32 character, s32 player_no)
{
    instance()->resetPlayerCharacter(character, player_no);
}

void ChangePlayerNumHaxx::setPlayerCharacter_(u32 _this, s32 character, s32 player_no)
{
    instance()->setPlayerCharacter(character, player_no);
}

void ChangePlayerNumHaxx::open_()
{
    instance()->open();
}
