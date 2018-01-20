// ▒█░▒█ ▒█▀▀▀█ ▒█▀▀█ ░░ ▒█▀▀█ ▒█▀▀▀█ ▒█░░▒█ ▒█▀▀▀ ▒█▀▀█ ░░ ▒█▀▀█ ▒█░░▒█ ▒█▀▀█ ▒█░░░ ▒█▀▀▀ ▒█▀▀█ 
// ▒█░▒█ ░▀▀▀▄▄ ▒█▀▀▄ ▀▀ ▒█▄▄█ ▒█░░▒█ ▒█▒█▒█ ▒█▀▀▀ ▒█▄▄▀ ▀▀ ▒█░░░ ▒█▄▄▄█ ▒█░░░ ▒█░░░ ▒█▀▀▀ ▒█▄▄▀ 
// ░▀▄▄▀ ▒█▄▄▄█ ▒█▄▄█ ░░ ▒█░░░ ▒█▄▄▄█ ▒█▄▀▄█ ▒█▄▄▄ ▒█░▒█ ░░ ▒█▄▄█ ░░▒█░░ ▒█▄▄█ ▒█▄▄█ ▒█▄▄▄ ▒█░▒█ 
/* --------------------------------------------------------------------------------------------------------------------------------------------
 *  Project: USB Power Cycler
 *  Author: Fahd Shiwani
 *  Version: Rev. A
 *  Target Microncontroller: ATMega328P-PU
 * --------------------------------------------------------------------------------------------------------------------------------------------
 */

// Pin Declarations
#define ACTIVITY_LED_PIN 8 // PB0
#define ENABLE_PIN 9 // PB1
#define SW_PIN_1 0 // PD0
#define SW_PIN_2 1 // PD1
#define SW_PIN_3 2 // PD2
#define SW_PIN_4 3 // PD3
#define SW_PIN_5 4 // PD4
#define SW_PIN_6 5 // PD5
#define SW_PIN_7 6 // PD6
#define SW_PIN_8 7 // PD7

unsigned int SW_STATE[8]; // DIP switch state

// function to read digital pins for DIP switch.
void readSWState(int SW_STATE[]){
  SW_STATE[0] = !digitalRead(SW_PIN_1); // MSB
  SW_STATE[1] = !digitalRead(SW_PIN_2);
  SW_STATE[2] = !digitalRead(SW_PIN_3);
  SW_STATE[3] = !digitalRead(SW_PIN_4);
  SW_STATE[4] = !digitalRead(SW_PIN_5);
  SW_STATE[5] = !digitalRead(SW_PIN_6);
  SW_STATE[6] = !digitalRead(SW_PIN_7);
  SW_STATE[7] = !digitalRead(SW_PIN_8); // LSB
}

// function to convert from binary switch state values to integer delay.
int convertSW(int SW_STATE[]){
  unsigned int delay = 0;
  
  for(int i=0; i<8; i++){
    delay = (delay << 1) + SW_STATE[i];
  }
  Serial.print("Requested Delay: ");
  Serial.print(delay);
  Serial.print(" seconds");
  return delay;
}

void setup() {
  Serial.begin(9600);
  
  // Intializing Pins
  pinMode(ACTIVITY_LED_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(SW_PIN_1, INPUT_PULLUP); // enabling internal pull-ups.
  pinMode(SW_PIN_2, INPUT_PULLUP);
  pinMode(SW_PIN_3, INPUT_PULLUP);
  pinMode(SW_PIN_4, INPUT_PULLUP);
  pinMode(SW_PIN_5, INPUT_PULLUP);
  pinMode(SW_PIN_6, INPUT_PULLUP);
  pinMode(SW_PIN_7, INPUT_PULLUP);
  pinMode(SW_PIN_8, INPUT_PULLUP);

  readSWState(SW_STATE);
  digitalWrite(ACTIVITY_LED_PIN, HIGH);
  digitalWrite(ENABLE_PIN, HIGH); // active-low enable.
  delay(convertSW(SW_STATE)*1000L); // converted to milliseconds
  digitalWrite(ENABLE_PIN, LOW); 
  digitalWrite(ACTIVITY_LED_PIN, LOW);
}

void loop() {

}
