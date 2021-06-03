//Kevin Muina

#include<stdio.h>
#include<math.h>
#include<string.h>
#define MAX_COMMAND_TOKEN_LENGTH 6
#define WHITE 1
#define BLACK -1
#define EMPTY 0
#define ROOK 4
#define KNIGHT 2
#define BISHOP 3
#define KING 6
#define QUEEN 5
#define PAWN 1

static int board[8][8] = { {-4, -2, -3, -5, -6, -3, -2, -4},
                           {-1, -1, -1, -1, -1, -1, -1, -1},
                           { 0,  0,  0,  0,  0,  0,  0,  0},
                           { 0,  0,  0,  0,  0,  0,  0,  0},
                           { 0,  0,  0,  0,  0,  0,  0,  0},
                           { 0,  0,  0,  0,  0,  0,  0,  0},
                           { 1,  1,  1,  1,  1,  1,  1,  1},
                           { 4,  2,  3,  5,  6,  3,  2,  4}};

int k_is_dead = 0;

static int isLegalMove(int srcI, int srcJ, int trgI, int trgJ) {
    int i;
    int pieceType;
    int piece = board[srcI][srcJ];//moved piece...
    if(piece == -1){
        pieceType = piece;
    }else
        pieceType = abs(piece);
    switch (pieceType) {
    case ROOK:
        if(srcI == trgI && srcJ < trgJ){
            for (i = 1; i+srcJ < trgJ; i++) {
                if (board[trgI][srcJ+i] != EMPTY) {
                    return 0;
                }
            }
        }else if(srcI == trgI && srcJ > trgJ){
            for (i = 1; srcJ-i > trgJ; i++) {
                if (board[trgI][srcJ-i] != EMPTY) {
                    return 0;
                }
            }
        }else if(srcJ == trgJ && srcI < trgI) {
            for (i = 1; i + srcI < trgI; i++) {
                if (board[srcI + i][trgJ] != EMPTY) {
                    return 0;
                }
            }
        }else if(srcJ == trgJ && srcI > trgI){
            for (i = 1; srcI - i > trgI; i++) {
                if (board[srcI - i][trgJ] != EMPTY) {
                    return 0;
                }
            }
        }else
            return 0;
        break;
    case PAWN:
        if(srcJ == trgJ && srcI > trgI){
            if((abs(srcI - trgI) > 2 && srcI == 6) || (abs(srcI - trgI) != 1) && srcI != 6){
                return 0;
            }
        }
        if(srcJ != trgJ || srcI < trgI){
            return 0;
        }
        break;
    case -1: //black pawn... i did this so that i could stop them from going backwards easier
        if(srcJ == trgJ && srcI < trgI) {
            if ((abs(srcI - trgI) > 2 && srcI == 1) || (abs(srcI - trgI) != 1) && srcI != 1) {
                return 0;
            }
        }
        if(srcJ != trgJ || srcI > trgI){
            return 0;
        }
        break;
    case KNIGHT://L shape
        return abs((srcI - trgI) * (srcJ - trgJ)) == 2;
        break;
    case BISHOP:
        if (abs(srcI - trgI) != abs(srcJ - trgJ))   //checks if piece are in the way
            return 0;
        if (srcI < trgI && srcJ < trgJ){//case 1
            for (i = 1; i+srcI < trgI; i++){
                if (board[srcI + i][srcJ + i] != EMPTY)
                    return 0;
            }
        }else if (srcI > trgI && srcJ > trgJ) {//case 2
            for (i = 1; srcI - i > trgI; i++){
                if (board[srcI - i][srcJ - i] != EMPTY)
                    return 0;
            }
        }
        else if (srcI > trgI && srcJ < trgJ) //case 3
            for (i = 1; srcI - i > trgI; i++) {
                if (board[srcI - i][srcJ + i] != EMPTY)
                    return 0;
            }
        else //case 4
            for (i = 1; srcI + i < trgI; i++) {
                if (board[srcI + i][srcJ - i] != EMPTY)
                    return 0;
            }
        break;
    case QUEEN:
        if(srcI==trgI || srcJ==trgJ) {
            if (srcI == trgI && srcJ < trgJ) {
                for (i = 1; i + srcJ < trgJ; i++) {
                    if (board[trgI][srcJ + i] != EMPTY) {
                        return 0;
                    }
                }
            } else if (srcI == trgI && srcJ > trgJ) {
                for (i = 1; srcJ - i > trgJ; i++) {
                    if (board[trgI][srcJ - i] != EMPTY) {
                        return 0;
                    }
                }
            } else if (srcJ == trgJ && srcI < trgI) {
                for (i = 1; i + srcI < trgI; i++) {
                    if (board[srcI + i][trgJ] != EMPTY) {
                        return 0;
                    }
                }
            } else if (srcJ == trgJ && srcI > trgI) {
                for (i = 1; srcI - i > trgI; i++) {
                    if (board[srcI - i][trgJ] != EMPTY) {
                        return 0;
                    }
                }
            }
        }else if(abs(srcI-trgI)==abs(srcJ-trgJ)) {
            if (srcI < trgI && srcJ < trgJ) {//case 1
                for (i = 1; i + srcI < trgI; i++) {
                    if (board[srcI + i][srcJ + i] != EMPTY)
                        return 0;
                }
            } else if (srcI > trgI && srcJ > trgJ) {//case 2
                for (i = 1; srcI - i > trgI; i++) {
                    if (board[srcI - i][srcJ - i] != EMPTY)
                        return 0;
                }
            } else if (srcI > trgI && srcJ < trgJ) { //case 3
                for (i = 1; srcI - i > trgI; i++) {
                    if (board[srcI - i][srcJ + i] != EMPTY)
                        return 0;
                }
            } else if (srcI < trgI && srcJ > trgJ) {//case 4
                for (i = 1; srcI + i < trgI; i++) {
                    if (board[srcI + i][srcJ - i] != EMPTY)
                        return 0;
                }
            }
        }else
            return 0;
        break;
    case KING:
        if (((abs(srcI-trgI) != 1) && srcJ == trgJ) ||
            ((abs(srcJ-trgJ) != 1) && srcI == trgI) ||
            ((abs(srcJ-trgJ) != 1) && (abs(srcI -trgI) != 1))
                ) {
            return 0;
        }
        break;
    }
    return 1;//legal move
}
static int isLegalCapture(int srcI, int srcJ, int trgI, int trgJ) {
    int i;
    int piece = board[srcI][srcJ];//moved piece...
    int pieceType;
    if(piece == -1){
        pieceType = piece;
    }else
        pieceType = abs(piece);
    switch (pieceType) {
        case ROOK:
            if (srcI == trgI && srcJ < trgJ) {
                for (i = 1; i + srcJ < trgJ; i++) {
                    if (board[trgI][srcJ + i] != EMPTY) {
                        return 0;
                    }
                }
            } else if (srcI == trgI && srcJ > trgJ) {
                for (i = 1; srcJ - i > trgJ; i++) {
                    if (board[trgI][srcJ - i] != EMPTY) {
                        return 0;
                    }
                }
            } else if (srcJ == trgJ && srcI < trgI) {
                for (i = 1; i + srcI < trgI; i++) {
                    if (board[srcI + i][trgJ] != EMPTY) {
                        return 0;
                    }
                }
            } else if (srcJ == trgJ && srcI > trgI) {
                for (i = 1; srcI - i > trgI; i++) {
                    if (board[srcI - i][trgJ] != EMPTY) {
                        return 0;
                    }
                }
            } else
                return 0;
            break;
        case PAWN:
            if(srcI > trgI && abs(trgI-srcI) == 1) {
                if (abs(srcI - trgI) != abs(srcJ - trgJ))   //checks if piece are in the way
                    return 0;
            }else
                return 0;
            break;
        case -1:
            if(srcI < trgI && abs(trgI-srcI) == 1) {
                if (abs(srcI - trgI) != abs(srcJ - trgJ))   //checks if piece are in the way
                    return 0;
            }else
                return 0;
            break;
        case KNIGHT://L shape
            return abs((srcI - trgI) * (srcJ - trgJ)) == 2;
            break;
        case BISHOP:
            if (abs(srcI - trgI) != abs(srcJ - trgJ))   //checks if piece are in the way
                return 0;
            if (srcI < trgI && srcJ < trgJ) {//case 1
                for (i = 1; i + srcI < trgI; i++) {
                    if (board[srcI + i][srcJ + i] != EMPTY)
                        return 0;
                }
            } else if (srcI > trgI && srcJ > trgJ) {//case 2
                for (i = 1; srcI - i > trgI; i++) {
                    if (board[srcI - i][srcJ - i] != EMPTY)
                        return 0;
                }
            } else if (srcI > trgI && srcJ < trgJ) //case 3
                for (i = 1; srcI - i > trgI; i++) {
                    if (board[srcI - i][srcJ + i] != EMPTY)
                        return 0;
                }
            else //case 4
                for (i = 1; srcI + i < trgI; i++) {
                    if (board[srcI + i][srcJ - i] != EMPTY)
                        return 0;
                }
            break;
        case QUEEN:
            if(srcI==trgI || srcJ==trgJ) {
                if (srcI == trgI && srcJ < trgJ) {
                    for (i = 1; i + srcJ < trgJ; i++) {
                        if (board[trgI][srcJ + i] != EMPTY) {
                            return 0;
                        }
                    }
                } else if (srcI == trgI && srcJ > trgJ) {
                    for (i = 1; srcJ - i > trgJ; i++) {
                        if (board[trgI][srcJ - i] != EMPTY) {
                            return 0;
                        }
                    }
                } else if (srcJ == trgJ && srcI < trgI) {
                    for (i = 1; i + srcI < trgI; i++) {
                        if (board[srcI + i][trgJ] != EMPTY) {
                            return 0;
                        }
                    }
                } else if (srcJ == trgJ && srcI > trgI) {
                    for (i = 1; srcI - i > trgI; i++) {
                        if (board[srcI - i][trgJ] != EMPTY) {
                            return 0;
                        }
                    }
                }
            }else if(abs(srcI-trgI)==abs(srcJ-trgJ)) {
                if (srcI < trgI && srcJ < trgJ) {//case 1
                    for (i = 1; i + srcI < trgI; i++) {
                        if (board[srcI + i][srcJ + i] != EMPTY)
                            return 0;
                    }
                } else if (srcI > trgI && srcJ > trgJ) {//case 2
                    for (i = 1; srcI - i > trgI; i++) {
                        if (board[srcI - i][srcJ - i] != EMPTY)
                            return 0;
                    }
                } else if (srcI > trgI && srcJ < trgJ) { //case 3
                    for (i = 1; srcI - i > trgI; i++) {
                        if (board[srcI - i][srcJ + i] != EMPTY)
                            return 0;
                    }
                } else if (srcI < trgI && srcJ > trgJ) {//case 4
                    for (i = 1; srcI + i < trgI; i++) {
                        if (board[srcI + i][srcJ - i] != EMPTY)
                            return 0;
                    }
                }
            }else
                return 0;
            break;
        case KING:
            if (((abs(srcI-trgI) != 1) && srcJ == trgJ) ||
                ((abs(srcJ-trgJ) != 1) && srcI == trgI) ||
                ((abs(srcJ-trgJ) != 1) && (abs(srcI -trgI) != 1))
                ) {
                return 0;
            }
            break;
    }
    return 1;//legal move
}
static int turn = WHITE;
char getCommandWord(char command[], int maxLength) {
    char lastCharacter;//either space or new line
    int i;
    for (i = 0; (lastCharacter = getchar()) == ' '; i++);//skip leading white spaces
    if (lastCharacter == '\n') {
        command[0] = '\0';
        return lastCharacter;
    }
    command[0] = lastCharacter;
    for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';
    return lastCharacter;
}
static int upgradeTime(int srcI, int srcJ) {
    char answer[6];
    int exit = 0;
    char queen[] = "Queen";
    char rook[] = "Rook";
    char Bishop[] = "Bishop";
    char Knight[] = "Knight";
    while(exit == 0) {
            printf("Please enter what you would like to upgrade you pawn to \n"
                   "your choices include Queen, Knight, Rook, or Bishop: \n");
            scanf("%s", answer);
            if(strcmp(answer, queen) == 0)//if command == "Queen"
            {
                if(turn == WHITE){
                    board[srcI][srcJ] = 5;
                }else
                    board[srcI][srcJ] = -5;
                printf("Your pawn is now a Queen\n");
                exit = 1;
            } else if (strcmp(answer, Knight) == 0) {
                if(turn == WHITE) {
                    board[srcI][srcJ] = 2;
                }else
                    board[srcI][srcJ] = -2;
                printf("Your pawn is now a Knight\n");
                exit = 1;
            } else if (strcmp(answer, rook) == 0) {
                if(turn == WHITE) {
                    board[srcI][srcJ] = 4;
                }else
                    board[srcI][srcJ] = -4;
                printf("Your pawn is now a Rook\n");
                exit = 1;
            } else if (strcmp(answer, Bishop) == 0) {
                if(turn == WHITE) {
                    board[srcI][srcJ] = 3;
                }else
                    board[srcI][srcJ] = -3;
                printf("Your pawn is now a Bishop\n");
                exit = 1;
            } else if (strcmp(answer, "\n") == 0) {
                printf("Insert a correct option!");
            }
        }
    }
