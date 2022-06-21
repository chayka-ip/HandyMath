// Created by Jeremie Boga in 2020

#pragma once

#include "CoreMinimal.h"
#include "EnumsHM.h"
#include "HMStructs/FloatMinMax.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandyMathLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HANDYMATH_API UHM : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	static float GetWorldDeltaSeconds(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category="Handy Math Library")
	static float NegateFloat(float F);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static float NegateFloatPure(float F);

	UFUNCTION(BlueprintCallable, Category="Handy Math Library")
	static float RoundFloatWithPrecision(float Val, int Digits);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static float RoundFloatWithPrecisionPure(float Val, int Digits);

	UFUNCTION(BlueprintCallable, Category="Handy Math Library")
	static float RoundFloatWithPrecisionByEnum(float Val, EFloatPrecision E);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static float RoundFloatWithPrecisionByEnumPure(float Val, EFloatPrecision E);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"),  Category="Handy Math Library")
	static float FloatIncreaseByWorldDeltaSeconds(const UObject* WorldContextObject, float F);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category="Handy Math Library Pure")
	static float FloatIncreaseByWorldDeltaSecondsPure(const UObject* WorldContextObject, float F);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"),  Category="Handy Math Library")
	static float FloatDecreaseByWorldDeltaSeconds(const UObject* WorldContextObject, float F);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category="Handy Math Library Pure")
	static float FloatDecreaseByWorldDeltaSecondsPure(const UObject* WorldContextObject, float F);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"),  Category="Handy Math Library")
	static float FloatMultiplyByWorldDeltaSeconds(const UObject* WorldContextObject, float F);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category="Handy Math Library Pure")
	static float FloatMultiplyByWorldDeltaSecondsPure(const UObject* WorldContextObject, float F);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category="Handy Math Library")
	static float FloatDivideByWorldDeltaSeconds(const UObject* WorldContextObject, float F);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category="Handy Math Library Pure")
	static float FloatDivideByWorldDeltaSecondsPure(const UObject* WorldContextObject, float F);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static bool IsFloatInRangeFromRefDeltaAbs(float V, float RefVal, float HalfWidth);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static bool IsFloatInRange(float Val, float Min, float Max);
	
	UFUNCTION(BlueprintCallable, Category="Handy Math Library")
	static float GetRandomSign();

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static float GetRandomSignPure();

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static  float Sign(float V);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static float SafeDivision(float A, float B);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static float SafeReciprocal(float A);

	static float DivInt(float A, float B);
	
	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static int SafeDivideRoundUp(float A, float B);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static int SafeDivideRoundDown(float A, float B);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static float FClampMaxAbsSigned(float V, float MaxAbs);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static  float FClampZeroOne(float V);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static float FTrimMinAbsSigned(float V, float MinAbs);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static void SinCosRad(float A, float& Sin, float& Cos);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static void SinCosDeg(float A, float& Sin, float& Cos);
	
	/*
	 * if DivisionStep > Value => Integer = 0
	 * returns leftover
	 */
	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static float SplitFloatsIntWithLeftOver(float Value, int& Integer, float DivStep);

	// how much  should be added to ceil integer number steps
	UFUNCTION(BlueprintPure)
	static float GetCeilLeftover(float Value, float DivStep);

	UFUNCTION(BlueprintPure)
	static float FRandRangePlusMinus(float AbsLimit);
	
	static void ScaleTransformLocationAndScale(FTransform &T, float Scale);

	static void PrintToLog(const FString Msg);

	// array should be sorted by min->max;
	UFUNCTION(BlueprintCallable)
	static bool FloatBinSearchIntervalOfValue(const TArray<float>& A, float Target, float& ValueMin, float& ValueMax, bool bAllowOverrange);
	
	// array should be sorted by max->min
	static bool FloatBinSearch(const TArray<float>& A, float Target, float AbsTolerance, int& Index);
	
	// array should be sorted by max->min
	static bool FloatBinSearchSum(const TArray<float>& A, float TargetSum, int NumSum, float AbsTolerance, int& StartIndex);

	static bool AreFloatsEqualsWithTolerance(float A, float B, float AbsTolerance);
	static bool IsSumEqualsToTarget(const TArray<float>& A, float TargetSum, float AbsTolerance);
	static float GetFloatSum(const TArray<float>& A);

	// todo: move to array library
	static void GetMinMaxFloatArray(const TArray<float>& A, float& Min, float& Max);

	static float GetMinOrMax(float A, float B, bool bMax);
	static void MapMinMax(float A, float B, float& Min, float& Max);

	UFUNCTION(BlueprintPure)
	static int GetNumSegmentsFromFloatRange(float Min, float Max, float Delta);
	UFUNCTION(BlueprintPure)
	static float GetFloatValueOnRangeSegment(float Min, float Max, float Delta, int Index);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static float FloatMulInt(float Value, int Times=1);

	UFUNCTION(BlueprintPure, Category="Handy Math Library Pure")
	static void FloatMulIntWithNeg(float& V, float& NegV, float Value, int Times=1);

	static bool ModifyValueTimePairsByStripTime(TArray<float>& InOutValues, TArray<float>& InOutTimes, float StripTime, float ValueOnStripTime);

	static float GetValueFromFloatRangeByAlpha(float Min, float Max, float Alpha, bool bSelectFromMin);
	
	UFUNCTION(BlueprintPure)
	static float GetValueFromFloatRangeByAlphaFromMin(float Min, float Max, float Alpha);

	UFUNCTION(BlueprintPure)
	static float GetValueFromFloatRangeBySignedAlpha(float Min, float Max, float Alpha);

	UFUNCTION(BlueprintPure)
	static void FloatToIntRange(float Value, int& Min, int& Max);
	
	UFUNCTION(BlueprintPure)
	static void FloatToIntRangeWithClosestValue(float Value, int& Min, int& Max, int& Closest);

	static float FGetClosestValue(float Value, float A, float B);
	
	UFUNCTION(BlueprintPure)
	static  float GetRatioFromPositiveRange(float Value, float Min, float Max);

	static float NormalizeFloat(float V);
	static float NormalizeSignedFloat(float V);

	static TArray<FFloatMinMax> MakeConsequentTimePairsFromArrays(const TArray<float>& MinLocationTimes, const TArray<float>& MaxLocationTimes, float SwitchTime);
