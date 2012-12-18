/****************************************************/
//
//
//
//
//
//
/****************************************************/

#define BLINK  P1OUT^= BIT0;	// Toggle LED

/********************* INTERRUPT TIMER A0 *********************/
// Function Name:    interrupt timer A0
// Parametter:       none
// Return value:     none
// Description:    
/****************************************************/
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{  
  clock_inc();    //Tinh toan thoi gian
  LcdClear();      // Hai dong nay dung de hien thi gia tri ra LCD
  displayScreen();
}

/********************* SETUP *********************/
// Function Name:    setup()
// Parametter:       none
// Return value:     none
// Description:      Thuc hien nhiem vu khoi ta cac gia tri ban dau
/****************************************************/
void setup(){
  Serial.begin(9600);
  LcdInitialise();
  LcdClear();

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer. This line of code is needed at the beginning of most MSP430 projects. 
  // This line of code turns off the watchdog timer, which can reset the device after a certain period of time.
  BCSCTL1 |= DIVA_3;	// ACLK/8
  BCSCTL3 |= XCAP_3;	//12.5pF cap- setting for 32768Hz crystal
  P1DIR |= 0x01;        // P1DIR is a register that configures the direction (DIR) of a port pin as an output or an input.
  P1OUT |= BIT0;	// P1.0 low

  CCTL0 = CCIE;	// CCR0 interrupt enabled
  CCR0 = 512;	// 512 -> 1 sec, 30720 -> 1 min
  TACTL = TASSEL_1 + ID_3 + MC_1;	// ACLK, /8, upmode
 }

/********************* MAIN *********************/
// Function Name:    loop()
// Parametter:       none
// Return value:     none
// Description:      Duoc lap lien tuc de lam nhung cong viec chinh
/****************************************************/
void loop(){
  if(Serial.available() ) 
  {
    processSyncMessage();
  }
}
