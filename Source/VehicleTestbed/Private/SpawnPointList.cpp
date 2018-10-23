// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPointList.h"

TArray<SpawnPoint> spList;
 
//  TODO - NEED INFO FROM RYAN FOR HOW TO USE GETWORLD
//UWorld* const World = AActor::GetWorld();

SpawnPointList::SpawnPointList() {
	TArray<SpawnPoint> spList;
	PopulateList();
	
}


bool SpawnPointList::PopulateList() {

	SpawnPoint sp1 = SpawnPoint(TEXT("ALLY1"), FVector(128581.210938, 161129.390625, -53666.914062), FRotator(0, 0, 165.599533));
	SpawnPoint sp2 = SpawnPoint(TEXT("ALLY2"), FVector(179069.40625, 137120, -53797.636719), FRotator(0, 0, 161.999588));
	SpawnPoint sp3 = SpawnPoint(TEXT("ENEMY1"), FVector(80932.445312, 164541.28125, -47791.210938), FRotator(0, 0, 0));
	SpawnPoint sp4 = SpawnPoint(TEXT("ENEMY2"), FVector(87885.257812, 205574.890625, -48679.117188), FRotator(0, 0, 295.199066));
	SpawnPoint sp5 = SpawnPoint(TEXT("ENEMY3"), FVector(114588.4375, 206807.359375, -45675.542969), FRotator(0, 0, 273.59924));

	spList.Add(sp1);
	spList.Add(sp2);
	spList.Add(sp3);
	spList.Add(sp4);
	spList.Add(sp5);


	return true;
}

SpawnPointList::~SpawnPointList()
{
}