handleMove() {
    char source[MAX_COMMAND_TOKEN_LENGTH];
    char target[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;
    lastCharacter = getCommandWord(source, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter == '\n') {
        printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
        return;
    }
    lastCharacter = getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter != '\n') {
        printf("Too many arguments for mv command! It must be in the form of mv ai bj.\n");
        while (getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the rest of illegal command..
        return;
    }
    sourceFile = source[0];//source = "a5", sourceFile = 'a'
    targetFile = target[0];
    sourceRank = source[1] - '0';//source = "a5", sourceRank = 5
    targetRank = target[1] - '0';
    //board[sourceI][sourceJ]: source square...
    //board[targetI][targetJ]: target square...
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
        printf("invalid mv arguments\n");
        return;
    }
    //checking the turn first
    if (board[sourceI][sourceJ] * turn < 0) {
        printf("Turn violation, it's %s to move\n", turn == 1 ? "white" : "black");
        return;
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] != EMPTY) {
        printf("Invalid move: either source square is empty or target square is not empty\n");
        return;
    }
    if (!isLegalMove(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess move\n");
        return;
    }
    //end of error checking....
    board[targetI][targetJ] = board[sourceI][sourceJ];
    if(abs(board[targetI][targetJ]) ==PAWN && turn == WHITE && targetI == 0){
        upgradeTime(targetI, targetJ);
    }else if(abs(board[targetI][sourceJ]==PAWN) && turn == BLACK && targetI == 7){
        upgradeTime(targetI, targetJ);
    }
    board[sourceI][sourceJ] = EMPTY;
    turn *= -1;//WHITE --> BLACK and BLACK --> WHITE
}
handleCapture() {
    char source[MAX_COMMAND_TOKEN_LENGTH];
    char target[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;
    lastCharacter = getCommandWord(source, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter == '\n') {
        printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
        return;
    }
    lastCharacter = getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter != '\n') {
        printf("Too many arguments for cp command! It must be in the form of cp ai bj.\n");
        while (getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH) != '\n');
        return;
    }
    sourceFile = source[0];
    targetFile = target[0];
    sourceRank = source[1] - '0';
    targetRank = target[1] - '0';
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
        printf("invalid mv arguments\n");
        return;
    }
    //checking the turn first
    if (board[sourceI][sourceJ] * turn < 0) {
        printf("Turn violation, it's %s to move \n", turn == WHITE ? "WHITE" : "BLACK");
        return;
    }
    if (board[sourceI][sourceJ] * board[targetI][targetJ] > 0) {
        printf("Violation, %s cannot capture its own piece. \n", turn == WHITE ? "WHITE" : "BLACK");
        return;
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] == EMPTY) {
        printf("Invalid capture: either source square is empty or target square is empty \n");
        return;
    }
    if (!isLegalCapture(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess capture \n");
        return;
    }
    if (abs(board[targetI][targetJ]) == KING) {
        if(board[targetI][targetJ] == -1*KING)
            k_is_dead = -1;
        else
            k_is_dead = 1;
    }
    //end of error checking....
    board[targetI][targetJ] = board[sourceI][sourceJ];
    if(abs(board[sourceI][sourceJ]) == PAWN && turn == WHITE && targetI == 0){
        upgradeTime(sourceI, sourceJ);
    }else if(abs(board[sourceI][sourceJ]) == PAWN && turn == BLACK && targetI == 7){
        upgradeTime(sourceI, sourceJ);
    }
    board[sourceI][sourceJ] = 0;
    turn *= -1;
}
handleShow() {
    int i, j;
    printf("board\t");
    for (i = 0; i < 8; i++)//file labels...
        printf("%c%c", 'a' + i, i == 7 ? '\n' : '\t');
    for (i = 0; i < 8; i++)//table itself
        for (j = 0; j < 9; j++)
            printf("%d%c", j == 0 ? 8 - i: board[i][j - 1], j == 8 ? '\n' : '\t');
}
main() {
    char command[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    while (1) {//infinite while loop...
        printf("Please enter a new command...\n");
        lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        if (strcmp(command, "quit") == 0)//if command === "quit"
            break;
        else if (!strcmp(command, "mv"))//if command == "mv"
        {
            if (lastCharacter == '\n')//mv\n
                printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
            else {
                handleMove();
                handleShow();
            }
        } else if (!strcmp(command, "cp"))//if command == "cp"
        {
            if (lastCharacter == '\n')//cp\n
                printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
            else {
                handleCapture();
                handleShow();
                if(k_is_dead == -1){
                    printf("Game Over! \nWhite has won the game!");
                    break;
                }
                if (k_is_dead == 1){
                    printf("Game Over! \nBlack has won the game!");
                    break;
                }
            }
        } else if (!strcmp(command, "show"))//if command == "show"
        {
            if (lastCharacter != '\n') {//show x\n
                printf("Too many arguments for show command! It must be in the form of show.\n");
                while (getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the invalid show command...
            } else
                handleShow();
        } else {
            printf("invalid command! Your command must start either with quit, mv or cp.\n");
            while (lastCharacter != '\n')//skip the remainder of my invalid command...
                lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        }
    }
}