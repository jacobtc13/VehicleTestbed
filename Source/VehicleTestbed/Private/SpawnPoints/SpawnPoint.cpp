// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"




SpawnPoint::SpawnPoint(FName Name, FVector Location, FRotator Rotation, FString Tags)
{
	spName = Name;
	spLocation = Location;
	spRotation = Rotation;
	spTags = Tags;
}

// Default Constructor
SpawnPoint::SpawnPoint()
{
	spName = TEXT("defaultName");
	spLocation = FVector(float(0));
	spRotation = FRotator(float(0));
	spTags = TEXT("");
}

// Updates Spawnpoint name
void SpawnPoint::SetName(FName newName)
{
	spName = newName;
	
}

// Updates SpawnPoint Location
void SpawnPoint::SetLocation(FVector newLocation)
{
	spLocation = newLocation;
	
}

// Updates SpawnPoint Rotation
void SpawnPoint::SetRotation(FRotator newRotation)
{
	spRotation = newRotation;
	
}

// Updates SpawnPoint Tags
void SpawnPoint::SetTags(FString newTags)
{
	spTags = newTags;
	
}

//Updated SpawnPoint Location and Rotation
void SpawnPoint::SetSpawnPoint(FVector newLocation, FRotator newRotation)
{
	spLocation = newLocation;
	spRotation = newRotation;
	
}

// Returns SpawnPoint Name
FName SpawnPoint::GetName() const
{
	return spName;
}

// Returns SpawnPoint Location as an FVector
FVector SpawnPoint::GetLocation() const
{
	return spLocation;
}

// Returns SpawnPoint Rotation as an FRotator
FRotator SpawnPoint::GetRotation() const
{
	return spRotation;
}

// Returns SpawnPoint Tags as an FString
FString SpawnPoint::GetTags() const
{
	return spTags;
}


SpawnPoint::~SpawnPoint()
{}
