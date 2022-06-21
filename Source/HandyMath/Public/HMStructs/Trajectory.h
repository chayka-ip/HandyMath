#pragma once

#include "CoreMinimal.h"
#include "Trajectory.generated.h"

USTRUCT(BlueprintType)
struct HANDYMATH_API FTrajectory
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> Points = {};

	bool IsEmpty() const {return Points.Num() == 0;}
	bool IsNotEmpty() const {return !IsEmpty();}
	

public:
	FVector GetClosestPointOfTrajectoryRelToPoint(FVector Location, bool bXY) const;
};