#include "StackStateMachineComponent.h"

void UStackStateMachineComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (StateCount() > 0)
	{
		TScriptInterface<IStackStateInterface> CurrentState = GetTopState();
		if (CurrentState != nullptr)
		{
			TopStateTime += DeltaTime;
			CurrentState->UpdateState(DeltaTime);
		}
	}
}

void UStackStateMachineComponent::PushState(TScriptInterface<IStackStateInterface> NewState)
{
	//Before:ִ��ԭ״̬�˳�
	if (StateCount() > 0)
	{
		TScriptInterface<IStackStateInterface> PreState = GetTopState();
		if (PreState != nullptr) PreState->ExitState(EStackAction::Push);
	}

	//Now:��״̬��ջ
	States.Push(NewState);
	
	//After:ִ��ʱ�����->ִ����״̬����->����Pushed����
	TopStateTime = 0.0f;
	NewState->EnterState(EStackAction::Push);
	StatePushed(NewState);
}

void UStackStateMachineComponent::PopState()
{
	if (StateCount() > 0)
	{
		//Before:ִ��ԭ״̬�˳�
		TScriptInterface<IStackStateInterface> PreState = GetTopState();
		if (PreState != nullptr) PreState->ExitState(EStackAction::Pop);

		//Now:����״̬��ջ
		States.Pop();

		//After:ִ��ʱ�����->�ж��Ƿ���״̬->ִ����״̬����->����Popped����
		TopStateTime = 0.0f;
		if (StateCount() > 0)
		{
			TScriptInterface<IStackStateInterface> NewState = GetTopState();
			if (NewState != nullptr) NewState->EnterState(EStackAction::Pop);
		}
		StatePopped(PreState);
	}
}

void UStackStateMachineComponent::PopStates(int32 Count)
{
	while (Count > 0)
	{
		PopState();
		Count--;
	}
}

void UStackStateMachineComponent::PopAllStates()
{
	PopStates(StateCount());
}


void UStackStateMachineComponent::StatePushed(TScriptInterface<IStackStateInterface> PushedState)
{
	UE_LOG(LogStackStateMachine, Display, TEXT("Pushed״̬:%s"), *PushedState.GetObject()->GetName());

	if (OnStatePushed.IsBound())
	{
		OnStatePushed.Broadcast(PushedState);
	}
}

void UStackStateMachineComponent::StatePopped(TScriptInterface<IStackStateInterface> PoppedState)
{
	UE_LOG(LogStackStateMachine, Display, TEXT("Popped״̬:%s"), *PoppedState.GetObject()->GetName());

	if (OnStatePopped.IsBound())
	{
		OnStatePopped.Broadcast(PoppedState);
	}
}