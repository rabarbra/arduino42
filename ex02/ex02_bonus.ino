#include <Servo.h>

Servo		servo1;
Servo		servo2;

const int	servo1Pin = 5;
const int	servo2Pin = 6;
const int	buttonPin = 7;

int			initServo1Angle = 0;
int			initServo2Angle = 0;

int			buttonCounter = 0;
int			prevButtonState = 0;

// Settings:
const int	angleDelta = 2;
const int	delayBeforeLightMeasure = 40;

void setup()
{
	Serial.begin(9600);
	pinMode(buttonPin, INPUT);
	servo1.attach(servo1Pin);
	servo2.attach(servo2Pin);
	servo1.write(initServo1Angle);
	servo2.write(initServo2Angle);
}

void	rotateHor()
{
	int currAngle = 0;
	int minAngle = 180;
	int minLightVal = 2000;
	int currLight = 2000;
	while (currAngle <= 180)
	{
		servo1.write(currAngle);
		delay(delayBeforeLightMeasure);
		currLight = min(analogRead(A0), analogRead(A1));
		if (currLight < minLightVal)
		{
			minLightVal = currLight;
			minAngle = currAngle;
			Serial.println("MIN light: " + String(currLight) + " angle: " + String(currAngle));
		}
		// Serial.println("Curr light: " + String(currLight));
		currAngle += angleDelta;
	}
	Serial.println("MIN FOUND with light: " + String(currLight) + " angle: " + String(minAngle));
	servo1.write(minAngle);  
}

void	rotateVert()
{
	int currAngle = 0;
	int minAngle = 180;
	int minLightVal = 2000;
	int currLight = 2000;
	while (currAngle <= 180)
	{
		servo2.write(currAngle);
		delay(delayBeforeLightMeasure);
		currLight = analogRead(A2);
		if (currLight < minLightVal)
		{
			minLightVal = currLight;
			minAngle = currAngle;
			Serial.println("MIN light: " + String(currLight) + " angle: " + String(currAngle));
		}
		// Serial.println("Curr light: " + String(currLight));
		currAngle += angleDelta;
	}
	Serial.println("MIN FOUND with light: " + String(currLight) + " angle: " + String(minAngle));
	servo2.write(minAngle);  
}

void	printLightValues()
{
	int light1 = analogRead(A0);
	int light2 = analogRead(A1);
	int light3 = analogRead(A2);
	Serial.print(light1);
	Serial.print(" ");
	Serial.print(light2);
	Serial.print(" ");
	Serial.println(light3);
}

void	printLightDirection()
{
	int	l1 = analogRead(A0);
	int	l2 = analogRead(A1);
	int	angleHor = servo1.read();
	int	angleVert = servo2.read();
	if (l2 < l1)
		angleHor += 180;
	Serial.println("Direction hor: " + String(angleHor) + "°, vert: " + String(angleVert) + "°");
}

void	loop()
{
	int buttonState = digitalRead(buttonPin);
	if (buttonState == HIGH && buttonState != prevButtonState)
		buttonCounter += 1;
	//printLightValues();
	if (buttonCounter % 2 == 1)
	{
		rotateHor();
		Serial.println("Light source found");
		delay(100);
		rotateVert();
		buttonCounter++;
		printLightDirection();
	}
	prevButtonState = buttonState;
	delay(100);
}
