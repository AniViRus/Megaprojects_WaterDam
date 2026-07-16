

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "AVRPBuildableWaterTower.generated.h"

/**
 * Water Towers which produce water in big amounts based on amount of currently built instances
 */
UCLASS()
class MEGAPROJECTS_WATERDAM_API AAVRPBuildableWaterTower : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AAVRPBuildableWaterTower();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual void Factory_TickProducing(float dt) override;
	virtual void Factory_PushPipeOutput_Implementation(float dt) override;
	// End AFGBuildableFactory interface

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFGItemDescriptor> extractedResource;
	UPROPERTY()
	TArray<TObjectPtr<UFGPipeConnectionComponent>> mPipeOutputConnections;
	UPROPERTY()
	TObjectPtr<UFGInventoryComponent> mOutputInventory;
	UPROPERTY(EditDefaultsOnly)
	float mCycleTime;
	UPROPERTY(EditDefaultsOnly)
	float mItemsPerTower;
	UPROPERTY()
	float mTowerAmount;
	float mCurrentExtractProgress;
};
