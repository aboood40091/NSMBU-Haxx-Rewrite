#include <collision/CollisionRenderer.h>
#include <game/AreaTask.h>
#include <game/Info.h>
#include <map/CourseData.h>

extern f32 PlayerJumpArc;
extern f32 MiniPlayerJumpArc;
extern f32 PlayerJumpMax;
extern f32 PlayerDescentRate;

void AreaTask::setLoopType()
{
    mLoopType = 0;

    CourseDataFile* file = CourseData::instance()->getFile(Info::instance()->getFileNo());
    const Options* options = reinterpret_cast<const Options*>(file->getBlock(CourseDataFile::cBlock_Options));

    if (options->loop & 1)
        mLoopType = 1;

    if (options->loop & 2)
    {
        PlayerJumpArc = 0.5f;
        MiniPlayerJumpArc = 0.5f;
        PlayerJumpMax = 4.5f;
        PlayerDescentRate = -2.0f;
    }
    else
    {
        PlayerJumpArc = 2.5f;
        MiniPlayerJumpArc = 2.5f;
        PlayerJumpMax = 3.628f;
        PlayerDescentRate = -4.0f;
    }
}

void AreaTask::debugDraw(const agl::lyr::RenderInfo& render_info)
{
    drawLayer3D(render_info);
    CollisionRenderer::draw(render_info);
}
