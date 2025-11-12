class Character {
  public:
    Character();
    Character(char lives);
    ~Character() = default;
    float get_x() const;
    float get_y() const;
    bool get_jumped() const;
    int get_x_rounded() const;
    int get_y_rounded() const;
    void get_input();
    void decrease_life();
    char get_lives() const;
    void jump();
    void update_x(float new_x);
    void update_y(float new_y);
    void update_x_vel(float new_x_vel);
    void update_y_vel(float new_y_vel);


  private:
    float x_pos_;
    float y_pos_;
    float delta_x_;
    float delta_y_;
    char lives_;
    bool jumped_;

};