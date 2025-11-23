#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 6

char** initialize_lab(int size) {
	char **lab = malloc(sizeof(char*) * (size*2+1));
	for (int i = 0; i < size*2+1; i++) {
		lab[i] = malloc(size*2+1);
		for (int j = 0; j < size*2+1; j++) {
			if (i % 2 && j % 2) {
				lab[i][j] = '.';
			} else {
				lab[i][j] = '#';
			}
		}
	}
	return lab;
}

int get_neighbours(int *neighbours, char *checked, int room, int neigh_size, int size) {
	if (room % size && !checked[room-1]) {
		checked[room-1] = 1;
		neighbours[neigh_size++] = room-1;
	}
	if ((room+1) % size && !checked[room+1]) {
		checked[room+1] = 1;
		neighbours[neigh_size++] = room+1;
	}
	if (room / size && !checked[room-size]) {
		checked[room-size] = 1;
		neighbours[neigh_size++] = room-size;
	}
	if (room / size < size-1 && !checked[room+size]) {
		checked[room+size] = 1;
		neighbours[neigh_size++] = room+size;
	}
	return neigh_size;
}

int get_candidates(int candidates[4], char *checked, int room, int size) {
	int can_size = 0;
	if (room % size && checked[room-1]) {
		candidates[can_size++] = room-1;
	}
	if ((room+1) % size && checked[room+1]) {
		candidates[can_size++] = room+1;
	}
	if (room / size && checked[room-size]) {
		candidates[can_size++] = room-size;
	}
	if (room / size < size-1 && checked[room+size]) {
		candidates[can_size++] = room+size;
	}
	return can_size;
}

void print_and_free_lab(char **lab, int size) {
	for (int i = 0; i < size*2+1; i++) {
		for (int j = 0; j < size*2+1; j++) {
			printf("%c", lab[i][j]);
		}
		free(lab[i]);
		printf("\n");
	}
	free(lab);
}

int main(int argc, char **argv) {
	srand(time(NULL));
	char **lab = initialize_lab(SIZE);

	int first_room = rand() % (SIZE*SIZE);
	char *checked = calloc(SIZE*SIZE, sizeof(char));
	char *neighboured = calloc(SIZE*SIZE, sizeof(char));
	checked[first_room] = 1;
	neighboured[first_room] = 1;
	int *neighbours = malloc(SIZE*SIZE * sizeof(int));
	int neighbours_size = get_neighbours(neighbours, neighboured, first_room, 0, SIZE);

	for (int i = 1; i < SIZE*SIZE; i++) {
		int next_room_idx = rand() % neighbours_size;
		int next_room = neighbours[next_room_idx];
		checked[next_room] = 1;
		neighbours[next_room_idx] = neighbours[--neighbours_size];
		int candidates[4];
		int candidates_size = get_candidates(candidates, checked, next_room, SIZE);
		int door_choice = candidates[rand() % candidates_size];
		int door_i = door_choice / SIZE + next_room / SIZE + 1;
		int door_j = door_choice % SIZE + next_room % SIZE + 1;
		lab[door_i][door_j] = '.';
		neighbours_size = get_neighbours(neighbours, neighboured, next_room, neighbours_size, SIZE);
	}

	print_and_free_lab(lab, SIZE);
	free(checked);
	free(neighboured);

	return 0;
}
