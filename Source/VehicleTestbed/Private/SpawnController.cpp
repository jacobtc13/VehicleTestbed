// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnController.h"




TArray<FName> USpawnController::GetSpawnPointRefs() const
{
	return spList.GetSpawnPointRefs();
}
