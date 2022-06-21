#include "HandyMath/Public/HMStructs/CustomVectorCurve.h"
#include "HandyMathCurveLibrary.h"
#include "HandyMathTrajectoryLibrary.h"

float FCustomVectorCurve::GetTimeFromRatio(float Ratio) const
{
    return UHMC::GetCurveTimeFromRatio(X, Ratio);
}

FVector FCustomVectorCurve::LastKey() const
{
    FFloatKeyTime x;
    FFloatKeyTime y;
    FFloatKeyTime z;
    const bool bx = UHMC::GetFloatCurveLastKey(X,x);
    const bool by = UHMC::GetFloatCurveLastKey(Y,y);
    const bool bz = UHMC::GetFloatCurveLastKey(Z,z );
    return bx && by && bz ? FVector(x.Value, y.Value, z.Value) : FVector::ZeroVector;
}

float FCustomVectorCurve::GetTimeAtKeyIndex(int Index) const
{
    float Time;
    return UHMC::GetTimeAtKeyIndex(X, Index, Time) ? Time : 0.0f;
}

float FCustomVectorCurve::GetTimeBetweenKeyIndices(int StartIndex, int EndIndex, float Alpha) const
{
    float Time;
    return UHMC::GetTimeBetweenIndices(X, StartIndex, EndIndex, Alpha, Time) ? Time : 0.0f;
}

TArray<float> FCustomVectorCurve::GetTimes() const
{
    TArray<float>Times, _;
    UHMC::GetFloatCurveValueTimeArrays(X, _, Times);
    return Times;
}

TArray<FVector> FCustomVectorCurve::GetVectorKeys() const
{
    TArray<FVector> Out;
    TArray<float> Times;
    GetTimesAndValues(Times, Out);
    return Out;
}

TArray<FVector> FCustomVectorCurve::GetVectorsFromTimes(const TArray<float>& Times) const
{
    TArray<FVector> Out;
    for (const auto Time : Times)
    {
        FVector V = GetVectorValue(Time);
        Out.Add(V);
    }
    return Out;
}

void FCustomVectorCurve::GetTimesAndValues(TArray<float>& Times, TArray<FVector>& Values) const
{
    Times = GetTimes();
    for (const auto Time : Times) Values.Add(GetVectorValue(Time));
}

bool FCustomVectorCurve::GetAllVectorsWhereValueEquals(const FRuntimeFloatCurve& Curve, float Value, TArray<FVector>& OutVectors) const
{
    TArray<float> Times;
    bool HasTimes = UHMC::GetCurveTimesWhenValueEquals(Curve, Value, Times);
    OutVectors = GetVectorsFromTimes(Times);
    return OutVectors.Num() > 0; 
}

bool FCustomVectorCurve::GetAllVectorsWhereXEquals(float Value, TArray<FVector>& OutVectors) const
{
    return GetAllVectorsWhereValueEquals(X, Value, OutVectors);
}

FCustomVectorCurve::FCustomVectorCurve(const TArray<FVector>& Vectors, float TimeStep)
{
    for (int i = 0; i < Vectors.Num(); ++i)
    {
        InsertKeyToEnd(TimeStep * i, Vectors[i]);
    }
}

FCustomVectorCurve::FCustomVectorCurve(const TArray<float>& Times, const TArray<FVector> Values)
{
    AddKeys(Times, Values);
}

void FCustomVectorCurve::Reset()
{
    X.GetRichCurve()->Reset();
    Y.GetRichCurve()->Reset();
    Z.GetRichCurve()->Reset();
}

void FCustomVectorCurve::Init(const TArray<float>& Times, const TArray<FVector> Values)
{
    Reset();
    AddKeys(Times, Values);
}

void FCustomVectorCurve::UpdateOrAddKey(float Time, const FVector& V)
{
    X.EditorCurveData.UpdateOrAddKey(Time, V.X, false);
    Y.EditorCurveData.UpdateOrAddKey(Time, V.Y, false);
    Z.EditorCurveData.UpdateOrAddKey(Time, V.Z, false);
}

void FCustomVectorCurve::InsertKeyToEnd(float Time, const FVector& V)
{
    UHMC::FloatCurveInsertKeyToEnd(X, V.X, Time);
    UHMC::FloatCurveInsertKeyToEnd(Y, V.Y, Time);
    UHMC::FloatCurveInsertKeyToEnd(Z, V.Z, Time);
}

void FCustomVectorCurve::AddKeys(const TArray<float>& Times, const TArray<FVector>& Values)
{
    check(Times.Num() <= Values.Num())
    for (int i = 0; i < Times.Num(); ++i)
    {
        InsertKeyToEnd(Times[i], Values[i]);
    }
}

