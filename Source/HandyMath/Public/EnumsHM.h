#pragma once

#include "CoreMinimal.h"

UENUM()
enum HM3DPlane
{
    XY   UMETA(DisplayName = "XY"),
    XZ   UMETA(DisplayName = "XZ"),
    YZ   UMETA(DisplayName = "YZ"),
 };

UENUM()
enum EVectorComponents
{
    VC_X UMETA(DisplayName = "X"),
    VC_Y UMETA(DisplayName = "Y"),
    VC_Z UMETA(DisplayName = "Z"),
    VC_XY UMETA(DisplayName = "XY"),
    VC_XZ UMETA(DisplayName = "XZ"),
    VC_YZ UMETA(DisplayName = "YZ"),
    VC_XYZ UMETA(DisplayName = "XYZ"),
};

UENUM()
enum EFloatPrecision
{
    // equals num digits after point
	
    Tens = -2 UMETA(DisplayName = "Tens"),
    Ones = -1 UMETA(DisplayName = "Ones"),
    Tenth = 1 UMETA(DisplayName = "Tenth"),
    Hundredths = 2 UMETA(DisplayName = "Hundredths"),
    TenThousandths = 3 UMETA(DisplayName = "Ten Thousandths"),
    HundredThousandths = 4 UMETA(DisplayName = "Hundred Thousandths"),
    Millionths = 5 UMETA(DisplayName = "Millionths"), 
};


UENUM(BlueprintType)
enum EFST_FloatSearchType
{
    EFST_Less,
    EFST_Equal,
    EFST_Greater,
};

UENUM(BlueprintType)
enum EVST_VectorValueType
{
    EVST_Magnitude,
    EVST_AngleXY,
    EVST_AngleXZ,
};

UENUM(BlueprintType)
enum ECPVT_VelocityType
{
    ECPVT_Linear,
    ECPVT_Angular,
};