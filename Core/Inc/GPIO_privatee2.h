#ifndef		GPIO_PRIVATE_H
#define		GPIO_PRIVATE_H

#include     "STD_TYPES.h"

#define		GPIOA_BASE_ADD		(u32)(0x40020000)
#define		GPIOB_BASE_ADD		(u32)(0x40020400)
#define		GPIOC_BASE_ADD		(u32)(0x40020800)

typedef  struct
{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;

}GPIO_MemMap_t;


#define GPIOA   ((volatile GPIO_MemMap_t*)GPIOA_BASE_ADD)
#define GPIOB   ((volatile GPIO_MemMap_t*)GPIOB_BASE_ADD)
#define GPIOC   ((volatile GPIO_MemMap_t*)GPIOC_BASE_ADD)

#endif
