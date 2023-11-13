#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void USART_voidInit(void);

void USART_voidSend( u8 Copy_u8Data );

void USART_voidSendText(char *Copy_u8Data);

u8 USART_u8Receive( void );

u8 USART_u8TransReceive( u8 Copy_u8Data );

void USART_voidReceiveText(char *Copy_u8Data);

// USART Interrupt

void USART_voidRXEnableInterrupt();

void USART_voidRXDisableInterrupt();

u8 USART_u8ReceiveInterrupt(void);

void USART_voidTXEnableInterrupt();

void USART_voidTXDisableInterrupt();

void USART_voidSendInterrupt(u8 Copy_u8Data);

void USART_voidUDREnableInterrupt();

void USART_voidUDRDisableInterrupt();


void USART_voidRXCallBackFunc(void (*PTR)(void));

void USART_voidTXCallBackFunc(void (*PTR)(void));

void USART_voidUDRCallBackFunc(void (*PTR)(void));


#endif
