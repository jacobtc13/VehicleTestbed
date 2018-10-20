// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"


FName spName;
FVector spLocation;
FString defName;


SpawnPoint::SpawnPoint(FName Name, FVector Location)
{
	FName spName = Name;
	FVector spLocation = Location;
}

// Default Constructor
SpawnPoint::SpawnPoint() {
	
	SpawnPoint(TEXT("defaultName"), FVector(float(0)));
}

// Updates Spawnpoint name
bool SpawnPoint::setName(FName newName) {
	
	spName = newName;
	
	return true;

}

// Updates SpawnPoint Location
bool SpawnPoint::setLocation(FVector newLocation) {
	spLocation = newLocation;

	return true;
}

// Returns SpawnPoint Name
FName SpawnPoint::getName() {
	return spName;
}

// Returns SpawnPoint Location as an FVector
FVector SpawnPoint::getLocation() {
	return spLocation;
}


SpawnPoint::~SpawnPoint()
{
}
