#include "AVRPWaterTowerHologram.h"

bool AAVRPWaterTowerHologram::IsValidHitResult(const FHitResult& hitResult) const
{
	bool canBuild;
	GetTowerCount(canBuild);
	return canBuild && Super::IsValidHitResult(hitResult);
}

void AAVRPWaterTowerHologram::OnInvalidHitResult()
{
	bool canBuild;
	GetTowerCount(canBuild);
	if (!canBuild) {
		AddConstructDisqualifier(UWaterDamCD_LimitReached::StaticClass());
		return;
	}
	Super::OnInvalidHitResult();
}

TArray<FItemAmount> AAVRPWaterTowerHologram::GetBaseCost() const
{
	auto cost = UFGRecipe::GetIngredients(this, GetRecipe());
	cost.Add(GetAddedCost());
	return cost;
}
