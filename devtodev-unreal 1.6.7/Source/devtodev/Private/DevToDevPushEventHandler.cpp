#include "DevToDevPrivatePCH.h"
#include "DevToDevPushEventHandler.h"

void UDevToDevPushEventHandler_OnPushTokenReceived(FString token)
{
	for ( TObjectIterator<UDevToDevPushEventHandler> Itr; Itr; ++Itr )
    {
        if(Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType.GetValue() == EWorldType::Game || Itr->GetWorld()->WorldType.GetValue() == EWorldType::PIE) && (!Itr->HasAnyFlags(RF_PendingKill))){
               Itr->OnPushTokenReceived.Broadcast(token);
		}
    }
}