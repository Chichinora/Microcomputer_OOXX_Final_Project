#include <xc.h>
#include <pic18f4520.h>
    //setting TX/RX

char mystring[20];
int lenStr = 0;

void UART_Initialize() {
           
    /*       TODObasic   
           Serial Setting      
        1.   Setting Baud rate
        2.   choose sync/async mode 
        3.   enable Serial port (configures RX/DT and TX/CK pins as serial port pins)
        3.5  enable Tx, Rx Interrupt(optional)
        4.   Enable Tx & RX
    */        
    TRISCbits.TRISC6 = 1;            
    TRISCbits.TRISC7 = 1;            
    
    //  Setting baud rate = 1200
    TXSTAbits.SYNC = 0;  // Asynchronous mode           
    BAUDCONbits.BRG16 = 0;          
    TXSTAbits.BRGH = 0;
    SPBRG = 51;      
    
   //   Serial enable
    RCSTAbits.SPEN = 1;  //Enable asynchronous serial port              
    PIR1bits.TXIF = 1;   //TXREG is empty
    PIR1bits.RCIF = 0;   //Reception is not complete
    TXSTAbits.TXEN = 1;  //Enable transmission           
    RCSTAbits.CREN = 1;  //Enables receiver             
    PIE1bits.TXIE = 0;   //Enable interrupt       
    IPR1bits.TXIP = 0;   //Transmit Interrupt is low Priority             
    PIE1bits.RCIE = 1;   //Enable interrupt              
    IPR1bits.RCIP = 1;   //Receive Interrupt is high Priority    
    
    ADCON1 = 0x0f;       //Digital
    INTCONbits.GIEH = 1;    // enable high priority interrupt
    INTCONbits.GIEL = 1;    // disable low priority interrupt
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1;   //Enables Priority
    INTCONbits.GIE = 1;     //Set Global Interrupt Enable bit
    INTCONbits.INT0IE = 1;  //Enables the INT0 external interrupt
    INTCONbits.INT0IF = 0;  //Clear Interrupt Flag bit
    
    PIR1bits.TMR2IF = 0;		//????TIMER2??????????TMR2IF?TMR2IE?TMR2IP?
    IPR1bits.TMR2IP = 1;	//set timer high priority
    PIE1bits.TMR2IE = 1;
    T2CON = 255;            //?Prescale?Postscale???1:16???????256??????TIMER2+1
    //0.25s = 61 0.5s = 122 1s = 244
    PR2 = 244;
    
    TRISAbits.RA0 = 0;
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 0;
    LATA = 0;
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC2 = 0;
    LATC = 0;
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;
    LATD = 0;
        
    }

void UART_Write(unsigned char data)  // Output on Terminal
{
    while(!TXSTAbits.TRMT);
    TXREG = data;              //write to TXREG will send data 
}


void UART_Write_Text(char* text) { // Output on Terminal, limit:10 chars
    for(int i=0;text[i]!='\0';i++)
        UART_Write(text[i]);
}

void ClearBuffer(){
    for(int i = 0; i < 10 ; i++)
        mystring[i] = '\0';
    lenStr = 0;
}

void MyusartRead()
{
    /* TODObasic: try to use UART_Write to finish this function */
    char temp = RCREG;
    if (temp == '\r'){
        UART_Write('\n');
        UART_Write('\r');
        ClearBuffer();
    }
    else {
        UART_Write(temp);
        if(lenStr < 9) {   // Prevent buffer overflow
            mystring[lenStr++] = temp;
            mystring[lenStr] = '\0';  // Null terminate
        }
        else ClearBuffer();
    }  
    return ;
}

char *GetString(){
    return mystring;
}


// void interrupt low_priority Lo_ISR(void)
void __interrupt(low_priority)  Lo_ISR(void)
{
    if(RCIF)
    {
        if(RCSTAbits.OERR)
        {
            CREN = 0;
            Nop();
            CREN = 1;
        }
        
        MyusartRead();
    }
    
   // process other interrupt sources here, if required
    return;
}