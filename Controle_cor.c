#include <stdio.h>
#include "pico/stdlib.h"
#include "tcs34725.h"
#include "inc/ssd1306.h"
#include "inc/ssd1306_fonts.h"

int main() {
    stdio_init_all();
    configurar_i2c();

    sleep_ms(3000);
    printf("Inicializando sensor de cor...\n");

    iniciar_sensor();
    sleep_ms(50);
    habilitar_sensor();
    sleep_ms(700);

    // Inicializa o display OLED
    ssd1306_Init();           // Inicializa o driver
    ssd1306_Fill(Black);      // Limpa a tela
    ssd1306_UpdateScreen();   // Atualiza a tela

    while (true) {
        uint16_t claro    = tc_read16(0x14);
        uint16_t vermelho = tc_read16(0x16);
        uint16_t verde    = tc_read16(0x18);
        uint16_t azul     = tc_read16(0x1A);

        const char* cor = detectar_cor(vermelho, verde, azul, claro);

        printf("Detectado: %s (Claro:%d Vermelho:%d Verde:%d Azul:%d)\n", cor, claro, vermelho, verde, azul);

        char buffer[32]; // Buffer para formatar strings

        // === Atualiza informações no display OLED ===
        ssd1306_Fill(Black); // Limpa tela
        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString("DECT-COR", Font_7x10, White);

        // Exibe o nome da cor corretamente
        snprintf(buffer, sizeof(buffer), "COR: %s", cor);
        ssd1306_SetCursor(0, 12);
        ssd1306_WriteString(buffer, Font_7x10, White);

        ssd1306_UpdateScreen(); // Atualiza a tela

        sleep_ms(1000);
    }
    return 0;
}