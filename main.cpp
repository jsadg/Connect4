#include <iostream>
#include <stdlib.h>

void printBoard(char (&board)[6][7]);
void move(char (&board)[6][7], char symbol);
bool validMove(char (&board)[6][7], int move);
bool checkWin(char (&board)[6][7], int lastMove, char symbol);
bool checkDraw(char (&board)[6][7]);

int lastMove=0;

int main(){
    char board[6][7] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };
    char player1 = 'O';
    char player2 = 'X';
    bool end = false;


    while(!end){
        printBoard(board);
        move(board, player1);
        if(checkWin(board,lastMove,player1)){
            printBoard(board);
            std::cout << "Player 1 wins";
            end = true;
            break;
        }
        printBoard(board);
        move(board,player2);
        if(checkWin(board,lastMove,player2)){
            printBoard(board);
            std::cout << "Player 2 wins";
            end = true;
            break;
        }
        if(checkDraw(board)){
            printBoard(board);
            std::cout << "It is a draw";
            end = true;
            break;
        }
    }
    return 0;
}

void printBoard(char (&board)[6][7]){
    std::cout << " 1 2 3 4 5 6 7" << std::endl;
    for(int i=5;i>=0;i--){
        for(int j=0;j<7;j++){
            std::cout << "|" << board[i][j];
        }
        std::cout << "|" << std::endl;
    }
    std::cout << " - - - - - - -" << std::endl;
}

void move(char (&board)[6][7], char symbol){
    int choice = -1;
    while(!validMove(board, choice)){
        std::cout << "Select the row where you want to move";
        std::cin >> choice; 
        if(!std::cin){
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            choice=-1;
        }
    }
    choice--;
    for(int i=0;i<6;i++){
        if(board[i][choice] == ' '){
            board[i][choice] = symbol;
            break;
        }
    }
    lastMove = choice;
}

bool validMove(char (&board)[6][7], int move){
    if(move > 7 || move < 0){
        return false;
    }
    for(int i=0;i<6;i++){
        if(board[i][move] == ' '){
            return true;
        }
    }
    return false;
}

bool checkWin(char (&board)[6][7], int lastMove, char symbol){
    int numInARow=1;
    //Get vertical position
    int vertPos=0;
    while((vertPos+1)<=6 && board[vertPos+1][lastMove]!=' '){
        vertPos++;
    }
    //Check vertical win
    if(vertPos>=3){
        if(board[vertPos-1][lastMove]==symbol && board[vertPos-2][lastMove]==symbol && board[vertPos-3][lastMove]==symbol){
            return true;
        }
    }
    //Check horizontal win
    for(int i=1;i<=3;i++){
        if((lastMove-i)>=0 && board[vertPos][lastMove-i]==symbol){
            numInARow++;
        }
        else{
            break;
        }
    }
    for(int i=1;i<=3;i++){
        if((lastMove+i)<=7 && board[vertPos][lastMove+i]==symbol){
            numInARow++;
        }
        else{
            break;
        }
    }
    if(numInARow>=4){
        return true;
    }
    numInARow=1;
    //Check right diagonal win
    for(int i=1;i<=3;i++){
        if((lastMove-i)>=0 && (vertPos-i)>=0 && board[vertPos-i][lastMove-i]==symbol){
            numInARow++;
        }
        else{
            break;
        }
    }
    for(int i=1;i<=3;i++){
        if((lastMove+i)<=7 && (vertPos+i)<=6 && board[vertPos+i][lastMove+i]==symbol){
            numInARow++;
        }
        else{
            break;
        }
    }
    if(numInARow>=4){
        return true;
    }
    numInARow=1;
    //Check left diagonal win
    for(int i=1;i<=3;i++){
        if((lastMove-i)>=0 && (vertPos+i)<=6 && board[vertPos+i][lastMove-i]==symbol){
            numInARow++;
        }
        else{
            break;
        }
    }
    for(int i=1;i<=3;i++){
        if((lastMove+i)<=7 && (vertPos-i)>=0 && board[vertPos-i][lastMove+i]==symbol){
            numInARow++;
        }
        else{
            break;
        }
    }
    if(numInARow>=4){
        return true;
    }
    return false;
}

bool checkDraw(char (&board)[6][7])
{
    for(int i=0;i<6;i++){
        for(int j=0;j<7;j++){
            if(board[i][j]==' '){
                return false;
            }
        }
    }
    return true;
}