#include <input/SysController_Haxx.h>

#include <cafe/pads/wpad/wpad.h>

void SysControllerHaxx::calcRemote_(const sead::CafeRemoteController& controller)
{
    switch (controller.getCurrentDeviceType())
    {
    case WPAD_DEV_CLASSIC:
    case WPAD_DEV_MPLS_CLASSIC:
        calcRemote_URCC_(&controller);
        calcRemote_URCC_Acc_(&controller);
        return;
    case WPAD_DEV_FREESTYLE:
    case WPAD_DEV_MPLS_FREESTYLE:
        calcRemote_Nunchuk_(&controller);
        return;
    default:
        calcRemote_Core_(&controller);
    }
}

sead::CafeRemoteController& PostCreate_CafeRemoteController(sead::CafeRemoteController& controller)
{
    controller.setEnableCL(true);
    return controller;
}
