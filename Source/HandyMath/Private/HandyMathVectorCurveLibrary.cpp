// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyMathVectorCurveLibrary.h"

#include "HandyMathTrajectoryLibrary.h"

FVector UHMVC::GetVectorValue(const FCustomVectorCurve& Curve, float Time)
{
    return Curve.GetVectorValue(Time);
}

FVector UHMVC::GetLastKey(const FCustomVectorCurve& Curve)
{
    return Curve.LastKey();
}

bool UHMVC::GetLastTimeWhenZEquals(const FCustomVectorCurve& Curve, float& OutTime, float Value, float Tolerance, float StartTime)
{
    return Curve.GetLastTimeWhenZEquals(OutTime, Value, Tolerance, StartTime);
}

FCustomVectorCurve UHMVC::SplitVectorCurveByPlaneIntersection(const FCustomVectorCurve& Curve, const FPlane& Plane,
                                                              bool PreservePartFromOrigin)
{
    const auto Points = Curve.GetVectorKeys();
    
    FVector Intersection;
    float Alpha;
    int StartIndex;
    const bool bIntersect = UHMTrajectory::TrajectoryIntersectionWithPlane(Points, Plane, Intersection, Alpha,StartIndex);
    
    if(bIntersect)
    {
        const int EndIndex = StartIndex + 1;
        check(EndIndex < Points.Num())
        const float IntersectionTime = Curve.GetTimeBetweenKeyIndices(StartIndex, EndIndex, Alpha);

        if(PreservePartFromOrigin)
        {
            auto Slice = Curve.GetSliceByKeyIndexFromStart(StartIndex);
            Slice.UpdateOrAddKey(IntersectionTime, Intersection);
            return Slice;
        }
        
        auto Slice = Curve.GetSliceByKeyIndexFromEnd(EndIndex);
        Slice.UpdateOrAddKey(IntersectionTime, Intersection);
        return Slice;
    }

    return  PreservePartFromOrigin ? Curve : FCustomVectorCurve();
}

FCustomVectorCurve UHMVC::SplitVectorCurveByPlaneIntersectionFromOrigin(const FCustomVectorCurve& Curve, const FPlane& Plane)
{
    return SplitVectorCurveByPlaneIntersection(Curve, Plane, true);
}

TArray<FVector> UHMVC::GetCustomVectorCurvePoints(const FCustomVectorCurve& Curve)
{
    return Curve.GetVectorKeys();
}
