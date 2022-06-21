#pragma once

#include "CoreMinimal.h"
#include "FloatWrap.h"
#include "HandyMathVectorLibrary.h"
#include "DetailedVector.generated.h"

USTRUCT(BlueprintType)
struct HANDYMATH_API FDetailedVector
{
    GENERATED_BODY()
    
public:
    FDetailedVector(){}
    FDetailedVector(const FVector& v) {Initialize(v);}
    
public:

    UPROPERTY()
    FVector V = FVector::ZeroVector;
    UPROPERTY()
    FVector Direction = FVector::ZeroVector;
    UPROPERTY()
    FFloatWrap Magnitude;
    UPROPERTY()
    FFloatWrap Angle_XY;
    UPROPERTY()
    FFloatWrap Angle_XZ;

public:
    void Initialize(float magnitude, float angle_XY, float angle_XZ);
    void Initialize(const FVector& v);

public:
    bool HasAcceptableValue(float Ref, EVST_VectorValueType ValueType, EFST_FloatSearchType SearchType) const;

public:
    bool IsSimilarTo(const FDetailedVector& Other) const;
    
public:
    FVector GetV() const {return V;}
    float GetMagnitude() const {return Magnitude.Value;}
    FVector GetV_XY() const {return UHMV::TrimVectorZ(GetV());}
    float GetDistanceXY() const {return GetV_XY().Size();}
};