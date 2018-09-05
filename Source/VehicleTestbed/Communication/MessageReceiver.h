#pragma once

#include "CoreMinimal.h"
#include "Communication/Messager.h"
#include "MessageReceiver.generated.h"

UCLASS()
class VEHICLETESTBED_API UMessageReceiver : public UMessager
{
	GENERATED_BODY()

public:
	template <class Message>
	void Receive(Message message, float SNR)
	{

	}
};
