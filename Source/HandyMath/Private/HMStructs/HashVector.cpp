#include "HandyMath/Public/HMStructs/HashVector.h"
#include "HandyMathArrayLibrary.h"
#include "HandyMathCurveLibrary.h"
#include "HandyMathLibrary.h"

void FHashVector::Reset()
{
    KeyCurve.GetRichCurve()->Reset();
}

void FHashVector::AddKey(float SearchKey, int Value)
{
    KeyCurve.GetRichCurve()->AddKey(SearchKey, Value);
}

void FHashVector::MakeCurveFromValues(const TArray<float>& Values)
{
    KeyCurve.GetRichCurve()->Reset();
    const int NumKeys = Values.Num();
    for (int i = 0; i < NumKeys; ++i)
    {
        AddKey(Values[i], i);
    }
}

float FHashVector::GetFirstKeyTime() const
{
    return KeyCurve.GetRichCurveConst()->Keys[0].Time;
}

bool FHashVector::GetHashValues(float Key, int& LeftValue, int& RightValue, int& ClosestKey) const
{
    if(!HasKeys()) return false;

    FFloatKeyTime MinTimeKey;
    FFloatKeyTime MaxTimeKey;
    
    const bool bValid = UHMC::GetCurveNearestKeys(KeyCurve, Key, MinTimeKey, MaxTimeKey);
    check(bValid)

    LeftValue = static_cast<int>(MinTimeKey.Value);
    RightValue = static_cast<int>(MaxTimeKey.Value);

    const float ClosestKeyTime = UHM::FGetClosestValue(Key, MinTimeKey.Time, MaxTimeKey.Time);
    ClosestKey = MinTimeKey.Time == ClosestKeyTime ? MinTimeKey.Value : MaxTimeKey.Value;
    
    return true;
}

FIntMinMax FHashVector::GetHashValues(float Key, int& ClosestKey) const
{
    FIntMinMax Out;
    GetHashValues(Key, Out.Min, Out.Max, ClosestKey);
    return Out;
}

FIntMinMax FHashVector::GetHashValues(float Key) const
{
    int _;
    return GetHashValues(Key, _);
}

int FHashVector::GetClosestHashValue(float Key) const
{
    int Out;
    GetHashValues(Key, Out);
    return Out;
}

float FHashVector::GetSearchValueFromHash(int Hash) const
{
    float OutValue;
    const bool bFound = UHMC::GetCurveFirstTimeWhenValueEquals(KeyCurve, Hash, OutValue, GetFirstKeyTime(), 0.05f);
    check(bFound)
    return OutValue;
}

TArray<int> FHashVector::GetHashesAfterValue(float SearchValue) const
{
    return GetHashesAfterValue(SearchValue, true);
}

TArray<int> FHashVector::GetHashesAfterValue(float SearchValue, bool bIncludeFirstKeyBeforeTime) const
{
    TArray<FFloatKeyTime> Keys;
    const bool bKeys = UHMC::GetAllValuesAfterTime(KeyCurve, SearchValue, bIncludeFirstKeyBeforeTime, Keys);
    check(bKeys)
    const auto FValues = UHMC::ValueArrayFromKeyArray(Keys);
    return UHMA::FloatArrayToIntArrayStaticCast(FValues);
}
