#include "turtle.h"
#include <cmath>

Turtle::Turtle(double x0, double y0, double d0){
  x = x0;
  y = y0;
  d = d0;
  p = true;
  paint = draw::BLACK;
  
}

void Turtle::setColor(Color c){
  paint = c;
}

void Turtle::off(){
  p = false;
}

void Turtle::on(){
  p = true;
}

void Turtle::move(double dist){ 
  draw::setcolor(paint);
  double x1, y1, x2, y2;
  x1 = x;
  y1 = y;
  x2 = x1 + dist*cos((double)(d*M_PI)/180.0);
  y2 = y1 + dist*sin((double)(d*M_PI)/180.0);
  if(p){
    draw::line(x1, y1, x2, y2);
  } 
  x = x2;
  y = y2;
}

void Turtle::turn(double deg) {
  d = d + deg;
}
