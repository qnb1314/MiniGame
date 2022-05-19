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
	//Before:执行原状态退出
	if (StateCount() > 0)
	{
		TScriptInterface<IStackStateInterface> PreState = GetTopState();
		if (PreState != nullptr) PreState->ExitState(EStackAction::Push);
	}

	//Now:新状态入栈
	States.Push(NewState);
	
	//After:执行时间归零->执行新状态进入->调用Pushed函数
	TopStateTime = 0.0f;
	NewState->EnterState(EStackAction::Push);
	StatePushed(NewState);
}

void UStackStateMachineComponent::PopState()
{
	if (StateCount() > 0)
	{
		//Before:执行原状态退出
		TScriptInterface<IStackStateInterface> PreState = GetTopState();
		if (PreState != nullptr) PreState->ExitState(EStackAction::Pop);

		//Now:顶层状态出栈
		States.Pop();

		//After:执行时间归零->判断是否还有状态->执行新状态进入->调用Popped函数
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
	UE_LOG(LogStackStateMachine, Display, TEXT("Pushed状态:%s"), *PushedState.GetObject()->GetName());

	if (OnStatePushed.IsBound())
	{
		OnStatePushed.Broadcast(PushedState);
	}
}

void UStackStateMachineComponent::StatePopped(TScriptInterface<IStackStateInterface> PoppedState)
{
	UE_LOG(LogStackStateMachine, Display, TEXT("Popped状态:%s"), *PoppedState.GetObject()->GetName());

	if (OnStatePopped.IsBound())
	{
		OnStatePopped.Broadcast(PoppedState);
	}
}