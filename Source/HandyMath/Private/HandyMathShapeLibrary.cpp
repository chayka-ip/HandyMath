// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyMathShapeLibrary.h"

#include "HandyMathVectorLibrary.h"
#include "NativeLib.h"

TArray<FVector> UHMS::GetEllipsePoints(FVector Center, FVector Right, FVector Up, float MajorR, float MinorR, TArray<FVector> &InnerPoints, int Density,  bool bComputeInnerPoints)
{
    // (x / MajorR)^2 + (y / MinorR)^2 = 1
    // y = (+/-) * (MinorR / MajorR) * sqrt(MajorR^2 - x^2)

    TArray<FVector> Points;

    MajorR = FMath::Abs(MajorR);
    MinorR = FMath::Abs(MinorR);
    
    if(FMath::IsNearlyZero(MajorR) || FMath::IsNearlyZero(MinorR)) return Points;
    if(Density < 2) Density = 2;

    const float IntervalScale = 1.0f / Density;
    const float AxisRatioInv = MinorR / MajorR;
    const float MajorRSquared = MajorR * MajorR;
    
    const float dX = MajorR * IntervalScale;
    const float dY = MinorR * IntervalScale;

    float X = -MajorR;

    TArray<FVector> BottomHalfPoints;
    while (true)
    {
        const float ZeroTolerance = 0.2f * dX;
        const bool bFirstIter = FMath::IsNearlyEqual(X, -MajorR, ZeroTolerance);
        const bool bLastIter = FMath::IsNearlyEqual(X, MajorR, ZeroTolerance);
        const bool IsNotVertex = !(bFirstIter || bLastIter);

        const float Y = AxisRatioInv * FMath::Sqrt(MajorRSquared - X*X);

        FVector CPX = Center + Right * X;
        FVector PYMax = Up * Y;

        Points.Add(CPX + PYMax);
        
        if(IsNotVertex)
        {
            BottomHalfPoints.Add(CPX - PYMax);

            if(bComputeInnerPoints)
            {
                const int StepsBetween = (2.0f * Y / dY) - 1;
                if (StepsBetween > 0)
                {
                    float YInner = Y - dY;
                    for (int i = 0; i < StepsBetween; ++i)
                    {
                        FVector PYInner = Up * YInner;
                        InnerPoints.Add(CPX + PYInner);
                        YInner -= dY;
                    }
                }
            }
        }
        
        X += dX;
        if(bLastIter) break;
    }

    Native::AddToArrayAsInverted(Points, BottomHalfPoints);
    return Points;
}

TArray<FVector> UHMS::GetEllipsePointsCombined(FHMEllipse P, bool bComputeInnerPoints)
{
    TArray<FVector> InnerPoints;
    TArray<FVector> Border = GetEllipsePoints(P.Center, P.Right, P.Up, P.MajorR, P.MinorR, InnerPoints, P.Density, bComputeInnerPoints);
    Border.Append(InnerPoints);
    return Border;
}

TArray<FVector> UHMS::ProjectPointsOntoSphere(FVector SC, float SR, const TArray<FVector>& Points, FVector N, bool bExcludePointsInsideSphere)
{
    TArray<FVector> Out;
    const bool bComputeForPointsInsideSphere = !bExcludePointsInsideSphere;
    for (FVector P : Points)
    {
        const bool IsPointInSphere = (SC - P).Size() < SR;
        if(IsPointInSphere)
        {
            if(bComputeForPointsInsideSphere)
            {
                P = P - 5.0f * SR * N;
            }
            else
            {
                continue;
            }
        }
        
        FVector ClosestIntersection, _;
        if(UHMV::GetLineIntersectionsWithSphereFromPAndNormal(P, N, SC, SR, ClosestIntersection, _))
        {
            Out.Add(ClosestIntersection);
        }
    }
    return  Out;
}

TArray<FVector> UHMS::CalculatePointsOnRadialBound(FVector Center, FVector DirectionInPlane, float FullAngle, float AngleStep, float Radius)
{
    TArray<FVector> TargetPoints;
    const FVector V = Radius * DirectionInPlane;

    FVector FirstPoint = V + Center;
    FVector LastPoint = V.RotateAngleAxis(FullAngle, FVector::UpVector) + Center;
	
    if(FMath::Abs(FullAngle) <= FMath::Abs(AngleStep))
    {
        TargetPoints = {FirstPoint, LastPoint};
    }
    else
    {
        const float DeltaAngle = FMath::Abs(AngleStep) * FMath::Sign(FullAngle);
        const int NumSteps = FMath::Abs(FullAngle) / AngleStep;
        for (int i = 0; i < NumSteps; ++i)
        {
            FVector P = V.RotateAngleAxis(i * DeltaAngle, FVector::UpVector) + Center;
            TargetPoints.Add(P);
        }
        TargetPoints.Add(LastPoint);
    }
    return TargetPoints;
}

TArray<FVector> UHMS::CalculateCirclePoints(FVector Center, FVector DirectionInPlane, float AngleStep, float Radius)
{
    const auto FullCircleAngleComp = 360.0f + AngleStep;
    return  CalculatePointsOnRadialBound(Center, DirectionInPlane, FullCircleAngleComp, AngleStep, Radius);
}
