#ifndef COMMANDS_H
#define COMMANDS_H

#define MAX_LINES 512
#define MAX_LINE_LENGTH 1024
#define MAX_CONTENT_LENGTH 2048
#define MAX_ARGUMENT_LENGTH 256
#define MAX_USER_NAME_LENGTH 128
#define MAX_OS_TITLE_LANGTH 128
#define MAX_HOST_NAME_LENGTH 128
#define MAX_QUANTITY_OF_COMMANDS 256

typedef struct {
    const char *user_name[MAX_USER_NAME_LENGTH];
    const char *os_title[MAX_OS_TITLE_LANGTH];
    const char *host_name[MAX_HOST_NAME_LENGTH];
    const char *cpu[128];
    const char *gpu[128];
    double disk_memory[32768];
} UserInfo;

typedef struct {
    int number_of_versions[16];
    const char *phoenix[128];
    const char *signalmann[128];
    const char *teemagnat[128];
    const char *hanz_hanz[128];
    const char *iwgnig[128];
    const char *neu_delta[128];
    const char *deltonium[128];
    const char *open_dlt_sh[128];    
} Versions;

typedef struct {
	int quantity_of_commands[MAX_QUANTITY_OF_COMMANDS];
} Commands;

void your_version();

void editor();


void print_fetch();

#endif
