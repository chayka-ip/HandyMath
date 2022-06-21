// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandyMathArrayLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HANDYMATH_API UHMA : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category="Handy Math Library Array Pure")
	static void FloatArraySort(const TArray<float>& A, TArray<float>& OutArray, bool bDescending);

	UFUNCTION(BlueprintCallable, Category="Handy Math Array Library")
    static void FloatArrayToString(const TArray<float> &A, FString &S);
	UFUNCTION(BlueprintCallable, Category="Handy Math Array Library")
	static void IntArrayToString(const TArray<int> &A, FString &S);

	static bool ArraySlice(const TArray<float>& A, int NumToSlice, TArray<float> &Out, int StartFrom=0);
	static bool ArraySlice(const TArray<float>& A,  TArray<float> &Out, int StartInd, int EndInd);
	static void ArrayReverse(TArray<float>& A);

	static void FloatArrayRemoveItems(TArray<float>& A, const TArray<float>& ItemsToRemove);
	static void IntArrayRemoveItems(TArray<int>& A, const TArray<int>& ItemsToRemove);
	
	UFUNCTION(BlueprintCallable, Category="Handy Math Array Library")
	static void FloatArrayRemoveItemsBP(const TArray<float>& A, const TArray<float>& ItemsToRemove, TArray<float>& OutArray);
	UFUNCTION(BlueprintCallable, Category="Handy Math Array Library")
	static void IntArrayRemoveItemsBP(const TArray<int>& A, const TArray<int>& ItemsToRemove, TArray<int>& OutArray);
	
	static void FloatArraySort(TArray<float>& A, bool bDescending);
	static TArray<float> FloatArrayCopy(const TArray<float>& A) {return A;}

	// Array should be sorted min->max; for every item removes all that is greater than val+tolerance
	static void FloatArrayReduce(TArray<float>& A, float AbsTolerance);

	UFUNCTION(BlueprintCallable, Category="Handy Math Library Pure")
    static void FloatArrayReduceBP(const TArray<float>& A, float AbsTolerance, TArray<float>& Out);

	UFUNCTION(BlueprintCallable)
	static void IntArrayGetMinMax(const TArray<int> A, int& Min, int& Max);

	static TArray<float> MakeFloatArrayFromRange(float MinVal, float MaxVal, float Delta, bool bIncludeMin = true, bool bIncludeMax=true);
	
	// Ascending sort with indices sequence from original input
	UFUNCTION(BlueprintCallable)
	static TArray<float> SortFloatArrayWithIndicesTracking(const TArray<float>& Array, TArray<int>& Indices);

	static float FloatArraySelectClosestValue(float Value, const TArray<float>& Array, int& OutIndex);
	static TArray<int> FloatArrayToIntArrayStaticCast(const TArray<float>& A);
};
