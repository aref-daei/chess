#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CBD 10 // Chess Board Dimensions

void clearScreen();

void displayBoard(char board[][CBD], char log[]);
void switchTurn(char board[][CBD], int *turn);
void move(char board[][CBD], char command[], int turn, char log[]);

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
            if (isValidPawnMove(board, command, turn, log))
                move(board, command, turn, log);
            else
                continue;
        }
        else if (command[0] == 'R')
        {
            if (isValidRookMove(board, command, turn, log))
                move(board, command, turn, log);
            else
                continue;
        }
        else if (command[0] == 'N')
        {
            if (isValidKnightMove(board, command, turn, log))
                move(board, command, turn, log);
            else
                continue;
        }
        else if (command[0] == 'B')
        {
            if (isValidBishopMove(board, command, turn, log))
                move(board, command, turn, log);
            else
                continue;
        }
        else if (command[0] == 'Q')
        {
            if (isValidQueenMove(board, command, turn, log))
                move(board, command, turn, log);
            else
                continue;
        }
        else if (command[0] == 'K')
        {
            if (isValidKingMove(board, command, turn, log))
                move(board, command, turn, log);
            else
                continue;
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

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayBoard(char board[][CBD], char log[])
{
    const char *colorWhite = "\x1b[1;34;47m"; // White
    const char *colorBlack = "\x1b[1;34;40m"; // Black
    const char *colorGray = "\x1b[3;90m";     // Gray
    const char *colorReset = "\x1b[0m";       // Reset color

    clearScreen();

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

void move(char board[][CBD], char command[], int turn, char log[])
{
    if (command[1] < 'i' && command[2] < '9' && command[3] < 'i' && command[4] < '9')
    {
        switch (turn)
        {
        case 1:
            board[CBD - (command[4] - 49 + 1 + 1)][command[3] - 97 + 1] = board[CBD - (command[2] - 49 + 1 + 1)][command[1] - 97 + 1];
            board[CBD - (command[2] - 49 + 1 + 1)][command[1] - 97 + 1] = ' ';
            break;
        case 2:
            board[command[4] - 49 + 1][CBD - (command[3] - 97 + 1 + 1)] = board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1 + 1)];
            board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1 + 1)] = ' ';
            break;
        }
    }
    else
        strcpy(log, "The movement is out of the zone.");
}

int isValidPawnMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 1 + 1)][command[1] - 97 + 1] != 'P')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1 + 1)] != 'p')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        break;
    }

    return 1;
}

int isValidRookMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 1 + 1)][command[1] - 97 + 1] != 'R')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if ((command[2] != command[4]) && (command[1] != command[3]))
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1 + 1)] != 'r')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if ((command[2] != command[4]) && (command[1] != command[3]))
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        break;
    }

    return 1;
}

int isValidKnightMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 1 + 1)][command[1] - 97 + 1] != 'N')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1 + 1)] != 'n')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        break;
    }

    return 1;
}

int isValidBishopMove(char board[][CBD], char command[], int turn, char log[]) /* This has a problem. */
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 1 + 1)][command[1] - 97 + 1] != 'B')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if (CBD - (command[2] - 49 + 1) + command[1] - 97 != CBD - (command[4] - 49 + 1) + command[3] - 97)
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        if ((command[1] - 97 + 1 < 5 && command[1] > command[3]) || (command[1] - 97 + 1 > 4 && command[1] < command[3]))
        {
            strcpy(log, "You can't go that way.");
            return 0;
        }
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1 + 1)] != 'b')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if (command[2] - 49 + 1 + CBD - (command[1] - 97 + 1) != command[4] - 49 + 1 + CBD - (command[3] - 97 + 1))
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        break;
    }

    return 1;
}

int isValidQueenMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 1 + 1)][command[1] - 97 + 1] != 'Q')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1 + 1)] != 'q')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        break;
    }

    return 1;
}

int isValidKingMove(char board[][CBD], char command[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        if (board[CBD - (command[2] - 49 + 1 + 1)][command[1] - 97 + 1] != 'K')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        break;

    case 2:
        if (board[command[2] - 49 + 1][CBD - (command[1] - 97 + 1 + 1)] != 'k')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        break;
    }

    return 1;
}

int isCheckMate() {}