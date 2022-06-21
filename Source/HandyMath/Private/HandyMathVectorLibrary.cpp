// Fill out your copyright notice in the Description page of Project Settings.

#include "HandyMathVectorLibrary.h"

#include "HandyMathRotatorLibrary.h"
#include "NativeLib.h"
#include "Kismet/KismetMathLibrary.h"


float UHMV::GetVectorComponentByEnum(const FVector V, const EVectorComponents E)
{
    if (E == VC_X) return V.X;
    if (E == VC_Y) return V.Y;
    if (E == VC_Z) return V.Z;
    return 0.0f;
}

float UHMV::SignedAngleBetweenVectorsThroughNormalDeg(FVector Dir, FVector V, FVector N)
{
    constexpr float Tol = 0.001f;
    const float Deg = AngleBetweenVectorsDeg(Dir, V);
    const FVector Rotated = Dir.RotateAngleAxis(Deg, N).GetSafeNormal();
    const float Sign = Rotated.Equals(V.GetSafeNormal(), Tol) ? 1.0f : -1.0f;
    
    return Sign * Deg;
}

float UHMV::SignedAngleBetweenVectorsThroughNormalRad(FVector Dir, FVector V, FVector N)
{
    const float Deg = SignedAngleBetweenVectorsThroughNormalDeg(Dir, V, N);
    return FMath::DegreesToRadians(Deg);
}

bool UHMV::AreVectorsPointToSimilarHalfPlane(FVector V1, FVector V2)
{
    return  AngleBetweenVectorsDeg(V1, V2) < 90.0f;
}

bool UHMV::IsRightSideVectorTowardsDirOnPlane(FVector Direction, FVector V, HM3DPlane Plane)
{
    Direction = TrimVectorByPlane(Direction, Plane);
    V = TrimVectorByPlane(V,Plane);

    if (HasZeroVector(Direction, V)) return false;

    const FVector LocalUp = GetUpVectorBasedOnPlane(Plane);
    const FVector LocalRight = UKismetMathLibrary::RotateAngleAxis(Direction, 90, LocalUp);

    const float Angle = AngleBetweenVectorsDeg(LocalRight, V);
    return Angle <= 90 ? true : false;
}

bool UHMV::HasZeroVector(FVector V1, FVector V2, float Tol)
{
    return V1.IsNearlyZero(Tol) || V2.IsNearlyZero(Tol);
}

bool UHMV::IsRightSideVectorTowardsDirOnPlanePure(const FVector Direction, const FVector V, HM3DPlane Plane)
{
    return  IsRightSideVectorTowardsDirOnPlane(Direction, V, Plane);
}

FVector UHMV::GetForwardVectorBasedOnPlane(const HM3DPlane Plane)
{
    switch (Plane)
    {
        case XY: return FVector(1,0,0);
        case XZ: return FVector(1,0,0);
        case YZ: return FVector(0,1,0);
        default: return FVector(1,0,0);       
    }    
}

FVector UHMV::GetForwardVectorBasedOnPlanePure(const HM3DPlane Plane)
{
    return  GetForwardVectorBasedOnPlane(Plane);
}

FVector UHMV::GetUpVectorBasedOnPlane(const HM3DPlane Plane)
{
    switch (Plane)
    {
        case XY: return FVector(0,0,1);
        case XZ: return FVector(0,1,0);
        case YZ: return FVector(1,0,0);
        default: return FVector(0,0,1);       
    }    
}

FVector UHMV::GetUpVectorBasedOnPlanePure(const HM3DPlane Plane)
{
    return  GetUpVectorBasedOnPlane(Plane);
}

FVector UHMV::GetRightVectorBasedOnPlane(const HM3DPlane Plane)
{
    switch (Plane)
    {
        case XY: return FVector(0,1,0);
        case XZ: return FVector(0,0,1);
        case YZ: return FVector(0,0,1);
        default: return FVector(0,1,0);       
    }    
}

FVector UHMV::GetRightVectorBasedOnPlanePure(const HM3DPlane Plane)
{
    return  GetRightVectorBasedOnPlane(Plane);
}

float UHMV::GetForwardVectorComponentBasedOnPlane(FVector V, const HM3DPlane Plane)
{
    switch (Plane)
    {
        case XY: return V.X;
        case XZ: return V.X;
        case YZ: return V.Y;
        default: return V.X;       
    }    
}

float UHMV::GetForwardVectorComponentBasedOnPlanePure(FVector V, const HM3DPlane Plane)
{
    return  GetForwardVectorComponentBasedOnPlane(V, Plane);
}

float UHMV::GetUpVectorComponentBasedOnPlane(FVector V, const HM3DPlane Plane)
{
    switch (Plane)
    {
        case XY: return V.Z;
        case XZ: return V.Y;
        case YZ: return V.X;
        default: return V.Z;       
    }    
}

float UHMV::GetUpVectorComponentBasedOnPlanePure(FVector V, const HM3DPlane Plane)
{
    return  GetUpVectorComponentBasedOnPlane(V, Plane);
}

float UHMV::GetRightVectorComponentBasedOnPlane(FVector V, const HM3DPlane Plane)
{
    switch (Plane)
    {
        case XY: return V.Y;
        case XZ: return V.Z;
        case YZ: return V.Z;
        default: return V.Y;       
    }    
}

float UHMV::GetRightVectorComponentBasedOnPlanePure(FVector V, const HM3DPlane Plane)
{
    return  GetRightVectorComponentBasedOnPlane(V, Plane);
}

