#pragma once
#include "StackStateInterface.h"
#include "Blueprint/UserWidget.h"
#include "UIStackState.generated.h"

UCLASS(ABSTRACT, BlueprintType, Blueprintable)
class MINIGAME_API UUIStackState :public UUserWidget, public IStackStateInterface
{
	GENERATED_BODY()

public:
	/* IStackStateInterface���� */
	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
	virtual void UpdateState(float Deltatime) override;

	/* ��ͼ�ص��¼�,����ͼ�н������� */
	UFUNCTION(BlueprintImplementableEvent, Category = "UIStackState", meta = (DisplayName = "OnEnterState"))
		void ReceiveEnterState(EStackAction StackAction);
	UFUNCTION(BlueprintImplementableEvent, Category = "UIStackState", meta = (DisplayName = "OnExitState"))
		void ReceiveExitState(EStackAction StackAction);
	UFUNCTION(BlueprintImplementableEvent, Category = "UIStackState", meta = (DisplayName = "OnUpdateState"))
		void ReceiveUpdateState(float Deltatime);
};