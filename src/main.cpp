#include <Arduino.h>
#include "GY521.h"   



/* ANTES DE COMENZAR: Asegure que en el <<platformio.ini>> seleccione su dipositivo: 
Para las varitas dos modelos son utilizados el ESP32-S3 y el ESP32-C3.

Si su dispositivo es C3:
[env:lolin_c3_mini]
platform = espressif32
board = lolin_c3_mini

Si su dispositivo es S3:
[env:lolin_s3_mini]
platform = espressif32
board = lolin_s3_mini

Ademas cambiar los IO de los botones.
El GY521 esta conectado a los pines I2C defecto de su dispositivo, para mayor informacion de que pines son estos consulte la hoja de datos de su dispositivo.
La direccion default del GY521 es (0x68) y la alterna en caso de que no funcione la default es la (0x69)


*/

GY521 sensor(0x68);
uint32_t counter = 0;

float ax, ay, az;
float gx, gy, gz;
float t;

const int ledPin = 5;     //Nota: Cambiar el PIN del led. Si su dipositivo es ESP-S3: 5, Si es ESP-C3: 7
const int buttonPin = 3;  //Nota: Cambiar el PIN del boton. Si su dipositivo es ESP-S3: 3, Si es ESP-C3: 3
int buttonState = 0;      

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GY521_LIB_VERSION: ");
  Serial.println(GY521_LIB_VERSION);

  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin,LOW); 

  Wire.begin();  
  delay(100);
  if (sensor.wakeup() == false)
  {
    Serial.println("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
  }
  //  adjust when needed.
  sensor.setAccelSensitivity(0);  
  sensor.setGyroSensitivity(0);   
  sensor.setThrottle(false);

  //  set all calibration errors to zero
  sensor.axe = 0;
  sensor.aye = 0;
  sensor.aze = 0;
  sensor.gxe = 0;
  sensor.gye = 0;
  sensor.gze = 0;

  Serial.println("\n\nReading calibration numbers...");
}


void loop()
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);  // Turn off the LED when the button is pressed
  } else {
    digitalWrite(ledPin, LOW); // Keep the LED on when the button is not pressed
  }

  ax = ay = az = 0;
  gx = gy = gz = 0;
  t = 0;
  for (int i = 0; i < 20; i++)
  {
    sensor.read();
    ax -= sensor.getAccelX();
    ay -= sensor.getAccelY();
    az -= sensor.getAccelZ();
    gx -= sensor.getGyroX();
    gy -= sensor.getGyroY();
    gz -= sensor.getGyroZ();
    t += sensor.getTemperature();
  }

  if (counter % 10 == 0)
  {
    Serial.println("\n\tACCELEROMETER\t\tGYROSCOPE\t\tTEMPERATURE");
    Serial.print('\t');
    Serial.print(sensor.axe, 3);
    Serial.print('\t');
    Serial.print(sensor.aye, 3);
    Serial.print('\t');
    Serial.print(sensor.aze, 3);
    Serial.print('\t');
    Serial.print(sensor.gxe, 3);
    Serial.print('\t');
    Serial.print(sensor.gye, 3);
    Serial.print('\t');
    Serial.print(sensor.gze, 3);
    Serial.print('\n');
    Serial.println("\taxe\taye\taze\tgxe\tgye\tgze\tT");
  }

  Serial.print(counter);
  Serial.print('\t');
  Serial.print(ax * 0.05, 3);
  Serial.print('\t');
  Serial.print(ay * 0.05, 3);
  Serial.print('\t');
  Serial.print(az * 0.05, 3);
  Serial.print('\t');
  Serial.print(gx * 0.05, 3);
  Serial.print('\t');
  Serial.print(gy * 0.05, 3);
  Serial.print('\t');
  Serial.print(gz * 0.05, 3);
  Serial.print('\t');
  Serial.print(t * 0.05, 2);
  Serial.println();

  //  adjust calibration errors so table should get all zero's.
  sensor.axe += ax * 0.05;
  sensor.aye += ay * 0.05;
  sensor.aze += az * 0.05;
  sensor.gxe += gx * 0.05;
  sensor.gye += gy * 0.05;
  sensor.gze += gz * 0.05;

  counter++;
  delay(100);
}


//  -- END OF FILE --



