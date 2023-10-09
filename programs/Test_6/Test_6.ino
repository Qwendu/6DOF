#define T_X A1
#define T_Y A0
#define T_Z A2
#define R_X A3
#define R_Y A4
#define R_Z A5


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("tx\tty\ttz");
}

void loop() {
  // put your main code here, to run repeatedly:
  int tx = analogRead(T_X);
  int ty = analogRead(T_Y);
  int tz = analogRead(T_Z);
  int rx = analogRead(R_X);
  int ry = analogRead(R_Y);
  int rz = analogRead(R_Z);
  Serial.print(" tx:");Serial.print(tx);
  Serial.print(" ty:");Serial.print(ty);
  Serial.print(" tz:");Serial.print(tz);
  Serial.print(" rx:");Serial.print(rx);
  Serial.print(" ry:");Serial.print(ry);
  Serial.print(" rz:");Serial.print(rz);
  Serial.println();
}
