
void output()
{
  
    for(int i = 0; i < 10; i++)
    {

        /**
         * The pos and neg pins control the direction of the current 
         * and hence the voltage levels. Depending on the dicrection of
         * the current, the output voltagge may be either positive or negative.
         * This will generate the square wave output. The del variable sets the frequency at
         * which the signal will be sent. Since there is a del integer 
         * agter each output, there is a 50% duty cycle. 
        **/

        digitalWrite(pos, LOW);
        digitalWrite(neg, HIGH);
        delay(del);

        digitalWrite(pos, HIGH);
        digitalWrite(neg, LOW);
        delay(del);
        
    }

     digitalWrite(pos, LOW);
     digitalWrite(neg, LOW);
}
