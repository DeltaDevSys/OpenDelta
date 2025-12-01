#ifndef FILES_H
#define FILES_H

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

void add_file();

void add_dir();

void del();

void displayFile(const char *fileName);

void showThisDir();

void goToDir(const char *path);

void list();

#endif
