// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyMathArrayLibrary.h"

#include "NativeLib.h"

void UHMA::FloatArraySort(const TArray<float>& A, TArray<float>& OutArray, bool bDescending)
{
	OutArray = A;
	FloatArraySort(OutArray, bDescending);
}

void UHMA::FloatArrayToString(const TArray<float>& A, FString& S)
{
	S = "[";
	for (const float Element : A)
	{
		S += FString::SanitizeFloat(Element) + ", ";
	}
	S += "]";
}

void UHMA::IntArrayToString(const TArray<int>& A, FString& S)
{
    S = "[";
    for (const float Element : A)
    {
        S += FString::FromInt(Element) + ", ";
    }
    S += "]";
}

bool UHMA::ArraySlice(const TArray<float>& A, int NumToSlice, TArray<float>& Out, int StartFrom)
{
    if(NumToSlice <= A.Num() - StartFrom)
    {
        for (int i = StartFrom; i < A.Num(); ++i)
        {
            Out.Add(A[i]);
        }
        return true;
    }
    return false;
}

bool UHMA::ArraySlice(const TArray<float>& A, TArray<float>& Out, int StartInd, int EndInd)
{
    const int MaxInd = A.Num() - 1;
    if((StartInd < EndInd) && (StartInd < MaxInd))
    {
        if (EndInd > MaxInd)
        {
            EndInd = MaxInd;
        }
        for (int i = StartInd; i < EndInd + 1; ++i)
        {
            Out.Add(A[i]);
        }
        return true;
    }
    return false;
}

void UHMA::ArrayReverse(TArray<float>& A)
{
    TArray<float> B;
    for (int i = A.Num(); i > 0; ++i)
    {
        B.Add(A[i-1]);
    }
    A = B;
}

void UHMA::FloatArrayRemoveItems(TArray<float>& A, const TArray<float>& ItemsToRemove)
{
    Native::ArrayRemoveItems(A, ItemsToRemove);
}

void UHMA::IntArrayRemoveItems(TArray<int>& A, const TArray<int>& ItemsToRemove)
{
    Native::ArrayRemoveItems(A, ItemsToRemove);
}

void UHMA::FloatArrayRemoveItemsBP(const TArray<float>& A, const TArray<float>& ItemsToRemove, TArray<float>& OutArray)
{
    OutArray = A;
    FloatArrayRemoveItems(OutArray, ItemsToRemove);
}

void UHMA::IntArrayRemoveItemsBP(const TArray<int>& A, const TArray<int>& ItemsToRemove, TArray<int>& OutArray)
{
    OutArray = A;
    IntArrayRemoveItems(OutArray, ItemsToRemove);
}

void UHMA::FloatArraySort(TArray<float>& A, bool bDescending)
{
    if(bDescending)
    {
        A.Sort([](const float& f1, const float& f2) {return  f1 >  f2;});
        return;
    }
    A.Sort([](const float& f1, const float& f2) {return  f1 <  f2;});
}

void UHMA::FloatArrayReduce(TArray<float>& A, float AbsTolerance)
{
    TArray<float> Copy = FloatArrayCopy(A);
    A.Empty();

    const int Num = Copy.Num();

    if(Num > 2)
    {
        if(Copy[0] == Copy.Last())
        {
            A = {Copy[0]};
            return;
        }
    }
    
    for (int i = 0; i < Num; ++i)
    {
        const float ValRef = Copy[i];
        A.Add(ValRef);

        bool bRet = true;
        
        for (int j = i + 1; j < Num; ++j)
        {
            const float Val = Copy[j];
            const float ValMax = ValRef + AbsTolerance;
            if(Val > ValMax)
            {
                i = j - 1;
                bRet = false;
                break;
            }                    
        }
        if(bRet)
        {
            return;
        }
    }
}

void UHMA::FloatArrayReduceBP(const TArray<float>& A, float AbsTolerance, TArray<float>& Out)
{
    Out = A;
    FloatArrayReduce(Out, AbsTolerance);
}

void UHMA::IntArrayGetMinMax(const TArray<int> A, int& Min, int& Max)
{
    Native::GetArrayMinMax(A, Min, Max);
}

TArray<float> UHMA::MakeFloatArrayFromRange(float MinVal, float MaxVal, float Delta, bool bIncludeMin, bool bIncludeMax)
{
    check((MinVal < MaxVal) && (Delta > 0.0f))
    TArray<float> Out;
    
    float CurrentValue = MinVal;
    if(!bIncludeMin) CurrentValue += Delta;
    
    while (true)
    {
        bool bReturn = false;
        if(CurrentValue >= MaxVal)
        {
            CurrentValue = MaxVal;
            bReturn = true;
            if(!bIncludeMax) return Out;
        }

        Out.Add(CurrentValue);
        
        if(bReturn) return Out;
        CurrentValue += Delta;
    }
}

TArray<float> UHMA::SortFloatArrayWithIndicesTracking(const TArray<float>& Array, TArray<int>& Indices)
{
    TArray<float> OutArray;
    FloatArraySort(Array, OutArray, false);

    const int NumElem = OutArray.Num(); 
    
    for (int i = 0; i < NumElem; ++i)
    {
        const float Value = OutArray[i];
        for (int j = 0; j < NumElem; ++j)
        {
            const bool bEqual = Value == Array[j];
            const bool bNewIndex = !Indices.Contains(j);
            if(bEqual && bNewIndex)
            {
                Indices.Add(j);
                break;
            }
        }
    }
    
    check(Indices.Num() == NumElem);
    return OutArray;
}

float UHMA::FloatArraySelectClosestValue(float Value, const TArray<float>& Array, int& OutIndex)
{
    const int Count = Array.Num();
    check(Count > 0)

    OutIndex = 0;
    float OutValue = Array[OutIndex];

    for (int i = 0; i < Count; ++i)
    {
        const float Item = Array[i];
        const bool B = FMath::Abs(Value - Item) < FMath::Abs(Value - OutValue);
        if(B)
        {
            OutValue = Item;
            OutIndex = i;
        }
    }
    return OutValue;
}

TArray<int> UHMA::FloatArrayToIntArrayStaticCast(const TArray<float>& A)
{
    TArray<int> Out;
    for (const auto Value : A) Out.Add(static_cast<int>(Value));
    return Out;
}


