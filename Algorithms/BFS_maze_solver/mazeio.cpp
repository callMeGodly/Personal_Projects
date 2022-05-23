#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a 
 *  2D dynamically  allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and 
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols) 
{
	
   // *** You complete ****
	ifstream myfile;
  myfile.open(filename);
  if(myfile.fail()){
    return NULL;
  }
  int r, c;
  if(myfile >> r && myfile >> c){
    *rows = r;
    *cols = c;
  }
  else{
    return NULL;
  }
  
  char** maze = new char*[*rows];
  for(int i = 0; i < *rows; ++i){
    maze[i] = new char[*cols];
    for(int j = 0; j < *cols; ++j){
      char into;
      myfile >> into;
      if(into != 'S' and into != 'F' and into != '#' and into != '.'){
        cout << "Error, input format incorrect.";
      }
      maze[i][j] = into;
    }
  }
  return maze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) 
{
   // *** You complete ****
  
   cout << rows << " " << cols << endl;
   for(int i = 0; i < rows; ++i){
     for(int j = 0; j < cols ; ++j){
       cout << maze[i][j];
     }
     cout << endl;
   }
}
