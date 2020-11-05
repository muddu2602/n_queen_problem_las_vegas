#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;
/// <summary>
/// 8-Queen Randomised Algorithm ( Las Vegas Algorithm )
	/// board[i][j] == 1 -----> Queen is Placed There
	/// board[i][j] == 0 -----> All other queens in the board doesnt attack the position 
	/// board[i][j] == 2 -----> The position is attacked by alteast 1 queen in the board
	/// </summary>
	/// <returns></returns>
//Globally Set the board
int board[200][200];
int n;
void initialise_board() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = 0;
		}
	}
}
void display_board() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] != 1)
				board[i][j] = 0;
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
void spot_attack_vertical(int row, int col) {
	for (int i = row+1; i < n; i++)
		board[i][col] = 2;
}
void spot_attack_left_diagonal(int row, int col) {
	for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--) {
		board[i][j] = 2;
	}
}
void spot_attack_right_diagonal(int row, int col) {
	for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++) {
		board[i][j] = 2;
	}
}
vector<int> compute_empty_slots(int row) {
	vector<int> empty{};
	for (int i = 0; i < n; i++) {
		if (board[row][i] == 0)
			empty.push_back(i);
	}
	return empty;
}
//Send the Empty_slot_indexes vector and the row to place the queen as parameters
bool compute_board(vector<int> empty_slots, int row) {
	//Its last row on the board while computing and only 1 empty_slot is left
	if (row == n-1 && empty_slots.size() == 1) {
		board[row][empty_slots.at(0)] = 1;
		return true;
	}
	//Its computation of any row and No of empty slots in that row is 0 --> no safe_slot to place the queen 
	else if (row <= (n-1) && empty_slots.size() == 0) {
		return false;
	}
	else {
		//Randomly Select any element_index in the empty slot vector
		int rand_index = rand() % empty_slots.size();
		//select the column at the random index
		int col = empty_slots.at(rand_index);
		//Assume queen is safe there and place the queen
		board[row][col] = 1;
		//Marks all unsafe position in all directions and mark them as -1
		spot_attack_vertical(row, col);
		spot_attack_left_diagonal(row, col);
		spot_attack_right_diagonal(row, col);
		//Compute the New Empty Slots Indexes for the next row 
		vector<int> new_empty_slots = compute_empty_slots(row + 1);
		return compute_board(new_empty_slots, row + 1);
	}
}
int main() {
	// Indexes of the empty_slots in the board
	cout << "Enter the size of the Chess Board" << endl;
	cin >> n;
	vector<int> empty_slots{ };
	for (int i = 0; i < n; i++) {
		empty_slots.push_back(i);
	}
	//Set initial result to false
	bool result = false;
	//Start from row = 0 to row = 7
    if(n == 1){
        cout<<1<<endl;
        cout << "This is the Only possible solution board " << endl;
    }
    else if (n==2 || n==3) {
		cout << "Solution Not Possible" << endl;
	}
    else{
        while (!result && n > 3){
		//set all positions in board to zeros
		initialise_board();
		result = compute_board(empty_slots, 0);
        }
        display_board();
		cout << "This is one of the possible solution board " << endl;
    }
}
