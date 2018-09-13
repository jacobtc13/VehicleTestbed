#include "ROSIntegrationGameInstance.h"
#include "RI/Topic.h"
#include "RI/Service.h"

static void MarkAllROSObjectsAsDisconnected()
{
    for (TObjectIterator<UTopic> It; It; ++It)
    {
        UTopic* Topic = *It;

        Topic->MarkAsDisconnected();
    }
    for (TObjectIterator<UService> It; It; ++It)
    {
        UService* Service = *It;

        Service->MarkAsDisconnected();
    }
}

void UROSIntegrationGameInstance::Init()
{
	if (bConnectToROS)
	{
        ROSIntegrationCore = NewObject<UROSIntegrationCore>(UROSIntegrationCore::StaticClass());
		bIsConnected = ROSIntegrationCore->Init(ROSBridgeServerHost, ROSBridgeServerPort);

        GetTimerManager().SetTimer(TimerHandle_CheckHealth, this, &UROSIntegrationGameInstance::CheckROSBridgeHealth, 1.0f, true, 5.0f);

		if (bIsConnected)
		{
			UWorld* CurrentWorld = GetWorld();
			if (CurrentWorld) 
            {
                ROSIntegrationCore->SetWorld(CurrentWorld);
                ROSIntegrationCore->InitSpawnManager();
			}
			else 
            {
				UE_LOG(LogROS, Error, TEXT("World not available in UROSIntegrationGameInstance::Init()!"));
			}
		}
        else if(!bReconnect)
        {
            UE_LOG(LogROS, Error, TEXT("Failed to connect to server %s:%u. Please make sure that your rosbridge is running."), *ROSBridgeServerHost, ROSBridgeServerPort);
        }
	}
}

void UROSIntegrationGameInstance::CheckROSBridgeHealth()
{
    if (bIsConnected && ROSIntegrationCore->IsHealthy())
    {
        return;
    }

    if (bIsConnected)
    {
        UE_LOG(LogROS, Error, TEXT("Connection to rosbridge %s:%u was interrupted."), *ROSBridgeServerHost, ROSBridgeServerPort);
    }

    // reconnect again
    bIsConnected = false;
    bReconnect = true;
    Init();
    bReconnect = false;

    // tell everyone (Topics, Services, etc.) they lost connection and should stop any interaction with ROS for now.
    MarkAllROSObjectsAsDisconnected();

    if(!bIsConnected)
    {
        return; // Let timer call this method again to retry connection attempt
    }

    // tell everyone (Topics, Services, etc.) they can try to reconnect (subscribe and advertise)
    {
        for (TObjectIterator<UTopic> It; It; ++It)
        {
            UTopic* Topic = *It;

            bool success = Topic->Reconnect(ROSIntegrationCore);
            if (!success)
            {
                bIsConnected = false;
                UE_LOG(LogROS, Error, TEXT("Unable to re-establish topic %s."), *Topic->GetDetailedInfo());
            }
        }
        for (TObjectIterator<UService> It; It; ++It)
        {
            UService* Service = *It;

            bool success = Service->Reconnect(ROSIntegrationCore);
            if (!success)
            {
                bIsConnected = false;
                UE_LOG(LogROS, Error, TEXT("Unable to re-establish service %s."), *Service->GetDetailedInfo());
            }
        }
    }

    UE_LOG(LogROS, Display, TEXT("Successfully reconnected to rosbridge %s:%u."), *ROSBridgeServerHost, ROSBridgeServerPort);
}

void UROSIntegrationGameInstance::Shutdown() 
{
    GetTimerManager().ClearTimer(TimerHandle_CheckHealth);
}

void UROSIntegrationGameInstance::BeginDestroy() 
{
    // tell everyone (Topics, Services, etc.) they should stop any interaction with ROS.
    MarkAllROSObjectsAsDisconnected();

	Super::BeginDestroy();
}