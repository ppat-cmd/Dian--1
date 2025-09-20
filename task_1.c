#include <stdio.h>
#include <string.h>

void help() {
    printf("任务一\n");
    printf("  info          显示用户名字\n");
    printf("  --help        显示此帮助信息\n");
}


void info(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "错误: 'info' 命令需要提供一个名字参数\n");
        fprintf(stderr, "用法: %s info <名字>\n", argv[0]);
        return;
    }
    else{
    printf("你好，%s\n", argv[2]);
    }
}


int main(int argc, char *argv[]) {

    if (argc == 1) {
        printf("没有提供任何命令，请参考以下帮助信息：\n\n");
        help();
    }

    
    else if (strcmp(argv[1], "info") == 0) {

        if (argc > 3) {
            fprintf(stderr, "'info' 命令不需要额外参数，多余的参数将被忽略\n");
        }
        else{
        command_info();
        }
    } 

    else if (strcmp(argv[1], "--help") == 0) {
        help();
    }  
    
    else {
        fprintf(stderr, "错误: 未知命令 '%s'\n", argv[1]);
        fprintf(stderr, "请使用 '--help' 查看支持的命令\n");
        return 1; 
    }
    
    return 0;
}