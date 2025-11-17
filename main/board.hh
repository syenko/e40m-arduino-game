#include "character.hh"

class Board {
  public:
    Board();
    ~Board();
    void updateBoardState();
    char** getDisplay();
    void updateDisplay();
  private:
    Character* character;
    char get(int x, int y);
    
    bool isColliding(int x, int y); 

    int boardWidth;
    int boardHeight;
    char** board;
    char** display;
};
