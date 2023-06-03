#include <collision/ActorBgCollisionCheck.h>
#include <collision/ActorBgCollisionCheckMgr.h>

SEAD_SINGLETON_DISPOSER_IMPL(ActorBgCollisionCheckMgr)

ActorBgCollisionCheckMgr::List::Node* ActorBgCollisionCheckMgr::findInDrawList_(const ActorBgCollisionCheck& bc) const
{
    for (List::Node* node = mDrawList.front(); node != nullptr; node = node->next)
        if (node->obj == &bc)
            return node;

    return nullptr;
}

bool ActorBgCollisionCheckMgr::isInDrawList_(const ActorBgCollisionCheck& bc) const
{
    return findInDrawList_(bc) != nullptr;
}

void ActorBgCollisionCheckMgr::addToDrawList_(const ActorBgCollisionCheck& bc)
{
    if (!isInDrawList_(bc))
    {
        List::Node* node = new (MEMAllocFromDefaultHeap(sizeof(List::Node))) List::Node(const_cast<ActorBgCollisionCheck*>(&bc));
        mDrawList.pushBack(node);
    }
}

void ActorBgCollisionCheckMgr::removeFromDrawList_(const ActorBgCollisionCheck& bc)
{
    List::Node* node = findInDrawList_(bc);
    if (node != nullptr)
    {
        mDrawList.erase(node);
        MEMFreeToDefaultHeap(node);
    }
}

void ActorBgCollisionCheckMgr::entry(const ActorBgCollisionCheck& bc)
{
    addToDrawList_(bc);
}

void ActorBgCollisionCheckMgr::release(const ActorBgCollisionCheck& bc)
{
    removeFromDrawList_(bc);
}

extern "C" uintptr ActorBgCollisionCheckMgr_createInstance(uintptr collider_mgr)
{
    ActorBgCollisionCheckMgr::createInstance(nullptr);
    return collider_mgr;
}

extern "C" void ActorBgCollisionCheckMgr_entry(const ActorBgCollisionCheck& bc)
{
    ActorBgCollisionCheckMgr::instance()->entry(bc);
}
