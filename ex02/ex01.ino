#include <Servo.h>

Servo		servo1;
int			prevServoAngle = 0;
const int	servo1Pin = 5;
const int	lightMaxVal = 300; // We need to setup it in praxis

void setup()
{
	Serial.begin(9600);
	servo1.attach(servo1Pin);
	servo1.write(prevServoAngle);
}

int	calculateAngle(int a, int b, int c)
{
	Serial.print("Leds: ");
	Serial.print(a);
	Serial.print(" ");
	Serial.print(b);
	Serial.print(" ");
	Serial.println(c);
	if (a > c && b > c)
	{
		return (60 + ((b - a) * 60 / lightMaxVal));
	}
	else if (a > b && c > b)
	{
		return (300 + ((a - c) * 60 / lightMaxVal));
	}
	else if (c > a && b > a)
	{
		return (180 + ((c - b) * 60 / lightMaxVal));
	}
	else if (a > c && b == c)
		return (0);
	else if (b > c && a == c)
		return (120);
	else if (c > a && a == b)
		return (240);
	else
		return (0);
}

void loop()
{
	int light1 = analogRead(A0);
	int light2 = analogRead(A1);
	int light3 = analogRead(A2);
	int servoAngle = calculateAngle(light1, light2, light3);
	if (servoAngle > 180)
		servoAngle = servoAngle - 180;
	Serial.print("Angle: ");
	Serial.println(servoAngle);
	if (servoAngle != prevServoAngle)
	{
		prevServoAngle = servoAngle;
		servo1.write(servoAngle);
	}
	delay(100);
}
