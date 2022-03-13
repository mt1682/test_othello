#include "func.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "disk.h"
#include "header.h"

Disk DISK[BOARD_SIZE];

//座標変換
int get64(int x, int y) {
    y++;
    x++;
    return y * BOARD_WIDTH + x;
}

//座標変換
int getXY(int position) {
    int x, y;
    y = position / BOARD_WIDTH;
    x = position % BOARD_WIDTH;
    y = y - 1;
    x = x - 1;
    return x * 10 + y;
}

//初期化
void init(void) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        DISK[i].init();
        if (i == 44 || i == 55) {
            DISK[i].set(2);
        } else if (i == 45 || i == 54) {
            DISK[i].set(1);
        } else if (i / 10 == 0 || i / 10 == BOARD_HIGHT - 1 || i % 10 == 0 ||
                   i % 10 == BOARD_WIDTH - 1) {
            DISK[i].set(-2);
        }
    }
}

//横方向チェック
bool checkLateral(int x, int y, int color) {
    int judge = 0;
    int position = get64(x, y);
    //右方向
    if (DISK[position].near[5] == 3 - color) {
        for (int i = x + 1; i < BOARD_WIDTH - 2; i++) {
            if (DISK[get64(i, y)].getColor() == 0) {
                break;
            }
            if (DISK[get64(i, y)].getColor() == color) {
                judge++;
            }
        }
    }
    //左方向
    if (DISK[position].near[3] == 3 - color) {
        for (int i = x - 1; i >= 0; i--) {
            if (DISK[get64(i, y)].getColor() == 0) {
                break;
            }
            if (DISK[get64(i, y)].getColor() == color) {
                judge++;
            }
        }
    }
    if (judge)
        return true;
    else
        return false;
}

