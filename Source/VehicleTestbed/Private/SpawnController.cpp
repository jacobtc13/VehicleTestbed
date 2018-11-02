// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnController.h"


SpawnPointList spList;


TArray<FName> getSpawnPointRefs() {
	
	return spList.getSpawnPointRefs();

}
