// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandyMathLibrary.h"
#include "HMStructs/FloatMinMax.h"
#include "HandyMathVectorLibrary.generated.h"

/*
 *  Positive Angle measured clockwise
 *
 *  Signed angle between Direction and Vector (when Direction is first) shows rotation from Direction To Vector
 */
UCLASS()
class HANDYMATH_API UHMV : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static float GetVectorComponentByEnum(FVector V, EVectorComponents E);
public:

	// Normal is perpendicular to both vectors
	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static float SignedAngleBetweenVectorsThroughNormalDeg(FVector Dir, FVector V, FVector N);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static float SignedAngleBetweenVectorsThroughNormalRad(FVector Dir, FVector V, FVector N);
	
	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static bool AreVectorsPointToSimilarHalfPlane(FVector V1, FVector V2);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static bool IsRightSideVectorTowardsDirOnPlane(FVector Direction, FVector V, HM3DPlane Plane);

	static bool HasZeroVector(FVector V1, FVector V2, float Tol=0.001f);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static  bool IsRightSideVectorTowardsDirOnPlanePure(const FVector Direction, const FVector V, HM3DPlane Plane);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
    static FVector GetForwardVectorBasedOnPlane(HM3DPlane Plane);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static FVector GetForwardVectorBasedOnPlanePure(HM3DPlane Plane);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector GetUpVectorBasedOnPlane(HM3DPlane Plane);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector GetUpVectorBasedOnPlanePure(HM3DPlane Plane);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector GetRightVectorBasedOnPlane(HM3DPlane Plane);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static FVector GetRightVectorBasedOnPlanePure(HM3DPlane Plane);

	// UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static float GetForwardVectorComponentBasedOnPlane(FVector V, HM3DPlane Plane);

	// UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static float GetForwardVectorComponentBasedOnPlanePure(FVector V, HM3DPlane Plane);

	// UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static float GetUpVectorComponentBasedOnPlane(FVector V, HM3DPlane Plane);

	// UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static float GetUpVectorComponentBasedOnPlanePure(FVector V, HM3DPlane Plane);

	// UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static float GetRightVectorComponentBasedOnPlane(FVector V, HM3DPlane Plane);

	// UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static float GetRightVectorComponentBasedOnPlanePure(FVector V, HM3DPlane Plane);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Vector Library")
	static FVector VectorMultiplyByWorldDeltaSeconds(const UObject* WorldContextObject, FVector V);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category= "Handy Math Vector Library Pure")
	static FVector VectorMultiplyByWorldDeltaSecondsPure(const UObject* WorldContextObject, FVector V);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Handy Math Vector Library")
	static FVector VectorDivideByWorldDeltaSeconds(const UObject* WorldContextObject, FVector V);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static float GetAngleVectorToPlaneXY(FVector V);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category= "Handy Math Vector Library Pure")
    static FVector VectorDivideByWorldDeltaSecondsPure(const UObject* WorldContextObject, FVector V);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector RandomVector(const float MinLimit, const float MaxLimit, const bool bNormalize=false);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector RandomVectorPure(const float MinLimit, const float MaxLimit, const bool bNormalize);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector RandomVectorShort(const float Limit, const bool bNormalize=false);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector RandomVectorShortPure(const float Limit, const bool bNormalize);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector  VectorFromFloat(float F);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector  VectorFromFloatPure(float F);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector GetForwardRotatedUpAxis(float AngleDeg);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector ReplaceVectorValue(FVector V, float Val, EVectorComponents E);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector ReplaceVectorValuePure(FVector V, float Val, EVectorComponents E);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector ReplaceVectorValues(FVector V, float X, float Y, float Z,  bool bX,  bool bY,  bool bZ, bool bNormalize=false);

	UFUNCTION(BlueprintPure, Category = "Handy Math Vector Library Pure")
	static FVector ReplaceVectorValuesPure(FVector V, float X, float Y, float Z,  bool bX,  bool bY,  bool bZ, bool bNormalize=false);

	// TODO: Now it handles only X Y Z, we want all cases possible
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector VectorAddValueToCurrent(FVector V, float Val, EVectorComponents E);

	UFUNCTION(BlueprintPure, Category = "Handy Math Vector Library Pure")
	static FVector VectorAddValueToCurrentPure(FVector V, float Val, EVectorComponents E);
	
	UFUNCTION(BlueprintCallable,meta=(AdvancedDisplay = "1"), Category = "Handy Math Vector Library")
	static FVector TrimVector(const FVector V, const bool bX, const bool bY, const bool bZ, const bool bNormalize=false);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "1"), Category= "Handy Math Vector Library Pure")
	static FVector TrimVectorPure(const FVector V, const bool bX, const bool bY, const bool bZ, const bool bNormalize=false);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "1"), Category= "Handy Math Vector Library Pure")
	static FVector TrimVectorZ(FVector V);

	UFUNCTION(BlueprintCallable,meta=(AdvancedDisplay = "1"), Category = "Handy Math Vector Library")
    static FVector TrimVectorByPlane(const FVector V, HM3DPlane Plane, const bool bNormalize=false);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "1"), Category= "Handy Math Vector Library Pure")
    static FVector TrimVectorByPlanePure(const FVector V, HM3DPlane Plane, const bool bNormalize=false);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector TrimSmallVectorToZero(FVector V, float MinSize=0.0f);
	
	UFUNCTION(BlueprintCallable,meta=(AdvancedDisplay = "1"), Category = "Handy Math Vector Library")
    static FVector VectorNegateComponent(const FVector V, const bool bX, const bool bY, const bool bZ, const bool bNormalize=false);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "1"), Category= "Handy Math Vector Library Pure")
    static FVector VectorNegateComponentPure(const FVector V, const bool bX, const bool bY, const bool bZ, const bool bNormalize=false);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector VectorScaleFromFloat(const float F);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector VectorScaleFromFloatPure(const float F);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static  FVector RotateVectorZAxis(FVector V, float AngleDeg);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector ConvertVectorToPlaneXZ(FVector V);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static float GetSphereRadiusFromScale(const FVector V);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static float GetSphereRadiusFromScalePure(const FVector V);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static float AngleBetweenVectorsDeg(const FVector V1, const FVector V2);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static float AngleBetweenVectorsDegPure(const FVector V1, const FVector V2);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static float AngleBetweenVectorsRad(const FVector V1, const FVector V2);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static float AngleBetweenVectorsRadPure(const FVector V1, const FVector V2);

	UFUNCTION(BlueprintCallable,meta=(AdvancedDisplay = "2"), Category = "Handy Math Vector Library")
    static float AngleBetweenVectorsDegOnPlane(FVector V1, FVector V2,HM3DPlane Plane);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "2"), Category= "Handy Math Vector Library Pure")
    static float AngleBetweenVectorsDegOnPlanePure(FVector V1, FVector V2,HM3DPlane Plane);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static float AngleByThreePointsDeg(const FVector P0, const FVector P1, const FVector P2);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static float AngleByThreePointsDegPure(const FVector P0, const FVector P1, const FVector P2);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static float SignedAngleBetweenVectorsDeg(const FVector Direction, const FVector V, bool IsRightSideVector);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static float SignedAngleBetweenVectorsDegPure(const FVector Direction, const FVector V, bool IsRightSideVector);
	
	UFUNCTION(BlueprintCallable,meta=(AdvancedDisplay = "2"), Category = "Handy Math Vector Library")
    static float SignedAngleBetweenVectorsDegOnPlane(const FVector Direction, const FVector V,HM3DPlane Plane);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "2"), Category= "Handy Math Vector Library Pure")
    static float SignedAngleBetweenVectorsDegOnPlanePure(const FVector Direction, const FVector V,HM3DPlane Plane);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "2"), Category= "Handy Math Vector Library Pure")
	static float Angle360BetweenVectorsDegOnPlanePure(const FVector Direction, const FVector V,HM3DPlane Plane);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "2"), Category= "Handy Math Vector Library Pure")
	static float SignedAngleBetweenVectorsDegXY(const FVector& Direction, const FVector& V);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "2"), Category= "Handy Math Vector Library Pure")
	static float SignedAngleVectorToWorldForwardDegXY(FVector V);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "2"), Category= "Handy Math Vector Library Pure")
	static float SignedAngleWorldForwardToVectorDegXY(FVector V);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static float SignedAngleVectorToPlaneXY(const FVector& V=FVector::ZeroVector);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static void SplitVectorToDetailed(const FVector& V, float& Magnitude, float& Angle_XY, float& Angle_XZ);
	
	UFUNCTION(BlueprintPure,  Category = "Handy Math Rotator Pure")
	static FVector GetForwardVectorFromDeltaOrientation_WorldForwardRotated_XY_XZ(FVector V1, FVector V2);
	UFUNCTION(BlueprintPure,  Category = "Handy Math Rotator Pure")
	static FVector GetVectorFromDeltaOrientation_WorldForwardRotated_XY_XZ(FVector V1, FVector V2);
	// Do not use
	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector GetVectorRotated_XY_XZ(FVector V, float AngleXY, float AngleXZ);
	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector GetVectorRotated_XY(FVector Dir_XY, float OwnAngleXY, float OwnAngleXZ);
	
	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector GetWorldForwardRotated_XY_XZ(float AngleXY, float AngleXZ);
	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector GetWorldForwardRotatedScaled_XY_XZ(float Magnitude, float AngleXY, float AngleXZ);
	static FVector RotateVectorZeroAngleCheck(const FVector& V, float Angle, const FVector& Axis);
	
	UFUNCTION(BlueprintCallable,meta=(AdvancedDisplay = "2"), Category = "Handy Math Vector Library")
	static float SignedAngleBetweenVectorsRadOnPlane(const FVector V1, const FVector V2,HM3DPlane Plane);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "2"), Category= "Handy Math Vector Library Pure")
    static float SignedAngleBetweenVectorsRadOnPlanePure(const FVector V1, const FVector V2,HM3DPlane Plane);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static float SignedAngleTo360Deg(float AngleDeg);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector GetMiddleBetweenLocations(const FVector V1, const FVector V2);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static FVector GetMiddleBetweenLocationsPure(const FVector V1, const FVector V2);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static bool IsLocationInRadiusFromOrigin(const FVector &Origin, const FVector &Location, float Distance);

	UFUNCTION(BlueprintPure, Category = "Handy Math Vector Library Pure")
	static bool IsLocationInRadiusFromOriginPure(const FVector &Origin, const FVector &Location, float Distance);

	UFUNCTION(BlueprintCallable,meta=(AdvancedDisplay = "3"), Category = "Handy Math Vector Library")
	static bool IsLocationInRadiusFromOriginInPlane(const FVector &Origin, const FVector &Location, float Distance, HM3DPlane Plane);

	UFUNCTION(BlueprintPure,meta=(AdvancedDisplay = "3"), Category = "Handy Math Vector Library Pure")
	static bool IsLocationInRadiusFromInOriginInPlanePure(const FVector &Origin, const FVector &Location, float Distance, HM3DPlane Plane);

	/*
	 * V1 - direction start
	 * V2 - direction end
	 */
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector GetPerpendicularLocationFromPointToLine(const FVector Origin, const FVector V1, const FVector V2);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static FVector GetPerpendicularLocationFromPointToLinePure(const FVector Origin, const FVector V1, const FVector V2);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector GetPerpendicularLocationFromPointToLineWithDir(const FVector Origin, const FVector Direction, const FVector PointOnLine);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector GetPerpendicularLocationFromPointToLineWithDirPure(const FVector Origin, const FVector Direction, const FVector PointOnLine);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static  FVector GetLocationOfPerpendicularToDirectionThroughOtherLocation(FVector Direction, FVector Origin, FVector OtherLocation);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
    static  FVector GetLocationOfPerpendicularToDirectionThroughOtherLocationPure(FVector Direction, FVector Origin, FVector OtherLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector GetWorldLocationFromDirectionAndDistance(const FVector StartLocation, const FVector Direction, const float Distance);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector GetWorldLocationFromDirectionAndDistancePure(const FVector StartLocation, const FVector Direction, const float Distance);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector LerpVector(const FVector& A, const FVector& B, float Alpha, float Tolerance);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector LerpVectorPure(const FVector& A, const FVector& B, float Alpha, float Tolerance);
	
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector ScaleRadiusVector(const FVector &Origin,  const FVector &InLocation,  float Multiplier = 1);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector ScaleRadiusVectorPure(const FVector &Origin,  const FVector &InLocation,  float Multiplier = 1);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static  bool IsLocationNotFarThanRadiusVectorFromTarget(FVector Center, FVector RadiusPoint,  FVector Location);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static  bool IsLocationNotFarThanRadiusVectorFromTargetPure(FVector WTarget, FVector WRadiusPoint,  FVector ThisLocation);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector ConvertVectorToSameBasisRotatedAroundNormal(const FVector TargetForward, const FVector V, HM3DPlane Plane);
	
	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector ConvertVectorToSameBasisRotatedAroundNormalPure(const FVector TargetForward, const FVector V, HM3DPlane Plane);
	
	/*
	 * \brief use from camera
	 * \param TargetForward 
	 * \param V 
	 * \param Plane 
	 * \return 
	 */
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector ConvertVectorToOtherBasisPreserveRelativityOnPlane(const FVector TargetForward, const FVector V, HM3DPlane Plane);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector ConvertVectorToOtherBasisPreserveRelativityOnPlanePure(const FVector TargetForward, const FVector V, HM3DPlane Plane);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector GetLocationOnDistanceFromVectorEnd(const FVector Start, const FVector End, float Distance);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector GetLocationOnDistanceFromVectorEndPure(const FVector Start, const FVector End, float Distance);

	/*
	 * HypEndAdjacent - point on AdjacentNormal
	 * PerpendicularPoint - point on AdjacentNormal
	 */
	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static void CalculateRightTriangleFromHypoAndNormal(FVector HypEndAdjacent, FVector HypEndOpposite, FVector AdjacentNormal, FVector &PerpendicularPoint, FVector &AjacentSide, FVector &OppositeSide);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static void CalculateRightTriangleFromHypoAndNormalPure(FVector HypEndAdjacent, FVector HypEndOpposite, FVector AdjacentNormal, FVector &PerpendicularPoint, FVector &AjacentSide,  FVector &OppositeSide);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static void CalculateVectorProjectionComponentsOntoNormal(FVector Normal, FVector V, FVector& TangentialComp, FVector& PerpendicularComp);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static void CalculateVectorProjectionComponentsOntoNormalPure(FVector Normal, FVector V, FVector& TangentialComp, FVector& PerpendicularComp);

	UFUNCTION(BlueprintCallable, Category = "Handy Math Vector Library")
	static FVector RemoveProjectionFromVector(FVector Direction,  FVector V);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector RemoveProjectionFromVectorPure(FVector Direction,  FVector V);

	/*
	 * All vectors must be in one plane
	 * LineP2 is more distant from start than LineP1
	 */
	UFUNCTION(BlueprintCallable)
	static bool GetTriangleVertexLayingOnLineFromDefinedVectorPlaneXY(FVector Start, FVector End, FVector LineP1, FVector LineP2, FVector &OutV, float &RotAngle);
	
	static FVector GetVectorTrimmedXY(FVector V, bool DoTrim);
	static FVector GetVectorTrimmedXY(const bool DoTrim, const bool bNormalized, FVector V);
	static FVector GetVectorNormalizedOptional(const FVector& V, bool bN);

	static void SetRotationAngleSignInPlane(FVector RefDir, FVector V, float& A, HM3DPlane Plane);
	/*
	* Determines sign of angle when  rotating vector
	* Suppose than clockwise is positive angle direction
	*/
	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static void SetRotationAngleSignInPlane(FVector RefDir, FVector V, float InA, float& A, HM3DPlane Plane);

	/*A1 and A2 represents points on the angle ends*/
	static bool IsPointBelongsToAngleOnPlane(FVector Center, FVector Point, FVector A1, FVector A2, HM3DPlane Plane);
	
	UFUNCTION(BlueprintPure, Category = "Handy Math Vector Library Pure")
	static bool IsPointBelongsToAngleOnPlaneCommon(FVector Center, FVector Point, FVector BisectorEndFromCenter, float PosSectorAngleDegAbs, float NegSectorAngleDegAbs, HM3DPlane Plane);
	UFUNCTION(BlueprintPure, Category = "Handy Math Vector Library Pure")
	static bool IsPointBelongsToSectorOnPlane(FVector Center, FVector Point, FVector BisectorEndFromCenter, float HalfSectorAngle, HM3DPlane Plane);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static bool IsVectorBetweenVectorsOnPlane(FVector V, FVector A, FVector B, FVector Mid, HM3DPlane Plane, float& AngleToA, float& AngleToB);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static bool IsVectorBetweenVectorsOnPlaneXY(FVector V, FVector A, FVector B, FVector Mid, float& AngleToA, float& AngleToB);
	static bool IsVectorBetweenVectorsOnPlaneXY(FVector V, FVector A, FVector B, FVector Mid);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector ClampVectorToMaxSize(FVector V, float Size);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static bool GetLineIntersectionsWithSphereFromPAndNormal(FVector P, FVector N, FVector SC, float SR, FVector& Res1, FVector& Res2);

	// Returns points of intersection if they exist. Res1 is the closest to P1.
	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static bool GetLineIntersectionsWithSphereFromTwoPoints(FVector P1, FVector P2, FVector SC, float SR, FVector& Res1, FVector& Res2);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static FVector GetNearestLocation(const TArray<FVector> &Locations, FVector Target);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static bool IsAngleBetweenVectorsInRange(FVector A, FVector B, float AngleMin, float AngleMax, float Tolerance=0.01f);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static bool LineToLineIntersection(const FVector& A1, const FVector& B1, const FVector& A2, const FVector& B2, FVector& Intersection);

	UFUNCTION(BlueprintPure, Category= "Handy Math Vector Library Pure")
	static float GetSignedAngleForDirectionToLocationFromLocationDegXY(const FVector& Origin, const FVector& Target, const FVector& Dir);

	static bool VectorsMapMinMaxComponent(FVector A, FVector B, float& Min, float& Max, EVectorComponents Component);
	static bool VectorsMapMinMaxComponent(FVector A, FVector B, EVectorComponents Component, FFloatMinMax& Out);
	static FFloatMinMax VectorsMapMinMaxComponent(FVector A, FVector B, EVectorComponents Component);
};
