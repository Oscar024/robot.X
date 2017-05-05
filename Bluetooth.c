
#include"Bluetooth.h"
#include"UART1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Funciones_Db.h"
#include "lcd.h"
extern char          SBUSART;
unsigned char         comando[20];
extern unsigned char  cad;
extern unsigned char  BluetoothDato[20];
extern unsigned char  dato[8];
extern unsigned char  TramaTablet[20];

void BT_Init(){


    UART1_Init(51); //9600 frecuencia de 8MHZ
//      UART1_Init(6); //38400 frecuencia de 4MHZ

//
//    SendBlueToothCommand("\r\n+STBD=38400\r\n",15);
//    Close1USART();

//     UART1_Init(51);
//
//    SendBlueToothCommand("\r\n+STBD=19200\r\n",15);
//    Close1USART();

//    UART1_Init(51);
//
//    SendBlueToothCommand("\r\n+STBD=19200\r\n",15);
//    Close1USART();

//       UART1_Init(51);
       Pause_seg(1);
//       char nameBT[18]={"\r\n+STNA=DriveBy\r\n\0"};                                //Pausa de 1 seg. necesaria
           char nameBT[18]={"AT+NAME=robot\r\n\0"};                                //Pausa de 1 seg. necesaria
//       
//       while (BusyUSART());
//       putcUSART(0x33);
//       Lcd_Clear();
//      Lcd_Set_Cursor(1,1);
//      Lcd_Write_String("Escrito");
//       while(1);
       
//       SendBlueToothCommand("\r\n+STWMOD=0\r\n",13);                               //Esa onda como esclavo
//
//       Pause_seg(4);
//
//
//       SendBlueToothCommand((const char*)nameBT,sizeof(nameBT));                  //El nombre
//       Pause_seg(1);
//
//       SendBlueToothCommand("\r\n+STOAUT=1\r\n",13);                               //ENCENDIDO permite que se le conecte un dispositivo emparejado
//       Pause_seg(4);
//
//
//
//       SendBlueToothCommand("\r\n+STPIN=0000\r\n",15);                             //Establece un codigo de PIN                                                                //Espera 2 seg.
//       Pause_seg(4);
//
//       SendBlueToothCommand("\r\n+INQ=1\r\n",10);                                  //Lo pone visible
//       Pause_seg(4);
//       SendBlueToothCommand("\r\n+INQ=1\r\n",10);                                  //Lo pone visible
//       Pause_seg(4);

        SendBlueToothCommand("AT+ROLE=0\r\n",11);                               //Esa onda como esclavo

       Pause_seg(1);


       SendBlueToothCommand((const char*)nameBT,sizeof(nameBT));                  //El nombre
       Pause_seg(2);

       SendBlueToothCommand("AT+PSWD=0000\r\n",14);                               //Password
       Pause_seg(2);



       SendBlueToothCommand("AT+INQ\r\n",8);                                    //MODO VISIBLE                                                                //Espera 2 seg.
       Pause_seg(2);

       SendBlueToothCommand("AT+INQ\r\n",8);                                    //Modo visible                                                               //Espera 2 seg.
       Pause_seg(2);
       return;
}





void SendBlueToothCommand(const char *command,unsigned int total){
       putSTRINGU1(command,total);
       return;
}

void CheckTX(const char *CheckC){

       strcpy(comando,CheckC);
       clrBufferUSART();
       SBUSART=0;
       while(SBUSART==0){
             if(strcmp(comando,BluetoothDato)==0){
                   SBUSART=1;
                   cad=0;                         }
             else if(strcmp(comando,BluetoothDato)!=0)
                   SBUSART=0;
                        }
        return;
}

void clrBufferUSART(void){
       int i;
       for(i=0;i<20;i++){
             BluetoothDato[i]=0;
             cad=0;     }
       return;

}
void putcBluetoothString(int NumBytes) {
        //Manda los datos a la Tablet con el tamaño de la trama
       int i;
       for(i=0;i<NumBytes;i++){  //Trama a enviar
             putcUSART(dato[i]);
             while (BusyUSART()); }
       return;
}
