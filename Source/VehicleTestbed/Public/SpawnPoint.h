#pragma once

#include "CoreMinimal.h"


///<summary>SpawnPoint class for SpawnList, holds location name, location coordinates, Rotation and Tags to identify the spawnpoint</summary>


class VEHICLETESTBED_API SpawnPoint
{
private:
	FName spName;
	FVector spLocation;
	FRotator spRotation;
	FString spTags;



public:
	
	
	///<summary>Constructor with name and location provided</summary>
	SpawnPoint(FName aName, FVector aLocation, FRotator aRotation, FString aTags);

	///<summary>Default Constructor</summary>
	SpawnPoint();

	
	///<summary>Destructor</summary>
	~SpawnPoint();

	///<summary>Update the name of the SpawnPoint</summary>
	///<param name="newName">Name to be set</param>
	///<returns><see cref="bool" /> True if update is successful</returns>
	bool SpawnPoint::setName(FName newName);


	///<summary>Update the Location of the SpawnPoint</summary>
	///<param name="newLocation">Location to be set</param>
	///<returns><see cref="bool" /> True if update is successful</returns>
	bool SpawnPoint::setLocation(FVector newLocation);

	///<summary>Update the Location of the SpawnPoint</summary>
	///<param name="newLocation">Location to be set</param>
	///<returns><see cref="bool" /> True if update is successful</returns>
	bool SpawnPoint::setRotation(FRotator newRotation);

	///<summary>Update the Tags of the SpawnPoint</summary>
	///<param name="newTags">Tags to be set</param>
	///<returns><see cref="bool" /> True if update is successful</returns>
	bool SpawnPoint::setTags(FString newTags);

	///<summary>Update the Location of the SpawnPoint</summary>
	///<param name="newLocation">Location to be set</param>
	///<returns><see cref="bool" /> True if update is successful</returns>
	bool SpawnPoint::setSpawnPoint(FVector newLocation, FRotator newRotation);

	///<summary>Returns the name of the Spawn Point</summary>
	///<returns><see cref="FName" /> Name of SpawnPoint</returns>
	FName SpawnPoint::getName();

	///<summary>Returns the Location of the Spawn Point</summary>
	///<returns><see cref="FVector" /> Location of SpawnPoint</returns>
	FVector SpawnPoint::getLocation();

	///<summary>Returns the Rotation of the Spawn Point</summary>
	///<returns><see cref="FRotator" /> Rotation of SpawnPoint</returns>
	FRotator SpawnPoint::getRotation();

	///<summary>Returns the Tags of the Spawn Point</summary>
	///<returns><see cref="FString" /> Tags of SpawnPoint</returns>
	FString SpawnPoint::getTags();

};




