#pragma once

#include "CoreMinimal.h"

static constexpr float Pi = 3.14159265359f;

static constexpr float TurnToRad = 2.0f * Pi;
static constexpr float RadToTurn = 1.0f / TurnToRad;

static float SECONDS_IN_MINUTE = 60.0f;
static float SECONDS_IN_HOUR = SECONDS_IN_MINUTE * 60.0f;

static float RadSecToRpM = RadToTurn * SECONDS_IN_MINUTE;
static float RpMToRadSec = 1.0f / RadSecToRpM;

static float M_IN_KM = 1000.0f;
static float CM_IN_M = 100.0f;
static float CM_IN_KM = M_IN_KM * CM_IN_M;
static float CmToM = 1.0f / CM_IN_M;
static float Cm3ToM3 = CM_IN_M * CM_IN_M * CM_IN_M;
static float M3ToCm3 = 1.0f / Cm3ToM3;

static float MSecToKmHour = SECONDS_IN_HOUR / M_IN_KM;
static float CmSecToKmHour = SECONDS_IN_HOUR / CM_IN_KM;
static float KmHourToMSec =  1.0f / MSecToKmHour;
static float KmHourToCmSec = 1.0f / CmSecToKmHour;