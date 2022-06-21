#pragma once

#include "CoreMinimal.h"
#include "TimeAngleVector.generated.h"

USTRUCT(BlueprintType)
struct FTimeAngleVector
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    float Time = 0.0f;
    UPROPERTY(BlueprintReadWrite)
    float Angle = 0.0f;
    UPROPERTY(BlueprintReadWrite)
    FVector Vector = FVector::ZeroVector;
};
