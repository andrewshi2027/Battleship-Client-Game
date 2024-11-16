#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT1 2201
#define PORT2 2202 
#define BUFFER_SIZE 1024
#define MAX_SHIPS 5

//Structs
typedef struct {
    int width;
    int height;
    int **grid;
} Board;

Board *create_board(int width, int height) {
    Board *board = malloc(sizeof(Board));
    board->width = width;
    board->height = height;

    board->grid= (int**)malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++) {
        board->grid[i] = (int *)malloc(width * sizeof(int));
    }
    return board;
}

void display_board(Board *board, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", board->grid[i][j]);
        }
        printf("\n");
    }
}

Board *begin(Board *board, int width, int height) {
    //Set all cells to 0
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            board->grid[i][j] = 0;
        }
    }
    display_board(board, width, height);
    return board;
}

void delete_board(Board *board){
    for (int i = 0; i < board->height; i++) {
        free(board->grid[i]);
    }
    free(board->grid);
    free(board);
}

//Checks if Valid Ship Placement
int is_within_board(Board *board, int row, int column) {
    return (row >= 0 && row < board->height && column >=0 && column < board->width);
}

//Place the Ship on the Board
int initialize(Board *board, char* buffer, int width, int height) {
    int piece_type, piece_rotation, piece_column, piece_row;

    int pieces_index = 0;
    int space = 0;
    int pieces[20]; 
    int buffer_index = 2;

    while (sscanf(&buffer[buffer_index], "%d ", &pieces[pieces_index], &space) == 1) {
        pieces_index++;
        buffer_index += space; 
        if (pieces_index >= 20) {break;}
    }

    if (pieces_index < 20) {
        printf("Error");
        return 302;
    }

    for (int i = 0; i < pieces_index; i += 4) {
        int piece_type = pieces[i];
        int piece_rotation = pieces[i + 1];
        int piece_column = pieces[i + 2];
        int piece_row = pieces[i + 3];
    
        switch (piece_type) {
            case 1: //Shape 1
                if (piece_rotation == 1 || piece_rotation == 2 || piece_rotation == 3 || piece_rotation == 4) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;} 
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 0] == 1) {return -1;} 
                    if (is_within_board(board, piece_row + 1, piece_column + 0) == 1) {board->grid[piece_row + 1][piece_column + 0] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 1] == 1) {return -1;} 
                    if (is_within_board(board, piece_row + 1, piece_column + 1) == 1) {board->grid[piece_row + 1][piece_column + 1] = 1;}           
                    else {return -1;}
                }
                
            case 2: //Shape 2
                if (piece_rotation == 1 || piece_rotation == 3) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row + 1, piece_column) == 1) {board->grid[piece_row + 1][piece_column] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row + 2][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row + 2, piece_column) == 1) {board->grid[piece_row + 2][piece_column] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 3][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row + 3, piece_column) == 1) {board->grid[piece_row + 3][piece_column] = 1;}           
                    else {return -1;}
                }
                
                else if (piece_rotation == 2 || piece_rotation == 4) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row, piece_column + 1) == 1) {board->grid[piece_row][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row, piece_column + 2) == 1) {board->grid[piece_row][piece_column + 2] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 3] == 1) {return -1;}
                    if (is_within_board(board, piece_row, piece_column + 3) == 1) {board->grid[piece_row][piece_column + 3] = 1;}           
                    else {return -1;}
                }

            case 3: //Shape 3
                if (piece_rotation == 1 || piece_rotation == 3) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row - 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row - 1, piece_column + 1) == 1) {board->grid[piece_row - 1][piece_column + 1] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row - 1][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row - 1, piece_column + 2) == 1) {board->grid[piece_row - 1][piece_column + 2] = 1;}           
                    else {return -1;}
                }
                
                else if (piece_rotation == 2 || piece_rotation == 4) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 0) == 1) {board->grid[piece_row + 1][piece_column + 0] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 1) == 1) {board->grid[piece_row + 1][piece_column + 1] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 2][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 2, piece_column + 1) == 1) {board->grid[piece_row + 2][piece_column + 1] = 1;}           
                    else {return -1;}
                }

            case 4: //Shape 4
                if (piece_rotation == 1) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 0) == 1) {board->grid[piece_row + 1][piece_column + 0] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row + 2][piece_column] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 2, piece_column + 0) == 1) {board->grid[piece_row + 2][piece_column + 0] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 2][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 2, piece_column + 1) == 1) {board->grid[piece_row + 2][piece_column + 1] = 1;}           
                    else {return -1;}
                }

                else if (piece_rotation == 2) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 2) == 1) {board->grid[piece_row + 0][piece_column + 2] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 0) == 1) {board->grid[piece_row + 1][piece_column + 0] = 1;}           
                    else {return -1;}
                }

                else if (piece_rotation == 3) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 1) == 1) {board->grid[piece_row + 1][piece_column + 1] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 2][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 2, piece_column + 1) == 1) {board->grid[piece_row + 2][piece_column + 1] = 1;}           
                    else {return -1;}
                }

                else if (piece_rotation == 4) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 2) == 1) {board->grid[piece_row + 0][piece_column + 2] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row - 1][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row - 1, piece_column + 2) == 1) {board->grid[piece_row - 1][piece_column + 2] = 1;}           
                    else {return -1;}
                }

            case 5: //Shape 5
                if (piece_rotation == 1 || piece_rotation == 3) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 1) == 1) {board->grid[piece_row + 1][piece_column + 1] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 2) == 1) {board->grid[piece_row + 1][piece_column + 2] = 1;}           
                    else {return -1;}
                }
                
                else if (piece_rotation == 2 || piece_rotation == 4) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 1) == 1) {board->grid[piece_row + 1][piece_column + 1] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row - 1][piece_column] == 1) {return -1;}
                    if (is_within_board(board, piece_row - 1, piece_column + 0) == 1) {board->grid[piece_row - 1][piece_column + 0] = 1;}           
                    else {return -1;}
                }

            case 6: //Shape 6
                if (piece_rotation == 1) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row - 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row - 1, piece_column + 1) == 1) {board->grid[piece_row - 1][piece_column + 1] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row - 2][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row - 2, piece_column + 1) == 1) {board->grid[piece_row - 2][piece_column + 1] = 1;}           
                    else {return -1;}
                }

                else if (piece_rotation == 2) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 0) == 1) {board->grid[piece_row + 1][piece_column + 0] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 1) == 1) {board->grid[piece_row + 1][piece_column + 1] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 2) == 1) {board->grid[piece_row + 1][piece_column + 2] = 1;}           
                    else {return -1;}
                }

                else if (piece_rotation == 3) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 0) == 1) {board->grid[piece_row + 1][piece_column + 0] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 2][piece_column] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 2, piece_column + 0) == 1) {board->grid[piece_row + 2][piece_column + 0] = 1;}           
                    else {return -1;}
                }

                else if (piece_rotation == 4) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 2) == 1) {board->grid[piece_row + 0][piece_column + 2] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 2) == 1) {board->grid[piece_row + 1][piece_column + 2] = 1;}           
                    else {return -1;}
                }

            case 7: //Shape 7
                if (piece_rotation == 1) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row + 0][piece_column + 1] == 1) {return -1;} 
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 2) == 1) {board->grid[piece_row + 0][piece_column + 2] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 1) == 1) {board->grid[piece_row + 1][piece_column + 1] = 1;}           
                    else {return -1;}
                }

                else if (piece_rotation == 2) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row - 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row - 1, piece_column + 1) == 1) {board->grid[piece_row - 1][piece_column + 1] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 1) == 1) {board->grid[piece_row + 1][piece_column + 1] = 1;}           
                    else {return -1;}
                }

                else if (piece_rotation == 3) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 1) == 1) {board->grid[piece_row + 0][piece_column + 1] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row][piece_column + 2] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 0, piece_column + 2) == 1) {board->grid[piece_row + 0][piece_column + 2] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row - 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row - 1, piece_column + 1) == 1) {board->grid[piece_row - 1][piece_column + 1] = 1;}           
                    else {return -1;}
                }

                else if (piece_rotation == 4) {
                    if (board->grid[piece_row][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row, piece_column) == 1) {board->grid[piece_row][piece_column] = 1;} 
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 0) == 1) {board->grid[piece_row + 1][piece_column + 0] = 1;}    
                    else {return -1;}

                    if (board->grid[piece_row + 2][piece_column] == 1) {return -1;} 
                    if (is_within_board(board, piece_row + 2, piece_column + 0) == 1) {board->grid[piece_row + 2][piece_column + 0] = 1;}   
                    else {return -1;}

                    if (board->grid[piece_row + 1][piece_column + 1] == 1) {return -1;}
                    if (is_within_board(board, piece_row + 1, piece_column + 1) == 1) {board->grid[piece_row + 1][piece_column + 1] = 1;}           
                    else {return -1;}
                }
        }
    }
}

