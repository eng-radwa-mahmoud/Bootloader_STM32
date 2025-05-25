#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"


u8 global_u8String[20];

void (*MUSART1_CallBack)(void);
void (*MUSART2_CallBack)(void);
void (*MUSART6_CallBack)(void);



void MUSART_voidInit(USART_InitType *A_InitStruct,USART_ClockInitTypeDef *A_ClockInitStruct,USART_t *USARTx)
{
	switch (A_InitStruct->Oversampling)
	{
	case OVER_SAMPLING_16: USARTx->BRR = UART_BRR_SAMPLING16(__PCLK__,A_InitStruct->BaudRate); break;
	case OVER_SAMPLING_8 : USARTx->BRR = UART_BRR_SAMPLING8(__PCLK__,A_InitStruct->BaudRate); break;
	}

	USARTx->CR1 = (A_InitStruct->Oversampling << MUSART_CR1_OVER8_BIT)     |
			      (A_InitStruct->HardwareFlowControl<<MUSART_CR1_UE_BIT)   |
				  (A_InitStruct->DataWidth <<MUSART_CR1_M_BIT)             |
				  (A_InitStruct->Parity_Enable <<MUSART_CR1_PCE_BIT)       |
				  (A_InitStruct->Parity_Selection <<MUSART_CR1_PS_BIT)     ;
	switch (A_InitStruct->TransferDirection)
	{
	case TX_ONLY: SET_BIT(USARTx->CR1, MUSART_CR1_TE_BIT); break;
	case RX_ONLY: SET_BIT(USARTx->CR1, MUSART_CR1_RE_BIT); break;
	case TX_RX:   SET_BIT(USARTx->CR1, MUSART_CR1_TE_BIT);
				  SET_BIT(USARTx->CR1, MUSART_CR1_RE_BIT); break;
	}
	USARTx->CR2 =   (A_InitStruct->StopBits<<MUSART_CR2_STOP_BIT)				  |
					(A_ClockInitStruct->ClockOutput <<MUSART_CR2_CLKEN_BIT)       |
					(A_ClockInitStruct->ClockPhase <<MUSART_CR2_CPHA_BIT)         |
					(A_ClockInitStruct->ClockPolarity <<MUSART_CR2_CPOL_BIT)      |
					(A_ClockInitStruct->LastBitClockPulse <<MUSART_CR2_LBCL_BIT)  ;

	USARTx->SR = 0																  ;
}


void MUSART_Enable(USART_t *USARTx)
{
	SET_BIT(USARTx->CR1,MUSART_CR1_UE_BIT);
}
void MUSART_Disable(USART_t *USARTx)
{
	CLR_BIT(USARTx->CR1,MUSART_CR1_UE_BIT);
}

void MUSART_voidTransmitByte (USART_t *USARTx,u8 A_u8Byte)
{
	USARTx->DR= A_u8Byte;
	while (GET_BIT(USARTx->SR,MUSART_SR_TC_BIT)==0)
		{
			asm("NOP");
		}
	CLR_BIT(USARTx->SR,MUSART_SR_TC_BIT);
}


void MUSART_voidTransmitString (USART_t *USARTx, u8 * A_ptru8String )
{
	u8 loc_u8Iterator =0;
	while (A_ptru8String[loc_u8Iterator] != '\0')
	{
		MUSART_voidTransmitByte(USARTx, A_ptru8String[loc_u8Iterator]);
		loc_u8Iterator++;
	}
}

u8 MUSART_u8ReceiveByteSynchNonBlocking ( USART_t *USARTx )
{
	u8 loc_u8Data = 0;
	u32 loc_u8TimeOut = 0;
	while ((GET_BIT(USARTx->SR,MUSART_SR_RXNE_BIT)==0) && (loc_u8TimeOut < THRESHOLD_VALUE) )
	{
		loc_u8TimeOut++;
	}
	if (loc_u8TimeOut==THRESHOLD_VALUE)
	{
		loc_u8Data = 255;
	}
	else
	{
		loc_u8Data = USARTx->DR;
	}
	return loc_u8Data;
}

u8 * MUSART_ptrReceiveStringSynchNonBlocking ( USART_t *USARTx )
{
	u8 loc_Iterator = 0 , loc_u8DataCome ;
	while( ( loc_u8DataCome = MUSART_u8ReceiveByteSynchNonBlocking(USARTx) ) != 13 )
	{
		global_u8String[ loc_Iterator ] = loc_u8DataCome ;
		loc_Iterator++;
	}
	global_u8String[loc_Iterator] = '\0';
	return ( global_u8String );
}

u8 MUSART_u8ReadDataRegister(USART_t *USARTx)
{
	return USARTx -> DR;
}

void MUSART_voidClearFlags(USART_t *USARTx)
{
	USARTx -> SR=0;
}

void MUSART_RxIntSetStatus(USART_t *USARTx, u8 copy_u8Status)
{
	switch (copy_u8Status)
	{
	case ENABLE:  SET_BIT(USARTx->CR1 ,(MUSART_CR1_RXNEIE_BIT)); break;
	case DISABLE: CLR_BIT(USARTx->CR1 ,(MUSART_CR1_RXNEIE_BIT)); break;
	}

}

u8 MUSART_vReceive_Synch(u8* A_pu8Byte)
{
	u8 L_u8status = 1;
	if((GET_BIT(USART1->SR,MUSART_SR_RXNE_BIT))==1)
	{
		*A_pu8Byte = USART1->DR;
		CLR_BIT(USART1->SR,MUSART_SR_RXNE_BIT);
	}
	else
	{
		L_u8status = 0;
	}
	return L_u8status;
}

void MUSART1_voidSetCallBack( void (*ptr) (void) )
{
	MUSART1_CallBack = ptr ;
}

void MUSART2_voidSetCallBack( void (*ptr) (void) )
{
	MUSART2_CallBack = ptr ;
}

void MUSART6_voidSetCallBack( void (*ptr) (void) )
{
	MUSART6_CallBack = ptr ;
}

void USART1_IRQHandler(void)
{
	USART1 -> SR = 0 ;
	MUSART1_CallBack();
}

void USART2_IRQHandler(void)
{
	USART2 -> SR = 0 ;
	MUSART2_CallBack();
}

void USART6_IRQHandler(void)
{
	USART6 -> SR = 0 ;
	MUSART6_CallBack();
}
