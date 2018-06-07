#include<avr/io.h>

int k=2000;                         //Variable to produce the delay of blinking.
int main()
{ 
  DDRB |= (1<<PINB5);               //Configuring PINB5 of portb as output.
  DDRD = 0x00;                      //Configuring PIND2, PIND3 of portd as input.    
  PORTD = 0b00001100;
  int i=0;
  
  TCCR1B |= (1<<CS10);              //no prescaler.
  
  EIMSK |= (1<<INT0) | (1<<INT1);   //Enabling external interrupts.
  EICRA |= (1<<ISC01) | (1<<ISC11); //falling edge.
  sei();                            //Enabling global interrupts.

  while(1)
  {
    if(TCNT1>10000)                 //Start of code to blink the led.
    {
      TCNT1 = 0;
      i++;  
    }
    if(i==k)
    {
      PORTB ^= (1<<PINB5);
      i=0;
    }
  }                                 //End of code to blink the led.                             
}
ISR(INT0_vect)                      //Decreases blinking rate.
{
  k+=400;
}
ISR(INT1_vect)                      //Increases binking rate.
{
  k-=400;
}



 
