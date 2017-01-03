#include <Arduino.h>

const int RLED = 9;
const int GLED = 11;
const int BLED = 10;

const int RBUTTON = 2;
const int GBUTTON = 4;
const int BBUTTON = 6;

const int LIGHT = 0;

const int DELAY = 10;
const int LIGHT_REPORT_PERIOD = 1000;

int rval = 120;
int gval = 0;
int bval = 250;

bool rbutton_released = true;
bool gbutton_released = true;
bool bbutton_released = true;

int silent_time = 0;

void setup()
{
	pinMode(RLED, OUTPUT);
	pinMode(GLED, OUTPUT);
	pinMode(BLED, OUTPUT);

	pinMode(RBUTTON, INPUT);
	pinMode(GBUTTON, INPUT);
	pinMode(BBUTTON, INPUT);

	Serial.begin(9600);
}

void loop()
{
	if(digitalRead(RBUTTON) == HIGH)
	{
		if(rbutton_released)
		{
			rbutton_released = false;
			rval += 10;
			if(rval > 255)
				rval = 0;
			Serial.println("rval = " + String(rval));
		}
	} else
		rbutton_released = true;

	if(digitalRead(GBUTTON) == HIGH)
	{
		if(gbutton_released)
		{
			gbutton_released = false;
			gval += 10;
			if(gval > 255)
				gval = 0;
			Serial.println("gval = " + String(gval));
		}
	} else
		gbutton_released = true;	

	if(digitalRead(BBUTTON) == HIGH)
	{
		if(bbutton_released)
		{
			bbutton_released = false;
			bval += 10;
			if(bval > 255)
				bval = 0;
			Serial.println("bval = " + String(bval));
		}
	} else
		bbutton_released = true;

	analogWrite(RLED, rval);
	analogWrite(GLED, gval);
	analogWrite(BLED, bval);

	delay(DELAY);
	silent_time += DELAY;
	if(silent_time >= LIGHT_REPORT_PERIOD)
	{
		int light_val = analogRead(LIGHT);
		Serial.println("light_val = " + String(light_val));
		silent_time = 0;
	}
}
