void main() {
      TRISB = 0;
      for (;;)
      {
      PORTB.F4 = 1;
      PORTB.F5 = 1;
      PORTB.F6 = 1;
      PORTB.F7 = 1;
      Delay_ms(2000);
      PORTB.F4 = 0;
      PORTB.F5 = 0;
      PORTB.F6 = 0;
      PORTB.F7 = 0;
      Delay_ms(2000);

      }
      
}