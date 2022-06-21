// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandyMathTrajectoryLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HANDYMATH_API UHMTrajectory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static TArray<float> GetDistancesFromPoint(const TArray<FVector> &Trajectory, FVector Location, bool bXY);
	
	UFUNCTION(BlueprintCallable)
	static FVector GetClosestPointOfTrajectoryRelToPoint(const TArray<FVector>& Trajectory, FVector Location, bool bXY, int& Index);

	UFUNCTION(BlueprintCallable)
	static TArray<FVector> RotateTrajectoryByQuat(const TArray<FVector>& P, const FQuat& Q);

	UFUNCTION(BlueprintCallable)
	static bool TrajectoryIntersectionWithPlane(const TArray<FVector>& P, const FPlane& APlane, FVector& Intersection, float& AlphaLineStartEnd, int& StartIndex);
};