FVector FCustomVectorCurve::GetVectorValue(float Time) const
{
    const float x = X.GetRichCurveConst()->Eval(Time, 0);
    const float y = Y.GetRichCurveConst()->Eval(Time, 0);
    const float z = Z.GetRichCurveConst()->Eval(Time, 0);
    return FVector(x, y, z);
}

float FCustomVectorCurve::GetMaxX() const
{
    return UHMC::GetFloatCurveMaxValue(X);
}

float FCustomVectorCurve::GetMaxZ() const
{
    return UHMC::GetFloatCurveMaxValue(Z);
}

float FCustomVectorCurve::GetMaxZTime() const
{
    float Time;
    const bool bOK = GetFirstTimeWhenZEquals(Time, GetMaxZ());
    return bOK ? Time : 0.0f;
}

bool FCustomVectorCurve::GetAllVectorsWhereZEquals(float Value, TArray<FVector>& OutVectors) const
{
    return GetAllVectorsWhereValueEquals(Z, Value, OutVectors);
}

bool FCustomVectorCurve::GetTimesWhenXEquals(float Value, TArray<float>& Times, float Tolerance, float StartTime) const
{
    return UHMC::GetCurveTimesWhenValueEquals(X, Value, Times, StartTime, Tolerance);
}

bool FCustomVectorCurve::GetTimesWhenZEquals(float Value, TArray<float>& Times, float Tolerance, float StartTime) const
{
    return UHMC::GetCurveTimesWhenValueEquals(Z, Value, Times, StartTime, Tolerance);
}

FCustomVectorCurve FCustomVectorCurve::GetSliceByKeyIndexFromStart(int LastIndex) const
{
    FCustomVectorCurve Out;
    Out.X = UHMC::GetFloatCurveSliceFromStartByIndex(X, LastIndex);
    Out.Y = UHMC::GetFloatCurveSliceFromStartByIndex(Y, LastIndex);
    Out.Z = UHMC::GetFloatCurveSliceFromStartByIndex(Z, LastIndex);
    return Out;
}

FCustomVectorCurve FCustomVectorCurve::GetSliceByKeyIndexFromEnd(int StartIndex) const
{
    FCustomVectorCurve Out;
    Out.X = UHMC::GetFloatCurveSliceFromEndByIndex(X, StartIndex);
    Out.Y = UHMC::GetFloatCurveSliceFromEndByIndex(Y, StartIndex);
    Out.Z = UHMC::GetFloatCurveSliceFromEndByIndex(Z, StartIndex);
    return Out;
}

FRuntimeFloatCurve FCustomVectorCurve::GetDistanceToVector(FVector V) const
{
    FRuntimeFloatCurve OutCurve;
    const auto Curve = OutCurve.GetRichCurve();
        
    TArray<float> Times, _;
    UHMC::GetFloatCurveValueTimeArrays(X, _, Times);

    for (const auto Time : Times)
    {
        FVector Value = GetVectorValue(Time);
        FVector Delta = V - Value;
        const float Distance = Delta.Size();
        Curve->AddKey(Time, Distance);
    }
        
    return OutCurve;
}

void FCustomVectorCurve::RotateByQuat(const FQuat& Q)
{
    TArray<float> Times;
    TArray<FVector> PrevValues;
    GetTimesAndValues(Times, PrevValues);
    const TArray<FVector> NewValues = UHMTrajectory::RotateTrajectoryByQuat(PrevValues, Q);
    Init(Times, NewValues);
}

bool FCustomVectorCurve::GetNthTimeWhenXEquals(float Value, float& OutTime, int Index, float Tolerance, float StartTime) const
{
    return UHMC::GetCurveNthTimeWhenValueEquals(X, Value, OutTime, Index,  StartTime, Tolerance);
}

bool FCustomVectorCurve::GetNthTimeWhenYEquals(float Value, float& OutTime, int Index, float Tolerance, float StartTime) const
{
    return UHMC::GetCurveNthTimeWhenValueEquals(Y, Value, OutTime, Index, StartTime, Tolerance);
}

bool FCustomVectorCurve::GetNthTimeWhenZEquals(float Value, float& OutTime, int Index, float Tolerance, float StartTime) const
{
    return UHMC::GetCurveNthTimeWhenValueEquals(Z, Value, OutTime, Index, StartTime, Tolerance);
}

 bool FCustomVectorCurve::GetFirstTimeWhenZEquals(float& OutTime, float Value, float Tolerance, float StartTime) const
{
    return UHMC::GetCurveFirstTimeWhenValueEquals(Z, Value, OutTime, StartTime, Tolerance);
}

bool FCustomVectorCurve::GetLastTimeWhenZEquals(float& OutTime, float Value, float Tolerance, float StartTime) const
{
    return UHMC::GetCurveLastTimeWhenValueEquals(Z, Value, OutTime, StartTime, Tolerance);
}
