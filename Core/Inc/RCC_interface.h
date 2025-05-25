#ifndef   RCC_INTERFACE_H_
#define   RCC_INTERFACE_H_

#include  "STD_TYPES.h"

#define		AHB1		    0
#define		AHB2		    1
#define		APB1		    2
#define		APB2		    3
#define     AHB1LP        4

#define     SYSCFG_EN       14

void RCC_voidInit(void);
void RCC_voidEnablePerClock(u32 BusId , u32 Per);
void RCC_voidDisablePerClock(u32 BusId , u32 Per);




#endif
