#ifndef NW_LYT_DRAWINFO_H_
#define NW_LYT_DRAWINFO_H_

#include <nw/lyt/lyt_Types.h>

namespace nw { namespace lyt {

class   GraphicsResource;
class   Layout;
struct  ShaderConnection;

class DrawInfo
{
    DrawInfo();
    virtual ~DrawInfo();

private:
    math::MTX44 m_ProjMtx;
    math::MTX34 m_ViewMtx;
    math::MTX34 m_ModelViewMtx;
    math::VEC2 m_LocationAdjustScale;
    GraphicsResource* m_pGraphicsResource;
    Layout* m_pLayout;

    s8 m_TexCoordSrc[TexMapMax];
    u8 m_NumTexEnv;
    u8 m_NumTexMap;
    bool m_TexEnvAuto;
    bool m_ModelViewMtxLoaded;
    bool m_FirstDraw;
    u32 m_AllowableTextureQuantity;
    ShaderConnection* m_CurrentShader;

    struct Flag
    {
        u8 locationAdjust : 1;
        u8 invisiblePaneCalculateMtx : 1;
        u8 alphaZeroPaneCalculateMtx : 1;
    };

    Flag m_Flag;
};

} } // namespance nw::lyt

#endif // NW_LYT_DRAWINFO_H_
