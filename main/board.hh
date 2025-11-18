#include "character.hh"

const char GRAVITY = 1;
const char BOARD_SIZE = 8;
const float TIME_CONST = 0.01;
const char CHUNK_COUNT = 5;
const char CHARACTER_SIZE = 2;
const char MAX_LIVES = 4;
const char WIN_VAL = 2;
const char START_THRESHOLD = 0.5;

enum State {
  playing, won, lost
};

class Board {
  public:
    // Creates the board, initializes tiles, display buffers, and character.
    Board();
    // Releases heap-allocated character and display memory.
    ~Board();
    // Advances physics and transitions game state based on input/collisions.
    void updateBoardState();
    // Returns the 8x8 display buffer for LED driving.
    char** getDisplay();
    // Rebuilds what should be shown based on the character and state.
    void updateDisplay();
    // Future hook for generating procedural chunk data.
    void generateChunk();

  private:
    Character* character;
    // Safely reads the board at (x, y), or zero when out of bounds.
    char get(int x, int y);
    
    // Returns the highest collision value within the character footprint.
    int isColliding(int x, int y); 

    char** chunks[CHUNK_COUNT];
    char chunkHeights[CHUNK_COUNT];
    int boardWidth;
    int boardHeight;
    char** board;
    char** display;
    char** nextBoard;
    State state;
};
