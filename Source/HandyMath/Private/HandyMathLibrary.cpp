// Created by Jeremie Boga in 2020


#include "HandyMathLibrary.h"


#include "ConstantsHM.h"
#include "HandyMathArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "NativeLib.h"


float UHM::GetWorldDeltaSeconds(const UObject* WorldContextObject)
{
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    return World ? World->GetDeltaSeconds() : 0.f;
}

float UHM::NegateFloat(const float F)
{
    return -1 * F;
}

float UHM::NegateFloatPure(const float F)
{
    return  NegateFloat(F);
}

float UHM::RoundFloatWithPrecision(const float Val, const int Digits)
{
    if (Digits == 0)
        return FMath::RoundHalfFromZero(Val);
    const int Mul = FMath::Pow(10, Digits);
    return FMath::RoundHalfFromZero(Val * Mul) / Mul; 
}

float UHM::RoundFloatWithPrecisionPure(const float Val, const int Digits)
{
    return RoundFloatWithPrecision(Val, Digits);
}

float UHM::RoundFloatWithPrecisionByEnum(const float Val, const EFloatPrecision E)
{
    return RoundFloatWithPrecision(Val, static_cast<int>(E));
}

float UHM::RoundFloatWithPrecisionByEnumPure(const float Val, const EFloatPrecision E)
{
    return RoundFloatWithPrecisionByEnum(Val, E);
}

float  UHM::FloatIncreaseByWorldDeltaSeconds(const UObject* WorldContextObject, const float F) 
{
    return GetWorldDeltaSeconds(WorldContextObject) +  F;
}

float  UHM::FloatIncreaseByWorldDeltaSecondsPure(const UObject* WorldContextObject, const float F) 
{
    return FloatIncreaseByWorldDeltaSeconds(WorldContextObject, F);
}

float  UHM::FloatDecreaseByWorldDeltaSeconds(const UObject* WorldContextObject, const float F) 
{
    return F - GetWorldDeltaSeconds(WorldContextObject);
}

float  UHM::FloatDecreaseByWorldDeltaSecondsPure(const UObject* WorldContextObject, const float F) 
{
    return FloatDecreaseByWorldDeltaSeconds(WorldContextObject, F);
}

float  UHM::FloatMultiplyByWorldDeltaSeconds(const UObject* WorldContextObject, const float F) 
{
    return GetWorldDeltaSeconds(WorldContextObject) *  F;
}

float UHM::FloatMultiplyByWorldDeltaSecondsPure(const UObject* WorldContextObject, const float F) 
{
    return FloatMultiplyByWorldDeltaSeconds(WorldContextObject, F);
}

float UHM::FloatDivideByWorldDeltaSeconds(const UObject* WorldContextObject, const float F)
{
    const float dt = GetWorldDeltaSeconds(WorldContextObject);
    return dt == 0 ? 0 : F / dt;
}

float UHM::FloatDivideByWorldDeltaSecondsPure(const UObject* WorldContextObject, const float F)
{
    return FloatDivideByWorldDeltaSeconds(WorldContextObject, F);
}

bool UHM::IsFloatInRangeFromRefDeltaAbs(float V, float RefVal, float HalfWidth)
{
    const float Abs = FMath::Abs(HalfWidth);
    const float Min = RefVal - Abs;
    const float Max = RefVal + Abs;
    return FMath::IsWithinInclusive(V, Min, Max);
}

bool UHM::IsFloatInRange(float Val, float Min, float Max)
{
    return UKismetMathLibrary::InRange_FloatFloat(Val, Min, Max);
}

float UHM::GetRandomSign()
{
    return FMath::RandRange(-10,9) > 0 ? 1 : -1;
}

float UHM::GetRandomSignPure()
{
    return  GetRandomSign();
}

float UHM::Sign(const float V)
{
    return V >= 0.0f ? 1.0f : -1.0f;
}

