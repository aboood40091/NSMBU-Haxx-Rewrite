#include <effect/PtclMgr.h>
#include <game/SelectCursor.h>
//#include <graphics/LayerMgr.h>
#include <graphics/LightMapMgr.h>
#include <graphics/Renderer.h>
#include <koopatlas/KoopatlasLayer.h>
#include <koopatlas/KoopatlasLayerMgr.h>
#include <koopatlas/KoopatlasTask.h>
#include <layout/ChangePlayerNum_Haxx.h>
#include <scene/Scene.h>
#include <system/MainGame.h>

#include <gfx/seadGraphicsContext.h>

#include <log.h>

template
sead::TaskBase* sead::TTaskFactory<KoopatlasTask>(const sead::TaskConstructArg& arg);

static inline ChangePlayerNum&
ChangePlayerNum_GetInstance()
{
    return *ChangePlayerNumHaxx::instance();
}

void E3CourseSelectScene_SwitchToTitleScene(sead::TaskBase* _this); // Originally a state function of E3CourseSelectScene

CREATE_STATE_ID(KoopatlasTask, ContinueWait)
CREATE_STATE_ID(KoopatlasTask, Normal)
CREATE_STATE_ID(KoopatlasTask, PlayerChangeWait)

SEAD_TASK_SINGLETON_DISPOSER_IMPL(KoopatlasTask)

KoopatlasTask::KoopatlasTask(const sead::TaskConstructArg& arg)
    : sead::CalculateTask(arg, "KoopatlasTask")
    , mStateMgr(*this, StateID_ContinueWait)
{
}

void KoopatlasTask::prepare()
{
    // GameAudio::loadSceneSnd();
    {
        PtclMgr::instance()->resetUserDataCallbacks();
        LightMapMgr::instance()->initialize();

        KoopatlasLayerMgr::createLayers(nullptr);

        /*
        SpammyReport("Setting Active Players\n");
        for (int i = 0; i < 4; i++) {
            bool isThere = QueryPlayerAvailability(i);
            int id = Player_ID[i];
            Player_Active[i] = isThere ? 1 : 0;
            if (!isThere) Player_Flags[i] = 0;
        }
        */

        /*
      //CommonWindowMgr::createInstance(nullptr);
        SelectCursor::createInstance(nullptr);

      //mGuide.create();
        mMenu.create();
        mItemList.create();
        mItemStock.create();
      //mKinopioTalkWindow.create();
      //mStarCoinList.create();
      //mSetUpOlive.create();
      //mShadowTalkWindow.create();
      //mBaloonGuide.create();
      //mAttentionScreen.create();
        mChangePlayerNum.create();
      //mSetUpBtn.create();
      //mWarpSelectWindow.create();
      //mWorldName.create();
      //mEventWindow.create();
      //mTutorialOliveWindow.create();
      //CommonWindowMgr::instance()->create();
        SelectCursor::instance()->create();
        */

        ChangePlayerNumHaxx::createInstance(nullptr);
        SelectCursor::createInstance(nullptr);

        ChangePlayerNum_GetInstance().create();
        SelectCursor::instance()->create();

        // --------------------

        startLoading_();
        loadStaticFiles_();
        stockLoadEffects_();
        loadSIAnims_();
        endLoading_();
        loadResources1_();
        loadResources2_();
        setupWait_();
        setupExtra_();
        setupWipe_();

        // ---------------------

        adjustHeapAll();
    }
    // GameAudio::waitLoadSceneSnd();
}

void KoopatlasTask::startLoading_()
{
}

void KoopatlasTask::loadStaticFiles_()
{
}

void KoopatlasTask::stockLoadEffects_()
{
}

void KoopatlasTask::loadSIAnims_()
{
}

void KoopatlasTask::endLoading_()
{
}

void KoopatlasTask::loadResources1_()
{
}

void KoopatlasTask::loadResources2_()
{
}

void KoopatlasTask::setupWait_()
{
}
void KoopatlasTask::setupExtra_()
{
}

void KoopatlasTask::setupWipe_()
{
}

