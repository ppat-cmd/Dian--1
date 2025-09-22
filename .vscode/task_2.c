#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 判断是否为空行（仅包含空白字符）
int blank_line(const char *str) {
    if (str == NULL) {
        return 1;
    }
    
    while (*str != '\0') {
        if (!isspace((unsigned char)*str)) {
            return 0;  // 找到非空白字符，不是空行
        }
        str++;
    }
    return 1;  // 全是空白字符，是空行
}

// 去除行尾的空白字符
void remove_trailing_space(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        len--;
    }
    str[len] = '\0';  // 在第一个非空白字符后添加结束符
}

// 去除#后的内容
void remove_comment(char *str) {
    if (str == NULL) {
        return;
    }
    
    // 查找#字符
    char *comment_start = strchr(str, '#');
    if (comment_start != NULL) {
        *comment_start = '\0';  // 在#处截断字符串
    }
}

// 处理Makefile
void makefile(int verbose) {
    FILE *in_file, *out_file = NULL;
    char buffer[1024];  
    
    // 打开输入文件
    in_file = fopen("./Makefile", "r");
    if (in_file == NULL) {
        perror("无法打开Makefile");
        return;
    }
    
    // 如果启用调试模式，打开输出文件
    if (verbose) {
        out_file = fopen("./Minimake_cleared.mk", "w");
        if (out_file == NULL) {
            perror("无法创建输出文件Minimake_cleared.mk");
            fclose(in_file);
            return;
        }
    }
    
    // 逐行读取并处理
    printf("清理后的Makefile内容\n");
    while (fgets(buffer, sizeof(buffer), in_file) != NULL) {

        remove_comment(buffer);// 去除注释
        
        remove_trailing_space(buffer);// 去除行尾空格
        
        // 过滤空行
        if (blank_line(buffer)) {
            continue;
        }
        
        printf("%s\n", buffer);// 输出清理后的行（控制台）
        
        // 如果启用调试模式，写入文件
        if (verbose && out_file != NULL) {
            fprintf(out_file, "%s\n", buffer);
        }
    }
    
    // 检查读取过程是否有错误
    if (ferror(in_file)) {
        perror("读取文件时发生错误");
    }
    
    // 关闭文件
    fclose(in_file);
    if (verbose && out_file != NULL) {
        fclose(out_file);
        printf("清理后的内容已保存到Minimake_cleared.mk\n");
    }
}



int main(int argc, char *argv[]) {
    // 检查是否启用调试模式
    int verbose = 0;
    if (argc > 1) {
        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--verbose") == 0) {
            verbose = 1;
        } else {
            fprintf(stderr, "用法: %s [-v|--verbose]\n", argv[0]);
            return 1;
        }
    }
    
    makefile(verbose);
    return 0;
}