float UHM::SafeDivision(float A, float B)
{
    return Native::SafeDivision(A,B);
}

float UHM::SafeReciprocal(float A)
{
    return SafeDivision(1.0f, A);
}

float UHM::DivInt(float A, float B)
{
    return A/B;
}

int UHM::SafeDivideRoundUp(float A, float B)
{
    return UKismetMathLibrary::FCeil(Native::SafeDivision(A,B));
}

int UHM::SafeDivideRoundDown(float A, float B)
{
    return UKismetMathLibrary::FFloor(Native::SafeDivision(A,B));
}

float UHM::FClampMaxAbsSigned(float V, float MaxAbs)
{
    return Native::FClampMaxAbsSigned(V, MaxAbs);
}

float UHM::FClampZeroOne(float V)
{
    return FMath::Clamp(V, 0.0f, 1.0f);
}

float UHM::FTrimMinAbsSigned(float V, float MinAbs)
{
    return Native::FTrimMinAbsSigned(V, MinAbs);
}

void UHM::SinCosRad(float A, float& Sin, float& Cos)
{
    SinCosDeg(FMath::RadiansToDegrees(A), Sin, Cos);
}

void UHM::SinCosDeg(float A, float& Sin, float& Cos)
{
    Sin = UKismetMathLibrary::DegSin(A);
    Cos = UKismetMathLibrary::DegCos(A);
}

float UHM::SplitFloatsIntWithLeftOver(float Value, int& Integer, float DivStep)
{
    Integer = 0;
    if(FMath::IsNearlyZero(DivStep)) return 0;
    Integer = UKismetMathLibrary::FFloor(Value / DivStep);
    return Value - Integer * DivStep;
}

float UHM::GetCeilLeftover(float Value, float DivStep)
{
    int Integer;
    const float A = SplitFloatsIntWithLeftOver(Value, Integer, DivStep);
    return FMath::IsNearlyZero(A) ? 0.0f : DivStep - A;
}

float UHM::FRandRangePlusMinus(float AbsLimit)
{
    return FMath::FRandRange(-AbsLimit, AbsLimit);
}

void UHM::ScaleTransformLocationAndScale(FTransform& T, float Scale)
{
    T.ScaleTranslation(Scale);
    T = T.GetScaled(Scale);
}

void UHM::PrintToLog(const FString Msg)
{
#if WITH_EDITOR
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg)
#endif
}

bool UHM::FloatBinSearchIntervalOfValue(const TArray<float>& A, float Target, float& ValueMin, float& ValueMax, bool bAllowOverrange)
{
    const int Num = A.Num();
    if(Num > 1)
    {
        const int IndMin = 0;
        const int IndMax = Num - 1;

        const float Min = A[IndMin];
        const float Max = A.Last();
        
        if(Target < Min)
        {
            if(bAllowOverrange)
            {
                ValueMin = Min;
                ValueMax = Min;
                return true;
            }
            return false;
        }
        
        if(Target == Min)
        {
            ValueMin = Min;
            ValueMax = A[IndMin + 1];
            return true;
        }
        
        if(Target >= Max)
        {
            if(bAllowOverrange)
            {
                ValueMin = Max;
                ValueMax = Max;
                return true;
            }
            return false;
        }

        if(Num == 2)
        {
            if(UKismetMathLibrary::InRange_FloatFloat(Target, Min, Max))
            {
                ValueMin = A[IndMin];
                ValueMax = A[IndMax];
                return true;
            }
            return false;
        }

        const int IndMid = Num == 3 ? 1 : IndMax / 2;
        const float Mid = A[IndMid];

        if(Target == Mid)
        {
            ValueMin = Mid;
            ValueMax = A[IndMid + 1];
            return true;
        }

        int IndSliceMin;
        int IndSliceMax;

        if(Target > Mid)
        {
            IndSliceMin = IndMid;
            IndSliceMax = IndMax;
        }
        else
        {
            IndSliceMin = IndMin;
            IndSliceMax = IndMid;
        }
        
        TArray<float> Slice;
        if(UHMA::ArraySlice(A,  Slice, IndSliceMin, IndSliceMax))
        {
            return FloatBinSearchIntervalOfValue(Slice, Target, ValueMin, ValueMax, false);
        }
        return false;
    }
    return false;
}

