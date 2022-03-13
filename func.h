#ifndef func_h
#define func_h

#include "disk.h"

int get64(int x, int y);
int getXY(int position);
void print(void);
void init(void);
bool checkLateral(int x, int y, int color);
bool checkLongtitudinal(int x, int y, int color);
bool checkDiagonal(int x, int y, int color);
bool isSafe(int x, int y, int color);
void setDisk(int x, int y, int color);
int flipDisk(int x, int y, int color);
void flipLateral(int x, int y, int color);
void flipLongtitudinal(int x, int y, int color);
void flipDiagonal(int x, int y, int color);
int randomPlay(int color);
bool cntZero(void);
int cntScore(void);
void copyDisk(Disk DISK_COPY[], Disk DISK_ORG[]);
void saveDisk(void);
void restoreDisk(void);
int allSearch(int color);
int play(int x, int y, int color);

#endif