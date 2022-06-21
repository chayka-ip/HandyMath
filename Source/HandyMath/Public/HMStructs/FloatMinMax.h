#pragma once

#include "CoreMinimal.h"
#include "FloatMinMax.generated.h"

USTRUCT(BlueprintType)
struct FFloatMinMax
{
    GENERATED_BODY()
    
public:
    
    FFloatMinMax(){}
    FFloatMinMax(float min, float max)
    {
        SetMinMax(min, max);
    }

public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Min = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Max = 0.0f;

public:
    void SetMinMax(float min, float max)
    {
        Min = min;
        Max = max;
    }
    
public:
    void AddToMin(float V){Min += V;}
    void AddToMax(float V){Max += V;}
    void SetMin(float V){Min = V;}
    void SetMax(float V){Max = V;}
    void MultiplyMinMax(float V)
    {
        Min *= V;
        Max *= V;
    }
    
public:
    float GetMin() const {return Min;}
    float GetMax() const {return Max;}
    float GetAverage() const {return 0.5f * (Min + Max);}
    float GetMinSum(float v) const {return v + Min;}
    float GetMaxSum(float v) const {return v + Max;}
    float GetDeltaMinMax() const {return GetMax() - GetMin();}
    bool  IsNearlyZeroDeltaMinMax() const {return FMath::IsNearlyZero(GetDeltaMinMax(), 0.01f);}
    bool  IsValueInRange(float V) const {return FMath::IsWithinInclusive(V, Min, Max);}

public:
    FString ToString() const
    {
        return  "Min: " + FString::SanitizeFloat(Min) + " | Max: " + FString::SanitizeFloat(Max);
    }
};