bool UHM::FloatBinSearch(const TArray<float>& A, float Target, float AbsTolerance, int& Index)
{
    if(A.Find(Target, Index))
    {
        return true;
    }

    if(A.Num() > 0)
    {           
        int FirstInd = 0;
        int LastInd = A.Num() - 1;
        
        while (true)
        {
            const int MidInd = FirstInd + ((LastInd - FirstInd) / 2);
            const float First = A[FirstInd];
            const float Last = A[LastInd];
            const float Mid = A[MidInd];

            if(FMath::Abs(Target - First) <= AbsTolerance)
            {
                Index = FirstInd;
                return true;
            }
            
            if(Target > First)
            {
                return false;
            }

            if(FMath::Abs(Target - Last) <= AbsTolerance)
            {
                Index = LastInd;
                return true;
            }
            
            if(Target < Last)
            {
                return false;
            }

            const int D = LastInd - FirstInd;
            if(D <= 0)
            {
                return  false;
            }
            
            if(Target > Mid)
            {
                LastInd = MidInd;
            }
            else
            {
                FirstInd = MidInd;                
            }
        }
    }
    return false;
}

bool UHM::FloatBinSearchSum(const TArray<float>& A, float TargetSum, int NumSum, float AbsTolerance, int& StartIndex)
{
    const bool B1 = NumSum >0 && TargetSum > 0;
    const bool B2 = A.Num() >= NumSum;

    if(B1 && B2)
    {
        //find  value that is close to the sum itself if any
        int Index;
        if(!FloatBinSearch(A, TargetSum, AbsTolerance, Index)) Index = 0;
            
        const bool HasItemsToSum = A.Num() - Index >= NumSum;
        if(HasItemsToSum)
        {
            for (int i = Index; i < A.Num(); ++i)
            {
                TArray<float> Slice;
                if(UHMA::ArraySlice(A, NumSum, Slice, i))
                {
                    if(IsSumEqualsToTarget(Slice, TargetSum, AbsTolerance))
                    {
                        StartIndex = i;
                        return true;
                    }
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

bool UHM::AreFloatsEqualsWithTolerance(float A, float B, float AbsTolerance)
{
    return FMath::Abs(A - B) <= AbsTolerance;
}

float UHM::GetFloatSum(const TArray<float>& A)
{
    float f = 0;
    for (const float n : A) f += n;
    return f;
}

void UHM::GetMinMaxFloatArray(const TArray<float>& A, float& Min, float& Max)
{
    Native::GetArrayMinMax(A, Min, Max);
}

float UHM::GetMinOrMax(float A, float B, bool bMax)
{
    return bMax ? FMath::Max(A,B) : FMath::Min(A,B);
}

void UHM::MapMinMax(float A, float B, float& Min, float& Max)
{
    if(A < B)
    {
        Min = A;
        Max = B;
    }
    else
    {
        Min = B;
        Max = A;
    }
}

int UHM::GetNumSegmentsFromFloatRange(float Min, float Max, float Delta)
{
    check(!FMath::IsNearlyZero(Delta))
    const int S =  FMath::Abs(FMath::CeilToInt( Max - Min / Delta));
    return  S == 0 ? 1 : S;
}

float UHM::GetFloatValueOnRangeSegment(float Min, float Max, float Delta, int Index)
{
    const int NumSeg = GetNumSegmentsFromFloatRange(Min, Max, Delta);
    if(Index <= 0) return Min;
    if(Index >= NumSeg) return Max;
    return FMath::Clamp(Min + Delta * Index, Min, Max);
}

float UHM::FloatMulInt(float Value, int Times)
{
    return  Times * Value;
}

void UHM::FloatMulIntWithNeg(float& V, float& NegV, float Value, int Times)
{
    V = FloatMulInt(Value, Times);
    NegV = -V;
}

bool UHM::ModifyValueTimePairsByStripTime(TArray<float>& InOutValues, TArray<float>& InOutTimes, float StripTime, float ValueOnStripTime)
{
    const int ValuesNum = InOutValues.Num();
    const int TimesNum = InOutTimes.Num();

    check(ValuesNum == TimesNum)
    if(ValuesNum < 1) return false;

    const bool bInvalidTime = StripTime >= InOutTimes.Last();
    if(bInvalidTime) return false;
    
    TArray<float> Values = {};
    TArray<float> Times  = {};

    Values.Add(ValueOnStripTime);
    Times.Add(StripTime);

    for (int i = 0; i < TimesNum; ++i)
    {
        float Time = InOutTimes[i];
        float Value = InOutValues[i];
        if(Time > StripTime)
        {
            Values.Add(Value);
            Times.Add(Time);
        }
    }

    InOutValues = Values;
    InOutTimes = Times;
    
    return InOutValues.Num() > 0;
}

float UHM::GetValueFromFloatRangeByAlpha(float Min, float Max, float Alpha, bool bSelectFromMin)
{
    Alpha = NormalizeFloat(Alpha);
    const float Delta = Max - Min;
    const float Change = Delta * Alpha;
    return bSelectFromMin ? Min + Change : Max - Change;
}

float UHM::GetValueFromFloatRangeByAlphaFromMin(float Min, float Max, float Alpha)
{
    return GetValueFromFloatRangeByAlpha(Min, Max, Alpha, true);
}

float UHM::GetValueFromFloatRangeBySignedAlpha(float Min, float Max, float Alpha)
{
    Alpha = NormalizeSignedFloat(Alpha);
    const bool bPositiveAlpha = Alpha >= 0.0f;
    const float AbsAlpha = FMath::Abs(Alpha);
    const float Mid = GetValueFromFloatRangeByAlphaFromMin(Min, Max, 0.5f);

    if(bPositiveAlpha) return GetValueFromFloatRangeByAlpha(Mid, Max, AbsAlpha, true);
    return GetValueFromFloatRangeByAlpha(Min, Mid, AbsAlpha, false);
}

void UHM::FloatToIntRange(float Value, int& Min, int& Max)
{
    int _;
    FloatToIntRangeWithClosestValue(Value, Min, Max, _);
}

void UHM::FloatToIntRangeWithClosestValue(float Value, int& Min, int& Max, int& Closest)
{
    const int a = FMath::RoundToZero(Value);
    const int b = FMath::RoundFromZero(Value);

    float fmin;
    float fmax;
    MapMinMax(a, b, fmin, fmax);

    Min = static_cast<int>(fmin);
    Max = static_cast<int>(fmax);

    Closest = static_cast<int>(FGetClosestValue(Value, Min, Max));
}

float UHM::FGetClosestValue(float Value, float A, float B)
{
    float Min;
    float Max;
    MapMinMax(A, B, Min, Max);

    if(Value <= Min) return Min;
    if(Value >= Max) return Max;

    const float Mid = 0.5f * (Max - Min) + Min;
    return Value >= Mid ? Max : Min;
}

float UHM::GetRatioFromPositiveRange(float Value, float Min, float Max)
{
    Value -= Min;
    Max -= Min;
    const float v = Value / Max;
    return FMath::Clamp(v, 0.0f, 1.0f);
}

float UHM::NormalizeFloat(float V)
{
    return FMath::Clamp(V, 0.0f, 1.0f);
}

float UHM::NormalizeSignedFloat(float V)
{
    return FMath::Clamp(V, -1.0f, 1.0f);
}

TArray<FFloatMinMax> UHM::MakeConsequentTimePairsFromArrays(const TArray<float>& MinLocationTimes, const TArray<float>& MaxLocationTimes, float SwitchTime)
{
    TArray<FFloatMinMax> Out;
    const int NumMin = MinLocationTimes.Num();
    const int NumMax = MaxLocationTimes.Num();

    TArray<float> MinLocationTimesSorted;
    TArray<float> MaxLocationTimesSorted;

    constexpr bool bDescending = false;
    UHMA::FloatArraySort(MinLocationTimes, MinLocationTimesSorted, bDescending);
    UHMA::FloatArraySort(MaxLocationTimes, MaxLocationTimesSorted, bDescending);

    int MaxTimeStartIndex = 0;
    for (int i_min = 0; i_min < NumMin; ++i_min)
    {
        for (int j_max = MaxTimeStartIndex; j_max < NumMax; ++j_max)
        {
            const float MinLocationTime = MinLocationTimesSorted[i_min];
            const float MaxLocationTime = MaxLocationTimesSorted[j_max];

            const bool bSwappedMinMaxTime = MinLocationTime > SwitchTime;

            const bool B1 = bSwappedMinMaxTime && (MaxLocationTime <= MinLocationTime);
            const bool B2 = !bSwappedMinMaxTime && (MaxLocationTime >= MinLocationTime);

            if(B1 || B2)
            {   
                float Min = MinLocationTime;
                float Max = MaxLocationTime;
                if(bSwappedMinMaxTime) Native::Swap(Min, Max);
                Out.Add(FFloatMinMax(Min, Max));
                MaxTimeStartIndex = j_max + 1;
                break;
            }
        }
        if(MaxTimeStartIndex == NumMax) break;
    }        
    
    return Out;
}

bool UHM::IsSumEqualsToTarget(const TArray<float>& A, float TargetSum, float AbsTolerance)
{
    return AreFloatsEqualsWithTolerance(TargetSum, GetFloatSum(A), AbsTolerance);
}

FVector UHM::RadSec2Rps(FVector V)
{
    return V * RadToTurn;
}

FVector UHM::RadSec2Rpm(FVector V)
{
    return V * RadSecToRpM;
}

FVector UHM::Rps2RadSec(FVector V)
{
    return V * TurnToRad;
}

FVector UHM::Rpm2RadSec(FVector V)
{
    return V * RpMToRadSec;
}

FVector UHM::Kmph2MSec(FVector V)
{
    return V * KmHourToMSec;
}

FVector UHM::Kmph2CMSec(FVector V)
{
    return V * KmHourToCmSec;
}

FVector UHM::MSec2Kmph(FVector V)
{
    return V * MSecToKmHour;
}

FVector UHM::CMSec2Kmph(FVector V)
{
    return V * CmSecToKmHour;
}

FVector UHM::AngVelocityDegToRad(FVector V)
{
    const float Rad = FMath::DegreesToRadians(V.Size());
    return Rad * V.GetSafeNormal();
}

float UHM::FRadSec2Rps(float V)
{
    return  V * RadToTurn;
}

float UHM::FRadSec2Rpm(float V)
{
    return V * RadSecToRpM;
}

float UHM::FRps2RadSec(float V)
{
    return V * TurnToRad;
}

float UHM::FRpm2RadSec(float V)
{
    return  V * RpMToRadSec;
}

float UHM::FKmph2MSec(float V)
{
    return V * KmHourToMSec;
}

float UHM::FKmph2CMSec(float V)
{
    return V * KmHourToCmSec;
}

float UHM::FMSec2Kmph(float V)
{
 return V * MSecToKmHour;   
}

float UHM::FCMSec2Kmph(float V)
{
    return V * CmSecToKmHour;
}

float UHM::FCM2M(float V)
{
    return V * CmToM;
}
