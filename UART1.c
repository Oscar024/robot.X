#include"UART1.h"
#include <plib/usart.h>
// <editor-fold defaultstate="collapsed" desc="UART1">

void UART1_Init(char bdr)
{
 
    OpenUSART(USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH,bdr);

}

void putcTxU1(char character)
{
    putcUSART(character);
    while (BusyUSART());
}




void putSTRINGU1(const char *dato,unsigned int total){
        unsigned char cont,last;

    for(cont=0,last=0;cont<total;cont++){
         if(dato[cont]!='\0') last=cont;
     }

    for (cont=0;cont<=last;cont++){
        putcTxU1(*dato++);
    }
}
//
//void putHEXU1(unsigned long dato, char caracteres){
//    unsigned long del=0x0F;
//    unsigned char nibble, x=0;
//    char str[6]={0,0,0,0,0,0};
//    while(x<caracteres){
//        nibble=(dato & del)>>(x * 4);
//        if(nibble<10)str[caracteres - x - 1] = ('0' + nibble);
//        else str[caracteres - x - 1] = ('A' + nibble - 10);
//        x=x+1;
//        del=(del<<4)|0xF;
//    }
//    for(x=0;x<caracteres;x++)
//        putcTxU1(str[x]);
//}
//
//void putlHEXU1(unsigned long dato, char caracteres){
//    unsigned long del=0x0F;
//    unsigned char nibble, x=0;
//    char str[8]={0,0,0,0,0,0,0,0};
//    while(x<caracteres){
//        nibble=(dato&del)>>(x * 4);
//        if(nibble<10)str[caracteres - x - 1]=('0' + nibble);
//        else str[caracteres - x - 1]=('A' + nibble - 10);
//        x=x+1;
//        del = (del << 4) | 0xF;
//    }
//    for (x=0;x<caracteres;x++)
//        putcTxU1(str[x]);
//}
//
//void putDEC5U2(unsigned int dato) {
//    if (dato < 10)putSTRINGU1("0000",4);
//    if (dato > 9 && dato < 100) putSTRINGU1("000",3);
//    if (dato > 99 && dato < 1000) putSTRINGU1("00",2);
//    if (dato > 999 && dato < 10000) putSTRINGU1("0",1);
//    PRNTVARU1(dato);
//}
//
//void putDEC4U2(unsigned int dato) {
//    if (dato < 10)putSTRINGU1("000",3);
//    if (dato > 9 && dato < 100)putSTRINGU1("00",2);
//    if (dato > 99 && dato < 1000)putSTRINGU1("0",1);
//    PRNTVARU1(dato);
//}
//
//void putDEC3U2(unsigned int dato) {
//    if (dato < 10)putSTRINGU1("00",2);
//    if (dato > 9 && dato < 100)putSTRINGU1("0",1);
//    PRNTVARU1(dato);
//}
//
//void putDEC2U2(unsigned int dato) {
//    if (dato < 10)putSTRINGU1("0",1);
//    PRNTVARU1(dato);
//}

// <editor-fold defaultstate="collapsed" desc="UART2">
//
//void UART2_Init() {
//    OpenUART2(UART_EN & UART_IDLE_STOP & UART_IrDA_DISABLE &
//            UART_MODE_SIMPLEX & UART_UEN_00 & UART_DIS_WAKE &
//            UART_DIS_LOOPBACK & UART_UXRX_IDLE_ONE & UART_DIS_ABAUD &
//            UART_NO_PAR_8BIT & UART_BRGH_FOUR & UART_1STOPBIT, UART_INT_TX &
//            UART_IrDA_POL_INV_ZERO & UART_SYNC_BREAK_DISABLED &
//            UART_TX_ENABLE & UART_INT_RX_CHAR & UART_ADR_DETECT_DIS &
//            UART_RX_OVERRUN_CLEAR, BRGVAL2);
//
//}
//
//void putcTxU2(char character){
//    putcUART2(character);
//    while (BusyUART2());
//}
//
//void PRNTVARU2(unsigned int var){
//    char estrin[9];
//    utoa(estrin, var, 10); //Convert an unsigned long integer to a string.
//    putsUART2((unsigned int*) estrin);
//}
//
//void PRNTsVARU2(int var){
//    char estrin[9];
//    itoa(estrin, var, 10); //Convert an signed long integer to a string.
//    putsUART2((unsigned int*) estrin);
//}
//
//void putSTRINGU2(const char *dato,unsigned int total){
//    unsigned char cont,last;
//
//    for(cont=0,last=0;cont<total;cont++){
//         if(dato[cont]!='\0') last=cont;
//     }
//
//    for (cont=0;cont<=last;cont++){
//        putcTxU2(*dato++);
//    }
//}
//
//void putHEXU2(unsigned long dato, char caracteres){
//    unsigned long del = 0x0F;
//    unsigned char nibble, x = 0;
//    char str[6] = {0, 0, 0, 0, 0, 0};
//    while (x < caracteres) {
//        nibble = (dato & del) >> (x * 4);
//        if (nibble < 10)str[caracteres - x - 1] = ('0' + nibble);
//        else str[caracteres - x - 1] = ('A' + nibble - 10);
//        x = x + 1;
//        del = (del << 4) | 0xF;
//    }
//    for (x = 0; x < caracteres; x++)
//        putcTxU2(str[x]);
//}
//
//void putlHEXU2(unsigned long dato, char caracteres){
//    unsigned long del = 0x0F;
//    unsigned char nibble, x = 0;
//    char str[8] = {0, 0, 0, 0, 0, 0, 0, 0};
//    while (x < caracteres) {
//        nibble = (dato & del) >> (x * 4);
//        if (nibble < 10)str[caracteres - x - 1] = ('0' + nibble);
//        else str[caracteres - x - 1] = ('A' + nibble - 10);
//        x = x + 1;
//        del = (del << 4) | 0xF;
//    }
//    for (x = 0; x < caracteres; x++)
//        putcTxU2(str[x]);
//}
//
//void putDEC5U2(unsigned int dato) {
//    if (dato < 10)putSTRINGU2("0000",4);
//    if (dato > 9 && dato < 100) putSTRINGU2("000",3);
//    if (dato > 99 && dato < 1000) putSTRINGU2("00",2);
//    if (dato > 999 && dato < 10000) putSTRINGU2("0",1);
//    PRNTVARU2(dato);
//}
//
//void putDEC4U2(unsigned int dato) {
//    if (dato < 10)putSTRINGU2("000",3);
//    if (dato > 9 && dato < 100)putSTRINGU2("00",2);
//    if (dato > 99 && dato < 1000)putSTRINGU2("0",1);
//    PRNTVARU2(dato);
//}
//
//void putDEC3U2(unsigned int dato) {
//    if (dato < 10)putSTRINGU2("00",2);
//    if (dato > 9 && dato < 100)putSTRINGU2("0",1);
//    PRNTVARU2(dato);
//}
//
//void putDEC2U2(unsigned int dato) {
//    if (dato < 10)putSTRINGU2("0",1);
//    PRNTVARU2(dato);
//}
//// </editor-fold>
//
