#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 256
#define MAX_NUMBERS 7

int main() {
    char filename[] = "lotto.txt";
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LEN];
    int winning[3];
    int found_any = 0;
    
    // 輸入中獎號碼
    printf("請輸入中獎號碼三個： ");
    scanf("%d %d %d", &winning[0], &winning[1], &winning[2]);
    
    printf("輸入中獎號碼為：%02d %02d %02d\n", winning[0], winning[1], winning[2]);
    printf("以下為中獎彩卷：\n\n");
    
    // 重新讀取檔案，從頭開始找
    rewind(file);
    
    // 跳過檔案開頭格式行，直到找到日期行
    while (fgets(line, MAX_LINE_LEN, file)) {
        if (strstr(line, "March 13 2025")) {
            break;
        }
    }
    
    // 讀取每一張彩券
    while (fgets(line, MAX_LINE_LEN, file)) {
        // 檢查是否讀到結尾分隔線
        if (strstr(line, "========= csie@CGU =========")) {
            break;
        }
        
        // 只處理包含 "[" 的行（彩券行）
        if (strstr(line, "[") == NULL) {
            continue;
        }
        
        // 解析彩券號碼
        int numbers[MAX_NUMBERS];
        char *token;
        char temp_line[MAX_LINE_LEN];
        strcpy(temp_line, line);
        
        // 找到 [號碼]: 後面的數字
        token = strtok(temp_line, ":");
        
        if (token) {
            token = strtok(NULL, ":"); // 取得號碼部分
            
            // 讀取7個號碼
            int count = 0;
            char *num_token = strtok(token, " ");
            
            while (num_token != NULL && count < MAX_NUMBERS) {
                numbers[count] = atoi(num_token);
                count++;
                num_token = strtok(NULL, " ");
            }
            
            // 檢查是否包含至少一個中獎號碼
            int match = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < MAX_NUMBERS; j++) {
                    if (winning[i] == numbers[j]) {
                        match = 1;
                        break;
                    }
                }
                if (match) break; // 找到一個匹配就夠了
            }
            
            // 如果至少匹配一個中獎號碼，輸出這張彩券
            if (match) {
                // 移除換行符號
                line[strcspn(line, "\n")] = 0;
                printf("售出時間： March 13 2025: %s\n", line);
                found_any = 1;
            }
        }
    }
       
    fclose(file);
    return 0;
}
