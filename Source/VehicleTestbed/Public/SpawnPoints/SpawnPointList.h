// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Array.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
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

	///<summary>Populate SpawnPoint List</summary>
	void PopulateList();

	///<summary>Add a new SpawnPoint to the SpawnPointList</summary>
	///<param name="Name">Name of SpawnPoint</param>
	///<param name="Location">Location of SpawnPoint</param>
	///<param name="Rotation">Rotation of SpawnPoint</param>
	///<param name="Tags">Tags to find SpawnPoint</param>
	///<returns><see cref="bool" /> True if Spawn Point is created successfully</returns>
	bool AddSpawnPoint(FName Name, FVector Location, FRotator Rotation, FString Tags);

	///<summary>Returns a Spawn Ppoint based on position in Array</summary>
	///<param name="position">position in TArray of SpawnPoint</param>
	///<returns><see cref="SpawnPoint" /> SpawnPoint requested or if no Spawnpoint at postion provided returns default SpawnPoint</returns>
	SpawnPoint GetSpawnPointbyPos(int position) const;

	///<summary>Returns a SpawnPoint Based on Name of SpawnPoint</summary>
	///<param name="SpawnPointName">Name of SpawnPoint to be returned</param>
	///<returns><see cref="SpawnPoint" /> SpawnPoint requested or if no Spawnpoint with name provided returns default SpawnPoint</returns>
	SpawnPoint GetSpawnPointbyName(FName SpawnPointName) const;

	///<summary>Returns a random SpawnPoint</summary>
	///<returns><see cref="SpawnPoint" /> SpawnPoint selected randomly from SpawnPointList</returns>
	SpawnPoint GetRandomSpawnPoint() const;

	///<summary>Returns an Array of FNames representing all SpawnPoints</summary>
	///<returns><see cref="TArray"> Returns a TArray of FNames</returns> 
	TArray<FName> GetSpawnPointRefs() const;

	///<summary>Returns True if Spawnpoint found in list</summary>
	///<returns><see cref="bool"> Returns True if Spawnpoint is found in list. False if not found</returns> 
	bool CheckSpawnPointInList(FName Name) const;
};
