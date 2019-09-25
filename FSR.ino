 /* FSR testing sketch.

Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 1K resistor from Analog 0 to ground

For more information see www.ladyada.net/learn/sensors/fsr.html */
#include <math.h>

int fsrPin = 9;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to volta
float fsrResistance;  // The voltage converted to resistance, can be very big so make "long"
float fsrConductance;
float fsrForce;       // Finally, the resistance converted to force

int fsrPin2 = 10;     // the FSR and 10K pulldown are connected to a0
int fsrReading2;     // the analog reading from the FSR resistor divider
int fsrVoltage2;     // the analog reading converted to volta
float fsrResistance2;  // The voltage converted to resistance, can be very big so make "long"
float fsrConductance2;
float fsrForce2;
float reading;
float reading2;

int pos = 0;
int neg = 1;
int del = 100; // Period of the is equal to 2*del. The frequency is the inverse 
               // this product.

float fsr_get2 = 0.00;
float therm_get1 = 0.00;
float therm_get2 = 0.00;

float resist_1 = 0.00;
float resist_2 = 0.00;

float diff_thermo = 0.00;
float diff_fsr = 0.00;

// the value of the 'other' resistor
#define SERIESRESISTOR 10000

// What pin to connect the sensor to
int THERMISTORPIN = 7;
int thermo_pin2 11;




//thermo_loop();

void setup(void) 
{
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(pos, OUTPUT); // Feeds to the positive input for the H-Bridge
  pinMode(neg, OUTPUT);  //Feeds to the negative input of the H-Bridge
}

void loop(void) 
{
  fsrReading = analogRead(fsrPin);     /*Read in the changing voltage at forse senssor pin.
                                       The bits will be from a range of 0 - 1023. */
  Serial.print("Analog reading 1 = ");
  Serial.println(fsrReading);

  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 3300mV)

  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
  Serial.print("Voltage reading in mV = ");
  Serial.println(fsrVoltage);
  /* Map the reading between a range of 0 - 1-1023.
     The voltage will be read into in mV. */

  fsrReading2 = analogRead(fsrPin2); /*Read in the changing voltage at forse senssor pin.
                                       The bits will be from a range of 0 - 1023. */
  Serial.print("Analog reading 2 = ");
  Serial.println(fsrReading2);

  fsrVoltage2 = map(fsrReading2, 0, 1023, 0, 5000);
  Serial.print("Voltage reading in mV = ");
  Serial.println(fsrVoltage2);
  /* Map the reading between a range of 0 - 1-1023.
     The voltage will be read into in mV. */

  if (fsrVoltage == 0) 
  {
    Serial.println("No pressure");
    fsrForce = 0.00;
  } 
  else 
  {
    // The voltage = Vcc * R / (R + FSR) where R = 1K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 3.3V = 3300mV
    fsrResistance *= 10000;                // 1K resistor
    fsrResistance /= fsrVoltage;
    Serial.print("FSR43 resistance in ohms = ");
    Serial.println(fsrResistance);

    fsrConductance = 1000000;           // we measure in micromhos so
    fsrConductance /= fsrResistance;
    Serial.print("Conductance in microOhm: ");
    Serial.println(fsrConductance);

    // Use the two FSR guide graphs to approximate the force
    if (fsrConductance <= 10000) 
    {
      fsrForce = fsrConductance / 80;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce, 4);
    } 
    else 
    {
      fsrForce = fsrConductance - 10000;
      fsrForce /= 30;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce, 5);
    }

  }

  /*Assign values returned from each function to the varaibles 
    for the force sensros and the temperature sensors.*/

  fsr_get2 = fsr_loop2();      
  
  therm_get1 = thermo_loop();

  therm_get2 = thermo_loop2();
  
  /*Following equations are to convert the readings from the temperature 
    sensor to the actual */
  
  resist_1 = (log10(therm_get1) - 4.4646)/-0.01861;

  resist_2 = (log10(therm_get2) - 4.4646)/-0.01861;

  diff_thermo = abs(resist_1 - resist_2);

  

  diff_fsr = abs(fsr_get2 - fsrForce);

  
  

  Serial.println("Difference in temperature ");
  Serial.println(diff_thermo);

/***
 The following code checks the threshold to determine whether the parameters 
 for varicose veins are reached. If the threshold is reached for both the temperature 
 and the pressure, the screen willl state that varicose veins are present. and the output() function will be 
 initiated. The function triggers the activation of the muscle stimulating electrodes. If the 
 thresholds are not reached, then the screen will state that varicose veins are not present.
****/
  if ((diff_fsr > 1.077) && (diff_thermo > 0.500))
  {
    Serial.println("Varicose Veins are present ");
    Serial.println("Difference in Force: ");
    Serial.println(diff_fsr);
    
    Serial.println("Difference in temperature: ");
    Serial.println(diff_thermo);
    
    output();

  }
  else
  {
    Serial.println();
     Serial.println("Varicose Veins not occuring ");
    Serial.println("Difference in Force: ");
    Serial.println(diff_fsr);

    Serial.println("Difference in temperature: ");
    Serial.println(diff_thermo);

    
  }
  
  Serial.println("--------------------");
  delay(1000);
}
