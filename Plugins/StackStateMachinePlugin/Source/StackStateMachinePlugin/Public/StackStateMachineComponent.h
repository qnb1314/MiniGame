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
	/* ���֡�¼� */
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	/* Push&Pop���� */
	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PushState(TScriptInterface<IStackStateInterface> NewState);

	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PopState();

	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PopStates(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PopAllStates();


	/* ״̬�����ݻ�ȡ�������� */
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
	/* ���ջ���ú���,�����״̬�� */
	virtual void StatePushed(TScriptInterface<IStackStateInterface> PushedState);
	virtual void StatePopped(TScriptInterface<IStackStateInterface> PoppedState);


	/* ��ͼ�ص��¼�,����ͼ�н������� */
	UFUNCTION(BlueprintImplementableEvent, Category = "StackStateMachine", meta = (DisplayName = "StatePushed"))
	void ReceiveStatePushed(EStackAction StackAction);

	UFUNCTION(BlueprintImplementableEvent, Category = "StackStateMachine", meta = (DisplayName = "StatePopped"))
	void ReceiveStatePopped(EStackAction StackAction);


	/* ���ջ�¼�ί�� */
	UPROPERTY(BlueprintAssignable, Category = "StackStateMachine")
	FOnStackStatePushPopSignature OnStatePushed;

	UPROPERTY(BlueprintAssignable, Category = "StackStateMachine")
	FOnStackStatePushPopSignature OnStatePopped;


	/* ״̬ջ */
	TArray<TScriptInterface<IStackStateInterface>> States;


	/* ��¼ջ����״̬����ʱ�� */
	UPROPERTY(VisibleAnywhere)
	float TopStateTime = 0.0f;
};