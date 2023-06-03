#include <common/aglRenderBuffer.h>
#include <gfx/seadViewport.h>
#include <layer/aglLayer.h>
#include <layer/aglRenderer.h>

//#include <log.h>

namespace agl { namespace lyr {

class LayerHaxx : public Layer
{
public:
    void setName(const char* name)
    {
        static_assert((uintptr)((u32*)&(((LayerHaxx*)0)->mDebugInfo) + 1) == 0x90);
        *(const char**)((u32*)&mDebugInfo + 1) = name;
    }

    const char* getName() const
    {
        static_assert((uintptr)((const u32*)&(((LayerHaxx*)0)->mDebugInfo) + 1) == 0x90);
        return *(const char* const*)((const u32*)&mDebugInfo + 1);
    }
};
static_assert(sizeof(LayerHaxx) == sizeof(Layer));

class RendererHaxx : public Renderer
{
protected:
    bool drawTV_(DisplayType display_type) const;
    bool drawDRC_(DisplayType display_type) const;

    void initLayer_(LayerHaxx* layer, s32 layer_index, const sead::SafeString& name, DisplayType display_type, sead::Heap* heap);
};
static_assert(sizeof(RendererHaxx) == sizeof(Renderer));

/* Clear TV and DRC frame buffers to black before each frame */

bool RendererHaxx::drawTV_(DisplayType display_type) const
{
    if (mGpuCounter % mGpuCounterPeriod)
        return false;

    if (mFlag.isOffBit(4) && mFlag.isOffBit(0))
    {
        agl::RenderBuffer* p_render_buffer = mRenderBuffer[cDisplayType_Top_TV];
        if (p_render_buffer != nullptr)
        {
            u32 clr_flag = 1;
            if (p_render_buffer->getRenderTargetDepth() != nullptr)
                clr_flag = 3;

            p_render_buffer->bind();

            sead::Viewport viewport = sead::Viewport(*p_render_buffer);
            viewport.apply(*p_render_buffer);

            p_render_buffer->clear(
                clr_flag,
                sead::Color4f::cBlack,
                1.0f,
                0
            );
        }

        // Render buffer clear bit
        mFlag.resetBit(8);
    }

    // This must return true
    return draw(display_type);
}

bool RendererHaxx::drawDRC_(DisplayType display_type) const
{
    if (mGpuCounter % mGpuCounterPeriod)
        return false;

    if (mFlag.isOffBit(4) && mFlag.isOffBit(0))
    {
        agl::RenderBuffer* p_render_buffer = mRenderBuffer[cDisplayType_Bottom_DRC];
        if (p_render_buffer != nullptr)
        {
            u32 clr_flag = 1;
            if (p_render_buffer->getRenderTargetDepth() != nullptr)
                clr_flag = 3;

            p_render_buffer->bind();

            sead::Viewport viewport = sead::Viewport(*p_render_buffer);
            viewport.apply(*p_render_buffer);

            p_render_buffer->clear(
                clr_flag,
                sead::Color4f::cBlack,
                1.0f,
                0
            );
        }

        // Render buffer clear bit
        mFlag.resetBit(8);
    }

    // This must return true
    return draw(display_type);
}

/* Save the Layer's name */

void RendererHaxx::initLayer_(LayerHaxx* layer, s32 layer_index, const sead::SafeString& name, DisplayType display_type, sead::Heap* heap)
{
    const char* c_name = name.cstr();
    Renderer::initLayer_(layer, layer_index, name, display_type, heap);
    //SEAD_ASSERT(layer->getName() == nullptr);
    layer->setName(c_name);
    //LOG("Restored agl::lyr::Layer name for %s", c_name);
}

} }
