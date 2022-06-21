// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyMathRotatorLibrary.h"


#include "HandyMathVectorLibrary.h"
#include "Kismet/KismetMathLibrary.h"


FRotator UHMR::FindLookAtRotationTrimmedByPlane(const FVector& Start, const FVector& Target, HM3DPlane Plane)
{
	return UKismetMathLibrary::FindLookAtRotation(UHMV::TrimVectorByPlane(Start, Plane), UHMV::TrimVectorByPlane(Target, Plane));
}

FRotator UHMR::FindLookAtRotationTrimmedByPlanePure(const FVector& Start, const FVector& Target, HM3DPlane Plane)
{
	return FindLookAtRotationTrimmedByPlane(Start, Target, Plane);
}

FVector UHMR::FindLookAtRotationTrimmedByPlaneRightVector(const FVector& Start, const FVector& Target, const HM3DPlane Plane)
{
	const auto Rotator = FindLookAtRotationTrimmedByPlane(Start, Target, Plane);

	return UKismetMathLibrary::GetRightVector(Rotator);
}

FQuat UHMR::QuatFromAxisAngleRad(FVector Axis, float AngleRad, bool bNormalizeAxis)
{
	return bNormalizeAxis ? FQuat(Axis.GetSafeNormal(), AngleRad) : FQuat(Axis, AngleRad);
}

FQuat UHMR::QuatFromAxisAngleDeg(FVector Axis, float AngleDeg, bool bNormalizeAxis)
{
	const float AngleRad = FMath::DegreesToRadians(AngleDeg);
	return QuatFromAxisAngleRad(Axis, AngleRad, bNormalizeAxis);
}

FQuat UHMR::QuatZAxisAngleDeg(float AngleDeg)
{
	return QuatFromAxisAngleDeg(FVector::UpVector, AngleDeg, false);
}

FQuat UHMR::GetDeltaRotation(const FQuat& Target, const FQuat& Initial)
{
	FQuat Q = Initial;
	Q.EnforceShortestArcWith(Target);
	return Target * Q.Inverse();
}

float UHMR::GetDeltaRotationAngleRad(const FQuat& Target, const FQuat& Initial)
{
	return GetDeltaRotation(Target, Initial).GetAngle();
}

void UHMR::MirrorQuat(const FQuat& InQ, FQuat& Q)
{
	Q = InQ;
	MirrorQuat(Q);
}

void UHMR::MirrorQuat(FQuat& Q)
{
	float Angle;
	FVector Axis;
	Q.ToAxisAndAngle(Axis, Angle);
	Q = FQuat(Axis, -1.0f * Angle);
}

void UHMR::RotateTransformRotation(FTransform& T, FQuat Q)
{
	T.SetRotation(Q * T.GetRotation());
}

void UHMR::RotateTransformRotationAxisAngleDeg(FTransform& T, FVector Axis, float Angle, bool bNormalizeAxis)
{
	if (bNormalizeAxis)
	{
		Axis.Normalize();
	}
	RotateTransformRotation(T, QuatAxisAngleDeg(Axis, Angle));
}

void UHMR::RotateTransformRotation(const FTransform& InT, FRotator R, FTransform& OutT)
{
	OutT = InT;
	RotateTransformRotation(OutT, R.Quaternion());
}

void UHMR::RotateTransformRotationAxisAngleDeg(const FTransform& InT, FVector Axis, float Angle, bool bNormalizeAxis, FTransform& OutT)
{
	OutT = InT;
	RotateTransformRotationAxisAngleDeg(OutT, Axis, Angle, bNormalizeAxis);
}

void UHMR::RotateTransformLocationAngleDeg(FTransform& T, FVector Axis, float Angle, bool bNormalizeAxis)
{
	if(bNormalizeAxis)
	{
		Axis.Normalize();
	}
	const FVector V = T.GetLocation().RotateAngleAxis(Angle, Axis);
	T.SetLocation(V);
}

void UHMR::RotateTransformLocationZAxisAngleDeg(FTransform& T, float Angle)
{
	RotateTransformLocationAngleDeg(T, FVector::UpVector, Angle, false);
}

void UHMR::MirrorTransform(FTransform& T)
{
	FQuat R = T.GetRotation();
	MirrorQuat(R);
	const FVector V = R.RotateVector(T.GetLocation());
	T.SetLocation(V);
	T.SetRotation(R);
}

float UHMR::GetOrientationForwardVectorToDirectionOnPlane(FVector Dir, FQuat Q, HM3DPlane Plane)
{
	return UHMV::SignedAngleBetweenVectorsDegOnPlane(Dir, Q.GetForwardVector(), Plane);
}

