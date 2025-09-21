#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DX 2
#define BUF_SIZE 1024

// very long comment for test: 123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

char* read_line(FILE *fp) {
    if (feof(fp)) return NULL;

    char buffer[BUF_SIZE];
    char *result = NULL;
    size_t total_len = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);

        char *tmp = realloc(result, total_len + len + 1);
        
        if (!tmp) {
            free(result);
            return NULL;
        }
        result = tmp;

        strcpy(result + total_len, buffer);
        total_len += len;

        if (total_len > 0 && result[total_len-1] == '\n') {
            result[total_len-1] = '\0';
            break;
        }
    }

    if (result == NULL) {
        result = malloc(1);
        if (result) result[0] = '\0';
    }
    
    return result;
}

void print_lines(WINDOW *win, char **buffer, int total_lines, int cur_line, int cur_col, int max_lines, int max_cols) {
    werase(win);

    for (int i = 0; i < max_lines; i++) {
        int line_i = cur_line + i;
        
        if (line_i >= total_lines || buffer[line_i] == NULL) {
            break;
        }

        char *line = buffer[line_i];
        size_t line_len = strlen(line);

        if (cur_col < line_len) {
            int available_width = max_cols-1;
            if (line_len - cur_col < available_width) {
                available_width = line_len - cur_col;
            }

            mvwaddnstr(win, i, 0, line + cur_col, available_width);
        } else {
            mvwaddnstr(win, i, 0, "", 0);
        }
    }
    
    wrefresh(win);
}

int load_more_lines(FILE *fp, char ***cache, int *cache_size, int *cur_size, int lines_needed) {
    if (feof(fp)) return 0;

    for (int i = 0; i < lines_needed; i++) {
        if (*cur_size >= *cache_size) {
            int new_cache_size = *cache_size * 2;
            char **new_cache = realloc(*cache, sizeof(char*) * new_cache_size);
            if (!new_cache) {
                return -1;
            }

            *cache = new_cache;
            for (int j = *cache_size; j < new_cache_size; j++) {
                (*cache)[j] = NULL;
            }
            *cache_size = new_cache_size;
        }
        
        (*cache)[*cur_size] = read_line(fp);
        if (!(*cache)[*cur_size]) {
            return i;
        }
        (*cur_size)++;
    }
    
    return lines_needed;
}

int main(int argc, char **argv) {
    if (!(initscr())) {
        fprintf(stderr, "Error initialising nsurses");
        exit(1);
    }

    if (argc < 2) {
        endwin();
        fprintf(stderr, "Error parsing argv");
        exit(1);
    }

    char *file_name = argv[1];
    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        endwin();
        fprintf(stderr, "Error opening file");
        exit(1);
    }

    WINDOW *win, *frame;

    noecho();
    cbreak();
    curs_set(0);

    printw("esc to close\n");
    printw("space to scroll | arrows to navigate | PgUp/PgDown to scroll by blocks");
    refresh();

    frame = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, 1, file_name);
    wrefresh(frame);

    win = newwin(LINES-2*DX-2, COLS-2*DX-2, DX+1, DX+1);

    keypad(win, TRUE);
    scrollok(win, TRUE);

    int cache_size = LINES-2*DX-2;
    int cur_size = 0;
    char **cache = malloc(sizeof(char*) * cache_size);

    if (!cache) {
        fclose(fp);
        endwin();
        fprintf(stderr, "Memory allocation failed");
        exit(1);
    }

    for (int i = 0; i < cache_size; i++) {
        cache[i] = NULL;
    }

    int initial_lines = (LINES-2*DX-2) * 2;
    load_more_lines(fp, &cache, &cache_size, &cur_size, initial_lines);

    int cur_line = 0;
    int cur_col = 0;
    int max_display_lines = LINES-2*DX-2;

    print_lines(win, cache, cur_size, cur_line, cur_col, max_display_lines, COLS-2*DX-2);
    wrefresh(win);

    for(int c = wgetch(win); c != 27; c = wgetch(win)) {
        int lines_to_load = 0;

        switch (c)
        {
        case ' ':
            cur_line++;
            if (cur_line > cur_size - 2*max_display_lines) {
                lines_to_load = max_display_lines;
            }
            break;
        case KEY_UP:
            if (cur_line > 0) {
                cur_line--;
            }
            break;
        case KEY_DOWN:
            cur_line++;
            if (cur_line > cur_size - 2*max_display_lines) {
                lines_to_load = max_display_lines;
            }
            break;
        case KEY_LEFT:
            if (cur_col > 0) {
                cur_col--;
            }
            break;
        case KEY_RIGHT:
            cur_col++;
            break;
        case KEY_PPAGE:
            cur_line -= max_display_lines;
            if (cur_line < 0){
                cur_line = 0;
            }
            break;
        case KEY_NPAGE:
            cur_line += max_display_lines;
            if (cur_line >= cur_size - max_display_lines) {
                lines_to_load = max_display_lines * 2;
            }
            break;
        default:
            continue;
        }

        if (lines_to_load > 0 && !feof(fp)) {
            int loaded = load_more_lines(fp, &cache, &cache_size, &cur_size, lines_to_load);

            if (loaded == -1) {
                fprintf(stderr, "Reading file failed");
                break;
            }
        }

        if (cur_line > cur_size - max_display_lines) {
            cur_line = cur_size - max_display_lines > 0 ? cur_size - max_display_lines : 0;
        }

        print_lines(win, cache, cur_size, cur_line, cur_col, max_display_lines, COLS-2*DX-2);
    }

    for (int i = 0; i < cur_size; i++) {
        free(cache[i]);
    }
    free(cache);

    fclose(fp);

    delwin(win);
    delwin(frame);

    endwin();

    return 0;
}
