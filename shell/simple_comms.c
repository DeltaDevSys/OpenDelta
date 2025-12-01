#include <stdio.h>

#define T_RED "\033[38;2;255;0;0m"
#define T_GREEN "\033[38;2;0;255;0m"
#define T_BLUE "\033[38;2;0;0;255m"
#define T_YELLOW "\033[38;2;255;255;0m"
#define T_CYAN "\033[38;2;0;255;255m"
#define T_RESET "\033[0m"
#define T_MAGENTA "\033[0;35m"

void help()
{
    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("| 1.dlt-fetch: как неофетч, но для нашей ОС.         | 11.help - вывод списка команд и их значение. |\n");
    printf("| 2.calc - калькулятор.                              | 12.quit - выход из dltsh.                    |\n");
    printf("| 3.list - выводит список файлов в текущем каталоге. | 13.cls - очистка экрана.                     |\n");
    printf("| 4.std - показывает путь к текущей директории.      | 14.ver - вывод текущей версии dltsh.         |\n");
    printf("| 5.gtd - переходит в какую-либо папку.              |                                              |\n");
    printf("| 6.display - выводит содержимое файла.              |                                              |\n");
    printf("| 7.del - удаление папки или файла.                  |                                              |\n");
    printf("| 8.add - создание файла или каталога.               |                                              |\n");
    printf("| 9.lsf - вывод всех файлов для работы ОС.           |                                              |\n");
    printf("| 10.dex - консольный текстовый редактор.            |                                              |\n");
    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
}

void files()
{
    const char frame[128] =        T_CYAN    "[===================]\n" T_RESET;
    const char c_lang[128] =       T_CYAN    "| [C language]      |\n" T_RESET;
    const char term_dot_c[128] =   T_CYAN    "|  [term.c]         |\n" T_RESET;
    const char comm_dot_c[115] =   T_CYAN    "|  [commands.c]     |\n" T_RESET;
    const char strt_dot_c[115] =   T_CYAN    "|  [simple_comms.c] |\n" T_RESET;
    const char add_dot_c[115] =    T_CYAN    "|  [files.c]        |\n" T_RESET;
    const char add_dot_h[115] =    T_CYAN    "|  [files.h]        |\n" T_RESET;
    const char strt_dot_h[115] =   T_CYAN    "|  [simple_comms.h] |\n" T_RESET;
    const char comm_dot_h[115] =   T_CYAN    "|  [commands.h]     |\n" T_RESET;
    const char bash[115] =         T_GREEN   "| [bash]            |\n" T_RESET;
    const char start_dot_sh[115] = T_GREEN   "|  [build.sh]       |\n" T_RESET;
    const char text[115] =         T_YELLOW  "| [txt]             |\n" T_RESET;
    const char logo_dot_txt[115] = T_YELLOW  "|   [unkhnown]      |\n" T_RESET;
    const char bin[115] =          T_MAGENTA "| [binary]          |\n" T_RESET;
    const char bin_file[115] =     T_MAGENTA "|  [term.elf]       |\n" T_RESET;
    const char end_frame[114] =    T_CYAN    "[===================]\n" T_RESET;

    printf("%s", frame);
    printf("%s", c_lang);
    printf("%s", term_dot_c);
    printf("%s", comm_dot_c);
    printf("%s", comm_dot_h);
    printf("%s", add_dot_c);
    printf("%s", add_dot_h);
    printf("%s", strt_dot_h);
    printf("%s", strt_dot_c);
    printf("%s", bash);
    printf("%s", start_dot_sh);
    printf("%s", text);
    printf("%s", logo_dot_txt);
    printf("%s", bin);
    printf("%s", bin_file);
    printf("%s", end_frame);
}

void write_logo()
{
    printf(T_CYAN " ___________       ___________  ___          _________________            ____ \n" T_RESET);
    printf(T_CYAN " | |      XX       | |     | |  |  |         |______   ______|            //XX  \n" T_RESET);
    printf(T_CYAN " | |       XX      | |     | |  |  |                | |                  //  XX  \n" T_RESET);
    printf(T_CYAN " | |        XX     | |     | |  |  |                | |                 //    XX  \n" T_RESET);
    printf(T_CYAN " | |         XX    |_|_____|_|  |  |                | |                //      XX  \n" T_RESET);
    printf(T_CYAN " | |          XX   | |          |  |                | |               //        XX  \n" T_RESET);
    printf(T_CYAN " | |           XX  | |          |  |                | |              //==========XX  \n" T_RESET);
    printf(T_CYAN " | |           //  | |     ___  |  |      ___       | |             //            XX  \n" T_RESET);
    printf(T_CYAN " | |          //   | |     | |  |  |      | |       | |            //              XX  \n" T_RESET);
    printf(T_CYAN " | |_________//    |_|_____|_|  |__|______|_|       |_|           //                XX  \n" T_RESET);
}

void welcome()
{
    const char frstln[] = ".____________________________.";
    const char newlin[] = "|                            |";
    const char scndln[] = "|FFFFFFFFFFFFFFFFFFFFFFFFFFFF|";
    const char thrdln[] = "|[ Welcome to the DeltaOS!  ]|";
    const char frthln[] = "|FFFFFFFFFFFFFFFFFFFFFFFFFFFF|";
    const char endlne[] = "|____________________________|";

    printf("%s\n", frstln);
    printf("%s\n", newlin);
    printf("%s\n", thrdln);
    printf("%s\n", endlne);
    printf(T_CYAN "[впешите help для того чтобы узнать большинство команд]\n" T_RESET);
}

