#include "AVRPBuildableWaterDam.h"
#include "FGPowerInfoComponent.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "AVRPBPFL_MegaprojectsLib.h"
#include "FGSchematicManager.h"
#include "FGPowerCircuit.h"

AAVRPBuildableWaterDam::AAVRPBuildableWaterDam()
{
	this->connections = TArray<UFGFactoryConnectionComponent*>();
}

void AAVRPBuildableWaterDam::BeginPlay()
{
	Super::BeginPlay();
	GetPowerInfo()->SetBaseProduction(50000);
	connections.Empty();
	ForEachComponent<UFGFactoryConnectionComponent>(true, [&](UFGFactoryConnectionComponent* FactoryConn) {
		switch (FactoryConn->GetDirection()) {
		case EFactoryConnectionDirection::FCD_INPUT:
			connections.AddUnique(FactoryConn);
			break;
		}
		});
}

void AAVRPBuildableWaterDam::Factory_TickProducing(float dt)
{
	Super::Factory_TickProducing(dt);
	if (!HasAuthority()) return;
	UAVRPBPFL_MegaprojectsLib::Factory_PayoffOnMegagproject(this, connections);
}

bool AAVRPBuildableWaterDam::CanProduce_Implementation() const
{
	return true;
}

bool AAVRPBuildableWaterDam::Factory_HasPower() const
{
	return HasPower() || CanProduce_Implementation();
}

EProductionStatus AAVRPBuildableWaterDam::GetProductionIndicatorStatus() const
{
	auto powerCircuit = mPowerInfo->GetPowerCircuit();
	bool fuseTriggered = IsValid(powerCircuit) && powerCircuit->IsFuseTriggered();
	if (fuseTriggered || !Factory_IsProducing()) return EProductionStatus::IS_ERROR;

	return EProductionStatus::IS_PRODUCING;
}

void AAVRPBuildableWaterDam::BeginFromLevel_Implementation(int level)
{
	GetPowerInfo()->SetDynamicProductionCapacity(.0f);
	OnLevelChanged_Implementation(level);
	AddAsRepresentation();
}

void AAVRPBuildableWaterDam::OnLevelChanged_Implementation(int level)
{
	GetPowerInfo()->SetBaseProduction(AFGSchematicManager::Get(this)->IsSchematicPurchased(waterDamConfiguration.phase.schematic) ? waterDamConfiguration.completedPowerGeneration : 250.0f);
}

bool AAVRPBuildableWaterDam::AddAsRepresentation()
{
	if (!HasAuthority()) return false;
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		cachedRepresentation = manager->CreateAndAddNewRepresentation(this);
		return true;
	}
	return false;
}

bool AAVRPBuildableWaterDam::UpdateRepresentation()
{
	if (!HasAuthority()) return false;
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		manager->UpdateRepresentation(cachedRepresentation);
		return true;
	}
	return false;
}

bool AAVRPBuildableWaterDam::RemoveAsRepresentation()
{
	if (!HasAuthority()) return false;
	if (auto manager = AFGActorRepresentationManager::Get(this)) {
		manager->RemoveRepresentationOfActor(this);
		cachedRepresentation = nullptr;
		return true;
	}
	return false;
}

bool AAVRPBuildableWaterDam::IsActorStatic()
{
	return true;
}

FVector AAVRPBuildableWaterDam::GetRealActorLocation()
{
	return GetActorLocation();
}

FRotator AAVRPBuildableWaterDam::GetRealActorRotation()
{
	return FRotator::ZeroRotator;
}

UTexture2D* AAVRPBuildableWaterDam::GetActorRepresentationTexture()
{
	return mRepresentationTexture;
}

UMaterialInterface* AAVRPBuildableWaterDam::GetActorRepresentationCompassMaterial()
{
	return mRepresentationCompassMaterial;
}

FText AAVRPBuildableWaterDam::GetActorRepresentationText()
{
	return mDisplayName;
}

void AAVRPBuildableWaterDam::SetActorRepresentationText(const FText& newText) {}

FLinearColor AAVRPBuildableWaterDam::GetActorRepresentationColor()
{
	return FLinearColor(.1f, .1f, .1f);
}

void AAVRPBuildableWaterDam::SetActorRepresentationColor(FLinearColor newColor) {}

ERepresentationType AAVRPBuildableWaterDam::GetActorRepresentationType()
{
	return ERepresentationType::RT_SpaceElevator;
}

bool AAVRPBuildableWaterDam::GetActorShouldShowInCompass()
{
	return true;
}

bool AAVRPBuildableWaterDam::GetActorShouldShowOnMap()
{
	return true;
}

EFogOfWarRevealType AAVRPBuildableWaterDam::GetActorFogOfWarRevealType()
{
	return EFogOfWarRevealType::FOWRT_None;
}

float AAVRPBuildableWaterDam::GetActorFogOfWarRevealRadius()
{
	return 0.0f;
}

ECompassViewDistance AAVRPBuildableWaterDam::GetActorCompassViewDistance()
{
	return ECompassViewDistance::CVD_Far;
}

void AAVRPBuildableWaterDam::SetActorCompassViewDistance(ECompassViewDistance compassViewDistance) {}

FPlayerInfoHandle AAVRPBuildableWaterDam::GetLastEditedBy() const
{
	return FPlayerInfoHandle();
}

void AAVRPBuildableWaterDam::SetActorLastEditedByHandle(const FPlayerInfoHandle& LastEditedBy) {}