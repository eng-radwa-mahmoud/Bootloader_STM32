#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "Flash_interface.h"
#include "Flash_private.h"
#include "Flash_config.h"


void Flash_vEraseAppArea(void)
{
	for(u8 i=1; i<=7; i++)
	{
		Flash_vSectorErase(i);
	}

}
void Flash_vSectorErase(u8 A_u8SectorNo)
{
	/* 1- wait if flash is busy */
	while(GET_BIT(FLASH -> SR,16)==1){asm("NOP");}

	/* 2- Unlock flash register using KEYR */
	if(GET_BIT(FLASH->CR,31)==1)
	{
		FLASH->KEYR = FLASH_KEY1;
		FLASH->KEYR = FLASH_KEY2;

	}

	/* 3- Select sector num to erase */
	FLASH->CR &=~((u32)(0b1111<<3));
	FLASH->CR |= (A_u8SectorNo<<3);

	/* 4- Select erase operation */
	SET_BIT(FLASH->CR,1);


	/* 5- Start erase operation */
	SET_BIT(FLASH->CR,16);

	/* 6- Wait for busy flag (cleared automatically) */
	while(GET_BIT(FLASH -> SR,16)==1){asm("NOP");}

	/* 7- Clear EOP flag */
	SET_BIT(FLASH->SR,0);

	/* 8- Deselect Erase operation ( Reverse of step 4 ) */
	CLR_BIT(FLASH->CR,1);

}
void Flash_vFlashWrite(u32 A_u32Address, u16* A_pu16Data,u16 A_u16Length)
{
	/* 1- wait if flash is busy */
	while(GET_BIT(FLASH -> SR,16)==1){asm("NOP");}

	/* 2- Unlock flash register using KEYR */
	if(GET_BIT(FLASH->CR,31)==1)
	{
		FLASH->KEYR = FLASH_KEY1;
		FLASH->KEYR = FLASH_KEY2;
	}

	/* 3- Select element size ( PSIZE ) */
    FLASH->CR &= ~((u32)(0b11<<8));
    FLASH->CR |= (0b01<<8);

    /* 4- Activate programming Mode (PG bit) */
	SET_BIT(FLASH->CR,0);

	/* 5- Write data array on flash address */
	for(u16 i=0;i<A_u16Length;i++)
	{
		*((volatile u16*)A_u32Address) = A_pu16Data[i];
		A_u32Address += 2;

		while(GET_BIT(FLASH -> SR,16)==1){asm("NOP");}

		/* 7- Clear EOP flag */
		SET_BIT(FLASH->SR,0);
	}

	/* 8- Deactivate programming mode */
	CLR_BIT(FLASH->CR,0);



}
