#pragma once

#include "CoreMinimal.h"
#include "FGFluidIntegrantInterface.h"
#include "Buildables/FGBuildableCheatFluidSpawner.h"
#include "AVRPBuildableWaterTower.generated.h"

/**
 * Water Towers which produce water in big amounts based on amount of currently built instances
 */
UCLASS()
class MEGAPROJECTS_WATERDAM_API AAVRPBuildableWaterTower : public AFGBuildableCheatFluidSpawner
{
	GENERATED_BODY()
public:
	AAVRPBuildableWaterTower();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGBuildableFactory interface
	virtual void Factory_Tick(float dt) override;
	virtual void Factory_TickProducing(float dt) override;
	// End AFGBuildableFactory interface

	// Begin Fluid Integrant Interface
	virtual TArray< class UFGPipeConnectionComponent* > GetPipeConnections() override;
	// End Fluid Integrant Interface

	UFUNCTION(BlueprintCallable)
	void SetTowerAmount(int amount);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UFGItemDescriptor> extractedResource;
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UFGPipeConnectionComponent>> mPipeOutputConnections;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float mItemsPerTower;
	UPROPERTY(BlueprintReadOnly)
	float mTowerAmount;
private:
	UPROPERTY(EditDefaultsOnly)
	float mAdditionalPressure;
	UPROPERTY()
	float mSpawnedLastTick;
};
