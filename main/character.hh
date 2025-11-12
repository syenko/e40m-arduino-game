class Character {
  public:
    Character();
    Character(char lives);
    ~Character() = default;
    float get_x() const;
    float get_y() const;
    int get_x_rounded() const;
    int get_y_rounded() const;
    void get_input();
    void decrease_life();
    char get_lives() const;

  private:
    float x_pos;
    float y_pos;
    float delta_x;
    float delta_y;
    char lives;
};