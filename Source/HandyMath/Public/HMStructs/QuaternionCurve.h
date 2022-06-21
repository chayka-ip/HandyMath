#pragma once

#include "CoreMinimal.h"
#include "QuaternionCurve.generated.h"

// todo: inherit from vector curve

USTRUCT(BlueprintType)
struct HANDYMATH_API FQuaternionCurve
{
    GENERATED_BODY()
    
public:
    
    UPROPERTY(BlueprintReadWrite)
    FRuntimeFloatCurve X = FRuntimeFloatCurve();
    UPROPERTY(BlueprintReadWrite)
    FRuntimeFloatCurve Y = FRuntimeFloatCurve();
    UPROPERTY(BlueprintReadWrite)
    FRuntimeFloatCurve Z = FRuntimeFloatCurve();
    UPROPERTY(BlueprintReadWrite)
    FRuntimeFloatCurve W = FRuntimeFloatCurve();

public:
    void Reset();
    void UpdateOrAddKey(float Time, const FQuat &Q);
    void InsertKeyToEnd(float Time, const FQuat &Q);
    FQuat GetQuatValue(float Time) const;
    FQuat LastKey() const;

public:
    int GetNumKeys() const {return X.GetRichCurveConst()->GetNumKeys();}
    bool HasKeys() const {return GetNumKeys() > 0;}
    int LastKeyIndex() const {return GetNumKeys() - 1;}
};
