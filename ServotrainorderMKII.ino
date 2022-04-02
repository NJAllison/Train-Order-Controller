/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nelson.allison@aberdeencarshops.ca> wrote this file.  As long as you retain
 * this notice you can do whatever you want with this stuff. If we meet some day
 * , and you think this stuff is worth it, you can buy me a beer in return.
 * Nelson Allison
 * -----------------------------------------------------------------------------
 */
 
#include <VarSpeedServo.h>

#define ACTIVE 0    // 0 if a detector grounds the input, 1 if it connects it to VCC

VarSpeedServo semaphore[2];

// With neither D2 or D3 grounded, the semaphore shows Green
#define yellowPin1        2        // D2 - ground this pin to get Yellow
#define redPin1           3        // D3 - ground this pin to get Red
#define semaphorePin1     4        // D4 - output for servo
#define yellowPin2        5        // D5 - ground this pin to get Yellow
#define redPin2           6        // D6 - ground this pin to get Red
#define semaphorePin2     7        // D7 - output for servo
#define yelButtonPin1     8        // D9 - output for buttonlight
#define redButtonPin1     9        // D8 - output for buttonlight
#define yelButtonPin2     10       // D11 - output for buttonlight
#define redButtonPin2     11       // D10 - output for buttonlight
#define semaphoreLed      12       // D12 - output for semaphoreled

#define REDPOS1          90     // Change to match your semaphore...
#define YELLOWPOS1       99
#define GREENPOS1       110
#define REDPOS2          90     // Change to match your semaphore...
#define YELLOWPOS2       99
#define GREENPOS2       110


int  BOUNCE = 0;
int semaphoreSpeed = 8;
enum States  { RED, YELLOW, GREEN };
byte currentstate1;
byte newstate1;
byte currentstate2;
byte newstate2;


void setup() {
  pinMode(yellowPin1,    INPUT_PULLUP);
  pinMode(redPin1,       INPUT_PULLUP);
  pinMode(semaphorePin1, OUTPUT);
  pinMode(yellowPin2,    INPUT_PULLUP);
  pinMode(redPin2,       INPUT_PULLUP);
  pinMode(semaphorePin2, OUTPUT);
  pinMode(redButtonPin1, OUTPUT);
  pinMode(yelButtonPin1, OUTPUT);
  pinMode(yelButtonPin2, OUTPUT);
  pinMode(redButtonPin2, OUTPUT);
  pinMode(semaphoreLed,  OUTPUT);
  digitalWrite(semaphoreLed, HIGH);
  semaphore[0].attach(semaphorePin1);
  semaphore[0].write(REDPOS1, semaphoreSpeed, true);
  currentstate1 = RED;
  newstate1     = RED;

  semaphore[1].attach(semaphorePin2);
  semaphore[1].write(REDPOS2, semaphoreSpeed, true);
  currentstate2 = RED;
  newstate2     = RED;
}

void loop() {
  // get state of inputs
  if (digitalRead(redPin1) == ACTIVE) {
    newstate1 = RED;
  } else if (digitalRead(yellowPin1) == ACTIVE) {
    newstate1 = YELLOW;
  } else {
    newstate1 = GREEN;
  }
  // If anything changed, set servo position to match desired position
  if (newstate1 != currentstate1) {
    switch (newstate1) {
      case GREEN:   digitalWrite(redButtonPin1, LOW);
                    digitalWrite(yelButtonPin1, LOW);
                    semaphore[0].write(GREENPOS1, semaphoreSpeed, true);
                    delay(100);
                    BOUNCE = GREENPOS1 - 6;
                    semaphore[0].write(BOUNCE, semaphoreSpeed, true);
                    delay(100);
                    semaphore[0].write(GREENPOS1, semaphoreSpeed, true);
                    break;
      case YELLOW:  digitalWrite(yelButtonPin1, HIGH);
                    semaphore[0].write(YELLOWPOS1, semaphoreSpeed, true);
                    break;
      default:
      case RED:     digitalWrite(redButtonPin1, HIGH);
                    semaphore[0].write(REDPOS1, semaphoreSpeed, true);
                    delay (200);
                    BOUNCE = REDPOS1 + 6;
                    semaphore[0].write(BOUNCE, semaphoreSpeed + 4, true);
                    delay(200);
                    semaphore[0].write(REDPOS1, semaphoreSpeed, true);
                    BOUNCE = REDPOS1 + 3;
                    semaphore[0].write(BOUNCE, semaphoreSpeed + 2, true);
                    delay(300);
                    semaphore[0].write(REDPOS1, semaphoreSpeed, true);
      break;
    }
    currentstate1 = newstate1;
  }
  if (digitalRead(redPin2) == ACTIVE) {
    newstate2 = RED;
  } else if (digitalRead(yellowPin2) == ACTIVE) {
    newstate2 = YELLOW;
  } else {
    newstate2 = GREEN;
  }
  // If anything changed, set servo position to match desired position
  if (newstate2 != currentstate2) {
    switch (newstate2) {
      case GREEN:   digitalWrite(redButtonPin2, LOW);
                    digitalWrite(yelButtonPin2, LOW);
                    semaphore[1].write(GREENPOS2, semaphoreSpeed, true);
                    delay(200);
                    BOUNCE = GREENPOS2 - 6;
                    semaphore[1].write(BOUNCE, semaphoreSpeed, true);
                    delay(200);
                    semaphore[1].write(GREENPOS2, semaphoreSpeed, true); 
                    break;
      case YELLOW:  digitalWrite(yelButtonPin2, HIGH);
                    semaphore[1].write(YELLOWPOS2, semaphoreSpeed, true);
                    break;
      default:
      case RED:     digitalWrite(redButtonPin2, HIGH);
                    semaphore[1].write(REDPOS2, semaphoreSpeed, true);
                    delay(200);
                    BOUNCE = REDPOS2 + 6;
                    semaphore[1].write(BOUNCE, semaphoreSpeed + 4, true);
                    delay(200);
                    semaphore[1].write(REDPOS2, semaphoreSpeed, true);
                    BOUNCE = REDPOS2 + 3;
                    semaphore[1].write(BOUNCE, semaphoreSpeed + 2, true);
                    delay(200);
                    semaphore[1].write(REDPOS2, semaphoreSpeed, true);
      break;
    }
    currentstate2 = newstate2;
  }
}
