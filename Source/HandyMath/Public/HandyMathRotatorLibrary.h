// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HandyMathLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandyMathRotatorLibrary.generated.h"

/*
 * orig angle:
 * clockwise => negative 
 * counter clockwise => positive
 * 
 * UE angle relative to forward:
 * clockwise => positive
 * counter clockwise => negative
 */

// if abs value of angle is less than this -> quat will be identity
static constexpr float MIN_ANGLE_DEG_FOR_QUAT = 0.1f;


UCLASS()
class HANDYMATH_API UHMR : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Library")
	static  FRotator FindLookAtRotationTrimmedByPlane(const FVector &Start, const FVector &Target, HM3DPlane Plane);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
    static  FRotator FindLookAtRotationTrimmedByPlanePure(const FVector &Start, const FVector &Target, HM3DPlane Plane);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Library")
    static  FVector FindLookAtRotationTrimmedByPlaneRightVector(const FVector &Start, const FVector &Target, HM3DPlane Plane);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FQuat RotatorToQuat(const FRotator &Rotator) {return Rotator.Quaternion();}

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FQuat QuatFromAxisAngleRad(FVector Axis, float AngleRad, bool bNormalizeAxis);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FQuat QuatFromAxisAngleDeg(FVector Axis, float AngleDeg, bool bNormalizeAxis);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FQuat QuatZAxisAngleDeg(float AngleDeg);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FQuat GetDeltaRotation(const FQuat &Target, const FQuat &Initial);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static float GetDeltaRotationAngleRad(const FQuat &Target, const FQuat &Initial);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static void MirrorQuat(const FQuat &InQ, FQuat &Q);
	static void MirrorQuat(FQuat &Q);

	static void RotateTransformRotation(FTransform &T, FQuat Q);
	static void RotateTransformRotationAxisAngleDeg(FTransform &T, FVector Axis, float Angle, bool bNormalizeAxis=false);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static void RotateTransformRotation(const FTransform &InT, FRotator R, FTransform &OutT);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static void RotateTransformRotationAxisAngleDeg(const FTransform &InT, FVector Axis, float Angle, bool bNormalizeAxis, FTransform &OutT);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static void RotateTransformLocationAngleDeg(FTransform& T,FVector Axis, float Angle, bool bNormalizeAxis);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static void RotateTransformLocationZAxisAngleDeg(FTransform& T, float Angle);

	static  void MirrorTransform(FTransform &T);

	static  float GetOrientationForwardVectorToDirectionOnPlane(FVector Dir, FQuat Q, HM3DPlane Plane);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static  float GetOrientationForwardVectorToDirectionOnPlane(FVector Dir, FRotator R, HM3DPlane Plane);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static float AngleBetweenRotationsForwardOnPlaneDeg(FQuat A, FQuat B, HM3DPlane Plane, bool bRotateToA=false);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static float AngleBetweenRotatorsForwardOnPlane(FRotator A, FRotator B, HM3DPlane Plane, bool bRotateToA=false);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static void ConvertQuatsToCodirectionalAxisZ(FQuat A, FQuat B, FQuat &OutA, FQuat &OutB);
	static void ConvertQuatsToCodirectionalAxisZ(FQuat &A, FQuat &B);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FQuat NegateQuat(FQuat Q);
	static void QuatNegate(FQuat &Q);

	static FQuat Slerp(const FQuat& A, const FQuat& B, float Alpha);

	UFUNCTION(BlueprintPure)
	static FQuat QuatAxisAngleDeg(FVector Axis, float A);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FQuat ScaleQuat(FQuat Q, float V);
	static void QuatScale(FQuat& Q, float V, bool bClampByAbs=false);

	UFUNCTION(BlueprintPure, Category = "Handy Math Rotator Pure")
	static FQuat GetRandomQuat();
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FString QuatToString(FQuat Q, bool bAngleRad=false);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Library")
	static void PrintQuatToLog(FQuat Q);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static void SplitQuat(FQuat Q, FVector &Axis, float &AngleDeg);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FVector GetOrientationForwardVectorOnPlane(FQuat Q, HM3DPlane Plane);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static float ZQuatGetAngleDeg(const FQuat& Q);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FQuat QuatUpAngleDeg(float A);
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FQuat QuatUpAngleDegValidated(float A);
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static FQuat GetAlmostZeroUpQuat();
	static FQuat GetZQuatValidated(const FQuat& Q);
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static bool IsZQuat(const FQuat &Q);

	UFUNCTION(BlueprintPure,  Category = "Handy Math Rotator Pure")
	static FQuat GetDeltaOrientation_WorldForwardRotated_XY_XZ(FVector V1, FVector V2);
	
	UFUNCTION(BlueprintPure,  Category = "Handy Math Rotator Pure")
	static FQuat GetOrientationFromWorldForwardRotated_XY_XZ_FromV(FVector V);
	
	UFUNCTION(BlueprintPure,  Category = "Handy Math Rotator Pure")
	static FQuat GetOrientationFromWorldForwardRotated_XY_XZ(float AngleXY, float AngleXZ);

	UFUNCTION(BlueprintPure,  Category = "Handy Math Rotator Pure")
	static FQuat QuatApplyRightUpRotation(FQuat Q, float AngleDegRight, float AngleDegUp);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Rotator Pure")
	static float GetDeltaRotationZQuatAngleDeg(const FQuat &Target, const FQuat &Initial);

	static float SplitAngleToCircles(float Angle, int& NumCircles);

	static float ClampedAngleTo360Positive(float A);
	UFUNCTION(BlueprintPure)
	static float GetAngle360LeftoverPositiveClockwiseAlwaysPositive(float Angle);
	UFUNCTION(BlueprintPure)
	static float ClampAnglesAndSumAlwaysPositive360(float A1, float A2);
	
	static float ConvertAngleDeg180To360ClockwisePositive(float Angle);

};
