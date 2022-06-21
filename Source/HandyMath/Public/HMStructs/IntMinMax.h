#pragma once

#include "CoreMinimal.h"
#include "IntMinMax.generated.h"

USTRUCT(BlueprintType)
struct FIntMinMax
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Min = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Max = 0;
};
