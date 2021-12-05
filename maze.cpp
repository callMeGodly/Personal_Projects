#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze=NULL;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
  
   mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS
   
     
     
   if (mymaze == NULL) {
      cout << "Error, input format incorrect." << endl;
      return 1;
   }
	 //================================
   // When working on Checkpoint 3, you will call maze_search here.
   // But for Checkpoint 1, just assume we found the path.
  
   result = maze_search(mymaze, rows, cols); // <--- TASK: CHANGE THIS
	
	
   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

	 //================================
   // ADD CODE BELOW
   // to delete all memory that read_maze allocated
  
   for(int i = 0; i < rows; ++i){
       delete[] mymaze[i];
   }
   delete[] mymaze;
   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
  // *** You complete ****
  int check_start = 0;
  int check_finish = 0;
  bool found = false;
  Location star;
  Queue q(rows*cols);
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      if(maze[i][j] == 'S'){
        star.row = i; star.col = j;
        ++check_start;
      }
      else if(maze[i][j] == 'F'){
        ++check_finish;
      }
    }
  }
  
  if(check_start != 1 or check_finish != 1){
    return -1;
  }
  
  int** visited = new int*[rows];
  for(int i = 0; i < rows; ++i){
    visited[i] = new int[cols];
    for(int j = 0; j < cols; ++j){
      visited[i][j] = 0;
    }
  }
  
  Location** predecessor = new Location*[rows];
  for(int i = 0; i < rows; ++i){
    predecessor[i] = new Location[cols];
    for(int j = 0; j < cols; ++j){
      predecessor[i][j].row = -1;
      predecessor[i][j].col = -1;
    }
  }
  
  Location last_loc;
  q.add_to_back(star); 
  while(!q.is_empty()){ 
    Location current_loc;
    Location neighbor;
    current_loc = q.remove_from_front();
    if(current_loc.row - 1 >= 0 && maze[current_loc.row - 1][current_loc.col] == '.'){
        if(visited[current_loc.row - 1][current_loc.col] == 0){
          visited[current_loc.row - 1][current_loc.col] = 1;
          neighbor.row = current_loc.row - 1;
          neighbor.col = current_loc.col;
          q.add_to_back(neighbor);
          predecessor[neighbor.row][neighbor.col] = current_loc;
        }
    }
 
    if(current_loc.col - 1 >= 0 && maze[current_loc.row][current_loc.col - 1] == '.'){
        if(visited[current_loc.row][current_loc.col - 1] == 0){
          visited[current_loc.row][current_loc.col - 1] = 1;
          neighbor.row = current_loc.row;
          neighbor.col = current_loc.col - 1;
          q.add_to_back(neighbor);
          predecessor[neighbor.row][neighbor.col] = current_loc;
        }
    }
    
    if(current_loc.row + 1 < rows && maze[current_loc.row + 1][current_loc.col] == '.'){
        if(visited[current_loc.row + 1][current_loc.col] == 0){
          visited[current_loc.row + 1][current_loc.col] = 1;
          neighbor.row = current_loc.row + 1;
          neighbor.col = current_loc.col;
          q.add_to_back(neighbor);
          predecessor[neighbor.row][neighbor.col] = current_loc;
        }
    }
    
    if(current_loc.col + 1 < cols && maze[current_loc.row][current_loc.col + 1] == '.'){
        if(visited[current_loc.row][current_loc.col + 1] == 0){
          visited[current_loc.row][current_loc.col + 1] = 1;
          neighbor.row = current_loc.row;
          neighbor.col = current_loc.col + 1;
          q.add_to_back(neighbor); 
          predecessor[neighbor.row][neighbor.col] = current_loc;
        }
    }
 
    if(current_loc.row - 1 >= 0 && maze[current_loc.row - 1][current_loc.col] == 'F'){
        found = true;
        last_loc = current_loc;
        break;
    }
    else if(current_loc.col - 1 >= 0 && maze[current_loc.row][current_loc.col - 1] == 'F'){
        found = true;
        last_loc = current_loc;
        break;
    }
    else if(current_loc.row + 1 < rows && maze[current_loc.row + 1][current_loc.col] == 'F'){
        found = true;
        last_loc = current_loc;
        break;
    }
    else if(current_loc.col + 1 < cols && maze[current_loc.row][current_loc.col + 1] == 'F'){
        found = true;
        last_loc = current_loc;
        break;
    }
  }
  
  if(found){
    while(maze[last_loc.row][last_loc.col] != 'S'){
        maze[last_loc.row][last_loc.col] = '*';
        last_loc = predecessor[last_loc.row][last_loc.col];
    }
    for(int i = 0; i < rows; ++i){
        delete[] predecessor[i];
    }
    delete[] predecessor;
    for(int i = 0; i < rows; ++i){
        delete[] visited[i];
    }
    delete[] visited;
    return 1;
  }
  else{
    return 0;
  }
}
