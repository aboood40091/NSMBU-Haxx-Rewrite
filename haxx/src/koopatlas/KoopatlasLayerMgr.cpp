#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>
#include <koopatlas/KoopatlasLayer.h>
#include <koopatlas/KoopatlasLayerMgr.h>

#include <layer/aglRenderer.h>

void KoopatlasLayerMgr::createLayers(sead::Heap* heap)
{
    RenderMgr* p_render_mgr_world = new (heap) RenderMgr("KoopatlasWorld");
    p_render_mgr_world->initialize(1, 0x200, 5, 5, heap);

    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(cLayer_3D_World, "3D_World", agl::lyr::cDisplayType_Top_TV, heap)->setRenderMgr(p_render_mgr_world);

    agl::lyr::Renderer::instance()->createLayer<KoopatlasLayer2D>(cLayer_2D_Pre3D, "2D_Pre3D", agl::lyr::cDisplayType_Top_TV, heap);
    agl::lyr::Renderer::instance()->createLayer<KoopatlasLayer2D>(cLayer_2D, "2D", agl::lyr::cDisplayType_Top_TV, heap)->setClearDepthEnable(true);
    agl::lyr::Renderer::instance()->createLayer<KoopatlasLayer2D>(cLayer_2D_Menu, "2D_Menu", agl::lyr::cDisplayType_Top_TV, heap)->setClearDepthEnable(true);

    agl::lyr::Renderer::instance()->createLayer<KoopatlasLayer2D>(cLayer_2D_Pre3D_DRC, "2D_Pre3D_DRC", agl::lyr::cDisplayType_Bottom_DRC, heap);
    agl::lyr::Renderer::instance()->createLayer<KoopatlasLayer2D>(cLayer_2D_DRC, "2D_DRC", agl::lyr::cDisplayType_Bottom_DRC, heap)->setClearDepthEnable(true);
}
