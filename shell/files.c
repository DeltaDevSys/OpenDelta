#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lib/commands.h"

#ifdef _WIN32
    #include <direct.h>
    #define mkdir(path, mode) _mkdir(path)
    #define chdir _chdir
    #define getcwd _getcwd
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <stdlib.h>
#endif

/* colors */
#define T_RED "\033[38;2;255;0;0m"
#define T_GREEN "\033[38;2;0;255;0m"
#define T_BLUE "\033[38;2;0;0;255m"
#define T_YELLOW "\033[38;2;255;255;0m"
#define T_CYAN "\033[38;2;0;255;255m"
#define T_RESET "\033[0m"
#define T_MAGENTA "\033[0;35m"

/* constants */
#define MFNL 256 //maximum file name length
#define MAX_TOKEN_LENGTH 1024
#define MAX_FOLDER_NAME_LENGTH 1024
#define MAX_CONTENT_LENGTH 1024
#define MAX_LINES 512
#define MAX_LINE_LENGTH 1024
#define MAX_FOLDER_LENGTH 128
#define MAX_PATH_LENGTH 128

struct file_explorer {
    char fileName[MFNL];
    char token[MAX_TOKEN_LENGTH];
    char line[MAX_LINES];
    char folderName[MAX_FOLDER_LENGTH];
    char cwd[MAX_FOLDER_NAME_LENGTH];
    FILE * file;
    int numFiles;
    int isCreated;
    int isDeleted;
    int isDisplaying;
};

/* add file */
void add_file()
{
    struct file_explorer var;

    printf(T_CYAN "[🖹 введите имя файла]: \n" T_RESET);
    scanf("%s\n", var.fileName);
    printf(T_CYAN "[файл '%s' создан]\n" T_RESET, var.fileName);

    int isCreated = 0;
    var.file = fopen(var.fileName, "w");
    if (var.file == NULL) {
        printf(T_RED "[ошибка создания файла]\n" T_RESET);
        var.isCreated = 0;
    }
    else {
        fclose(var.file);
        var.isCreated = 1;
    }
}

/* add dir */
void add_dir()
{
    struct file_explorer var;

    printf(T_CYAN "[🗀 введите имя папки]: \n" T_RESET);
    scanf("%s\n", var.folderName);
    mkdir(var.folderName, 0777);
    printf(T_CYAN "[папка '%s' создана]\n" T_RESET, var.folderName);

    if (var.file == NULL) {
        printf(T_RED "[ошибка создания папки]\n" T_RESET);
        var.isCreated = 1;
    }
    else {
        fclose(var.file);
        var.isCreated = 0;
    }
}

/* display content in file */
void displayFile(const char *fileName)
{
    
    struct file_explorer var;
    var.file = NULL;
    var.isDisplaying = 0;

    printf(T_CYAN "[🖹 введите имя файла]: " T_RESET);
    if (scanf("%511s", var.fileName) != 1) {
        printf(T_RED "[ошибка чтения имени файла]\n" T_RESET);
        return;
    }

    var.file = fopen(var.fileName, "r");
    if (var.file == NULL) {
        printf(T_RED "[ошибка открытия файла для чтения: %s]\n" T_RESET, var.fileName);
        return;
    }

    var.isDisplaying = 1;
    while (fgets(var.line, sizeof(var.line), var.file) != NULL) {
        fputs(var.line, stdout);
    }

    fclose(var.file);
    var.isDisplaying = 0;
}

/* delete file */
void del()
{
    struct file_explorer var;

    printf(T_CYAN "[введите что будем удалять(file/dir)]: \n" T_RESET);
    scanf("%s\n", &*var.token);
    if (strcmp(var.token, "file") == 0) {
        printf(T_CYAN "[🖹 введите имя файла]: \n" T_RESET);
        scanf("%s\n", &*var.fileName);

        var.isDeleted = 0;
        if (remove(var.fileName) == 0) {
            printf(T_GREEN "[файл '%s' удалён!]\n" T_RESET, var.fileName);
            var.isDeleted = 1;
        }
        else {
            printf(T_RED "[ошибка удаления файла]\n" T_RESET);
            var.isDeleted = 0;
        }
    }

    else if (strcmp(var.token, "dir") == 0) {
        printf(T_CYAN "[🗀 введите имя папки для удаления]: \n" T_RESET);
        scanf("%s\n", &*var.folderName);

        var.isDeleted = 0;
        if (remove(var.folderName) == 0) {
            printf(T_GREEN "[ папка '%s' удалена!]\n" T_RESET, var.folderName);
            var.isDeleted = 1;
        }
        else {
            printf(T_RED "[ошибка удаления папки]\n" T_RESET);
            var.isDeleted = 0;
        }
    }
}

/* go to directory */
void goToDir(const char *path)
{
    if (path == NULL) {
        fprintf(stderr, T_RED "[err]: [пустой путь]\n" T_RESET);
        return;
    }

    if (chdir(path) == 0) {
        printf(T_GREEN "[🗀 Успешно перешли в директорию]: %s\n" T_RESET, path);
    }
    else {
        perror("Ошибка при переходе в директорию");
    }
}

/* show this directory */
void showThisDir()
{
    struct file_explorer var = {0};
    if (getcwd(var.cwd, sizeof(var.cwd)) != NULL) {
        printf(T_CYAN "[🗀 текущая папка: '%s']\n" T_RESET, var.cwd);
    }
    else {
        printf(T_RED "[err]: [удалось определить путь к папке]\n" T_RESET);
    }
}

/* list files */
void list()
{
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL) {
        printf("Не удалось открыть текущую директорию.\n");
        return;
    }

    printf(T_CYAN "[🖹 Файлы в текущей директории]:\n" T_RESET);
    while ((de = readdir(dr)) != NULL) {

        if (de->d_name[0] != '.') {
            printf("%s\n", de->d_name);
        }
    }

    closedir(dr);
}
