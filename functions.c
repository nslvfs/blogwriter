int countLines(char filename[100])
{
        FILE *fp;
        int count = 0;
        char c;
        fp = fopen(filename, "r");
        for (c = getc(fp); c != EOF; c = getc(fp)) {
                if (c == '\n')
                        count = count + 1;
        }
        fclose(fp);
        return count;
}

void createRSS(char xss[100], char temp[100],char pseudo[20], char text[10000],int lines)
{
        FILE *xssPtr;
        FILE *tempPtr;
        int header = 7;
        int count = 0;
        char c;
        char ch;

        xssPtr = fopen(xss, "r");
        tempPtr = fopen(temp,"w");

        if (tempPtr == NULL)
        {
                fclose(tempPtr);
                printf("tut nicht temp\n");
                exit(EXIT_FAILURE);
        }

        if(xssPtr == NULL)
        {
                xssPtr = fopen(xss, "w");
                if(xssPtr == NULL) {
                        printf("tut nicht target\n");
                        exit(EXIT_FAILURE);
                }
        }

        fprintf(tempPtr,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        fprintf(tempPtr,"<rss version=\"2.0\">\n");
        fprintf(tempPtr,"<channel>\n");
        fprintf(tempPtr,"<title>Neuschwabenlandblog</title>\n");
        fprintf(tempPtr,"<link>https://blog.neuschwabenland.net</link>\n");
        fprintf(tempPtr,"<description>Der offizielle Neuschwabenlandblog</description>\n");
        fprintf(tempPtr,"<language>de</language>\n");
        fprintf(tempPtr,"<item>\n");
        fprintf(tempPtr,"<title>%s</title>\n",text);
        fprintf(tempPtr,"<link>https://blog.neuschwabenland.net/index.html#%d</link>\n",lines);
        fprintf(tempPtr,"<guid>https://blog.neuschwabenland.net/index.html#%d</guid>\n",lines);
        fprintf(tempPtr,"</item>");

        for (c = getc(xssPtr); c != EOF; c = getc(xssPtr)) {
                if (c == '\n')
                        count = count + 1;
                if(count >= 7 && count < 58)
                        fputc(c, tempPtr);
                if(count == 58)
                        break;
        }

        if(count >= 58) {
                fprintf(tempPtr,"</channel>\n");
                fprintf(tempPtr,"</rss>");
        }
        fclose(tempPtr);
        fclose(xssPtr);
        remove(xss);
        rename(temp,xss);
}
