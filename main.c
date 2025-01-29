#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CBD 10 // Chess Board Dimensions

void clearScreen();

void displayBoard(char board[][CBD], char log[]);
void switchTurn(char board[][CBD], int *turn);
void move(char board[][CBD], char cmd[], int turn, char log[]);

int isValidPawnMove(char board[][CBD], char cmd[], int turn, char log[]);
int isValidRookMove(char board[][CBD], char cmd[], int turn, char log[]);
int isValidKnightMove(char board[][CBD], char cmd[], int turn, char log[]);
int isValidBishopMove(char board[][CBD], char cmd[], int turn, char log[]);
int isValidQueenMove(char board[][CBD], char cmd[], int turn, char log[]);
int isValidKingMove(char board[][CBD], char cmd[], int turn, char log[]);
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

    char log[64] = {'\0'};

    while (1)
    {
        displayBoard(board, log);

        char cmd[8];
        printf("Command:   [PIECE][poo][pod]\nExit:      exit\n> ");
        scanf("%s", cmd);

        if (cmd[0] == 'P')
        {
            if (isValidPawnMove(board, cmd, turn, log))
                move(board, cmd, turn, log);
            else
                continue;
        }
        else if (cmd[0] == 'R')
        {
            if (isValidRookMove(board, cmd, turn, log))
                move(board, cmd, turn, log);
            else
                continue;
        }
        else if (cmd[0] == 'N')
        {
            if (isValidKnightMove(board, cmd, turn, log))
                move(board, cmd, turn, log);
            else
                continue;
        }
        else if (cmd[0] == 'B')
        {
            if (isValidBishopMove(board, cmd, turn, log))
                move(board, cmd, turn, log);
            else
                continue;
        }
        else if (cmd[0] == 'Q')
        {
            if (isValidQueenMove(board, cmd, turn, log))
                move(board, cmd, turn, log);
            else
                continue;
        }
        else if (cmd[0] == 'K')
        {
            if (isValidKingMove(board, cmd, turn, log))
                move(board, cmd, turn, log);
            else
                continue;
        }
        else if (!strcmp(cmd, "exit"))
            break;
        else
        {
            strcpy(log, "The command is invalid!");
            continue;
        }

        // if (isCheckMate())
        // {
        //     printf("%s\n", log);
        //     break;
        // }

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
            printf("    \x1b[93mLog: %s%s", log, colorReset);

        for (int i = 0; i < 65; i++)
            log[i] = '\0';

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

void move(char board[][CBD], char cmd[], int turn, char log[])
{
    switch (turn)
    {
    case 1:
        board[CBD - (cmd[4] - 49 + 1 + 1)][cmd[3] - 97 + 1] = board[CBD - (cmd[2] - 49 + 1 + 1)][cmd[1] - 97 + 1];
        board[CBD - (cmd[2] - 49 + 1 + 1)][cmd[1] - 97 + 1] = ' ';
        break;
    case 2:
        board[cmd[4] - 49 + 1][CBD - (cmd[3] - 97 + 1 + 1)] = board[cmd[2] - 49 + 1][CBD - (cmd[1] - 97 + 1 + 1)];
        board[cmd[2] - 49 + 1][CBD - (cmd[1] - 97 + 1 + 1)] = ' ';
        break;
    }
}

int isValidPawnMove(char board[][CBD], char cmd[], int turn, char log[])
{
    if ((97 > cmd[3] || cmd[3] > 'h') || (49 > cmd[4] || cmd[4] > '8'))
    {
        strcpy(log, "The movement is out of the zone.");
        return 0;
    }
    switch (turn)
    {
    case 1:
        if (board[CBD - (cmd[2] - 49 + 1 + 1)][cmd[1] - 97 + 1] != 'P')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if (cmd[2] == '2')
        {
            if ((cmd[1] != cmd[3]) || (cmd[4] - cmd[2] > 2))
            {
                strcpy(log, "Movement is not allowed.");
                return 0;
            }
        }
        else
        {
            if ((cmd[1] != cmd[3]) || (cmd[4] - cmd[2] > 1))
            {
                strcpy(log, "Movement is not allowed.");
                return 0;
            }
        }
        break;

    case 2:
        if (board[cmd[2] - 49 + 1][CBD - (cmd[1] - 97 + 1 + 1)] != 'p')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if (cmd[2] == '7')
        {
            if ((cmd[1] != cmd[3]) || (cmd[2] - cmd[4] > 2))
            {
                strcpy(log, "Movement is not allowed.");
                return 0;
            }
        }
        else
        {
            if ((cmd[1] != cmd[3]) || (cmd[2] - cmd[4] > 1))
            {
                strcpy(log, "Movement is not allowed.");
                return 0;
            }
        }
        break;
    }

    return 1;
}

int isValidRookMove(char board[][CBD], char cmd[], int turn, char log[])
{
    if ((97 > cmd[3] || cmd[3] > 'h') || (49 > cmd[4] || cmd[4] > '8'))
    {
        strcpy(log, "The movement is out of the zone.");
        return 0;
    }
    switch (turn)
    {
    case 1:
        if (board[CBD - (cmd[2] - 49 + 1 + 1)][cmd[1] - 97 + 1] != 'R')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if ((cmd[2] != cmd[4]) && (cmd[1] != cmd[3]))
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        break;

    case 2:
        if (board[cmd[2] - 49 + 1][CBD - (cmd[1] - 97 + 1 + 1)] != 'r')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if ((cmd[2] != cmd[4]) && (cmd[1] != cmd[3]))
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        break;
    }

    return 1;
}

int isValidKnightMove(char board[][CBD], char cmd[], int turn, char log[])
{
    if ((97 > cmd[3] || cmd[3] > 'h') || (49 > cmd[4] || cmd[4] > '8'))
    {
        strcpy(log, "The movement is out of the zone.");
        return 0;
    }
    switch (turn)
    {
    case 1:
        if (board[CBD - (cmd[2] - 49 + 1 + 1)][cmd[1] - 97 + 1] != 'N')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if (abs(cmd[1]-cmd[3]) != abs(cmd[2]-cmd[4]) || abs(cmd[2]-cmd[4]) != 2)
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        break;

    case 2:
        if (board[cmd[2] - 49 + 1][CBD - (cmd[1] - 97 + 1 + 1)] != 'n')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if (abs(cmd[1]-cmd[3]) != abs(cmd[2]-cmd[4]) || abs(cmd[2]-cmd[4]) != 2)
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        break;
    }

    return 1;
}

int isValidBishopMove(char board[][CBD], char cmd[], int turn, char log[])
{
    if ((97 > cmd[3] || cmd[3] > 'h') || (49 > cmd[4] || cmd[4] > '8'))
    {
        strcpy(log, "The movement is out of the zone.");
        return 0;
    }
    switch (turn)
    {
    case 1:
        if (board[CBD - (cmd[2] - 49 + 1 + 1)][cmd[1] - 97 + 1] != 'B')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if (abs(cmd[1]-cmd[3]) != abs(cmd[2]-cmd[4]))
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        if ((cmd[1] - 97 + 1 < 5 && cmd[1] > cmd[3]) || (cmd[1] - 97 + 1 > 4 && cmd[1] < cmd[3]))
        {
            strcpy(log, "You can't go that way.");
            return 0;
        }
        break;

    case 2:
        if (board[cmd[2] - 49 + 1][CBD - (cmd[1] - 97 + 1 + 1)] != 'b')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if (abs(cmd[1]-cmd[3]) != abs(cmd[2]-cmd[4]))
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        if ((CBD - (cmd[1] - 97 + 1 + 1) < 5 && cmd[1] < cmd[3]) || (CBD - (cmd[1] - 97 + 1 + 1) > 4 && cmd[1] > cmd[3]))
        {
            strcpy(log, "You can't go that way.");
            return 0;
        }
        break;
    }

    return 1;
}

int isValidQueenMove(char board[][CBD], char cmd[], int turn, char log[])
{
    if ((97 > cmd[3] || cmd[3] > 'h') || (49 > cmd[4] || cmd[4] > '8'))
    {
        strcpy(log, "The movement is out of the zone.");
        return 0;
    }
    switch (turn)
    {
    case 1:
        if (board[CBD - (cmd[2] - 49 + 1 + 1)][cmd[1] - 97 + 1] != 'Q')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if ((cmd[2] != cmd[4]) && (cmd[1] != cmd[3]) && (abs(cmd[1]-cmd[3]) != abs(cmd[2]-cmd[4])) && (abs(cmd[1]-cmd[3]) != 1) && (abs(cmd[2]-cmd[4]) != 2))
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        break;

    case 2:
        if (board[cmd[2] - 49 + 1][CBD - (cmd[1] - 97 + 1 + 1)] != 'q')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        if ((cmd[2] != cmd[4]) && (cmd[1] != cmd[3]) && (abs(cmd[1]-cmd[3]) != abs(cmd[2]-cmd[4])) && (abs(cmd[1]-cmd[3]) != 1) && (abs(cmd[2]-cmd[4]) != 2))
        {
            strcpy(log, "Movement is not allowed.");
            return 0;
        }
        break;
    }

    return 1;
}

int isValidKingMove(char board[][CBD], char cmd[], int turn, char log[])
{
    if ((97 > cmd[3] || cmd[3] > 'h') || (49 > cmd[4] || cmd[4] > '8'))
    {
        strcpy(log, "The movement is out of the zone.");
        return 0;
    }
    switch (turn)
    {
    case 1:
        if (board[CBD - (cmd[2] - 49 + 1 + 1)][cmd[1] - 97 + 1] != 'K')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        break;

    case 2:
        if (board[cmd[2] - 49 + 1][CBD - (cmd[1] - 97 + 1 + 1)] != 'k')
        {
            strcpy(log, "The piece you chose is wrong.");
            return 0;
        }
        break;
    }

    return 1;
}

int isCheckMate() {}