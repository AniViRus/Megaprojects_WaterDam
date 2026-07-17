#pragma once

#include "CoreMinimal.h"
#include "FGFluidIntegrantInterface.h"
#include "Buildables/FGBuildableFactory.h"
#include "AVRPBuildableWaterTower.generated.h"

/**
 * Water Towers which produce water in big amounts based on amount of currently built instances
 */
UCLASS()
class MEGAPROJECTS_WATERDAM_API AAVRPBuildableWaterTower : public AFGBuildableFactory, public IFGFluidIntegrantInterface
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

	// Begin Fluid Integrant Interface
	virtual FFluidBox* GetFluidBox() override;
	virtual TArray< class UFGPipeConnectionComponent* > GetPipeConnections() override;
	// End Fluid Integrant Interface

protected:
	UPROPERTY(SaveGame)
	FFluidBox mFluidBox;
	UPROPERTY(EditDefaultsOnly, Category = "Pipeline Attachment")
	float mFluidBoxVolume;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UFGItemDescriptor> extractedResource;
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UFGPipeConnectionComponent>> mPipeOutputConnections;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UFGInventoryComponent> mOutputInventory;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float mCycleTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float mItemsPerTower;
	UPROPERTY(BlueprintReadOnly)
	float mTowerAmount;
	float mCurrentExtractProgress;
private:
	UPROPERTY()
	float mFluidMovedLastProducingTick;
	UPROPERTY(EditDefaultsOnly)
	float additionalPressure;
};