public:
	
	UFUNCTION(BlueprintPure)
	static FVector RadSec2Rps(FVector V);
    
	UFUNCTION(BlueprintPure)
	static FVector RadSec2Rpm(FVector V);
    
	UFUNCTION(BlueprintPure)
	static FVector Rps2RadSec(FVector V);
    
	UFUNCTION(BlueprintPure)
	static FVector Rpm2RadSec(FVector V);

	UFUNCTION(BlueprintPure)
	static FVector Kmph2MSec(FVector V);

	UFUNCTION(BlueprintPure)
	static FVector Kmph2CMSec(FVector V);
    
	UFUNCTION(BlueprintPure)
	static FVector MSec2Kmph(FVector V);

	UFUNCTION(BlueprintPure)
	static FVector CMSec2Kmph(FVector V);

	UFUNCTION(BlueprintPure)
	static FVector AngVelocityDegToRad(FVector V);
	
	UFUNCTION(BlueprintPure)
	static float FRadSec2Rps(float V);
    
	UFUNCTION(BlueprintPure)
	static float FRadSec2Rpm(float V);
    
	UFUNCTION(BlueprintPure)
	static float FRps2RadSec(float V);
    
	UFUNCTION(BlueprintPure)
	static float FRpm2RadSec(float V);

	UFUNCTION(BlueprintPure)
	static float FKmph2MSec(float V);

	UFUNCTION(BlueprintPure)
	static float FKmph2CMSec(float V);
    
	UFUNCTION(BlueprintPure)
	static float FMSec2Kmph(float V);

	UFUNCTION(BlueprintPure)
	static float FCMSec2Kmph(float V);

	UFUNCTION(BlueprintPure)
	static float FCM2M(float V);

};

