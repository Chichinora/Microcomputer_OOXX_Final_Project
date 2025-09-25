/*
 * File:   final_project.c
 * Author: NB
 *
 * Created on 2025?1?13?, ?? 5:29
 */

#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include <stdbool.h>
#include "stdio.h"
#include "string.h"
#define _XTAL_FREQ 1000000
// using namespace std;
int player_a[3] = {0}, player_b[3] = {0};
int turn = 0; //0 = turn O, 1 = turn X
char str[20];
int temp = 0;
int JUDGE(int turn, int player[3]){
    int arr[3];
    arr[0] = player[0];
    arr[1] = player[1];
    arr[2] = player[2];
    //sort arr
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[i]) {
                int x = arr[j];
                    arr[j] = arr[i];
                    arr[i] = x;
            }
        }
    }
    int a = 0;
    bool win = false;
    if (arr[0]==1 && arr[1]==2 && arr[2]==3) win = true;
    else if (arr[0]==4 && arr[1]==5 && arr[2]==6) win = true;
    else if (arr[0]==7 && arr[1]==8 && arr[2]==9) win = true;
    else if (arr[0]==1 && arr[1]==4 && arr[2]==7) win = true;
    else if (arr[0]==2 && arr[1]==5 && arr[2]==8) win = true;
    else if (arr[0]==3 && arr[1]==6 && arr[2]==9) win = true;
    else if (arr[0]==1 && arr[1]==5 && arr[2]==9) win = true;
    else if (arr[0]==3 && arr[1]==5 && arr[2]==7) win = true;
    if (win == true){
        if (turn == 0) a = 1;
        else if (turn == 1) a = 2;
    }
    else if (win == false) a = 0;
    return a;
}
void Mode2(){   // Todo : Mode2 
    return ;
}
void main(void) 
{
    
    SYSTEM_Initialize() ;
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
    if (temp == 0) UART_Write_Text("Player 1 input:");
    while(1) {
        if(temp != 0){
            exit(0);
        }
    }
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{
    if (RCIF){
        strcpy(str, GetString());
        MyusartRead();
        char ch = RCREG;
        if (ch == '\r'){ //we get a full string
            int position = ((int)str[0])-48; //the position wanted to light up
            //judge if the input is validate
            if (turn == 0){
                if (player_a[2] != 0){
                    switch(player_a[0]){
                        case 1:
                            LATD = LATD & 254;
                            break;
                        case 2:
                            LATD = LATD & 253;
                            break;
                        case 3:
                            LATD = LATD & 251;
                            break;
                        case 4:
                            LATC = LATC & 254;
                            break;
                        case 5:
                            LATC = LATC & 253;
                            break;
                        case 6:
                            LATC = LATC & 251;
                            break;
                        case 7:
                            LATA = LATA & 254;
                            break;
                        case 8:
                            LATA = LATA & 253;
                            break;
                        case 9:
                            LATA = LATA & 251;
                            break;
                    }
                    player_a[0] = player_a[1];
                    player_a[1] = player_a[2];
                    player_a[2] = position;
                    
                }
                else {
                    if (player_a[0] == 0) player_a[0] = position;
                    else if (player_a[1] == 0) player_a[1] = position;
                    else if (player_a[2] == 0) player_a[2] = position;
                }
                switch(player_a[0]){
                        case 1:
                            LATD = LATD | 1;
                            break;
                        case 2:
                            LATD = LATD | 2;
                            break;
                        case 3:
                            LATD = LATD | 4;
                            break;
                        case 4:
                            LATC = LATC | 1;
                            break;
                        case 5:
                            LATC = LATC | 2;
                            break;
                        case 6:
                            LATC = LATC | 4;
                            break;
                        case 7:
                            LATA = LATA | 1;
                            break;
                        case 8:
                            LATA = LATA | 2;
                            break;
                        case 9:
                            LATA = LATA | 4;
                            break;
                    }
                switch(player_a[1]){
                        case 1:
                            LATD = LATD | 1;
                            break;
                        case 2:
                            LATD = LATD | 2;
                            break;
                        case 3:
                            LATD = LATD | 4;
                            break;
                        case 4:
                            LATC = LATC | 1;
                            break;
                        case 5:
                            LATC = LATC | 2;
                            break;
                        case 6:
                            LATC = LATC | 4;
                            break;
                        case 7:
                            LATA = LATA | 1;
                            break;
                        case 8:
                            LATA = LATA | 2;
                            break;
                        case 9:
                            LATA = LATA | 4;
                            break;
                    }
                switch(player_a[2]){
                        case 1:
                            LATD = LATD | 1;
                            break;
                        case 2:
                            LATD = LATD | 2;
                            break;
                        case 3:
                            LATD = LATD | 4;
                            break;
                        case 4:
                            LATC = LATC | 1;
                            break;
                        case 5:
                            LATC = LATC | 2;
                            break;
                        case 6:
                            LATC = LATC | 4;
                            break;
                        case 7:
                            LATA = LATA | 1;
                            break;
                        case 8:
                            LATA = LATA | 2;
                            break;
                        case 9:
                            LATA = LATA | 4;
                            break;
                    }
                //turn = (turn+1)%2;
            }else if(turn == 1){
                if (player_b[2] != 0){
                    switch(player_b[0]){
                        case 1:
                            LATD = LATD & 254;
                            break;
                        case 2:
                            LATD = LATD & 253;
                            break;
                        case 3:
                            LATD = LATD & 251;
                            break;
                        case 4:
                            LATC = LATC & 254;
                            break;
                        case 5:
                            LATC = LATC & 253;
                            break;
                        case 6:
                            LATC = LATC & 251;
                            break;
                        case 7:
                            LATA = LATA & 254;
                            break;
                        case 8:
                            LATA = LATA & 253;
                            break;
                        case 9:
                            LATA = LATA & 251;
                            break;
                    }
                    player_b[0] = player_b[1];
                    player_b[1] = player_b[2];
                    player_b[2] = position;
                    
                }
                else {
                    if (player_b[0] == 0) player_b[0] = position;
                    else if (player_b[1] == 0) player_b[1] = position;
                    else if (player_b[2] == 0) player_b[2] = position;
                }
                switch(player_b[0]){
                        case 1:
                            LATD = LATD | 1;
                            break;
                        case 2:
                            LATD = LATD | 2;
                            break;
                        case 3:
                            LATD = LATD | 4;
                            break;
                        case 4:
                            LATC = LATC | 1;
                            break;
                        case 5:
                            LATC = LATC | 2;
                            break;
                        case 6:
                            LATC = LATC | 4;
                            break;
                        case 7:
                            LATA = LATA | 1;
                            break;
                        case 8:
                            LATA = LATA | 2;
                            break;
                        case 9:
                            LATA = LATA | 4;
                            break;
                    }
                switch(player_b[1]){
                        case 1:
                            LATD = LATD | 1;
                            break;
                        case 2:
                            LATD = LATD | 2;
                            break;
                        case 3:
                            LATD = LATD | 4;
                            break;
                        case 4:
                            LATC = LATC | 1;
                            break;
                        case 5:
                            LATC = LATC | 2;
                            break;
                        case 6:
                            LATC = LATC | 4;
                            break;
                        case 7:
                            LATA = LATA | 1;
                            break;
                        case 8:
                            LATA = LATA | 2;
                            break;
                        case 9:
                            LATA = LATA | 4;
                            break;
                    }
                switch(player_b[2]){
                        case 1:
                            LATD = LATD | 1;
                            break;
                        case 2:
                            LATD = LATD | 2;
                            break;
                        case 3:
                            LATD = LATD | 4;
                            break;
                        case 4:
                            LATC = LATC | 1;
                            break;
                        case 5:
                            LATC = LATC | 2;
                            break;
                        case 6:
                            LATC = LATC | 4;
                            break;
                        case 7:
                            LATA = LATA | 1;
                            break;
                        case 8:
                            LATA = LATA | 2;
                            break;
                        case 9:
                            LATA = LATA | 4;
                            break;
                    }
//                turn = (turn+1)%2;
            }

            if(turn == 0){
                temp = JUDGE(turn,player_a);
            }else if(turn == 1){
                temp = JUDGE(turn,player_b);
            }
            if(temp == 0){
                turn = (turn+1)%2;
                //if yes -> turn = (turn+1)%2
                //test if player win
                if (turn == 1) UART_Write_Text("Player 2 input:");
                else if (turn == 0) UART_Write_Text("Player 1 input:");
            }else{
                //__delay_ms(10);
                if(temp == 1) UART_Write_Text("Player 1 WIN\n\r");
                else if(temp == 2) UART_Write_Text("Player 2 WIN\n\r");
                
            }
        }   
    }
    if(PIR1bits.TMR2IF == 1){   //LED
        //test which led if for player b
        //toggle those led
        switch(player_b[0]){
                        case 1:
                            LATD = LATD ^ 1;
                            break;
                        case 2:
                            LATD = LATD ^ 2;
                            break;
                        case 3:
                            LATD = LATD ^ 4;
                            break;
                        case 4:
                            LATC = LATC ^ 1;
                            break;
                        case 5:
                            LATC = LATC ^ 2;
                            break;
                        case 6:
                            LATC = LATC ^ 4;
                            break;
                        case 7:
                            LATA = LATA ^ 1;
                            break;
                        case 8:
                            LATA = LATA ^ 2;
                            break;
                        case 9:
                            LATA = LATA ^ 4;
                            break;
                    }
                switch(player_b[1]){
                        case 1:
                            LATD = LATD ^ 1;
                            break;
                        case 2:
                            LATD = LATD ^ 2;
                            break;
                        case 3:
                            LATD = LATD ^ 4;
                            break;
                        case 4:
                            LATC = LATC ^ 1;
                            break;
                        case 5:
                            LATC = LATC ^ 2;
                            break;
                        case 6:
                            LATC = LATC ^ 4;
                            break;
                        case 7:
                            LATA = LATA ^ 1;
                            break;
                        case 8:
                            LATA = LATA ^ 2;
                            break;
                        case 9:
                            LATA = LATA ^ 4;
                            break;
                    }
                switch(player_b[2]){
                        case 1:
                            LATD = LATD ^ 1;
                            break;
                        case 2:
                            LATD = LATD ^ 2;
                            break;
                        case 3:
                            LATD = LATD ^ 4;
                            break;
                        case 4:
                            LATC = LATC ^ 1;
                            break;
                        case 5:
                            LATC = LATC ^ 2;
                            break;
                        case 6:
                            LATC = LATC ^ 4;
                            break;
                        case 7:
                            LATA = LATA ^ 1;
                            break;
                        case 8:
                            LATA = LATA ^ 2;
                            break;
                        case 9:
                            LATA = LATA ^ 4;
                            break;
                    }
        PIR1bits.TMR2IF = 0;
    }
    __delay_ms(10);
    return;
}

