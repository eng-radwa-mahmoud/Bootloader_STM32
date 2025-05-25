#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include "RCC_config.h"
#include "RCC_interface.h"
#include "RCC_private.h"


void RCC_voidInit(void)
{
	/* 1- css(on/off) */
	if(RCC_CSS_ENABLE==ENABLE)
	{
		SET_BIT(RCC -> CR , CSSON);
	}
	else if (RCC_CSS_ENABLE==DISABLE)
	{
		CLR_BIT(RCC -> CR , CSSON);
	}

	/* 2- HSE_BYP */
	CLR_BIT(RCC -> CR , HSEBYP);

	/* 3- Select clock switch(HSI/HSE/PLL) */
	SET_BIT(RCC -> CFGR,SW0);
	CLR_BIT(RCC -> CFGR,SW1);
	/* 4- bus prescalars */
	/* 5- PLL configuration */

	/* 6- Enable selected clock (HSI on/HSE on/PLL on)*/
	if (RCC_HSE_ENABLE == ENABLE)
		{
		 SET_BIT(RCC -> CR, HSEON);
		}

}
void RCC_voidEnablePerClock(u32 BusId , u32 Per)
{
	switch(BusId)
	{
		case AHB1 : SET_BIT(RCC -> AHB1ENR,Per); break;
		case AHB2 : SET_BIT(RCC -> AHB2ENR,Per); break;
		case APB1 : SET_BIT(RCC -> APB1ENR,Per); break;
		case APB2 : SET_BIT(RCC -> APB2ENR,Per); break;
		case AHB1LP : SET_BIT(RCC -> AHB1LPENR,Per); break;
		default : /* ERROR */ break;
	}
}
void RCC_voidDisablePerClock(u32 BusId , u32 Per)
{
	switch(BusId)
	{
		case AHB1 : CLR_BIT(RCC -> AHB1ENR,Per); break;
		case AHB2 : CLR_BIT(RCC -> AHB2ENR,Per); break;
		case APB1 : CLR_BIT(RCC -> APB1ENR,Per); break;
		case APB2 : CLR_BIT(RCC -> APB2ENR,Per); break;
	}
}
