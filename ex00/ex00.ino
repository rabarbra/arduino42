const int buttonPin = 7;
const int greenLedPin = 12;
const int redLedPin = 13;
int buttonState = 0;

void setup() {
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(greenLedPin, HIGH);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(greenLedPin, LOW);
    while(1)
    {
    	digitalWrite(redLedPin, HIGH);
      	delay(1000);
      	digitalWrite(redLedPin, LOW);
        delay(1000);
    }
  }
}

