/*    
 * hc    atmega8    F_CPU = 16000000 Hz
 * 
 * Created on: 29.07.2023
 *     Author: Tomasz Kilinczyk
*/

#ifndef HC_
#define HC_
 
/* hardware SPI */
#define MOSI (1<<PB3)  //   <---- A (SER IN)
#define SCK (1<<PB5)  //   <---- SHIFT CLOCK (SC)
#define LT (1<<PB2)   //   <---- LATCH CLOCK (LT)
     
#define LT_ON PORTB |= LT            
#define LT_OFF PORTB &= ~LT
     
void initTimer ( void ) ;
void InitSpi ( void ) ;
void SendSpiDisplay ( uint8_t x , uint8_t y , uint8_t state ) ;  
void ClearDisplay (void);  

void print_E ( int8_t x , int8_t y , uint8_t stete1 ) ;
void print_H ( int8_t x , int8_t y , uint8_t stete1 ) ;  
void print_L ( int8_t x , int8_t y , uint8_t stete1 ) ;
void print_O ( int8_t x , int8_t y , uint8_t stete1 ) ;

void print_Hello ( int8_t x , int8_t y , uint8_t stete1 ) ;
  

#endif  /* HC_ */            