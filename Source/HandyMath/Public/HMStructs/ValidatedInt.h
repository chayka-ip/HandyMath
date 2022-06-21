#pragma once

#include "CoreMinimal.h"
#include "ValidatedInt.generated.h"

USTRUCT()
struct FValidatedIntMinMax
{
    GENERATED_BODY()

    int InvalidValue = -1;
    int Min = InvalidValue;
    int Max = InvalidValue;

public:
    void SetInvalidValue(int V)
    {
        InvalidValue = V;
        SetMin(V);
        SetMax(V);
    }
    void SetMin(int V){Min = V;}
    void SetMax(int V){Max = V;}

    int GetMin() const {return Min;}
    int GetMax() const {return Max;}
    
public:
    bool IsValidValue(int V) const {return V != InvalidValue;}
    
    bool IsValidMin() const {return IsValidValue(Min);}
    bool IsValidMax() const {return IsValidValue(Max);}
    bool AreValidBoth() const {return IsValidMin() && IsValidMax();}

    bool IsInvalidMin() const {return !IsValidMin();}
    bool IsInvalidMax() const {return !IsValidMax();}
    bool AreInvalidBoth() const {return !AreValidBoth();}

    bool IsValidMinOnly() const {return IsValidMin() && IsInvalidMax();}
};
