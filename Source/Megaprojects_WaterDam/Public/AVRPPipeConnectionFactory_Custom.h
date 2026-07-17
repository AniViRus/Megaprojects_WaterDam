

#pragma once

#include "CoreMinimal.h"
#include "FGPipeConnectionFactory.h"
#include "AVRPPipeConnectionFactory_Custom.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MEGAPROJECTS_WATERDAM_API UAVRPPipeConnectionFactory_Custom : public UFGPipeConnectionFactory
{
	GENERATED_BODY()
public:
	UAVRPPipeConnectionFactory_Custom();
	// Begin ActorComponent Interface
	virtual void BeginPlay() override;
	// End ActorComponent Interface
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Connection")
	float mAdditionalPressure;
};
