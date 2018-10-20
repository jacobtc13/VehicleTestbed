#pragma once

#include "CoreMinimal.h"


///<summary>SpawnPoint class for SpawnList, holds location name and a location coordinates</summary>


class VEHICLETESTBED_API SpawnPoint
{
private:
	FName spName;
	FVector Location;


public:
	
	///<summary>Default Constructor</summary>
	SpawnPoint();
	
	
	///<summary>Constructor with name and location provided</summary>
	SpawnPoint(FName Name, FVector Location);
	
	///<summary>Destructor</summary>
	~SpawnPoint();

	///<summary>Update the name of the SpawnPoint</summary>
	///<param name="newName">Name to be set</param>
	///<returns><see cref="bool" /> True if update is successful</returns>
	bool setName(FName newName);

	///<summary>Update the Location of the SpawnPoint</summary>
	///<param name="newLocation">Location to be set</param>
	///<returns><see cref="bool" /> True if update is successful</returns>
	bool SpawnPoint::setLocation(FVector newLocation);

	///<summary>Returns the name of the Spawn Point</summary>
	///<returns><see cref="FName" /> Name of SpawnPoint</returns>
	FVector SpawnPoint::getLocation();

	///<summary>Returns the Location of the Spawn Point</summary>
	///<returns><see cref="FVector" /> Location of SpawnPoint</returns>
	FName SpawnPoint::getName();

};




