#pragma once

#include "CoreMinimal.h"
#include "EnumsHM.h"
#include "FloatWrap.generated.h"


USTRUCT()
struct FFloatWrap
{
    GENERATED_BODY()
    
    UPROPERTY()
    float Value = 0.0;
    
public:
    bool HasLowerValue(float Ref, bool bAllowEqual=true, float Tolerance=0.5f) const
    {
        const float S = Ref + Tolerance;
        return bAllowEqual ? Value <= S : Value < S;
    }
    bool HasNearlyEqualValue(float Ref, float Tolerance=0.5f) const
    {
        return  FMath::IsNearlyEqual(Ref, Value, Tolerance);
    }
    bool HasGreaterValue(float Ref,  bool bAllowEqual=true, float Tolerance=0.5f) const
    {
        const float S = Ref - Tolerance;
        return bAllowEqual ? Value >= S : Value > S;
    }
    bool IsAcceptable(float Ref, EFST_FloatSearchType SearchType) const
    {
        if(SearchType == EFST_Less) return HasLowerValue(Ref);
        if(SearchType == EFST_Equal) return HasNearlyEqualValue(Ref);
        if(SearchType == EFST_Greater) return HasGreaterValue(Ref);
        return false;
    }
};
