#pragma once

#include <graphics/Layer.h>

class KoopatlasLayer2D : public Layer
{
public:
    enum RenderStep
    {
        cRenderStep_HUD = 0,
        cRenderStep_Num
    };

public:
    u32 getRenderStepNum() const override
    {
        return cRenderStep_Num;
    }

    void getRenderStepName(sead::SafeString* p_name, s32 idx) const override
    {
        new (p_name) sead::SafeString("HUD");
    }
};
