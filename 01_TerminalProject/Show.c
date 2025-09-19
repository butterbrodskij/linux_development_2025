#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DX 2
#define BUF_SIZE 1024

// very long comment for test: 1234567890123456789012345678901234567890123456789012345678901234567890

void read_line(FILE *fp, char *s, int max_line) {
    fgets(s, max_line, fp);
    size_t len = strlen(s);
    if (len == 0) {
        s[0] = '\0';
        return;
    }
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
        return;
    }

    char buffer[BUF_SIZE];

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            return;
        }
    }

    return;
}

int main(int argc, char **argv) {
    if (!(initscr())) {
        fprintf(stderr, "Error initialising nsurses\n");
        exit(1);
    }

    if (argc < 2) {
        fprintf(stderr, "Error parsing argv\n");
        exit(1);
    }

    char *file_name = argv[1];
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    WINDOW *win, *frame;

    noecho();
    cbreak();
    curs_set(0);

    printw("space to scroll\nesc to close");
    refresh();

    frame = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, 1, file_name);
    wrefresh(frame);

    win = newwin(LINES-2*DX-2, COLS-2*DX-2, DX+1, DX+1);

    keypad(win, TRUE);
    scrollok(win, TRUE);

    for (int i = 0; i < LINES-2*DX-2; i++) {
        char line[COLS-2*DX-2];
        read_line(fp, line, COLS-2*DX-2);
        wprintw(win, "\n%s", line);
    }

    wrefresh(win);

    for(int c = wgetch(win); c != 27; c = wgetch(win)) {
        if (c == ' ' && !feof(fp)) {
            char line[COLS-2*DX-2];
            read_line(fp, line, COLS-2*DX-2);
            wprintw(win, "\n%s", line);
        }
    }

    fclose(fp);

    delwin(win);
    delwin(frame);

    endwin();
}