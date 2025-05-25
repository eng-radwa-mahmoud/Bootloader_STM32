#include  "GPIO_interface2.h"
#include  "GPIO_privatee2.h"
#include   "GPIO_config2.h"

#include     "STD_TYPES.h"
#include     "BIT_MATH.h"



void GPIO_voidSetPinMode(u8 PortId, u8 PinNo, u8 Mode)
{   switch (PortId)
{
	case PORTA: (GPIOA -> MODER) &= ~(0b11<<(PinNo*2));
	(GPIOA -> MODER) |= (Mode)<<(PinNo*2); break;

	case PORTB: (GPIOB -> MODER) &= ~(0b11<<(PinNo*2));
		(GPIOB -> MODER) |= (Mode)<<(PinNo*2); break;

	case PORTC: (GPIOC -> MODER) &= ~(0b11<<(PinNo*2));
		(GPIOC -> MODER) |= (Mode)<<(PinNo*2); break;

}
}
void GPIOSetPinOutputType(u8 PortId, u8 PinNo, u8 OutType)
{   if (OutType == GPIO_OUTYPE_OPENDRAIN)
{
	switch (PortId)
	{
	case PORTA:
		SET_BIT (GPIOA -> OTYPER , PinNo);
		break;
	case PORTB:
		SET_BIT (GPIOB -> OTYPER , PinNo);
		break;
	case PORTC:
		SET_BIT (GPIOC -> OTYPER , PinNo);
		break;
	}
}
else if (OutType == GPIO_OUTYPE_PUSHPULL)
{
	switch (PortId)
	{
	case PORTA:
		CLR_BIT (GPIOA -> OTYPER , PinNo);
		break;
	case PORTB:
		CLR_BIT (GPIOB -> OTYPER , PinNo);
		break;
	case PORTC:
		CLR_BIT (GPIOC -> OTYPER , PinNo);
		break;
	}
}
}
void GPIOSetPinOutputSpeed(u8 PortId, u8 PinNo, u8 OutSpeed )
{
	  switch (PortId)
	{
		case PORTA: (GPIOA -> OSPEEDR) &= ~(0b11<<(PinNo*2));
		(GPIOA -> OSPEEDR) |= (OutSpeed)<<(PinNo*2); break;

		case PORTB: (GPIOB -> OSPEEDR) &= ~(0b11<<(PinNo*2));
			(GPIOB -> OSPEEDR) |= (OutSpeed)<<(PinNo*2); break;

		case PORTC: (GPIOC -> OSPEEDR) &= ~(0b11<<(PinNo*2));
			(GPIOC -> OSPEEDR) |= (OutSpeed)<<(PinNo*2); break;

	}
}
void GPIOSetPinInputPull(u8 PortId, u8 PinNo, u8 Pull)
{
	  switch (PortId)
	{
		case PORTA: (GPIOA -> PUPDR) &= ~(0b11<<(PinNo*2));
		(GPIOA -> PUPDR) |= (Pull)<<(PinNo*2); break;

		case PORTB: (GPIOB -> PUPDR) &= ~(0b11<<(PinNo*2));
			(GPIOB -> PUPDR) |= (Pull)<<(PinNo*2); break;

		case PORTC: (GPIOC -> PUPDR) &= ~(0b11<<(PinNo*2));
			(GPIOC -> PUPDR) |= (Pull)<<(PinNo*2); break;

	}
}
u8   GPIOGetPinValue(u8 PortId, u8 PinNo)
{   u8 Local_u8PinValue;
	switch (PortId)
	{
	case PORTA:
		Local_u8PinValue = GET_BIT(GPIOA->IDR,PinNo);
		break;
	case PORTB:
		Local_u8PinValue = GET_BIT(GPIOB->IDR,PinNo);
		break;
	case PORTC:
		Local_u8PinValue = GET_BIT(GPIOC->IDR,PinNo);
		break;
	}
	return Local_u8PinValue;
}
void GPIOSetPinValue(u8 PortId, u8 PinNo, u8 Value)
{

	if(Value == GPIO_HIGH)
	{
		switch (PortId)
	{
	case PORTA:
        SET_BIT(GPIOA->ODR,PinNo);
		break;
	case PORTB:
        SET_BIT(GPIOB->ODR,PinNo);
		break;
	case PORTC:
        SET_BIT(GPIOC->ODR,PinNo);
		break;
	}

	}
	else if(Value == GPIO_LOW)
	{
		switch (PortId)
	{
	case PORTA:
         CLR_BIT(GPIOA->ODR,PinNo);
		break;
	case PORTB:
         CLR_BIT(GPIOB->ODR,PinNo);
		break;
	case PORTC:
         CLR_BIT(GPIOC->ODR,PinNo);
		break;
	}

	}
}
void GPIOSetPinValue_Fast(u8 PortId, u8 PinNo, u8 Value)
{

}
void GPIOSetAlternativeFunction(u8 PortId, u8 PinNo, u8 ALFun)
{
	if (PinNo<8)
	{
	switch(PortId)
	{
	case PORTA:
		GPIOA->AFRL &=~(0b1111<<(PinNo*4));
		GPIOA->AFRL |=(ALFun<<(PinNo*4));
		break;
	}
	}
	else if(PinNo>8)
	{
		switch(PortId)
		{
		case PORTA:
			GPIOA->AFRH &=~(0b1111<<((PinNo-8)*4));
			GPIOA->AFRH |=(ALFun<<((PinNo-8)*4));
			break;
		}
	}
}

GPIO_VoidInit(GPIO_Config_t* PinConfig)
{
 GPIO_voidSetPinMode(PinConfig->Port,PinConfig->Pin,PinConfig->Mode);
 GPIOSetPinOutputType(PinConfig->Port,PinConfig->Pin,PinConfig->OutputType);
 GPIOSetPinOutputSpeed(PinConfig->Port,PinConfig->Pin,PinConfig->OutputSpeed);
 GPIOSetPinInputPull(PinConfig->Port,PinConfig->Pin,PinConfig->InputPull);
 GPIOSetAlternativeFunction(PinConfig->Port,PinConfig->Pin,PinConfig->AltFunc);
}