float UHMR::GetOrientationForwardVectorToDirectionOnPlane(FVector Dir, FRotator R, HM3DPlane Plane)
{
	return GetOrientationForwardVectorToDirectionOnPlane(Dir, R.Quaternion(), Plane);
}

float UHMR::AngleBetweenRotationsForwardOnPlaneDeg(FQuat A, FQuat B, HM3DPlane Plane, bool bRotateToA)
{
	const FVector F1 = A.GetForwardVector();
	const FVector F2 = B.GetForwardVector();
	const float Angle = UHMV::SignedAngleBetweenVectorsDegOnPlane(F1, F2, Plane);
	return  bRotateToA ? -Angle : Angle;
}

float UHMR::AngleBetweenRotatorsForwardOnPlane(FRotator A, FRotator B, HM3DPlane Plane,  bool bRotateToA)
{
	return AngleBetweenRotationsForwardOnPlaneDeg(A.Quaternion(), B.Quaternion(), Plane,bRotateToA);
}

void UHMR::ConvertQuatsToCodirectionalAxisZ(FQuat A, FQuat B, FQuat& OutA, FQuat& OutB)
{
	OutA = A;
	OutB = B;
	ConvertQuatsToCodirectionalAxisZ(OutA, OutB);
}

void UHMR::ConvertQuatsToCodirectionalAxisZ(FQuat& A, FQuat& B)
{
	const bool bUpA = A.GetRotationAxis().Equals(FVector::UpVector, 0.01f);
	const bool bUpB = B.GetRotationAxis().Equals(FVector::UpVector, 0.01f);

	if(bUpA != bUpB)
	{
		QuatNegate(B);
	}
}

FQuat UHMR::NegateQuat(FQuat Q)
{
	FQuat A = Q;
	QuatNegate(A);
	return A;
}

void UHMR::QuatNegate(FQuat& Q)
{
	Q = FQuat(-Q.GetRotationAxis(), -Q.GetAngle());
}

FQuat UHMR::Slerp(const FQuat& A, const FQuat& B, float Alpha)
{
	return FQuat::Slerp(A, B, Alpha);
}

FQuat UHMR::QuatAxisAngleDeg(FVector Axis, float A)
{
	return FQuat(Axis, FMath::DegreesToRadians(A)); 
}

FQuat UHMR::ScaleQuat(FQuat Q, float V)
{
	FQuat A = Q;
	QuatScale(A, V);
	return  A;
}

void UHMR::QuatScale(FQuat& Q, float V, bool bClampByAbs)
{
	const float A = Q.GetAngle();
	const float F = A * V;
	float Angle;
	
	if(bClampByAbs)
	{
		Angle = UHM::FClampMaxAbsSigned(F, FMath::Abs(A));
	}
	else
	{
		Angle = F;
	}
	
	Q = FQuat(Q.GetRotationAxis(), Angle).GetNormalized();
}

FQuat UHMR::GetRandomQuat()
{
	const FVector Axis = UHMV::RandomVector(0,1,true);
	const float W = FMath::RandRange(0.0f, 1.0f);
	return  FQuat(Axis, W).GetNormalized();
}


FString UHMR::QuatToString(FQuat Q, bool bAngleRad)
{
	float A = Q.GetAngle();

	if(!bAngleRad)
	{
		A = FMath::RadiansToDegrees(A);
	}
	
	return  Q.GetRotationAxis().ToString() + " : " + FString::SanitizeFloat(A);
}

void UHMR::PrintQuatToLog(FQuat Q)
{
	UHM::PrintToLog(QuatToString(Q));
}

void UHMR::SplitQuat(FQuat Q, FVector& Axis, float& AngleDeg)
{
	Axis = Q.GetRotationAxis();
	AngleDeg = FMath::RadiansToDegrees(Q.GetAngle());
}

FVector UHMR::GetOrientationForwardVectorOnPlane(FQuat Q, HM3DPlane Plane)
{
	return UHMV::TrimVectorByPlane(Q.GetForwardVector(), Plane, true);
}

float UHMR::ZQuatGetAngleDeg(const FQuat& Q)
{
	const FVector Axis = Q.GetRotationAxis();
	const float Angle = FMath::RadiansToDegrees(Q.GetAngle());
	if (Axis.Equals(FVector::UpVector, 0.1f)) return Angle;
	if (Axis.Equals(FVector::DownVector, 0.1f)) return -Angle;
	if(FMath::IsNearlyZero(Angle)) return 0;
	
	if (!Q.IsIdentity(0.001f)) UE_LOG(LogTemp, Warning, TEXT("ZQuatGetAngle: not ZQuat passed"))
	return 0;
}

