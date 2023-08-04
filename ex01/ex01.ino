#include <LiquidCrystal.h>

long           	prevSensorValue = -1;
long          	prevIncomingVal = 0;
const int     	ledPin = 9;
LiquidCrystal	lcd(12, 11, 5, 4, 3, 2);

void setup()
{
	lcd.begin(16, 2);
	Serial.begin(9600);
}

void  controlLed(long val, bool serial)
{
	lcd.clear();
	if (val > 1023)
	{
		lcd.print("Incoming: " + String(val));
		lcd.setCursor(0, 1);
		lcd.print("TOO HIGH!");
	}
	else if (val < 0)
	{
		lcd.print("Incoming: " + String(val));
		lcd.setCursor(0, 1);
		lcd.print("SHOULD BE >0!");
	}
	else
	{
		lcd.print("Brightness: " + String(int(val / 10.23)) + "%");
		lcd.setCursor(0, 1);
		if (serial)
			lcd.print("Serial val: " + String(val));
		else
			lcd.print("Sensor val: " + String(val));
		analogWrite(ledPin, val / 4);
	}
}

void loop()
{
	long  incomingVal;
	long  sensorValue;
	int   proc;

	sensorValue = analogRead(A0);
	if (sensorValue - prevSensorValue > 1 || sensorValue - prevSensorValue < -1)
	{
		prevSensorValue = sensorValue;
		controlLed(sensorValue, false);
	}
	else if (Serial.available() > 0)
	{
		incomingVal = Serial.parseInt(SKIP_ALL);
		proc = Serial.read();
		while (Serial.available() > 0)
			Serial.read();
		if ((incomingVal && incomingVal != prevIncomingVal) || proc == '%')
		{
			if (proc == '%')
				incomingVal = incomingVal * 10.23 + 1;
			prevIncomingVal = incomingVal;
			controlLed(incomingVal, true);
		}
	}
	 delay(200);
}
