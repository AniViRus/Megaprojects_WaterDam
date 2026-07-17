#include "AVRPBuildableWaterTower.h"
#include "FGPipeConnectionComponent.h"

AAVRPBuildableWaterTower::AAVRPBuildableWaterTower()
{
	mOutputInventory = CreateDefaultSubobject<UFGInventoryComponent>(TEXT("OutputInventory"));
	mTowerAmount = 1;
}

void AAVRPBuildableWaterTower::BeginPlay()
{
	Super::BeginPlay();
	if (!HasAuthority()) return;
	mTowerAmount = 1;
	mOutputInventory->SetAllowedItemOnIndex(0, extractedResource);
	mOutputInventory->AddArbitrarySlotSize(0, UFGItemDescriptor::GetStackSize(extractedResource) * mTowerAmount); //Temp
	ForEachComponent<UFGPipeConnectionComponent>(true, [&](UFGPipeConnectionComponent* Conn) {
		if (Conn->GetPipeConnectionType() == EPipeConnectionType::PCT_PRODUCER) {
		}
		mPipeOutputConnections.Add(Conn);
		Conn->SetInventoryAccessIndex(0);
		});
}

bool AAVRPBuildableWaterTower::CanProduce_Implementation() const
{
	return Super::CanProduce_Implementation() && mOutputInventory->HasEnoughSpaceForStack(FInventoryStack(mItemsPerTower * mTowerAmount, extractedResource));
}

void AAVRPBuildableWaterTower::Factory_TickProducing(float dt)
{
	Super::Factory_TickProducing(dt);
	mCurrentExtractProgress += dt / mCycleTime;
	while (mCurrentExtractProgress >= 1) {
		FInventoryStack stack;
		mOutputInventory->GetStackFromIndex(0, stack);
		int amount = FMath::Min(mItemsPerTower * mTowerAmount, mOutputInventory->GetSlotSize(0) - stack.NumItems);
		mOutputInventory->AddStack(FInventoryStack(mItemsPerTower * mTowerAmount, extractedResource));
		mCurrentExtractProgress -= 1.0f;
	}
}

void AAVRPBuildableWaterTower::Factory_PushPipeOutput_Implementation(float dt)
{
	Super::Factory_PushPipeOutput_Implementation(dt);
	if (!HasAuthority()) return;
	for (auto i = 0; i < mPipeOutputConnections.Num(); i++) {
		FInventoryStack stack;
		mOutputInventory->GetStackFromIndex(0, stack);
		int pushedAmount = mPipeOutputConnections[i]->Factory_PushPipeOutput(dt, stack);
		if (pushedAmount > 0) {
			mFluidMovedLastProducingTick = pushedAmount;
			mOutputInventory->RemoveFromIndex(0, pushedAmount);
		}
	}
}

FFluidBox* AAVRPBuildableWaterTower::GetFluidBox()
{
	return nullptr;
}

TArray<class UFGPipeConnectionComponent*> AAVRPBuildableWaterTower::GetPipeConnections()
{
	return mPipeOutputConnections;
}
