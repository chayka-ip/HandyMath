#pragma once

#include "CoreMinimal.h"
#include "HMEllipse.generated.h"

USTRUCT(BlueprintType)
struct FHMEllipse
{
    GENERATED_BODY()

public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Center = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Right = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Up = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Forward = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MajorR = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinorR = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Density = 5;
};