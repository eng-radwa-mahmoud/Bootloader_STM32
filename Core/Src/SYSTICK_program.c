#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"
#include "SYSTICK_config.h"


static void (*STK_Callback)(void);
static u8 u8SingleFlag;

void STK_voidInit(void)
{
	/*Disable the Timer*/
	CLR_BIT(STK->CTRL,STK_ENABLE_BIT);

#if STK_CLK_SOURCE == STK_AHB
	SET_BIT(STK->CTRL,CLKSOURCE);
#else
	CLR_BIT(STK->CTRL,CLKSOURCE);
#endif

#if STK_INTERRPUT_EN==ENABLE
	SET_BIT(STK->CTRL, TICKINT) ;
#else
	CLR_BIT(STK->CTRL, TICKINT) ;
#endif
}

void STK_voidStartTimer(u32 LoadValue)
{
	STK -> LOAD = LoadValue;
	SET_BIT(STK->CTRL,STK_ENABLE_BIT);
}
void STK_voidStopTimer(void)
{
	CLR_BIT(STK->CTRL,STK_ENABLE_BIT);
}

void STK_voidSetBusyWait(u32 Ticks)
{
  /* 1- reset timer value */
	STK->VAL=0;
  /* 2- Load timer with value */
	STK->LOAD = Ticks;
  /* 3- Start timer */
	SET_BIT(STK->CTRL,STK_ENABLE_BIT);
  /* 4- wait for timer flag to be raised*/
	while((GET_BIT(STK->CTRL,COUNTFLAG))==0){}
	u8 countflag = (GET_BIT(STK->CTRL,COUNTFLAG));
	/* 5- Stop timer */
	CLR_BIT(STK->CTRL,STK_ENABLE_BIT);
	STK -> LOAD = 0;
	STK->VAL = 0;
}

void STK_voidSetInterval_Single(u32 Ticks,void(*CallbackFun)(void))
{
	  u8SingleFlag = 1;
	  /* 0- Set callback function */
	    STK_Callback = CallbackFun;
	  /* 1- reset timer value */
		STK->VAL=0;
	  /* 2- Load timer with value */
		STK->LOAD = Ticks;
	  /* 3- Start timer */
		SET_BIT(STK->CTRL,STK_ENABLE_BIT);

}
void STK_voidSetInterval_Periodic(u32 Ticks,void(*CallbackFun)(void))
{
	  u8SingleFlag = 0;
      /* 0- Set callback function */
      STK_Callback = CallbackFun;
	  /* 1- reset timer value */
		STK->VAL=0;
	  /* 2- Load timer with value */
		STK->LOAD = Ticks;
	  /* 3- Start timer */
		SET_BIT(STK->CTRL,STK_ENABLE_BIT);

}

u32 STK_GetElapsedTime(void)
{
  return (STK->LOAD - STK->VAL);
}
u32 STK_GetRemainingTime(void)
{
 return STK->VAL;
}

void SysTick_Handler(void)
{

  if(u8SingleFlag == 1)
  {
	  u8SingleFlag=0;
		/* 5- Stop timer */
		CLR_BIT(STK->CTRL,STK_ENABLE_BIT);
  }
  if (STK_Callback!=NULL)
  {
	  STK_Callback();
  }

}
