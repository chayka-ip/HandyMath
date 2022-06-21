// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyMathCurveLibrary.h"
#include "HandyMathLibrary.h"

FRuntimeFloatCurve UHMC::MakeRuntimeFloatCurve(const TArray<float>& Values, const TArray<float>& Times)
{
    FRuntimeFloatCurve Curve;
    const auto C = Curve.GetRichCurve();
    
    const int ValueNum = Values.Num();
    const int TimeNum = Times.Num();
    const int N = FMath::Min(ValueNum, TimeNum);
    
    for (int i = 0; i < N; ++i)
    {
        C->AddKey(Times[i], Values[i]);
    }

    return Curve;
}

void UHMC::FillCurveFromTimeRangeAndSetValues(FRuntimeFloatCurve& Curve, float MinTime, float MaxTime, float TimeDelta, bool bResetKeys)
{
    check(MinTime < MaxTime && TimeDelta > 0)
    const auto CurvePtr = Curve.GetRichCurve();
    if(bResetKeys) CurvePtr->Reset();

    auto CurrentValue = MinTime;
    while (true)
    {
        bool bReturn = false;
        if(CurrentValue >= MaxTime)
        {
            CurrentValue = MaxTime;
            bReturn = true;
        }
        CurvePtr->AddKey(CurrentValue, CurrentValue);
        
        if(bReturn) return;
        CurrentValue += TimeDelta;
    }
}

TArray<float> UHMC::TimeArrayFromKeyArray(const TArray<FFloatKeyTime>& Data)
{
    TArray<float> Out;
    for (auto Item : Data)
    {
        Out.Add(Item.Time);
    }
    return Out;
}

TArray<float> UHMC::ValueArrayFromKeyArray(const TArray<FFloatKeyTime>& Data)
{
    TArray<float> Out;
    for (auto Item : Data)
    {
        Out.Add(Item.Value);
    }
    return Out;
}

bool UHMC::GetFloatCurveLastKey(const FRuntimeFloatCurve& Curve, FFloatKeyTime& Out)
{
    const auto Ptr = Curve.GetRichCurveConst();
    const auto Index  = Ptr->GetNumKeys() - 1;
    if(Index < 0) return false;
    const auto Key = Ptr->Keys[Index];
    Out = FFloatKeyTime(Key.Time, Key.Value);
    return true;
}

FRuntimeFloatCurve UHMC::GetFloatCurveSlice(const FRuntimeFloatCurve& Curve, int Index, bool bFromStart)
{
    if(Index < 0) return {};
    auto Keys = GetFloatCurveKeys(Curve);
    
    FRuntimeFloatCurve Out;
    const auto CurveRef = Out.GetRichCurve();

    const int StartIndex = bFromStart ? 0 : Index;
    const int LastIndex = bFromStart ? Index : Keys.Num();
    
    for (int i = StartIndex; i < LastIndex; ++i)
    {
        const auto Key = Keys[i];
        CurveRef->AddKey(Key.Time, Key.Value);   
    }
    
    return Out;
}

FRuntimeFloatCurve UHMC::GetFloatCurveSliceFromStartByIndex(const FRuntimeFloatCurve& Curve, int LastIndex)
{
    return GetFloatCurveSlice(Curve, LastIndex, true);
}

FRuntimeFloatCurve UHMC::GetFloatCurveSliceFromEndByIndex(const FRuntimeFloatCurve& Curve, int StartIndex)
{
    return GetFloatCurveSlice(Curve, StartIndex, false);
}

void UHMC::GetFloatCurveValueTimeArrays(const FRuntimeFloatCurve& Curve, TArray<float>& Values, TArray<float>& Times)
{
    for (auto Key : Curve.GetRichCurveConst()->Keys)
    {
        Values.Add(Key.Value);
        Times.Add(Key.Time);
    }
}

TArray<float> UHMC::GetFloatCurveTimeArray(const FRuntimeFloatCurve& Curve)
{
    TArray<float> T;
    TArray<float> _;
    GetFloatCurveValueTimeArrays(Curve, _, T);
    return T;
}

bool UHMC::GetFloatCurveKeys(const FRuntimeFloatCurve& Curve, TArray<FFloatKeyTime>& Data)
{
    for (const auto Key : Curve.GetRichCurveConst()->Keys)
    {
        FFloatKeyTime Item = FFloatKeyTime(Key.Time,Key.Value);
        Data.Add(Item);
    }
    return Data.Num() > 0;
}

TArray<FFloatKeyTime> UHMC::GetFloatCurveKeys(const FRuntimeFloatCurve& Curve)
{
    TArray<FFloatKeyTime> Keys;
    GetFloatCurveKeys(Curve, Keys);
    return Keys;
}