FVector UHMV::VectorMultiplyByWorldDeltaSeconds(const UObject* WorldContextObject, FVector V)
{
    return UHM::GetWorldDeltaSeconds(WorldContextObject) * V;
}

FVector UHMV::VectorMultiplyByWorldDeltaSecondsPure(const UObject* WorldContextObject, FVector V)
{
    return VectorMultiplyByWorldDeltaSeconds(WorldContextObject, V);
}

FVector UHMV::VectorDivideByWorldDeltaSeconds(const UObject* WorldContextObject, FVector V)
{
    const float dt = UHM::GetWorldDeltaSeconds(WorldContextObject);
    return dt == 0 ? FVector().ZeroVector : V / dt;
}

float UHMV::GetAngleVectorToPlaneXY(FVector V)
{
    const float S = FMath::Sign(V.Z);
    return  S * AngleBetweenVectorsDeg(TrimVectorZ(V), V);
}

FVector UHMV::VectorDivideByWorldDeltaSecondsPure(const UObject* WorldContextObject, FVector V)
{
    return VectorDivideByWorldDeltaSeconds(WorldContextObject, V);
}

FVector UHMV::RandomVector(const float MinLimit, const float MaxLimit, const bool bNormalize)
{
    const float X = FMath::RandRange(MinLimit, MaxLimit);
    const float Y = FMath::RandRange(MinLimit, MaxLimit);
    const float Z = FMath::RandRange(MinLimit, MaxLimit);
    
    return bNormalize ? FVector(X,Y,Z).GetSafeNormal() : FVector(X,Y,Z);
}

FVector UHMV::RandomVectorPure(const float MinLimit, const float MaxLimit, const bool bNormalize)
{
    return RandomVector(MinLimit, MaxLimit, bNormalize);
}

FVector UHMV::RandomVectorShort(const float Limit, const bool bNormalize)
{
    const float NegLimit = -1 * Limit;
    return RandomVector(NegLimit, Limit, bNormalize);
}

FVector UHMV::RandomVectorShortPure(const float Limit, const bool bNormalize)
{
    return  RandomVectorShort(Limit, bNormalize);
}

FVector UHMV::VectorFromFloat(float F)
{
    return FVector(F,F,F);
}

FVector UHMV::VectorFromFloatPure(float F)
{
    return VectorFromFloat(F);
}

FVector UHMV::GetForwardRotatedUpAxis(float AngleDeg)
{
    return FVector::ForwardVector.RotateAngleAxis(AngleDeg, FVector::UpVector);
}

FVector UHMV::ReplaceVectorValue(const FVector V, const float Val, const EVectorComponents E)
{
    switch (E)
    {
        case VC_X: return FVector(Val, V.Y, V.Z);
        case VC_Y: return FVector(V.X, Val, V.Z);
        case VC_Z: return FVector(V.X, V.Y, Val);
        case VC_XY: return FVector(Val, Val, V.Z);
        case VC_XZ: return FVector(Val, V.Y, Val);
        case VC_YZ: return FVector(V.X, Val, Val);
        case VC_XYZ: return FVector(Val, Val, Val);
        default: return V;
    }

}

FVector UHMV::ReplaceVectorValuePure(FVector V, float Val, EVectorComponents E)
{
    return ReplaceVectorValue(V, Val, E);
}

FVector UHMV::ReplaceVectorValues(const FVector V, const float X, const float Y, const float Z, const bool bX, const bool bY, const bool bZ, const bool bNormalize)
{
    FVector OutV = V;
    if (bX) OutV.X = X;
    if(bY) OutV.Y = Y;
    if(bZ) OutV.Z = Z;
    return GetVectorNormalizedOptional(OutV, bNormalize);
}

FVector UHMV::ReplaceVectorValuesPure(FVector V, float X, float Y, float Z, bool bX, bool bY, bool bZ, bool bNormalize)
{
    return ReplaceVectorValues(V, X, Y, Z, bX, bY, bZ, bNormalize);
}

FVector UHMV::VectorAddValueToCurrent(FVector V, float Val, EVectorComponents E)
{
    const float F = GetVectorComponentByEnum(V, E) + Val;
    return ReplaceVectorValue(V, F, E);
}

FVector UHMV::VectorAddValueToCurrentPure(FVector V, float Val, EVectorComponents E)
{
    return VectorAddValueToCurrent(V, Val, E);
}

FVector UHMV::TrimVector(const FVector V, const bool bX, const bool bY, const bool bZ, const bool bNormalize)
{
    FVector OutV = V;
    if (bX) OutV.X = 0;
    if (bY) OutV.Y = 0;
    if (bZ) OutV.Z = 0;
    return GetVectorNormalizedOptional(OutV, bNormalize);
}

FVector UHMV::TrimVectorPure(const FVector V, const bool bX, const bool bY, const bool bZ, const bool bNormalize)
{
    return TrimVector(V, bX, bY, bZ, bNormalize);
}

FVector UHMV::TrimVectorZ(FVector V)
{
    return TrimVector(V, false, false, true);
}

FVector UHMV::TrimVectorByPlane(const FVector V, HM3DPlane Plane, const bool bNormalize)
{
    switch (Plane)
    {
        case XY: return TrimVector(V,false, false, true, bNormalize);
        case XZ: return TrimVector(V,false, true, false, bNormalize);
        case YZ: return TrimVector(V,true, false, false, bNormalize);
        default: return TrimVector(V,false, false, true, bNormalize);       
    }
}

