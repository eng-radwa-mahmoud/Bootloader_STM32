
#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

/**********************************************/
/* 			USART Register Structure 		  */
/**********************************************/
typedef struct{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}USART_t;

/**********************************************/
/* 		The USART Structure Pointer 		  */
/**********************************************/
#define 	USART1 		((USART_t *)0x40011000)
#define 	USART2 		((USART_t *)0x40014400)
#define 	USART6 		((USART_t *)0x40011400)

typedef struct
{
	u32 BaudRate;

	u8 DataWidth;

	u8 StopBits;

	u8 Parity_Enable;

	u8 Parity_Selection;

	u8 TransferDirection; // TX_ONLY  RX_ONLY  TX_RX

	u8 HardwareFlowControl;

	u8 Oversampling;
}USART_InitType;

typedef struct
{
	u8 ClockOutput;
	u8 ClockPolarity;
	u8 ClockPhase;
	u8 LastBitClockPulse;
}USART_ClockInitTypeDef;

#define OVER_SAMPLING_16	0
#define OVER_SAMPLING_8 	1

#define TX_ONLY             0
#define RX_ONLY             1
#define TX_RX               2

#define EVEN_PARITY         0
#define ODD_PARITY          1

#define MODE_8BIT			0
#define MODE_9BIT			1

#define STOP_BIT_1			0
#define STOP_BIT_0_5		1
#define STOP_BIT_2			2
#define STOP_BIT_1_5		3

#define     USART1EN_PER	4

#define ENABLE				1
#define DISABLE				0

void MUSART_voidInit(USART_InitType *A_InitStruct,USART_ClockInitTypeDef *A_ClockInitStruct,USART_t *USARTx);
void MUSART_Enable(USART_t *USARTx);
void MUSART_voidTransmitByte (USART_t *USARTx,u8 A_u8Byte);
void MUSART_voidTransmitString (USART_t *USARTx, u8 * A_ptru8String );
u8 MUSART_vReceive_Synch(u8* A_pu8Byte);
u8   MUSART_u8ReceiveByteSynchNonBlocking ( USART_t *USARTx );
u8 * MUSART_ptrReceiveStringSynchNonBlocking ( USART_t *USARTx );
void MUSART_RxIntSetStatus(USART_t *USARTx, u8 copy_u8Status);
void MUSART_voidClearFlags(USART_t *USARTx);
u8   MUSART_u8ReadDataRegister(USART_t *USARTx);
void MUSART1_voidSetCallBack( void (*ptr) (void) );
void MUSART2_voidSetCallBack( void (*ptr) (void) );
void MUSART6_voidSetCallBack( void (*ptr) (void) );




#endif
