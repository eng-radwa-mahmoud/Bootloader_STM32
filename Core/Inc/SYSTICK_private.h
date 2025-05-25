#ifndef		STK_PRIVATE_H_
#define  	STK_PRIVATE_H_


#define   STK_AHB              1
#define   STK_AHB_DIV_8        0

#define   STK_ENABLE_BIT   0
#define   CLKSOURCE        2
#define   TICKINT          1
#define   COUNTFLAG        16

#define   ENABLE           0
#define   DISABLE          1

#define  STK_BASE_ADD      0xE000E010

typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;

}STK_MemMap_t;

#define  STK ((volatile STK_MemMap_t*)STK_BASE_ADD)

#endif
