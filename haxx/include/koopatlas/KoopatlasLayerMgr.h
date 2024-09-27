#pragma once

#include <graphics/LayerMgr.h>

class KoopatlasLayerMgr
{
public:
    enum Layer
    {
        // Aliases
        cLayer_Gather       = LayerMgr::cLayer_Gather,
        cLayer_2D_TV        = LayerMgr::cLayer_DRCMode,

        cLayer_2D_Pre3D     = LayerMgr::cLayer_User_0,
      //cLayer_3D           = LayerMgr::cLayer_User_1,
        cLayer_2D           = LayerMgr::cLayer_User_2,
        cLayer_3D_World     = LayerMgr::cLayer_User_3,
        cLayer_2D_Menu      = LayerMgr::cLayer_User_4,

        cLayer_2D_Pre3D_DRC = LayerMgr::cLayer_DRC_User_0,
      //cLayer_3D_DRC       = LayerMgr::cLayer_DRC_User_1,
        cLayer_2D_DRC       = LayerMgr::cLayer_DRC_User_2
    };

public:
    static void createLayers(sead::Heap* heap);
};
