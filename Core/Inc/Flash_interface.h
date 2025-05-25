#ifndef FLASH_INTERFACE_H
#define FLASH_INTERFACE_H



void Flash_vEraseAppArea(void);
void Flash_vSectorErase(u8 A_u8SectorNo);
void Flash_vFlashWrite(u32 A_u32Address, u16* A_pu16Data,u16 A_u16Length);



#endif
