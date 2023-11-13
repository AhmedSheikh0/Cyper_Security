#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_


#define F_OC	16000000UL

/****************************************************************/
/*  UMSEL = 1 synchronous 										*/
/*  UMSEL = 0 Asynchronous										*/
/****************************************************************/
/** !comment : Please Enter the Operation Mode					*/
/** 		   MODE_OF_OPERATION can be : 						*/
/*					    					ASYNCHRONOUS 		*/
/*						    				SYNCHRONOUS 		*/
/****************************************************************/

#define MODE_OF_OPERATION	ASYNCHRONOUS


/****************************************************************/
/** !comment : For using  Speed Operation the Mode of Operation	*/
/**							MUST be ASYNCHRONOUS				*/
/****************************************************************/
/*	U2X = 0 normal speed										*/
/*	U2X = 1 double speed										*/
/****************************************************************/
/** !comment : Please Enter the Speed Operation					*/
/** 		   Speed Operation can be : 						*/
/*					    				NORMAL_SPEED_MODE 		*/
/*						    			DOUBLE_SPEED_MODE		*/
/****************************************************************/

#define SPEED_OPERATION		DOUBLE_SPEED_MODE

/****************************************************************/
/** !comment : Please Enter the Frame Size						*/
/** 		   FRAME_SIZE can be : 								*/
/*					    			5 Bits				 		*/
/*						    		6 Bits						*/
/*									7 Bits						*/
/*									8 Bits						*/
/*									9 Bits						*/
/****************************************************************/

#define FRAME_SIZE			8


/****************************************************************/
/** !comment : Please Enter the Baud Rate						*/
/****************************************************************/

#define BAUD_RATE			9600UL

/****************************************************************/
/** !comment : Please Enter the Parity Mode						*/
/** 		   PARITY_MODE can be : 							*/
/*					    			DISABLED_PARTITY 			*/
/*						    		EVEN_PARITY 				*/
/*							    	ODD_PARITY					*/
/****************************************************************/

#define PARITY_MODE			DISABLED_PARTITY

/****************************************************************/
/** !comment : Please Enter the Number of Stop Bits				*/
/** 		   STOP_BIT_SELECT can be : 						*/
/*					    				ONE_BIT 				*/
/*						    			TWO_BIT					*/
/****************************************************************/

#define STOP_BIT_SELECT		TWO_BIT

/****************************************************************/
/** !comment : For using  Clock Polarity the Mode of Operation	*/
/**							MUST be SYNCHRONOUS					*/
/****************************************************************/
/*	UCPOL = 0 Rising Edge (Transmitted) Falling Edge (Received)	*/
/*	UCPOL = 1 Falling Edge (Transmitted) Rising Edge (Received) */
/****************************************************************/
/** !comment : Please Enter the Clock Polarity					*/
/** 		   CLOCK_POLARITY can be : 							*/
/*					    				RISING			 		*/
/*						    			FALLING					*/
/****************************************************************/

#define CLOCK_POLARITY		RISING


#endif
