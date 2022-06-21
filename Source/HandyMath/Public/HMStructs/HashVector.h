#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "HMStructs/IntMinMax.h"
#include "HashVector.generated.h"

USTRUCT(BlueprintType)
struct HANDYMATH_API FHashVector
{
    GENERATED_BODY()

public:

    // value is integer key for passed search value
    UPROPERTY()
    FRuntimeFloatCurve KeyCurve;
    
public:
    bool HasKeys() const {return KeyCurve.GetRichCurveConst()->GetNumKeys() > 0;}
    void Reset();
    void AddKey(float SearchKey, int Value);
    void MakeCurveFromValues(const TArray<float>& Values);
    float GetFirstKeyTime() const;
    
public:
    bool GetHashValues(float Key, int& LeftValue, int& RightValue, int& ClosestKey) const;
    // min max are basically left and right values
    FIntMinMax GetHashValues(float Key, int& ClosestKey) const;
    FIntMinMax GetHashValues(float Key) const;
    int GetClosestHashValue(float Key) const;
    float GetSearchValueFromHash(int Hash) const;
    TArray<int> GetHashesAfterValue(float SearchValue) const;
    TArray<int> GetHashesAfterValue(float SearchValue, bool bIncludeFirstKeyBeforeTime) const;
};