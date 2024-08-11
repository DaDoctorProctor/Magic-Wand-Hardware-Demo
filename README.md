ANTES DE COMENZAR: Asegure que en el <<platformio.ini>> seleccione su dipositivo: 
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
