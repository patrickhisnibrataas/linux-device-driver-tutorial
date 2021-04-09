#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*** Function prototypes ***/
static void get_param_value(void);
static void set_param_value(void);

bool read_line(char* file_path, char* buffer, size_t size);
bool write_line(char* file_path, char* line);
 
int main()
{
    int cmd;

    printf("************************************\n");
    printf("****** User space application ******\n");
    printf("************************************");

    while (true) {
        bool exit = false;

        printf("\n\n*************************\n");
        printf("*** Select an option: ***\n");
        printf("*************************\n\n");
        printf("0. exit program\n");
        printf("1. read param_value\n");
        printf("2. set param_value\n");

        printf("\n");
        scanf("%d",&cmd);

        switch (cmd)
        {
        case 0:
            exit = true;
            break;
        case 1:
            get_param_value();
            break;
        case 2:
            set_param_value();
            break;
        default:
            printf("Invalid option entered\n");
            break;
        }

        if (exit == true)
            break;

        while(getchar()!='\n');
        getchar();
    };

    return 0;
}

/*** Functions ***/
static void get_param_value(void) {
    char buffer[10];
    read_line("/sys/module/devicedriver/parameters/parameter_value", &buffer[0], 10);
    printf("param_value is: %s", buffer);
}

static void set_param_value(void) {
    char value[10];
    printf("Input value to write: ");
    scanf("%s",&value);
    write_line("/sys/module/devicedriver/parameters/parameter_value", &value[0]);
}

/*** Helper functions ***/
bool read_line(char* file_path, char* buffer, size_t size) {
    FILE *file;
    file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Unable to open file: %s", file_path);
        return false;
    }

    fgets(buffer, size, file);
    fclose(file);
    return true;
}

bool write_line(char* file_path, char* line) {
    FILE *file;
    file = fopen(file_path, "w");
    if (file == NULL) {
        printf("Unable to open file: %s", file_path);
        return false;
    }

    fputs(line, file);
    fclose(file);
    return true;
}
