#pragma once

#include <input/SysController.h>

#include <controller/cafe/seadCafeRemoteControllerCafe.h>

class SysControllerHaxx : public SysController
{
protected:
    void calcRemote_(const sead::CafeRemoteController& controller); // Core & Nunchuk & Classic Controller
};
