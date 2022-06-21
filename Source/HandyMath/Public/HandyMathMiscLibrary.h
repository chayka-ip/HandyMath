// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandyMathMiscLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HANDYMATH_API UHandyMathMiscLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static FPlane PlaneFromPoints(FVector A, FVector B, FVector C);
};
