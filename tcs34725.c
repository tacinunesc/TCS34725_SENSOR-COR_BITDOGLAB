#include "tcs34725.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdlib.h>

// Endereço I2C do sensor
#define ENDERECO_TCS34725 0x29
#define BIT_COMANDO 0x80

// Registradores do sensor
#define HABILITAR_REG   0x00
#define TEMPO_REG       0x01
#define CONTROLE_REG    0x0F

#define REG_CLARO 0x14
#define REG_VERMELHO 0x16
#define REG_VERDE 0x18
#define REG_AZUL 0x1A

// Configura a comunicação I2C
void configurar_i2c() {
    i2c_init(PORTA_I2C, 100 * 1000);
    gpio_set_function(PINO_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PINO_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PINO_SDA);
    gpio_pull_up(PINO_SCL);
}

// Escreve um valor de 8 bits em um registrador
void write(uint8_t registrador, uint8_t valor) {
    uint8_t buffer[2] = { BIT_COMANDO | registrador, valor };
    i2c_write_blocking(PORTA_I2C, ENDERECO_TCS34725, buffer, 2, false);
}

// Lê um valor de 16 bits de um registrador
uint16_t tc_read16(uint8_t registrador) {
    uint8_t buffer[2];
    uint8_t comando = BIT_COMANDO | registrador;
    i2c_write_blocking(PORTA_I2C, ENDERECO_TCS34725, &comando, 1, true);
    i2c_read_blocking(PORTA_I2C, ENDERECO_TCS34725, buffer, 2, false);
    return (buffer[1] << 8) | buffer[0];
}

// Inicializa o sensor
void iniciar_sensor() {
    write(HABILITAR_REG, 0x00);
    write(TEMPO_REG, 0xEB);       // Tempo de integração
    write(CONTROLE_REG, 0x01);    // Ganho
}

// Liga o sensor
void habilitar_sensor() {
    write(HABILITAR_REG, 0x03);   // Liga e ativa ADC
}

// Desliga o sensor
void desabilitar_sensor() {
    write(HABILITAR_REG, 0x00);
}

// Detecta a cor com base nos valores brutos
const char* detectar_cor(uint16_t vermelho, uint16_t verde, uint16_t azul, uint16_t claro) {
  if (vermelho < 60 && verde < 60 && azul < 85) {
    return "Preto";
  } else if (vermelho > 200 && verde > 200 && azul > 200) {
    return "Branco";
  } else if (vermelho > 200 && verde > 200 && azul < 150) {
    return "Amarelo";
  } else if (vermelho > verde + 40 && vermelho > azul + 40) {
    return "Vermelho";
  } else if (verde > vermelho + 40 && verde > azul + 40) {
    return "Verde";
  } else if (azul > vermelho + 40 && azul > verde + 40) {
    return "Azul";
  } else if (vermelho > 180 && verde > 100 && azul < 80) {
    return "Laranja";
  } else if (vermelho > 150 && azul > 150 && verde < 100) {
    return "Roxo";
  } else if (vermelho > 180 && azul > 180 && verde < 130) {
    return "Lilás";
  } else if (verde > 180 && azul > 180 && vermelho < 100) {
    return "Ciano";
  } else if (vermelho > 200 && verde < 150 && azul > 150) {
    return "Rosa";
  } else {
    return "Indefinido";
  }
}
