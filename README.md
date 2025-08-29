# 🔴🟠🟡🟢🔵 Sensor de Cor o TCS34725 atuando com Pico W (BitDogLab)
![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Plataforma](https://img.shields.io/badge/Plataforma-Raspberry%20Pi%20Pico-purple.svg)
![Sensor](https://img.shields.io/badge/Sensor-TCS34725-red.svg)


## Sobre o Projeto
Este projeto visa criar um firmware para detectar a coloração com o sensor (TCS34725).

## 🛠️ Estrutura do projeto
- Controle_cor.c – Programa principal em C que faz leitura de presença, com base nesta informação utiliza o servo motor girar para direita caso haja presença detectada a menos de 10cm e para a esquerda de 10cm ou mais e essa informação é exibida no porta serial e no visor oled da BitDogLab e grava no SD Card a distancia, o estado do servo e tempo
- tcs34725.c - Onde fica as definições do sensor de para a detecção da cor
- Pasta inc - Onde esta localizada as informações da oled
- CMakeLists.txt – Configuração do build usando o Pico SDK

- ## 🔌 Requisitos
Hardware:

- Raspberry Pi Pico W
- Sensor de Distancia (TCS34725)


## ⚙️ Como usar
1- Clone o repositorio

2- Deploy no Pico W
 - Segure o botão BOOTSEL do Pico W e conecte-o ao PC
 - Clique no botão run no Vscode ou arraste o arquivo .u2 para dentro do disco removível que aparecer
 - O Pico irá reiniciar executando o firmware
   
## 🔧 Funcionamento do Código
O programa realiza as seguintes ações:

1. Inicialização dos periféricos
- Configura o barramento I2C0 (SDA_I2C = 0 | SCL_I2C = 1) para o sensor de COR

2. Leitura da Coloração
A cada segundo, o sistema:

- Detecta a cor com o sensor de cor TCS34725
- Exibe  no display OLED a coloração detectada

## 📦 Dependências

tcs34725.h para o sensor de cor

