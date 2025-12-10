#ifndef SCRIPT_LANG_H
#define SCRIPT_LANG_H

#define MAX_STRING_TYPE_LENGTH 1024
#define MAX_CHAR_TYPE_LENGTH 512
#define MAX_INT_TYPE_LENGTH 1024
#define MAX_BOOL_TYPE_LENGTH 128

typedef struct {
    const char *for_keyword[128];
    const char *while_keyword[128];
    const char *if_keyword[128];
    const char *then_keyword[128];
    const char *else_keyword[128];
    const char *let_keyword[128];
    const char *func_keyword[128];
    const char *type_keyword[128];
    const char *struct_keyword[128];
    const char *import_keyword[128];
    const char *extern_keyword[128];
} Keywords;

typedef struct {
    const char *double_ampersand[3];
    const char *double_vertical_lines[2];
    const char *plus;
    const char *minus;
    const char *star;
    const char *slash;
    const char *dollar;
} SpecificSymbols;

typedef struct {
    const char *double_ampersand_val[128];
    const char *double_vertical_lines_val[128];
    const char *plus_value[128];
    const char *minus_value[128];
    const char *star_values[128];
    const char *slash_values[128];
    const char *dollar_value[128];
} ValueForSymbols;

typedef struct {
    const char *string_type[MAX_STRING_TYPE_LENGTH];
    const char *character_type[MAX_CHAR_TYPE_LENGTH];
    const char *integer_type[MAX_INT_TYPE_LENGTH];
    const char *bool_type[MAX_BOOL_TYPE_LENGTH];
} TypesNames; 

void set_keyword();

void set_symbols();

void set_values();

void set_types();

#endif