//縦方向チェック
bool checkLongtitudinal(int x, int y, int color) {
    int judge = 0;
    int position = get64(x, y);
    //下方向
    if (DISK[position].near[7] == 3 - color) {
        for (int i = y + 1; i < BOARD_HIGHT - 2; i++) {
            if (DISK[get64(x, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(x, i)].getColor() == color) {
                judge++;
            }
        }
    }
    //上方向
    if (DISK[position].near[1] == 3 - color) {
        for (int i = y - 1; i >= 0; i--) {
            if (DISK[get64(x, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(x, i)].getColor() == color) {
                judge++;
            }
        }
    }
    if (judge)
        return true;
    else
        return false;
}

//斜め方向チェック
bool checkDiagonal(int x, int y, int color) {
    int judge = 0;
    int position = get64(x, y);
    //右上
    if (DISK[position].near[2] == 3 - color) {
        int j = x + 1;
        for (int i = y - 1; i >= 0; i--) {
            if (DISK[get64(j, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(j, i)].getColor() == color && j < BOARD_WIDTH - 2) {
                judge++;
            }
            j++;
        }
    }
    //右下
    if (DISK[position].near[8] == 3 - color) {
        int j = x + 1;
        for (int i = y + 1; i < BOARD_HIGHT - 2; i++) {
            if (DISK[get64(j, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(j, i)].getColor() == color && j < BOARD_WIDTH - 2) {
                judge++;
            }
            j++;
        }
    }
    //左上
    if (DISK[position].near[0] == 3 - color) {
        int j = x - 1;
        for (int i = y - 1; i >= 0; i--) {
            if (DISK[get64(j, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(j, i)].getColor() == color && j >= 0) {
                judge++;
            }
            j--;
        }
    }
    //左下
    if (DISK[position].near[6] == 3 - color) {
        int j = x - 1;
        for (int i = y + 1; i < BOARD_HIGHT - 2; i++) {
            if (DISK[get64(j, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(j, i)].getColor() == color && j >= 0) {
                judge++;
            }
            j--;
        }
    }
    if (judge)
        return true;
    else
        return false;
}

//合法手チェック
bool isSafe(int x, int y, int color) {
    if (checkLateral(x, y, color) == true ||
        checkLongtitudinal(x, y, color) == true ||
        checkDiagonal(x, y, color) == true) {
        // printf("SAFE\n");
        return true;
    }
    // printf("NG: %d %d\n", x, y);
    return false;
}

//石を置く(x, y, color, near設定)
void setDisk(int x, int y, int color) {
    int position = get64(x, y);
    DISK[position].set(color);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            DISK[position].near[(i + 1) * 3 + (j + 1)] =
                DISK[get64(x + j, y + i)].getColor();
            // printf("%d ", DISK[position].near[(i + 1) * 3 + (j + 1)]);
        }
    }
    // printf("\n");
}

//石を取る
int flipDisk(int x, int y, int color) {
    flipLateral(x, y, color);
    flipLongtitudinal(x, y, color);
    flipDiagonal(x, y, color);
    return 0;
}

//表示
void print(void) {
    printf("   ");
    for (int i = 0; i < BOARD_WIDTH - 2; i++) {
        printf("%d ", i);
    }
    printf("\n");

    printf("  ");
    for (int i = 0; i < BOARD_WIDTH - 2; i++) {
        printf("--");
    }
    printf("\n");

    for (int i = 0; i < BOARD_HIGHT - 2; i++) {
        printf("%d| ", i);
        for (int j = 0; j < BOARD_WIDTH - 2; j++) {
            if (DISK[get64(j, i)].getColor() == 1) {
                printf("● ");
            } else if (DISK[get64(j, i)].getColor() == 2) {
                printf("○ ");
            } else {
                printf("× ");
            }
            // printf("%d ", DISK[get64(j, i)].getColor());
        }
        printf("\n");
    }
    printf("\n");
}

//横方向に取る
void flipLateral(int x, int y, int color) {
    int position = get64(x, y);
    //右方向
    if (DISK[position].near[5] == 3 - color) {
        for (int i = x + 1; i < BOARD_WIDTH - 2; i++) {
            if (DISK[get64(i, y)].getColor() == 0) {
                break;
            }
            if (DISK[get64(i, y)].getColor() == color) {
                for (int j = x + 1; j < i; j++) {
                    DISK[get64(j, y)].flip();
                }
                break;
            }
        }
    }
    //左方向
    if (DISK[position].near[3] == 3 - color) {
        for (int i = x - 1; i >= 0; i--) {
            if (DISK[get64(i, y)].getColor() == 0) {
                break;
            }
            if (DISK[get64(i, y)].getColor() == color) {
                for (int j = x - 1; j > i; j--) {
                    DISK[get64(j, y)].flip();
                }
                break;
            }
        }
    }
}

//縦方向に取る
void flipLongtitudinal(int x, int y, int color) {
    int position = get64(x, y);
    //下方向
    if (DISK[position].near[7] == 3 - color) {
        for (int i = y + 1; i < BOARD_HIGHT - 2; i++) {
            if (DISK[get64(x, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(x, i)].getColor() == color) {
                for (int j = y + 1; j < i; j++) {
                    DISK[get64(x, j)].flip();
                }
                break;
            }
        }
    }
    //上方向
    if (DISK[position].near[1] == 3 - color) {
        for (int i = y - 1; i >= 0; i--) {
            if (DISK[get64(x, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(x, i)].getColor() == color) {
                for (int j = y - 1; j > i; j--) {
                    DISK[get64(x, j)].flip();
                }
                break;
            }
        }
    }
}

//斜め方向に取る
void flipDiagonal(int x, int y, int color) {
    int position = get64(x, y);
    //右上
    if (DISK[position].near[2] == 3 - color) {
        int j = x + 1;
        for (int i = y - 1; i >= 0; i--) {
            if (DISK[get64(j, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(j, i)].getColor() == color && j < BOARD_WIDTH - 2) {
                int l = x + 1;
                for (int k = y - 1; k > i; k--) {
                    DISK[get64(l, k)].flip();
                    l++;
                }
                break;
            }
            j++;
        }
    }
    //右下
    if (DISK[position].near[8] == 3 - color) {
        int j = x + 1;
        for (int i = y + 1; i < BOARD_HIGHT - 2; i++) {
            if (DISK[get64(j, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(j, i)].getColor() == color && j < BOARD_WIDTH - 2) {
                int l = x + 1;
                for (int k = y + 1; k < i; k++) {
                    DISK[get64(l, k)].flip();
                    l++;
                }
                break;
            }
            j++;
        }
    }
    //左上
    if (DISK[position].near[0] == 3 - color) {
        int j = x - 1;
        for (int i = y - 1; i >= 0; i--) {
            if (DISK[get64(j, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(j, i)].getColor() == color && j >= 0) {
                int l = x - 1;
                for (int k = y - 1; k > i; k--) {
                    DISK[get64(l, k)].flip();
                    l--;
                }
                break;
            }
            j--;
        }
    }
    //左下
    if (DISK[position].near[6] == 3 - color) {
        int j = x - 1;
        for (int i = y + 1; i < BOARD_HIGHT - 2; i++) {
            if (DISK[get64(j, i)].getColor() == 0) {
                break;
            }
            if (DISK[get64(j, i)].getColor() == color && j >= 0) {
                int l = x - 1;
                for (int k = y + 1; k < i; k++) {
                    DISK[get64(l, k)].flip();
                    l--;
                }
                break;
            }
            j--;
        }
    }
}

int randomPlay(int color) {
    int x = rand() % (BOARD_WIDTH - 2);
    int y = rand() % (BOARD_HIGHT - 2);
    int position = get64(x, y);
    int cnt = 0;

    while (DISK[position].getColor() != 0) {
        x = rand() % BOARD_WIDTH;
        y = rand() % BOARD_HIGHT;
        position = get64(x, y);
    }

    setDisk(x, y, color);
    while (!isSafe(x, y, color)) {
        DISK[position].init();
        cnt++;
        if (cnt > 100) {
            color = 3 - color;
            return color;
        }
        x = rand() % BOARD_WIDTH;
        y = rand() % BOARD_HIGHT;
        position = get64(x, y);
        while (DISK[position].getColor() != 0) {
            x = rand() % BOARD_WIDTH;
            y = rand() % BOARD_HIGHT;
            position = get64(x, y);
        }
        setDisk(x, y, color);
    }
    setDisk(x, y, color);
    flipDisk(x, y, color);
    DISK[position].set(color);
    color = 3 - color;
    // print();
    return color;
}

bool cntZero(void) {
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (DISK[j].getColor() == 0) {
            return false;
        }
    }
    return true;
}

int cntScore(void) {
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (DISK[i].getColor() == 1) {
            cnt1++;
        } else if (DISK[i].getColor() == 2) {
            cnt2++;
        }
    }
    return cnt1;
}

void copyDisk(Disk DISK_COPY[], Disk DISK_ORG[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        DISK_COPY[i].set(DISK_ORG[i].getColor());
        for (int j = 0; j < 9; j++) {
            DISK_COPY[i].near[j] = DISK_ORG[i].near[j];
            // printf("%d ", DISK_ORG[i].near[j]);
        }
        // printf("\n");
    }
}

void saveDisk(void) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        DISK[i].save();
    }
}

void restoreDisk(void) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        DISK[i].restore();
    }
}

int allSearch(int color) {
    int buffColor = color;
    int score = 0;
    int maxScore = INT_MIN;
    int bestposition = 0;
    saveDisk();

    for (int y = 0; y < BOARD_HIGHT - 2; y++) {
        for (int x = 0; x < BOARD_WIDTH - 2; x++) {
            int position = get64(x, y);
            color = buffColor;
            score = 0;
            if (DISK[position].getColor() != 0) {
                continue;
            }
            setDisk(x, y, color);
            // printf("first OK: %d %d\n", x, y);
            if (!isSafe(x, y, color)) {
                DISK[position].init();
                continue;
            }
            /*
            for (int j = 0; j < 9; j++) {
                printf("%d ", DISK[position].near[j]);
            }
            printf("\n");
            */
            // printf("OK: %d %d\n", x, y);

            // DISK[position].init();

            for (int i = 0; i < 10; i++) {
                setDisk(x, y, color);
                flipDisk(x, y, color);
                DISK[position].set(color);
                color = 3 - color;
                int cnt = 0;
                while (!cntZero()) {
                    cnt++;
                    color = randomPlay(color);
                    if (cnt > 200) {
                        break;
                    }
                }
                // printf("YES\n");
                if (cntScore() - 40 > 0) {
                    score++;
                } else {
                    score--;
                }
                if (DISK[get64(0, 0)].getColor() == 1) {
                    score++;
                }
                if (DISK[get64(7, 0)].getColor() == 1) {
                    score++;
                }
                if (DISK[get64(7, 7)].getColor() == 1) {
                    score++;
                }
                if (DISK[get64(0, 7)].getColor() == 1) {
                    score++;
                }

                // score += cntScore();
                restoreDisk();
            }
            if (maxScore < score) {
                maxScore = score;
                bestposition = position;
            }

            restoreDisk();
        }
    }
    //  printf("%d\n", bestposition);

    /*
    for (int j = 0; j < 9; j++) {
        printf("%d ", DISK[46].near[j]);
    }
    printf("\n");
    */
    return bestposition;
}

int play(int x, int y, int color) {
    setDisk(x, y, color);
    if (isSafe(x, y, color) == false) {
        printf("ILLEGAL\n");
        return -1;
    }
    flipDisk(x, y, color);
    setDisk(x, y, color);
    color = 3 - color;
    return color;
}
