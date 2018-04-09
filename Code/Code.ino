/*
by Ody
12-2015

Edited by Caleb
04-2017
*/
int colpin1 = 7;
int colpin2 = 8;
int colpin3 = 9;
int colpin4 = 10;
int colpin5 = 11;
int colpin6 = 12;
int colpin7 = 13;

int rowpin1 = 6;
int rowpin2 = A2;
int rowpin3 = A3;
int rowpin4 = A4;
int rowpin5 = A5;

int strobe = 4; // strobe pins on digital 4
int res = 5; // reset pins on digital 5
long left[7]; // store band values in this array
long low[7]; // store the min values read here
int store;
int band;

// this runs once, to initalize
void setup()
{
	Serial.begin(115200);
	pinMode(res, OUTPUT); // reset
	pinMode(strobe, OUTPUT); // strobe
  delay(4);

  // read the initial values
  for (band = 0; band < 7; band++)
  {
    digitalWrite(strobe, LOW); // strobe pin on the shield - kicks the IC up to the next band 
    delayMicroseconds(30); // 
    low[band] = analogRead(0); // store left band reading
    digitalWrite(strobe, HIGH);
  }

  // use if you want to see what your min values are
//  for (band = 0; band < 7; band++) 
//  {
//    Serial.print(low[band]);
//    Serial.print(" ");
//  }
//  Serial.println(" - low ");

  
  readMSGEQ7();

  // initalize the pins
	pinMode(colpin1, OUTPUT);
	pinMode(colpin2, OUTPUT);
	pinMode(colpin3, OUTPUT);
	pinMode(colpin4, OUTPUT);
	pinMode(colpin5, OUTPUT);
	pinMode(colpin6, OUTPUT);
	pinMode(colpin7, OUTPUT);

	pinMode(rowpin1, OUTPUT);
	pinMode(rowpin2, OUTPUT);
	pinMode(rowpin3, OUTPUT);
	pinMode(rowpin4, OUTPUT);
	pinMode(rowpin5, OUTPUT);

	digitalWrite(res, LOW); // reset low
	digitalWrite(strobe, HIGH); //pin 5 is RESET on the shield
}

// this runs continually. The shorter it is, the quicker the code loops
void loop()
{
	readMSGEQ7();

	/*// to display values of left channel on serial monitor
	for (band = 0; band < 7; band++)
	{
		Serial.print(left[band]);
		Serial.print(" ");
	}
	Serial.println(" - Left ");
 */

	spec(colpin1, left[0], 0);
	spec(colpin2, left[1], 1);
	spec(colpin3, left[2], 2);
	spec(colpin4, left[3], 3);
	spec(colpin5, left[4], 4);
	spec(colpin6, left[5], 5);
	spec(colpin7, left[6], 6);
}

void readMSGEQ7()
// Function to read 7 band equalizers
{
	digitalWrite(res, HIGH);
	digitalWrite(res, LOW);
	for (band = 0; band < 7; band++)
	{
		digitalWrite(strobe, LOW); // strobe pin on the shield - kicks the IC up to the next band 
		delayMicroseconds(30); // 
		left[band] = analogRead(0); // store left band reading
    // NOTE: just needs left or right for reference. So we just track one.
		digitalWrite(strobe, HIGH);
	}
}

// function that lights a column depending on height
void spec(int col, int height, int band)
{
	digitalWrite(col, LOW);

	//for height
  // if you want your LED's to be more or less sensitive, this is what you adjust.
	if (height > (low[band] + 5))
	{
		digitalWrite(rowpin1, HIGH);
	}

	if (height > (low[band] + 10)) 
	{
		digitalWrite(rowpin2, HIGH);
	}

	if (height > (low[band] + 15))
	{
		digitalWrite(rowpin3, HIGH);
	}

	if (height > (low[band] + 50))
	{
		digitalWrite(rowpin4, HIGH);
	}

	if (height > (low[band] + 100))
	{
		digitalWrite(rowpin5, HIGH);
	}

  //default back to off
	delay(2);
  digitalWrite(colpin1, HIGH);
  digitalWrite(colpin2, HIGH);
  digitalWrite(colpin3, HIGH);
  digitalWrite(colpin4, HIGH);
  digitalWrite(colpin5, HIGH);
  digitalWrite(colpin6, HIGH);
  digitalWrite(colpin7, HIGH);

  digitalWrite(rowpin1, LOW);
  digitalWrite(rowpin2, LOW);
  digitalWrite(rowpin3, LOW);
  digitalWrite(rowpin4, LOW);
  digitalWrite(rowpin5, LOW);
}
