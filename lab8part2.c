#include <stdio.h>
#include <stdbool.h>
//#include "lab8part2lib.h" //for testing

void printBoard(char board[][26], int n){
	int i,j;
	
	//print initial row of column letter values ie abcdefg
	printf("  ");
	for(i = 0; i < n; i++){
		printf("%c",'a'+i);
	}
	printf("\n");
	
	
	for(i = 0; i < n; i++){
		//print column of row letter values ie abcdfge
		printf("%c ", 'a'+ i);
		
		//print values on board
		for(j = 0; j < n; j++){
			printf("%c", board[i][j]);
		}
		
		printf("\n");
	}
	
}

void boardInitialization(char board[][26], int n){
	int i, j;
	
	//set all values in array to U
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			board[i][j] = 'U';
		}
	}
	
	//initialize starting values
	board[n/2][n/2] = 'W';
	board[n/2][n/2-1] = 'B';
	board[n/2-1][n/2-1] = 'W';
	board[n/2-1][n/2] = 'B';
	
}

/**
 * Call this function to check if a position is in bounds
 *
 * @param n The size of the array that represents the current state of the game.
 * @param row The index of the row being looked at.
 * @param col The index of the column being looked at.
 */
bool positionInBounds(int n, int row, int col){
	
	bool inBounds = true;

	//check if the row and col are within the boundary n
	if(row < 0 || row >= n || col < 0 || col >= n){
		inBounds = false;
	}	
	
	return inBounds;
	
}

/**
 * Call this function to check if a move is legal
 *
 * @param board An array that represents the current state of the game.
 * @param n The size of the array that represents the current state of the game.
 * @param row The index of the row being looked at.
 * @param col The index of the column being looked at.
 * @param colour The colour of the piece whos turn it is.
 * @param deltaRow A number either -1, 0 or 1 that directs the direction to look in.
 * @param deltaCol A number either -1, 0 or 1 that directs the direction to look in.
 */

bool checkLegalInDirection(char board[][26], int n, int row, int col, 
						   char colour, int deltaRow, int deltaCol){
	
	//check in line for opposite colour -> if same colour then not legal direction
	
	int i;
	
	char currentColour = board[row][col];
	
	//check if a line can be started or not
	if(!positionInBounds(n,row+deltaRow, col+deltaCol) || currentColour != 'U'){
		return false;
	}
	
	currentColour = board[row+deltaRow][col+deltaCol];
	
	if(currentColour == 'U' || currentColour == colour){
		return false;
	}
	
	//loop down the line while in bounds
	for(i = 2; positionInBounds(n,row+deltaRow*i,col+deltaCol*i); i++){
		
		
		currentColour = board[row+deltaRow*i][col+deltaCol*i];
		
		//check for end of line and return results depending on if tile is U or the colour
		if(currentColour == 'U'){
			return false;
		}else if(currentColour == colour){
			return true;
		}
	}
	
	return false;
							
}


void flipTiles(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
	
	int i;
	
	//loop down line and flip tiles until you reach the end of the line
	for(i = 1; positionInBounds(n,row+deltaRow*i,col+deltaCol*i); i++){
		
		if(board[row+deltaRow*i][col+deltaCol*i] == 'U' || board[row+deltaRow*i][col+deltaCol*i] == colour ){
			break;
		}else{
			board[row+deltaRow*i][col+deltaCol*i] = colour;
		}
		
	}
	
}



//checks if a single move is valid at all
bool validMove(char board[][26], int n, int row, int col, char colour){
	
	int i, j;
	
	//check if tile can be used
	if(board[row][col] != 'U'){
		return false;
	}
	
	//loop through directions and check if line can be started
	for(i = -1; i <= 1; i++){
		
		for(j = -1; j <= 1; j++){
			
			if(checkLegalInDirection(board, n, row, col, colour, i, j)){
				//printf("VALID: %d %d, ", row,col);
				return true;
			}
			
		}
	}
	
	return false;

}

//returns true if the game is over
bool gameOver(char board[][26], int n){
	
	int i, j;
	//loop through board with validMove() for each colour
	
	//check if both players have no moves left
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
		
			if(validMove(board,n,i,j,'B') || validMove(board,n,i,j,'W')){
				return false;
			}
		}
	}
	
	return true;
	
}