bool UHMC::GetFloatCurveValueTimeArrays(const FRuntimeFloatCurve& Curve, TArray<float>& Values, TArray<float>& Times, float StripTime)
{
    GetFloatCurveValueTimeArrays(Curve, Values, Times);
    const float StartTimeValue = Curve.GetRichCurveConst()->Eval(StripTime);
    return  UHM::ModifyValueTimePairsByStripTime(Values, Times, StripTime, StartTimeValue);
}

void UHMC::FloatCurveInsertKeyToEnd(FRuntimeFloatCurve& Curve, float Value, float Time)
{
    const auto curve = Curve.GetRichCurve();
    const int32 Index = curve->GetNumKeys();
    curve->Keys.Insert(FRichCurveKey(Time, Value), Index);
}

bool UHMC::GetCurveNthTimeWhenValueEquals(const FRuntimeFloatCurve& Curve, float Value, float& OutTime, int Index, float StartTime, float Tolerance)
{
    TArray<float> Times;
    if(GetCurveTimesWhenValueEquals(Curve, Value, Times, StartTime, Tolerance))
    {
        if(Times.Num() > Index)
        {
            OutTime = Times[Index];
            return true;
        }
    }
    return false;
}

bool UHMC::GetCurveFirstTimeWhenValueEquals(const FRuntimeFloatCurve& Curve, float Value, float& OutTime, float StartTime, float Tolerance)
{
    return GetCurveNthTimeWhenValueEquals(Curve, Value, OutTime, 0, StartTime, Tolerance);
}

bool UHMC::GetCurveLastTimeWhenValueEquals(const FRuntimeFloatCurve& Curve, float Value, float& OutTime, float StartTime, float Tolerance)
{
    TArray<float> Times;
    if(GetCurveTimesWhenValueEquals(Curve, Value, Times, StartTime, Tolerance))
    {
        OutTime = Times.Last();
        return true;
    }
    return false;
}

bool UHMC::GetCurveTimesWhenValueEquals(const FRuntimeFloatCurve& Curve, float Value, TArray<float>& OutTimes, float StartTime, float Tolerance)
{
    const auto RefCurve = Curve.GetRichCurveConst();
    
    if(!RefCurve->HasAnyData()) return false;

    TArray<float> Values;
    TArray<float> Times;
    const bool HasKeys = GetFloatCurveValueTimeArrays(Curve, Values, Times, StartTime);
    if(!HasKeys) return false;

    float MinValue,MaxValue;
    UHM::GetMinMaxFloatArray(Values, MinValue, MaxValue);
    
    if(UHM::IsFloatInRange(Value, MinValue - Tolerance, MaxValue + Tolerance))
    {
        const int NumKeys = Values.Num();
        if(NumKeys == 1)
        {
            if(UHM::AreFloatsEqualsWithTolerance(Values[0], Value, Tolerance))
            {
                OutTimes.Add(Times[0]);
            }
        }
        else
        {
            const int NumIter = NumKeys - 1;
            for (int i = 0; i < NumIter; ++i)
            {
                const int FirstKey = i;
                const int SecondKey = i + 1;
                
                const float V0 = Values[FirstKey];
                const float V1 = Values[SecondKey];

                const bool bNearlyEqual = FMath::IsNearlyEqual(V0, V1, Tolerance * 0.5f);
                if(bNearlyEqual)
                {
                    if(UHM::AreFloatsEqualsWithTolerance(V0, Value, Tolerance))
                    {
                        float Time = Times[FirstKey];
                        OutTimes.Add(Time);
                    }
                }
                
                float Min, Max;
                UHM::MapMinMax(V0, V1, Min, Max);
                
                if(UHM::IsFloatInRange(Value, Min, Max))
                {
                    const float Delta = Value - V0;
                    const float Interval = V1 - V0;
                    const float R = FMath::Abs(Delta / Interval);

                    const float T0 = Times[FirstKey];
                    const float T1 = Times[SecondKey];

                    const float TimeInterval = T1 - T0;
                    const float TimeDelta = TimeInterval * R;
                    
                    float Time = T0 + TimeDelta;
                    OutTimes.Add(Time);
                }
            }
        }
    }
    return OutTimes.Num() > 0;
}

float UHMC::GetCurveTimeFromRatio(const FRuntimeFloatCurve& Curve, float Ratio)
{
    float MinTime, MaxTime;
    Curve.GetRichCurveConst()->GetTimeRange(MinTime, MaxTime);
    Ratio = FMath::Clamp(Ratio, 0.0f, 1.0f);
    const float Delta = MaxTime - MinTime;
    return MinTime + Delta * Ratio;
}

bool UHMC::GetCurveMinMaxTime(const FRuntimeFloatCurve& Curve, float& MinTime, float& MaxTime)
{
    auto Keys = Curve.GetRichCurveConst()->Keys;
    if(Keys.Num() > 0)
    {
        MinTime = Keys[0].Time;
        MaxTime = Keys.Last().Time;
        return true;
    }
    return false;
}

