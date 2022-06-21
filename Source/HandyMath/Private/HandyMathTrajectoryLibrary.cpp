// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyMathTrajectoryLibrary.h"

#include "HandyMathVectorLibrary.h"
#include "Kismet/KismetMathLibrary.h"


TArray<float> UHMTrajectory::GetDistancesFromPoint(const TArray<FVector> &Trajectory, FVector Location, bool bXY)
{
	TArray<float> A = {};
	for (FVector Element : Trajectory)
	{
		FVector Delta  = Element - Location;
		if(bXY) Delta.Z = 0;
		A.Add(Delta.Size());		
	}
	return A;
}

FVector UHMTrajectory::GetClosestPointOfTrajectoryRelToPoint(const TArray<FVector> &Trajectory, FVector Location, bool bXY, int& Index)
{
	Index = 0;
	const TArray<float> Distances = GetDistancesFromPoint(Trajectory, Location, bXY);
	float MinDistance;
	UKismetMathLibrary::MinOfFloatArray(Distances, Index, MinDistance);
	const FVector V = Index >= 0 ?  Trajectory[Index] : Location;
	return bXY ? UHMV::GetVectorTrimmedXY(V, bXY) : V;
}

TArray<FVector> UHMTrajectory::RotateTrajectoryByQuat(const TArray<FVector>& P, const FQuat& Q)
{
	const int NumKeys = P.Num();
	if(NumKeys < 2) return P;

	const FVector Origin = P[0];
        
	TArray<FVector> NewValues = {Origin};
	for (int i = 1; i < NumKeys; ++i)
	{
		const FVector V = P[i] - Origin;
		NewValues.Add(Q.RotateVector(V) + Origin);
	}

	return NewValues;
}

bool UHMTrajectory::TrajectoryIntersectionWithPlane(const TArray<FVector>& P, const FPlane& APlane, FVector& Intersection, float& AlphaLineStartEnd, int& StartIndex)
{
	const int Num = P.Num();
	const int MaxIter = Num - 1;
	if(Num > 2)
	{
		for (int i = 0; i < MaxIter; ++i)
		{
			const int Next = i + 1;
			FVector Start = P[i];
			FVector End = P[Next];

			if(UKismetMathLibrary::LinePlaneIntersection(Start, End, APlane, AlphaLineStartEnd, Intersection))
			{
				StartIndex = i;
				return true;
			}
		}
	}
	return false;
}
