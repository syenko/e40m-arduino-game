#include "character.hh"

class Board {
  public:
    Board();
    ~Board(); 
    void updateBoardState();
    char** getDisplay();
  private:
    Character* character;
    char get(int x, int y);
    void updateDisplay();

    int boardWidth;
    int boardHeight;
    char** board;
    char** display;
};