float UHMC::GetCurveMinTime(const FRuntimeFloatCurve& Curve)
{
    float Min = 0.0f;
    float Max = 0.0f;
    GetCurveMinMaxTime(Curve, Min, Max);
    return Min;
}

float UHMC::GetCurveMaxTime(const FRuntimeFloatCurve& Curve)
{
    float Min = 0.0f;
    float Max = 0.0f;
    GetCurveMinMaxTime(Curve, Min, Max);
    return Max;
}

bool UHMC::GetTimeAtKeyIndex(const FRuntimeFloatCurve& Curve, int Index, float& OutTime)
{
    auto T = GetFloatCurveTimeArray(Curve);
    if(Index < T.Num())
    {
        OutTime = T[Index];
        return true;
    }
    return false;
}

bool UHMC::GetTimeBetweenIndices(const FRuntimeFloatCurve& Curve, int StartIndex, int EndIndex, float Alpha, float& OutTime)
{
    float StartTime;
    float EndTime;
    const bool bStart = GetTimeAtKeyIndex(Curve, StartIndex, StartTime);
    const bool bEnd = GetTimeAtKeyIndex(Curve, EndIndex, EndTime);

    if(bStart && bEnd)
    {
        OutTime = UHM::GetValueFromFloatRangeByAlphaFromMin(StartTime, EndTime, Alpha);
        return true;
    }
    
    return false;
}

bool UHMC::GetCurveNearestKeys(const FRuntimeFloatCurve& Curve, float SearchTime, FFloatKeyTime& MinKeyData, FFloatKeyTime& MaxKeyData)
{
    const auto CurvePtr = Curve.GetRichCurveConst();
    const auto Keys = CurvePtr->Keys;
    const int NumKeys = Keys.Num();
    if(NumKeys > 0)
    {
        TArray<FFloatKeyTime> KeyData;
        GetFloatCurveKeys(Curve, KeyData);

        float TimeRangeMin;
        float TimeRangeMax;
        CurvePtr->GetTimeRange(TimeRangeMin, TimeRangeMax);

        const bool bReturnFirst = SearchTime <= TimeRangeMin;
        const bool bReturnLast = NumKeys == 1 || SearchTime >= TimeRangeMax;
        
        if(bReturnFirst)
        {
            MinKeyData = KeyData[0];
            MaxKeyData = KeyData[0];
            return true;
        }
        
        if(bReturnLast)
        {
            MinKeyData = KeyData.Last();
            MaxKeyData = KeyData.Last();
            return true;
        }

        for (int i = 0; i < NumKeys; ++i)
        {
            const auto KeyPtr = &KeyData[i];
            if(KeyPtr->Time >= SearchTime)
            {
                const auto CurrentKey = FFloatKeyTime(KeyPtr->Time, KeyPtr->Value);
                MaxKeyData = CurrentKey;

                if(i == 0)
                {
                    MinKeyData = CurrentKey;
                }
                else
                {
                    const auto PrevKeyPtr = &Keys[i - 1];
                    MinKeyData = FFloatKeyTime(PrevKeyPtr->Time, PrevKeyPtr->Value);
                }
                return true;
            }
        }
    }
    return false;
}

void UHMC::GetFloatCurveValueRange(const FRuntimeFloatCurve& Curve, float& Min, float& Max)
{
    Curve.GetRichCurveConst()->GetValueRange(Min, Max);
}

float UHMC::GetFloatCurveMinOrMaxValue(const FRuntimeFloatCurve& Curve, bool bMin)
{
    float Min, Max;
    GetFloatCurveValueRange(Curve, Min, Max);
    return bMin ? Min : Max;
}

float UHMC::GetFloatCurveMinValue(const FRuntimeFloatCurve& Curve)
{
    return GetFloatCurveMinOrMaxValue(Curve, true);
}

float UHMC::GetFloatCurveMaxValue(const FRuntimeFloatCurve& Curve)
{
    return GetFloatCurveMinOrMaxValue(Curve, false);
}

bool UHMC::GetAllValuesAfterTime(const FRuntimeFloatCurve& Curve, float Time, bool bIncludeFirstKeyBeforeTime, TArray<FFloatKeyTime>& OutKeys)
{
    FFloatKeyTime MinKey;
    FFloatKeyTime MaxKey;
    const bool bKeys = GetCurveNearestKeys(Curve, Time, MinKey, MaxKey);
    if(bKeys)
    {
        if(bIncludeFirstKeyBeforeTime) OutKeys.Add(MinKey);

        TArray<FFloatKeyTime> AllKeys;
        GetFloatCurveKeys(Curve, AllKeys);

        check(AllKeys.Contains(MinKey))
        const int MinKeyIndex = AllKeys.IndexOfByKey(MinKey);
        if(AllKeys.Last() != MinKey)
        {
            for (int i = MinKeyIndex + 1; i < AllKeys.Num(); ++i)
            {
                OutKeys.Add(AllKeys[i]);
            }
        }
        
    }
    return OutKeys.Num() > 0;
}
