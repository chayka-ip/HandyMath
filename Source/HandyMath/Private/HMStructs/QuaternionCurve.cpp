#include "HandyMath/Public/HMStructs/QuaternionCurve.h"

#include "HandyMathCurveLibrary.h"

void FQuaternionCurve::Reset()
{
    X.GetRichCurve()->Reset();
    Y.GetRichCurve()->Reset();
    Z.GetRichCurve()->Reset();
    W.GetRichCurve()->Reset();
}

void FQuaternionCurve::UpdateOrAddKey(float Time, const FQuat& Q)
{
    X.EditorCurveData.UpdateOrAddKey(Time, Q.X, false);
    Y.EditorCurveData.UpdateOrAddKey(Time, Q.Y, false);
    Z.EditorCurveData.UpdateOrAddKey(Time, Q.Z, false);
    W.EditorCurveData.UpdateOrAddKey(Time, Q.W, false);
}

void FQuaternionCurve::InsertKeyToEnd(float Time, const FQuat& Q)
{
    UHMC::FloatCurveInsertKeyToEnd(X, Q.X, Time);
    UHMC::FloatCurveInsertKeyToEnd(Y, Q.Y, Time);
    UHMC::FloatCurveInsertKeyToEnd(Z, Q.Z, Time);
    UHMC::FloatCurveInsertKeyToEnd(W, Q.W, Time);
}

FQuat FQuaternionCurve::GetQuatValue(float Time) const
{
    const float x = X.GetRichCurveConst()->Eval(Time, 0);
    const float y = Y.GetRichCurveConst()->Eval(Time, 0);
    const float z = Z.GetRichCurveConst()->Eval(Time, 0);
    const float w = W.GetRichCurveConst()->Eval(Time, 0);
    return FQuat(x, y, z, w);
}

FQuat FQuaternionCurve::LastKey() const
{
    if(HasKeys())
    {
        const int Index = LastKeyIndex();
        const float x = X.GetRichCurveConst()->Keys[Index].Value;
        const float y = Y.GetRichCurveConst()->Keys[Index].Value;
        const float z = Z.GetRichCurveConst()->Keys[Index].Value;
        const float w = W.GetRichCurveConst()->Keys[Index].Value;
        return FQuat(x, y, z, w);
    }
    return FQuat::Identity;
}
