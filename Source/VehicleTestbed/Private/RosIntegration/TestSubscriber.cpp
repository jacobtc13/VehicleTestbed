// Fill out your copyright notice in the Description page of Project Settings.

#include "TestSubscriber.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/std_msgs/String.h"

#include <iostream>

// Sets default values
ATestSubscriber::ATestSubscriber()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestSubscriber::BeginPlay()
{
	Super::BeginPlay();

	ExampleTopic = NewObject<UTopic>(UTopic::StaticClass());
	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
	ExampleTopic->Init(rosinst->ROSIntegrationCore, TEXT("/example_topic"), TEXT("std_msgs/String"));

	std::function<void(TSharedPtr<FROSBaseMsg>)> SubscribeCallback = ATestSubscriber::SubscribeCallbackImpl;
	ExampleTopic->Subscribe(SubscribeCallback);
	
}

// Called every frame
void ATestSubscriber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestSubscriber::SubscribeCallbackImpl(TSharedPtr<FROSBaseMsg> msg)
{
	auto Concrete = StaticCastSharedPtr<ROSMessages::std_msgs::String>(msg);
	if (Concrete.IsValid())
	{
		std::cout << "Subscriber listened: " << TCHAR_TO_UTF8(*(Concrete->_Data)) << std::endl;
	}
	return;
}