#include <emscripten.h>
#include <stdlib.h>
#include <stdint.h>
#include "Adventure.h"

// Screen buffer for rendering
uint32_t screenBuffer[ADVENTURE_SCREEN_WIDTH * ADVENTURE_TOTAL_SCREEN_HEIGHT];

// Input state
bool keyLeft = false, keyUp = false, keyRight = false, keyDown = false, keyFire = false;
bool keySelect = false, keyReset = false;

// Exported functions for JS to call
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void set_key(int key, bool state) {
        switch(key) {
            case 37: keyLeft = state; break;   // Arrow Left
            case 38: keyUp = state; break;     // Arrow Up
            case 39: keyRight = state; break;  // Arrow Right
            case 40: keyDown = state; break;   // Arrow Down
            case 32: keyFire = state; break;   // Space
            case 13: keySelect = state; break; // Enter
            case 82: keyReset = state; break;  // R
        }
    }

    EMSCRIPTEN_KEEPALIVE
    uint8_t* get_screen_buffer() {
        return (uint8_t*)screenBuffer;
    }
}

// Implement platform dependencies required by Adventure.cpp
void Platform_PaintPixel(int r, int g, int b, int x, int y, int width, int height) {
    // ImageData expects bytes in R, G, B, A order.
    // In a Little-Endian uint32, this is 0xAABBGGRR.
    // If the color looks "thin" or "wrong", it might be due to R/B swap or alpha issues.
    uint32_t color = 0xFF000000 | (b << 16) | (g << 8) | r; 

    for (int dy = 0; dy < height; dy++) {
        for (int dx = 0; dx < width; dx++) {
            int px = x + dx;
            int py = y + dy;
            if (px >= 0 && px < ADVENTURE_SCREEN_WIDTH && py >= 0 && py < ADVENTURE_TOTAL_SCREEN_HEIGHT) {
                screenBuffer[py * ADVENTURE_SCREEN_WIDTH + px] = color;
            }
        }
    }
}

void Platform_ReadJoystick(bool* left, bool* up, bool* right, bool* down, bool* fire) {
    *left = keyLeft;
    *up = keyUp;
    *right = keyRight;
    *down = keyDown;
    *fire = keyFire;
}

void Platform_ReadConsoleSwitches(bool* select, bool* reset) {
    *select = keySelect;
    *reset = keyReset;
}

void Platform_ReadDifficultySwitches(int* left, int* right) {
    *left = DIFFICULTY_B;
    *right = DIFFICULTY_B;
}

void Platform_MakeSound(int sound) {
    // Send sound command to JS
    EM_ASM({
        if (window.playAdventureSound) window.playAdventureSound($0);
    }, sound);
}

float Platform_Random() {
    return (float)rand() / (float)RAND_MAX;
}

void main_loop() {
    Adventure_Run();
    
    // Tell JS to draw the frame buffer
    EM_ASM({
        if (window.renderAdventureFrame) {
            var view = new Uint8ClampedArray(HEAPU8.buffer, $0, 320 * 224 * 4);
            window.renderAdventureFrame(view);
        }
    }, screenBuffer);
}

int main() {
    emscripten_set_main_loop(main_loop, ADVENTURE_FPS, 1);
    return 0;
}
