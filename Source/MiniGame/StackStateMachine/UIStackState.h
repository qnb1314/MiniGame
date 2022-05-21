#pragma once
#include "StackStateInterface.h"
#include "Blueprint/UserWidget.h"
#include "UIStackState.generated.h"

UCLASS(ABSTRACT, BlueprintType, Blueprintable)
class MINIGAME_API UUIStackState :public UUserWidget, public IStackStateInterface
{
	GENERATED_BODY()

public:
	/* IStackStateInterface定义 */
	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
	virtual void UpdateState(float Deltatime) override;

	/* 蓝图回调事件,在蓝图中进行重载 */
	UFUNCTION(BlueprintImplementableEvent, Category = "UIStackState", meta = (DisplayName = "OnEnterState"))
		void ReceiveEnterState(EStackAction StackAction);
	UFUNCTION(BlueprintImplementableEvent, Category = "UIStackState", meta = (DisplayName = "OnExitState"))
		void ReceiveExitState(EStackAction StackAction);
	UFUNCTION(BlueprintImplementableEvent, Category = "UIStackState", meta = (DisplayName = "OnUpdateState"))
		void ReceiveUpdateState(float Deltatime);
};