FVector UHMV::TrimVectorByPlanePure(const FVector V, HM3DPlane Plane, const bool bNormalize)
{
    return TrimVectorByPlane(V, Plane, bNormalize);
}

FVector UHMV::TrimSmallVectorToZero(FVector V, float MinSize)
{
    return FMath::Abs(MinSize) > V.Size() ? FVector::ZeroVector : V; 
}

FVector UHMV::VectorNegateComponent(const FVector V, const bool bX, const bool bY, const bool bZ, const bool bNormalize)
{
    FVector OutV = V;
    if (bX) OutV.X = -1 * V.X;
    if (bY) OutV.Y = -1 * V.Y;
    if (bZ) OutV.Z = -1 * V.Z;
    return GetVectorNormalizedOptional(OutV, bNormalize);
}

FVector UHMV::VectorNegateComponentPure(const FVector V, const bool bX, const bool bY, const bool bZ, const bool bNormalize)
{
    return VectorNegateComponent(V, bX, bY, bZ, bNormalize);
}

FVector UHMV::VectorScaleFromFloat(const float F)
{
    const float f  = F/100.0f;
    return  FVector(f,f,f);
}

FVector UHMV::VectorScaleFromFloatPure(const float F)
{
    return VectorScaleFromFloat(F);
}

FVector UHMV::RotateVectorZAxis(FVector V, float AngleDeg)
{
    return V.RotateAngleAxis(AngleDeg, FVector::UpVector);
}

FVector UHMV::ConvertVectorToPlaneXZ(FVector V)
{
    const float X = TrimVectorZ(V).Size();
    const float Z = V.Z;
    return FVector(X, 0.0f, Z);
}

float UHMV::GetSphereRadiusFromScale(const FVector V)
{
    return V.X  * 50.0f;
}

float UHMV::GetSphereRadiusFromScalePure(const FVector V)
{
    return  GetSphereRadiusFromScale(V);
}

float UHMV::AngleBetweenVectorsDeg(const FVector V1, const FVector V2)
{
    if (HasZeroVector(V1, V2)) return 0.0f;
    const float DotProd = FVector::DotProduct(V1.GetSafeNormal(), V2.GetSafeNormal());
    return UKismetMathLibrary::DegAcos(DotProd);
}

float UHMV::AngleBetweenVectorsDegPure(const FVector V1, const FVector V2)
{
    return AngleBetweenVectorsDeg(V1, V2);
}

float UHMV::AngleBetweenVectorsRad(const FVector V1, const FVector V2)
{
    const float DegAng = AngleBetweenVectorsDeg(V1, V2);
    return FMath::DegreesToRadians(DegAng);
}

float UHMV::AngleBetweenVectorsRadPure(const FVector V1, const FVector V2)
{
    return AngleBetweenVectorsRad(V1, V2);
}

float UHMV::AngleBetweenVectorsDegOnPlane(FVector V1, FVector V2, HM3DPlane Plane)
{
    V1 = TrimVectorByPlane(V1, Plane,true);
    V2 = TrimVectorByPlane(V2, Plane,true);
    return AngleBetweenVectorsDeg(V1, V2);
}

float UHMV::AngleBetweenVectorsDegOnPlanePure(FVector V1, FVector V2, HM3DPlane Plane)
{
    return AngleBetweenVectorsDegOnPlane(V1, V2, Plane);
}

float UHMV::AngleByThreePointsDeg(const FVector P0, const FVector P1, const FVector P2)
{
    return AngleBetweenVectorsDeg(P1 - P0, P2 - P0);
}

float UHMV::AngleByThreePointsDegPure(const FVector P0, const FVector P1, const FVector P2)
{
    return AngleByThreePointsDeg(P0, P1, P2);
}

float UHMV::SignedAngleBetweenVectorsDeg(const FVector Direction, const FVector V, bool IsRightSideVector)
{
    const float Angle = AngleBetweenVectorsDeg(Direction, V);
    return IsRightSideVector ? Angle : -1 *  Angle;
}

float UHMV::SignedAngleBetweenVectorsDegPure(const FVector Direction, const FVector V, const bool IsRightSideVector)
{
    return SignedAngleBetweenVectorsDeg(Direction, V, IsRightSideVector);
}

float UHMV::SignedAngleBetweenVectorsDegOnPlane(const FVector Direction, const FVector V, const HM3DPlane Plane)
{
    const bool IsRightSide = IsRightSideVectorTowardsDirOnPlane(Direction,V,Plane);
    const FVector DirTrimmed = TrimVectorByPlane(Direction, Plane, false);
    const FVector VTrimmed = TrimVectorByPlane(V, Plane, false);
    return SignedAngleBetweenVectorsDeg(DirTrimmed, VTrimmed, IsRightSide);
}

float UHMV::SignedAngleBetweenVectorsDegOnPlanePure(const FVector Direction, const FVector V, const HM3DPlane Plane)
{
    return SignedAngleBetweenVectorsDegOnPlane(Direction, V, Plane);
}

float UHMV::Angle360BetweenVectorsDegOnPlanePure(const FVector Direction, const FVector V, HM3DPlane Plane)
{
    const float A = SignedAngleBetweenVectorsDegOnPlane(Direction, V, Plane);
    return SignedAngleTo360Deg(A);
}

