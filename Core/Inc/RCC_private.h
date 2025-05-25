#ifndef   RCC_PRIVATE_H_
#define   RCC_PRIVATE_H_


#define   RCC_BASE_ADD   (u32)0x40023800

#include  "STD_TYPES.h"

//RCC_CREG
#define		HSION	        0
#define		HSEON		    16
#define     HSEBYP          18
#define     CSSON           19
#define		PLLON		    24

#define     SW0             0
#define     SW1             1



//AHB1_REG
#define     GPIOAEN_PER		0
#define     GPIOBEN_PER		1
#define     GPIOCEN_PER		2
#define     GPIODEN_PER		3
#define     GPIOEEN_PER		4
#define     GPIOHEN_PER		7
#define     CRC_PER		    12
#define     DMA1EN_PER		21
#define     DMA2EN_PER		22


//AHB2_REG
#define     OTGFSEN_PER		7


//APB1_REG
#define     TIM2EN_PER		0
#define     TIM3EN_PER		1
#define     TIM4EN_PER		2
#define     TIM5EN_PER		3
#define     WWDGEN_PER		11
#define     SPI2EN_PER		14
#define     SPI3EN_PER		15
#define     USART2EN_PER	17
#define     I2C1EN_PER		21
#define     I2C2EN_PER		22
#define     I2C3EN_PER		23
#define     PWREN_PER		28


//APB2_REG
#define     TIM1EN_PER		0
#define     USART1EN_PER	4
#define     USART6EN_PER	5
#define     ADC1EN_PER		8
#define     SDIOEN_PER		11
#define     SPI1EN_PER		12
#define     SPI4AEN_PER		13
#define     SYSCFGEN_PER	14
#define     TIM9EN_PER		16
#define     TIM10EN_PER		17
#define     TIM11EN_PER		18

typedef struct
{
	u32  CR;
	u32  PLLCFGR;
	u32  CFGR;
	u32  CIR;
	u32  AHB1RSTR;
	u32  AHB2RSTR;
	u32  RESRVED1;
	u32  RESERVED2;
	u32  APB1RSTR;
	u32  APB2RSTR;
	u32  RESERVED3;
	u32  RESERVED4;
	u32  AHB1ENR;
	u32  AHB2ENR;
	u32  RESERVED5;
	u32  RESERVED6;
	u32  APB1ENR;
	u32  APB2ENR;
	u32  RESERVED7;
	u32  RESERVED8;
	u32  AHB1LPENR;
	u32  AHB2LPENR;
	u32  RESERVED9;
	u32  RESERVED10;
	u32  APB1LPENR;
	u32  APB2LPENR;
	u32  RESERVED11;
	u32  RESERVED12;
	u32  BDCR;
	u32  CSR;
	u32  RESERVED13;
	u32  RESERVED14;
	u32  SSCGR;
	u32  PLLI2SCFGR;


}RCC_MemMap_t;

#define  			RCC   		   ((RCC_MemMap_t*)RCC_BASE_ADD)

#define  			ENABLE   	   0
#define  			DISABLE  	   1






#endif
