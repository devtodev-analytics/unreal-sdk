#include "DevToDevPrivatePCH.h"

#include "DevToDevComponent.h"

UDevToDevComponent::UDevToDevComponent()
{
	bWantsInitializeComponent = true;
}

void UDevToDevComponent::InitializeComponent()
{
	Super::InitializeComponent();

	FAnalyticsDevToDev::PushRegisterSuccess.AddUObject(this, &UDevToDevComponent::PushRegisterSuccess_Handler);
	FAnalyticsDevToDev::PushRegisterError.AddUObject(this, &UDevToDevComponent::PushRegisterError_Handler);
	FAnalyticsDevToDev::PushReceived.AddUObject(this, &UDevToDevComponent::PushReceived_Handler);
	FAnalyticsDevToDev::PushOpened.AddUObject(this, &UDevToDevComponent::PushOpened_Handler);
}

void UDevToDevComponent::PushRegisterSuccess_Handler(FString token)
{
	PushRegistrationSucceeded.Broadcast(token);
}

void UDevToDevComponent::PushRegisterError_Handler(FString error)
{
	PushRegistrationError.Broadcast(error);
}

void UDevToDevComponent::PushReceived_Handler(FString data)
{
	PushReceived.Broadcast(data);
}

void UDevToDevComponent::PushOpened_Handler(FString pushMessage, FString actionButton)
{
	PushOpened.Broadcast(pushMessage, actionButton);
}