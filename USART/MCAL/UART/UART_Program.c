#include "../../LIB/STD_Types.h"
#include "../../LIB/Bit_Math.h"


#include "UART_Private.h"
#include "UART_Config.h"
#include "UART_Registers.h"
#include "UART_Interface.h"

void (*Private_voidRXFunc)(void) = NULL;
void (*Private_voidUDRFunc)(void) = NULL;
void (*Private_voidTXFunc)(void) = NULL;

void USART_voidInit(void)
{
	Set_Bit(UCSRC, UCSRC_URSEL); // Using UCSRC

	// ASYNCHRONOUS MODE
#if 	MODE_OF_OPERATION == ASYNCHRONOUS
	Clear_Bit(UCSRC, UCSRC_UMSEL);
	Clear_Bit(UCSRC, UCSRC_UCPOL);

	// Select Speed in Asynchronous MOde
#if 	SPEED_OPERATION == NORMAL_SPEED_MODE
	Clear_Bit(UCSRA, UCSRA_U2X);
#define UBRRL_VAL 	( (F_OC / (16 * BAUD_RATE) ) - 1)
#elif 	SPEED_OPERATION == DOUBLE_SPEED_MODE
	Set_Bit(UCSRA, UCSRA_U2X);
#define UBRRL_VAL 	( ( (f32)F_OC / (8 * (f32)BAUD_RATE) ) - 1)
#else
#endif

	// SYNCHRONOUS MODE
#elif 	MODE_OF_OPERATION == SYNCHRONOUS
	Set_Bit(UCSRC, UCSRC_UMSEL);

#if 	CLOCK_POLARITY == RISING
	Clear_Bit(UCSRC, UCSRC_UCPOL);

#elif 	CLOCK_POLARITY == FALLING
	Set_Bit(UCSRC, UCSRC_UCPOL);
#else
#endif

#define UBRRL_VAL ( (F_OC / (2 * BAUD_RATE) ) - 1)

#else
#endif

	Set_Bit(UCSRC, UCSRC_URSEL);

	// Selecting Frame
#if 	FRAME_SIZE == 8
	Set_Bit(UCSRC, UCSRC_UCSZ0);
	Set_Bit(UCSRC, UCSRC_UCSZ1);
	Clear_Bit(UCSRB, UCSRB_UCSZ2);

#elif 	FRAME_SIZE == 9
	Set_Bit(UCSRC, UCSRC_UCSZ0);
	Set_Bit(UCSRC, UCSRC_UCSZ1);
	Set_Bit(UCSRB, UCSRB_UCSZ2);
#else
#endif


	// Selecting Parity Mode
#if 	PARITY_MODE == DISABLED_PARTITY
	Clear_Bit(UCSRC, UCSRC_UPM0);
	Clear_Bit(UCSRC, UCSRC_UPM1);

#elif 	PARITY_MODE == EVEN_PARITY
	Clear_Bit(UCSRC, UCSRC_UPM0);
	Set_Bit(UCSRC, UCSRC_UPM1);

#elif 	PARITY_MODE == ODD_PARITY
	Set_Bit(UCSRC, UCSRC_UPM0);
	Set_Bit(UCSRC, UCSRC_UPM1);

#else
#endif

	// Select Stop Bit
#if 	STOP_BIT_SELECT == ONE_BIT
	Clear_Bit(UCSRC, UCSRC_USBS);

#elif 	STOP_BIT_SELECT == TWO_BIT
	Set_Bit(UCSRC, UCSRC_USBS);

#else
#endif


	Clear_Bit(UCSRC, UCSRC_URSEL);
	// Calculating UBRRL value
	UCSRC = 0;
	UBRRL = UBRRL_VAL;

	// Enabling TX and RX
	Set_Bit(UCSRB, UCSRB_TXEN);
	Set_Bit(UCSRB, UCSRB_RXEN);

}

void USART_voidSend(u8 Copy_u8Data)
{
	while(Get_Bit(UCSRA, UCSRA_UDRE) == 0 );

	UDR = Copy_u8Data;
}


u8 USART_u8Receive(void)
{
	while( Get_Bit(UCSRA, UCSRA_RXC) == 0 );

	return UDR;
}

u8 USART_u8TransReceive( u8 Copy_u8Data )
{
	// wait until UDRE is zero to send
	while(Get_Bit(UCSRA, UCSRA_UDRE) == 0 );
	UDR = Copy_u8Data;

	// Wait Until Receive flag is zero
	while( Get_Bit(UCSRA, UCSRA_RXC) == 0 );

	return UDR;

}

// Interrupt RX/TX

void USART_voidSendInterrupt(u8 Copy_u8Data)
{
	UDR = Copy_u8Data;
}

u8 USART_u8ReceiveInterrupt(void)
{
	return UDR;
}

// RX/TX
void USART_voidSendText(char *Copy_u8Data)
{
	u8 i = 0;

	while( *(Copy_u8Data + i) != '\0')
	{
		USART_voidSend( *(Copy_u8Data + i) );
		i++;
	}

}

void USART_voidReceiveText(char *Copy_u8Data)
{
	u8 i = 0;
	while( *(Copy_u8Data + i) != '\0' )
	{
		*(Copy_u8Data + i) = USART_u8Receive();
		i++;
	}
}

void USART_voidRXCallBackFunc(void (*PTR)(void))
{
	if(PTR != NULL)
	{
		Private_voidRXFunc = PTR;
	}
}

void USART_voidTXCallBackFunc(void (*PTR)(void))
{
	if( PTR != NULL )
	{
		Private_voidTXFunc = PTR;
	}
}

void USART_voidUDRCallBackFunc(void (*PTR)(void) )
{
	if( PTR != NULL )
	{
		Private_voidUDRFunc = PTR;
	}
}

void USART_voidRXEnableInterrupt()
{
	Set_Bit(UCSRB,UCSRB_RXCIE);
}

void USART_voidRXDisableInterrupt()
{
	Clear_Bit(UCSRB,UCSRB_RXCIE);
}

void USART_voidTXEnableInterrupt()
{
	Set_Bit(UCSRB,UCSRB_TXCIE);
}

void USART_voidTXDisableInterrupt()
{
	Clear_Bit(UCSRB,UCSRB_TXCIE);
}


void USART_voidUDREnableInterrupt()
{
	Set_Bit(UCSRB,UCSRB_UDRIE);
}

void USART_voidUDRDisableInterrupt()
{
	Clear_Bit(UCSRB,UCSRB_UDRIE);
}


void __vector_13(void)__attribute__((signal,used, externally_visible));
void __vector_13(void)
{
	if( Private_voidRXFunc != NULL )
	{
		Private_voidRXFunc();
	}
}

void __vector_14(void)__attribute__((signal,used, externally_visible));
void __vector_14(void)
{
	if( Private_voidUDRFunc != NULL )
	{
		Private_voidUDRFunc();
	}
}

void __vector_15(void) __attribute__((signal,used, externally_visible));
void __vector_15(void)
{
	if( Private_voidTXFunc != NULL )
	{
		Private_voidTXFunc();
	}
}