float UHMV::SignedAngleBetweenVectorsDegXY(const FVector& Direction, const FVector& V)
{
    return SignedAngleBetweenVectorsDegOnPlane(Direction, V, XY);
}

float UHMV::SignedAngleVectorToWorldForwardDegXY(FVector V)
{
    return SignedAngleBetweenVectorsDegXY(V, FVector::ForwardVector);
}

float UHMV::SignedAngleWorldForwardToVectorDegXY(FVector V)
{
    return SignedAngleBetweenVectorsDegXY(FVector::ForwardVector, V);
}

float UHMV::SignedAngleVectorToPlaneXY(const FVector& V)
{
    if (V.IsNearlyZero())return 0.0f;
    return UKismetMathLibrary::DegAsin(V.Z / V.Size());
}

void UHMV::SplitVectorToDetailed(const FVector& V, float& Magnitude, float& Angle_XY, float& Angle_XZ)
{
    const float m = V.Size();
    Magnitude = m * UHM::Sign(m);
    Angle_XY = SignedAngleWorldForwardToVectorDegXY(V);
    Angle_XZ = SignedAngleVectorToPlaneXY(V);
}

FVector UHMV::GetForwardVectorFromDeltaOrientation_WorldForwardRotated_XY_XZ(FVector V1, FVector V2)
{
    float m1, xy1, xz1;
    float m2, xy2, xz2;
    SplitVectorToDetailed(V1, m1, xy1, xz1);
    SplitVectorToDetailed(V2, m2, xy2, xz2);
    const float xy = UHMR::ClampAnglesAndSumAlwaysPositive360(-xy1, xy2);
    const float xz = UHMR::ClampAnglesAndSumAlwaysPositive360(-xz1, xz2);
    return GetWorldForwardRotated_XY_XZ(xy, xz);
}

FVector UHMV::GetVectorFromDeltaOrientation_WorldForwardRotated_XY_XZ(FVector V1, FVector V2)
{
    return V2.Size() * GetForwardVectorFromDeltaOrientation_WorldForwardRotated_XY_XZ(V1, V2);
}

FVector UHMV::GetVectorRotated_XY_XZ(FVector V, float AngleXY, float AngleXZ)
{
    float m, xy, xz;
    SplitVectorToDetailed(V, m, xy, xz);
    const float XY = UHMR::ClampAnglesAndSumAlwaysPositive360(xy, AngleXY);
    const float XZ = UHMR::ClampAnglesAndSumAlwaysPositive360(xz, AngleXZ);
    return m * GetWorldForwardRotated_XY_XZ(XY, XZ);
}

FVector UHMV::GetVectorRotated_XY(FVector Dir_XY, float OwnAngleXY, float OwnAngleXZ)
{
    float m, xy, xz;
    SplitVectorToDetailed(Dir_XY, m, xy, xz);
    xy = UHMR::ClampAnglesAndSumAlwaysPositive360(xy, OwnAngleXY);
    return m * GetWorldForwardRotated_XY_XZ(xy, OwnAngleXZ);
}

FVector UHMV::GetWorldForwardRotated_XY_XZ(float AngleXY, float AngleXZ)
{
    return UHMR::GetOrientationFromWorldForwardRotated_XY_XZ(AngleXY, AngleXZ).GetForwardVector();
}

FVector UHMV::GetWorldForwardRotatedScaled_XY_XZ(float Magnitude, float AngleXY, float AngleXZ)
{
    return Magnitude * GetWorldForwardRotated_XY_XZ(AngleXY, AngleXZ);
}

FVector UHMV::RotateVectorZeroAngleCheck(const FVector& V, float Angle, const FVector& Axis)
{
    if(FMath::IsNearlyZero(Angle)) return V;
    return V.RotateAngleAxis(Angle, Axis);
}

float UHMV::SignedAngleBetweenVectorsRadOnPlane(const FVector V1, const FVector V2, const HM3DPlane Plane)
{
    const float DegAng = SignedAngleBetweenVectorsDegOnPlane(V1, V2, Plane);
    return FMath::DegreesToRadians(DegAng);
}

float UHMV::SignedAngleBetweenVectorsRadOnPlanePure(const FVector V1, const FVector V2, const HM3DPlane Plane)
{
    return SignedAngleBetweenVectorsRadOnPlane(V1, V2, Plane);
}

float UHMV::SignedAngleTo360Deg(float AngleDeg)
{
    AngleDeg = FMath::Fmod(AngleDeg, 360.0f);
    return AngleDeg >= 0 ?  AngleDeg : 360.0f - FMath::Abs(AngleDeg);
}

FVector UHMV::GetMiddleBetweenLocations(const FVector V1, const FVector V2)
{
    return (V2 - V1)/2.0f + V1;
}

FVector UHMV::GetMiddleBetweenLocationsPure(const FVector V1, const FVector V2)
{
    return GetMiddleBetweenLocations(V1, V2);
}

bool UHMV::IsLocationInRadiusFromOrigin(const FVector& Origin, const FVector& Location, const float Distance)
{
    return (Location - Origin).Size() <= Distance;
}

bool UHMV::IsLocationInRadiusFromOriginPure(const FVector& Origin, const FVector& Location, float Distance)
{
    return IsLocationInRadiusFromOrigin(Origin, Location, Distance);
}

