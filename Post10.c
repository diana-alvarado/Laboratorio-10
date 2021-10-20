/*
 * File: postlab10.c
 * Autor: Diana Alvarado
 * Creado: 18/10/2021
 * 
 * Descripción: terminal serial
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

/*
 * --------------------------- Configracion de bits --------------------------
 */
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillador Interno sin salidas, XT
#pragma config WDTE = OFF       // WDT disabled (reinicio repetitivo del pic)
#pragma config PWRTE = OFF     // PWRT enabled  (espera de 72ms al iniciar)
#pragma config MCLRE = OFF      // El pin de MCLR se utiliza como I/O
#pragma config CP = OFF         // Sin protección de código
#pragma config CPD = OFF        // Sin protección de datos
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit 
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit 
#pragma config LVP = OFF         // Low Voltage Programming Enable bit 

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit 
#pragma config WRT = OFF        // Flash Program Memory Self Write 

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

/*
 * --------------------------- Librerias --------------------------
 */

#include <xc.h>
#include <stdint.h>
#include <pic16f887.h>

/*
 * ---------------------------- Constantes -----------------------------------
 */
#define _XTAL_FREQ 8000000

/*
 * ----------------------------- Variables ----------------------------------
 */
char variable;
char uno;
char dos;
char tres;

/*
 * ------------------------------- Tabla ------------------------------------
 */

/*
 * -------------------------- Prototipos de funciones -----------------------
 */
void setup (void);
void TX_usart(char data);
char RX_resultado();
void cadena(char *str);

/*
 * ------------------------------ Interrupción -------------------------------
 */

/*
 * ----------------------------- MAIN CONFIGURACION --------------------------- 
 */
void main (void)
{
    setup ();
    
    //---------------------- Loop principal ------------------
    while (1)
    {
        cadena("\r Que opcion desea escoger? \r");
        cadena("\r 1. Cadena de caracteres \r");
        cadena("\r 2. Cambiar PORTB \r");
        cadena("\r 3. Cambiar PORTA \r");
        
        while(PIR1bits.RCIF == 0);
        variable = RCREG;
        
        switch(variable)
        {
            case('1'):
                cadena("Hola Mundo\r");
                break;

            case ('2'):
                cadena("Ingresa un valor para el PORTB tiene que ser de 3 dígitos, por ejemplo 001 : ");
                while (PIR1bits.RCIF == 0);
                PORTB = 0x00;
                uno = RCREG - 48;
                while (PIR1bits.RCIF == 0);
                dos = RCREG;
                while (PIR1bits.RCIF == 0);
                tres = RCREG;
                __delay_ms(500);
                PORTB = uno;
                __delay_ms(500);
                PORTB = dos;
                __delay_ms(500);
                PORTB = tres;
                __delay_ms(500);
                PORTB = uno*100 + dos*10 + tres;
                cadena("\r se guardo el dato \r");
                break;

            case('3'):
                cadena("Ingrese un valor para el PORTA ingrese tres digitos, por ejemplo 020: ");
                while (PIR1bits.RCIF == 0);
                PORTA = 0x00;
                uno = RCREG - 48;
                while (PIR1bits.RCIF == 0);
                dos = RCREG;
                while (PIR1bits.RCIF == 0);
                tres = RCREG;
                __delay_ms(500);
                PORTA = uno;
                __delay_ms(500);
                PORTA = dos;
                __delay_ms(500);
                PORTA = tres;
                __delay_ms(500);
                PORTA = uno*100 + dos*10 + tres;
                cadena("\r se guardo el dato \r");
                break;
                

        }

    }
        return;
}
/*
 * -------------------------------- Funciones --------------------------------
 */
void setup (void) 
{
    //Configuración de puertos
    ANSEL = 0;
    ANSELH = 0;
    
    TRISB = 0;
    PORTB = 0;
    
    TRISA = 0;
    PORTA = 0;
    
    //9600 bauds
    //Configuración del oscilador a 8MHz
    OSCCONbits.IRCF = 0b111;
    OSCCONbits.SCS = 1;
    
    //Configuración de TX y RX
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    BAUDCTLbits.BRG16 = 1;
    
    SPBRG = 207;                 //SPBRGH : SPBRG = 25
    SPBRGH = 0;
    
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;          //Modo 8 bits
    RCSTAbits.CREN = 1;         //Habilitmaos la recpeción
    TXSTAbits.TXEN = 1;         //Habilitamos la transmisión
    //TXSTAbits.TX9 = 0;
}
void cadena (char *str){
        while(*str != '\0'){
            TX_usart(*str);
            str++;
        }
    }
void TX_usart(char data)
    {
        while(TXSTAbits.TRMT == 0);
        TXREG = data;
    }
char RX_resultado()
    {
        return RCREG;
    }



