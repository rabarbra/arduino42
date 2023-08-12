#include <Servo.h>

Servo		servo1;
Servo		servo2;
const int	servo1Pin = 5;
const int	servo2Pin = 6;
int			prevServo1Angle = 0;
int			prevServo2Angle = 0;
int			prevLight1 = 0;
int			prevLight2 = 0;
int			prevLight3 = 0;

// Settings:
const int	lightDelta = 5;
const int	angleDelta = 5;
const int	delayBeforeLightMeasure = 50;

void setup()
{
	Serial.begin(9600);
	servo1.attach(servo1Pin);
	servo2.attach(servo2Pin);
	servo1.write(prevServo1Angle);
	servo2.write(prevServo2Angle);
}

void	rotateHor(int a, int b)
{
	int currAngle = servo1.read();
	int	finalAngle = currAngle + 180;
	int minLightVal = min(a, b);
	int	lightIsRising = 0;
	while (currAngle <= finalAngle)
	{
		currAngle += angleDelta * 2;
		servo1.write(currAngle % 180);
		delay(delayBeforeLightMeasure);
		int currLight = min(analogRead(A0), analogRead(A1));
		if (currLight < minLightVal)
		{
			minLightVal = currLight;
			lightIsRising = 1;
		}
		else if(lightIsRising)
		{
			currAngle -= angleDelta;
			servo1.write(currAngle % 180);
			delay(delayBeforeLightMeasure);
			int currLight = min(analogRead(A0), analogRead(A1));
			if (currLight <= minLightVal)
				return ;
			else
			{
				currAngle -= angleDelta;
				servo1.write(currAngle % 180);
				return ;
			}
		}
	}
}

void	rotateVert(int c)
{
	int currAngle = servo2.read();
}

void loop()
{
	int light1 = analogRead(A0);
	int light2 = analogRead(A1);
	int light3 = analogRead(A2);
	if (
		abs(light1, prevLight1) > lightDelta
		|| abs(light2, prevLight2) > lightDelta
		|| abs(light3, prevLight3) > lightDelta
	)
	{
		rotateHor(light1, light2);
		rotateVert(light3);
		prevLight1 = light1;
		prevLight2 = light2;
		prevLight3 = light3;
	}
	delay(100);
}
