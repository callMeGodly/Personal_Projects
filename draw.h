#include "draw.h"

class Turtle {
  public:
    Turtle(double x0, double y0, double d0);
    void move(double dist);
    void turn(double deg);
    void setColor(Color c);
    void off();
    void on();
  private:
    double x;
    double y;
    double d;
    Color paint;
    bool p;
};
