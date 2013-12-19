/* Programmer: Ryan Foo
 * Project: Electronics 2 Final
 * Date: 12/14/12
 * Description: A 16 button pad MIDI controller with an acclerometer controlling effects such as
 *              low pass filters, high pass filters, and delays; Controller is controlled by a 
 *              a grid of buttons (with a LED matrix) and can be mapped to any DAW.
 */
 
/* For Development:
 * I have code that uses the acclerometer to control effects but I sadly didn't 
 * finish in time for my final presentation. I am working on completing this in
 * the near future when my schedule permits me.
 */
//extend Keypad class
#include <Keypad.h>

//initialize rows and columns
const byte ROWS = 4; 
const byte COLS = 4; 

//define the symbols on the buttons
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};

//row pinouts
byte rowPins[ROWS] = {5, 4, 3, 2}; 
//column pinouts
byte colPins[COLS] = {9, 8, 7, 6};

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int MIDInotes[16] = {60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79, 81, 83, 84, 86};

//SOME METHODS:
//MIDIiu noteON
void noteOn(int channel, int pitch, int velocity) {
  Serial.write(channel);
  Serial.write(pitch);
  Serial.write(velocity);
  delay(1);
}
  
void setup() {
    
  Serial.begin(31250);
  } 
  
void loop() {
  
  char customKey = customKeypad.getKey();
  
  if (customKey){
 
    char testChar = customKey;
    int someInt;
    if (testChar >= 'A' && testChar <= 'F')
    {
      someInt = 10 + (int)(testChar- 'A');
    }
    else
    {
      someInt = (int)(customKey - '0');
    }

  noteOn(144, MIDInotes[someInt], 127); 
  delay(100); 
 } 
  
 /*
 else if (!customKey) {
   for (int i = 0; i < 15; i++) 
   {
     noteOn(144, MIDInotes[i], 0);
   }
 }
 */
 /*
  //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);

  //convert read values to degrees -90 to 90 - Needed for atan2
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
  
  xMIDI = map(x, 0, 360, 0, 127);
  yMIDI = map(y, 0, 360, 0, 127);
  zMIDI = map(z, 0, 360, 0, 127);
  
  noteOn(176, 17, xMIDI);
  noteOn(176, 19, yMIDI);
  noteOn(176, 24, zMIDI);
  */
}


