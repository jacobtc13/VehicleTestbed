// Fill out your copyright notice in the Description page of Project Settings.

#include "TestPublisher.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/std_msgs/String.h"

#include <sstream>

// Sets default values
ATestPublisher::ATestPublisher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestPublisher::BeginPlay()
{
	Super::BeginPlay();

	ExampleTopic = NewObject<UTopic>(UTopic::StaticClass());
	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
	ExampleTopic->Init(rosinst->ROSIntegrationCore, TEXT("/example_topic"), TEXT("std_msgs/String"));
	
}

// Called every frame
void ATestPublisher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	nFrames++;
	if (bPublish)
	{
		std::ostringstream oss;
		oss << "Message from frame " << nFrames;
		Publish(oss.str().c_str());
	}

}

void ATestPublisher::Publish(const char *Content)
{
	TSharedPtr<ROSMessages::std_msgs::String> StringMessage(new ROSMessages::std_msgs::String(Content));
	ExampleTopic->Publish(StringMessage);
}

