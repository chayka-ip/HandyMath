#include "HandyMath/Public/HMStructs/Trajectory.h"
#include "HandyMathTrajectoryLibrary.h"

FVector FTrajectory::GetClosestPointOfTrajectoryRelToPoint(FVector Location, bool bXY) const
{
    int Index;
    return UHMTrajectory::GetClosestPointOfTrajectoryRelToPoint(Points, Location, bXY, Index);
}
