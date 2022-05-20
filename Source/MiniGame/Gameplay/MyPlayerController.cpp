// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "StackStateMachineComponent.h"

AMyPlayerController::AMyPlayerController()
{
	UIStackStateMachine = CreateDefaultSubobject<UStackStateMachineComponent>(TEXT("UIStackStateMachine"));
}