#include "StackState.h"

void UStackState::EnterState(EStackAction StackAction)
{
	ReceiveEnterState(StackAction);
}

void UStackState::ExitState(EStackAction StackAction)
{
	ReceiveExitState(StackAction);
}

void UStackState::UpdateState(float Deltatime)
{
	ReceiveUpdateState(Deltatime);
}