/**************************************************************************************************************************
 *  Name: Deniz Jasarbasic                           Nifty Mountains assignment                               2020/09/21  *
 *                                                                                                                        *
 *  DESCRIPTION: This program reads in a set of topographic elevation data into a 2D array and write methods to compute   *
 *  various paths through the mountains as well as visualize them using the Allegro graphics library.  This program will  *
 *  also return various total elevation changes given different "best" paths from east to west across the mountain.       *
 **************************************************************************************************************************/

#include "functions.h"

// Declaration of allegro addons, functions, and structs:
ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* elevScale;
FONT font;
COLOR color;

// Modular function that test that all allegro addons and functions are set and pre-initialized before main.
void must_init(bool test, const char *description);

int main() {

    // Declaration and initialization of all local variables and 2D array:
    int bestGreedyElevation = 0, bestLowElevation = 0, bestImprovedElevation = 0;
    int indexBestGreedyRow = 0, indexLowGreedyRow = 0, indexImprovedGreedyRow = 0;

    const int dataRows = 480, dataCols = 844;
    short minValue = 0, maxValue = 0;

    apmatrix<short> terrainData(dataRows, dataCols);

    /*************INPUT**************/

    int userSelection = mapMenu();

    while (userSelection == 1 || userSelection == 2 || userSelection == 3) {

        // initialization of all allegro addons and functions:
        must_init(al_init(), "allegro");
        keyboard_init();
        display_init();
        font_init();
        primitive_init();
        scale_init();

        // Reads any topographic data into an 2D array given an input/data file:
        readData("colorado.dat", terrainData, dataRows, dataCols);

        // Set and intializing of allegro colors after allegro has been intilized
        color_init(color);

        /*************PROCESS**************/

        // Find min and max elements of the matrix.
        maxValue = findMax(terrainData);
        minValue = findMin(terrainData);

        // Draw the map given the topographic data and its attributes (min and max values):
        drawMap(terrainData, minValue, maxValue, userSelection);

        // Determine the greedy path from each row without drawing, and returns best row:
        indexLowGreedyRow = indexOfLowestElevPath(terrainData, computeLowestLowElevPath);
        indexImprovedGreedyRow = indexOfLowestElevPath(terrainData, computeReverseGreedyElevPath);

        /*************OUTPUT**************/
        // Only draws all rows of regulary greedy, but also returns best row. Saves drawing time and memory if drawn in this instance.
        indexBestGreedyRow = indexOfLowestElevPath(terrainData, computeLowestElevPath);

        // Draws the best greedy paths given the best rows:
        bestGreedyElevation = drawLowestElevPath(terrainData, indexBestGreedyRow, color.colorBestGreedyCyan, greedyAlgorithm);
        bestLowElevation = drawLowestElevPath(terrainData, indexLowGreedyRow, color.colorBestLowGreedyGreen, lowGreedyAlgorithm);
        bestImprovedElevation = drawReverseGreedyElevPath(terrainData, indexImprovedGreedyRow, color.colorBestImprovedGreedyPurple);

        // Output results and draw the mountain legend:
        outputResults(bestGreedyElevation, bestLowElevation, bestImprovedElevation, indexBestGreedyRow, indexLowGreedyRow, indexImprovedGreedyRow);
        drawLegend(terrainData);

        al_flip_display();

        // Allegro program continues to run unless the user exits the program via the ESC key.
        while (!escapeProgram());

        // De-initialization of all allegro functions and addons:
        font_deinit();
        scale_deinit();
        display_deinit();

        break; // Break out of loop once program is completed;

    }

    return 0; // Sucessfull run!
}
