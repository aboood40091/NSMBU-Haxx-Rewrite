#include <controller/cafe/seadCafeRemoteControllerCafe.h>

#include <cafe/pads/wpad/wpad.h>

bool IsCCorURCC(const sead::CafeRemoteController* p_con)
{
    if (p_con != nullptr)
    {
        switch (p_con->getCurrentDeviceType())
        {
        case WPAD_DEV_CLASSIC:
        case WPAD_DEV_MPLS_CLASSIC:
        case WPAD_DEV_URCC:
            return true;
        }
    }
    return false;
}
