#pragma once
#include "StackStateInterface.h"
#include "UObject/Object.h"
#include "StackState.generated.h"

UCLASS(ABSTRACT, BlueprintType, Blueprintable, HideCategories = ("Cooking", "LOD", "Physics", "Activation", "Tags", "Rendering"))
class STACKSTATEMACHINEPLUGIN_API UStackState :public UObject, public IStackStateInterface
{
	GENERATED_BODY()

public:
	/* IStackStateInterface���� */
	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
	virtual void UpdateState(float Deltatime) override;

	/* ��ͼ�ص��¼�,����ͼ�н������� */
	UFUNCTION(BlueprintImplementableEvent, Category = "StackState", meta = (DisplayName = "OnEnterState"))
	void ReceiveEnterState(EStackAction StackAction);
	UFUNCTION(BlueprintImplementableEvent, Category = "StackState", meta = (DisplayName = "OnExitState"))
	void ReceiveExitState(EStackAction StackAction);
	UFUNCTION(BlueprintImplementableEvent, Category = "StackState", meta = (DisplayName = "OnUpdateState"))
	void ReceiveUpdateState(float Deltatime);
};