#include <Arduino.h>
#include "board.hh"

void generateFirstOrLastSection(char** board, const char size) {
    
}

void generateMiddleSection(char** board, const char size) {
    
}

void generateChunk(char** board) {
    char remaining_size = BOARD_SIZE;
    char section_size = random(1, remaining_size - 1);
    // First section has to be ground


    while (remaining_size > 0) {
        
        generateSection(board, section_size);
        remaining_size -= section_size;
    }
}