//determine which player has most tiles on board
char checkWinner(char board[][26], int n){
	
	
	char winner;
	int i,j, numWhite = 0,numBlack = 0;
	
	//tally up each colour
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(board[i][j] == 'B'){
				numBlack++;
			}else if(board[i][j] == 'W'){
				numWhite++;
			}
		}
	}
	
	//check who won
	if(numBlack > numWhite){
		winner = 'B';
	}else if(numWhite > numBlack){
		winner = 'W';
	}else{
		//return 'T' if draw
		winner = 'T';
	}
	
	return winner;
}

//function that evaluates current board state
//assumes that state given has already had tiles flipped
int stateEval(char state[][26], int n, char maximizingPlayer){
	
	int i,j, evaluation = 0;
	
	//loop through all tiles and get difference in pieces
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(state[i][j] == maximizingPlayer){
				evaluation++;
			}else if(state[i][j] != 'U'){
				evaluation--;
			}
		}
	}
	
	return evaluation;
	
}

void makeMove(char state[][26], int n, int row, int col, char tileColour){
	
	int i, j;
	
	//make move and flip tiles
	for(i = -1; i <= 1; i++){
		for(j = -1; j <= 1; j++){
				
			//check directions that the move can go in then flip the tiles
			if(checkLegalInDirection(state, n, row, col, tileColour, i, j)){
				flipTiles(state,n,row,col,tileColour,i,j);
			}
					
		}
	}
				
	//flip current tile
	state[row][col] = tileColour;
}


int minimax(char state[][26], int depth, bool maximizingPlayer, int n, int alpha, int beta, char maxPlayer, char minPlayer){
	
	char cpyState[26][26];
	int eval, i, j;
	
	memcpy(cpyState, state, sizeof(char)*26*26);
	
	//check terminate conditions
	if(depth == 0 || gameOver(cpyState,n)){	
		//evaluate current state and return
		//printf("CURRENT STATE: \n");
		//printBoard(cpyState,n);
		return stateEval(cpyState, n, maxPlayer);
	}
	
	//either max or min depending on player
	if(maximizingPlayer){
		
		int maxEval = -100000;
		
		//look for valid moves and get their scores
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				
				memcpy(cpyState, state, sizeof(char)*26*26);
				
				if(validMove(cpyState,n,i,j,maxPlayer)){
					
					//make move on copied board and call minimax to get evaluation
					makeMove(cpyState, n, i, j, maxPlayer);
					
					eval = minimax(cpyState,depth-1,false,n, alpha, beta, maxPlayer,minPlayer);
					//printf("max eval: %d\n", eval);
					
					if(eval > maxEval){
						maxEval = eval;
					}
					
				    if(eval > alpha){
						alpha = eval;
					}
					
					if(beta <= alpha){
						break;
					}
				}
				
			}
		}
		
		return maxEval;
	}else{
		
		int minEval = 1000000;
		
		//look for valid moves and get their scores
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				
				memcpy(cpyState, state, sizeof(char)*26*26);				
				
				if(validMove(cpyState,n,i,j,minPlayer)){
					
					//printf("CURRENT STATE: \n");
					//printBoard(cpyState,n);
					
					//make move on copied board and call minimax to get evaluation
					makeMove(cpyState, n, i, j, minPlayer);
					
					eval = minimax(cpyState,depth-1,true,n,alpha,beta,maxPlayer,minPlayer);
					
					//printf("min eval: %d\n", eval);
					
					if(eval < minEval){
						minEval = eval;
					}
					
					if(eval < beta){
						beta = eval;
					}
					
					if(beta <= alpha){
						break;
					}
					
				}
				
			}
		}
		
		return minEval;
	}
	
	
	
	
}


