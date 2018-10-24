// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"


FName spName;
FVector spLocation;
FRotator spRotation;
FString spTags;


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
bool SpawnPoint::setName(FName newName) {
	
	spName = newName;
	
	return true;

}

// Updates SpawnPoint Location
bool SpawnPoint::setLocation(FVector newLocation) {
	spLocation = newLocation;

	return true;
}

// Updates SpawnPoint Rotation
bool SpawnPoint::setRotation(FRotator newRotation) {
	spRotation = newRotation;

	return true;
}

// Updates SpawnPoint Tags
bool SpawnPoint::setTags(FString newTags) {
	spTags = newTags;

	return true;
}

//Updated SpawnPoint Location and Rotation
bool SpawnPoint::setSpawnPoint(FVector newLocation, FRotator newRotation) {
	spLocation = newLocation;
	spRotation = newRotation;

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

// Returns SpawnPoint Rotation as an FRotator
FRotator SpawnPoint::getRotation() {
	return spRotation;
}

// Returns SpawnPoint Tags as an FString
FString SpawnPoint::getTags() {
	return spTags;
}


SpawnPoint::~SpawnPoint()
{
}
