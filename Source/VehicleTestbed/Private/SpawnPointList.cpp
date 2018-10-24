// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPointList.h"

TArray<SpawnPoint> spList;


//SpawnPoint Constructor
SpawnPointList::SpawnPointList() {
	TArray<SpawnPoint> spList;
	spList.Init(SpawnPoint(TEXT("DEFAULT"), FVector(0, 0, 0), FRotator(0, 0, 0), ""),1);
	PopulateList();
	
}


//Populate spawnpoint list with Spawnpoints from Desert Map
bool SpawnPointList::PopulateList() {
	
	spList.Add(SpawnPoint(TEXT("DEFAULT"), FVector(0, 0, 0), FRotator(0, 0, 0), ""));
	spList.Add(SpawnPoint(TEXT("ALLY1"), FVector(128581.210938, 161129.390625, -53666.914062), FRotator(0, 0, 165.599533), ""));
	spList.Add(SpawnPoint(TEXT("ALLY2"), FVector(179069.40625, 137120, -53797.636719), FRotator(0, 0, 161.999588), ""));
	spList.Add(SpawnPoint(TEXT("ENEMY1"), FVector(80932.445312, 164541.28125, -47791.210938), FRotator(0, 0, 0), ""));
	spList.Add(SpawnPoint(TEXT("ENEMY2"), FVector(87885.257812, 205574.890625, -48679.117188), FRotator(0, 0, 295.199066), ""));
	spList.Add(SpawnPoint(TEXT("ENEMY3"), FVector(114588.4375, 206807.359375, -45675.542969), FRotator(0, 0, 273.59924), ""));

	return true;
}

//Returns SpawnPoint based on array position
SpawnPoint SpawnPointList::getSpawnPointbyPos(int position) {
	return spList[position];
}

//Returns SpawnPoint based on SpawnPoint Name
SpawnPoint SpawnPointList::getSpawnPointbyName(FName SpawnPointName) {
	
	SpawnPoint spFound;
	int listLength = spList.Num();

	for (int i = 0; i < (listLength + 1); i++) {
		if(spList[i].getName() == SpawnPointName){
			spFound = spList[i];
			break;
		}
	}
	return spFound;
};

//Returns TArray of Names for all Spawnpoints
TArray<FName> SpawnPointList::getSpawnPointRefs() {
	TArray<FName> spNames;
	int listLength = spList.Num();

	for (int i = 0; i < (listLength + 1); i++) {
		spNames.Add(spList[i].getName());
	}
	return spNames;
}

//Create a new SpawnPoint and add to the SpawnPoint List
bool SpawnPointList::addSpawnPoint(FName Name, FVector Location, FRotator Rotation, FString Tags) {
	SpawnPoint newSpawnPoint = SpawnPoint(Name, Location, Rotation, Tags);
	
	spList.Add(newSpawnPoint);
	return true;
}

SpawnPointList::~SpawnPointList()
{
}
