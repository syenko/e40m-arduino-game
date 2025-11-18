const char MAX_JUMP = 3;
const char MAX_Y = 127;
const char MIN_SECTION_SIZE = 1;
const char MIN_PLATFORM_WIDTH = 1;
const char MAX_PLATFORM_WIDTH = 2;

class Chunk {
    public:
        Chunk();
        Chunk(Chunk* prev);

    private:
        int generateFirstOrLastSection();
        int generateMiddleSection();


        int height_;

}