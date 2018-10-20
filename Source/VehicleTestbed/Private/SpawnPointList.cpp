// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPointList.h"

TArray<SpawnPoint> spList;

//  TODO - NEED INFO FROM RYAN FOR HOW TO USE GETWORLD
UWorld* const World = AActor::GetWorld();

SpawnPointList::SpawnPointList()
{
	TArray<SpawnPoint> spList = generateList();
	
}


TArray<SpawnPoint> generateList() {

	TArray<SpawnPoint> foundPoints;
	FName allyTag = TEXT("allyPos");
	TArray<AActor*> playerStartActorsFound;
	UGameplayStatics::GetAllActorsWithTag(World, allyTag, playerStartActorsFound);
	 
	//TODO - Loop through playerStartActorsFound to create SpawnPoints, populating Name and FVector and storing in foundPoints


	return foundPoints;
}

SpawnPointList::~SpawnPointList()
{
}
