#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define X_MAX 40
#define Y_MAX 100

char field[X_MAX][Y_MAX];
char buf_field[X_MAX][Y_MAX];

void
init_field(char field[X_MAX][Y_MAX], char dead)
{
    for(size_t i = 0; i < X_MAX; i++)
    {
        for(size_t j = 0; j < Y_MAX; j++)
        {
            field[i][j] = dead;
        }
    }
}

void
reset_buf_field(char buf_field[X_MAX][Y_MAX],char dead)
{
    for(size_t i = 0; i < X_MAX; i++)
    {
        for(size_t j = 0; j < Y_MAX; j++)
        {
            buf_field[i][j] = dead;
        }
    } 
}

void
print_field(char field[X_MAX][Y_MAX])
{
    for (int i = 1; i < X_MAX-1; i++)
    {
        for(int j = 1; j < Y_MAX-1; j++)
        {
            printf("%c", field[i][j]);  
        }
        printf("\n");
    }
}

void
check_itsself(char field[X_MAX][Y_MAX], int i, int j, char life, char dead)
{   
    int live_around = 0;

    for(int k = -1; k < 2; k++)
    {
        for(int l = -1; l < 2; l++)
        {   
            if (l == 0 && k == 0)
            {
                continue;
            }
            
            if (field[i+k][j+l] == life)
            {
                live_around++;
            }
            
        }
    }

// printf("neighbors = %d\n", live_around);

    if (field[i][j] == dead)
    {
        if (live_around == 3)
        {
            buf_field[i][j] = life;
        }
    }
    else if (field[i][j] == life)
    {
        if (live_around == 2 || live_around == 3)
        {
            buf_field[i][j] = life;
        }
        if (live_around < 2 || live_around > 3)
        {
            buf_field[i][j] = dead;
        }

    }
    // if(field[i][j] == dead && live_around == 3)
    // {
    //     field[i][j] = life;
    // }
    //     else if (field[i][j] == life && (live_around == 2 || live_around == 3))
    //     {
    //         field[i][j] = life;
    //     }
    //         else if(field[i][j] == life && (live_around < 2 || live_around > 3))
    //         {
    //             field[i][j] = dead;
    //         }
    //             else
    //             {
    //                 field[i][j] = dead;
    //             }
}

void
next_eteration_field(char field[X_MAX][Y_MAX], char life, char dead)
{
    for(size_t i = 1; i < X_MAX-1; i++)
    {
        for (size_t j = 1; j < Y_MAX-1; j++)
        {
            check_itsself(field, i, j, life, dead);
        }
        
    }

    for(size_t i = 1; i < X_MAX-1; i++)
    {
        for (size_t j = 1; j < Y_MAX-1; j++)
        {
            field[i][j] = buf_field[i][j];
        }
    }

    reset_buf_field(buf_field, dead );
}

int
main()
{   
    char living_cells = '#';
    char dead_cells = '*';
    // getchar();

    init_field(field, dead_cells);
    reset_buf_field(buf_field, dead_cells);

    field[1][2] = living_cells;
    field[2][2] = living_cells;
    field[3][2] = living_cells;

    field[33][40] = living_cells;
    field[34][40] = living_cells;
    field[33][41] = living_cells;

    field[4][5] = living_cells;
    field[5][6] = living_cells;
    field[6][6] = living_cells;
    field[6][5] = living_cells;
    field[6][4] = living_cells;

    field[30][5] = living_cells;
    field[30][6] = living_cells;
    field[31][6] = living_cells;
    field[32][5] = living_cells;
    field[33][5] = living_cells;
    field[33][6] = living_cells;

    field[1][2] = living_cells;
    field[2][2] = living_cells;
    field[3][2] = living_cells;

    field[7][65] = living_cells;
    field[8][66] = living_cells;
    field[9][66] = living_cells;
    field[9][65] = living_cells;
    field[9][64] = living_cells;


    for(;;) 
    {   
        // printf("\033[?47l");

        print_field(field);
        next_eteration_field(field, living_cells, dead_cells);
        
        putc('\n', stdout);
        printf("\033[2J");

        usleep(200000);
    }
    
    
    
    return 0;
}