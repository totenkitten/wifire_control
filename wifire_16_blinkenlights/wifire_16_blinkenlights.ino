
/* This code is for the V1 wifire16, which uses 74x595 shift registers. 
 * 
 * Connections to the ATMega328 are as follows
 * 
 * 74x595 pin   Pin Name    ATMega328 pin   Arduino Pin Name  Description
 * 10           /SRCLR      6               4                 Master reclear, active low
 * 11           SRCLK       19              13                Shift register clock
 * 12           RCLK        11              5                 Latch storage register
 * 13           /OE         12              6                 Output enable, active low
 * 14           SER         17              11                Serial data input
 * 
 * Pin 9 (Qh') of one of the shift registers goes to SER on the other, so they're daisy chained.
 */
#define CLOCK 13
#define DATA  11
#define OE    6
#define CLR   4
#define RCLK  5

unsigned int count = 0;

void setup() {
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(OE, OUTPUT);
  digitalWrite(OE, LOW);   //disable outputs
  pinMode(CLR, OUTPUT);
  digitalWrite(CLR, HIGH);  //don't clear the register
  pinMode(RCLK, OUTPUT);
  digitalWrite(RCLK, HIGH);

  //For testing reasons, always enable output
  digitalWrite(OE, LOW);
  
}

void loop() {

//  digitalWrite(DATA, HIGH);
//  delay(30);
//  digitalWrite(DATA, LOW);
//  delay(30);

  

  //Latch low to shift out
  digitalWrite(RCLK, LOW);
  //Send the 16bit, annoyingly, this only shifts a byte
  shiftOut(DATA, CLOCK, MSBFIRST, count);
  //Done shifting out, latch to storage register
  digitalWrite(RCLK, HIGH);

  //This will eventually overflow back to 0, which is fine in this case
  count++;

  //So we can see what's going on
  delay(30);
  
}
