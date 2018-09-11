// Fill out your copyright notice in the Description page of Project Settings.

#include "GadgetMountingSocket.h"


UGadgetMountingSocket::UGadgetMountingSocket()
{
}

UGadgetMountingSocket::~UGadgetMountingSocket()
{
}

AGadget *UGadgetMountingSocket::GetMountedGadget()
{
	AGadget * result = nullptr;

	_mutexMountedGadget.lock();

	result = _mountedGadget;

	_mutexMountedGadget.unlock();

	return result;
}

int UGadgetMountingSocket::SetMountedGadget(AGadget *toSetTo)
{
	int result = 0;

	_mutexMountedGadget.lock();

	//Assume success for return codes
	if (_mountedGadget != nullptr)
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
