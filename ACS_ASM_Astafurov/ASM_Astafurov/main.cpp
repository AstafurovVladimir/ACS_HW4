#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "Plant.h"

bool CheckFile(char* filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

char* RandString() {
    const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
    int lenght = rand() % 10 + 2;
    char* str = new char[lenght];
    for (int i = 0; i < lenght; i++) {
        int pos = rand() % 26;
        str[i] = alphabet[pos];
    }
    str[lenght - 1] = '\0';
    return str;
}

bool FillFile(char* input_file, Plant* plants, int amount) {
    FILE* fp = fopen(input_file, "r");
    fscanf(fp, "%d%*c", &amount);
    if (amount < 1 || amount > 10000) {
        amount = 0;
        fclose(fp);
        return false;
    }
    for (int i = 0; i < amount; i++) {
        char* line = new char[500];
        int type = 0;
        fscanf(fp, "%d%*c", &type);
        Plant plant;
        if (type <= 0 || type > 3) {
            amount = 0;
            fclose(fp);
            return false;
        }
        fscanf(fp, "%[^\n]%*c", line);
        plant.name = line;
        line = new char[500];
        switch (type) {
            case 1:
                line = new char[500];
                plant.type = TREE;
                fscanf(fp, "%[^\n]%*c", line);
                plant.tree = new Tree;
                SetAge(plant.tree, atoi(line));
                break;
            case 2:
                plant.type = BUSH;
                fscanf(fp, "%[^\n]%*c", line);
                plant.bush = new Bush;
                SetMonth(plant.bush, atoi(line));
                break;
            case 3:
                plant.type = FLOWER;
                fscanf(fp, "%[^\n]%*c", line);
                plant.flower = new Flower;
                SetType(plant.flower, atoi(line));
                break;
        }
        plants[i] = plant;
        line = new char[500];
    }
    fclose(fp);
    return 1;
}

void FillRandom(int amount, Plant* plants){
    for (int i = 0; i < amount; i++) {
        int type = rand() % 3 + 1;
        Plant plant;
        plant.name = RandString();
        switch (type) {
            case 1:
                plant.type = TREE;
                plant.tree = new Tree;
                SetAge(plant.tree, rand() % 2001);
                break;
            case 2:
                plant.type = BUSH;
                plant.bush = new Bush;
                SetMonth(plant.bush, rand() % 12 + 1);
                break;
            case 3:
                plant.type = FLOWER;
                plant.flower = new Flower;
                SetType(plant.flower, rand() % 3 + 1);
                break;
        }
        plants[i] = plant;
    }
}

double NameFunction(Plant plant) {
    const char* vowels = "aeiyou";
    double length = strlen(plant.name);
    double vCount = 0;
    for (int i = 0; i < length; i++) {
        if (strchr(vowels, plant.name[i]) != NULL) {
            vCount++;
        }
    }
    return vCount / length;
}

void Write(char* outputPath, Plant* plants, int amount){
    FILE* file = fopen(outputPath, "w+");
    if (amount == 0) {
        fprintf(file, "Container was empty");
        return;
    }
    fprintf(file, "Container contains ");
    fprintf(file, "%d", amount);
    fprintf(file, " plants\n");
    for (int i = 0; i < amount; i++) {
        switch (plants[i].type)
        {
            case TREE:
                WriteTree(plants[i], file);
                break;
            case BUSH:
                WriteBush(plants[i], file);
                break;
            case FLOWER:
                WriteFlower(plants[i], file);
                break;
        }
    }
    fclose(file);
}

int main(int argc, char* argv[]) {
    clock_t begin = clock();
    srand(time(NULL));
    Plant* plants = new Plant[10000];
    long long* positions = new long long[10000];
    double* values = new double[10000];
    int amount = 0;
    if (argc != 5) {
        printf("Incorrect console parameters\n");
        return 1;
    }
    char* inputFile = new char[300];
    char* outputFile1 = new char[300];
    char* outputFile2 = new char[300];
    if (strcmp(argv[1], "file") == 0) {
        if (!CheckFile(argv[2])) {
            printf("Incorrect console parameters\n");
            return 1;
        }
        if (!FillFile(inputFile, plants, amount)) {
            printf("Error reading the input file\n");
            return 1;
        }
    }
    else if (strcmp(argv[1], "random") == 0) {
        amount = atoi(argv[2]);
        if (amount <= 0 || amount > 10000) {
            printf("Incorrect console parameters\n");
            return 1;
        }
        FillRandom(amount, plants);
    }
    else {
        printf("Incorrect console parameters\n");
        return 1;
    }
    if (!CheckFile(argv[3]) || !CheckFile(argv[4])) {
        printf("Incorrect console parameters\n");
        return 1;
    }
    strcpy(outputFile1, argv[3]);
    strcpy(outputFile2, argv[4]);
    Write(outputFile1, plants, amount);
    for (int i = 0; i < amount; i++) {
    	positions[i] = i;
    	values[i] = CountVowels(plants[i].name, strlen(plants[i].name));
    }
    HeapSort(values, positions, amount);
    Plant* plantsSorted = new Plant[10000];
    for (int i = 0; i < amount; i++) {
    	plantsSorted[i] = plants[positions[i]];
    }
    Write(outputFile2, plantsSorted, amount);
    clock_t end = clock();
    printf("Programm finished in ");
    printf("%f", (double)(end - begin) / CLOCKS_PER_SEC);
    printf(" seconds\n");
    free(plants);
}
