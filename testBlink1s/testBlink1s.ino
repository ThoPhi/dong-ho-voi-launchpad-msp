// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{  
  P1OUT^= BIT0;
}

void setup(){
  BCSCTL1 |= DIVA_3; // ACLK/8
  BCSCTL3 |= XCAP_3; //12.5pF cap- setting for 32768Hz crystal

  CCTL0 = CCIE;	// CCR0 interrupt enabled
  CCR0 = 512;	// 512 -> 1 sec, 30720 -> 1 min
  TACTL = TASSEL_1 + ID_3 + MC_1; // ACLK, /8, upmode

  P1DIR |= 0x01;  // P1.0 Output
  P1OUT |= BIT0;  // P1.0 low
}
void loop(){  
}

