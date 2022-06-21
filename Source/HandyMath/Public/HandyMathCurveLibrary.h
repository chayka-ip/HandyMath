// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandyMathCurveLibrary.generated.h"

USTRUCT()
struct FFloatKeyTime
{
    GENERATED_BODY()
    
public:
    FFloatKeyTime(){}
    FFloatKeyTime(float time, float value)
    {
        Time = time;
        Value = value;
    }

    bool operator != (const FFloatKeyTime& Other) const
    {
        return !Equals(Other);
    }
    
    bool operator == (const FFloatKeyTime& Other) const
    {
        return Equals(Other);
    }
    
    bool Equals(const FFloatKeyTime& Other) const
    {
        const bool B1 = Time == Other.Time;
        const bool B2 = Value == Other.Value;
        return B1 && B2;
    }
public:
    
    float Time = 0.0f;
    float Value = 0.0f;
};
/**
 * 
 */
UCLASS()
class HANDYMATH_API UHMC : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    static FRuntimeFloatCurve MakeRuntimeFloatCurve(const TArray<float>& Values, const TArray<float>& Times);
    static void FillCurveFromTimeRangeAndSetValues(FRuntimeFloatCurve& Curve, float MinTime, float MaxTime, float TimeDelta, bool bResetKeys);
    static TArray<float> TimeArrayFromKeyArray(const TArray<FFloatKeyTime>& Data);
    static TArray<float> ValueArrayFromKeyArray(const TArray<FFloatKeyTime>& Data);
    static bool GetFloatCurveLastKey(const FRuntimeFloatCurve& Curve, FFloatKeyTime& Out);
    
    static FRuntimeFloatCurve GetFloatCurveSlice(const FRuntimeFloatCurve& Curve, int Index, bool bFromStart);
    static FRuntimeFloatCurve GetFloatCurveSliceFromStartByIndex(const FRuntimeFloatCurve& Curve, int LastIndex);
    static FRuntimeFloatCurve GetFloatCurveSliceFromEndByIndex(const FRuntimeFloatCurve& Curve, int StartIndex);
    
public:
    static void GetFloatCurveValueTimeArrays(const FRuntimeFloatCurve& Curve, TArray<float>& Values, TArray<float>& Times);
    static TArray<float> GetFloatCurveTimeArray(const FRuntimeFloatCurve& Curve);
    static bool GetFloatCurveKeys(const FRuntimeFloatCurve& Curve, TArray<FFloatKeyTime>& Data);
    static TArray<FFloatKeyTime> GetFloatCurveKeys(const FRuntimeFloatCurve& Curve);
    static bool GetFloatCurveValueTimeArrays(const FRuntimeFloatCurve& Curve, TArray<float>& Values, TArray<float>& Times, float StripTime);
    static void FloatCurveInsertKeyToEnd(FRuntimeFloatCurve& Curve, float Value, float Time);
    

    UFUNCTION(BlueprintPure)
    static bool GetCurveNthTimeWhenValueEquals(const FRuntimeFloatCurve& Curve, float Value, float& OutTime, int Index=0, float StartTime=0.0f, float Tolerance=0.01f);
    UFUNCTION(BlueprintPure)
    static bool GetCurveFirstTimeWhenValueEquals(const FRuntimeFloatCurve& Curve, float Value, float& OutTime, float StartTime=0.0f, float Tolerance=0.01f);
    UFUNCTION(BlueprintPure)
    static bool GetCurveLastTimeWhenValueEquals(const FRuntimeFloatCurve& Curve, float Value, float& OutTime, float StartTime = 0.0f, float Tolerance = 0.01f);
    UFUNCTION(BlueprintPure)
    static bool GetCurveTimesWhenValueEquals(const FRuntimeFloatCurve& Curve, float Value, TArray<float>& OutTimes, float StartTime=0.0f, float Tolerance=0.01f);
    static float GetCurveTimeFromRatio(const FRuntimeFloatCurve& Curve, float Ratio);

    UFUNCTION(BlueprintPure)
    static bool GetCurveMinMaxTime(const FRuntimeFloatCurve& Curve, float& MinTime, float& MaxTime);
    static float GetCurveMinTime(const FRuntimeFloatCurve& Curve);
    static float GetCurveMaxTime(const FRuntimeFloatCurve& Curve);
    static bool GetTimeAtKeyIndex(const FRuntimeFloatCurve& Curve, int Index, float& OutTime);
    static bool GetTimeBetweenIndices(const FRuntimeFloatCurve& Curve, int StartIndex, int EndIndex, float Alpha, float& OutTime);
    static bool GetCurveNearestKeys(const FRuntimeFloatCurve& Curve, float SearchTime, FFloatKeyTime& MinKeyData, FFloatKeyTime& MaxKeyData);
    
    static void  GetFloatCurveValueRange(const FRuntimeFloatCurve& Curve, float& Min, float& Max);
    static float GetFloatCurveMinOrMaxValue(const FRuntimeFloatCurve& Curve, bool bMin);
    static float GetFloatCurveMinValue(const FRuntimeFloatCurve& Curve);
    static float GetFloatCurveMaxValue(const FRuntimeFloatCurve& Curve);

    static bool GetAllValuesAfterTime(const FRuntimeFloatCurve& Curve, float Time, bool bIncludeFirstKeyBeforeTime, TArray<FFloatKeyTime>& OutKeys);
};
