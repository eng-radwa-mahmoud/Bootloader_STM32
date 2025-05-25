#ifndef		STK_INTERFACE_H_
#define  	STK_INTERFACE_H_

#include "STD_TYPES.h"

void STK_voidInit(void);

void STK_voidStartTimer(u32 LoadValue);
void STK_voidStopTimer(void);

void STK_voidSetBusyWait(u32 Ticks);

void STK_voidSetInterval_Single(u32 Ticks,void(*CallbackFun)(void));
void STK_voidSetInterval_Periodic(u32 Ticks,void(*CallbackFun)(void));

u32 STK_GetElapsedTime(void);
u32 STK_GetRemainingTime(void);

#endif
