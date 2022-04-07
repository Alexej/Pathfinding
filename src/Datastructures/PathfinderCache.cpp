#include "PathfinderCache.hpp"
#include "PathfinderReturnType.hpp"


namespace Pathfinding::Datastructures
{
    void PathfinderCache::cache(PathfinderReturnType aStarReturnType)
    {
        currentPath = aStarReturnType.path;
        nodesExpandedAll.push_back(aStarReturnType.nodesExpandedAll);
    }

    void PathfinderCache::reset()
    {
        currentPath.clear();
        nodesExpandedAll.clear();
    }

    bool PathfinderCache::nodesExpandedLastIteration() const
    {
        return nodesExpandedAll.back().size() != 0;
    }
}