FQuat UHMR::QuatUpAngleDeg(float A)
{
	return FQuat(FVector::UpVector, FMath::DegreesToRadians(A)).GetNormalized();
}

FQuat UHMR::QuatUpAngleDegValidated(float A)
{
	return FMath::Abs(A) > MIN_ANGLE_DEG_FOR_QUAT ? QuatUpAngleDeg(A) : GetAlmostZeroUpQuat();
}

FQuat UHMR::GetAlmostZeroUpQuat()
{
	return  QuatUpAngleDeg(MIN_ANGLE_DEG_FOR_QUAT);
}

FQuat UHMR::GetZQuatValidated(const FQuat& Q)
{
	const FQuat ZeroUp = GetAlmostZeroUpQuat();
	if(IsZQuat(Q))
	{
		const bool bZeroAngle = FMath::IsNearlyZero(Q.GetAngle());
		return bZeroAngle ? ZeroUp : Q;
	}
	UE_LOG(LogTemp, Warning, TEXT("ZQuatGetAngle: not ZQuat passed"))
	return ZeroUp;
}

bool UHMR::IsZQuat(const FQuat& Q)
{
	constexpr float T = 0.1f;
	const FVector Axis = Q.GetRotationAxis();
	const float Angle = Q.GetAngle();
	if(Axis.Equals(FVector::UpVector, T) || Axis.Equals(FVector::DownVector, T)) return true;
	if(FMath::IsNearlyZero(Angle)) return true;
	return Q.IsIdentity(0.001f);
}

FQuat UHMR::GetDeltaOrientation_WorldForwardRotated_XY_XZ(FVector V1, FVector V2)
{
	const FQuat Q1 = GetOrientationFromWorldForwardRotated_XY_XZ_FromV(V1);
	const FQuat Q2 = GetOrientationFromWorldForwardRotated_XY_XZ_FromV(V2);
	return GetDeltaRotation(Q2, Q1);
}

FQuat UHMR::GetOrientationFromWorldForwardRotated_XY_XZ_FromV(FVector V)
{
	float m, xy, xz;
	UHMV::SplitVectorToDetailed(V, m, xy, xz);
	return GetOrientationFromWorldForwardRotated_XY_XZ(xy, xz);
}

FQuat UHMR::GetOrientationFromWorldForwardRotated_XY_XZ(float AngleXY, float AngleXZ)
{
	const FQuat Q1 = FQuat(FVector::UpVector, FMath::DegreesToRadians(AngleXY));
	const FQuat Q2 = FQuat(FVector::LeftVector, FMath::DegreesToRadians(AngleXZ));
	return (Q1 * Q2).GetNormalized();
}

FQuat UHMR::QuatApplyRightUpRotation(FQuat Q, float AngleDegRight, float AngleDegUp)
{
	const FQuat R = QuatFromAxisAngleDeg(Q.GetRightVector(), AngleDegRight, true);
	const FQuat U = QuatFromAxisAngleDeg(Q.GetUpVector(), AngleDegUp, true);
	return  R * U * Q;
}

float UHMR::GetDeltaRotationZQuatAngleDeg(const FQuat& Target, const FQuat& Initial)
{
	const FQuat Q = GetDeltaRotation(Target, Initial);
	return ZQuatGetAngleDeg(Q);
}

float UHMR::SplitAngleToCircles(float Angle, int& NumCircles)
{
	return UHM::SplitFloatsIntWithLeftOver(Angle, NumCircles, 360.0f);
}

float UHMR::ClampedAngleTo360Positive(float A)
{
	return A < 0.0f ?  360.0f + A : A;
}

float UHMR::GetAngle360LeftoverPositiveClockwiseAlwaysPositive(float Angle)
{
	int _;
	const float Leftover = SplitAngleToCircles(Angle, _);
	return ClampedAngleTo360Positive(Leftover);
}

float UHMR::ClampAnglesAndSumAlwaysPositive360(float A1, float A2)
{
	A1 = GetAngle360LeftoverPositiveClockwiseAlwaysPositive(A1);
	A2 = GetAngle360LeftoverPositiveClockwiseAlwaysPositive(A2);
	return GetAngle360LeftoverPositiveClockwiseAlwaysPositive(A1 + A2);
}
