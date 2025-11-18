class Character {
  public:
    // Builds a default character starting at (0, 0) with full lives.
    Character();
    // Builds a character placed at coordinates (x, y).
    Character(int x, int y);
    // Builds a character with the provided life count.
    Character(char lives);
    ~Character() = default;
    // Returns the precise x-position.
    float get_x() const;
    // Returns the precise y-position.
    float get_y() const;
    // Indicates whether the character is currently airborne.
    bool get_jumped() const;
    // Returns the grid-aligned x-position.
    int get_x_rounded() const;
    // Returns the grid-aligned y-position.
    int get_y_rounded() const;
    // Returns the x-axis velocity component.
    float get_delta_x() const;
    // Returns the y-axis velocity component.
    float get_delta_y() const;
    // Polls input hardware to update velocity commands.
    void get_input();
    // Deducts one life from the player.
    void decrease_life();
    // Returns the remaining lives.
    char get_lives() const;
    // Applies jump velocity if allowed.
    void jump();
    // Sets the precise x-position.
    void set_x(float new_x);
    // Sets the precise y-position.
    void set_y(float new_y);
    // Sets the x-axis velocity.
    void set_x_vel(float new_x_vel);
    // Sets the y-axis velocity.
    void set_y_vel(float new_y_vel);
    // Updates the double-jump guard flag.
    void set_jumped(bool jumped);
    // Resets the character to its spawn point and decrements lives.
    void respawn();

  private:
    float x_pos_;
    float y_pos_;
    int start_x_;
    int start_y_;
    float delta_x_;
    float delta_y_;
    char lives_;
    bool jumped_;

};
