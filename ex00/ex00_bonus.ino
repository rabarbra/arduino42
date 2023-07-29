const int       buttonPin = 7;
const int       greenLedPin = 13;
const int       redLedPin = 8;
const int       orangeLedPin = 12;

int             buttonCounter = 0;
int             buttonState = LOW;
int             prevButtonState = LOW;

int             redLedState = LOW;
int             greenLedState = LOW;
int             orangeLedState = LOW;

unsigned long   prevTime1 = 0;
unsigned long   prevTime2 = 0;

void setup()
{
    pinMode(greenLedPin, OUTPUT);
    pinMode(redLedPin, OUTPUT);
    pinMode(buttonPin, INPUT);
}

int	checkTime(int delay, unsigned long *prev)
{
    unsigned long	currTime;

    currTime = millis();
    if (currTime - *prev >= delay)
    {
        *prev = currTime;
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
        if (checkTime(500, &prevTime1))
        {
            if (redLedState == LOW)
                redLedState = HIGH;
            else
                redLedState = LOW;
            digitalWrite(redLedPin, redLedState);
        }
         if (checkTime(2000, &prevTime2))
        {
            if (orangeLedState == LOW)
                orangeLedState = HIGH;
            else
                orangeLedState = LOW;
            digitalWrite(orangeLedPin, orangeLedState);
        }
    }
    else
    {
        if (redLedState == HIGH)
        {
            redLedState = LOW;
            digitalWrite(redLedPin, LOW);
        }
		if (orangeLedState == HIGH)
        {
            orangeLedState = LOW;
            digitalWrite(orangeLedPin, LOW);
        }
        if (greenLedState == LOW)
        {
            greenLedState = HIGH;
            digitalWrite(greenLedPin, HIGH);
        }
    }
    prevButtonState = buttonState;
}
