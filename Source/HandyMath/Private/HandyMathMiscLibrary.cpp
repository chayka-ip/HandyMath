// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyMathMiscLibrary.h"

FPlane UHandyMathMiscLibrary::PlaneFromPoints(FVector A, FVector B, FVector C)
{
    return FPlane(A, B, C);
}
