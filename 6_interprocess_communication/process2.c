#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

int main()
{
    int fd, ch;
    int characters = 0, words = 0, lines = 0;
    int inword = 0, last = '\n';

    fd = open("fifo1", O_RDONLY);

    while(read(fd, &ch, 1) > 0)
    {
        last = ch;

        if(ch != '\n')
            characters++;

        if(ch == '\n')
            lines++;

        if(isspace(ch))
            inword = 0;
        else if(inword == 0)
        {
            words++;
            inword = 1;
        }
    }

    close(fd);

    if(characters > 0 && last != '\n')
        lines++;

    FILE *fp = fopen("result.txt", "w");

    fprintf(fp, "Characters: %d\n", characters);
    fprintf(fp, "Words: %d\n", words);
    fprintf(fp, "Lines: %d\n", lines);

    fclose(fp);

    fd = open("fifo2", O_WRONLY);

    fp = fopen("result.txt", "r");

    while((ch = fgetc(fp)) != EOF)
        write(fd, &ch, 1);

    fclose(fp);
    close(fd);

    return 0;
}
