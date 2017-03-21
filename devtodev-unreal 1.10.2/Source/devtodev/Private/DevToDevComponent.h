#pragma once

#include "Components/ActorComponent.h"
#include "DevToDevComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDevToDevRegisterSuccessDynamicDelegate, FString, PushToken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDevToDevRegisterErrorDynamicDelegate, FString, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDevToDevPushAcceptedDynamicDelegate, FString, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDevToDevPushOpenedDynamicDelegate, FString, PushMessage, FString, ActionButton);

UCLASS( ClassGroup=(DevToDev), meta=(BlueprintSpawnableComponent) )
class UDevToDevComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDevToDevComponent();

	UPROPERTY(BlueprintAssignable, Category = "DevToDev")
	FDevToDevRegisterSuccessDynamicDelegate PushRegistrationSucceeded;

	UPROPERTY(BlueprintAssignable, Category = "DevToDev")
	FDevToDevRegisterErrorDynamicDelegate PushRegistrationError;

	UPROPERTY(BlueprintAssignable, Category = "DevToDev")
	FDevToDevPushAcceptedDynamicDelegate PushReceived;

	UPROPERTY(BlueprintAssignable, Category = "DevToDev")
	FDevToDevPushOpenedDynamicDelegate PushOpened;
	
	void InitializeComponent() override;

private:	
	void PushRegisterSuccess_Handler(FString token);
	void PushRegisterError_Handler(FString error);
	void PushReceived_Handler(FString data);
	void PushOpened_Handler(FString pushMessage, FString actionButton);
};
