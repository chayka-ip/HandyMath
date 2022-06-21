#pragma once

#include "CoreMinimal.h"
#include "HandyMathCurveLibrary.h"
#include "CustomVectorCurve.generated.h"

USTRUCT(BlueprintType)
struct HANDYMATH_API FCustomVectorCurve
{
    GENERATED_BODY()
    
public:
    FCustomVectorCurve(){}
    FCustomVectorCurve(const TArray<FVector>& Vectors, float TimeStep);
    FCustomVectorCurve(const TArray<float> &Times, const TArray<FVector> Values);

public:
    
    UPROPERTY(BlueprintReadWrite)
    FRuntimeFloatCurve X = FRuntimeFloatCurve();
    UPROPERTY(BlueprintReadWrite)
    FRuntimeFloatCurve Y = FRuntimeFloatCurve();
    UPROPERTY(BlueprintReadWrite)
    FRuntimeFloatCurve Z = FRuntimeFloatCurve();

public:
    void Reset();
    void Init(const TArray<float> &Times, const TArray<FVector> Values);
    void UpdateOrAddKey(float Time, const FVector &V);
    void InsertKeyToEnd(float Time, const FVector &V);
    void AddKeys(const TArray<float>& Times, const TArray<FVector>& Values);
    FVector GetVectorValue(float Time) const;
    float GetMaxTime() const {return UHMC::GetCurveMaxTime(X);}
    float GetMaxX() const;
    float GetMaxZ() const;
    float GetMaxZTime() const;
    float GetTimeFromRatio(float Ratio) const;

    FVector GetValueAtZero() const {return GetVectorValue(0.0f);}
    FVector LastKey() const;
    
public:
    float GetTimeAtKeyIndex(int Index) const;
    float GetTimeBetweenKeyIndices(int StartIndex, int EndIndex, float Alpha) const;
    TArray<float> GetTimes() const;
    TArray<FVector> GetVectorKeys() const;
    TArray<FVector> GetVectorsFromTimes(const TArray<float>& Times) const;
    void GetTimesAndValues(TArray<float>& Times, TArray<FVector>& Values) const;

public:
    bool GetAllVectorsWhereValueEquals(const FRuntimeFloatCurve& Curve, float Value, TArray<FVector>& OutVectors) const;
    bool GetAllVectorsWhereXEquals(float Value, TArray<FVector>& OutVectors) const;
    bool GetAllVectorsWhereZEquals(float Value, TArray<FVector>& OutVectors) const;
    bool GetNthTimeWhenXEquals(float Value, float& OutTime, int Index=0, float Tolerance=0.01f, float StartTime=0.0f) const;
    bool GetNthTimeWhenYEquals(float Value, float& OutTime, int Index=0, float Tolerance=0.01f, float StartTime=0.0f) const;
    bool GetNthTimeWhenZEquals(float Value, float& OutTime, int Index=0, float Tolerance=0.01f, float StartTime=0.0f) const;
    bool GetFirstTimeWhenZEquals(float& OutTime, float Value=0.0f, float Tolerance=0.01f, float StartTime=0.0) const;
    bool GetLastTimeWhenZEquals(float& OutTime, float Value=0.0f, float Tolerance=0.01f, float StartTime=0.0) const;
    bool GetTimesWhenXEquals(float Value, TArray<float>& Times, float Tolerance=0.01f, float StartTime=0.0) const;
    bool GetTimesWhenZEquals(float Value, TArray<float>& Times, float Tolerance=0.01f, float StartTime=0.0) const;

public:
    FCustomVectorCurve GetSliceByKeyIndexFromStart(int LastIndex) const;
    FCustomVectorCurve GetSliceByKeyIndexFromEnd(int StartIndex) const;

public:
    FRuntimeFloatCurve GetDistanceToVector(FVector V) const;
    void RotateByQuat(const FQuat& Q);
    int GetNumKeys() const {return X.GetRichCurveConst()->GetNumKeys();}
    bool HasKeys() const {return GetNumKeys() > 0;}
};