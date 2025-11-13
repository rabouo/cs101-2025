#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define COUNTER_FILE "counter.bin"
#define MAX_LOTTO_NUM 7
#define MAX_LOTTO_NUMSET 5

// 判斷號碼是否重複
int num_in_numset(int num, int numset[], int Len) {
    int ret = 0;
    for (int i = 0; i < Len; i++) {
        if (num == numset[i]) {
            ret = 1;
            break;
        }
    }
    return ret;
}

// 初始化計數器檔案
void init_file() {
    int write_array[1] = {0};
    FILE* fp = fopen(COUNTER_FILE, "r");
    if (fp == NULL) {
        FILE* tmpfp = fopen(COUNTER_FILE, "wb+");
        fwrite(write_array, sizeof(int), 1, tmpfp);
        fclose(tmpfp);
    } else {
        fclose(fp);
    }
}

// 讀取計數器
int get_counter() {
    int read_array[1];
    FILE* tmpfp = fopen(COUNTER_FILE, "rb");
    fread(read_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
    return read_array[0];
}

// 設定計數器
void set_counter(int counter) {
    int write_array[1];
    write_array[0] = counter;
    FILE* tmpfp = fopen(COUNTER_FILE, "wb");
    fwrite(write_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
}

// 排序樂透號碼
void sorting_lotto_row(int numset[]) {
    for (int i = 0; i < MAX_LOTTO_NUM - 1; ++i) {
        for (int j = 0; j < i; ++j) {
            if (numset[j] > numset[i]) {
                int temp = numset[j];
                numset[j] = numset[i];
                numset[i] = temp;
            }
        }
    }
}
// 輸出一組樂透號碼
void print_lotto_row(FILE* tmpfp, int n) {
    int numset[MAX_LOTTO_NUM];

    // 生成樂透號碼 (前6個號碼: 1-69)
    for (int i = 0; i < MAX_LOTTO_NUM - 1; ) {
        int num = (rand() % 69) + 1;
        if (num_in_numset(num, numset, i)) {
            continue;
        } else {
            numset[i] = num;
            i++;
        }
    }

    // 生成特別號 (第7個號碼: 1-10)
    for (int i = 0; i < 1; ) {
        int num = (rand() % 10) + 1;
        if (num_in_numset(num, numset, MAX_LOTTO_NUM - 1)) {
            continue;
        } else {
            numset[MAX_LOTTO_NUM - 1] = num;
            i++;
        }
    }

    // 排序前6個號碼
    sorting_lotto_row(numset);

    // 輸出號碼
    fprintf(tmpfp, "[%d]: ", n);
    for (int i = 0; i < MAX_LOTTO_NUM; i++) {
        fprintf(tmpfp, "%02d ", numset[i]);
    }
    fprintf(tmpfp, "\n");
}

// 生成樂透檔案
void print_lottofile(int num_set, int counter, char lotto_file[]) {
    time_t curtime;
    time(&curtime);
    srand((unsigned int)time(NULL));

    FILE* tmpfp = fopen(lotto_file, "w+");
    fprintf(tmpfp, "======== Lotto649 =========\n");
    fprintf(tmpfp, "=======+ No.%05d +========\n", counter);
    fprintf(tmpfp, "= %.24s =\n", ctime(&curtime));

    for (int i = 0; i < MAX_LOTTO_NUMSET; i++) {
        if (i < num_set) {
            print_lotto_row(tmpfp, i + 1);
        } else {
            fprintf(tmpfp, "[%d]: -- -- -- -- -- -- --\n", i + 1);
        }
    }

    fprintf(tmpfp, "======== csie@CGU =========\n");
    fclose(tmpfp);
}

// 主樂透功能
void do_lotto_main(int counter) {
    char lotto_file[32];
    int num_set = 0;
    sprintf(lotto_file, "lotto[%05d].txt", counter);

    printf("歡迎光臨長庚樂透彩購買機\n");
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &num_set);

    print_lottofile(num_set, counter, lotto_file);
    printf("已為您購買的 %d 組樂透組合輸出至 %s\n", num_set, lotto_file);
}
// 主程式
int main() {
    int counter;

    // 初始化紀錄檔
    init_file();

    // 讀取當前計數器
    counter = get_counter();
    printf("counter = %d\n", counter);

    // 執行樂透主程式
    do_lotto_main(counter + 1);

    // 更新計數器 (加1後寫回)
    set_counter(counter + 1);

    return 0;
}
