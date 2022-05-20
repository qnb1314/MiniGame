#pragma once
#include "StackStateMachineTypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Interface.h"
#include "StackStateInterface.generated.h"

UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class STACKSTATEMACHINEPLUGIN_API UStackStateInterface :public UInterface
{
	GENERATED_BODY()
};

class STACKSTATEMACHINEPLUGIN_API IStackStateInterface
{
	GENERATED_BODY()

public:
	//���붥��״̬
	virtual void EnterState(EStackAction StackAction) = 0;
	//�˳�����״̬
	virtual void ExitState(EStackAction StackAction) = 0;
	//����״̬
	virtual void UpdateState(float Deltatime) = 0;
};