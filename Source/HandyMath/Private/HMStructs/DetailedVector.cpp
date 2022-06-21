#include "HandyMath/Public/HMStructs/DetailedVector.h"

void FDetailedVector::Initialize(float magnitude, float angle_XY, float angle_XZ)
{
    const FVector vector = magnitude * UHMV::GetWorldForwardRotated_XY_XZ(angle_XY, angle_XZ);
    Initialize(vector);
}

void FDetailedVector::Initialize(const FVector& v)
{
    V = v;
    Direction = V.GetSafeNormal();
    UHMV::SplitVectorToDetailed(V, Magnitude.Value, Angle_XY.Value, Angle_XZ.Value);
}

bool FDetailedVector::HasAcceptableValue(float Ref, EVST_VectorValueType ValueType, EFST_FloatSearchType SearchType) const
{
    if(ValueType == EVST_Magnitude)return Magnitude.IsAcceptable(Ref, SearchType);
    if(ValueType == EVST_AngleXY)return Angle_XY.IsAcceptable(Ref, SearchType);
    if(ValueType == EVST_AngleXZ)return Angle_XZ.IsAcceptable(Ref, SearchType);
    return  false;
}

bool FDetailedVector::IsSimilarTo(const FDetailedVector& Other) const
{
    const bool B1 = Direction.Equals(Other.Direction,0.05f);
    const bool B2 = HasAcceptableValue(Other.Magnitude.Value, EVST_Magnitude, EFST_Equal);
    const bool B3 = HasAcceptableValue(Other.Angle_XY.Value, EVST_AngleXY, EFST_Equal);
    const bool B4 = HasAcceptableValue(Other.Angle_XZ.Value, EVST_AngleXZ, EFST_Equal);
    return B1 && B2 && B3 && B4;
}
