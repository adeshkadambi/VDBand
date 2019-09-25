

float thermo_loop(void) 
{
 
  reading = analogRead(THERMISTORPIN);   //Read in the analog value for first thermistor 
 
  Serial.print("Analog reading "); 
  Serial.println(reading);
 
  // convert the value to resistance
  reading = (1023 / reading)  - 1;     // (1023/ADC - 1) 
  reading = SERIESRESISTOR / reading;  // 10K / (1023/ADC - 1)
  Serial.print("Thermistor resistance  "); 
  Serial.println(reading);
 
  delay(200);
  return reading;
}
