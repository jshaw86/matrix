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
	if(!down->visited && ( best == NULL || (best != NULL && down->weight < best->weight ))){
			cout << "\t CHOOSING DOWN"<<endl;
			best = down;

	}

	if(!right->visited && ( best == NULL || (best != NULL && right->weight <best->weight) )){
			cout << "\t CHOOSING RIGHT"<<endl;
			best = right;

	}
	
	 
	if(!up->visited && (best == NULL || (best != NULL && (up->weight * 3) < best->weight))){
		cout << "\t CHOOSING UP"<<endl;
		best = up;	

	}	

	if(!left->visited && (best == NULL || (best != NULL && (left->weight * 3) <best->weight))){
			cout << "\t CHOOSING LEFT"<<endl;
			best = left;

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

			cout << "THE CURRENT IS:" << x << ","<<y <<"THE WEIGHT IS: "<< current->weight<<endl;

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
				int next_y = y+ y_direction(best_cell,up,down);
				int next_x = x + x_direction(best_cell,left,right);
				matrix[y][x]->best = matrix[next_y][next_x];
				cout << "\tNEXT BEST IS: "<<best_cell<<":" << next_x <<"," << next_y<< "THE WEIGHT IS: " << matrix[next_y][next_x]->weight <<endl;
				
				if(best_cell == NULL){
					cout << "\t\tBACKING OUT" <<endl;
					return NULL;

				}
				else{
					
					//cout << "VISITED:" << matrix[y][x]->visited << endl;
					cell* next =  go(matrix,next_x,next_y,rows,columns);
					if(next != NULL){
						return next;
					}

					next = go(matrix,next_x,next_y,rows,columns);
					return next;
					
				
			}
		}
}

/*cell*** build_matrix(string input, int rows,int columns){
	int** weights = new int*[columns];
	*weights = new int[rows];
	int row =0;
	for(int i = 0;input.length();i++){
		char c= input.at(i);
		int column = 0;
		if(&c == "|"){
			int j = i;
			while(j<input.length() && &input.at(j) != "|"){
					j++;
			}
			column++;
			weights[column][row] = input.substr(i,j);
			if(column ==columns){
				row++;
				column = 0;
	
			}

			i = j;

		}

	}

	cell*** matrix = allocmatrix(rows,columns);
	for(int x = 0;x <rows;x++){
		for(int y =0;y<columns;y++){
			alloccell(matrix,weights[y][x],x,y,rows,columns);		

		}

	}

	return matrix;


}
*/
int main(int argc,const char* argv[]){
	int rows = 6;
	int columns = 4;

	srand ( time(NULL) );

	
	/*
	 0       |       4       |       4       |       3       |
	 3       |       5       |       2       |       3       |
   7       |       2       |       5       |       4       |
   5       |       9       |       6       |       7       |
   3       |       10      |       3       |       2       |
   8       |       10      |       2       |       0       |
	 */
	/*
	   0 | 5 | 7 | 6 |
		 1 | 3 | 2 | 7 |
		 9 | 2 | 1 | 6 |
	  10 | 1 | 8 | 2 |
		 2 | 3 | 6 | 10  |
		 1 | 8 | 3 | 0 |
		 */

	cell*** matrix = alloccells(rows,columns);
		
	mprint(matrix,rows,columns);
	cout << "------------traversing-------------"<<endl;
	go(matrix,0,0,rows,columns);
	int total = 0;
	cell* current = matrix[0][0];
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


