#include "character.hh"

class Board {
  public:
    Board();
<<<<<<< HEAD
    ~Board();
=======
    ~Board(); 
>>>>>>> dc2eedbc5bb02b7aa56354e6771270e58fbe7eee
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
