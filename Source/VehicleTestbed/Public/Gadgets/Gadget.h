// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MountablePawn.h"
#include <mutex>

/**
 * Base class which handles being mounted/dismounted from a pawn
 */
class VEHICLETESTBED_API Gadget
{
public:
	Gadget();
	~Gadget();

	UFUNCTION()
	///<summary>Returns true if this Gadget is mounted, otherwise false</summary>
	bool IsMounted();

	UFUNCTION()
	///<summary>Returns a pointer to the currently mounted pawn, can be NULL, blocks</summary>
	///<returns>A pointer to the currently mounted Pawn</returns>
	AMountablePawn *GetMountedPawn();

	UFUNCTION()
	///<summary>Sets the internal reference for the currently mounted pawn, blocks</summary>
	///<params name ='toSetTo'>Address of the Pawn this Gadget is mounted to</params>
	///<returns>Error code, 0 success, 1 success overriding data</returns>
	int SetMountedPawn(AMountablePawn *toSetTo);

private:
	///<summary>The internal reference for the currently mounted pawn</summary>
	AMountablePawn *_mountedPawn = NULL;

	///<summary>MUTEX to synchronise access to _mountedPawn</summary>
	std::mutex _mutexMountedPawn;


};
