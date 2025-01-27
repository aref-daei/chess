#include <stdio.h>
#include <string.h>

#define CBD 10 // Chess Board Dimensions

void displayBoard(char board[][CBD]);
void switchTurn(char board[][CBD]);
void move();

int isValidPawnMove();
int isValidRookMove();
int isValidKnightMove();
int isValidBishopMove();
int isValidQueenMove();
int isValidKingMove();
int isCheckMate();

int main()
{
    char board[][CBD] = {
        "-abcdefgh-",
        "8rnbqkbnr8",
        "7pppppppp7",
        "6        6",
        "5        5",
        "4        4",
        "3        3",
        "2PPPPPPPP2",
        "1RNBQKBNR1",
        "-abcdefgh-",
    };

    int turn = 1;

    while (1)
    {
        displayBoard(board);

        char command[10];
        printf("Command:   [command]\nExit:      exit\n> ");
        scanf("%s", command);

        char log[100];

        if (command[0] == 'P')
        {
            isValidPawnMove();
        }
        else if (command[0] == 'R')
        {
            isValidRookMove();
        }
        else if (command[0] == 'N')
        {
            isValidKnightMove();
        }
        else if (command[0] == 'B')
        {
            isValidBishopMove();
        }
        else if (command[0] == 'Q')
        {
            isValidQueenMove();
        }
        else if (command[0] == 'K')
        {
            isValidKingMove();
        }
        else if (!strcmp(command, "exit"))
            break;
        else
        {
            printf("The command is invalid!\n");
            continue;
        }

        if (isCheckMate())
        {
            printf("%s\n", log);
            break;
        }

        switchTurn(board);
        turn == 1 ? (turn = 2) : (turn = 1);
    }

    return 0;
}

void displayBoard(char board[][CBD])
{
    const char *colorWhite = "\x1b[1;34;47m"; // White
    const char *colorBlack = "\x1b[1;34;40m"; // Black
    const char *colorGray = "\x1b[3;90m";     // Gray
    const char *colorReset = "\x1b[0m";       // Reset color

    for (int i = 0; i < CBD; i++)
    {
        for (int j = 0; j < CBD; j++)
        {
            if (i % (CBD - 1) == 0 || j % (CBD - 1) == 0)
                printf("%s%c %s", colorGray, board[i][j], colorReset);
            else if ((i + j) % 2 == 0)
                printf("%s%c %s", colorWhite, board[i][j], colorReset);
            else
                printf("%s%c %s", colorBlack, board[i][j], colorReset);
        }
        printf("\n");
    }
}

void switchTurn(char board[][CBD])
{
    char temp[CBD][CBD];

    for (int i = 0; i < CBD; i++)
    {
        for (int j = 0; j < CBD; j++)
            temp[i][j] = board[CBD - 1 - i][CBD - 1 - j];
    }

    for (int i = 0; i < CBD; i++)
    {
        for (int j = 0; j < CBD; j++)
            board[i][j] = temp[i][j];
    }
}

void move() {}

int isValidPawnMove() {}

int isValidRookMove() {}

int isValidKnightMove() {}

int isValidBishopMove() {}

int isValidQueenMove() {}

int isValidKingMove() {}

int isCheckMate() {}