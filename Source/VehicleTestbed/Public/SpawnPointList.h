// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Array.h"
#include "VehicleTestbed.h"
#include "SpawnPoint.h"



/**
 * 
 */
class VEHICLETESTBED_API SpawnPointList
{

private:
	TArray<SpawnPoint> spList;


public:
	
	SpawnPointList();
	
	~SpawnPointList();

	///<summary>Update the name of the SpawnPoint</summary>
	///<param name="newName">Name to be set</param>
	///<returns><see cref="bool" /> True if update is successful</returns>
	bool SpawnPointList::PopulateList();

	///<summary>Add a new SpawnPoint to the SpawnPointList</summary>
	///<param name="Name">Name of SpawnPoint</param>
	///<param name="Location">Location of SpawnPoint</param>
	///<param name="Rotation">Rotation of SpawnPoint</param>
	///<param name="Tags">Tags to find SpawnPoint</param>
	///<returns><see cref="bool" /> True if Spawn Point is created successfully</returns>
	bool SpawnPointList::addSpawnPoint(FName Name, FVector Location, FRotator Rotation, FString Tags);

	///<summary>Returns a Spawn Ppoint based on position in Array</summary>
	///<param name="position">position in TArray of SpawnPoint</param>
	///<returns><see cref="SpawnPoint" /> SpawnPoint requested</returns>
	SpawnPoint SpawnPointList::getSpawnPointbyPos(int position);

	///<summary>Returns a SpawnPoint Based on Name of SpawnPoint</summary>
	///<param name="SpawnPointName">Name of SpawnPoint to be returned</param>
	///<returns><see cref="SpawnPoint" /> SpawnPoint requested</returns>
	SpawnPoint SpawnPointList::getSpawnPointbyName(FName SpawnPointName);

	///<summary>Returns an Array of FNames representing all SpawnPoints</summary>
	///<returns><see cref="TArray"> Returns a TArray of FNames</returns> 
	TArray<FName> SpawnPointList::getSpawnPointRefs();
};
