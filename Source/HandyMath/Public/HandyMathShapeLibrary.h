// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMStructs/HMEllipse.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandyMathShapeLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HANDYMATH_API UHMS : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

    UFUNCTION(BlueprintCallable)
    static TArray<FVector> GetEllipsePoints(FVector Center, FVector Right, FVector Up, float MajorR, float MinorR, TArray<FVector> &InnerPoints, int Density=5, bool bComputeInnerPoints=false);

    UFUNCTION(BlueprintCallable)
    static TArray<FVector> GetEllipsePointsCombined(FHMEllipse P, bool bComputeInnerPoints=false);
    
    UFUNCTION(BlueprintCallable)
    static TArray<FVector> ProjectPointsOntoSphere(FVector SC, float SR, const TArray<FVector> &Points, FVector N, bool bExcludePointsInsideSphere);

    UFUNCTION(BlueprintCallable)
    static TArray<FVector> CalculatePointsOnRadialBound(FVector Center, FVector DirectionInPlane, float FullAngle, float AngleStep, float Radius);

    UFUNCTION(BlueprintCallable)
    static TArray<FVector> CalculateCirclePoints(FVector Center, FVector DirectionInPlane, float AngleStep, float Radius);
};
