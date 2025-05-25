#include "STD_TYPES.h"

#include "HexParser_interface.h"

#include "Flash_interface.h"

#define     FLASH_BASE_ADD   0x08000000
u16 DataBuffer [100];


static u8 HexParser_u8Ascii2Hex(u8 A_u8Ascii)

{
	u8 L_u8HexValue = 0;
	if(A_u8Ascii >='0' && A_u8Ascii<='9')
	{
		L_u8HexValue = A_u8Ascii - '0';
	}
	else if (A_u8Ascii >= 'A' && A_u8Ascii<='F')
	{
		L_u8HexValue = A_u8Ascii - 55; //55 = 'A'-10
	}
return L_u8HexValue;
}

void HexParser_vParseData(u8 A_pu8Data[])
{
	/* charcter count variables */
	u8 cc_high, cc_low, cc;

	/* 4 digits for conversion */
	u8 digit0, digit1, digit2, digit3 ;

	/* Address variable */
	u32 address = 0;

	/* 1- convert character count */
	cc_high = HexParser_u8Ascii2Hex(A_pu8Data[1]);
	cc_low =  HexParser_u8Ascii2Hex(A_pu8Data[2]);
	cc = (cc_high<<4)|cc_low;

	/* 2- convert address */
	digit0 =  HexParser_u8Ascii2Hex(A_pu8Data[3]);
	digit1 =  HexParser_u8Ascii2Hex(A_pu8Data[4]);
	digit2 =  HexParser_u8Ascii2Hex(A_pu8Data[5]);
	digit3 =  HexParser_u8Ascii2Hex(A_pu8Data[6]);
	address = (FLASH_BASE_ADD)|
			  (digit0<<12)|
			  (digit1<<8)|
			  (digit2<<4)|(digit3<<0);

	for (u8 i=0;i<(cc/2);i++)
	{
		digit0 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+9]);
		digit1 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+10]);
		digit2 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+11]);
		digit3 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+12]);

		DataBuffer[i] = (digit0<<12)|
				  (digit1<<8)|
				  (digit2<<4)|(digit3<<0);
	}

	Flash_vFlashWrite(address,DataBuffer,cc/2);

}

void HexParser_vEraseAppArea(void)
{
	Flash_vEraseAppArea();
}
