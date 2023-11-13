/*
 * main.c
 *
 *  Created on: Nov 11, 2023
 *      Author: AHMED
 */

#include <string.h>
#include <stdlib.h>

#include "LIB/STD_TYPES.h"
#include "LIB/Bit_Math.h"

#include "HAL/LCD2/LCD_Interface.h"

#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/Port/Port_Interface.h"
#include "MCAL/GIE/GIE_Interface.h"
#include "MCAL/UART/UART_Interface.h"

#define MAX_CMD_SIZE 	20


volatile u8 RX_Index = 0;

u8 Globale_u8Data[MAX_CMD_SIZE];

u8 Key[] = "01010101";

u8 Accessed[]  =  "6701";
u8 NS_Routine[] = "7F2735";
u8 NS_Req[] = "7F3135";

u8 Cipher[9];

u8 tempStr[20];

u8 Done_Flag = 0;

u8 Security_Flag = 0;

u8 Error_Flag;


void RX_Complete();

u8 Random(u8 Copy_u8R1, u8 Copy_u8R2){
	u8 num = (rand() %  (Copy_u8R2 - Copy_u8R1 + 1)) + Copy_u8R1;
	return num;
}


u8* IntToString(s32 Copyu8Int, u8 *str)
{

	u32 flag = 0;
	u32 i = 20 - 1;
	str[i--] = '\0';

	if (Copyu8Int < 0)
	{
		flag = 1;
		Copyu8Int = -Copyu8Int;
	}
	while (Copyu8Int != 0)
	{
		str[i--] = (Copyu8Int % 10) + '0';
		Copyu8Int /= 10;
	}

	if (flag)
	{
		str[i--] = '-';
	}

	i++;

	return str + i;

}


int main()
{
	PORT_voidInit();

	LCD_voidInit();

	GIE_voidEnable();

	USART_voidRXCallBackFunc(RX_Complete);

	USART_voidInit();

	USART_voidRXEnableInterrupt();


	while(1)
	{
		u32 RandNum = Random(1,250) * Random(1,250) + 84267531;

		if(Done_Flag == 1)
		{
			Done_Flag = 0;

			if(memcmp(Globale_u8Data, "2701", 4) == 0 )
			{
				strcat(Accessed, IntToString(RandNum, tempStr));
				LCD_voidWriteString(Accessed);

				for(u8 i = 4; i < 12; i++)
				{
					Cipher[i-4]= ((Accessed[i] - '0') ^ (Key[i-4] - '0')) + '0';
				}

				Cipher[8]='\0';

				LCD_voidGoToPosition(2,0);

				LCD_voidWriteString(Cipher);
			}
			else if(memcmp(Globale_u8Data, "3101AA00", 8) == 0 )
			{
				if(Security_Flag == 1)
				{
					LCD_voidWriteString((u8*)"7101AA00");
					DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_0, DIO_u8PIN_HIGH);
				}
				else
				{
					LCD_voidWriteString(NS_Req);
				}
			}
			else if(memcmp(Globale_u8Data, "2702", 4) == 0 )
			{
				for(u8 i = 4; i < 12 ; i++)
				{
					if( Cipher[i-4] != Globale_u8Data[i])
					{
						Error_Flag = 1;
						break;
					}
				}
				if(Error_Flag == 0)
				{
					LCD_voidWriteString((u8*)"6702");
					Security_Flag=1;
				}
				else
				{
					LCD_voidWriteString(NS_Routine);
				}
			}

			RX_Index = 0;
			USART_voidRXEnableInterrupt();
		}

	}
	return 0;
}


void RX_Complete()
{
	u8 temp = 0;
	temp = USART_u8ReceiveInterrupt();

	if(  temp == '\r' )
	{
		Globale_u8Data[RX_Index] = '\0';
		Done_Flag = 1;
		USART_voidRXDisableInterrupt();
		LCD_voidSendCommand(LCD_ClearDisplay);
	}
	else if( temp == 0x08)
	{
		Globale_u8Data[--RX_Index]= '\0';
	}
	else
	{
		Globale_u8Data[RX_Index] = temp ;
		RX_Index++;
	}
}
