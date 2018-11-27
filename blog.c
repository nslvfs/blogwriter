#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.c"

int main(int argc, char *argv[])
{
        FILE * fPtr;
        FILE * nPtr;
        char target[] = "/var/www/messages.txt";
        char temp[] = "/var/www/temp.txt";
        char rss[] = "/var/www/html/rss.xml";
        char ch;
        char text[10000];
        char pseudo[20];
        char *pos;

        struct tm *newtime;
        time_t long_time;

        int lines = countLines(target);

        fPtr = fopen(target, "r");
        nPtr = fopen(temp, "w");

        if(fPtr == NULL)
        {
                fPtr = fopen(target, "w");
                if(fPtr == NULL) {
                        printf("tut nicht target\n");
                        exit(EXIT_FAILURE);
                }
        }

        if (nPtr == NULL)
        {
                fclose(fPtr);
                printf("tut nicht temp\n");
                exit(EXIT_FAILURE);
        }
        if(argc != 2){
                printf("nenne dein pseudonym cowboy: \n");
                fgets(pseudo, sizeof pseudo, stdin);

                if ((pos=strchr(pseudo, '\n')) != NULL)
                        *pos = '\0';

                printf("\n\ndann schreib mal 1 blogartikel mein sohn:\n");
                fgets(text, sizeof text, stdin);

                if ((pos=strchr(text, '\n')) != NULL)
                        *pos = '\0';

                printf("\n\n");
        } else {
                strcpy(pseudo,"vfs");
                strcpy(text, argv[1]);
        }

        time( &long_time );
        newtime = localtime( &long_time );

        fprintf(nPtr,"<span id='%d'><small><a href='#%d'>#</a> <b>%d.%d.%d %d:%d</b> von %s</small></span>\n",lines,lines,newtime->tm_mday,newtime->tm_mon+1,newtime->tm_year+1900,newtime->tm_hour, newtime->tm_min,pseudo);
        fprintf(nPtr,"<p>%s</p>\n<hr />\n",text);

        while ((ch = fgetc(fPtr)) != EOF)
        fputc(ch, nPtr);

        fclose(nPtr);
        fclose(fPtr);

        remove(target);
        rename(temp, target);

        createRSS(rss,temp,pseudo,text,lines);


        return 0;
}
