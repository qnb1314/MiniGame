#pragma once
#include "StackStateInterface.h"
#include "Components/ActorComponent.h"
#include "Containers/Array.h"
#include "UObject/ScriptInterface.h"
#include "StackStateMachineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStackStatePushPopSignature, TScriptInterface<IStackStateInterface>, State);

UCLASS(Blueprintable,BlueprintType,meta=(BlueprintSpawnableComponent))
class UStackStateMachineComponent :public UActorComponent
{
	GENERATED_BODY()

public:
	/* 组件帧事件 */
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	/* Push&Pop函数 */
	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PushState(TScriptInterface<IStackStateInterface> NewState);

	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PopState();

	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PopStates(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PopAllStates();


	/* 状态机内容获取函数定义 */
	UFUNCTION(BlueprintPure, Category = "StackStateMachine")
	FORCEINLINE TScriptInterface<IStackStateInterface> GetTopState() { return States[StateCount() - 1]; }

	UFUNCTION(BlueprintPure, Category = "StackStateMachine")
	FORCEINLINE TScriptInterface<IStackStateInterface> GetUnderState() { return States[StateCount() - 2]; }

	UFUNCTION(BlueprintPure, Category = "StackStateMachine")
	FORCEINLINE TScriptInterface<IStackStateInterface> GetState(int32 Index) { return States[Index]; }

	UFUNCTION(BlueprintPure, Category = "StackStateMachine")
	FORCEINLINE int32 StateCount()const { return States.Num(); }

	UFUNCTION(BlueprintPure, Category = "StackStateMachine")
	FORCEINLINE float GetTopStateTime() const { return TopStateTime; }

protected:
	/* 入出栈调用函数,针对于状态机 */
	virtual void StatePushed(TScriptInterface<IStackStateInterface> PushedState);
	virtual void StatePopped(TScriptInterface<IStackStateInterface> PoppedState);


	/* 蓝图回调事件,在蓝图中进行重载 */
	UFUNCTION(BlueprintImplementableEvent, Category = "StackStateMachine", meta = (DisplayName = "StatePushed"))
	void ReceiveStatePushed(EStackAction StackAction);

	UFUNCTION(BlueprintImplementableEvent, Category = "StackStateMachine", meta = (DisplayName = "StatePopped"))
	void ReceiveStatePopped(EStackAction StackAction);


	/* 入出栈事件委托 */
	UPROPERTY(BlueprintAssignable, Category = "StackStateMachine")
	FOnStackStatePushPopSignature OnStatePushed;

	UPROPERTY(BlueprintAssignable, Category = "StackStateMachine")
	FOnStackStatePushPopSignature OnStatePopped;


	/* 状态栈 */
	TArray<TScriptInterface<IStackStateInterface>> States;


	/* 记录栈顶部状态持续时间 */
	UPROPERTY(VisibleAnywhere)
	float TopStateTime = 0.0f;
};