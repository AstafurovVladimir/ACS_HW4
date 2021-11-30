#ifndef PLANT_H
#define PLANT_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Tree.h"
#include "Bush.h"
#include "Flower.h"

enum type {
    TREE, BUSH, FLOWER
};
struct Plant {
    enum type type;
    union {
        Tree* tree;
        Bush* bush;
        Flower* flower;
    };
    char* name;
};
void WriteTree(Plant plant, FILE* outputPath);
void WriteBush(Plant plant, FILE* outputPath);
void WriteFlower(Plant plant, FILE* outputPath);
extern "C" double CountVowels(void *str, int len);
extern "C" void HeapSort(void *arr, void *pos, int len);
#endif