int main(int argc, char **argv)
{
	int n,i,j, temp, highestRow = 0, highestCol = 0, highestScore = 0;
	
	bool valid = false, winnerFound = false, noValidMoves = false;
	
	char row, col;
	
	char computerColour, playerColour, currentColour = 'B', winner;
	
	char board[26][26]; 
	
	//prompt user for input on board size
	printf("Enter the board dimension: ");
	scanf("%d",&n);
	
	//get tile colour of computer
	printf("Computer plays (B/W): ");
	scanf(" %c", &computerColour);
	
	//set human player's colour
	if(computerColour == 'B'){
		playerColour = 'W';
	}else{
		playerColour = 'B';
	}
	
	//setup boards initial positions
	boardInitialization(board,n);
	
	//show board with initial positions
	printBoard(board, n);
	
	//game loop
	while(!winnerFound){
		
		//check to see whose turn it is
		if(currentColour == computerColour){
			
			noValidMoves = true;
			
			char cpyState[26][26]; 
			
			//evaluate spaces
			
			highestScore = -1000; //assume highest score is zero
			
			for(i = 0; i < n; i++){
				for(j = 0; j < n; j++){
					//check scores at each valid position
					memcpy(cpyState, board, sizeof(char)*26*26);
					
					if(validMove(board,n,i,j,computerColour)){
						noValidMoves = false;
						makeMove(cpyState,n,i,j,computerColour);
						//printf("INITIAL STATE:\n");
						//printBoard(cpyState,n);
						temp = minimax(cpyState,3,false, n, -100000,100000, computerColour, playerColour);
						if((i == 0 || i == n-1) && (j == 0 || j == n-1)){
							temp += 2;
						}else if((i > 1 && i < n-2) && (j == 0 || j == n-1)){
							temp++;
						}else if(!((i > 1 && i < n-2) && (j > 1 && j < n-2))){
							temp--;
						}
						//printf("EVAL: %d\n", temp);
						//check if there is a higher score position then set equal to
						if(temp > highestScore){
							highestRow = i;
							highestCol = j;
							highestScore = temp;
						}
					}
					
				}
			}
			
			//check for no valid moves
			if(noValidMoves){
				printf("%c player has no valid move.\n",computerColour);
			}else{
			
				//make move and flip tiles
				for(i = -1; i <= 1; i++){
					for(j = -1; j <= 1; j++){
						
						//check directions that the move can go in then flip the tiles
						if(checkLegalInDirection(board, n, highestRow, highestCol, computerColour, i, j)){
							flipTiles(board,n,highestRow,highestCol,computerColour,i,j);
						}
					
					}
				}
				
				//flip current tile
				board[highestRow][highestCol] = computerColour;
			
				//show user computers move
				printf("Computer places %c at %c%c.\n", computerColour, highestRow+'a', highestCol+'a');
				printBoard(board,n);
			}
			//change turns
			currentColour = playerColour;
			
		}else{
			noValidMoves = true;
			//check if there are no valid moves
			for(i = 0; i < n; i++){
				for(j = 0; j < n; j++){
		
					if(validMove(board,n,i,j,playerColour)){
						noValidMoves = false;
					}
				}
			}
	
			
			if(!noValidMoves){
				//prompt user for input
				printf("Enter move for colour %c (RowCol): ", playerColour);
				scanf(" %c%c", &row,&col);
				char cpyState[26][26];
				
				memcpy(cpyState, board, sizeof(char)*26*26);
				
				
				//findSmartestMove(cpyState, n, playerColour, &row, &col);
				//printf("Testing AI move (row, col): %c%c\n", row +'a', col+'a');
				
			 	row -= 'a';
				col -= 'a';
				
				valid = false;
				
				//make move and flip tiles
				for(i = -1; i <= 1; i++){
					for(j = -1; j <= 1; j++){
					
						if(checkLegalInDirection(board, n, row, col, playerColour, i, j)){
							valid = true;
							flipTiles(board,n,row,col,playerColour,i,j);
						}
					
					}
				}
				
				//flip tile if valid else tell user invalid move
				if(valid){
					board[row][col] = playerColour;
				}else{
					printf("Invalid move.\n");
					printf("%c player wins.", computerColour);
					return 0;
				}
				printBoard(board,n);
			}else{
				printf("%c player has no valid move.\n", playerColour);
			}
			//change turns
			currentColour = computerColour;
		}
		
		//check for game over
		if(gameOver(board,n)){
			winnerFound = true;
		}
		
		
	}
	
	//determine winner
	winner = checkWinner(board,n);
	if( winner == 'T'){
		printf("Draw!");
	}else{
		printf("%c player wins.", winner);
	}	
	
	return 0;
}
