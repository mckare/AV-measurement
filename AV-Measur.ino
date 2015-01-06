int VQ;
int AQ;
int VPINV = A1;
int APINV = A0;
 
void setup()
{
  Serial.begin(9600);
  VQ = determineVQ(VPINV); //Quiscent output voltage with no Load!
  AQ = determineAQ(APINV);
  delay(1000);
}
 
void loop()
{
     
  Serial.print("Current@A0:");Serial.print(readCurrent(APINV),3);Serial.println("A");
  Serial.print("Voltage@A1:");Serial.print(readVoltage(VPINV),3);Serial.println("V");
    delay(1000);
}
 
 
//Voltage Measurment with Voltage Divider R1: 22K R2: 4.7K
int determineVQ(int PINV)
{
  Serial.print("estimating avg. quiscent voltage:");
  long VQ = 0;
  //read  samples to stabilise value
  for (int i=0; i<7500; i++)
{
    VQ += analogRead(PINV);
    delay(1);//depends on sampling (on filter capacitor), can be 1/80000 (80kHz) max.
}
  VQ /= 7500;
  Serial.print(map(VQ, 0, 1023, 0, 7500));Serial.println(" mV");
  return int(VQ);
}
 
float readVoltage(int PINV)
{
  int Voltage = 0;
  int sensitivity = 267.5;
 
  for (int i=0; i<5; i++)
{
    Voltage += analogRead(PINV) - VQ;
    delay(1);
}
  Voltage = map(Voltage/5, 0, 1023, 0, 7500);
    return float(Voltage)/sensitivity;
}
 
//Currnet measurement with ACS712 
 
int determineAQ(int PINA)
{
long AQ = 0;
  //read  samples to stabilise value
  for (int i=0; i<7500; i++)
{
    AQ += analogRead(PINA);
    delay(1);//depends on sampling (on filter capacitor), can be 1/80000 (80kHz) max.
}
  AQ /= 7500;
  Serial.print(map(AQ, 0, 1023, 0, 7500));Serial.println(" mV");
  return int(AQ);
}
 
float readCurrent(int PINA)
{
  int current = 0;
  int sensitivity = 100;
  for (int i=0; i<5; i++)
{
    current += analogRead(PINA) - AQ;
    delay(1);
}
  current = map(current/5, 0, 1023, 0, 7500);
    return float(current)/sensitivity;
}
