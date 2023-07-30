/*  
 * main.c    ATmega8    F_CPU = 16000000 Hz
 * 
 * Created on: 29.07.2023
 *   Author: Tomasz K
*/
     
#include <avr/io.h>       
#include <util/delay.h>
#include <avr/interrupt.h>

#include "hc.h"



volatile uint8_t timerOverflowCount = 0 ;
volatile uint8_t t = 0 ;                     

int c = 0 ;
int b = 8 ;                     
                     

int main( void ) {


 InitSpi();
 initTimer();
  

    while(1) {
  print_Hello( 1 ,b , ~ t ) ; 
  if( t==0 ) c++ ;
  if( c > 200 ){ c = 0  ; b-- ; }
  if(b < -24 ){ b = 8 ; }
    }
                         
} 
ISR(TIMER1_COMPA_vect) {
  
    timerOverflowCount++;
    
    if ( timerOverflowCount >= 8 ) {  // czas przerwania
      
        t = 1; // Prze³¹czenie stanu diody LED
        
        timerOverflowCount = 0;
         } 
       else { 
      
            t = 0 ; 
            
            }
}