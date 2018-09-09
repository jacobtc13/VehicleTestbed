// Fill out your copyright notice in the Description page of Project Settings.

#include "GadgetMountingSocket.h"

GadgetMountingSocket::GadgetMountingSocket(FVector psoition)
{

}

GadgetMountingSocket::~GadgetMountingSocket()
{
}

Gadget * GadgetMountingSocket::GetMountedGadget()
{
	Gadget *result = NULL;

	_mutexMountedGadget.lock();

	result = _mountedGadget;

	_mutexMountedGadget.unlock();

	return result;
}

int GadgetMountingSocket::SetMountedGadget(Gadget * toSetTo)
{
	int result = 0;

	_mutexMountedGadget.lock();

	//Assume success for return codes
	if (_mountedGadget != NULL)
	{
		result = 1;//Successfully set from non-null reference
	}

	else
	{
		result = 0;//Successfully set from null refrence
	}

	_mountedGadget = toSetTo;

	_mutexMountedGadget.unlock();

	return result;
}
