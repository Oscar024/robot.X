/*******************************************************************************
 * Archivo: Robot.c
 * Autores: Ing. Oscar Rigoberto Carvajal Ortiz
 * Fecha: 4 de Mayo de 2017, 05:59 PM
 * Versión: 1.0
 * IDE: MPLAB XC8
 * Empresa: 
 * MCU: PIC18F4550

 ******************************************************************************/


#include <xc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include"CC1101_v2.h"
#include"Funciones_Db.h"
//#include"GLK12232-25.h"
//#include<plib/spi.h>
#include<plib/usart.h>
#include"Bluetooth.h"
#include "lcd.h"


//#pragma config PLLDIV = 2
//#pragma config CPUDIV = OSC3_PLL4
//#pragma config USBDIV = 1
//#pragma config FOSC = HS
//#pragma config FCMEN = OFF
//#pragma config IESO = OFF
//#pragma config PWRT = OFF
//#pragma config BOR = OFF
//#pragma config BORV = 2
//#pragma config VREGEN = OFF
//#pragma config WDT = OFF
//#pragma config WDTPS = 32768
//#pragma config CCP2MX = ON
//#pragma config PBADEN = OFF
//#pragma config LPT1OSC = OFF
//#pragma config MCLRE = ON
//#pragma config STVREN = OFF
//#pragma config LVP = OFF
//#pragma config ICPRT = OFF
//#pragma config XINST = OFF
//#pragma config CP0 = OFF
//#pragma config CP1 = OFF
//#pragma config CP2 = OFF
//#pragma config CP3 = OFF
//#pragma config CPB = OFF
//#pragma config CPD = OFF
//#pragma config WRT0 = OFF
//#pragma config WRT1 = OFF
//#pragma config WRT2 = OFF
//#pragma config WRT3 = OFF
//#pragma config WRTC = OFF
//#pragma config WRTB = OFF
//#pragma config WRTD = OFF
//#pragma config EBTR0 = OFF
//#pragma config EBTR1 = OFF
//#pragma config EBTR2 = OFF
//#pragma config EBTR3 = OFF
//#pragma config EBTRB = OFF

#pragma config VREGEN = OFF         // Voltage regulator USB , is Suspended
#pragma config WDT = OFF                // Watchdog timer is suspended
#pragma config PLLDIV = 1                // Internal Oscillator engaged
#pragma config MCLRE = ON
#pragma config WDTPS = 32768
#pragma config CCP2MX = ON
#pragma config PBADEN = OFF
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 2
#pragma config FOSC = INTOSCIO_EC
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config BORV = 3
#pragma config LPT1OSC = OFF
#pragma config STVREN = ON
#pragma config LVP = OFF
#pragma config ICPRT = OFF
#pragma config XINST = OFF
#pragma config DEBUG = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF
#pragma config WRTC = OFF
#pragma config WRTB = OFF
#pragma config WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF
#pragma config EBTRB = OFF

//CONFIG1L=0X00;
//CONFIG1H=0X00;
//CONFIG2L=0X19;
//CONFIG2H=0X1E;
//CONFIG3H=0X80; //0X00;
//CONFIG4L=0X80;
//CONFIG5L=0X0F;
//CONFIG5H=0XC0;
//CONFIG6L=0X0F;
//CONFIG6H=0XE0;
//CONFIG7L=0X0F;
//CONFIG7H=0X40;

//Variables Globales
char CheckSum;
char cleanBfer;
char ComanBFlag = 0;
char Comando;
char ComandoTablet;
char ComanTFlag = 0;
char EntTrama = 0;
extern char FinComandB;
extern char FinComandT;
char InicioComando;
char lenght;
char RXComandoTB = 0;
char SBUSART;
char Timer1 = 0;
unsigned char BluetoothDato[50];
//unsigned char contador2 = 0;
unsigned char cad = 0; // Valor para la cadena de incremento en recepcion
extern  unsigned  char contador;
extern  unsigned char contador2;
extern unsigned char comando[40];
extern unsigned char TramaTablet[20];


//Función (ISR) (interrupciones)
void interrupt TMRO_USART(void) { 


    
    //Interrupción USART
    if (PIR1bits.RCIF) {
//        Led_Verde = ~Led_Verde;
//         Lcd_Clear();
//         Lcd_Set_Cursor(1,1);
//         Lcd_Write_String("ISR");

        BluetoothDato[cad] = getcUSART();
        if (BluetoothDato[cad] == '#') {
            if (ComanTFlag == 0) {
                EntTrama = 1; //Bandera para indicar que los datos siguientes son parte de una trama Tablet o Bluetooth
                FinComandT = 0; //Bandera en 1 para indicar en bucle que se ha finalizado la entrada de comando de tablet
                ComanTFlag = 1; //Bandera indicando el inicio de trama
                cad++;
            }//Incremento de cadena
            else if (ComanTFlag == 1) {
                ComanTFlag = 0; //Bandera indicando el fin de la trama
                FinComandT = 1; //Bandera para indicar que los
                EntTrama = 0;
            }
        }
//        else if (BluetoothDato[cad] == '\n' && ComanBFlag == 0) {
//            EntTrama = 1; //Bandera para indicar que los datos siguientes son parte de una trama Tablet o Bluetooth
//            FinComandB = 0; //Limpiar bandera de finalizado de comando bluetooth
//            cad++;
//            ComanBFlag = 1;
//        }
//        else if (BluetoothDato[cad] == '\n' && ComanBFlag == 1) {
//            FinComandB = 1; //Bandera en 1 para indicar en bucle que se ha finalizado la entrada de comando de bluetooth
//            ComanBFlag = 0;
//            EntTrama = 0;
//        }
        else if (EntTrama == 1)
            cad++;

    }
    PIR1bits.RCIF=0;
}
/*
//Función Princpal
void main(void) {
    TRISB=0;
    Led_Rojo=1;
    for(int i=0;i<20;i++)
        __delay_ms(20);
    Inicializa_Driveby();
//    Led_Verde=1;
//    Led_Azul=0;
    
    while (1) {

        
//        Teclado();
        if (cleanBfer == 1) {
            clrBufferUSART();
            cleanBfer = 0;
        }
        if (FinComandT == 1) {
 
            FinComandT = 0;
            CloseUSART();
            Comando_Tablet();
    
        }
        else if (FinComandB == 1) {
           
            FinComandB = 0;
            CloseUSART();
            DelayCommands();
            BT_ModoVisible();
//            EstadoBluetooth();
        }

    }

    return;

}

*/


int main()
{
  
  TRISD = 0x00;
  TRISE = 0x00;
  RW1=0;
  ADCON1bits.PCFG=0b1111;
  Lcd_Init();
  Lcd_Clear();
  Lcd_Set_Cursor(1,1);
  Lcd_Write_String("Inicio");
  Inicializa_Driveby();
  while(1)
  {
      //        Teclado();
        if (cleanBfer == 1) {
            clrBufferUSART();
            cleanBfer = 0;
        }
        if (FinComandT == 1) {
//            Lcd_Clear();
//            Lcd_Set_Cursor(1,1);
//            Lcd_Write_String("CMD TABLET");
            FinComandT = 0;
            CloseUSART();
            Comando_Tablet();
            UART1_Init(51);

        }
        else if (FinComandB == 1) {

//             Lcd_Clear();
//            Lcd_Set_Cursor(1,1);
//            Lcd_Write_String("CMD BT");
            FinComandB = 0;
            CloseUSART();
//            DelayCommands();
            BT_ModoVisible();
//            EstadoBluetooth();
        }
    
  }
  return 0;
}
