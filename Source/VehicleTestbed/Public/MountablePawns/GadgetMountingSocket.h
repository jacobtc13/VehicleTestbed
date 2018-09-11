// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gadget.h"
#include <mutex>

/**
 * 
 */
class VEHICLETESTBED_API GadgetMountingSocket
{
private:
	///<summary>Internal reference to the gadget mounted at this position</summary>
	Gadget * _mountedGadget = NULL;

	///<summary>Position of this mounting socket</summary>
	FVector _position;

	std::mutex _mutexMountedGadget;
	std::mutex _mutexPosition;

public:
	GadgetMountingSocket(FVector postion);
	~GadgetMountingSocket();

	///<summary>Returns the pointer to the mounted gadget, can be NULL, blocks</summary>
	///<returns>Pointer to mounted gadget</returns>
	Gadget * GetMountedGadget();

	///<summary>Sets the internal refrence for the mounted gadget</summary>
	///<params name='toSetTo'>Pointer to replace current refrence to mounted gadget</params>
	///<returns>Error code, 0 success, 1 success overriding data</returns>
	int SetMountedGadget(Gadget *toSetTo);
};
