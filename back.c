#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct piece
{
    int position;
    bool bearedOff;
    bool emptyPiece;
    bool inBar;
    bool blackPiece;
} piece;

typedef struct triangle
{
    piece pcs[15];
    int pcCounter;

} triangle;

typedef struct board
{
    triangle triangles[24];
    piece bar[15];
    int numBar;
    bool playerTurn; // if true, player1; if false, player2
    int nStake;
    bool turnStake;
} board;

int getMax(board *boardPtr, int a, int b)
{
    // assumption: a < b
    // use case: triangle 12 -> 23
    // use case 2 : triangle 0 - > triangle 11
    // it gets the max value of pieces from triangle a to triangle b
    // triangle 0: 0
    // triangle 1: 1
    // triangle 2: 2
    // triangle 3: 0
    // triangle 4: 5
    // triangle 6: 1
    // triangle 7 : 3
    // return shoudl be 5
    // hint 1: declare a max variable and set it to 0
    // hint 2: iterate through the triangles, compare pcCounter to max
    // hint 3: if pcCounter > max, set max to pcCounter
    int max_count = boardPtr->triangles[a].pcCounter;

    for (int i = a; i < b; i++)
    {
        if (boardPtr->triangles[i].pcCounter > max_count)
            max_count = boardPtr->triangles[i].pcCounter;
    }
    return max_count;
}

void printContents(board *boardPtr)
{
    printf("Player turn: %s\n", boardPtr->playerTurn ? "true" : "false");
    printf("Number of pieces in bar: %d\n", boardPtr->numBar);
    printf("Number of points staked: %d\n", boardPtr->nStake);
    printf("Turn staked: %s\n", boardPtr->turnStake ? "true" : "false");

    printf("Bar: \n");
    for (int i = 0; i < 15; i++)
    {
        printf("Piece %d: position=%d, bearedOff=%s, emptyPiece=%s, inBar=%s, "
               "blackPiece=%s\n",
               i, boardPtr->bar[i].position,
               boardPtr->bar[i].bearedOff ? "true" : "false",
               boardPtr->bar[i].emptyPiece ? "true" : "false",
               boardPtr->bar[i].inBar ? "true" : "false",
               boardPtr->bar[i].blackPiece ? "true" : "false");
    }

    printf("triangles: \n");
    for (int i = 0; i < 24; i++)
    {
        printf("triangle %d: \n", i);
        printf("Number of pieces: %d\n", boardPtr->triangles[i].pcCounter);
        for (int j = 0; j < 15; j++)
        {
            printf("Piece %d: posi tion=%d, bearedOff=%s, emptyPiece=%s, inBar=%s, "
                   "blackPiece=%s\n",
                   j, boardPtr->triangles[i].pcs[j].position,
                   boardPtr->triangles[i].pcs[j].bearedOff ? "true" : "false",
                   boardPtr->triangles[i].pcs[j].emptyPiece ? "true" : "false",
                   boardPtr->triangles[i].pcs[j].inBar ? "true" : "false",
                   boardPtr->triangles[i].pcs[j].blackPiece ? "true" : "false");
        }
    }
}

void printBoard(board *boardPtr)
{

    for (int i = 12; i < 24; i++)
    {
        printf("|%d |", i);
    }
    printf("\n");
    for (int i = 0; i < getMax(boardPtr, 12, 23); i++)
    {
        for (int j = 12; j < 24; j++)
        {
            if (i < boardPtr->triangles[j].pcCounter)
            {
                if (boardPtr->triangles[j].pcs[i].blackPiece == true)
                {
                    printf("| X |");
                }
                else
                {

                    printf("| O |");
                }
            }
            else
            {
                printf("|   |");
            }
        }
        printf("\n");
    }
    printf("+----------------------------------------------------------+\n");
    for (int i = 0; i < getMax(boardPtr, 0, 11); i++)
    {
        for (int j = 11; j >= 0; j--)
        {
            if (i < boardPtr->triangles[j].pcCounter)
            {
                if (boardPtr->triangles[j].pcs[i].blackPiece == true)
                {
                    printf("| X |");
                }
                else
                {
                    printf("| O |");
                }
            }
            else
            {
                printf("|   |");
            }
        }
        printf("\n");
    }
    for (int i = 11; i >= 0; i--)
    {
        if (i < 10)
        {
            printf("| %d |", i);
        }
        else
        {
            printf("|%d |", i);
        }
    }
    printf("\n");
}

void blotPiece(int triangleIndex, board *boardPtr)
{
    if (boardPtr->triangles[triangleIndex].pcCounter == 0)
    {
        printf("Error: triangle at index %d is empty\n", triangleIndex);
        return;
    }

    // remove the last piece in the triangle and increment the bar counter
    boardPtr->triangles[triangleIndex].pcs[boardPtr->triangles[triangleIndex].pcCounter - 1].emptyPiece = true;
    boardPtr->triangles[triangleIndex].pcCounter--;
    boardPtr->numBar++;

    // adding the pieceToTheBar;
    boardPtr->bar[boardPtr->numBar - 1].emptyPiece = false;
    boardPtr->bar[boardPtr->numBar - 1].inBar = true;
    boardPtr->bar[boardPtr->numBar - 1].blackPiece = false ? boardPtr->playerTurn : true;
    boardPtr->bar[boardPtr->numBar - 1].position = -1;
    boardPtr->bar[boardPtr->numBar - 1].bearedOff = false;
}

