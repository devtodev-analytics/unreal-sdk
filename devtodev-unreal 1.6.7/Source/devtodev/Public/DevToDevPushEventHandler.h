#pragma once

#include "DevToDevPushEventHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPushTokenReceivedDelegate, FString, token );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPushTokenErrorDelegate, FString, error );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPushReceivedDelegate, FString, data );

UCLASS(meta = (BlueprintSpawnableComponent), Category = "PushMessages")
class UDevToDevPushEventHandler : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category="PushMessages")
    FOnPushTokenReceivedDelegate OnPushTokenReceived;

    UPROPERTY(BlueprintAssignable, Category="PushMessages")
    FOnPushTokenReceivedDelegate OnPushTokenError;

    UPROPERTY(BlueprintAssignable, Category="PushMessages")
    FOnPushTokenReceivedDelegate OnPushReceived;
};