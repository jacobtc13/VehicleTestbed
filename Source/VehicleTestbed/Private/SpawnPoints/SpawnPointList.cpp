// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPointList.h"




//SpawnPoint Constructor
SpawnPointList::SpawnPointList()
{
	PopulateList();
}

//Populate spawnpoint list with Spawnpoints from Desert Map
void SpawnPointList::PopulateList()
{
	spList.Add(SpawnPoint(FName(TEXT("DEFAULT")), FVector(0, 0, 0), FRotator(0, 0, 0), ""));
	spList.Add(SpawnPoint(FName(TEXT("ALLY1")), FVector(128581.210938, 161129.390625, -53666.914062), FRotator(0, 165.599533, 0), ""));
	spList.Add(SpawnPoint(FName(TEXT("ALLY2")), FVector(179069.40625, 137120, -53797.636719), FRotator(0, 161.999588, 0), ""));
	spList.Add(SpawnPoint(FName(TEXT("ENEMY1")), FVector(80932.445312, 164541.28125, -47791.210938), FRotator(0, 0, 0), ""));
	spList.Add(SpawnPoint(FName(TEXT("ENEMY2")), FVector(87885.257812, 205574.890625, -48679.117188), FRotator(0, 295.199066, 0), ""));
	spList.Add(SpawnPoint(FName(TEXT("ENEMY3")), FVector(114588.4375, 206807.359375, -45675.542969), FRotator(0, 273.59924, 0), ""));


}

//Returns SpawnPoint based on array position
SpawnPoint SpawnPointList::GetSpawnPointbyPos(int position) const
{
	if (spList.IsValidIndex(position))
	{
		return spList[position];
	}
	else
	{
		return SpawnPoint();
	}
}

//Returns SpawnPoint based on SpawnPoint Name
SpawnPoint SpawnPointList::GetSpawnPointbyName(FName SpawnPointName) const
{
	for (const SpawnPoint& sPoint : spList)
	{
		if (sPoint.GetName() == SpawnPointName)
		{
			return sPoint;
		}
	}
	return SpawnPoint();
};

//Returns Random SpawnPoint
SpawnPoint SpawnPointList::GetRandomSpawnPoint() const
{
	int LastElement = (spList.Num()-1);
	
	int RandomSelect = FMath::RandRange(0, LastElement);

	return GetSpawnPointbyPos(RandomSelect);

};

//Returns TArray of Names for all Spawnpoints
TArray<FName> SpawnPointList::GetSpawnPointRefs() const
{
	TArray<FName> spNames;

	for (const SpawnPoint& sPoint : spList)
	{
		spNames.Add(sPoint.GetName());
	}

	return spNames;
}

//Create a new SpawnPoint and add to the SpawnPoint List
bool SpawnPointList::AddSpawnPoint(FName Name, FVector Location, FRotator Rotation, FString Tags)
{
	SpawnPoint newSpawnPoint(Name, Location, Rotation, Tags);

	spList.Add(newSpawnPoint);

	return CheckSpawnPointInList(Name);

}

//Check whether Spawn Point is in list by Name
bool SpawnPointList::CheckSpawnPointInList(FName SpawnPointName) const
{
	for (const SpawnPoint& sPoint : spList)
	{
		if (sPoint.GetName() == SpawnPointName)
		{
			return true;
		}
	}
	return false;
}

SpawnPointList::~SpawnPointList()
{}
