/*
 * hc.c    atmega8    F_CPU = 16000000 Hz
 *
 * Created on: 29.07.2023
 *     Author: Tomasz Kilianczyk 
*/
#include <avr/io.h>
#include <avr/interrupt.h>
                              
#include "hc.h"


void initTimer( void ) {


    // Ustawienie trybu CTC (Clear Timer on Compare Match) dla Timer1
    TCCR1B |= ( 1 << WGM12 ) ;

    // Ustawienie preskalera na 256
    TCCR1B |= ( 1 << CS12 ) ;

    // Ustawienie wartoœci OCR1A dla czêstotliwoœc odliczania ( taktowania )
    OCR1A = 2000;

    // W³¹czenie przerwania dla porównania TIMER1_COMPA
    TIMSK |= ( 1 << OCIE1A ) ;

    // W³¹czenie globalnego przerwania
    sei() ;
}






void InitSpi( void ) {

    DDRB |= MOSI | SCK | LT; // piny SPI jako wyj?cia
    SPCR |= ( 1 << SPE ) | ( 1 << MSTR ); // w³acz SPI i ustaw Master
    SPSR |= ( 1 << SPI2X ); // fosc/2
}



void SendSpiDisplay( uint8_t x, uint8_t y , uint8_t state ) {

    uint8_t x1 = 0;
    uint8_t y1 = 0;

    if ( x == 0 ) {
        x1 = 1 ;
    }
    if ( x == 1 ) {
        x1 = 2 ;
    }
    if ( x == 2 ) {
        x1 = 4 ;
    }
    if ( x == 3 ) {
        x1 = 8 ;
    }
    if ( x == 4 ) {
        x1 = 16 ;
    }
    if ( x == 5 ) {
        x1 = 32 ;
    }
    if ( x == 6 ) {
        x1 = 64 ;
    }
    if ( x == 7 ) {
        x1 = 128 ;
    }

    if ( y == 0 ) {
        y1 = 1 ;
    }
    if ( y == 1 ) {
        y1 = 2 ;
    }
    if ( y == 2 ) {
        y1 = 4 ;
    }
    if ( y == 3 ) {
        y1 = 8 ;
    }
    if ( y == 4 ) {
        y1 = 16 ;
    }
    if ( y == 5 ) {
        y1 = 32 ;
    }
    if ( y == 6 ) {
        y1 = 64 ;
    }
    if ( y == 7 ) {
        y1 = 128 ;
    }



    if ( !state ) {
        x1 = 0 ;    //gaszenie wysiwietlacza
        y1 = 0 ;
    }

    SPDR =   ~x1 ;   //wyslanie danych x

    while ( !( SPSR & ( 1 << SPIF ) ) );

    SPDR =  ~y1 ;   //wyslanie danych y

    while ( !( SPSR & ( 1 << SPIF ) ) );

    LT_ON ;        //wyzwolenie zatrzasku
    LT_OFF ;


}

void ClearDisplay( void ) {

    //gaszenie wysiwietlacza


    uint8_t x1 = 0 ;
    uint8_t y1 = 0 ;

    SPDR =  ~x1 ;   //wyslanie danych x

    while ( !( SPSR & ( 1 << SPIF ) ) );

    SPDR =  ~y1 ;   //wyslanie danych y

    while ( !( SPSR & ( 1 << SPIF ) ) );

    LT_ON ;        //wyzwolenie zatrzasku
    LT_OFF ;


}

void print_E( int8_t x , int8_t y , uint8_t stete1 ) {

    //litera E


    for ( uint8_t i = 0 ; i < 5 ; i++ ) {
        SendSpiDisplay( i + x  , y , stete1 ) ;

    }


    for ( uint8_t i = 0 ; i < 3; i++ ) {
        SendSpiDisplay( x  , y + i, stete1 ) ;

    }


    for ( uint8_t i = 0 ; i < 3; i++ ) {
        SendSpiDisplay( x + 2, i + y , stete1 ) ;

    }


    for ( uint8_t i = 0 ; i < 3 ; i++ ) {
        SendSpiDisplay( x + 4, i + y , stete1 ) ;

    }



}


void print_H( int8_t x , int8_t y , uint8_t stete1 ) {

    //litera H


    for ( uint8_t i = 0 ; i < 5 ; i++ ) {
        SendSpiDisplay( i + x  , y , stete1 ) ;

    }


    for ( uint8_t i = 0 ; i < 4 ; i++ ) {
        SendSpiDisplay( x + 2, i + y , stete1 ) ;

    }


    for ( uint8_t i = 0 ; i < 5 ; i++ ) {
        SendSpiDisplay( i + x  , y + 3, stete1 ) ;

    }

}

void print_L( int8_t x , int8_t y , uint8_t stete1 ) {

    //litera L


    for ( uint8_t i = 0 ; i < 5 ; i++ ) {
        SendSpiDisplay( i + x  , y , stete1 ) ;

    }


    for ( uint8_t i = 0 ; i < 3 ; i++ ) {
        SendSpiDisplay( x + 4, i + y , stete1 ) ;

    }



}

void print_O( int8_t x , int8_t y , uint8_t stete1 ) {

    //litera O


    for ( uint8_t i = 0 ; i < 5 ; i++ ) {
        SendSpiDisplay( i + x  , y , stete1 ) ;

    }


    for ( uint8_t i = 0 ; i < 3; i++ ) {
        SendSpiDisplay( x  , y + i, stete1 ) ;

    }

    for ( uint8_t i = 0 ; i < 5 ; i++ ) {
        SendSpiDisplay( i + x  , y + 2, stete1 ) ;

    }


    for ( uint8_t i = 0 ; i < 3 ; i++ ) {
        SendSpiDisplay( x + 4, i + y , stete1 ) ;

    }



}

void print_Hello( int8_t x , int8_t y , uint8_t stete1 ) {

    //slowo hello



    print_H( x , y , stete1 ) ;

    print_E( x , y + 5, stete1 ) ;

    print_L( x , y + 9, stete1 ) ;

    print_L( x , y + 13, stete1 ) ;

    print_O( x , y + 17, stete1 ) ;


}