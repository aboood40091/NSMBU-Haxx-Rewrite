#include <sound/AudFxSocket.h>
#include <sound/SndAudioMgr.h>
#include <sound/SndSceneMgr.h>

extern "C" {

extern nw::snd::internal::FxReverbHiParam DefaultReverbHiParam;
extern nw::snd::internal::FxDelayParam    DefaultDelayParam;

extern f32 SFXReverb_0;
extern f32 SFXReverb_1;
extern f32 SFXReverbPlyJump_0;
extern f32 SFXReverbPlyJump_1;

void SetFxReverbHiAndDelay(void*, SndSceneMgr::EffectType sfx_mode)
{
    nw::snd::internal::FxReverbHiParam& reverbHiParam = SndAudioMgr::instance()->getFxSocket()->getReverbHiParam();
    nw::snd::internal::FxDelayParam&    delayParam    = SndAudioMgr::instance()->getFxSocket()->getDelayParam();

    reverbHiParam.preDelayTime = 0.02f;
    reverbHiParam.fusedTime = 3.0f;
    reverbHiParam.coloration = 0.6f;
    reverbHiParam.damping = 0.4f;
    reverbHiParam.crosstalk = 0.1f;
    reverbHiParam.outGain = 1.0f;
    reverbHiParam.earlyMode = 5;
    reverbHiParam.preDelayTimeMax = 0.02f;
    reverbHiParam.fusedMode = 0;
    reverbHiParam.earlyGain = 0.0f;
    reverbHiParam.fusedGain = 1.0f;
    DefaultReverbHiParam = reverbHiParam;

    delayParam.delay = 160.0f;
    delayParam.feedback = 0.4f;
    delayParam.outGain = 1.0f;
    delayParam.maxDelay = 160.0f;
    delayParam.lpf = 1.0f;
    DefaultDelayParam = delayParam;

    switch (sfx_mode)
    {
    case SndSceneMgr::cEffect_Soto:
  //case SndSceneMgr::cEffect_Default:
    default:
        reverbHiParam.fusedTime = 4.0f;
        reverbHiParam.damping = 0.0f;
        reverbHiParam.fusedMode = 5;

        delayParam.delay = 120.0f;
        delayParam.feedback = 0.1f;
        delayParam.maxDelay = 120.0f;

        SFXReverb_0 = 0.03f;
        SFXReverb_1 = 0.01f;
        SFXReverbPlyJump_0 = 0.04f;
        SFXReverbPlyJump_1 = 0.04f;
        return;
    case SndSceneMgr::cEffect_Chika:
    case SndSceneMgr::cEffect_Chika_Sa:
        reverbHiParam.fusedTime = 5.0f;
        reverbHiParam.fusedMode = 5;

        delayParam.delay = 180.0f;
        delayParam.feedback = 0.5f;
        delayParam.maxDelay = 180.0f;

        SFXReverb_0 = 0.04f;
        SFXReverb_1 = 0.1f;
        SFXReverbPlyJump_0 = 0.03f;
        SFXReverbPlyJump_1 = 0.05f;
        return;
    case SndSceneMgr::cEffect_Chika_S:
        reverbHiParam.fusedTime = 1.2f;
        reverbHiParam.damping = 0.9f;
        reverbHiParam.fusedMode = 2;

        delayParam.delay = 100.0f;
        delayParam.feedback = 0.1f;
        delayParam.maxDelay = 100.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.07f;
        SFXReverbPlyJump_0 = 0.07f;
        SFXReverbPlyJump_1 = 0.07f;
        return;
    case SndSceneMgr::cEffect_Water:
        reverbHiParam.fusedTime = 3.0f;
        reverbHiParam.fusedMode = 2;

        delayParam.delay = 180.0f;
        delayParam.feedback = 0.3f;
        delayParam.maxDelay = 180.0f;

        SFXReverb_0 = 0.1f;
        SFXReverb_1 = 0.1f;
        SFXReverbPlyJump_0 = 0.03f;
        SFXReverbPlyJump_1 = 0.1f;
        return;
    case SndSceneMgr::cEffect_Boss:
        reverbHiParam.damping = 0.2f;
        reverbHiParam.fusedMode = 3;

        delayParam.delay = 200.0f;
        delayParam.feedback = 0.38f;
        delayParam.maxDelay = 200.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.08f;
        SFXReverbPlyJump_0 = 0.07f;
        SFXReverbPlyJump_1 = 0.04f;
        return;
    case SndSceneMgr::cEffect_Toride:
        reverbHiParam.damping = 0.9f;
        reverbHiParam.fusedMode = 3;

        delayParam.delay = 190.0f;
        delayParam.feedback = 0.4f;
        delayParam.maxDelay = 190.0f;

        SFXReverb_0 = 0.05f;
        SFXReverb_1 = 0.12f;
        SFXReverbPlyJump_0 = 0.05f;
        SFXReverbPlyJump_1 = 0.07f;
        return;
    case SndSceneMgr::cEffect_Shiro:
        reverbHiParam.damping = 0.1f;
        reverbHiParam.fusedMode = 4;

        delayParam.delay = 190.0f;
        delayParam.feedback = 0.3f;
        delayParam.maxDelay = 190.0f;

        SFXReverb_0 = 0.1f;
        SFXReverb_1 = 0.13f;
        SFXReverbPlyJump_0 = 0.1f;
        SFXReverbPlyJump_1 = 0.08f;
        return;
    case SndSceneMgr::cEffect_Obake:
        reverbHiParam.fusedTime = 2.5f;
        reverbHiParam.fusedMode = 2;

        delayParam.delay = 94.0f;
        delayParam.feedback = 0.13f;
        delayParam.maxDelay = 94.0f;

        SFXReverb_0 = 0.06f;
        SFXReverb_1 = 0.17f;
        SFXReverbPlyJump_0 = 0.06f;
        SFXReverbPlyJump_1 = 0.17f;
        return;
    case SndSceneMgr::cEffect_Dokan:
        reverbHiParam.fusedTime = 1.8f;
        reverbHiParam.coloration = 0.4f;
        reverbHiParam.fusedMode = 1;

        delayParam.delay = 32.0f;
        delayParam.feedback = 0.83f;
        delayParam.maxDelay = 100.0f;

        SFXReverb_0 = 0.04f;
        SFXReverb_1 = 0.08f;
        SFXReverbPlyJump_0 = 0.04f;
        SFXReverbPlyJump_1 = 0.1f;
        return;
    case SndSceneMgr::cEffect_Gake:
        reverbHiParam.fusedTime = 1.0f;
        reverbHiParam.fusedMode = 5;

        delayParam.delay = 350.0f;
        delayParam.feedback = 0.1f;
        delayParam.maxDelay = 350.0f;

        SFXReverb_0 = 0.01f;
        SFXReverb_1 = 0.02f;
        SFXReverbPlyJump_0 = 0.01f;
        SFXReverbPlyJump_1 = 0.02f;
        return;
    case SndSceneMgr::cEffect_House:
        reverbHiParam.fusedTime = 0.3f;
        reverbHiParam.fusedMode = 2;

        delayParam.delay = 22.0f;
        delayParam.feedback = 0.4f;
        delayParam.maxDelay = 60.0f;

        SFXReverb_0 = 0.1f;
        SFXReverb_1 = 0.15f;
        SFXReverbPlyJump_0 = 0.1f;
        SFXReverbPlyJump_1 = 0.15f;
        return;
    case SndSceneMgr::cEffect_Boss_Jr:
        reverbHiParam.fusedTime = 0.8f;
        reverbHiParam.fusedMode = 2;

        delayParam.delay = 39.0f;
        delayParam.feedback = 0.3f;
        delayParam.maxDelay = 39.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.15f;
        SFXReverbPlyJump_0 = 0.07f;
        SFXReverbPlyJump_1 = 0.15f;
        return;
    case SndSceneMgr::cEffect_Kurayami:
        reverbHiParam.fusedTime = 3.5f;
        reverbHiParam.fusedMode = 5;

        delayParam.delay = 180.0f;
        delayParam.feedback = 0.4f;
        delayParam.maxDelay = 180.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.15f;
        SFXReverbPlyJump_0 = 0.05f;
        SFXReverbPlyJump_1 = 0.1f;
        return;
    case SndSceneMgr::cEffect_Chika_Ka:
        reverbHiParam.fusedTime = 5.0f;
        reverbHiParam.fusedMode = 5;

        delayParam.delay = 180.0f;
        delayParam.feedback = 0.5f;
        delayParam.maxDelay = 180.0f;

        SFXReverb_0 = 0.04f;
        SFXReverb_1 = 0.08f;
        SFXReverbPlyJump_0 = 0.04f;
        SFXReverbPlyJump_1 = 0.08f;
    }
}

}
