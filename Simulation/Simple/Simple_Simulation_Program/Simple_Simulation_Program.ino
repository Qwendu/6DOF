#define T_X_PIN A0
#define T_Y_PIN A1
#define T_Z_PIN A2
#define R_X_PIN A3
#define R_Y_PIN A4



void setup()
{
	pinMode(T_X_PIN, INPUT);
	pinMode(T_Y_PIN, INPUT);
	pinMode(T_Z_PIN, INPUT);
	pinMode(R_X_PIN, INPUT);
	pinMode(R_Y_PIN, INPUT);

	Serial.begin(9600);
}

void loop()
{
	int tx = analogRead(T_X_PIN);
	int ty = analogRead(T_Y_PIN);
	int tz = analogRead(T_Z_PIN);
	Serial.print(tx);
	Serial.print(",");
	Serial.print(ty);
	Serial.print(",");
	Serial.print(tz);
	Serial.println("");
	delay(500);
}
