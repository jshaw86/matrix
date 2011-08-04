#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "matrix.h"

using namespace std;

Matrix::Matrix(int rows, int columns){
	m = allocmatrix(rows,columns);
		
	print(rows,columns);

}

Matrix::cell*** Matrix::allocmatrix(int rows,int columns){
	m = new cell**[rows];
	for(int i = 0;i<rows;i++){
		m[i] = new cell*[columns];

	}

	for(int i =0;i<rows;i++){
		for(int x =0;x<columns;x++){
			cell* c = alloccell((int)	rand() % 10 + 1,i,x,rows,columns);
		}


	}

	m[0][0]->weight = 0;
	m[rows-1][columns-1]->weight = 0;
	return m;


}

Matrix::cell* Matrix::alloccell(int weight,int row,int column,int rmax,int cmax){
	cell* c = new cell(); 
	c->weight = weight;
	c->visited =false;
	m[row][column] = c;
	
	return c;
}


Matrix::cell* Matrix::best(cell* up,cell* down,cell* left,cell* right){
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

int Matrix::x_direction(cell* best,cell* left, cell* right){
	//cout << "BEST :" <<best <<"LEFT:"<<left << "RIGHT:"<<right;
	if(best == left){
   return -1;

	}
	else if(best == right){
		return 1;


	}

	return 0;

}

int Matrix::y_direction(cell* best,cell* up,cell* down){
	//cout << "BEST :" <<best <<"UP:"<<up << "DOWN:"<<down<<endl;
	if(best == up){
    return -1;

	}
	else if(best == down){
		return 1;


	}

	return 0;

}

Matrix::cell* Matrix::edge_cell(){
	cell* c = new cell();
	c->weight = 1000000000;
	c->visited = true;

	return c;


}
void Matrix::print(int rows,int columns){
	for(int i =0;i<rows;i++){
		for(int x =0;x<columns;x++){
			cout << m[i][x]->weight << "\t|\t";
		}

		cout << endl;

	}

}

void Matrix::sum(){
	int total = 0;
	Matrix::cell* current = m[0][0];
	while(current != NULL){
		cout <<"SUMMING:"<< current->weight<<endl;
		total += current->weight;	
		current = current->best;
	}
	cout <<"TOTAL:"<< total<<endl;

}

Matrix::cell* Matrix::go(int x,int y,int rows,int columns){
			cell* current = m[y][x];
			current->visited = true;	

			cout << "THE CURRENT IS:" << x << ","<<y <<"THE WEIGHT IS: "<< current->weight<<endl;

			if(x ==(columns -1) && y == (rows -1)){
			
			//cout <<"BEST ID"<<best_cell<<endl;
				cout << "THE END" <<endl;
				return current;

			}
			else{
				cell* up = y != 0 ?m[y-1][x]:edge_cell();
				cell* down = y != rows -1? m[y+1][x]:edge_cell();
				cell* left = x !=0? m[y][x-1]:edge_cell();
				cell* right = x!= columns -1? m[y][x+1]:edge_cell();

				cell* best_cell = best(up,down,left,right);
				int next_y = y+ y_direction(best_cell,up,down);
				int next_x = x + x_direction(best_cell,left,right);
				m[y][x]->best = m[next_y][next_x];
				cout << "\tNEXT BEST IS: "<<best_cell<<":" << next_x <<"," << next_y<< "THE WEIGHT IS: " << m[next_y][next_x]->weight <<endl;
				
				if(best_cell == NULL){
					cout << "\t\tBACKING OUT" <<endl;
					return NULL;

				}
				else{
					cell* next =  go(next_x,next_y,rows,columns);
					if(next != NULL){
						return next;
					}

					next = go(next_x,next_y,rows,columns);
					return next;
				
			}
		}
}
