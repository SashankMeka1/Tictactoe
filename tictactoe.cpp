#include <iostream>
#include <stdlib.h>
using namespace std;
void printboard(char game_arr[4][4]){
	for(int i = 0; i <4; i++){//print board
		for(int j = 0; j < 4; j++){
			cout<<game_arr[i][j]<<" ";
		}
		cout << endl;
	}
}
bool checkwins(int win_arr[7]){// check wins by seeing if row or column or diagonal is greater than 3
	for(int i =0 ; i < 7; i++){
		if(win_arr[i] >=3){
			return true;
		}
	}
	return false;
}
int * get_move(char game_arr[4][4], char player){
	char move[2];// get move and take out bad moves
	cout << player << " move: ";
	cin >> move;
	int * ptr = new int[2];
	ptr[0] = ((int)move[1])-48;
	ptr[1] = ((int)move[0])-96;
	if(game_arr[ptr[0]][ptr[1]] == ' '){
		return ptr;
	}
	else{
		cout << "Invalid input";
		return get_move(game_arr, player);
	}
	return ptr;
		
}
int game(char game_arr[4][4], int xwins[7], int owins[7], int turnnum){
	printboard(game_arr);
	turnnum++;//update board run game use length seven array for all rows and diagonals and increment each row and column till we get three and declare win for x or o
	int * move = get_move(game_arr, 'X');	
	game_arr[move[0]][move[1]] = 'X';
	xwins[move[0]-1] += 1;
	xwins[move[1]+2] += 1;
	xwins[7] += (move[0] == move[1]);
	if(checkwins(xwins)){
		printboard(game_arr);
		cout << "X won!"<<endl;
		return 0;
	}
	if(turnnum == 9){//if number of turns reaches nine its a tie
		cout << "Tie"<<endl;
		return 20;
	}
	else{
		printboard(game_arr);
		move = get_move(game_arr, 'O');
		game_arr[move[0]][move[1]] = 'O';
		owins[move[0]-1]+=1;
		owins[move[1]+2]+=1;
		owins[7] += (move[0] == move[1]);
		if(checkwins(owins)){
			printboard(game_arr);
			cout << "O won!";
			return 1;
		}
		turnnum++;
		return game(game_arr, xwins, owins, turnnum);
	}

}	
int main(){
	char input;
	int turnnum = 0;
	static int win[2] = {0};//variables and array tracking wins
	int xwins[7] = {0};
	int owins[7] = {0};
     	char game_arr[4][4] = {{' ','A','B','C'},{'1',' ',' ',' '},{'2',' ',' ',' '},{'3',' ',' ',' '}};
	win[game(game_arr, xwins, owins, turnnum)]++;//c++ doesnt give out of bounds error :)
	cout << "X wins:" <<win[0]<<" O wins:"<<win[1]<<endl; 
	cout << "play again? y or n only!"<<endl;
	cin >> input;
	if(input == 'y'){
		main();
	}
	else{
		return 0;
	}
	return 0;
}
