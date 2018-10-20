// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"


FName spName;
FVector spLocation;


SpawnPoint::SpawnPoint(FName Name, FVector Location)
{
	FName spName = Name;
	FVector spLocation = Location;
}

// Updates Spawnpoint name
bool setName(FName newName) {
	
	spName = newName;
	
	return true;

}

// Updates SpawnPoint Location
bool setLocation(FVector newLocation) {
	spLocation = newLocation;

	return true;
}

// Returns SpawnPoint Name
FName getName() {
	return spName;
}

// Returns SpawnPoint Location as an FVector
FVector getLocation() {
	return spLocation;
}


SpawnPoint::~SpawnPoint()
{
}
