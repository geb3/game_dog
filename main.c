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

int xrand() {
    return rand() % 58 + 1;
}
int yrand() {
    return rand() % 18 + 1;
}

#endif
int main() {
    srand(time(NULL));
    char map[20][61];
    int i;
    int x = 10, y = 5;
    int ox, oy, eox, eoy, eox1, eoy1, eox2, eoy2;
    int ax = xrand(), ay = yrand();
    int ex = 5, ey = 6;
    int ex1 = 4, ey1 = 3, ex2 = 3, ey2 = 4;
    char key;
    int score = 0;
    int enemy1 = 5, enemy2 = 10;
    do {
        sprintf(map[0], "|==========================================================|");
        for (i = 1; i < 19; i++) {
            sprintf(map[i],"|                                                          |");
        }
        sprintf(map[19], "|==========================================================|");
        
        map[y][x] = '@';
        map[ay][ax] = '*';
        map[ey][ex] = '#';
        if (score >= enemy1) map[ey1][ex1] = '#';
        if (score >= enemy2) map[ey2][ex2] = '#';

        system("clear");
        printf("\t\t\t  Score %d\n", score);
        for (i = 0; i < 20; i++) printf("%s\n", map[i]);
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
        if ((x == ax) && (y == ay)) { // яблоки
            ax = xrand();
            ay = yrand();
            ex = ax-1;
            ey = ay-1;
            score++;
        }

        ox = x; // сталкновения с полями
        oy = y; // сталкновения с полями
        eox = ex; // сталкновения с полями
        eoy = ey; // сталкновения с полями
        eox1 = ex1; // сталкновения с полями
        eoy1 = ey1; // сталкновения с полями
        eox2 = ex2; // сталкновения с полями
        eoy2 = ey2; // сталкновения с полями

        if (x <= ex) ex--;
        if (x >= ex) ex++;
        if (y <= ey) ey--;
        if (y >= ey) ey++;
        if ( ((ey == ey1) && (ex == ex1)) || (ey == ey2) && (ex == ex2) ) {
            ex = eox;
            ey = eoy;
        }
        if ((x == ex) && (y == ey)) {
            x = xrand();
            y = yrand();
            ex = xrand();
            ey = yrand();
            score=0;
        }

        if (score >= enemy1) {
            if (x <= ex1) ex1--;
            if (x >= ex1) ex1++;
            if (y <= ey1) ey1--;
            if (y >= ey1) ey1++;
            if ( ((ey1 == ey) && (ex1 == ex)) || (ey1 == ey2) && (ex1 == ex2) ) {
                ex1 = eox1;
                ey1 = eoy1;
            }
            if ((x == ex1) && (y == ey1)) {
                x = xrand();
                y = yrand();
                ex1 = xrand();
                ey1 = yrand();
                score=0;
            }
        }
        
        if (score >= enemy2) {
            if (x <= ex2) ex2--;
            if (x >= ex2) ex2++;
            if (y <= ey2) ey2--;
            if (y >= ey2) ey2++;
            if ( ((ey2 == ey) && (ex2 == ex)) || (ey2 == ey1) && (ex2 == ex1) ) {
                ex2 = eox2;
                ey2 = eoy2;
            }
            if ((x == ex2) && (y == ey2)) {
                x = xrand();
                y = yrand();
                ex2 = xrand();
                ey2 = yrand();
                score=0;
            }
        }
    }
    while (key != 'e');

    return 0;
}
