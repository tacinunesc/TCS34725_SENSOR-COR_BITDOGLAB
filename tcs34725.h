#ifndef SENSOR_COR_H
#define SENSOR_COR_H

#include <stdint.h> // Biblioteca para tipos inteiros com tamanho fixo

// Definições da comunicação I2C
#define PORTA_I2C i2c0       // Porta I2C utilizada
#define PINO_SDA 0           // Pino de dados (SDA)
#define PINO_SCL 1           // Pino de clock (SCL)

// Configura a interface I2C
void configurar_i2c();

// Inicializa o sensor de cor
void iniciar_sensor();

// Liga o sensor
void habilitar_sensor();

// Desliga o sensor
void desabilitar_sensor();

// Lê 16 bits de um registrador do sensor
uint16_t tc_read16(uint8_t registrador);

// Detecta a cor com base nos valores de vermelho, verde, azul e claro
const char* detectar_cor(uint16_t vermelho, uint16_t verde, uint16_t azul, uint16_t claro);

#endif

