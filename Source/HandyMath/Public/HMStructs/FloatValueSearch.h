#pragma once

#include "CoreMinimal.h"
#include "EnumsHM.h"
#include "FloatValueSearch.generated.h"

USTRUCT(BlueprintType)
struct FValueSearchData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    float Ref = 0.0f;
    UPROPERTY(BlueprintReadWrite)
    TEnumAsByte<EVST_VectorValueType> ValueType = EVST_Magnitude;
    UPROPERTY(BlueprintReadWrite)
    TEnumAsByte<EFST_FloatSearchType> SearchType = EFST_Equal;
    UPROPERTY(BlueprintReadWrite)
    TEnumAsByte<ECPVT_VelocityType> Velocity = ECPVT_Linear;

public:
    void Init(float ref, EVST_VectorValueType valueType, EFST_FloatSearchType searchType, ECPVT_VelocityType velocityType)
    {
        Ref = ref;
        ValueType = valueType;
        SearchType = searchType;
        Velocity = velocityType;
    }
public:
    EVST_VectorValueType GetValueType() const {return ValueType;}
    EFST_FloatSearchType GetSearchType() const {return SearchType;}
    ECPVT_VelocityType GetVelocityType() const {return Velocity;}
};