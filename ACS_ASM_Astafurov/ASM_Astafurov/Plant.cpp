#include "stdio.h"
#include "Plant.h"

void WriteBush(Plant plant, FILE* outputPath) {
    fprintf(outputPath, "Bush: ");
    fprintf(outputPath, plant.name);
    fprintf(outputPath, " that blossoms in ");
    fprintf(outputPath, "%i", plant.bush->month);
    fprintf(outputPath, "\n");
}

void WriteFlower(Plant plant, FILE* outputPath) {
    fprintf(outputPath, "Flower: ");
    fprintf(outputPath, plant.name);
    fprintf(outputPath, " of ");
    fprintf(outputPath, "%i", plant.flower->type);
    fprintf(outputPath, " type\n");
}

void WriteTree(Plant plant, FILE* outStream) {
    fprintf(outStream, "Tree: ");
    fprintf(outStream, plant.name);
    fprintf(outStream, " of age ");
    fprintf(outStream, "%i", plant.tree->age);
    fprintf(outStream, "\n");
}
