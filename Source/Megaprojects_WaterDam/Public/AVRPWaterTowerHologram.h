#pragma once

#include "CoreMinimal.h"
#include "FGConstructDisqualifier.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "Hologram/FGFactoryHologram.h"
#include "AVRPWaterTowerHologram.generated.h"


#define LOCTEXT_NAMESPACE "Megaprojects_WaterDamLocnamespace"
UCLASS()
class MEGAPROJECTS_WATERDAM_API UWaterDamCD_LimitReached : public UFGConstructDisqualifier
{
	GENERATED_BODY()
public:
	UWaterDamCD_LimitReached()
	{
		mDisqfualifyingText = LOCTEXT("WaterDamCD_LimitReached", "Water Tower limit has been reached!");
	}
};

#undef LOCTEXT_NAMESPACE
/**
 * Water Tower hologram to prevent building more towers than it is currently allowed
 */
UCLASS()
class MEGAPROJECTS_WATERDAM_API AAVRPWaterTowerHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
public:
	//Begin AFGHologram interface
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual void OnInvalidHitResult() override;
	virtual TArray< FItemAmount > GetBaseCost() const override;
	//End AFGHologram interface
	UFUNCTION(BlueprintImplementableEvent)
	int GetTowerCount(bool &canBuild) const;
	UFUNCTION(BlueprintImplementableEvent)
	FItemAmount GetAddedCost() const;
};
