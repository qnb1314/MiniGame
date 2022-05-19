#pragma once
#include "UObject/Class.h"
#include "Logging/LogMacros.h"

/* ջ״̬������Ϊ-ѹջ�ͳ�ջ */
UENUM(BlueprintType)
enum EStackAction { Push, Pop };

/* ����ģ��Log */
DECLARE_LOG_CATEGORY_EXTERN(LogStackStateMachine, Log, All);
