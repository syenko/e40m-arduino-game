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
    void generateFirstOrLastSection(const char size);
    void generateMiddleSection(const char size);

    char** chunks[CHUNK_COUNT];
    int boardWidth;
    int boardHeight;
    char** board;
    char** display;
    char** nextBoard;
};
