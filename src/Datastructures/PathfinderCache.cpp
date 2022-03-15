#include "PathfinderCache.hpp"
#include "PathfinderReturnType.hpp"


namespace Pathfinding::Datastructures
{
    void PathfinderCache::cache(PathfinderReturnType aStarReturnType)
    {
        currentPath = aStarReturnType.path;
        nodesExpandedAll.push_back(aStarReturnType.nodesExpanded);
    }

    void PathfinderCache::reset()
    {
        currentPath.clear();
        nodesExpandedAll.clear();
    }
}