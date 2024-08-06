#pragma once

#include <layout/ChangePlayerNum.h>

#include <heap/seadDisposer.h>

class ChangePlayerNumHaxx : public ChangePlayerNum
{
    SEAD_SINGLETON_DISPOSER(ChangePlayerNumHaxx)

public:
    ChangePlayerNumHaxx()
    {
    }

protected:
    static ChangePlayerNum* createInstance_();
    static void resetPlayerCharacter_(u32 _this, s32 character, s32 player_no);
    static void setPlayerCharacter_(u32 _this, s32 character, s32 player_no);
    static void open_();
};
