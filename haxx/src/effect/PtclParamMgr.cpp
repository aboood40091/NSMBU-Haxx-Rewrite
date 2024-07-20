#include <effect/PtclParam.h>
#include <effect/PtclParamMgr.h>

const PtclParam* PtclParamMgr::getParam(u32 index) const
{
    if (index < mParamNum)
        return &(mpParam[index]);
    else
        return nullptr;
}