bool UHMV::IsLocationInRadiusFromOriginInPlane(const FVector& Origin, const FVector& Location, float Distance, const HM3DPlane Plane)
{
    return TrimVectorByPlane(Location - Origin, Plane).Size() <= Distance;
}

bool UHMV::IsLocationInRadiusFromInOriginInPlanePure(const FVector& Origin, const FVector& Location, const float Distance, const HM3DPlane Plane)
{
    return IsLocationInRadiusFromOriginInPlane(Origin, Location, Distance, Plane);
}

FVector UHMV::GetPerpendicularLocationFromPointToLine(const FVector Origin, const FVector V1, const FVector V2)
{
    const FVector OriginToV1 =  Origin - V1;
    const FVector LineNormalized = (V2 - V1).GetSafeNormal();
    
    if(OriginToV1.IsZero() || LineNormalized.IsZero()) return V1;
    
    const FVector ProjectionEndPoint = UKismetMathLibrary::ProjectVectorOnToVector(OriginToV1, LineNormalized);
    return ProjectionEndPoint + V1;
}

FVector UHMV::GetPerpendicularLocationFromPointToLinePure(const FVector Origin, const FVector V1, const FVector V2)
{
    return GetPerpendicularLocationFromPointToLine(Origin, V1, V2);
}

FVector UHMV::GetPerpendicularLocationFromPointToLineWithDir(const FVector Origin, const FVector Direction, const FVector PointOnLine)
{
    const FVector Far = 1000 * Direction + PointOnLine;
    return GetPerpendicularLocationFromPointToLinePure(Origin, PointOnLine, Far);
}

FVector UHMV::GetPerpendicularLocationFromPointToLineWithDirPure(const FVector Origin, const FVector Direction, const FVector PointOnLine)
{
    return GetPerpendicularLocationFromPointToLineWithDir(Origin, Direction, PointOnLine);
}

FVector UHMV::GetLocationOfPerpendicularToDirectionThroughOtherLocation(FVector Direction, FVector Origin, FVector OtherLocation)
{
    return OtherLocation + (Origin - OtherLocation).ProjectOnToNormal(Direction.GetSafeNormal());
}

FVector UHMV::GetLocationOfPerpendicularToDirectionThroughOtherLocationPure(FVector Direction, FVector Origin,
    FVector OtherLocation)
{
    return GetLocationOfPerpendicularToDirectionThroughOtherLocation(Direction, Origin, OtherLocation);
}

FVector UHMV::GetWorldLocationFromDirectionAndDistance(const FVector StartLocation, const FVector Direction, const float Distance)
{
    return StartLocation + Direction.GetSafeNormal() * Distance;
}

FVector UHMV::GetWorldLocationFromDirectionAndDistancePure(const FVector StartLocation, const FVector Direction, const float Distance)
{
    return GetWorldLocationFromDirectionAndDistance(StartLocation, Direction, Distance);
}

FVector UHMV::LerpVector(const FVector& A, const FVector& B, float Alpha, float Tolerance)
{
    if(A.Equals(B, Tolerance)) return  A;
    if(FMath::IsNearlyEqual(Alpha, 0.0f, Tolerance)) return A;
    if(FMath::IsNearlyEqual(Alpha, 1.0f, Tolerance)) return B;
    return UKismetMathLibrary::VLerp(A, B, Alpha);
}

FVector UHMV::LerpVectorPure(const FVector& A, const FVector& B, float Alpha, float Tolerance)
{
    return LerpVector(A, B, Alpha, Tolerance);
}

FVector UHMV::ScaleRadiusVector(const FVector& Origin, const FVector& InLocation, const float Multiplier)
{
    return Origin + Multiplier * (InLocation - Origin);
}

FVector UHMV::ScaleRadiusVectorPure(const FVector& Origin, const FVector& InLocation, const float Multiplier)
{
    return ScaleRadiusVector(Origin, InLocation, Multiplier);
}

bool UHMV::IsLocationNotFarThanRadiusVectorFromTarget(const FVector Center, const FVector RadiusPoint, const FVector Location)
{
    const FVector R = RadiusPoint - Center;
    const FVector ThisToTarget = Center - Location;    
    return ThisToTarget.Size() <=  R.Size() ? true : false; 
}

bool UHMV::IsLocationNotFarThanRadiusVectorFromTargetPure(const FVector WTarget, const FVector WRadiusPoint, const FVector ThisLocation)
{
    return IsLocationNotFarThanRadiusVectorFromTarget(WTarget, WRadiusPoint, ThisLocation);
}

FVector UHMV::ConvertVectorToSameBasisRotatedAroundNormal(const FVector TargetForward, const FVector V, const HM3DPlane Plane)
{
    const FVector ForwardVector = GetForwardVectorBasedOnPlane(Plane);
    const FVector UpVector = GetUpVectorBasedOnPlane(Plane);
    const float Angle = SignedAngleBetweenVectorsDegOnPlane(ForwardVector, TargetForward, Plane);
    return V.RotateAngleAxis(Angle, UpVector);    
}

FVector UHMV::ConvertVectorToSameBasisRotatedAroundNormalPure(const FVector TargetForward, const FVector V, HM3DPlane Plane)
{
    return ConvertVectorToSameBasisRotatedAroundNormal(TargetForward, V, Plane);
}

