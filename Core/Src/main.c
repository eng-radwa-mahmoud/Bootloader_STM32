
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "RCC_interface.h"
#include "HexParser_interface.h"
#include "USART_interface.h"
#include "GPIO_interface2.h"

volatile u8 G_pu8RXBuffer[50];
volatile u8 G_u8RXBufferCounter = 0;

typedef void (*function_t)(void);
function_t App_Call = 0;

volatile u8 TimeoutFlag = 0;
volatile u8 EraseFlag = 0;
int i = 0;



void STK_Callback(void)
{

	if (i<88)
	{

		i++;
		STK_voidSetInterval_Single(16000000, STK_Callback);
	}
	else
	{
		//GPIOSetPinValue(PORTA, PIN2 , GPIO_HIGH);
  TimeoutFlag = 1;
  #define SCB_VTOR *((volatile u32*)(0xE000ED00+0x08))
  SCB_VTOR = 0x8004000;
  App_Call = *(function_t*) 0x8004004;
  App_Call();

	}

}

int main(void)
{

	RCC_voidInit();
    RCC_voidEnablePerClock(AHB1LP,15);
    RCC_voidEnablePerClock(APB2,USART1EN_PER);
    RCC_voidEnablePerClock(AHB1,GPIOAEN_PER);
    GPIO_Config_t Led = {PORTA,PIN2,.OutputSpeed = GPIO_SPEED_MEDIUM,.Mode =GPIO_MODE_OUTPUT,.OutputType = GPIO_OUTYPE_PUSHPULL };


    GPIO_Config_t UART_TX_Pin = {PORTA,PIN9,.OutputSpeed = GPIO_SPEED_MEDIUM,.Mode =GPIO_MODE_ALTFUN,.OutputType = GPIO_OUTYPE_PUSHPULL,.AltFunc = 7 };
    GPIO_Config_t UART_RX_Pin = {PORTA,PIN10,.OutputSpeed = GPIO_SPEED_MEDIUM,.Mode =GPIO_MODE_ALTFUN,.OutputType = GPIO_OUTYPE_PUSHPULL,.AltFunc = 7 };
    GPIO_VoidInit(&UART_TX_Pin);
    GPIO_VoidInit(&UART_RX_Pin);
    GPIO_VoidInit(&Led);

//    u8 record[] = ":10800000934206D8064A136008BD054A06491160B9";
//    //Flash_vFlashWrite(0x08008000, data, 3);
//    HexParser_vParseData(record);

    USART_InitType uart={9600,MODE_8BIT,STOP_BIT_1,DISABLE,EVEN_PARITY,TX_RX,DISABLE,OVER_SAMPLING_16};
    USART_ClockInitTypeDef uartclock ={DISABLE,0,0,0};

    MUSART_voidInit(&uart,&uartclock,USART1);
    MUSART_Enable(USART1);

    STK_voidInit();



    STK_voidSetInterval_Single(1600000000, STK_Callback);
    u8 L_u8UARTRXStatus = 0;

	while(TimeoutFlag==0)
	{
	    L_u8UARTRXStatus = MUSART_vReceive_Synch(&G_pu8RXBuffer[G_u8RXBufferCounter]);
	   // MUSART_voidTransmitByte(USART1, G_pu8RXBuffer[G_u8RXBufferCounter]);
	    if(L_u8UARTRXStatus == 1)
	    {
	    	if(G_pu8RXBuffer[2] == '2')
	    	{GPIOSetPinValue(PORTA, PIN2 , GPIO_HIGH);}

	    //	 MUSART_voidTransmitByte(USART1, G_pu8RXBuffer[G_u8RXBufferCounter]);
	    	/* Stop the timeout */
	    	STK_voidStopTimer();
	    	i=90;

	    	if (G_pu8RXBuffer[G_u8RXBufferCounter] == '\n')
	    	{
	    		GPIOSetPinValue(PORTA, PIN2 , GPIO_HIGH);
	    		if (EraseFlag !=1)
	    		    		{
	    		    		EraseFlag = 1;
	    		    		HexParser_vEraseAppArea();
	    		    		}
	    		HexParser_vParseData(G_pu8RXBuffer);

	    		MUSART_voidTransmitString(USART1,"ok");
	    		G_u8RXBufferCounter = 0;
	    	}
	    	else
	    	{
	    		//MUSART_voidTransmitString(USART1,"ok");
	    		G_u8RXBufferCounter++;
	    	}
	    	/* check for end of hex file */
	    	if (G_pu8RXBuffer[8] == '1')
	    	{
	    		STK_Callback();
	    	}
	    }

	}
}

