#include <stdio.h>
#include <string.h>

#define CBD 10 // Chess Board Dimensions

void displayBoard(char board[][CBD], char log[]);
void switchTurn(char board[][CBD], int *turn);
void move(char board[][CBD], char command[], char log[]);

int isValidPawnMove(char board[][CBD], char command[], int turn, char log[]);
int isValidRookMove(char board[][CBD], char command[], int turn, char log[]);
int isValidKnightMove(char board[][CBD], char command[], int turn, char log[]);
int isValidBishopMove(char board[][CBD], char command[], int turn, char log[]);
int isValidQueenMove(char board[][CBD], char command[], int turn, char log[]);
int isValidKingMove(char board[][CBD], char command[], int turn, char log[]);
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
        char log[128];

        displayBoard(board, log);

        char command[8];
        printf("Command:   [command]\nExit:      exit\n> ");
        scanf("%s", command);

        if (command[0] == 'P')
        {
            isValidPawnMove(board, command, turn, log);
        }
        else if (command[0] == 'R')
        {
            isValidRookMove(board, command, turn, log);
        }
        else if (command[0] == 'N')
        {
            isValidKnightMove(board, command, turn, log);
        }
        else if (command[0] == 'B')
        {
            isValidBishopMove(board, command, turn, log);
        }
        else if (command[0] == 'Q')
        {
            isValidQueenMove(board, command, turn, log);
        }
        else if (command[0] == 'K')
        {
            isValidKingMove(board, command, turn, log);
        }
        else if (!strcmp(command, "exit"))
            break;
        else
        {
            strcpy(log, "The command is invalid!");
            continue;
        }

        if (isCheckMate())
        {
            printf("%s\n", log);
            break;
        }

        switchTurn(board, &turn);
    }

    return 0;
}

void displayBoard(char board[][CBD], char log[])
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

        if (i == 0 && log[0] != '\0')
            printf("    Log: %s", log);

        printf("\n");
    }
}

void switchTurn(char board[][CBD], int *turn)
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

    *turn == 1 ? (*turn = 2) : (*turn = 1);
}

void move(char board[][CBD], char command[], char log[]) {}

int isValidPawnMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 2)][command[1] - 97 + 1] != 'P')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("POOOOOOO\n");
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1)] != 'p')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("pOOOOOOO\n");
        break;

    default:
        break;
    }

    return 1;
}

int isValidRookMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 2)][command[1] - 97 + 1] != 'R')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("ROOOOOOO\n");
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1)] != 'r')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("rOOOOOOO\n");
        break;

    default:
        break;
    }

    return 1;
}

int isValidKnightMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 2)][command[1] - 97 + 1] != 'N')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("NOOOOOOO\n");
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1)] != 'n')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("nOOOOOOO\n");
        break;

    default:
        break;
    }

    return 1;
}

int isValidBishopMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 2)][command[1] - 97 + 1] != 'B')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("BOOOOOOO\n");
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1)] != 'b')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("bOOOOOOO\n");
        break;

    default:
        break;
    }

    return 1;
}

int isValidQueenMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 2)][command[1] - 97 + 1] != 'Q')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("QOOOOOOO\n");
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1)] != 'q')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("qOOOOOOO\n");
        break;

    default:
        break;
    }

    return 1;
}

int isValidKingMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 2)][command[1] - 97 + 1] != 'K')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("KOOOOOOO\n");
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1)] != 'k')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        printf("kOOOOOOO\n");
        break;

    default:
        break;
    }

    return 1;
}

int isCheckMate() {}