FVector UHMV::ConvertVectorToOtherBasisPreserveRelativityOnPlane(const FVector TargetForward, const FVector V, const HM3DPlane Plane)
{
    const FVector LocalUpVector = GetUpVectorBasedOnPlane(Plane);
    const FVector LocalRightVector = GetRightVectorBasedOnPlane(Plane);

    const float AngleForwardToUp = AngleBetweenVectorsDeg(TargetForward, LocalUpVector);
    FVector TargetForwardProjection = TrimVectorByPlane(TargetForward,XY, true);
    
    if (AngleForwardToUp == 0)
    {
        TargetForwardProjection = UKismetMathLibrary::RotateAngleAxis(TargetForwardProjection, 90, LocalRightVector);
        TargetForwardProjection.Normalize();
    }

    FVector RightVectorProjection = UKismetMathLibrary::RotateAngleAxis(TargetForwardProjection, 90, LocalUpVector);
    RightVectorProjection.Normalize();

    return  V.X * TargetForwardProjection + V.Y * RightVectorProjection + V.Z * LocalUpVector;
}

FVector UHMV::ConvertVectorToOtherBasisPreserveRelativityOnPlanePure(const FVector TargetForward, const FVector V, const HM3DPlane Plane)
{
    return ConvertVectorToOtherBasisPreserveRelativityOnPlane(TargetForward, V, Plane);
}

FVector UHMV::GetLocationOnDistanceFromVectorEnd(const FVector Start, const FVector End, const float Distance)
{
    const FVector V = Distance * (Start - End).GetSafeNormal(); 
    return End + V;
}

FVector UHMV::GetLocationOnDistanceFromVectorEndPure(const FVector Start, const FVector End, float Distance)
{
    return GetLocationOnDistanceFromVectorEnd(Start,End,Distance);
}

void UHMV::CalculateRightTriangleFromHypoAndNormal(FVector HypEndAdjacent, FVector HypEndOpposite, FVector AdjacentNormal, FVector& PerpendicularPoint, FVector &AjacentSide,  FVector& OppositeSide)
{
    const FVector Hypotenuse = HypEndOpposite - HypEndAdjacent;
    const int Angle = AngleBetweenVectorsDeg(AdjacentNormal, Hypotenuse.GetSafeNormal());

    const float HypotenuseSize = Hypotenuse.Size();
    const float NormalComp = HypotenuseSize * UKismetMathLibrary::DegCos(Angle);

    PerpendicularPoint = HypEndAdjacent + AdjacentNormal * NormalComp;

    AjacentSide = PerpendicularPoint - HypEndAdjacent;
    OppositeSide = HypEndOpposite - PerpendicularPoint;
}

void UHMV::CalculateRightTriangleFromHypoAndNormalPure(FVector HypEndAdjacent, FVector HypEndOpposite, FVector AdjacentNormal, FVector& PerpendicularPoint, FVector &AjacentSide,  FVector& OppositeSide)
{
    CalculateRightTriangleFromHypoAndNormal(HypEndAdjacent, HypEndOpposite, AdjacentNormal, PerpendicularPoint, AjacentSide, OppositeSide);
}

void UHMV::CalculateVectorProjectionComponentsOntoNormal(FVector Normal, FVector V, FVector &TangentialComp, FVector &PerpendicularComp)
{
    const float VSize = V.Size();
    float Angle = AngleBetweenVectorsDeg(Normal, V);
    int TangentSign = 1;
    if(Angle >= 90.0f)
    {
        Angle = 180.0f - Angle;
        TangentSign = -1;
    }
    const float Cos = UKismetMathLibrary::DegCos(Angle);
    TangentialComp = TangentSign * Cos * VSize * Normal;
    PerpendicularComp = TangentSign * (TangentialComp - V);
}

void UHMV::CalculateVectorProjectionComponentsOntoNormalPure(FVector Normal, FVector V, FVector &TangentialComp, FVector &PerpendicularComp)
{
    CalculateVectorProjectionComponentsOntoNormal(Normal, V, TangentialComp, PerpendicularComp);
}

FVector UHMV::RemoveProjectionFromVector(FVector Direction, FVector V)
{
    return  V - V.ProjectOnToNormal(Direction);
}

FVector UHMV::RemoveProjectionFromVectorPure(FVector Direction, FVector V)
{
    return RemoveProjectionFromVector(Direction, V);
}

bool UHMV::GetTriangleVertexLayingOnLineFromDefinedVectorPlaneXY(FVector Start, FVector End, FVector LineP1, FVector LineP2, FVector& OutV, float& RotAngle)
{
    const FVector V = End - Start;
    const FVector Line = LineP2 - LineP1;
    const FVector Perp = GetPerpendicularLocationFromPointToLine(Start, LineP1, LineP2);
    const FVector StartToPerp = Perp - Start;
    const float SizeV = V.Size();
    const float SizePerp = StartToPerp.Size();
    
    if((SizeV >= SizePerp) && SizeV > 0)
    {
        const float A1 = AngleBetweenVectorsDeg(V, StartToPerp);
        const float B = UKismetMathLibrary::DegAsin(SizePerp / SizeV);
        RotAngle = 90.0f - (A1 + B);
        RotAngle = FMath::Abs(RotAngle);

        SetRotationAngleSignInPlane(Line, V, RotAngle, XY);
        
        OutV = V.RotateAngleAxis(RotAngle, FVector::UpVector) + Start;
            
        return true;
    }
    return false;
}

FVector UHMV::GetVectorTrimmedXY(FVector V, bool DoTrim)
{
    return DoTrim ? TrimVectorByPlane(V, XY) : V;
}

