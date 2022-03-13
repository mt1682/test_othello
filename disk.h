#ifndef disk_h
#define disk_h

class Disk {
   private:
    int x;
    int y;
    int color;
    int keepNear[9];
    int keepColor;

   public:
    int near[9];
    void init();
    void flip();
    int set(int player);
    int getColor();
    void save();
    void restore();
};

#endif