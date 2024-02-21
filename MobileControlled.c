/*
 * main.c
 *
 *  Created on: Feb 1, 2024
 *      Author: HP
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_private.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "UART_interface.h"
#include "UART_config.h"
#include "UART_private.h"
#include "SSD_interface.h"
#include "SSD_config.h"
#include "SSD_private.h"
#include <util/delay.h>
#include <string.h>



 u8 recievedData[20];// to store Recieved Name
 u8 recievedChar;
 u8 recievedPass[20];//to store Recieved Passward
 u8 recievedNum;


typedef struct{
	char name[10];
	u8 passward[10];
}checks;

checks data[10]={
			{
				"ROBA",
				"1410"
			},
			{
				"REHAM",
				"2412"
			},
			{
				"HABIBA",
				"0106"
			},
			{
				"RAFEEF",
				"410"
			},
			{
				"AHMED",
				"1710"
			},
			{
				"FATMA",
				"2510"
			},
			{
				"RANA",
				"0907"
			},
			{
				"HANAN",
				"1211"
			},
			{
				"AMER",
				"2411"
			},
			{
				"DINA",
				"2111"
			}
	};


u8 check(char *name, char *password);//to check name and passward

int main()
{
	//data CLCD
	DIO_voidSetPortDir(PORTA_REG,PORT_DIR_OUT);
	//7 Segment
	DIO_voidSetPortDir(PORTB_REG,PORT_DIR_OUT);
	//control CLCD
	DIO_voidSetPortDir(PORTC_REG,PORT_DIR_OUT);
	//MOTOR & LED
	DIO_voidSetPortDir(PORTD_REG,0b11111110);

	SSD_t seven={PORTB_REG,PORTB_REG,PIN7,COMMON_CATHODE};


	UART_voidInit();
    CLCD_voidInit();

    CLCD_voidSendString("Hello To....");
    UART_SendString("Hello To....");
    UART_SendString("\r\n");
    _delay_ms(1000);
    CLCD_voidSendCommand(0b00000001);
    _delay_ms(50);
    CLCD_voidSendString("Mobile Controlled");
    UART_SendString("Mobile Controlled Home");
    UART_SendString("\r\n");
    UART_SendString("\r\n");
    CLCD_voidSendPos(1,5);
    CLCD_voidSendString("Home");
    _delay_ms(2000);
    CLCD_voidSendCommand(0b00000001);
    _delay_ms(50);
  u8 Counter=0;
	while(1)
	{
		u8 i=0;
		u8 w=0;
         //Recieve Name and store it on array
		UART_SendString("ENTER YOUR NAME:");
		_delay_ms(100);
		UART_SendString("\r\n");
		 CLCD_voidSendString("ENTER NAME:");


         while((recievedChar=UART_u8Receive())!='.')
             {
            	 recievedData[i]=recievedChar;
            	 i++;
             }
         recievedData[i]='\0';
       //  UART_SendString(recievedData);
         UART_SendString("\r\n");
       //  _delay_ms(1000);
         CLCD_voidSendString(recievedData);




         CLCD_voidSendPos(1,0);


         //Recieve Passward and store it on array
         CLCD_voidSendString("ENTER PASS:");
         UART_SendString("ENTER YOUR PASSWORD:");
         UART_SendString("\r\n");

         u8 l=0;
         while((recievedNum=UART_u8Receive())!='.')
             {
            	 recievedPass[l]=recievedNum;
            	 l++;
             }
          recievedPass[l]='\0';
          UART_SendString("\r\n");
          CLCD_voidSendString(recievedPass);

          _delay_ms(1000);


          CLCD_voidSendCommand(0b00000001);
          _delay_ms(50);



          //check Name andPassward Recieved
          if(check(recievedData,recievedPass))
               {
        	  CLCD_voidSendString("CORRECT DATA");
        	  _delay_ms(100);
        	  UART_SendString("CORRECT DATA");
        	  UART_SendString("\r\n");
        	  UART_SendString(" OPTIONS FOR YOUR HOME: ");
        	  UART_SendString("\r\n");
            	    CLCD_voidSendString("Welcome to Mobile");
            	    CLCD_voidSendPos(1,1);
            	    CLCD_voidSendString("Controlled Home");
            	    _delay_ms(2000);
            	    CLCD_voidSendCommand(0b00000001);
            	    _delay_ms(50);
            	    UART_SendString("1-ROOM1 ");
            	   	    UART_SendString("\r\n");
                    	 UART_SendString("2-ROOM2  ");
                     	 UART_SendString("\r\n");
                   	    UART_SendString("3-OPEN DOOR  ");
                   	    UART_SendString("\r\n");
                   	    UART_SendString("4-CLOSE DOOR ");
                    	 UART_SendString("\r\n");
                         UART_SendString("5-CLOSE ROOM ");
                         UART_SendString("\r\n");
                  	   UART_SendString("6-LOGGING OUT  ");
                   	  UART_SendString("\r\n");
            	    CLCD_voidSendString("ROOM1  PRESS 1");

            	    CLCD_voidSendPos(1,0);
            	    CLCD_voidSendString("ROOM2  PRESS 2");
            	    _delay_ms(1000);

            	    CLCD_voidSendCommand(0b00000001);
            	    CLCD_voidSendString("  OPEN DOOR ");
            	    CLCD_voidSendPos(1,0);
            	    CLCD_voidSendString("     PRESS 3");
            	    _delay_ms(1000);

            	    CLCD_voidSendCommand(0b00000001);
            	    CLCD_voidSendString("  CLOSE DOOR ");
            	    CLCD_voidSendPos(1,0);
            	    CLCD_voidSendString("     PRESS 4");
            	    _delay_ms(1000);

               	    CLCD_voidSendCommand(0b00000001);
                 	 CLCD_voidSendString("  CLOSE ROOM ");
           	      CLCD_voidSendPos(1,0);
                   CLCD_voidSendString("      PRESS 5");
                _delay_ms(2000);

               CLCD_voidSendCommand(0b00000001);
               CLCD_voidSendString("   LOGGING OUT");
          	    CLCD_voidSendPos(1,0);
             CLCD_voidSendString("       PRESS 6");
             	    _delay_ms(1000);

          	    CLCD_voidSendCommand(0b00000001);
            	    _delay_ms(50);

            	    while(UART_u8Receive()!='6')
            	    {
            	    	u8 test=UART_u8Receive();
            	    	switch(test)
            	    	{
            	    	case '1' :
            	    		UART_SendString("\r\n");
            	    		DIO_voidSetPinVal(PORTD_REG,PIN7,1);
            	    	CLCD_voidSendCommand(0b00000001);
            	    	_delay_ms(50);
            	    	UART_SendString("ROOM1 OPENED SUCESSFULLY");
            	    	_delay_ms(50);
            	    	CLCD_voidSendString("ROOM1 OPENED");
            	    	CLCD_voidSendPos(1,2);
            	    	CLCD_voidSendString(" SUCESSFULLY");


            	    	break;
            	   	case '2' :
            	   		UART_SendString("\r\n");
            	   	DIO_voidSetPinVal(PORTD_REG,PIN5,1);
            	   	CLCD_voidSendCommand(0b00000001);
            	   	_delay_ms(50);
            	 	UART_SendString("ROOM2 OPENED SUCESSFULLY");
            	  	_delay_ms(50);
            	   	CLCD_voidSendString("ROOM2 OPENED");
            	   	CLCD_voidSendPos(1,2);
            	   	CLCD_voidSendString(" SUCESSFULLY");

            	   	break;
            	 case '3' :
            		 UART_SendString("\r\n");
            	  DIO_voidSetPinVal(PORTC_REG,PIN5,0);
            	  DIO_voidSetPinVal(PORTC_REG,PIN6,0);
            	  DIO_voidSetPinVal(PORTC_REG,PIN3,1);
            	  DIO_voidSetPinVal(PORTC_REG,PIN4,1);
            	  _delay_ms(50);
            	  CLCD_voidSendCommand(0b00000001);
            	  _delay_ms(50);
            	  UART_SendString("DOOR OPENED SUCESSFULLY");
            	  _delay_ms(50);
            	  CLCD_voidSendString("DOOR OPENED");
            	  CLCD_voidSendPos(1,2);
            	  CLCD_voidSendString("SUCESSFULLY");

            	  DIO_voidSetPinVal(PORTC_REG,PIN5,0);
            	  DIO_voidSetPinVal(PORTC_REG,PIN6,0);
            	  DIO_voidSetPinVal(PORTC_REG,PIN3,0);
            	  DIO_voidSetPinVal(PORTC_REG,PIN4,0);
            	  break;
            	case '4' :
            		UART_SendString("\r\n");
            		    DIO_voidSetPinVal(PORTC_REG,PIN3,0);
            	    	DIO_voidSetPinVal(PORTC_REG,PIN4,0);
            	    	DIO_voidSetPinVal(PORTC_REG,PIN5,1);
            	    	DIO_voidSetPinVal(PORTC_REG,PIN6,1);
            	    	_delay_ms(50);
            	    	CLCD_voidSendCommand(0b00000001);
            	    	_delay_ms(50);
            	   	  UART_SendString("DOOR CLOSED SUCESSFULLY");
            	   	_delay_ms(50);
            	    	CLCD_voidSendString("DOOR CLOSED");
            	    	CLCD_voidSendPos(1,2);
            	    	CLCD_voidSendString("SUCESSFULLY");

            	    	DIO_voidSetPinVal(PORTC_REG,PIN3,0);
            	    	DIO_voidSetPinVal(PORTC_REG,PIN4,0);
            	    	DIO_voidSetPinVal(PORTC_REG,PIN5,0);
            	    	DIO_voidSetPinVal(PORTC_REG,PIN6,0);
            	    	break;
            	    	case '5' :
            	    		UART_SendString("\r\n");
            	    		 DIO_voidSetPinVal(PORTD_REG,PIN7,0);
            	         	DIO_voidSetPinVal(PORTD_REG,PIN5,0);
            	        	CLCD_voidSendCommand(0b00000001);
            	        	_delay_ms(50);
            	        	UART_SendString("ROOM CLOSED SUCESSFULLY");
            	        	_delay_ms(50);
            	    	    CLCD_voidSendString("ROOM CLOSED");
            	    	   CLCD_voidSendPos(1,2);
            	        	CLCD_voidSendString("SUCESSFULLY");

            	         	break;
            	    	}



            	    }
            	    CLCD_voidSendCommand(0b00000001);
            	     _delay_ms(50);
            	    CLCD_voidSendString("  LOGGING OUT");
            	    _delay_ms(1000);
            	    UART_SendString("\r\n");
            	    UART_SendString("LOGGING OUT");
            	    UART_SendString("\r\n");
            	    CLCD_voidSendCommand(0b00000001);
            	    _delay_ms(50);



               }
          else
               {
        	       CLCD_voidSendPos(0,5);
        	       CLCD_voidSendString("Wrong");
        	       _delay_ms(1000);
        	       UART_SendString("Wrong Data");
        	       UART_SendString("\r\n");
        	       UART_SendString("Try Again");
        	       UART_SendString("\r\n");
        	       CLCD_voidSendCommand(0b00000001);
        	       _delay_ms(50);
        	      if(Counter==0)
        	      {
        	    	  CLCD_voidSendString("TWO MORE TRIES");
        	    	 _delay_ms(2000);
        	    	 UART_SendString("TWO MORE TRIES Remaining");
        	    	 UART_SendString("\r\n");

        	    	  Counter++;
        	    	  CLCD_voidSendCommand(0b00000001);
        	    	  _delay_ms(50);
        	      }
        	      else if(Counter==1)
        	      {
        	    	  CLCD_voidSendString("ONE MORE TRIE");
        	    	  _delay_ms(2000);
        	    	  UART_SendString("ONE MORE TRIE");
        	    	  UART_SendString("\r\n");
        	    	 Counter++;
        	    	 CLCD_voidSendCommand(0b00000001);
        	    	 _delay_ms(50);
        	      }
        	      else if(Counter==2)
        	      {
        	    	  CLCD_voidSendString("NO TRIES MORE");
        	    	  //BUZZER
        	    	  UART_SendString("NO TRIES MORE");
        	    	  UART_SendString("\r\n");
        	    	 // DIO_voidSetPinVal(PORTD_REG,PIN4,1);


        	    	  CLCD_voidSendCommand(0b00000001);
        	    	  _delay_ms(50);
        	    	  CLCD_voidSendString("Wait 10 Second ");

        	    	  _delay_ms(1000);
        	    	  UART_SendString("Wait 10 Second ");
        	    	  UART_SendString("\r\n");
        	    	  CLCD_voidSendCommand(0b00000001);
        	    	  u8 data=9;
        	    	  u8 flag=0;
        	    	  SSD_voidEnable(seven);
        	    	  while(flag!=1)
        	    	  {
                DIO_voidSetPinVal(PORTC_REG,PIN7,PIN_VAL_HIGH);
               _delay_ms(50);

        	    		  if(data==0)
        	    		  {
        	    			  flag=1;
        	    		  }


        	    		   CLCD_voidSendString("Loading.....");

        	    		   //CLCD_voidSendPos(0,14);
        	    		   if(data!=0)
        	    		   {
        	    		   CLCD_voidSendNum(data);

        	    		   SSD_voidSendNum(seven,data);
        	    		   }
        	    		   else
        	    		   {
                            CLCD_voidSendNum(0);
                            SSD_voidSendNum(seven,data);
                            _delay_ms(1000);


        	    		   }

        	    		   _delay_ms(1000);
        	    		   CLCD_voidSendCommand(0b00000001);
        	    		   _delay_ms(50);

        	    		   data--;

        	    	  }

        	    	 //SSD_voidDisable(seven);
        	    	 //_delay_ms(1000);
        	    	   DIO_voidSetPinVal(PORTC_REG,PIN7,PIN_VAL_LOW);
        	    	  DIO_voidSetPinVal(PORTD_REG,PIN4,0);
        	    	  CLCD_voidSendCommand(0b00000001);
        	    	  _delay_ms(50);
        	    	  Counter=0;

        	      }


               }


           //Delete buffer
          for(int j=0; j<20; j++)
          {
                    recievedData[j] = 0;
                    recievedPass[j]=0;
          }
             w=0;
          _delay_ms(2000);
          CLCD_voidSendCommand(0b00000001);
          _delay_ms(50);

	}
	return 0;
}


u8 check(char *name, char *password)
{
  for (u8 i = 0; i < 10; i++)
   {
   if (strcmp(data[i].name, recievedData) == 0 && strcmp(data[i].passward, recievedPass) == 0)
         {
            return 1;
         }
   }
    return 0;
}