FVector UHMV::GetVectorTrimmedXY(const bool DoTrim, const bool bNormalized, FVector V)
{
    return DoTrim ? TrimVectorByPlane(V, XY, bNormalized) : GetVectorNormalizedOptional(V, bNormalized);
}

FVector UHMV::GetVectorNormalizedOptional(const FVector& V, bool bN)
{
    return bN ? V.GetSafeNormal() : V;
}

void UHMV::SetRotationAngleSignInPlane(FVector RefDir, FVector V, float& A, HM3DPlane Plane)
{
    if (SignedAngleBetweenVectorsDegOnPlane(RefDir, V, Plane) > 0)
    {
        A *= -1;
    }
}

void UHMV::SetRotationAngleSignInPlane(FVector RefDir, FVector V, float InA, float& A, HM3DPlane Plane)
{
    A = InA;
    SetRotationAngleSignInPlane(RefDir, V, A, Plane);
}

bool UHMV::IsPointBelongsToAngleOnPlane(FVector Center, FVector Point, FVector A1, FVector A2, HM3DPlane Plane)
{
    Center = TrimVectorByPlane(Center, Plane);
    Point = TrimVectorByPlane(Point, Plane);

    A1 = TrimVectorByPlane(A1, Plane);
    A2 = TrimVectorByPlane(A2, Plane);

    const FVector Forward = GetForwardVectorBasedOnPlane(Plane);
    const float Angle1 = Angle360BetweenVectorsDegOnPlanePure(Forward, A1 - Center, Plane);
    const float Angle2 = Angle360BetweenVectorsDegOnPlanePure(Forward, A2 - Center, Plane);

    if(!FMath::IsNearlyEqual(Angle1, Angle2))
    {
        const FVector ToTarget = TrimVectorByPlane(Point - Center, Plane);

        const float Min = FMath::Min(Angle1, Angle2);
        const float Max = FMath::Max(Angle1, Angle2);
        const float Target = Angle360BetweenVectorsDegOnPlanePure(Forward, ToTarget, Plane);

        const float Delta = Max - Min;
        const bool  DeltaLess180 = Delta < 180.0f;
        
        return DeltaLess180 ? Target >= Min && Target <= Max : Target <= Min || Target >= Max;
    }

    return false;
}

bool UHMV::IsPointBelongsToAngleOnPlaneCommon(FVector Center, FVector Point, FVector BisectorEndFromCenter, float PosSectorAngleDegAbs, float NegSectorAngleDegAbs, HM3DPlane Plane)
{
    const FVector Bisector = TrimVectorByPlane(BisectorEndFromCenter - Center, Plane);

    if(!Bisector.IsZero())
    {
        const FVector Up = GetUpVectorBasedOnPlane(Plane);
        const FVector A1 = Bisector.RotateAngleAxis(PosSectorAngleDegAbs, Up) + Center;
        const FVector A2 = Bisector.RotateAngleAxis(NegSectorAngleDegAbs, Up) + Center;
        
        return IsPointBelongsToAngleOnPlane(Center, Point, A1, A2, Plane);
    }
    return false;
}

bool UHMV::IsPointBelongsToSectorOnPlane(FVector Center, FVector Point, FVector BisectorEndFromCenter, float HalfSectorAngle, HM3DPlane Plane)
{
    return IsPointBelongsToAngleOnPlaneCommon(Center, Point, BisectorEndFromCenter, HalfSectorAngle, -HalfSectorAngle, Plane);
}

bool UHMV::IsVectorBetweenVectorsOnPlane(FVector V, FVector A, FVector B, FVector Mid, HM3DPlane Plane, float &AngleToA, float &AngleToB)
{
    V = TrimVectorByPlane(V, Plane, true);
    A = TrimVectorByPlane(A, Plane, true);
    B = TrimVectorByPlane(B, Plane, true);

    const float AngleMaxSigned = SignedAngleBetweenVectorsDegOnPlane(A, B, Plane);
    const float HalfAbsMaxAngle = 0.5f * FMath::Abs(AngleMaxSigned);

    const float AngleToMid = AngleBetweenVectorsDeg(V, Mid);
    
    AngleToA = AngleBetweenVectorsDeg(V, A);
    AngleToB = AngleBetweenVectorsDeg(V, B);

    const float MinAngle = AngleToA < AngleToB ? AngleToA : AngleToB;

    const float Sum = MinAngle + AngleToMid + HalfAbsMaxAngle;

    // still has a problem when vector is over the mid -> we should check which angle is greater AtoMid or BtoMid
    
    return FMath::IsNearlyEqual(Sum, FMath::Abs(AngleMaxSigned), 0.01f); 
}

bool UHMV::IsVectorBetweenVectorsOnPlaneXY(FVector V, FVector A, FVector B, FVector Mid, float &AngleToA, float &AngleToB)
{
    return IsVectorBetweenVectorsOnPlane(V, A,B, Mid, XY, AngleToA, AngleToB);
}

bool UHMV::IsVectorBetweenVectorsOnPlaneXY(FVector V, FVector A, FVector B, FVector Mid)
{
    float a1, a2;
    return IsVectorBetweenVectorsOnPlane(V, A,B, Mid, XY, a1, a2);
}

FVector UHMV::ClampVectorToMaxSize(FVector V, float Size)
{
    Size = FMath::Abs(Size);
    return V.Size() > Size ? V.GetSafeNormal() * Size : V;
}

