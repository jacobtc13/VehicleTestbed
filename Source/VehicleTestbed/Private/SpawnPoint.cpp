// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"




SpawnPoint::SpawnPoint(FName Name, FVector Location, FRotator Rotation, FString Tags)
{
	FName spName = Name;
	FVector spLocation = Location;
	FRotator spRotation = Rotation;
	FString spTags = Tags;
}

// Default Constructor
SpawnPoint::SpawnPoint() {

	FName spName = TEXT("defaultName");
	FVector spLocation = FVector(float(0));
	FRotator spRoation = FRotator(float(0));
	FString spTags = TEXT("");

}

// Updates Spawnpoint name
bool SpawnPoint::SetName(FName newName) {

	spName = newName;
	if (spName == newName) { return true; }
	else { return false; };

}

// Updates SpawnPoint Location
bool SpawnPoint::SetLocation(FVector newLocation) {
	spLocation = newLocation;
	if (spLocation == newLocation) { return true; }
	else { return false; };
	return true;
}

// Updates SpawnPoint Rotation
bool SpawnPoint::SetRotation(FRotator newRotation) {
	spRotation = newRotation;
	if (spRotation == newRotation) { return true; }
	else { return false; };
}

// Updates SpawnPoint Tags
bool SpawnPoint::SetTags(FString newTags) {
	spTags = newTags;
	if (spTags == newTags) { return true; }
	else { return false; };

}

//Updated SpawnPoint Location and Rotation
bool SpawnPoint::SetSpawnPoint(FVector newLocation, FRotator newRotation) {
	spLocation = newLocation;
	spRotation = newRotation;
	if ((spLocation == newLocation) && (spRotation == newRotation)) { return true; }
	else { return false; };

}

// Returns SpawnPoint Name
FName SpawnPoint::GetName() {
	return spName;
}

// Returns SpawnPoint Location as an FVector
FVector SpawnPoint::GetLocation() {
	return spLocation;
}

// Returns SpawnPoint Rotation as an FRotator
FRotator SpawnPoint::GetRotation() {
	return spRotation;
}

// Returns SpawnPoint Tags as an FString
FString SpawnPoint::GetTags() {
	return spTags;
}


SpawnPoint::~SpawnPoint()
{
}
