#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 
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

        printf("\n");
        scanf("%d",&cmd);

        switch (cmd)
        {
        case 0:
            exit = true;
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
