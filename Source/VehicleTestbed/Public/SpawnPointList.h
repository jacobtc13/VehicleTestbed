// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Array.h"
#include "VehicleTestbed.h"
#include "SpawnPoint.h"



///<summary>SpawnPointList class for storing and modifying a TArray of SpawnPoints</summary>
class VEHICLETESTBED_API SpawnPointList
{

private:
	TArray<SpawnPoint> spList;


public:
	///<summary>Default Constructor</summary>
	SpawnPointList();


	///<summary>Destructor</summary>
	~SpawnPointList();

	///<summary>Update the name of the SpawnPoint</summary>
	///<param name="newName">Name to be set</param>
	///<returns><see cref="bool" /> True if update is successful</returns>
	bool PopulateList();

	///<summary>Add a new SpawnPoint to the SpawnPointList</summary>
	///<param name="Name">Name of SpawnPoint</param>
	///<param name="Location">Location of SpawnPoint</param>
	///<param name="Rotation">Rotation of SpawnPoint</param>
	///<param name="Tags">Tags to find SpawnPoint</param>
	///<returns><see cref="bool" /> True if Spawn Point is created successfully</returns>
	bool AddSpawnPoint(FName Name, FVector Location, FRotator Rotation, FString Tags);

	///<summary>Returns a Spawn Ppoint based on position in Array</summary>
	///<param name="position">position in TArray of SpawnPoint</param>
	///<returns><see cref="SpawnPoint" /> SpawnPoint requested</returns>
	SpawnPoint GetSpawnPointbyPos(int position);

	///<summary>Returns a SpawnPoint Based on Name of SpawnPoint</summary>
	///<param name="SpawnPointName">Name of SpawnPoint to be returned</param>
	///<returns><see cref="SpawnPoint" /> SpawnPoint requested</returns>
	SpawnPoint GetSpawnPointbyName(FName SpawnPointName);

	///<summary>Returns an Array of FNames representing all SpawnPoints</summary>
	///<returns><see cref="TArray"> Returns a TArray of FNames</returns> 
	TArray<FName> GetSpawnPointRefs();

	///<summary>Returns True if Spawnpoint found in list</summary>
	///<returns><see cref="TArray"> Returns a TArray of FNames</returns> 
	bool CheckSpawnPointInList(FName Name);
};