//Shoot
int shoot(Board *board, int row, int column) {
    //Hit
    if (board->grid[row][column] == 1) {
        board->grid[row][column] = 100;
        return 100;
    }
    //Miss
    else if (board->grid[row][column] == 0) {
        board->grid[row][column] = 200;
        return 200;
    }
    //Already Guessed Cell
    else if (board->grid[row][column] == 100 || board->grid[row][column] == 200) {
        board->grid[row][column] = 300;
        return 300;
    }
}

//Ships Left
int ships_left (Board *board, int width, int height) {
    int ships = 0;
    for (int i = 0; i < board->width; i++) {
        for (int j = 0; j < board->height; j++) {
            if(board->grid[i][j] == 1) {ships++;}
        }
    }
}

//Query

//Forfeit
//Error
//Halt
//Acknowledgment

int main() {
    int p1_listen_fd, p1_conn_fd, p2_listen_fd, p2_conn_fd;
    struct sockaddr_in p1_address, p2_address;
    int p1_addrlen = sizeof(p1_address);
    int p2_addrlen = sizeof(p2_address);
    char p1_buffer[BUFFER_SIZE] = {0};
    char p2_buffer[BUFFER_SIZE] = {0};
    int opt = 1;

    // Create socket for Player 1
    if ((p1_listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed for Player 1");
        exit(EXIT_FAILURE);
    }

    // Create socket for Player 2
    if ((p2_listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed for Player 2");
        exit(EXIT_FAILURE);
    }

    // Set socket options for Player 1
    if (setsockopt(p1_listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))");
        exit(EXIT_FAILURE);
    }

    // Set socket options for Player 2
    if (setsockopt(p2_listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))");
        exit(EXIT_FAILURE);
    }

    // Bind socket for Player 1
    p1_address.sin_family = AF_INET;
    p1_address.sin_addr.s_addr = INADDR_ANY;
    p1_address.sin_port = htons(PORT1);
    if (bind(p1_listen_fd, (struct sockaddr *)&p1_address, sizeof(p1_address)) < 0) {
        perror("[Server] bind() failed for Player 1");
        exit(EXIT_FAILURE);
    }

    // Bind socket for Player 2
    p2_address.sin_family = AF_INET;
    p2_address.sin_addr.s_addr = INADDR_ANY;
    p2_address.sin_port = htons(PORT2);
    if (bind(p2_listen_fd, (struct sockaddr *)&p2_address, sizeof(p2_address)) < 0) {
        perror("[Server] bind() failed for Player 2");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections for Player 1
    if (listen(p1_listen_fd, 3) < 0) {
        perror("[Server] listen() failed for Player 1.");
        exit(EXIT_FAILURE);
    }
    printf("[Server] Running on port %d for Player 1\n", PORT1);

    // Listen for incoming connections for Player 2
    if (listen(p2_listen_fd, 3) < 0) {
        perror("[Server] listen() failed for Player 2.");
        exit(EXIT_FAILURE);
    }
    printf("[Server] Running on port %d for Player 2\n", PORT2);

    // Accept incoming connection for Player 1
    if ((p1_conn_fd = accept(p1_listen_fd, (struct sockaddr *)&p1_address, (socklen_t *)&p1_addrlen)) < 0) {
        perror("[Server] accept() failed for Player 1.");
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection for Player 2
    if ((p2_conn_fd = accept(p2_listen_fd, (struct sockaddr *)&p2_address, (socklen_t *)&p2_addrlen)) < 0) {
        perror("[Server] accept() failed for Player 2.");
        exit(EXIT_FAILURE);
    }
    //_______________________________________________________________________________________________________________________
    //_______________________________________________________________________________________________________________________
    //_______________________________________________________GAME____________________________________________________________
    //_______________________________________________________________________________________________________________________
    Board *p1_board;
    Board *p2_board;

    //Receive message from Player 1
    while (1) {
        memset(p1_buffer, 0, BUFFER_SIZE);
        memset(p2_buffer, 0, BUFFER_SIZE);
        int width, height;

        int p1_nbytes = read(p1_conn_fd, p1_buffer, BUFFER_SIZE);

        if (p1_nbytes <= 0) {
            perror("[Server] read() failed for Player 1.");
            exit(EXIT_FAILURE);
        }

        //Forfeit
        if (strcmp(p1_buffer, "F") == 0) {
            printf("[Server] Player 1 forfeited\n");
            send(p1_conn_fd, "H 0", 3, 0); //Halt
            send(p2_conn_fd, "H 1", 3, 0); //Halt
            close(p1_conn_fd);
            close(p2_conn_fd);
            close(p1_listen_fd);
            close(p2_listen_fd);
            return 0;
        }

        if (p1_buffer[0] != 'B') {
            send(p1_conn_fd, "E 100", 5, 0);
        }
        else if (sscanf(p1_buffer, "B %d %d", &width, &height) != 2) {
            send(p1_conn_fd, "E 200", 5, 0);
        }
        else if (width >= 10 && height >= 10) {
            p1_board = create_board(width, height);
            p1_board = begin(p1_board, width, height);
            p2_board = create_board(width, height);
            p2_board = begin(p2_board, width, height);
            send(p1_conn_fd, "A", 1, 0); //Send Acknowledgement
            break;
        }
        //Invalid Dimensions (too small)
        else {
            send(p1_conn_fd, "E 200", 5, 0);
        }
    }

    //Receive message from Player 2
    while (1) {
        int temp;

        memset(p2_buffer, 0, BUFFER_SIZE);
        int p2_nbytes = read(p2_conn_fd, p2_buffer, BUFFER_SIZE);
        if (p2_nbytes <= 0) {
            perror("[Server] read() failed for Player 2.");
            exit(EXIT_FAILURE);
        }

        if (p2_nbytes <= 0) {
            perror("[Server] read() failed for Player 2.");
            exit(EXIT_FAILURE);
        }

        //Forfeit
        if (strcmp(p2_buffer, "F") == 0) {
            printf("Player 2 Forfeited\n");
            send(p2_conn_fd, "H 0", 4, 0); //Halt
            send(p1_conn_fd, "H 1", 4, 0); //Halt
            close(p1_conn_fd);
            close(p2_conn_fd);
            close(p1_listen_fd);
            close(p2_listen_fd);
            return 0;
        }

        if (p2_buffer[0] != 'B') {
            send(p1_conn_fd, "E 100", 5, 0);
            continue;
        }
        else if (p2_buffer[0] == 'B' && strlen(p2_buffer) == 1) {
            printf("Hello");
            send(p1_conn_fd, "A", 1, 0); //Send Acknowledgement
            break;
        }
        else {
            send(p2_conn_fd, "E 200", 5, 0);
        }

    }

    

    printf("[Server] Shutting down.\n");
    close(p1_conn_fd);
    close(p1_listen_fd);
    close(p2_conn_fd);
    close(p2_listen_fd);

    return EXIT_SUCCESS;
}