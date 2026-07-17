#include "AVRPPipeConnectionFactory_Custom.h"

UAVRPPipeConnectionFactory_Custom::UAVRPPipeConnectionFactory_Custom() : Super(){}

void UAVRPPipeConnectionFactory_Custom::BeginPlay()
{
	Super::BeginPlay();
	mFluidBox.AddedPressure = mAdditionalPressure;
}
