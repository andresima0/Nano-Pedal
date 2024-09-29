/* THE NANO PEDAL 
   Arduino Nano Guitar Pedal with 6 Presets, 8 Digital Outputs
   3 Buttons:
     - Select preset;
     - Navigation between OUTPUT 1, 2, 3, and 4;
     - Navigation between OUTPUT 5, 6, 7, and 8.
   The output states are saved automatically in each preset
   Erase all presets when Switch Preset is holdin by 2 seconds
*/

#include <EEPROM.h>

#define OUTPUT1 2
#define OUTPUT2 3
#define OUTPUT3 4
#define OUTPUT4 5

#define OUTPUT5 6
#define OUTPUT6 7
#define OUTPUT7 8
#define OUTPUT8 9

#define NAV_BUTTON1 10
#define NAV_BUTTON2 11
#define PRESET_BUTTON 12

const int presetPins[] = { 13, A0, A1 };  // Use digital pins 13, A0, and A1 for presets
int outputPinsGroup1[] = { OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4 };
int outputPinsGroup2[] = { OUTPUT5, OUTPUT6, OUTPUT7, OUTPUT8 };
int currentPreset = 1;   // Start from 1 to skip the 0 state
int presetStates[6][2];  // Array to store output configurations for each preset
int lastNavButton1State = HIGH;
int lastNavButton2State = HIGH;
int lastPresetButtonState = HIGH;
unsigned long lastPresetButtonPressTime = 0;
unsigned long debounceDelay = 50;
unsigned long longPressDuration = 2000;  // 2 seconds

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(outputPinsGroup1[i], OUTPUT);
    pinMode(outputPinsGroup2[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(presetPins[i], OUTPUT);
  }

  pinMode(NAV_BUTTON1, INPUT_PULLUP);
  pinMode(NAV_BUTTON2, INPUT_PULLUP);
  pinMode(PRESET_BUTTON, INPUT_PULLUP);

  // Load saved configurations from EEPROM for each preset
  loadFromEEPROM();

  currentPreset = EEPROM.read(12);
  if (currentPreset == 0 || currentPreset > 6) currentPreset = 1;  // Avoid preset 0 and invalid values
  applyPreset(currentPreset);
}

void loop() {
  int navButton1State = digitalRead(NAV_BUTTON1);
  int navButton2State = digitalRead(NAV_BUTTON2);
  int presetButtonState = digitalRead(PRESET_BUTTON);

  if (navButton1State == LOW && lastNavButton1State == HIGH) {
    changeOutputGroup1();
  }

  if (navButton2State == LOW && lastNavButton2State == HIGH) {
    changeOutputGroup2();
  }

  if (presetButtonState == LOW && lastPresetButtonState == HIGH) {
    lastPresetButtonPressTime = millis();  // Record the time the button was pressed
  }

  if (presetButtonState == LOW && (millis() - lastPresetButtonPressTime > longPressDuration)) {
    clearEEPROM();
    currentPreset = 1;
    applyPreset(currentPreset);
  } else if (presetButtonState == HIGH && lastPresetButtonState == LOW) {
    if (millis() - lastPresetButtonPressTime < longPressDuration) {
      currentPreset = (currentPreset % 6) + 1;  // Cycle through 1 to 6
      applyPreset(currentPreset);
      saveToEEPROM();
      EEPROM.write(12, currentPreset);
    }
  }

  lastNavButton1State = navButton1State;
  lastNavButton2State = navButton2State;
  lastPresetButtonState = presetButtonState;

  delay(50);
}

void changeOutputGroup1() {
  presetStates[currentPreset - 1][0] = (presetStates[currentPreset - 1][0] + 1) % 4;
  updateOutputs();
}

void changeOutputGroup2() {
  presetStates[currentPreset - 1][1] = (presetStates[currentPreset - 1][1] + 1) % 4;
  updateOutputs();
}

void applyPreset(int preset) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(outputPinsGroup1[i], i == presetStates[preset - 1][0] ? HIGH : LOW);
    digitalWrite(outputPinsGroup2[i], i == presetStates[preset - 1][1] ? HIGH : LOW);
  }
  updatePresets();
}

void updateOutputs() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(outputPinsGroup1[i], i == presetStates[currentPreset - 1][0] ? HIGH : LOW);
    digitalWrite(outputPinsGroup2[i], i == presetStates[currentPreset - 1][1] ? HIGH : LOW);
  }
}

void updatePresets() {
  digitalWrite(presetPins[0], bitRead(currentPreset, 0) ? HIGH : LOW);  // Output 25
  digitalWrite(presetPins[1], bitRead(currentPreset, 1) ? HIGH : LOW);  // Output 26
  digitalWrite(presetPins[2], bitRead(currentPreset, 2) ? HIGH : LOW);  // Output 27
}

void saveToEEPROM() {
  for (int i = 0; i < 6; i++) {
    EEPROM.write(i * 2, presetStates[i][0]);
    EEPROM.write(i * 2 + 1, presetStates[i][1]);
  }
  EEPROM.write(12, currentPreset);
}

void loadFromEEPROM() {
  for (int i = 0; i < 6; i++) {
    presetStates[i][0] = EEPROM.read(i * 2);
    presetStates[i][1] = EEPROM.read(i * 2 + 1);
  }
  currentPreset = EEPROM.read(12);
}

void clearEEPROM() {
  for (int i = 0; i < 13; i++) {
    EEPROM.write(i, 0);
  }
  for (int i = 0; i < 6; i++) {
    presetStates[i][0] = 0;
    presetStates[i][1] = 0;
  }
  currentPreset = 1;
  applyPreset(currentPreset);
  saveToEEPROM();
}
