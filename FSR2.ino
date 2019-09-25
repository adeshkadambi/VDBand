
 float fsr_loop2(void)
{
    
  if (fsrVoltage2 == 0) {
    Serial.println("No pressure (2) ");
    fsrForce2 = 0.00;
  } else {
    // The voltage = Vcc * R / (R + FSR) where R = 1K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance2 = 5000 - fsrVoltage2;     // fsrVoltage is in millivolts so 3.3V = 3300mV
    fsrResistance2 *= 10000;                // 1K resistor
    fsrResistance2 /= fsrVoltage2;
    Serial.print("FSR43 (2) resistance in ohms = ");
    Serial.println(fsrResistance2);

    fsrConductance2 = 1000000;           // we measure in micromhos so
    fsrConductance2 /= fsrResistance2;
    Serial.print("Conductance (2) in microOhm: ");
    Serial.println(fsrConductance);

    // Use the two FSR guide graphs to approximate the force
    if (fsrConductance2 <= 10000) {
      fsrForce2 = fsrConductance2 / 80;
      Serial.print("Force in Newtons on 2: ");

      Serial.println(fsrForce2, 4);
    } else {
      fsrForce2 = fsrConductance2 - 10000;
      fsrForce2 /= 30;
      Serial.print("Force in Newtons in 2: ");
      Serial.println(fsrForce2, 5);
    }

  }
  
  return fsrForce2;

}


