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
int* updateboard(char game_arr[4][4], char player){
    char move[2];
    cout << player <<" move: ";
    cin >> move;//check if slot empty and give update coords
    int y = move[0] -96;
    int x = move[1]-48;
    if(x < 4 and y < 4 and game_arr[x][y]==' '){
	int *update = new int[2];
	update[0] = x;
	update[1] = y;
	game_arr[x][y] = player;
	return update;
    }
    else{
        cout << "Illegal Move"<<endl;
        return updateboard(game_arr, player);
    }
}
int* game(char game_arr[4][4], int xcount, int ocount, int turnnum){
    int *update;//update based on coords
    update = updateboard(game_arr, 'X');
    xcount += *update+*(update+1);
    printboard(game_arr);//add coords to xcount. will be helpful later
    turnnum++;
    free (update);
    if (turnnum > 5 and turnnum%2==0 and (36 - xcount)%3==0){
        int* win_arr = new int[2];//if number of turns is greater than five then win is possible and if it is even then x wins otherwise o wins
        win_arr[0] = 1;
        win_arr[1] = 0;//the modulus of thirty six minus the sums of the coordinates will be zero. saves us from writing a checkwins function
        cout << "Player X won!"<<endl;
        return win_arr;
    }
    
    update = updateboard(game_arr, 'O');
    ocount += *update+*(update+1);
    printboard(game_arr);
    turnnum++;
    free (update);
    if (turnnum > 5 and turnnum%2!=0 and (36-ocount)%3==0){
        int* win_arr = new int[2];
        win_arr[0] = 0;
        win_arr[1] = 1;
        cout << "Player O won!"<<endl;
        return win_arr;
    }
    
    return game(game_arr, xcount, ocount, turnnum);
}
void gameloop(int xwins, int owins){
    int xcount = 0;//wins and game array
    int ocount = 0;
    int turnnum = 1;
    char game_arr[4][4]={{' ','A','B','C'},{'1',' ',' ',' '},{'2',' ',' ',' '},{'3',' ',' ',' '}};
    int* win_arr;
    printboard(game_arr);
    win_arr = game(game_arr, xcount, ocount, turnnum);
    xwins += win_arr[0];
    owins += win_arr[1];
    cout << "X Wins:" << xwins<<" and "<< "O wins:"<<owins<<" Play again?(y/n)";
    char answer;
    cin >> answer;//check if play again otherwise end
    if (answer == 'y'){
        gameloop(xwins, owins);
    }
    else{
        cout << "goodbye"<<endl;
    }
}
int main(){
    int xwins = 0;
    int owins = 0;
    gameloop(xwins, owins);
    return 0;
}
