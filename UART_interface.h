/**************************************************************/
/******************** Layer : MCAL*************************/
/********************Ver :01 *************************/
/********************Component :UART *************************/
/********************Author : Roba *************************/
/******************** *************************/
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_
void UART_voidInit(void);
void UART_voidSend(u8 Copy_u8Data);
u8 UART_u8Receive(void);
void UART_SendString(u8 *str);
void UART_RecieveString(u8 *str);

#endif
