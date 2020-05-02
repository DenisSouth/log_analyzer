
#include <MsTimer2.h>

volatile unsigned long oldTime = micros ();
volatile unsigned long currentTime = micros ();

const int datalen = 150;
volatile unsigned long data [datalen] = {};
volatile int counter = 0;


// is there anything other than zeros?
boolean isnone (unsigned long thedata [datalen]) {
  noInterrupts (); // disable interrupts
  for (int i = 0; i <datalen; i ++) {
    if (thedata [i]> 0) {
        interrupts (); // enable interrupts
      return true;
    }
  }
    interrupts (); // enable interrupts
  return false;
  
}


void by_timer () {
  noInterrupts (); // disable interrupts
  
  if (isnone (data)) {
    for (int i = 0; i <datalen; i ++) {
      Serial.print (data [i]);
      Serial.print (":");
    }
    Serial.println ();
  }
  memset (data, 0, sizeof (data)); // clear output
  counter = 0; // clear counter
  interrupts (); // enable interrupts
}

void by_interrupt () {
   noInterrupts (); // disable interrupts
  if (counter <datalen) {
    currentTime = micros (); // ms from interrupt
    data [counter] = currentTime - oldTime; // add to the array (old time minus current)
    data [counter + 1] = digitalRead (2);
    counter = counter + 2;
    oldTime = currentTime; // update minus current time
    interrupts (); // enable interrupts
    MsTimer2 :: start (); // if after the last interrupt n seconds have passed, "by_timer ()" will be called
  }
}


void setup () {
  Serial.begin (115200);
  MsTimer2 :: set (1000, by_timer);
  MsTimer2 :: start ();
  pinMode (2, INPUT_PULLUP); // if there is no INPUT_PULLUP , it is necessary to pull pin 2 to the ground by 10k-100k resistor
  attachInterrupt (0, by_interrupt, CHANGE); // CHANGE FALLING //Interrupt 0  is digital pin 2

}

void loop () {
}
