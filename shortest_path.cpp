#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;
typedef struct cell {
		int weight;
		bool visited;
		cell * best;	

	} cell;

cell*** allocmatrix(int rows,int columns){

	cell ***matrix;

	matrix = new cell**[rows];
	for(int i = 0;i<rows;i++){
		matrix[i] = new cell*[columns];

	}

	return matrix;


}

cell* alloccell(cell*** matrix,int weight,int row,int column,int rmax,int cmax){
	cell* c = new cell(); 
	c->weight = weight;
	c->visited =false;
	matrix[row][column] = c;
	
	return c;
}

cell*** alloccells(int rows,int columns){
	//2 dimensional array of cell pointers
	cell ***matrix = allocmatrix(rows,columns);
	for(int i =0;i<rows;i++){
		for(int x =0;x<columns;x++){
			cell* c = alloccell(matrix,(int)	rand() % 10 + 1,i,x,rows,columns);
		}


	}

	matrix[0][0]->weight = 0;
	matrix[rows-1][columns-1]->weight = 0;

	return matrix;

}

cell* best(cell* up,cell* down,cell* left,cell* right){
	cell* best =NULL;
	if(!up->visited){
		best = up;	

	}	

	if(!left->visited){
		best = best == NULL || left->weight <up->weight?left:up;

	}
	if(!down->visited){
		best = best == NULL || down->weight < left->weight?down:left;

	}
	if(!right->visited){
		best =  best == NULL || right->weight <down->weight?right:down;

	}
	
	return best;
	

}

int x_direction(cell* best,cell* left, cell* right){
	//cout << "BEST :" <<best <<"LEFT:"<<left << "RIGHT:"<<right;
	if(best == left){
   return -1;

	}
	else if(best == right){
		return 1;


	}

	return 0;

}

int y_direction(cell* best,cell* up,cell* down){
	//cout << "BEST :" <<best <<"UP:"<<up << "DOWN:"<<down<<endl;
	if(best == up){
    return -1;

	}
	else if(best == down){
		return 1;


	}

	return 0;

}

cell* edge_cell(){
	cell* c = new cell();
	c->weight = 1000000000;
	c->visited = true;

	return c;


}
void mprint(cell*** matrix,int rows,int columns){
	for(int i =0;i<rows;i++){
		for(int x =0;x<columns;x++){
			cout << matrix[i][x]->weight << "\t|\t";
		}

		cout << endl;

	}

}
cell* go(cell*** matrix,int x,int y,int rows,int columns){
			cell* current = matrix[y][x];
			current->visited = true;	

			if(x ==(columns -1) && y == (rows -1)){
			
			//cout <<"BEST ID"<<best_cell<<endl;
				cout << "THE END" <<endl;
				return current;

			}
			else{
				cell* up = y != 0 ?matrix[y-1][x]:edge_cell();
				cell* down = y != rows -1? matrix[y+1][x]:edge_cell();
				cell* left = x !=0? matrix[y][x-1]:edge_cell();
				cell* right = x!= columns -1? matrix[y][x+1]:edge_cell();

				cell* best_cell = best(up,down,left,right);
				current->best = best_cell;


				if(best_cell == NULL){
					cout << "BACKING OUT" <<endl;
					return NULL;

				}
				else{
					int next_y = y+ y_direction(best_cell,up,down);
					int next_x = x + x_direction(best_cell,left,right);
					//cout << "VISITED:" << matrix[y][x]->visited << endl;
					//cout << "THE CURRENT IS:" << x << ","<<y <<"THE WEIGHT IS: "<< current->weight<<endl;
					cout << "NEXT BEST IS: " << next_x <<"," << next_y<< "THE WEIGHT IS: " << matrix[next_y][next_x]->weight <<endl;
					go(matrix,next_x,next_y,rows,columns);

					return current->best;
					
		
				/*current->best = go(matrix,next_x,next_y,rows,columns);
				if(current->best != NULL){
					return current->best;
		
				}
				current->best = go(matrix,next_x,next_y,rows,columns);
				if(current->best != NULL){
					return current->best;
		
				}
				current->best = go(matrix,next_x,next_y,rows,columns);
				return current->best;
				*/
			}
		}
}

int main(int argc,const char* argv[]){
	int rows = 6;
	int columns = 4;

	srand ( time(NULL) );

	cell*** matrix = alloccells(rows,columns);
	
	/*
	 0       |       4       |       4       |       3       |
	3       |       5       |       2       |       3       |
 7       |       2       |       5       |       4       |
5       |       9       |       6       |       7       |
3       |       10      |       3       |       2       |
8       |       10      |       2       |       0       |
	 */
	/*
	matrix[0][0]->weight = 3;
	matrix[1][0]->weight = 8;
	matrix[2][0]->weight = 4;
	matrix[3][0]->weight = 4;
	matrix[4][0]->weight = 5;
	matrix[5][0]->weight = 4;

	matrix[0][1]->weight = 9;
	matrix[1][1]->weight = 7;
	matrix[2][1]->weight = 4;
	matrix[3][1]->weight = 5;
	matrix[4][1]->weight = 8;
	matrix[5][1]->weight = 9;

	matrix[0][2]->weight = 9;
	matrix[1][2]->weight = 5;
	matrix[2][2]->weight = 6;
	matrix[3][2]->weight = 4;
	matrix[4][2]->weight = 3;
	matrix[5][2]->weight = 7;

	matrix[0][3]->weight = 5;
	matrix[1][3]->weight = 6;
	matrix[2][3]->weight = 3;
	matrix[3][3]->weight = 7;
	matrix[4][3]->weight = 3;
	matrix[5][3]->weight = 5;
*/
	mprint(matrix,rows,columns);
	cout << "------------traversing-------------"<<endl;
	int total = 0;
	cell* HEAD = go(matrix,0,0,rows,columns);
	
	total = 0;
	cell* current = HEAD;
	while(current != NULL){
		cout <<"SUMMING:"<< current->weight<<endl;
		total += current->weight;	
		current = current->best;
	}
	cout <<"TOTAL:"<< total<<endl;

	cout << "---------------------------------";
		

	cout << "hi";

	return 0;
}


