#include <audio/GameAudio.h>
#include <item/Propeller_Haxx.h>

void PropellerHaxx::startGlideSound() const
{
    GameAudio::getAudioObjMap()->holdSound("SE_OBJ_ITEM_PRPL_GLIDE", mActorUniqueID.getValue(), mPos);
}
