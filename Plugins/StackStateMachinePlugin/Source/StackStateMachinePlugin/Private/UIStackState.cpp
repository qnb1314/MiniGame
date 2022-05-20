#include "UIStackState.h"

void UUIStackState::EnterState(EStackAction StackAction)
{
	switch (StackAction)
	{
	case Push:
		AddToViewport();
		break;
	case Pop:
		SetVisibility(ESlateVisibility::Visible);
		break;
	}
	ReceiveEnterState(StackAction);
}

void UUIStackState::ExitState(EStackAction StackAction)
{
	switch (StackAction)
	{
	case Push:
		SetVisibility(ESlateVisibility::Hidden);
		break;
	case Pop:
		RemoveFromParent();
		break;
	}
	ReceiveExitState(StackAction);
}

void UUIStackState::UpdateState(float Deltatime)
{
	ReceiveUpdateState(Deltatime);
}