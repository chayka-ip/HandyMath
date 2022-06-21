#pragma once

#include "CoreMinimal.h"
#include "TimeLocation.generated.h"

USTRUCT()
struct FTimeLocation
{
    GENERATED_BODY()

public:
    FTimeLocation(){}
    FTimeLocation(float time, FVector location)
    {
        Time = time;
        Location = location;
    }
    
public:
    float Time = 0.0f;
    FVector Location = FVector::ZeroVector;
};
