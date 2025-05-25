#ifndef   GPIO_INTERFACE_H
#define   GPIO_INTERFACE_H

#include     "STD_TYPES.h"

#define     GPIO_MODE_INPUT     0b00
#define     GPIO_MODE_OUTPUT    0b01
#define     GPIO_MODE_ALTFUN    0b10
#define     GPIO_MODE_ANALOG    0b11

#define GPIO_AF_5           0b0101


#define     GPIO_SPEED_LOW        0b00
#define     GPIO_SPEED_MEDIUM     0b01
#define     GPIO_SPEED_HIGH       0b10
#define     GPIO_SPEED_VERY_HIGH  0b11

#define     GPIO_INPUT_PULL_UP       0b01
#define     GPIO_INPUT_PULL_DOWN     0b10
#define     GPIO_INPUT_NO_PULL       0b00

#define     GPIO_OUTYPE_PUSHPULL        0
#define     GPIO_OUTYPE_OPENDRAIN       1


#define		PORTA		0
#define		PORTB		1
#define		PORTC		2



#define		GPIO_HIGH	     1
#define		GPIO_LOW		0


#define     GPIOAEN_PER		0
#define     GPIOBEN_PER		1
#define     GPIOCEN_PER		2

#define      PIN0     0
#define      PIN1     1
#define      PIN2     2
#define      PIN3     3
#define      PIN4     4
#define      PIN5     5
#define      PIN6     6
#define      PIN7     7
#define      PIN8     8
#define      PIN9     9
#define      PIN10     10
#define      PIN11     11
#define      PIN12     12
#define      PIN13    13
#define      PIN14    14
#define      PIN15    15

typedef struct
{
	u8 Port;
	u8 Pin;
    u8 Mode;
    u8 OutputType;
    u8 OutputSpeed;
    u8 InputPull;
    u8 AltFunc;

}GPIO_Config_t;

GPIO_VoidInit(GPIO_Config_t* PinConfig);

void GPIO_voidSetPinMode(u8 PortId, u8 PinNo, u8 Mode);
void GPIOSetPinOutputType(u8 PortId, u8 PinNo, u8 OutType);
void GPIOSetPinOutputSpeed(u8 PortId, u8 PinNo, u8 OutSpeed );
void GPIOSetPinInputPull(u8 PortId, u8 PinNo, u8 Pull);
u8   GPIOGetPinValue(u8 PortId, u8 PinNo);
void GPIOSetPinValue(u8 PortId, u8 PinNo, u8 Value);
void GPIOSetPinValue_Fast(u8 PortId, u8 PinNo, u8 Value);
void GPIOSetAlternativeFunction(u8 PortId, u8 PinNo, u8 ALFun);

#endif
