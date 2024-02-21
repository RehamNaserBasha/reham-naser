#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"



void UART_voidInit(void)
{

	//ON SIZE 8BIT
	//ONE STOP BIT
	//NO INTERRUPT
	//NO PARTIY
	UCSRC=0b10000110;
	//BAUD RATE 9600
	UBRRL=51;
	//ENABLE TX AND RX
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
}
void UART_voidSend(u8 Copy_u8Data)
{
	while (((GET_BIT(UCSRA , UCSRA_UDRE)) == 0));
	UDR= Copy_u8Data;
}
u8 UART_u8Receive(void)
{
	while (((GET_BIT(UCSRA , UCSRA_RXC)) == 0));
	return UDR;
}
void UART_SendString(u8 *str)
{
	u8 i=0;
	while(str[i]!='\0')
	{
		UART_voidSend(str[i]);
		i++;
	}

}
void UART_RecieveString(u8 *str)
{
	u8 i=0;
	u8 myvalue;

	do
	{
		myvalue =UART_u8Receive();
		if(myvalue !='\n')
		{
			str[i]=myvalue;
			UART_voidSend(str[i]);
			i++;
		}
		else
		{
			str[i]='\0';
			break;
		}

	}while (((GET_BIT(UCSRA , UCSRA_RXC)) == 0));
	printString(str);
}
void printString(const u8 *mystring)
{
	while(*mystring)
	{
		UART_voidSend(*mystring++);
	}
}
