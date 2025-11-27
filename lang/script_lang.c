/* constants for types */
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
    const char *string_type[MAX_STRING_TYPE_LENGTH];
    const char *character_type[MAX_CHAR_TYPE_LENGTH];
    const char *integer_type[MAX_INT_TYPE_LENGTH];
    const char *bool_type[MAX_BOOL_TYPE_LENGTH];
} TypesNames; 


void set_keyword() 
{
    Keywords keywords = {
        .for_keyword = "for",
        .while_keyword = "while",
        .if_keyword = "if",
        .then_keyword = "then",
        .else_keyword = "else",
        .let_keyword = "let",
        .func_keyword = "func"
    };
}

void set_symbols() 
{
    SpecificSymbols symbols = {
        .double_ampersand = "&&",
        .double_vertical_lines = "||",
        .plus = "+",
        .minus = "-",
        .star = "*",
        .slash = "/",
        .dollar = "$"
    };
}

void set_types()
{
    TypesNames types = {
        .integer_type = ": int",
        .character_type = ": char",
        .string_type = ": str",
        .bool_type = ": bool"
    };
}