void initializeBoardValues(board *boardPtr)
{
    // initialize pieces to empty and -1;
    // set position to -1
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 15; j++)
        {

            boardPtr->triangles[i].pcs[j].bearedOff = false;
            boardPtr->triangles[i].pcs[j].position = -1;
            boardPtr->triangles[i].pcs[j].emptyPiece = true;
            boardPtr->triangles[i].pcs[j].inBar = false;
            boardPtr->triangles[i].pcs[j].blackPiece = false;
        }
    }
    // set bearedOff to false

    // set emptyPiece to true

    // set inBar to false

    // set blackPiece to false

    // initialize all pieces in bar to empty and -1
    for (int i = 0; i < 15; i++)
    {
        boardPtr->bar[i].bearedOff = false;
        boardPtr->bar[i].emptyPiece = true;
        boardPtr->bar[i].inBar = true;
        boardPtr->bar[i].blackPiece = false;
    }
    boardPtr->turnStake = false;
    boardPtr->nStake = 64;
    boardPtr->playerTurn = true;
    boardPtr->numBar = 0;

    // set turnStake to false
    // set nStake = 64
    // set playerTurn to false
    // set numBar to 0

    // set all pcCounters to 0
    for (int i = 0; i < 24; i++)
    {
        boardPtr->triangles[i].pcCounter = 0;
    }

    int initialPos[2][24] = {{0, 0, 0, 0, 0, 5, 0, 3, 0, 0, 0, 0,
                              5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, // black
                             {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
                              0, 0, 0, 0, 3, 0, 5, 0, 0, 0, 0, 0}}; // white

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            if (boardPtr->triangles[j].pcCounter > 0)
            {
                continue;
            }
            else
            {
                boardPtr->triangles[j].pcCounter = initialPos[i][j];
            }
            for (int k = 0; k < initialPos[i][j]; k++)
            {
                if (i == 0)
                {
                    boardPtr->triangles[j].pcs[k].bearedOff = false;
                    boardPtr->triangles[j].pcs[k].blackPiece = true;
                    boardPtr->triangles[j].pcs[k].emptyPiece = false;
                    boardPtr->triangles[j].pcs[k].inBar = false;
                    boardPtr->triangles[j].pcs[k].position = j;
                }
                else
                {
                    boardPtr->triangles[j].pcs[k].bearedOff = false;
                    boardPtr->triangles[j].pcs[k].blackPiece = false;
                    boardPtr->triangles[j].pcs[k].emptyPiece = false;
                    boardPtr->triangles[j].pcs[k].inBar = false;
                    boardPtr->triangles[j].pcs[k].position = j;
                }
            }
        }
    }

    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 15; j++)
        {

            if (boardPtr->triangles[i].pcCounter > 0 && j < boardPtr->triangles[i].pcCounter)
            {
            }
            else
            {
                j = 15;
            }
        }
    }
    // set it to the appropriate values - INITIAL POSITIONS
    // position: 0, qty: 2 pcs, blackPiece = ?
    // position : 5, qty: 5, blackPiece = ?
}
void rolldice(int dice[])
{
    dice[0] = rand() % 6 + 1;
    dice[1] = rand() % 6 + 1;
}

// player turn
// piece in board
// piece position
// dice
// piece in bar
// piece beared off