bool UHMV::GetLineIntersectionsWithSphereFromPAndNormal(FVector P, FVector N, FVector SC, float SR, FVector& Res1, FVector& Res2)
{
    if(N.IsZero() || N.ContainsNaN()) return false;
    const FVector PP = P + N.GetSafeNormal();
    return GetLineIntersectionsWithSphereFromTwoPoints(P, PP, SC, SR, Res1, Res2);
}

bool UHMV::GetLineIntersectionsWithSphereFromTwoPoints(FVector P1, FVector P2, FVector SC, float SR, FVector& Res1, FVector& Res2)
{
    // http://paulbourke.net/geometry/circlesphere/raysphere.c
    // http://paulbourke.net/geometry/circlesphere/
    
    const FVector dP = P2-P1;
    const FVector _V1 = dP * (P1 - SC);
    const FVector _V2 = SC * P1;

    const float a = dP.SizeSquared();
    const float b = 2.0f * (_V1.X + _V1.Y + _V1.Z);
    const float c = SC.SizeSquared() + P1.SizeSquared() - SR * SR - 2.0f * (_V2.X + _V2.Y + _V2.Z);
    const float Discriminant = b*b - 4.0f * a * c;

    const bool NotValidA = FMath::IsNearlyZero(a, 0.0001f) && a < 0.0f;
    if(NotValidA || Discriminant < 0.0f) return false;

    const float SqRoot = FMath::Sqrt(Discriminant);
    const float Div =  1.0f / (2.0f * a);

    const float r1 = (-b + SqRoot) * Div;
    const float r2 = (-b - SqRoot) * Div;

    Res1 = P1 + r1 * dP;
    Res2 = P1 + r2 * dP;

    const FVector D1 = Res1 - P1;
    const FVector D2 = Res2 - P1;

    if(D1.Size() > D2.Size())
    {
        const FVector T1 = Res1; 
        const FVector T2 = Res2; 
        Res1 = T2;
        Res2 = T1;
    }
    return true;
}

FVector UHMV::GetNearestLocation(const TArray<FVector>& Locations, FVector Target)
{
    float MinDistance = MAX_FLOAT;
    FVector V;
    
    for (auto Location : Locations)
    {
        const float Distance = (Target - Location).Size();
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            V = Location;
        }
    }
    
    return V;
}

bool UHMV::IsAngleBetweenVectorsInRange(FVector A, FVector B, float AngleMin, float AngleMax, float Tolerance)
{
    const float Angle = AngleBetweenVectorsDeg(A, B);
    return UHM::IsFloatInRange(Angle, AngleMin - Tolerance, AngleMax + Tolerance);
}

bool UHMV::LineToLineIntersection(const FVector& A1, const FVector& B1, const FVector& A2, const FVector& B2, FVector& Intersection)
{
    const FVector da = B1 - A1;
    const FVector db = B2 - A2;
    const FVector dc = A2 - A1;

    const FVector crossDaDb = FVector::CrossProduct(da, db);
    const float prod = crossDaDb.X * crossDaDb.X + crossDaDb.Y * crossDaDb.Y + crossDaDb.Z * crossDaDb.Z;

    const bool W1 = FMath::IsNearlyZero(prod);
    const bool W2 = !FMath::IsNearlyZero(FVector::DotProduct(dc,crossDaDb));
    if(W1 || W2) return false;

    const float res = FVector::DotProduct(FVector::CrossProduct(dc, db), FVector::CrossProduct(da, db)) / prod;

    Intersection = A1 + da * FVector(res, res, res);

    const FVector fromAToIntersectPoint = Intersection - A1;
    const FVector fromBToIntersectPoint = Intersection - B1;
    const FVector toAToIntersectPoint = Intersection - A2;
    const FVector toBToIntersectPoint = Intersection - B2;

    const bool T1 = FVector::DotProduct(fromAToIntersectPoint, fromBToIntersectPoint) <= 0.0f;
    const bool T2 = FVector::DotProduct(toAToIntersectPoint, toBToIntersectPoint) <= 0.0f;
    return T1 && T2;
}

float UHMV::GetSignedAngleForDirectionToLocationFromLocationDegXY(const FVector& Origin, const FVector& Target, const FVector& Dir)
{
    return SignedAngleBetweenVectorsDegXY(Target - Origin, Dir);
}

bool UHMV::VectorsMapMinMaxComponent(FVector A, FVector B, float& Min, float& Max, EVectorComponents Component)
{
    if(Component == VC_X)
    {
        UHM::MapMinMax(A.X, B.X, Min, Max);
        return true;
    }
    if(Component == VC_Y)
    {
        UHM::MapMinMax(A.Y, B.Y, Min, Max);
        return true;
    }
    if(Component == VC_Z)
    {
        UHM::MapMinMax(A.Z, B.Z, Min, Max);
        return true;
    }
    return false;
}

bool UHMV::VectorsMapMinMaxComponent(FVector A, FVector B, EVectorComponents Component, FFloatMinMax& Out)
{
    return VectorsMapMinMaxComponent(A, B, Out.Min, Out.Max, Component);
}

FFloatMinMax UHMV::VectorsMapMinMaxComponent(FVector A, FVector B, EVectorComponents Component)
{
    FFloatMinMax Out;
    VectorsMapMinMaxComponent(A, B, Component, Out);
    return Out;
}
