#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "AVRPMegaprojectInterface.h"
#include "AVRPMegaprojectSubsystemBase.h"
#include "FGFactoryConnectionComponent.h"
#include "AVRPBuildableWaterDam.generated.h"

//Struct to store megaproject's phase info per instance, ordered
USTRUCT(BlueprintType)
struct FAVRPWaterDamConfiguration
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FAVRPMegaprojectPhase phase;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (MultiLine = true))
	float completedPowerGeneration;
};

/**
 * A base class C++ class for Water Dams 
 */
UCLASS()
class MEGAPROJECTS_WATERDAM_API AAVRPBuildableWaterDam : public AFGBuildableFactory, public IAVRPMegaprojectInterface
{
	GENERATED_BODY()
public:
	AAVRPBuildableWaterDam();
	
	virtual void BeginPlay() override;

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual bool Factory_HasPower() const override;
	virtual EProductionStatus GetProductionIndicatorStatus() const override;
	// End AFGBuildableFactory interface

	// Begin AVRPMegaprojectInterface
	virtual void BeginFromLevel_Implementation(int level) override;
	virtual void OnLevelChanged_Implementation(int level) override;
	//End AVRPMegaprojectInterface

	//Begin FGActorRepresentationInterface
	virtual bool AddAsRepresentation() override;
	virtual bool UpdateRepresentation() override;
	virtual bool RemoveAsRepresentation() override;
	virtual bool IsActorStatic() override;
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	virtual FText GetActorRepresentationText() override;
	virtual void SetActorRepresentationText(const FText& newText) override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual void SetActorRepresentationColor(FLinearColor newColor) override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual bool GetActorShouldShowInCompass() override;
	virtual bool GetActorShouldShowOnMap() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	virtual float GetActorFogOfWarRevealRadius() override;
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	virtual void SetActorCompassViewDistance(ECompassViewDistance compassViewDistance) override;
	virtual FPlayerInfoHandle GetLastEditedBy() const override;
	virtual void SetActorLastEditedByHandle(const FPlayerInfoHandle& playerInfoHandle) override;
	//End FGActorRepresentationInterface
	
protected:
	// Begin AFGBuildableFactory interface
	virtual void Factory_TickProducing(float dt) override;
	// End AFGBuildableFactory interface

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FAVRPWaterDamConfiguration waterDamConfiguration;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UMaterialInterface> mRepresentationCompassMaterial;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UTexture2D> mRepresentationTexture;
	UPROPERTY()
	TArray<TObjectPtr<UFGFactoryConnectionComponent>> connections;
private:
	UPROPERTY(Transient)
	TObjectPtr<UFGActorRepresentation> cachedRepresentation;
};
