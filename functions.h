// Functions Header File - Nifty Mountains Assignment - Deniz Jasarbasic:

#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "apmatrix.h"

#define display_width 844
#define display_height 795

using namespace std;

// GLOBAL STRUCTURES:

// Allegro Fonts:
typedef struct FONT {

    ALLEGRO_FONT* body;
    ALLEGRO_FONT* title;

} FONT;

// Allegro Colors:
typedef struct COLOR {

    ALLEGRO_COLOR colorBestGreedyCyan;
    ALLEGRO_COLOR colorGreedyAllRowsRed;
    ALLEGRO_COLOR colorBestLowGreedyGreen;
    ALLEGRO_COLOR colorBestImprovedGreedyPurple;

} COLOR;

// FUNCTION PROTOTYPES BY FILE NAMES:

/**** Allegro Setup ****/
void must_init(bool test, const char *description);
void display_init();
void display_deinit();
void font_init();
void font_deinit();
void keyboard_init();
bool escapeProgram();
void primitive_init();
void scale_init();
void scale_deinit();
void color_init(COLOR &color);

/**** Data Manipulation ****/
void readData(string fileName, apmatrix<short> &terrainData, int dataRows, int dataCols);
short findMax(apmatrix<short> &terrainData);
short findMin(apmatrix<short> &terrainData);

/**** User Interface ****/
// Draw Map & legend:
int mapMenu();
void drawMap(apmatrix<short> &terrainData, int minValue, int maxValue, int userSelection);
void drawLegend(apmatrix<short> &terrainData);

// Draws Paths using function pointer to draw various algorithms using a single function:
int drawLowestElevPath(apmatrix<short> &terrainData, int startRow, ALLEGRO_COLOR color, int (*f)(apmatrix<short> &, int &, ALLEGRO_COLOR, int));
int drawReverseGreedyElevPath(apmatrix<short> &terrainData, int startRow, ALLEGRO_COLOR color);

// Results:
void outputResults(int bestGreedyElevation, int bestLowElevation, int bestImprovedElevation, int indexBestGreedyRow, int indexLowGreedyRow, int indexImprovedGreedyRow);

/**** Path Algorithms ****/
// Algorithms:
int greedyAlgorithm(apmatrix<short> &terrainData, int &currentRow, ALLEGRO_COLOR color, int currentCol);
int lowGreedyAlgorithm(apmatrix<short> &terrainData, int &currentRow, ALLEGRO_COLOR color, int currentCol);

// Compute & determine lowest elev path:
int computeLowestElevPath(apmatrix<short> &terrainData, int startRow, ALLEGRO_COLOR color);
int computeLowestLowElevPath(apmatrix<short> &terrainData, int startRow, ALLEGRO_COLOR color);
int computeReverseGreedyElevPath(apmatrix<short> &terrainData, int startRow, ALLEGRO_COLOR color);

// Index row of lowest elev path:
int indexOfLowestElevPath(apmatrix<short> &terrainData, int (*f)(apmatrix<short> &, int, ALLEGRO_COLOR));
