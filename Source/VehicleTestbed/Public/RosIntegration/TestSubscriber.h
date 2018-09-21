// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestSubscriber.generated.h"

UCLASS()
class VEHICLETESTBED_API ATestSubscriber : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestSubscriber();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UTopic *ExampleTopic;

	static void SubscribeCallbackImpl(TSharedPtr<class FROSBaseMsg> msg);
	
};
