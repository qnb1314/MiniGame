#pragma once
#include "StackStateMachineTypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Interface.h"
#include "StackStateInterface.generated.h"

UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class UStackStateInterface :public UInterface
{
	GENERATED_BODY()
};

class IStackStateInterface
{
	GENERATED_BODY()

public:
	//½øÈë¶¥²ã×´Ì¬
	virtual void EnterState(EStackAction StackAction) = 0;
	//ÍË³ö¶¥²ã×´Ì¬
	virtual void ExitState(EStackAction StackAction) = 0;
	//¸üÐÂ×´Ì¬
	virtual void UpdateState(float Deltatime) = 0;
};