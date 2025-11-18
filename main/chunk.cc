#include "chunk.hh"
#include <math.h>

// NOTE: This files is the start of random platform generation,
// but we ran out of time :(
// They are commented out so that the code compiles and can be added to the
// arduino.

// Generates the first or last section in a chunk.
// int Chunk::generateFirstOrLastSection(const char** chunk, const char size, const int prev_chunk_y, const int max_chunk_y) {
//     // First or last section must be ground
//     const int min_chunk_y = max_chunk_y - BOARD_SIZE;
//     int section_y = min(prev_chunk_y + random(-MAX_JUMP, MAX_JUMP), MAX_Y);
//     section_y = max(min_chunk_y, section_y);
//     section_y = min(max_chunk_y, section_y);
//     const char platform_height = random(MIN_PLATFORM_WIDTH, MAX_PLATFORM_WIDTH);
//     for (int r = max_chunk_y - BOARD_SIZE + section_y - 1; 
//       r < min(BOARD_SIZE, section_y + platform_height); r++) {
//         for (int c = 0; c < size; c++) {
//             chunk[r][c] = 15;
//         }
//     }
// }

// Creates a middle section in a chunk.
// int Chunk::generateMiddleSection(const char** chunk, const char size, const int prev_chunk_y, const int max_chunk_y) {
    
// }

// Creates the first chunk of a level.
// void Chunk() {
//     char remaining_size = BOARD_SIZE;
//     char section_size = random(MIN_SECTION_SIZE, remaining_size - 1);
//     remaining_size -= section_size;
//     const int min_y = min(chunkHeights);
//     const int chunk_height = min(min_y + random(-MAX_JUMP, MAX_JUMP), MAX_Y);
//     generateFirstOrLastSection(board, section_size);
//     section_size = random(1, remaining_size);
//     remaining_size -= section_size;
//     while (remaining_size > 0) {
//         generateSection(board, section_size);
//         section_size = random(1, remaining_size);
//         remaining_size -= section_size;
//     }
//     generateFirstOrLastSection(board, remaining_size);
// }