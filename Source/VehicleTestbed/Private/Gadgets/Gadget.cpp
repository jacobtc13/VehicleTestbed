// Fill out your copyright notice in the Description page of Project Settings.

#include "Gadget.h"

Gadget::Gadget()
{
}

Gadget::~Gadget()
{
}

bool Gadget::IsMounted()
{
	return (GetMountedPawn() != NULL);
}

AMountablePawn *Gadget::GetMountedPawn()
{
	_mutexMountedPawn.lock();

	AMountablePawn *result = _mountedPawn;

	_mutexMountedPawn.unlock();

	return result;
}

int Gadget::SetMountedPawn(AMountablePawn *toSetTo)
{
	int result = 0;

	_mutexMountedPawn.lock();

	//Assume success for return codes
	if (IsMounted())
	{
		result = 1;//Successfully set from non-null reference
	}

	else
	{
		result = 0;//Successfully set from null refrence
	}

	_mountedPawn = toSetTo;

	_mutexMountedPawn.unlock();

	return result;
}
