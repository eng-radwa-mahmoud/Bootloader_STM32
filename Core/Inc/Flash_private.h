#ifndef   FLASH_PRIVATE_H
#define   FLASH_PRIVATE_H

#define FLASH_BASE_ADD   0x40023C00

#define FLASH_KEY1   0x45670123
#define FLASH_KEY2   0xCDEF89AB




typedef struct
{
	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 OPTCR;

}Flash_MemMap_t;

#define   FLASH   ((volatile Flash_MemMap_t*)(FLASH_BASE_ADD))

#endif
