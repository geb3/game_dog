#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef __linux
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>

int getch() {
    int ch;
    struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

#endif
int main() {
    srand(time(NULL));
    char map[20][61];
    int i;
    int x = 10, y = 5;
    int ox, oy;
    int ax = 4, ay = 5;
    char key;
    int score = 0;
    do {
        sprintf(map[0], "|==========================================================|");
        for (i = 1; i < 19; i++) {
            sprintf(map[i],"|                                                          |");
        }
        sprintf(map[19], "|==========================================================|");
        
        map[y][x] = '@';
        map[ay][ax] = '*';
        system("clear");
        printf("\t\t\t  Score %d\n", score);
        for (i = 0; i < 20; i++) printf("%s\n", map[i]);
        ox = x;
        oy = y;
        printf("\tW: up, A: left, S: down, D: right, E: exit\n");
        key = getch();
        if (key == 'w') y--;
        if (key == 's') y++;
        if (key == 'a') x--;
        if (key == 'd') x++;
        if ((map[y][x] == '|') || (map[y][x] == '=')) {
            x = ox;
            y = oy;
        }
        if ((x == ax) && (y == ay)) {
            ax = rand() % 58 + 1;
            ay = rand() % 18 + 1;
            score++;
        }

    }
    while (key != 'e');

    return 0;
}
