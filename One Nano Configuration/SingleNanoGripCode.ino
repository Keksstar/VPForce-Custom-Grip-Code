#include <SPI.h>

//Arduino Nano Based code - 10 digital pins usable + 8 Analog Pins available as optional digintal pins

//To be configured for 16 button inputs two axes

//THIS IS THE PROFILE WILL ONLY WORK ON ITS OWN FOR THE CONFIGURATION DESCRIBED ABOVE.

//Based on the WinWing profile in the VPForce configurator which uses the following structure per Walmis, updated 11/27/24:

// #define B(i) (i-1)
// winwing hat buttons { .left_bit = B(48), .right_bit = B(46), .up_bit = B(45), .down_bit = B(47), .center_bit = UNSET },
// union {
//   struct {
//    uint32_t buttons_lo; //[0..3]
//    uint16_t buttons_hi : 12; //[4] total 48 buttons
//    uint16_t reserved : 4; //hat directional value, unused [5]
//    uint8_t reserved_unused; //[6]
//    uint8_t id; //should be 0 for ww adapter, 0x10 for custom device, axis-to-hat will be ignored (will be added in v1.017b9) [7]

//    //first and second axis has hat mapped to axis-to-button for thumb hat (id=0)
//    //4th axis has a trigger axis-to-button mapped on ww adapter
//    int16_t axis[4]; // range 0..4096, center at 2048
//   } __attribute((packed));
//   uint8_t data[16];
//  } ;

// Grip Debug gives the following for custom device: 
// FF FF FF FF FF FF 00 10 FF 03 FF 03 FF 03 FF 03
// Each pair is an 8 bit number (hex), the structure reserves the first 6 pairs as buttons, the 7th pair is unused, the 8th pair is 0x10 to ignore axis to hat, and the
// remaining 8 pairs are the axis data, with two consecutive pairs making up the axis value (9&10, 11&12, 13&14, 15&16)

int digPin0 = A0; // Button input
int digPin1 = A1; // Button input
int digPin2 = A2; // Button input
int digPin3 = A3; // Button input
int digPin4 = A4; // Button input
int digPin5 = A5; // Button input
int analogPin1 = A6; 
int analogPin2 = A7; 
int val1 = 0;  // variable to store the value read by an axis
int val2 = 0;  // variable to store the value read by an axis
long smoothval1 = 0; 
long smoothval2 = 0; 
long conval1 = 0; //variable to store the converted axis value
long conval2 = 0; //variable to store the converted axis value
int minval1; //variable to store min for conversion
int maxval1; //variable to store max for conversion
int minval2; //variable to store min for conversion
int maxval2; //variable to store max for conversion
volatile byte lowerbit1 = 160;
volatile byte upperbit1 = 176; 
volatile byte lowerbit2 = 192;
volatile byte upperbit2 = 208; 
volatile byte buttonbit1 = 255; 
volatile byte buttonbit2 = 255; 
volatile byte pullcount; // variable to count the number of SPI pulls
int dval1;
int dval2; 
int dval3; 
int dval4;
int dval5; 
int dval6;
int dval7;
int dval8;
int dval9;
int dval10;
int dval11;
int dval12;
int dval13;
int dval14;
int dval15;
int dval16; 



void setup() {

//Serial.begin(9600); //debug

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT); //Pin 12
  pinMode(MOSI, INPUT); //Pin 11
  pinMode(SS, INPUT);  //Pin 10
  pinMode(digPin0, INPUT_PULLUP); //Button, default state high. 
  pinMode(digPin1, INPUT_PULLUP); //Button, default state high. 
  pinMode(digPin2, INPUT_PULLUP); //Button, default state high. 
  pinMode(digPin3, INPUT_PULLUP); //Button, default state high. 
  pinMode(digPin4, INPUT_PULLUP); //Button, default state high. 
  pinMode(digPin5, INPUT_PULLUP); //Button, default state high.  
  pinMode(9, INPUT_PULLUP); //Button, default state high. 
  pinMode(8, INPUT_PULLUP); //Button, default state high. 
  pinMode(7, INPUT_PULLUP); //Button, default state high. 
  pinMode(6, INPUT_PULLUP); //Button, default state high. 
  pinMode(5, INPUT_PULLUP); //Button, default state high. 
  pinMode(4, INPUT_PULLUP); //Button, default state high. 
  pinMode(3, INPUT_PULLUP); //Button, default state high.
  pinMode(2, INPUT_PULLUP); //Button, default state high.
  pinMode(1, INPUT_PULLUP); //Button, default state high.  
  pinMode(0, INPUT_PULLUP); //Button, default state high.  
  
  //intitialize pull counter
  pullcount = 1; 

  minval1 = analogRead(analogPin1); //initialize minval1
  maxval1 = minval1; //initialize maxval1
  minval2 = analogRead(analogPin2);  // initialize minval2
  maxval2 = minval2;  // initialize maxval2

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);
    
  //Enablie PCIE0 Port B for pin 10 interrupt
  PCICR |= B00000001;
  //Enable PICINT2 (Pin D10) for the interrupt
  PCMSK0 |= B00000100;

}

