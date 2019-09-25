

float  thermo_loop2(void) 
{
 
  reading2 = analogRead(thermo_pin2);  //Read the analog value of the second thermistor
 
  Serial.print("Analog reading (2) "); 
  Serial.println(reading2);
 
  // convert the value to resistance
  reading2 = (1023 / reading2)  - 1;     // (1023/ADC - 1) 
  reading2 = SERIESRESISTOR / reading2;  // 10K / (1023/ADC - 1)
  Serial.print("Thermistor resistance (2)"); 
  Serial.println(reading2);

  delay(200);
  return reading2;
}
