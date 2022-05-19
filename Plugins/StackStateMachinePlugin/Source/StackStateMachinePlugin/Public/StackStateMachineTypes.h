#pragma once
#include "UObject/Class.h"
#include "Logging/LogMacros.h"

/* 栈状态机的行为-压栈和出栈 */
UENUM(BlueprintType)
enum EStackAction { Push, Pop };

/* 定义模块Log */
DECLARE_LOG_CATEGORY_EXTERN(LogStackStateMachine, Log, All);
