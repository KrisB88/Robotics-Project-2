// Author: Ashely Eden Cox
// CSCI 4360 wavefront
// Purpose: The purpose of the program is to navigate a world that is given.
// File: wavefront.cpp

#include <iostream>
#include <string>
#define NORTH 1
#define SOUTH 2
#define WEST 3
#define EAST 4
using namespace std;

// functions
void WavefrontSearch(int array[8][16], int goal_x, int goal_y);
struct xy{
	unsigned int x;
	unsigned int y;
};

const int ROW = 8;
const int COL = 16;

int main(){
	//WORLD #1
	int worldArray[8][16] ={{2,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1},
							{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
							{0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0}};
	
	//WORLD #2 for testing
	//int worldArray[8][16] ={{2,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0},
	//						{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
	//						{0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0},
	//						{0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0},
	//						{0,0,0,1,1,1,1,0,0,1,0,0,0,0,0,0},
	//						{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	//						{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	//						{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}};


	//ask user for goal location.

	struct xy pathArray[50];
	int goal_x;
	int goal_y;
	int x = 0;
	int y = 0;
	cout << "Please enter x coordinate of goal: ";
	cin >> goal_x;
	while( (goal_x > 7) || (goal_x < 0) )
	{
		cout << "Please enter an x coordinate between 0 and 7: ";
		cin >> goal_x;
	}
	cout << endl;
	cout << "Please enter y coordinate of goal: ";
	cin >> goal_y;
	while( (goal_y > 15) || (goal_y < 0) )
	{
		cout << "Please enter an y coordinate between 0 and 15: ";
		cin >> goal_y;
	}

	cout << endl;

	x = goal_x;
	y = goal_y;


	WavefrontSearch(worldArray, goal_x, goal_y);
	cout << "The altared array is: " << endl;
		for( int i = 0; i < ROW; i++){
			cout << endl;
			for(int j = 0; j < COL; j++){
				cout << worldArray[i][j] << "   ";
		}
	}


//To plan an optimal path, you start at the goal, and at every point, until 
		//you've reached the goal, you pick the next cell that has the minimum 
		//value of all adjacent cells. For example, one good path from S to G 
		//(with each cell represented by its x,y Cartesian coordinates, starting 
		//at 0,0 in the lower-left corner):

	cout << endl;
	cout << endl;
	struct xy currLocation; 
	currLocation.x=0;
	currLocation.y=0;
	
	int distance = 0;
	int currentVal = worldArray[x][y];
	
	int currFace = SOUTH;

	 while(currLocation.x !=3 && currLocation.y != 15 )
 {
			 // //setting currentVal to the goal spot

				//if goalx goaly+1 != 1 && > curr val
			  // move right, chg prev 99, inc pathcount
			 
			if ( (worldArray[x][y + 1] > currentVal) && worldArray[x][y + 1] != 1  && y != 0) //this direction is SOUTH
			  {
				  currentVal = worldArray[x][y + 1];
				  y = (y + 1); //updating y
				   if(currFace == NORTH)
				  {
					//rotate right 2 times
					  currFace = SOUTH;
				  }
				  else if(currFace == EAST)
				  {
					//rotate right 1 times
					  currFace = SOUTH;
				  }
				  else if(currFace == WEST)
				  {
					//rotate right 3 times
					  currFace = SOUTH;
				  }
				 currLocation.y=y; //updating y
				 //GO STRAIGHT
				 worldArray[x][y] = 98;
				  /*pathArray[distance].x=x;
				  pathArray[distance].y=y;*/
				  distance ++;
			  }
			    //if goalx+1 goaly != 1 && > curr val
			  // move down, chg prev 99, inc pathcount
			  else if ( (worldArray[x + 1][y] > currentVal) && worldArray[x + 1][y] != 1  && y != 0) // this direction is EAST
			  {
				  currentVal = worldArray[x + 1][y];
				  x = (x + 1);
				   if(currFace == NORTH)
				  {
					//rotate right 1 times
					  currFace = EAST;
				  }
				  else if(currFace == WEST)
				  {
					//rotate right 2 times
					  currFace = EAST;
				  }
				  else if(currFace == SOUTH)
				  {
					//rotate right 3 times
					  currFace = EAST;
				  }
				  currLocation.x=x;
				  //GO STRAIGHT
				  worldArray[x][y] = 98;
				 /* pathArray[distance].x=x;
				  pathArray[distance].y=y;*/
				  distance ++;
			  } 
			
				//if [goalx -1][ y] != 1 && > current val && if the row is not 0 (to keep in bounds)
			  // move up, change prev to 99, increment pathcount
			  else if( (worldArray[x - 1][y] > currentVal) && worldArray[x -1][y] != 1  && x != 0) // this direction is WEST
			  {
				  currentVal = worldArray[x - 1][y];
				  x = (x - 1);
				  if(currFace == NORTH)
				  {
					//rotate right 3 times
					  currFace = WEST;
				  }
				  else if(currFace == EAST)
				  {
					//rotate right 2 times
					  currFace = WEST;
				  }
				  else if(currFace == SOUTH)
				  {
					//rotate right 1 times
					  currFace = WEST;
				  }
				  currLocation.x=x;
				  //GO STRAIGHT
				  worldArray[x][y] = 98;
			/*	 pathArray[distance].x=x;
				 pathArray[distance].y=y;*/
				 distance ++;


			  }
			  //if [goalx][goaly-1] != 1 && > curr val
			  // move left, change prev val to 99, increment pathcount
			  else if ( (worldArray[x][y - 1] > currentVal) && worldArray[x][y - 1] != 1  && y != 0) // this direction is NORTH
			  {
				  currentVal = worldArray[x][y - 1];
				  y = (y - 1);
				   if(currFace == WEST)
				  {
					//rotate right 1 times
					  currFace = NORTH;
				  }
				  else if(currFace == EAST)
				  {
					//rotate right 3 times
					  currFace = NORTH;
				  }
				  else if(currFace == SOUTH)
				  {
					//rotate right 2 times
					  currFace = NORTH;
				  }
				  currLocation.y=y;
				  //GO STRAIGHT
				  worldArray[x][y] = 98;
				  /*pathArray[distance].x=x;
				  pathArray[distance].y=y;*/
				  distance ++;
			  }
			  		
			 
			  
	}
	  




//ORIGINAL
	 //while(currentVal != 2 )
		// {
		//	 // //setting currentVal to the goal spot
		//	 

		//	  //if [goalx -1][ y] != 1 && < current val && if the row is not 0 (to keep in bounds)
		//	  // move up, change prev to 99, increment pathcount
		//	  if( (worldArray[x - 1][y] < currentVal) && worldArray[x -1][y] != 1  && x != 0)
		//	  {
		//		  currentVal = worldArray[x - 1][y];
		//		  x = (x - 1);
		//		  worldArray[x][y] = 98;
		//		 pathArray[distance].x=x;
		//		 pathArray[distance].y=y;
		//		 distance ++;


		//	  }
		//	  //if [goalx][goaly-1] != 1 && < curr val
		//	  // move left, change prev val to 99, increment pathcount
		//	  else if ( (worldArray[x][y - 1] < currentVal) && worldArray[x][y - 1] != 1  && y != 0)
		//	  {
		//		  currentVal = worldArray[x][y - 1];
		//		  y = (y - 1);
		//		  worldArray[x][y] = 98;
		//		  pathArray[distance].x=x;
		//		  pathArray[distance].y=y;
		//		  distance ++;
		//	  }
		//	    //if goalx+1 goaly != 1 && < curr val
		//	  // move down, chg prev 99, inc pathcount
		//	
		//	  else if ( (worldArray[x + 1][y] < currentVal) && worldArray[x + 1][y] != 1  && y != 0)
		//	  {
		//		  currentVal = worldArray[x + 1][y];
		//		  x = (x + 1);
		//		  worldArray[x][y] = 98;
		//		  pathArray[distance].x=x;
		//		  pathArray[distance].y=y;
		//		  distance ++;
		//	  } 
		//	  //if goalx goaly+1 != 1 && < curr val
		//	  // move right, chg prev 99, inc pathcount
		//	  else if ( (worldArray[x][y + 1] < currentVal) && worldArray[x][y + 1] != 1  && y != 0)
		//	  {
		//		  currentVal = worldArray[x][y + 1];
		//		  y = (y + 1);
		//		  worldArray[x][y] = 98;
		//		  pathArray[distance].x=x;
		//		  pathArray[distance].y=y;
		//		  distance ++;
		//	  }
	 //}
	 // 

	 
	 	cout << "The Path array is: " << endl;
		/*for( int i = (distance-1); i >= 0; i--){
			cout << pathArray[i].x <<" " << pathArray[i].y << endl;*/
			
	/*}*/
		cout << endl;
		cout << endl;


	 
	 	cout << "The Path is: ";
		for( int i = 0; i < ROW; i++){
			//cout << endl;
			for(int j = 0; j < COL; j++){
				if ( worldArray[i][j] == 98 )
				{
					cout << "(" << i << ", " << j << "),";
					
				}

		}
	}
		cout << endl;
		cout << "The number of steps from (0,0) to (" << goal_x << "," << goal_y << ") is: " << (distance -1) << endl;


	return 0;
}

void WavefrontSearch( int array[8][16], int goal_x, int goal_y)
{
 //int goal_x, goal_y, goal;
  bool foundWave = true;
  int currentWave = 2; //Looking for goal first
  

  array[goal_x][goal_y] = 98; //set goal
  int goal = 98;

  while(foundWave == true)
  {
    foundWave = false;
    for(int y=0; y < COL; y++)
    {
      for(int x=0; x < ROW; x++)
      {
        if(array[x][y] == currentWave)
        {
          foundWave = true;
          goal_x = x;
          goal_y = y;
		  
		  if(goal_x > 0) //This code checks the array bounds heading WEST
            if(array[goal_x-1][goal_y] == 0)  //This code checks the WEST direction
              array[goal_x-1][goal_y] = currentWave + 1;
 
          if(goal_x < (ROW - 1)) //This code checks the array bounds heading EAST
            if(array[goal_x+1][goal_y] == 0)//This code checks the EAST direction
              array[goal_x+1][goal_y] = currentWave + 1;
 
          if(goal_y > 0)//This code checks the array bounds heading SOUTH
            if(array[goal_x][goal_y-1] == 0) //This code checks the SOUTH direction
              array[goal_x][goal_y-1] = currentWave + 1;
 
          if(goal_y < (COL - 1))//This code checks the array bounds heading NORTH
            if(array[goal_x][goal_y+1] == 0) //This code checks the NORTH direction
              array[goal_x][goal_y+1] = currentWave + 1;
        }
      }
    }
    currentWave++;
  }


}