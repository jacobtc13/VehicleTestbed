// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MountablePawn.h"
#include <mutex>
#include "Gadget.generated.h"

/**
 * Base class which handles being mounted/dismounted from a pawn
 */
UCLASS()
class VEHICLETESTBED_API AGadget : public AActor
{
	GENERATED_BODY()

public:
	AGadget();
	~AGadget();

	UFUNCTION()
	///<summary>Returns true if this Gadget is mounted, otherwise false</summary>
	bool IsMounted();

	UFUNCTION()
	///<summary>Returns a pointer to the currently mounted pawn, can be NULL, blocks</summary>
	///<returns>A pointer to the currently mounted Pawn</returns>
	AMountablePawn* GetMountedPawn();

	UFUNCTION()
	///<summary>Sets the internal reference for the currently mounted pawn, blocks</summary>
	///<params name ='toSetTo'>Address of the Pawn this Gadget is mounted to</params>
	///<returns>Error code, 0 success, 1 success overriding data</returns>
	int SetMountedPawn(AMountablePawn *toSetTo);

private:
	///<summary>The internal reference for the currently mounted pawn</summary>
	AMountablePawn* _mountedPawn = nullptr;

	///<summary>MUTEX to synchronise access to _mountedPawn</summary>
	std::mutex _mutexMountedPawn;


};
