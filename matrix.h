
class Matrix{
	private:
		typedef struct cell {
			int weight;
			bool visited;
			Matrix::cell * best;	

		} cell;

		Matrix::cell*** m;
		int x_direction(Matrix::cell* best,Matrix::cell* left, Matrix::cell* right);
		int y_direction(Matrix::cell* best,Matrix::cell* up,Matrix::cell* down);
		Matrix::cell* edge_cell();

	protected:
		Matrix::cell*** allocmatrix(int rows,int columns);
		Matrix::cell* alloccell(int weight,int row,int column,int rmax,int cmax);
		Matrix::cell*** alloccells(int rows,int columns);
		Matrix::cell* best(Matrix::cell* up,Matrix::cell* down,Matrix::cell* left,Matrix::cell* right);

	public:
		Matrix(int rows,int columns);
		void print(int rows,int columns);
		void sum();
		Matrix::cell* go(int x,int y,int rows,int columns);
			
};