void KoopatlasTask::enter()
{
    // bool isDRCMain = !MainGame::instance()->isWiimote();
    // LayerMgr::instance()->setDisableMirrorTvToDrc(isDRCMain);
    // SysControllerMgr::instance()->setDRCMain(isDRCMain);

    for (s32 i = 0; i < cRemoteNum; i++)
        mRemote[i].registerWith(SysController::Id(SysController::cId_CafeRemote_1 + i));

    mDRC.registerWith(SysController::cId_CafeDRC_Multiplayer);

    mDrawMethod_Gather.bind(this, &KoopatlasTask::gather_, "Koopatlas");
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_Gather)->pushBackDrawMethod(&mDrawMethod_Gather);

    mDrawMethod_2D_Pre3D.bind(this, &KoopatlasTask::draw_2D_Pre3D_, "2D_Pre3D");
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_Pre3D)->pushBackDrawMethod(&mDrawMethod_2D_Pre3D);

    mDrawMethod_2D.bind(this, &KoopatlasTask::draw_2D_, "2D");
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D)->pushBackDrawMethod(&mDrawMethod_2D);

    mDrawMethod_2D_Menu.bind(this, &KoopatlasTask::draw_2D_Menu_, "2D_Menu");
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_Menu)->pushBackDrawMethod(&mDrawMethod_2D_Menu);

    mDrawMethod_2D_TV.bind(this, &KoopatlasTask::draw_2D_TV_, "2D_TV");
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_TV)->pushBackDrawMethod(&mDrawMethod_2D_TV);

    mDrawMethod_2D_Pre3D_DRC.bind(this, &KoopatlasTask::draw_2D_Pre3D_DRC_, "2D_Pre3D_DRC");
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_Pre3D_DRC)->pushBackDrawMethod(&mDrawMethod_2D_Pre3D_DRC);

    mDrawMethod_2D_DRC.bind(this, &KoopatlasTask::draw_2D_DRC_, "2D_DRC");
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_DRC)->pushBackDrawMethod(&mDrawMethod_2D_DRC);

    mProjection2D.setTBLR(360.0f, -360.0f, -640.0f, 640.0f);
    mProjection2D.setNear(0.0f);
    mProjection2D.setFar(20000.0f);

    mCamera2D.setByOrthoProjection(mProjection2D);

    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D)->setCamera(&mCamera2D);
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D)->setProjection(&mProjection2D);

    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_3D_World)->setCamera(&mCamera2D);
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_3D_World)->setProjection(&mProjection2D);

    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_Menu)->setCamera(&mCamera2D);
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_Menu)->setProjection(&mProjection2D);

    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_Pre3D)->setCamera(&mCamera2D);
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_Pre3D)->setProjection(&mProjection2D);

    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_DRC)->setCamera(&mCamera2D);
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_DRC)->setProjection(&mProjection2D);

    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_Pre3D_DRC)->setCamera(&mCamera2D);
    agl::lyr::Renderer::instance()->getLayer(KoopatlasLayerMgr::cLayer_2D_Pre3D_DRC)->setProjection(&mProjection2D);

    // LightMapMgr::instance()->initializeViewDependent(...);
    // ErrorViewerTask::instance()->enterScene();
}

void KoopatlasTask::exit()
{
    PtclMgr::instance()->cleanUp();
    PtclMgr::instance()->setUserDataCallbacks();

    // LightMapMgr::instance()->initializeViewIndependent();
    // LayerMgr::instance()->setDisableMirrorTvToDrc(false);
    // ErrorViewerTask::instance()->exitScene();
}

void KoopatlasTask::calc()
{
    ChangePlayerNum_GetInstance().execute();

    mStateMgr.executeState();
}

void KoopatlasTask::initializeState_ContinueWait()
{
}

void KoopatlasTask::executeState_ContinueWait()
{
    if (Scene::instance()->isFadein())
        return;

    mStateMgr.changeState(StateID_Normal);
}

void KoopatlasTask::finalizeState_ContinueWait()
{
}

void KoopatlasTask::initializeState_Normal()
{
}

void KoopatlasTask::executeState_Normal()
{
    if (mRemote[0].isTrig(SysControllerWrapper::cPadFlag_Plus))
        mStateMgr.changeState(StateID_PlayerChangeWait);

    else if (mRemote[0].isTrig(SysControllerWrapper::cPadFlag_Back))
        E3CourseSelectScene_SwitchToTitleScene(this);
}

void KoopatlasTask::finalizeState_Normal()
{
}

void KoopatlasTask::initializeState_PlayerChangeWait()
{
    ChangePlayerNum_GetInstance().open();
}

void KoopatlasTask::executeState_PlayerChangeWait()
{
    if (ChangePlayerNum_GetInstance().isOpen())
        return;

    mStateMgr.changeState(StateID_Normal);
}

void KoopatlasTask::finalizeState_PlayerChangeWait()
{
}

void KoopatlasTask::gather_(const agl::lyr::RenderInfo& render_info)
{
    Renderer::LayerSetter ls(KoopatlasLayerMgr::cLayer_3D_World, Renderer::cGatherType_1);
    ChangePlayerNum_GetInstance().gather();
}

void KoopatlasTask::draw_2D_Pre3D_(const agl::lyr::RenderInfo& render_info) const
{
    if (render_info.getRenderStep() != KoopatlasLayer2D::cRenderStep_HUD)
        return;
}

void KoopatlasTask::draw_2D_(const agl::lyr::RenderInfo& render_info) const
{
    if (render_info.getRenderStep() != KoopatlasLayer2D::cRenderStep_HUD)
        return;

    sead::GraphicsContext context;
    context.setBlendEnable(false);
    context.setDepthEnable(false, false);
    context.setAlphaTestEnable(false);
    context.apply();

    ChangePlayerNum_GetInstance().drawBtn(render_info);
}

void KoopatlasTask::draw_2D_Menu_(const agl::lyr::RenderInfo& render_info) const
{
    if (render_info.getRenderStep() != KoopatlasLayer2D::cRenderStep_HUD)
        return;

    ChangePlayerNum_GetInstance().draw(render_info);
}

void KoopatlasTask::draw_2D_TV_(const agl::lyr::RenderInfo& render_info) const
{
    if (render_info.getRenderStep() != /* DRCModeLayer::cRenderStep_2D */ 1)
        return;
}

void KoopatlasTask::draw_2D_Pre3D_DRC_(const agl::lyr::RenderInfo& render_info) const
{
    if (render_info.getRenderStep() != KoopatlasLayer2D::cRenderStep_HUD)
        return;
}

void KoopatlasTask::draw_2D_DRC_(const agl::lyr::RenderInfo& render_info) const
{
    if (render_info.getRenderStep() != KoopatlasLayer2D::cRenderStep_HUD)
        return;

    sead::GraphicsContext context;
    context.setBlendEnable(false);
    context.setDepthEnable(false, false);
    context.setAlphaTestEnable(false);
    context.apply();
}
