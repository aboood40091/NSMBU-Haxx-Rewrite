#pragma once

#include <input/SeadController.h>

#include <controller/cafe/seadCafeRemoteControllerCafe.h>

class SeadControllerHaxx : public SeadController
{
protected:
    void calcRemote_(const sead::CafeRemoteController& controller); // Core & Nunchuk & Classic Controller
};