//REPLACES HARDWARE INTERRUPT ON PIN 2
ISR (PCINT0_vect)
{
  if (digitalRead(10) == LOW)
  {
    pullcount = 1;
    SPDR = buttonbit1; //send byte 1 buttons
    pullcount++;
  }
}

// SPI interrupt routine
//This interrupt is called everytime SPI transfer is called from the master
ISR (SPI_STC_vect)
{


 if (pullcount == 2) // byte 2 buttons
    {
      SPDR = buttonbit2; //send byte2 buttons
      pullcount++; 
    }
    else if (pullcount == 3) //byte 3 buttons
    {
      SPDR = 255; //send 0xFF to keep buttons unpressed
      pullcount++; 
    }
    else if (pullcount == 4) //byte 4 buttons
    {
      SPDR = 255; //send 0xFF to keep buttons unpressed
      pullcount++;
    }
    else if (pullcount == 5) //byte 5 buttons
    {
      SPDR = 255; //send 0xFF to keep buttons unpressed
      pullcount++; 
    }
    else if (pullcount == 6) //byte 6 buttons
    {
      SPDR = 255; //send 0xFF to keep buttons unpressed
      pullcount++;  
    }
    else if (pullcount == 7) //byte 7 buttons
    {
      SPDR = 0; //send reserved 0
      pullcount++;  
    }
    else if (pullcount == 8) //byte 8 reserved
    {
      SPDR = 16; //send 0x10 to disable axis to hat
      pullcount++;  
    }
    else if (pullcount == 9) //byte 9 axis1b, signal from A6
    {
      //Swap the following two lines comments if axis is unused: 
      //SPDR = 0; 
      SPDR = lowerbit1;
      pullcount++;  
    }
    else if (pullcount == 10) //byte 10 axis1a, signal from A6
    {
      //Swap the following two lines comments if axis is unused: 
      //SPDR = 0; 
      SPDR = upperbit1;
      pullcount++;  
    }
    else if (pullcount == 11) //byte 11 axis2b, signal from A7
    {
      //Swap the following two lines comments if axis is unused: 
      //SPDR = 0; 
      SPDR = lowerbit2;
      pullcount++;  
    }
    else if (pullcount == 12) //byte 12 axis2a, signal from A7
    {
      //Swap the following two lines comments if only using 1 axis
      //SPDR = 0; 
      SPDR = upperbit2;
      pullcount++;  
    }
    else if (pullcount == 13) //byte 13 axis3b
    {
      SPDR = 0;
      pullcount++;  
    }
    else if (pullcount == 14) //byte 14 axis3a
    {
      SPDR = 0;
      pullcount++;  
    }
    else if (pullcount == 15) //byte 15 axis4b
    {
      SPDR = 0;
      pullcount++;  
    }
    else if (pullcount == 16) //byte 16 axis4a
    {
      SPDR = 0;
      pullcount++;  
    }
    else 
    {
      SPDR = 255;
      pullcount++; 
    }
  

}  // end of interrupt routine SPI_STC_vect


