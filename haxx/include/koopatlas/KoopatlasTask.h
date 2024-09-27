#pragma once

#include <input/SysControllerWrapper.h>
/*
//#include <layout/AttentionScreen.h>
//#include <layout/BaloonGuide.h>
*/
#include <layout/ChangePlayerNum.h>
/*
//#include <layout/CourseSelectGuide.h>
#include <layout/CourseSelectMenu.h>
//#include <layout/CourseSelectWorldName.h>
//#include <layout/EventWindow.h>
#include <layout/ItemList.h>
#include <layout/ItemStock.h>
//#include <layout/KinopioTalkWindow.h>
//#include <layout/SetUpBtn.h>
//#include <layout/SetUpOlive.h>
//#include <layout/ShadowTalkWindow.h>
//#include <layout/StarCoinList.h>
//#include <layout/TutorialOliveWindow.h>
//#include <layout/WarpSelectWindow.h>
*/
#include <state/FStateMgr.h>
#include <state/FStateID.h>

#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>
#include <layer/aglDrawMethod.h>

class KoopatlasTask : public sead::CalculateTask
{
    SEAD_TASK_SINGLETON_DISPOSER(KoopatlasTask)

public:
    static const s32 cRemoteNum = 4;

public:
    KoopatlasTask(const sead::TaskConstructArg& arg);

    void prepare() override;
    void enter() override;
    void exit() override;
    void calc() override;

    DECLARE_STATE_ID(KoopatlasTask, Limbo)
    DECLARE_STATE_ID(KoopatlasTask, ContinueWait)
    DECLARE_STATE_ID(KoopatlasTask, Normal)
    DECLARE_STATE_ID(KoopatlasTask, CompletionMsg)
    DECLARE_STATE_ID(KoopatlasTask, CompletionMsgHideWait)
    DECLARE_STATE_ID(KoopatlasTask, CSMenu)
    DECLARE_STATE_ID(KoopatlasTask, TitleConfirmOpenWait)
    DECLARE_STATE_ID(KoopatlasTask, TitleConfirmSelect)
    DECLARE_STATE_ID(KoopatlasTask, TitleConfirmHitWait)
    DECLARE_STATE_ID(KoopatlasTask, PlayerChangeWait)
    DECLARE_STATE_ID(KoopatlasTask, EasyPairingWait)
    DECLARE_STATE_ID(KoopatlasTask, PowerupsWait)
    DECLARE_STATE_ID(KoopatlasTask, ShopWait)
    DECLARE_STATE_ID(KoopatlasTask, CoinsWait)
    DECLARE_STATE_ID(KoopatlasTask, SaveOpen)
    DECLARE_STATE_ID(KoopatlasTask, SaveSelect)
    DECLARE_STATE_ID(KoopatlasTask, SaveWindowClose)
    DECLARE_STATE_ID(KoopatlasTask, SaveDo)
    DECLARE_STATE_ID(KoopatlasTask, SaveEndWindow)
    DECLARE_STATE_ID(KoopatlasTask, SaveEndCloseWait)
#ifdef QUICK_SAVE
    DECLARE_STATE_ID(KoopatlasTask, QuickSaveOpen)
    DECLARE_STATE_ID(KoopatlasTask, QuickSaveSelect)
    DECLARE_STATE_ID(KoopatlasTask, QuickSaveWindowClose)
    DECLARE_STATE_ID(KoopatlasTask, QuickSaveDo)
    DECLARE_STATE_ID(KoopatlasTask, QuickSaveEndWindow)
    DECLARE_STATE_ID(KoopatlasTask, QuickSaveEndCloseWait)
#endif
    DECLARE_STATE_ID(KoopatlasTask, SaveError)

private:
    void startLoading_();
    void loadStaticFiles_();
    void stockLoadEffects_();
    void loadSIAnims_();
    void endLoading_();
    void loadResources1_();
    void loadResources2_();
    void setupWait_();
    void setupExtra_();
    void setupWipe_();

    void gather_(const agl::lyr::RenderInfo& render_info);

    void draw_2D_Pre3D_(const agl::lyr::RenderInfo& render_info) const;
    void draw_2D_(const agl::lyr::RenderInfo& render_info) const;
    void draw_2D_Menu_(const agl::lyr::RenderInfo& render_info) const;
    void draw_2D_TV_(const agl::lyr::RenderInfo& render_info) const;
    void draw_2D_Pre3D_DRC_(const agl::lyr::RenderInfo& render_info) const;
    void draw_2D_DRC_(const agl::lyr::RenderInfo& render_info) const;

private:
    FStateMgr<KoopatlasTask>    mStateMgr;
    sead::UnsafeArray<
        SysControllerWrapper,
        cRemoteNum
    >                           mRemote;
    SysControllerWrapper        mDRC;
    sead::OrthoCamera           mCamera2D;
    sead::OrthoProjection       mProjection2D;
    agl::lyr::DrawMethod        mDrawMethod_Gather;
    agl::lyr::DrawMethod        mDrawMethod_2D_Pre3D;
    agl::lyr::DrawMethod        mDrawMethod_2D;
    agl::lyr::DrawMethod        mDrawMethod_2D_Menu;
    agl::lyr::DrawMethod        mDrawMethod_2D_TV;
    agl::lyr::DrawMethod        mDrawMethod_2D_Pre3D_DRC;
    agl::lyr::DrawMethod        mDrawMethod_2D_DRC;
    /*
  //CourseSelectGuide           mGuide;
    CourseSelectMenu            mMenu;
    ItemList                    mItemList;
    ItemStock                   mItemStock;
  //KinopioTalkWindow           mKinopioTalkWindow;
  //StarCoinList                mStarCoinList;
  //SetUpOlive                  mSetUpOlive;
  //ShadowTalkWindow            mShadowTalkWindow;
  //BaloonGuide                 mBaloonGuide;
  //AttentionScreen             mAttentionScreen;
    ChangePlayerNum             mChangePlayerNum;
  //SetUpBtn                    mSetUpBtn;
  //WarpSelectWindow            mWarpSelectWindow;
  //CourseSelectWorldName       mWorldName;
  //EventWindow                 mEventWindow;
  //TutorialOliveWindow         mTutorialOliveWindow;
    */
};
