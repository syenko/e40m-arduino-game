#include "board.hh"

/* LED array display code
 */

// Arrays of pin numbers. Fill these in with the pins to which you connected
// your anode (+) wires and cathode (-) wires.
const byte ANODE_PINS[8] = {13, 12, 11, 10, 9, 8, 7, 6 };
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2 };

#define NUM_PINS 8
#define FLASH_SPEED 200
#define REFRESH_DELAY 50

Board board = Board();

// Configures hardware IO and serial before the game starts.
void setup() {
  for (byte i = 0; i < NUM_PINS; i++) {
    // configure pins to be outputs
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);

    // turn all pins off
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);
  }

  // Initialize serial communication
  // (to be read by Serial Monitor on your computer)
  Serial.begin(115200);
  Serial.setTimeout(100);
}

/* Function: display
 * -----------------
 * Runs through one multiplexing cycle of the LEDs, controlling which LEDs are
 * on.
 *
 * During this function, LEDs that should be on will be turned on momentarily,
 * one row at a time. When this function returns, all the LEDs will be off
 * again, so it needs to be called continuously for LEDs to be on.
 */
void display(char** pattern, int big_cycle) {
  for (byte row = 0; row < NUM_PINS; row++) {
    for (byte col = 0; col < NUM_PINS; col++) {
      if (pattern[row][col] > 0) {
        digitalWrite(CATHODE_PINS[col], LOW);
      }
      // turn off
      else {
        digitalWrite(CATHODE_PINS[col], HIGH);
      }

      if (pattern[row][col] == WIN_VAL) {
        if (big_cycle < FLASH_SPEED / 2) {
          digitalWrite(CATHODE_PINS[col], LOW);
        }
        else {
          digitalWrite(CATHODE_PINS[col], HIGH);
        }
      }
    }
    // flash line
    digitalWrite(ANODE_PINS[row], LOW);
    delayMicroseconds(REFRESH_DELAY);
    digitalWrite(ANODE_PINS[row], HIGH);
  }
}

// Runs the main game loop: update state, refresh display, and multiplex LEDs.
void loop() {
  // use 'static' so that it retains its value between successive calls of loop()
  static byte ledOn[NUM_PINS][NUM_PINS];
  static byte cycle = 0;
  static int big_cycle = 0;

  // This function gets called every loop
  board.updateDisplay();
  board.updateBoardState();
  display(board.getDisplay(), big_cycle);
  big_cycle = (big_cycle + 1) % FLASH_SPEED;
}
