#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) {
  
	if(left < 0){
		width += left;
		left = 0;
	}
	else if(left + width > 256){
		width = 256 - left;
	}
	
	if(top < 0){
		height += top;
		top = 0;
	}
	else if(top + height > 256){
		height = 256 - top;
	}
	
  for(int i = top; i <= top + height; i++){
     image[i][left] = 0;
     image[i][left + width] = 0;
  }
  for(int i = left; i <= left + width; i++){
    image[top][i] = 0;
    image[top + height][i] = 0;
  }
}


// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) {
  
  double rx = width/2;
  double ry = height/2;
  for (double theta=0.0; theta < 2*M_PI; theta += .01) {
      double x = rx*cos(theta);
      double y = ry*sin(theta);
      x += cx;
      y += cy;
      
      if(y < 0 or x < 0 or y > 256 or x > 256){
        x = 0;
        y = 0;
      }
      
      image[(int)y][(int)x] = 0;
   }

}


int main() {
   // initialize the image to all white pixels
   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 255;
      }
   }
   
   // Main program loop here
   cout << "To draw a rectangle, enter: 0 top left height width" << endl;
   cout << "To draw an ellipse, enter: 1 cy cx height width" << endl;
   cout << "To save your drawing as ""output.bmp"" and quit, enter: 2" << endl;
   while(true){
		 int command; cin >> command;
     if(command == 2){
       break;
     }
     else if(command == 0){
       int top, left, height, width; cin >> top >> left >> height >> width;
       draw_rectangle(top, left, height, width);
     }
     else{
       int cy, cx, height, width; cin >> cy >> cx >> height >> width;
       draw_ellipse(cy, cx, height, width);
     }
   }

   // Write the resulting image to the .bmp file
   writeGSBMP("output.bmp", image);
   
   return 0;
}
