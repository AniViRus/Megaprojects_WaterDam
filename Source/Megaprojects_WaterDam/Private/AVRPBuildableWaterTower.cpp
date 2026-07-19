#include "AVRPBuildableWaterTower.h"
#include "FGPipeSubsystem.h"
#include "FGPipeConnectionComponent.h"

AAVRPBuildableWaterTower::AAVRPBuildableWaterTower() : Super()
{
	mTowerAmount = 1;
}

void AAVRPBuildableWaterTower::BeginPlay()
{
	AFGBuildableFactory::BeginPlay();
	if (!HasAuthority()) return;
	mPressure = mAdditionalPressure;
    mResourceType = extractedResource;
	ForEachComponent<UFGPipeConnectionComponent>(true, [&](UFGPipeConnectionComponent* Conn) {
		if (Conn->GetPipeConnectionType() == EPipeConnectionType::PCT_PRODUCER) {
		}
		mPipeOutputConnections.Add(Conn);
		});
    if (AFGPipeSubsystem* PipeSubsystem = AFGPipeSubsystem::Get(GetWorld()))
    {
        PipeSubsystem->RegisterFluidIntegrant(this);
    }

    GetFluidBox()->MaxContent = 5.0f;
    GetFluidBox()->Height = 2.0f;

    const float Z = RootComponent->GetComponentLocation().Z * 0.01f;
    GetFluidBox()->LowZ = Z;
    GetFluidBox()->HighZ = Z;
    GetFluidBox()->Z = Z;
}

void AAVRPBuildableWaterTower::Factory_TickProducing(float dt)
{
    if (!mResourceType) return;
    for (auto* connection : GetPipeConnections()) {
            if (connection->GetFluidDescriptor() != mResourceType){
                AFGPipeSubsystem* PipeSubsystem = AFGPipeSubsystem::Get(GetWorld());
                check(PipeSubsystem);
                PipeSubsystem->FlushPipeNetwork(connection->GetPipeNetworkID());
                PipeSubsystem->TrySetNetworkFluidDescriptor(connection->GetPipeNetworkID(), mResourceType);
        }
    } 

    const float MaxContent = GetFluidBox()->MaxContent * (1.0f + GetFluidBox()->MaxOverfillPct);

    float NewContent = GetFluidBox()->Content;

    if (GetSpawnRate() >= KINDA_SMALL_NUMBER)
    {
        NewContent = FMath::Min(
            GetFluidBox()->Content + GetSpawnRate() * dt,
            MaxContent);
    }

    const float Spawned = NewContent - GetFluidBox()->Content;
    mMeasuredSpawnRate = (Spawned / dt) * (dt * 2.5f) + mMeasuredSpawnRate * (1.0f - dt * 2.5f);
    GetFluidBox()->Content = NewContent;
}

TArray<class UFGPipeConnectionComponent*> AAVRPBuildableWaterTower::GetPipeConnections()
{
	return mPipeOutputConnections;
}

void AAVRPBuildableWaterTower::SetTowerAmount(int amount)
{
    mTowerAmount = amount;
    SetSpawnRate(mItemsPerTower * mTowerAmount);
}