void loop()
{  
  val1 = analogRead(analogPin1); 
  val2 = analogRead(analogPin2);
  smoothval1 = 0;
  smoothval2 = 0;   
    
    //smoothing to eliminate noise on the axis data
    for (int v1 = 0; v1 < 64; v1++) //take samples of analogPin1
    {
      smoothval1 = smoothval1 + analogRead(analogPin1); 
    }
    smoothval1 = round(smoothval1 / 64); // divide by samples to average smoothval1

    for (int v2 = 0; v2 < 64; v2++) //take samples of analogPin2
    {
      smoothval2 = smoothval2 + analogRead(analogPin2); 
    }
    smoothval2 = round(smoothval2 / 64);  // divide by samples to average smoothval2
  
  // the following code handles scaling for calibration, min and max to be used for conversion to 0..4096 values
  // cycle the axes over their full range each startup to set min and max, they will adjust as needed if full range is not achieved. 
  if (val1 < minval1)
    {
      minval1 = val1; //set new minimum to new low value
    }
  if (val1 > maxval1)
    {
      maxval1 = val1; //set new maxiumum to high value
    }
  if (val2 < minval2)
    {
      minval2 = val2; //set new minimum to new low value
    }
  if (val2 > maxval2)
    {
      maxval2 = val2; //set new maxiumum to high value
    }

    // the data shifts 8 bits at a time. The ADC of the arduino is a 10 bit ADC, and
    // the WinWing structure is given for a 12 bit value (0..4095), so 
    // we need to convert the 10 bit to a 12 bit number, the calibration must also be done in the
    // software, so we can use the conversion opportunity to scale to use the full range

if((maxval1 - minval1) > 0 )
  {
    int p = maxval1 - minval1;
    int q = smoothval1 - minval1;
    float r = (float)q / (float)p;
      if (r < 0.05) // lower deadzone
      {
        r = 0.0; 
      }
      if (r > 0.95) //upper deadzone
      {
        r = 1.0; 
      }
    conval1 = round(r * 4095); 
  }
else
  {
    conval1 = 0;
  }

if(maxval2 > minval2)
  {
    int i = maxval2 - minval2;
    int j = smoothval2 - minval2;
    float k = (float)j / (float)i;
      if (k < 0.05) // lower deadzone
      {
        k = 0.0; 
      }
      if (k > 0.95) //upper deadzone
      {
        k = 1.0; 
      } 
    conval2 = round(k * 4095); 
    
  }
else
  {
    conval2 = 0;
  }


    upperbit1 = conval1 >> 8;
    lowerbit1 = conval1;
    upperbit2 = conval2 >> 8;
    lowerbit2 = conval2;

// Serial.print(val1);
// Serial.print(",");
// Serial.print(minval1);
// Serial.print(",");
// Serial.print(maxval1);
// Serial.print(",");
// Serial.print(conval1);
// Serial.print(",");
// Serial.print(val2);
// Serial.print(",");
// Serial.print(minval2);
// Serial.print(",");
// Serial.print(maxval2);
// Serial.print(",");
// Serial.println(conval2); 
// delay(500); 

//pack the button inputs into an 8 bit where 1 = unpressed, 0 = pressed
    //Eight entries for buttonbit1
    if (digitalRead(0) == LOW)
      {
        dval1 = 254; //11111110
        buttonbit1 &= dval1;
      }
    else
      {
        dval1 = 1; //00000001
        buttonbit1 |= dval1; 
      }
      
    if (digitalRead(1) == LOW)
      {
        dval2 = 253; //11111101
        buttonbit1 &= dval2;
      }
    else
      {
        dval2 = 2; //00000010
        buttonbit1 |= dval2;  
      }
      
    if (digitalRead(2) == LOW)
      {
        dval3 = 251; //11111011
        buttonbit1 &= dval3;
      }
    else
      {
        dval3 = 4; //00000100
        buttonbit1 |= dval3;
      }

    if (digitalRead(3) == LOW)
      {
        dval4 = 247; //11110111
        buttonbit1 &= dval4;
      }
    else
      {
        dval4 = 8; //00001000
        buttonbit1 |= dval4;
      }

    if (digitalRead(4) == LOW)
      {
        dval5 = 239; //11101111
        buttonbit1 &= dval5;
      }
    else
      {
        dval5 = 16; //00010000
        buttonbit1 |= dval5;
      }

    if (digitalRead(5) == LOW)
      {
        dval6 = 223; //11011111
        buttonbit1 &= dval6;
      }
    else
      {
        dval6 = 32; //00100000
        buttonbit1 |= dval6;
      }

    if (digitalRead(6) == LOW) 
      {
        dval7 = 191; //10111111
        buttonbit1 &= dval7;
      }
    else
      {
        dval7 = 64; //01000000
        buttonbit1 |= dval7; 
      }

    if (digitalRead(7) == LOW)
      {
        dval8 = 127; //01111111
        buttonbit1 &= dval8;
      }
    else
      {
        dval8 = 128; //10000000
        buttonbit1 |= dval8;
      }


//PACK SECOND BUTTON BIT
    //Eight entries for buttonbit2
    if (digitalRead(8) == LOW)
      {
        dval9 = 254; //11111110
        buttonbit2 &= dval9;
      }
    else
      {
        dval9 = 1;
        buttonbit2 |= dval9; 
      }

    if (digitalRead(9) == LOW)
      {
        dval10 = 253; //11111101
        buttonbit2 &= dval10;
      }
    else
      {
        dval10 = 2; //00000010
        buttonbit2 |= dval10;
      }

    if (digitalRead(digPin0) == LOW) 
      {
        dval11 = 251; //11111011
        buttonbit2 &= dval11;
      }
    else
      {
        dval11 = 4; //00000100
        buttonbit2 |= dval11;
      }

    if (digitalRead(digPin1) == LOW) 
      {
        dval12 = 247; //11110111
        buttonbit2 &= dval12; 
      }
    else
      {
        dval12 = 8; //00001000
        buttonbit2 |= dval12; 
      }

      if (digitalRead(digPin2) == LOW)
      {
        dval13 = 239; //11101111
        buttonbit2 &= dval13;
      }
    else
      {
        dval13 = 16; //00010000
        buttonbit2 |= dval13;
      }

    if (digitalRead(digPin3) == LOW)
      {
        dval14 = 223; //11011111
        buttonbit2 &= dval14;
      }
    else
      {
        dval14 = 32; //00100000
        buttonbit2 |= dval14;
      }
if (digitalRead(digPin4) == LOW) 
      {
        dval15 = 191; //10111111
        buttonbit2 &= dval15;
      }
    else
      {
        dval15 = 64; //01000000
        buttonbit2 |= dval15; 
      }

    if (digitalRead(digPin5) == LOW)
      {
        dval16 = 127; //01111111
        buttonbit2 &= dval16;
      }
    else
      {
        dval16 = 128; //10000000
        buttonbit2 |= dval16;
      }    
}