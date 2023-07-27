const int       buttonPin = 7;
const int       greenLedPin = 12;
const int       redLedPin = 13;

int             buttonCounter = 0;
int             buttonState = LOW;
int             prevButtonState = LOW;

int             redLedState = LOW;
int             greenLedState = LOW;

unsigned long   prevTime = 0;

void setup()
{
    pinMode(greenLedPin, OUTPUT);
    pinMode(redLedPin, OUTPUT);
    pinMode(buttonPin, INPUT);
}

int	checkTime(int delay)
{
  	unsigned long	currTime;
  
  	currTime = millis();
  	if (currTime - prevTime >= delay)
    {
        prevTime = currTime;
        return (1);
    }
  	return (0);
}

void loop()
{
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH && buttonState != prevButtonState)
        buttonCounter += 1;
    if (buttonCounter % 2 == 1)
    {
        if (greenLedState == HIGH)
        {
        	  greenLedState = LOW;
         	  digitalWrite(greenLedPin, LOW);
        }
        if (checkTime(1000))
        {
          	if (redLedState == LOW)
                redLedState = HIGH;
            else
                redLedState = LOW;
          digitalWrite(redLedPin, redLedState);
        }
    }
    else
    {
        if (redLedState == HIGH)
        {
         	  redLedState = LOW;
        	  digitalWrite(redLedPin, LOW);
        }
        if (greenLedState == LOW)
        {
        	  greenLedState = HIGH;
          	digitalWrite(greenLedPin, HIGH);
        }
    }
    prevButtonState = buttonState;
}
