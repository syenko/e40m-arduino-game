#include "character.hh"

const char GRAVITY = 1;
const char BOARD_SIZE = 8;
const float TIME_CONST = 0.01;
const char CHUNK_COUNT = 5;

class Board {
  public:
    Board();
    ~Board();
    void updateBoardState();
    char** getDisplay();
    void updateDisplay();
    void generateChunk();
  private:
    Character* character;
    char get(int x, int y);
    
    bool isColliding(int x, int y); 
    int generateFirstOrLastSection(const char** chunk, const char size, const int prev_chunk_y, const int max_chunk_y);
    int generateMiddleSection(const char** chunk, const char size, const int prev_chunk_y, const int max_chunk_y);

    char** chunks[CHUNK_COUNT];
    char chunkHeights[CHUNK_COUNT];
    int boardWidth;
    int boardHeight;
    char** board;
    char** display;
    char** nextBoard;
};
