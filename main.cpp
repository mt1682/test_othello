#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "func.h"
#include "header.h"

//白=1, 黒=2, 空=0
int main() {
    int position;
    int x, y;
    int nowPlayer = 1;
    int cnt = 0;
    int f = 0;

    srand((unsigned int)time(NULL));

    init();
    print();
    int me;
    printf("黒なら1, 白なら2, input: ");
    scanf("%d", &me);

    for (int i = 0; i < 200; i++) {
        f = 0;
        printf("now player: %d\n", nowPlayer);

        if (nowPlayer == -3 - me) {
            printf("input: ");
            scanf("%d%d", &x, &y);
            if (x == -1) {
                nowPlayer = 3 - nowPlayer;
                continue;
            }
            position = get64(x, y);
            nowPlayer = play(x, y, nowPlayer);
            print();

        } else if (nowPlayer == 2) {
            nowPlayer = randomPlay(nowPlayer);
            print();
        } else if (nowPlayer == me) {
            int bestPosition = allSearch(nowPlayer);
            if (bestPosition == -1) {
                nowPlayer = 3 - nowPlayer;
                continue;
            }
            position = getXY(bestPosition);
            x = position / 10;
            y = position % 10;
        RE:
            position = get64(x, y);
            nowPlayer = play(x, y, nowPlayer);
            if (nowPlayer == -1) {
                printf("ILLEGAL\n");
                return 0;
                goto RE;
            }
            printf("%d %d\n", x, y);
            print();
        }

        f = cntZero();
        if (f) {
            break;
        }
    }

    int score1 = cntScore(me);

    printf("%d %d\n", score1, 64 - score1);
    return 0;
}
