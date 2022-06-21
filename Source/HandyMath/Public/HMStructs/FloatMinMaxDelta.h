#pragma once

#include "CoreMinimal.h"
#include "HandyMathArrayLibrary.h"
#include "FloatMinMax.h"
#include "FloatMinMaxDelta.generated.h"

USTRUCT(BlueprintType)
struct FFloatMinMaxDelta : public FFloatMinMax
{
    GENERATED_BODY()

    FFloatMinMaxDelta(){}
    FFloatMinMaxDelta(float min, float max, float delta)
    {
        SetMinMaxDelta(min, max, delta);
    }
    
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Delta = 0.0f;

public:
    void SetDelta(float V){Delta = V;}
    void SetMinMaxDelta(float min, float max, float delta)
    {
        SetMinMax(min, max);
        SetDelta(delta);
    }
public:
    float GetDelta() const {return Delta;}
    float GetHalfDelta() const {return 0.5f * Delta;}
    TArray<float> GetValueArray(bool bIncludeMin=true, bool bIncludeMax=true) const
    {
        return UHMA::MakeFloatArrayFromRange(Min, Max, Delta, bIncludeMin, bIncludeMax);
    }
    TArray<float> GetValueArrayFullRange() const {return GetValueArray(true, true);}
    TArray<float> GetValueArrayInnerRange() const {return GetValueArray(false, false);}

};
