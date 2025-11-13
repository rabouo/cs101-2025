#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5
#define COLS 7

int main() {
    FILE *fp;
    int lotto[ROWS][COLS];
    char date[50];
    char buffer[100];
    int win[3];
    int i, j;

    // 開啟檔案
    fp = fopen("lotto.txt", "r");
    if (fp == NULL) {
        printf("無法開啟 lotto.txt 檔案！\n");
        return 1;
    }

    // 讀前兩行
    fgets(buffer, sizeof(buffer), fp); // 第1行：========= lotto649 =========
    fgets(buffer, sizeof(buffer), fp); // 第2行：=====  March 13 2025  ======

    // 擷取日期內容
    sscanf(buffer, "=====  %[^=]  ======", date);

    // 從第3行開始讀取樂透號碼
    for (i = 0; i < ROWS; i++) {
        if (fscanf(fp, "[%*d]:") != 0) {
            for (j = 0; j < COLS; j++) {
                fscanf(fp, "%d", &lotto[i][j]);
            }
        }
    }
    fclose(fp);

    // 使用者輸入中獎號碼
    printf("請輸入中獎號碼3個 : ");
    for (i = 0; i < 3; i++) {
        scanf("%d", &win[i]);
    }

    // 輸出輸入的中獎號碼（前面補0）
    printf("輸入中獎號碼為 : ");
    for (i = 0; i < 3; i++) {
        printf("%02d ", win[i]);
    }
    printf("\n");

    // 檢查是否中獎
    int any = 0;
    printf("以下為中獎彩卷 :\n");

    for (i = 0; i < ROWS; i++) {
        int match = 0;
        for (j = 0; j < COLS; j++) {
            for (int k = 0; k < 3; k++) {
                if (lotto[i][j] == win[k]) {
                    match++;
                }
            }
        }

        if (match > 0) {
            any = 1;
            printf("售出時間 : %s : [ %d ]: ", date, i + 1);
            for (j = 0; j < COLS; j++) {
                printf("%02d ", lotto[i][j]); // 兩位數格式
            }
            printf("\n");
        }
    }
  return 0;
}

