#include <iostream>

using namespace std;

int grid[9][9];

void print_grid();
void take_input();
bool is_safe(int row, int col, int num);
bool row_check(int row, int num);
bool col_check(int col, int num);
bool box_check(int box_row, int box_col, int num);
bool find_unassigned_location(int &row, int &col);
bool solve_sudoku();

int main() {

	cout<<"\n\n                                       SUDOKU\n";
	
	for (int k = 0; k < 9; k++) {
		for (int j = 0; j < 9; j++) {
			grid[k][j] = 0;
		}
	}
	print_grid();
	take_input();
	print_grid();
	cout << "Solving Sudoku......." << endl;
	if (solve_sudoku())
		print_grid();
	else
		cout << "No Solution exits !!" << endl;
	return 0;
}

void print_grid() {
	
	cout << "\n\n\n";

	int i = 0;
	for (i = 0; i < 3; i++) {
		cout << "                           " << grid[i][0] << "  " << grid[i][1] << "  " << grid[i][2] << "  |  " << grid[i][3] << "  " << grid[i][4] << "  " << grid[i][5] << "  |  " << grid[i][6] << "  " << grid[i][7] << "  " << grid[i][8] << endl;
	}

	cout << "                         -----------------------------------" << endl;
	//cout << "------------------------------------------------------" << endl;
	for (i = 3; i < 6; i++) {
		cout << "                           " << grid[i][0] << "  " << grid[i][1] << "  " << grid[i][2] << "  |  " << grid[i][3] << "  " << grid[i][4] << "  " << grid[i][5] << "  |  " << grid[i][6] << "  " << grid[i][7] << "  " << grid[i][8] << endl;
	}
	//cout << "------------------------------------------------------" << endl;
	cout << "                         -----------------------------------" << endl;
	for (i = 6; i < 9; i++) {
		cout << "                           " << grid[i][0] << "  " << grid[i][1] << "  " << grid[i][2] << "  |  " << grid[i][3] << "  " << grid[i][4] << "  " << grid[i][5] << "  |  " << grid[i][6] << "  " << grid[i][7] << "  " << grid[i][8] << endl;
	}
	//cout << "------------------------------------------------------" << endl;
	//cout << "------------------------------------------------------" << endl;

}

void take_input() {
	bool ans = true;
	cout << " do you wish to input any value in the grid ? (y/n)\n";
	char c;
	cin >> c;
	if (c == 'n')
		ans = false;
	while (ans) {
		cout << "enter the cordinates of the position you want to edit separated by space. (format eg. 4 2)\n";
		int a, b;
		cin >> a >> b;
		cout << "enter the value you want to put on (" << a << "," << b<<")\n";
		int k;
		cin >> k;
		if (k < 1 || k>9) {
			cout << "Invalid value\n";
			exit(0);
		}
		//else
			grid[a][b] = k;
		cout << "do you wish to input more values ?(y/n)";
		char l;
		cin >> l;
		if (l == 'n')
			ans = false;
	}
}

bool is_safe(int row, int col, int num) {
	if (!row_check(row, num))
		if (!col_check(col, num))
			if (!box_check(row - row % 3, col - col % 3, num))
				if (grid[row][col] == 0)
					return true;
	return false;
}

bool row_check(int row, int num) {
	for (int col = 0; col < 9; col++) {
		if (grid[row][col] == num)
			return true;
	} 
	return false;
}

bool col_check(int col, int num) {
	for (int row = 0; row < 9; row++) {
		if (grid[row][col] == num)
			return true;
	}
	return false;
}

bool box_check(int box_row, int box_col, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row + box_row][col + box_col] == num)
				return true;
		}
	}
	return false;
}

bool find_unassigned_location(int &row, int &col) {
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (grid[row][col] == 0)
				return true;
	return false;
}

bool solve_sudoku() {
	int row, col;
	if (!find_unassigned_location(row, col))
		return true;
	for (int num = 1; num < 10; num++) {
		if (is_safe(row, col, num)) {
			grid[row][col] = num;

			if (solve_sudoku())
				return true;
			
			grid[row][col] = 0;
		}
	}
	return false;
}