bool checkTriangleOpenPoint(int amtToMove, board *boardPtr, int pcPosition)
{
    // if black, final position will be pcPosition - amtToMove
    // else, final position will be pcPosition + amtToMove
    // check if final position is open and has no enemy pieces
    // and if open point has the same pieces

    int finalPosition;
    if (boardPtr->playerTurn == true)
    {
        finalPosition = pcPosition - amtToMove;
    }
    else
    {
        finalPosition = pcPosition + amtToMove;
    }

    if (boardPtr->triangles[finalPosition].pcCounter == 0)
    {
        return true;
    }
    else if (boardPtr->triangles[finalPosition].pcCounter > 0)
    {
        if (boardPtr->triangles[finalPosition].pcs[0].blackPiece == boardPtr->playerTurn)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// function checks if selected piece is valid
bool checkPieceOwner(board *boardPtr, int pcPosition)
{
    triangle t = boardPtr->triangles[pcPosition];
    for (int i = t.pcCounter; i >= 0; i--)
    {
        if (boardPtr->triangles[pcPosition].pcs[i].emptyPiece != true)
        {
            if (boardPtr->playerTurn == true && t.pcs[i].blackPiece == true)
            {
                return true;
            }
            else if (boardPtr->playerTurn == false && t.pcs[i].blackPiece == false)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

// function
// purpose: move a piece to another position AND set the oldPosition to empty
// parameters: pcPosition, finalPosition, boardPtr
// return void
void movePiece(int pcPosition, int finalPosition, board *boardPtr)
{
    printf("mem of boardPtr is %p\n", boardPtr);
    // move pcPosition and remove previous piece
    if (boardPtr->playerTurn == true)
    {
        printf("Moving black piece at %d to %d\n", pcPosition, finalPosition);
        // getting old values
        int count = boardPtr->triangles[pcPosition].pcCounter;

        // copying
        int newCount = boardPtr->triangles[finalPosition].pcCounter;
        printf("new count is %d\n", newCount);
        boardPtr->triangles[finalPosition].pcs[newCount].position = finalPosition;
        boardPtr->triangles[finalPosition].pcs[newCount].emptyPiece = false;
        boardPtr->triangles[finalPosition].pcs[newCount].inBar = false;
        boardPtr->triangles[finalPosition].pcs[newCount].blackPiece = true;
        boardPtr->triangles[finalPosition].pcs[newCount].bearedOff = false;
        boardPtr->triangles[finalPosition].pcCounter++;
        printf("new count is %d\n", boardPtr->triangles[finalPosition].pcCounter);

        // deleting old values
        printf("old count is %d\n", count);
        boardPtr->triangles[pcPosition].pcs[count - 1].position = -1;
        boardPtr->triangles[pcPosition].pcs[count - 1].bearedOff = false;
        boardPtr->triangles[pcPosition].pcs[count - 1].emptyPiece = true;
        boardPtr->triangles[pcPosition].pcs[count - 1].inBar = false;
        boardPtr->triangles[pcPosition].pcs[count - 1].blackPiece = false;
        boardPtr->triangles[pcPosition].pcCounter--;
        printf("old count is %d\n", boardPtr->triangles[pcPosition].pcCounter);
    }
    else
    {
        // getting old values
        int count = boardPtr->triangles[pcPosition].pcCounter;
      
        // copying
        int newCount = boardPtr->triangles[finalPosition].pcCounter;
        boardPtr->triangles[finalPosition].pcs[newCount].position = finalPosition;
        boardPtr->triangles[finalPosition].pcs[newCount].bearedOff = false;
        boardPtr->triangles[finalPosition].pcs[newCount].emptyPiece = false;
        boardPtr->triangles[finalPosition].pcs[newCount].inBar = false;
        boardPtr->triangles[finalPosition].pcs[newCount].blackPiece = false;
        boardPtr->triangles[finalPosition].pcCounter++;

        // deleting old values
        boardPtr->triangles[pcPosition].pcs[count - 1].position = -1;
        boardPtr->triangles[pcPosition].pcs[count - 1].bearedOff = false;
        boardPtr->triangles[pcPosition].pcs[count - 1].emptyPiece = true;
        boardPtr->triangles[pcPosition].pcs[count - 1].inBar = false;
        boardPtr->triangles[pcPosition].pcs[count - 1].blackPiece = false;
        boardPtr->triangles[pcPosition].pcCounter--;
    }
}

bool checkIfPieceInTriangleCanBeEaten(int amtToMove, board *boardPtr, int piecePosition)
{
    int finalPosition = 0;
    if (boardPtr->playerTurn == true)
    {
        finalPosition = piecePosition - amtToMove;
        if (boardPtr->triangles[finalPosition].pcCounter == 1 && boardPtr->triangles[finalPosition].pcs[0].blackPiece == false)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        finalPosition = piecePosition + amtToMove;
        if (boardPtr->triangles[finalPosition].pcCounter == 1 && boardPtr->triangles[finalPosition].pcs[0].blackPiece == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void movePieceChoice(board *boardPtr, int dice[2])
{
    int choice;

    do
    {
        printf("You rolled a %d and %d\n", dice[0], dice[1]);
        printf("Move one piece: \n");
        printf("1.%d positions\n", dice[0] + dice[1]);
        if (dice[0] == dice[1])
        {
            printf("2.%d positions\n", dice[0] * 4);
        }
        printf("Move two pieces: \n");
        printf("3. One piece in %d positions, the other in %d positions\n", dice[0], dice[1]);
        scanf("%d", &choice);
        if (choice < 1)
        {
            printf("Invalid choice, try again\n");
        }
        else if (choice > 3)
        {
            printf("Invalid choice, try again\n");
        }
        else if (choice == 2 && dice[0] != dice[1])
        {
            printf("Invalid choice, try again\n");
        }
    } while ((choice < 1 || choice > 3) || (choice == 2 && dice[0] != dice[1]));

    if (choice == 1)
    {
        int pcPosition;
        int t = -1;
        do
        {
            printf("Which piece do you want to move %d positions?\n", dice[0] + dice[1]);
            scanf("%d", &pcPosition);
            if (pcPosition >= 0 && pcPosition <= 23)
            { // checking if the position is within the bounds of the board 0-23
                if (checkTriangleOpenPoint(dice[0] + dice[1], boardPtr, pcPosition) == true && checkPieceOwner(boardPtr, pcPosition) == true)
                {
                    t = 1;
                    int finalPos = 0;
                    if (boardPtr->playerTurn == true)
                    {
                        printf("in here1\n");
                        finalPos = pcPosition - (dice[0] + dice[1]);
                    }
                    else
                    {
                        printf("in here2\n");
                        finalPos = pcPosition + (dice[0] + dice[1]);
                    }

                    if (finalPos >= 0 && finalPos <= 23)
                    {
                        movePiece(pcPosition, finalPos, boardPtr);
                        boardPtr->playerTurn = !boardPtr->playerTurn;
                    }
                    else
                    {
                        printf("Invalid position, try again\n");
                    }

                    // checks if triangle is an open point -> which means there are no enemy pieces
                    // also, it checks if the piece belongs to the current player
                }
                else if (checkTriangleOpenPoint(dice[0] + dice[1], boardPtr, pcPosition) == false && checkPieceOwner(boardPtr, pcPosition) == true && checkIfPieceInTriangleCanBeEaten(dice[0] + dice[1], boardPtr, pcPosition) == true)
                {
                    t = 1;
                    int finalPos = 0;
                    if (boardPtr->playerTurn == true)
                    {
                        printf("in here1\n");
                        finalPos = pcPosition - (dice[0] + dice[1]);
                    }
                    else
                    {
                        printf("in here2\n");
                        finalPos = pcPosition + (dice[0] + dice[1]);
                    }

                    if (finalPos >= 0 && finalPos <= 23)
                    {
                        blotPiece(finalPos, boardPtr);
                        movePiece(pcPosition, finalPos, boardPtr);
                        boardPtr->playerTurn = !boardPtr->playerTurn;
                    }
                    else
                    {
                        printf("Invalid position, try again\n");
                    }
                }
                else if (checkTriangleOpenPoint(dice[0] + dice[1], boardPtr, pcPosition) == false && checkPieceOwner(boardPtr, pcPosition) == true)
                {
                    printf("The piece is yours but the position that you are trying to move to is not an open point. Try again.\n");
                }
                else if (checkTriangleOpenPoint(dice[0] + dice[1], boardPtr, pcPosition) == true && checkPieceOwner(boardPtr, pcPosition) == false)
                {
                    printf("The position is open but either there are no pieces in the position or it does not belong to you. Try again.\n");
                }
                else
                {
                    printf("The position is not open and you are trying to move a piece that does not belong to you.\n");
                }
            }
        } while (t == -1);
    }
    else if (choice == 2)
    {
        int pcPosition;
        int t = -1;
        int k = 4;
        do
        {
            printf("Which piece do you want to move %d positions?\n", dice[0] * k);
            scanf("%d", &pcPosition);
            if (pcPosition >= 0 && pcPosition <= 23)
            { // checking if the position is within the bounds of the board 0-23
                if (checkTriangleOpenPoint(dice[0] * k, boardPtr, pcPosition) == true && checkPieceOwner(boardPtr, pcPosition) == true)
                {
                    t = 1;
                    int finalPos = 0;
                    if (boardPtr->playerTurn == true)
                    {
                        printf("in here1\n");
                        finalPos = pcPosition - (dice[0] * k);
                    }
                    else
                    {
                        printf("in here2\n");
                        finalPos = pcPosition + (dice[0] * k);
                    }
                    if (finalPos >= 0 && finalPos <= 23)
                    {
                        movePiece(pcPosition, finalPos, boardPtr);
                        boardPtr->playerTurn = !boardPtr->playerTurn;
                    }
                    else
                    {
                        t = -1;
                        printf("Invalid position, try again\n");
                    }

                    // checks if triangle is an open point -> which means there are no enemy pieces
                    // also, it checks if the piece belongs to the current player
                }
                else if (checkTriangleOpenPoint(dice[0] * k, boardPtr, pcPosition) == false && checkPieceOwner(boardPtr, pcPosition) == true && checkIfPieceInTriangleCanBeEaten(dice[0] * k, boardPtr, pcPosition) == true)
                {
                    t = 1;
                    int finalPos = 0;
                    if (boardPtr->playerTurn == true)
                    {
                        printf("in here1\n");
                        finalPos = pcPosition - (dice[0] * k);
                    }
                    else
                    {
                        printf("in here2\n");
                        finalPos = pcPosition + (dice[0] * k);
                    }
                    if (finalPos >= 0 && finalPos <= 23)
                    {
                        blotPiece(finalPos, boardPtr);
                        movePiece(pcPosition, finalPos, boardPtr);
                        boardPtr->playerTurn = !boardPtr->playerTurn;
                    }
                    else
                    {
                        t = -1;
                        printf("Invalid position, try again\n");
                    }
                }
                else if (checkTriangleOpenPoint(dice[0] * k, boardPtr, pcPosition) == false && checkPieceOwner(boardPtr, pcPosition) == true)
                {
                    printf("The piece is yours but the position that you are trying to move to is not an open point. Try again.\n");
                    k--;
                }
                else if (checkTriangleOpenPoint(dice[0] * k, boardPtr, pcPosition) == true && checkPieceOwner(boardPtr, pcPosition) == false)
                {
                    printf("The position is open but either there are no pieces in the position or it does not belong to you. Try again.\n");
                }
                else
                {
                    printf("The position is not open and you are trying to move a piece that does not belong to you.\n");
                }
            }
        } while (t == -1);
    }
    else if (choice == 3)
    {
        int pcPosition1;
        int pcPosition2;
        int t = -1; // t is used to check if the user has entered a valid position
        do
        {
            printf("old dice[0] value: %d\n", dice[0]);
            printf("old dice[1] value: %d\n", dice[1]);

            if (dice[0] < dice[1])
            {
                int temp = dice[0];
                dice[0] = dice[1];
                dice[1] = temp;
            }
            printf("new dice[0] value: %d\n", dice[0]);
            printf("new dice[1] value: %d\n", dice[1]);
            printf("Which piece do you want to move %d positions?\n", dice[0]);
            scanf("%d", &pcPosition1);
            printf("Which piece do you want to move with %d positions\n", dice[1]);
            scanf("%d", &pcPosition2);
            if (pcPosition1 >= 0 && pcPosition1 <= 23 && pcPosition2 >= 0 && pcPosition2 <= 23)
            {
                //checks if pcPosition1 is trying to move to an open point and if the piece belongs to the current player
                if (checkTriangleOpenPoint(dice[0], boardPtr, pcPosition1) == true && checkPieceOwner(boardPtr, pcPosition1) == true)
                {
                    //checks if pcPosition2 is trying to move to an open point and if the piece belongs to the current player
                    if (checkTriangleOpenPoint(dice[1], boardPtr, pcPosition2) == true && checkPieceOwner(boardPtr, pcPosition2) == true)
                    {
                        t = 1;
                        int finalPos1 = 0;
                        int finalPos2 = 0;
                        if (boardPtr->playerTurn == true)
                        {
                            printf("in here1\n");
                            finalPos1 = pcPosition1 - dice[0];
                            finalPos2 = pcPosition2 - dice[1];
                        }
                        else
                        {
                            printf("in here2\n");
                            finalPos1 = pcPosition1 + dice[0];
                            finalPos2 = pcPosition2 + dice[1];
                        }
                        if (finalPos1 >= 0 && finalPos1 <= 23 && finalPos2 >= 0 && finalPos2 <= 23)
                        {
                            movePiece(pcPosition1, finalPos1, boardPtr);
                            movePiece(pcPosition2, finalPos2, boardPtr);
                            boardPtr->playerTurn = !boardPtr->playerTurn;
                        }
                        else
                        {
                            printf("Invalid position, try again\n");
                        }
                    } //

                    //pcPosition1 moves to an empty point, pcPosition2 eats a piece                    
                    else if(checkTriangleOpenPoint(dice[1], boardPtr, pcPosition2) == false && checkPieceOwner(boardPtr, pcPosition2) == true && checkIfPieceInTriangleCanBeEaten(dice[1], boardPtr, pcPosition2)){
                        t = 1;
                        int finalPos1 = 0;
                        int finalPos2 = 0;
                        if (boardPtr->playerTurn == true)
                        {
                            printf("in here1\n");
                            finalPos1 = pcPosition1 - dice[0];
                            finalPos2 = pcPosition2 - dice[1];
                        }
                        else
                        {
                            printf("in here2\n");
                            finalPos1 = pcPosition1 + dice[0];
                            finalPos2 = pcPosition2 + dice[1];
                        }
                        if (finalPos1 >= 0 && finalPos1 <= 23 && finalPos2 >= 0 && finalPos2 <= 23)
                        {
                            blotPiece(finalPos2, boardPtr);
                            movePiece(pcPosition1, finalPos1, boardPtr);
                            movePiece(pcPosition2, finalPos2, boardPtr);
                            boardPtr->playerTurn = !boardPtr->playerTurn;
                        }
                        else
                        {
                            printf("Invalid position, try again\n");
                        }

                    }
                    //checks if pcPosition2 is trying to move to a closed point but since pcPosition1 is the greater piece, we will move pcPos1 only
                    else if (checkTriangleOpenPoint(dice[1], boardPtr, pcPosition2) == false && checkPieceOwner(boardPtr, pcPosition2) == true)
                    {
                        printf("Since you cannot move both pieces, we move the piece with the higher positions\n");
                        t = 1;
                        int finalPos1 = 0;

                        if (boardPtr->playerTurn == true)
                        {
                            printf("in here1\n");
                            finalPos1 = pcPosition1 - dice[0];
                        }
                        else
                        {
                            printf("in here2\n");
                            finalPos1 = pcPosition1 + dice[0];
                        }
                        if (finalPos1 >= 0 && finalPos1 <= 23)
                        {
                            movePiece(pcPosition1, finalPos1, boardPtr);
                            boardPtr->playerTurn = !boardPtr->playerTurn;
                        }
                        else
                        {
                            printf("Invalid position, try again\n");
                        }
                    }
                    else if (checkTriangleOpenPoint(dice[1], boardPtr, pcPosition2) == true && checkPieceOwner(boardPtr, pcPosition2) == false)
                    {
                        printf("The position is open but either there are no pieces in the position or it does not belong to you. Try again.\n");
                    }
                    else
                    {
                        printf("The position is not open and you are trying to move a piece that does not belong to you.\n");
                    }
                }
                //if pcPosition1 is trying to move to a piece that is not an open point but it can eat a piece
                else if (checkTriangleOpenPoint(dice[0], boardPtr, pcPosition1) == false && checkPieceOwner(boardPtr, pcPosition1) == true && checkIfPieceInTriangleCanBeEaten(dice[0], boardPtr, pcPosition1) == true)
                {
                    //case 1: if pcPosition1 can eat a piece but pcPosition2 can just move to an empty spot
                    if (checkTriangleOpenPoint(dice[1], boardPtr, pcPosition2) == true && checkPieceOwner(boardPtr, pcPosition2) == true){
                        t = 1;
                        int finalPos1 = 0;
                        int finalPos2 = 0;
                        if (boardPtr->playerTurn == true)
                        {
                            printf("in here1\n");
                            finalPos1 = pcPosition1 - dice[0];
                            finalPos2 = pcPosition2 - dice[1];
                        }
                        else
                        {
                            printf("in here2\n");
                            finalPos1 = pcPosition1 + dice[0];
                            finalPos2 = pcPosition2 + dice[1];
                        }
                        if (finalPos1 >= 0 && finalPos1 <= 23 && finalPos2 >= 0 && finalPos2 <= 23)
                        {
                            blotPiece(finalPos1, boardPtr);
                            movePiece(pcPosition1, finalPos1, boardPtr);
                            movePiece(pcPosition2, finalPos2, boardPtr);
                            boardPtr->playerTurn = !boardPtr->playerTurn;
                        }
                        else
                        {
                            printf("Invalid position, try again\n");
                        }

                    }
                    //case 2: if pcPosition1 can eat a piece and pcPosition2 can ALSO eat another piece
                    else if (checkTriangleOpenPoint(dice[1], boardPtr, pcPosition2) == false && checkPieceOwner(boardPtr, pcPosition2) == true && checkIfPieceInTriangleCanBeEaten(dice[1], boardPtr, pcPosition2) == true){
                        t = 1;
                        int finalPos1 = 0;
                        int finalPos2 = 0;
                        if (boardPtr->playerTurn == true)
                        {
                            printf("in here1\n");
                            finalPos1 = pcPosition1 - dice[0];
                            finalPos2 = pcPosition2 - dice[1];
                        }
                        else
                        {
                            printf("in here2\n");
                            finalPos1 = pcPosition1 + dice[0];
                            finalPos2 = pcPosition2 + dice[1];
                        }
                        if (finalPos1 >= 0 && finalPos1 <= 23 && finalPos2 >= 0 && finalPos2 <= 23)
                        {
                            blotPiece(finalPos1, boardPtr);
                            blotPiece(finalPos2, boardPtr);
                            movePiece(pcPosition1, finalPos1, boardPtr);
                            movePiece(pcPosition2, finalPos2, boardPtr);
                            boardPtr->playerTurn = !boardPtr->playerTurn;
                        }
                        else
                        {
                            printf("Invalid position, try again\n");
                        }

                    }
                    //case 3: pcPosition1 can eat a piece but pcPosition2 is trying to move to a position that is not open
                    else if(checkTriangleOpenPoint(dice[1], boardPtr, pcPosition2) == false && checkPieceOwner(boardPtr, pcPosition2) == true && checkIfPieceInTriangleCanBeEaten(dice[1], boardPtr, pcPosition2) == false){
                        printf("Since you cannot move both pieces, we move the piece with the higher positions\n");
                        t = 1;
                        int finalPos1 = 0;

                        if (boardPtr->playerTurn == true)
                        {
                            printf("in here1\n");
                            finalPos1 = pcPosition1 - dice[0];
                        }
                        else
                        {
                            printf("in here2\n");
                            finalPos1 = pcPosition1 + dice[0];
                        }
                        if (finalPos1 >= 0 && finalPos1 <= 23)
                        {
                            blotPiece(finalPos1, boardPtr);
                            movePiece(pcPosition1, finalPos1, boardPtr);
                            boardPtr->playerTurn = !boardPtr->playerTurn;
                        }
                        else
                        {
                            printf("Invalid position, try again\n");
                        }
                    }

                }
                else if (checkTriangleOpenPoint(dice[0], boardPtr, pcPosition1) == false && checkPieceOwner(boardPtr, pcPosition1) == true)
                {
                    printf(" The piece is yours but the position that you are trying to move to is not an open point. Try again.\n");
                }
                else if (checkTriangleOpenPoint(dice[0], boardPtr, pcPosition1) == true && checkPieceOwner(boardPtr, pcPosition1) == false)
                {
                    printf("The position is open but either there are no pieces in the position or it does not belong to you. Try again.\n");
                }
                else
                {
                    printf("The position is not open and you are trying to move a piece that does not belong to you.\n");
                }
            }

        } while (t == -1);
    }
    
}

bool checkIfCanBeEaten(board *boardPtr, int pcPosition)
{
    if (boardPtr->triangles[pcPosition].pcCounter == 1)
    {
        if (boardPtr->playerTurn != boardPtr->triangles[pcPosition].pcs[0].blackPiece)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool checkIfPlayerCanStartBearingOff(board * boardPtr){
    int countOfPiecesInQuadrant = 0;
    int countPiecesOfPlayer = 0;

    if (boardPtr->playerTurn){
        //we count the pieces that are in the quadrant
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < boardPtr->triangles[i].pcCounter; j++){
                if(boardPtr->triangles[i].pcs[j].blackPiece == true && boardPtr->triangles[i].pcs[j].inBar == false && boardPtr->triangles[i].pcs[j].bearedOff == false){

                    countOfPiecesInQuadrant++;
                }
            }
        }
        //we count the pieces that are in the board
        for(int i = 0; i < 24; i++){
            for(int j = 0; j < boardPtr->triangles[i].pcCounter; j++){
                if(boardPtr->triangles[i].pcs[j].blackPiece == true && boardPtr->triangles[i].pcs[j].inBar == false && boardPtr->triangles[i].pcs[j].bearedOff == false){
                    countPiecesOfPlayer++;
                }
            }
        }
        if (countOfPiecesInQuadrant == countPiecesOfPlayer){
            return true;
        }
        else{
            return false;
        }
    }else{
        //we count the pieces that are in the quadrant
        for(int i = 18; i < 24; i++){
            for(int j = 0; j < boardPtr->triangles[i].pcCounter; j++){
                if(boardPtr->triangles[i].pcs[j].blackPiece == false && boardPtr->triangles[i].pcs[j].inBar == false && boardPtr->triangles[i].pcs[j].bearedOff == false){
                    countOfPiecesInQuadrant++;
                }
            }
        }
        //we count the pieces that are in the board
        for(int i = 0; i < 24; i++){
            for(int j = 0; j < boardPtr->triangles[i].pcCounter; j++){
                if(boardPtr->triangles[i].pcs[j].blackPiece == false && boardPtr->triangles[i].pcs[j].inBar == false && boardPtr->triangles[i].pcs[j].bearedOff == false){
                    countPiecesOfPlayer++;
                }
            }
        }
        if (countOfPiecesInQuadrant == countPiecesOfPlayer){
            return true;
        }
        else{
            return false;
        }
    }
    return false;

}

void bearingOffStage(board * boardPtr){
    if (boardPtr->playerTurn){
        printf("You are now in the bearing off stage.\n");
        printf("Roll dice to start bearing off? \n");
        printf("1. Yes\n");
        printf("2. No\n");
        int choice = 0;
        scanf("%d", &choice);
        if (choice == 1){
            int tempDice[2];
            rolldice(tempDice);
            int initialPoint = tempDice[0];
            int copy = initialPoint;
            int max = 5;
            int min = 0;
            bool hitUpperLimit = false;
            bool stopWhile = false;
            while((boardPtr->triangles[initialPoint].pcCounter == 0 || boardPtr->triangles[initialPoint].pcs[0].blackPiece == false) && stopWhile == false){
                
                if (hitUpperLimit == true){
                    initialPoint--;
                }else{
                    initialPoint++;
                }

                if (initialPoint > max){
                    hitUpperLimit = true;
                    initialPoint = copy;
                }else{
                    if (initialPoint < min){
                        stopWhile = true;
                    }
                }
            }
            if (initialPoint >= min && initialPoint <= max){
                int pcPosition = initialPoint;
                int pcsCounter = boardPtr->triangles[pcPosition].pcCounter;
                int pcIndex = pcsCounter - 1;
                boardPtr->triangles[pcPosition].pcs[pcIndex].bearedOff = true;
                //set to empty
                boardPtr->triangles[pcPosition].pcs[pcIndex].emptyPiece = true;
                boardPtr->triangles[pcPosition].pcs[pcIndex].blackPiece = true;
                boardPtr->triangles[pcPosition].pcs[pcIndex].inBar = false;
                boardPtr->triangles[pcPosition].pcCounter--;
                printf("You have beared off a piece.\n");
            }else{
                printf("You can't bear off any piece.\n");
            }

        }
    }else{
        printf("You are now in the bearing off stage.\n");
        printf("Roll dice to start bearing off? \n");
        printf("1. Yes\n");
        printf("2. No\n");
        int choice = 0;
        scanf("%d", &choice);
        if (choice == 1){
            int tempDice[2];
            rolldice(tempDice);
            int initialPoint = 17 + tempDice[0];
            int copy = initialPoint;
            int max = 23;
            int min = 18;
            bool hitUpperLimit = false;
            bool stopWhile = false;
            while((boardPtr->triangles[initialPoint].pcCounter == 0 || boardPtr->triangles[initialPoint].pcs[0].blackPiece == false) && stopWhile == false){
                
                if (hitUpperLimit == true){
                    initialPoint--;
                }else{
                    initialPoint++;
                }

                if (initialPoint > max){
                    hitUpperLimit = true;
                    initialPoint = copy;
                }else{
                    if (initialPoint < min){
                        stopWhile = true;
                    }
                }
            }
            if (initialPoint >= min && initialPoint <= max){
                int pcPosition = initialPoint;
                int pcsCounter = boardPtr->triangles[pcPosition].pcCounter;
                int pcIndex = pcsCounter - 1;
                boardPtr->triangles[pcPosition].pcs[pcIndex].bearedOff = true;
                //set to empty
                boardPtr->triangles[pcPosition].pcs[pcIndex].emptyPiece = true;
                boardPtr->triangles[pcPosition].pcs[pcIndex].blackPiece = true;
                boardPtr->triangles[pcPosition].pcs[pcIndex].inBar = false;
                boardPtr->triangles[pcPosition].pcCounter--;
                printf("You have beared off a piece.\n");
            }else{
                printf("You can't bear off any piece.\n");
            }

        }
    }

}


bool thereIsAPieceInBar(board * boardPtr){
    if (boardPtr->playerTurn){
        for(int i = 0; i < 24; i++){
            for(int j = 0; j < boardPtr->triangles[i].pcCounter; j++){
                if(boardPtr->triangles[i].pcs[j].blackPiece == true && boardPtr->triangles[i].pcs[j].inBar == true){
                    return true;
                }
            }
        }
    }else{
        for(int i = 0; i < 24; i++){
            for(int j = 0; j < boardPtr->triangles[i].pcCounter; j++){
                if(boardPtr->triangles[i].pcs[j].blackPiece == false && boardPtr->triangles[i].pcs[j].inBar == true){
                    return true;
                }
            }
        }
    }
    return false;
}
void putBackInBoardFromBar(board * boardPtr){
    if (boardPtr->playerTurn){
        printf("You have a piece in the bar. You must put it back in the board.\n");
        printf("Roll dice?");
        printf("1. Yes\n");
        printf("2. No\n");
        int choice = 0;
        scanf("%d", &choice);
        if (choice == 1){
            int tempDice[2];
            rolldice(tempDice);
            if (boardPtr->triangles[24 - tempDice[0]].pcCounter == 0){
                boardPtr->triangles[24 - tempDice[0]].pcs[0].blackPiece = true;
                boardPtr->triangles[24 - tempDice[0]].pcs[0].inBar = false;
                boardPtr->triangles[24 - tempDice[0]].pcs[0].bearedOff = false;
                boardPtr->triangles[24 - tempDice[0]].pcCounter++;
            }else{
                if (boardPtr->triangles[24 - tempDice[0]].pcs[0].blackPiece == true){
                    boardPtr->triangles[24 - tempDice[0]].pcs[boardPtr->triangles[24 - tempDice[0]].pcCounter].blackPiece = true;
                    boardPtr->triangles[24 - tempDice[0]].pcs[boardPtr->triangles[24 - tempDice[0]].pcCounter].inBar = false;
                    boardPtr->triangles[24 - tempDice[0]].pcs[boardPtr->triangles[24 - tempDice[0]].pcCounter].bearedOff = false;
                    boardPtr->triangles[24 - tempDice[0]].pcCounter++;
                }else{
                    printf("You can't put a piece in a triangle that has a white piece.\n");
                }
            }

        }else{
            boardPtr->playerTurn = !boardPtr->playerTurn;
        }

    }else{
        printf("You have a piece in the bar. You must put it back in the board.\n");
        printf("Roll dice?");
        printf("1. Yes\n");
        printf("2. No\n");
        int choice = 0;
        scanf("%d", &choice);
        if (choice == 1){
            int tempDice[2];
            rolldice(tempDice);
            if (boardPtr->triangles[tempDice[0]].pcCounter == 0){
                boardPtr->triangles[tempDice[0]].pcs[0].blackPiece = false;
                boardPtr->triangles[tempDice[0]].pcs[0].inBar = false;
                boardPtr->triangles[tempDice[0]].pcs[0].bearedOff = false;
                boardPtr->triangles[tempDice[0]].pcCounter++;
            }else{
                if (boardPtr->triangles[tempDice[0]].pcs[0].blackPiece == true){
                    boardPtr->triangles[tempDice[0]].pcs[boardPtr->triangles[tempDice[0]].pcCounter].blackPiece = false;
                    boardPtr->triangles[tempDice[0]].pcs[boardPtr->triangles[tempDice[0]].pcCounter].inBar = false;
                    boardPtr->triangles[tempDice[0]].pcs[boardPtr->triangles[tempDice[0]].pcCounter].bearedOff = false;
                    boardPtr->triangles[tempDice[0]].pcCounter++;
                }else{
                    printf("You can't put a piece in a triangle that has a black piece.\n");
                }
            }

        }else{
            //invert turn
            boardPtr->playerTurn = !boardPtr->playerTurn;
        }

    }

}   

void checkGameEndCondition(bool * gameEnd, board * boardPtr){
    int blackPieces = 0;
    int whitePieces = 0;
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < boardPtr->triangles[i].pcCounter; j++){
            if(boardPtr->triangles[i].pcs[j].blackPiece == true){
                blackPieces++;
            }else{
                whitePieces++;
            }
        }
    }

    //check bar
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < boardPtr->triangles[i].pcCounter; j++){
            if(boardPtr->triangles[i].pcs[j].blackPiece == true && boardPtr->triangles[i].pcs[j].inBar == true){
                blackPieces++;
            }else if(boardPtr->triangles[i].pcs[j].blackPiece == false && boardPtr->triangles[i].pcs[j].inBar == true){
                whitePieces++;
            }
        }
    }
    if (blackPieces == 0 || whitePieces == 0){
        *gameEnd = true;
    }

}

int main()
{
    // srand(time(NULL));
    int dice[2];
    board gameBoard;
    bool gameEnd = false;
    printf("mem of boardPtr %p\n", &gameBoard);
    initializeBoardValues(&gameBoard);
    do
    {

        rolldice(dice);
        printContents(&gameBoard);
        printBoard(&gameBoard);
        checkGameEndCondition(&gameEnd, &gameBoard);
        if (checkIfPlayerCanStartBearingOff(&gameBoard) == true){
            bearingOffStage(&gameBoard);
        }else if(thereIsAPieceInBar(&gameBoard) == true){
            putBackInBoardFromBar(&gameBoard);
        }
        else{
            movePieceChoice(&gameBoard, dice);
        }

    } while (gameEnd == false);
}
