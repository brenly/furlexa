/* Furlexa by @BrenlyMakes:
 * 
 *  
 *  documented functions: 
 *  void furbyMotions () --- controls furby motions 
 *  void ledReader () ------ listens for alexa's light that indicates speaking actions 
 *  void ledEyesOn () -------- sets furby eye colors during speaking
 *  void setup () ---------- sets each parameter 
 *  void loop () ----------- main body of code
 *  
 *  documented components:
 *  Arduino Micro
 *  TCS3475 -- watches for alexa led
 *  T50 stepper motor
 *  LED eyes x2
 *  
 *  
*/
/* Pathway / Wishlist:
 *  detecting certain colors on alexa sets certain actions
 *  different stepper motor patterns to create variance in speaking
 */
/* LED reader for Alexa details: 
 *  
 * Leonardo pin SDA = 2 SCL = 3 ground for white LED
 * 
 * Connect SCL    to analog 5
 * Connect SDA    to analog 4
 * Connect VDD    to 3.3V DC
 * Connect GROUND to common ground

 * Initialise with default values (int time = 2.4ms, gain = 1x) 
 * Adafruit_TCS34725 tcs = Adafruit_TCS34725(); 
 */
/* known const alexa values:
  alexa bby blue light Color Temp: 8058 K - Lux: 7 - R: 4 G: 9 B: 7 C: 20  
  alexa royal blue Color Temp: 9963 K - Lux: 6 - R: 4 G: 9 B: 9 C: 22  
  alexa red Color Temp: 4656 K - Lux: 5 - R: 7 G: 8 B: 6 C: 22  
*/

#include <Stepper.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

//stepper motor constants
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // initialize the stepper library on pins 8 through 11

// LED reader constants
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

// LED eye constants
/* will fill */

void furbyMotions () {
  //testing nonense. clean it up when the model is built.
  
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
  
}

bool ledReader () {
  bool talkingDetected = false; //return value
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);
 
/* known const alexa values:
  alexa bby blue light Color Temp: 8058 K - Lux: 7 - R: 4 G: 9 B: 7 C: 20  
  alexa royal blue Color Temp: 9963 K - Lux: 6 - R: 4 G: 9 B: 9 C: 22  
  alexa red Color Temp: 4656 K - Lux: 5 - R: 7 G: 8 B: 6 C: 22  
*/
/* debugging output
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  */
  return talkingDetected;
}

void ledEyesOn () {
  
}

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
  // TCS3475 sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
}

void loop() {
  
  if (ledReader() == true)
  {
    ledEyesOn();
    furbyMotions();
  }
}
