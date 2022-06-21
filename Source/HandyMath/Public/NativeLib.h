#pragma once

static float VERY_SMALL_POS = 0.0000001f;
static constexpr float MAX_FLOAT = TNumericLimits< float >::Max();

namespace Native
{
	template<typename  T>
	static T SafeDivision(T A, T B)
	{
		if(FMath::IsNearlyZero(B)) return INFINITY;
		return A/B;
	}

	template<typename  T>
	static T FClampMaxAbsSigned(T V, T MaxAbs)
	{
		return FMath::Clamp(V, -MaxAbs, MaxAbs);
	}

	template<typename  T>
	static T FTrimMinAbsSigned(T V, T MinAbs)
	{
		return FMath::Abs(V) > MinAbs ? V : 0;
	}

	template<typename  T>
	static  void ArrayRemoveItems(TArray<T>& A, const TArray<T>& ItemsToRemove)
	{
		for (auto Element : ItemsToRemove)
		{
			A.Remove(Element);
		}
	}

	template<typename T>
	static void AddToArrayAsInverted(TArray<T> &Destination, const TArray<T> &ArrayToAdd)
	{
		const int Num = ArrayToAdd.Num() - 1;
		for (int i = Num; i >= 0; --i)
		{
			Destination.Add(ArrayToAdd[i]);
		}
	}

	template<typename T>
	static void ShuffleArray(TArray<T> &A)
	{
		if (A.Num() == 0) return;
		
		TArray<T> TmpArray;

		while (true)
		{
			const int Num = A.Num();
			if (Num == 0) break;

			int Index = FMath::RandRange(0, Num - 1);
			auto Elem = A[Index];
			TmpArray.Add(Elem);
			A.RemoveAt(Index);
		}
		A = TmpArray;		
	}

	template<typename T>
	static T* ArrayGetElementByIndexInBounds(int Index, TArray<T> &Array)
	{
		if (Index < 0) Index = 0;
		const int Length = Array.Num();
		if(Length > 0)
		{
			Index = Index < Length ? Index : Length - 1;
			return &Array[Index];
		}
		return nullptr;
	}
	
	template<typename T>
	static T* ArrayGetElementInBoundsSafe(int Index, TArray<T> &Array, T DefaultReturn)
	{
		auto P = ArrayGetElementByIndexInBounds(Index, Array);
		return P ? P : &DefaultReturn;
	}
	
	template<typename T>
	static void ArrayRemoveItemsFromStart(TArray<T>& Array, int NumItems)
	{
		const int L  = Array.Num();
		if(NumItems >= L)
		{
			Array.Empty();
			return;
		}
		NumItems = FMath::Clamp(NumItems, 0, L);
		for (int i = 0; i < NumItems; ++i) Array.RemoveAt(0);
	}

	template<typename T>
	static TArray<T> ArrayGetSliceFromStart(const TArray<T>& Array, int LastIndex)
	{
		TArray<T> Out;
		const int Max = FMath::Clamp(LastIndex + 1, 0, Array.Num());
		for (int i = 0; i < Max; ++i)  Out.Add(Array[i]);
		return Out;
	}

	template<typename T>
	static void GetArrayMinMax(const TArray<T>& A, T& Min, T& Max)
	{
		check(A.Num() > 0)

		Min = A[0];
		Max = A[0];
		
		for (const auto V : A)
		{
			if(V < Min) Min = V;
			if(V > Max) Max = V;
		}
	}
	
	template<typename T>
	static T* ArrayGetRandomElementPtr(TArray<T>& A)
	{
		const int Num = A.Num();
		if(Num < 0) return nullptr;
		int Index = 0;
		if(Num > 1) Index = FMath::RandRange(0, Num - 1);
		return &A[Index];
	}

	template<typename T>
	void Swap(T& A, T& B)
	{
		T Tmp = A;
		A = B;
		B = Tmp;
	}
};
