#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "matrix.cpp"
using namespace std;


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
	Matrix* m = new Matrix(rows,columns);
	cout << "------------traversing-------------"<<endl;
	m->go(0,0,rows,columns);

	m->sum();

	cout << "---------------------------------";
		

	cout << "hi";

	return 0;
}


