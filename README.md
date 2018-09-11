# DM0BD2

OBJETIVO

Desarrollar un dispositivo que capture y entregue de una forma interpretable al FM la mayor cantidad de información posible de automóviles que implementen el estándar OBD2 sin importar si se basa en CAN, Kline o KWP; Haciendo énfasis en buscar la velocidad, las RPM y los códigos de falla.
Se utiliza el OBD-II a UART de Freematics que se conecta a un Arduino por los puertos seriales. La información de la velocidad, RPM y Consumo se entregan con señales de frecuencia. Las variables analogicas como temperatura, se entrega por una salida analogica.
Los codigos de falla se deben entregar por un protocolo serial.

Para los códigos de falla no se sabe si se puede cambiar en ejecución los pines de la comunicación serial para que se comunique con el FM, o si de alguna forma se puede usar el protocolo I2C o SPI como uart.
