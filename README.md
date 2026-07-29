# 📡 Sistema Dual LiDAR Unizona (2x VL53L4CD + STM32)

Este proyecto demuestra cómo conectar y utilizar **dos sensores ToF (Time-of-Flight) idénticos VL53L4CD** simultáneamente en un único bus I2C utilizando un microcontrolador **STM32F401RE**. 

El principal reto técnico de este proyecto es que todos los sensores VL53L4CD vienen de fábrica con la misma dirección I2C (`0x52`). Si se conectan en paralelo directamente, el bus colapsa. Aquí resolvemos ese conflicto utilizando los pines **XSHUT** para encender los sensores de forma secuencial y asignarles direcciones independientes mediante software.

## 🛠️ Hardware Utilizado
* Placa de desarrollo **STM32 Nucleo** (ej. STM32F401RETX)
* 2x Sensores LiDAR ToF Unizona **VL53L4CD**
* Cables de conexión Dupont

## 🔌 Esquema de Conexiones
La comunicación I2C y la alimentación se comparten, pero el encendido es independiente:

* **VIN / VCC:** 3.3V (Ambos sensores en paralelo)
* **GND:** GND (Ambos sensores en paralelo)
* **SDA y SCL:** A los pines I2C del STM32 (Ambos sensores en paralelo)
* **XSHUT (Sensor 1):** Conectado a un pin GPIO de salida (ej. PA10 / D2 en la placa Nucleo)
* **XSHUT (Sensor 2):** Conectado a otro pin GPIO de salida (ej. PB5 / D4 en la placa Nucleo)

*Nota: Para estos módulos específicos, es necesario activar las resistencias internas de **Pull-Up** en los pines SDA y SCL desde la configuración del microcontrolador (STM32CubeMX).*

## 🚀 Cómo funciona el cambio de dirección I2C
En el código fuente (archivo `main.c`), el arranque sigue esta secuencia estricta:
1. Se envían 0V a ambos pines XSHUT para mantener los dos sensores apagados.
2. Se enciende solo el **Sensor 1** (XSHUT 1 a 3.3V).
3. Se le envía un comando I2C para cambiar su dirección de `0x52` a una nueva (ej. `0x54`).
4. Se enciende el **Sensor 2** (XSHUT 2 a 3.3V). Al encenderse, mantiene su dirección original por defecto (`0x52`).
5. ¡Listo! El microcontrolador ya puede leer alternativamente ambas distancias sin colisiones.

## 💻 Cómo usar este código
1. Descarga o clona este repositorio y ábrelo con **STM32CubeIDE**.
2. Compila el proyecto (icono del martillo) y cárgalo en tu placa STM32 (icono de *Run/Play* verde).
3. Abre un monitor Serie (como la consola integrada del IDE, PuTTY o TeraTerm) conectándote al puerto COM correspondiente (ej. `/dev/ttyACM0` en Linux) a **115200 baudios**.
4. Verás las mediciones de ambos sensores actualizándose en milímetros en tiempo real.

## ⚠️ Notas sobre la precisión
Debido a tolerancias de fabricación, es normal que haya un error de lectura de algunos milímetros (normalmente en torno a ~1 cm) que suele ser constante. Si necesitas precisión exacta, mide una distancia conocida con una regla y aplica el *offset* correspondiente sumando o restando esos milímetros directamente en la variable del código C antes de imprimir el resultado.
