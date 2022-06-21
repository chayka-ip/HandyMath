// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMStructs/CustomVectorCurve.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandyMathVectorCurveLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HANDYMATH_API UHMVC : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintPure)
    static FVector GetVectorValue(const FCustomVectorCurve& Curve, float Time);
    UFUNCTION(BlueprintPure)
    static FVector GetLastKey(const FCustomVectorCurve& Curve);
    UFUNCTION(BlueprintPure)
    static bool GetLastTimeWhenZEquals(const FCustomVectorCurve& Curve, float& OutTime, float Value=0.0f, float Tolerance=0.01f, float StartTime=0.0);
    
public:
    UFUNCTION(BlueprintCallable)
    static FCustomVectorCurve SplitVectorCurveByPlaneIntersection(const FCustomVectorCurve& Curve, const FPlane& Plane, bool PreservePartFromOrigin=true);
    UFUNCTION(BlueprintCallable)
    static FCustomVectorCurve SplitVectorCurveByPlaneIntersectionFromOrigin(const FCustomVectorCurve& Curve, const FPlane& Plane);

    UFUNCTION(BlueprintPure)
    static TArray<FVector> GetCustomVectorCurvePoints(const FCustomVectorCurve& Curve);
};
