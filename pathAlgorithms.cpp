// Montain Path Algorithms CPP File - Nifty Mountains Assignment - Deniz Jasarbasic:

#include "functions.h"
#include <limits.h>
#include <time.h>

extern COLOR color;

/*************PROCESS**************/

int greedyAlgorithm(apmatrix<short> &terrainData, int &currentRow, ALLEGRO_COLOR color, int currentCol) {

    srand(time(0));
    int fwdUp = 0, fwd = 0, fwdDown = 0;

    // Calculate the changes in elevations:

    fwd = abs(terrainData[currentRow][currentCol] - terrainData[currentRow][currentCol+1]);

    if (currentRow > 0) { // If only above row 0, allow the intilization of fwdUp.
        fwdUp = abs(terrainData[currentRow][currentCol] - terrainData[currentRow-1][currentCol+1]);
    }
    if (currentRow < (terrainData.numrows()-1)) { // If below the last row, allow the intilization of fwdDown.
        fwdDown = abs(terrainData[currentRow][currentCol] - terrainData[currentRow+1][currentCol+1]);
    }

    if (currentRow > 0 && currentRow < (terrainData.numrows()-1)) {

        if (fwdUp < fwdDown && fwdUp < fwd) {
            currentRow--;
            return abs(fwdUp);
        }

        else if (fwdDown < fwdUp && fwdDown < fwd) {
            currentRow++;
            return abs(fwdDown);
        }

        else if (fwd < fwdUp && fwd < fwdDown) {
            return abs(fwd);
        }

        else if (fwd == fwdDown || fwd == fwdUp) {
            return abs(fwd);
        }

        else if (fwdUp == fwdDown && (fwdUp < fwd || fwdDown < fwd)) {

            // "Flip a coin" to decide which direction to go.
            int randNum = rand() % 2;

            if (randNum == 0) {
                currentRow--;
                return abs(fwdUp);
            }

            else {
                currentRow++;
                return abs(fwdDown);
            }
        }
    }

    else if (currentRow == 0) {

        // If at row 0, the path can only go fwd or fwd-down.

        if (fwd < fwdDown) {
            return abs(fwd);
        }

        else if (fwd == fwdDown) {
            return abs(fwd);
        }

        else if (fwdDown < fwd) {
            currentRow++;
            return abs(fwdDown);
        }
    }

    else if (currentRow == (terrainData.numrows()-1)) {

        // If on the last row, the path can only go fwd or fwd-up.

        if (fwd < fwdUp) {
            return abs(fwd);
        }

        else if (fwd == fwdUp) {
            return abs(fwd);
        }

        else if (fwdUp < fwd) {
            currentRow--;
            return abs(fwdUp);
        }

    }

    exit(1); // Return an error if no condition are met.
}

int lowGreedyAlgorithm(apmatrix<short> &terrainData, int &currentRow, ALLEGRO_COLOR color, int currentCol) {

    srand(time(0));

    int fwdUp = 0, fwd = 0, fwdDown = 0;
    int fwdUpChange = 0, fwdChange = 0, fwdDownChange = 0;

    fwd = abs(terrainData[currentRow][currentCol+1]);
    fwdChange = abs(terrainData[currentRow][currentCol] - terrainData[currentRow][currentCol+1]); // Accout for elevation change (fwd).

    if (currentRow > 0) {
        fwdUp = abs(terrainData[currentRow-1][currentCol+1]);
        fwdUpChange = abs(terrainData[currentRow][currentCol] - terrainData[currentRow-1][currentCol+1]); // Accout for elevation change (fwdUp).
    }

    if (currentRow < (terrainData.numrows()-1)) {
        fwdDown = abs(terrainData[currentRow+1][currentCol+1]);
        fwdDownChange = abs(terrainData[currentRow][currentCol] - terrainData[currentRow+1][currentCol+1]); // Accout for elevation change (fwdDown).
    }

    if (currentRow > 0 && currentRow < (terrainData.numrows()-1)) {

        if (fwdUp < fwdDown && fwdUp < fwd) {
            currentRow--;
            return abs(fwdUpChange);
        }

        else if (fwdDown < fwdUp && fwdDown < fwd) {
            currentRow++;
            return abs(fwdDownChange); // Prioritize going down hill.
        }

        else if (fwd < fwdUp && fwd < fwdDown) {
            return abs(fwdChange);
        }

        else if (fwd == fwdDown || fwd == fwdUp) {
            currentRow++;
            return abs(fwdDownChange);
        }

        else if (fwdDown == fwdUp && fwdDown < fwd) {
            currentRow++;
            return abs(fwdDownChange);
        }

        else if (fwdUp == fwdDown && fwdUp < fwd) {
            currentRow--;
            return abs(fwdUpChange);
        }

    }

    else if (currentRow == 0) {

        // If at row 0, the path can only go fwd or fwd-down.

        if (fwd < fwdDown) {
            return abs(fwdChange);
        }

        else if (fwd == fwdDown) {
            currentRow++;
            return abs(fwdDownChange);
        }

        else if (fwdDown < fwd) {
            currentRow++;
            return abs(fwdDownChange);
        }
    }

    else if (currentRow == (terrainData.numrows()-1)) {

        // If on the last row, the path can only go fwd or fwd-up.

        if (fwd < fwdUp) {
            return abs(fwdChange);
        }

        else if (fwd == fwdUp) {
            return abs(fwdChange);
        }

        else if (fwdUp < fwd) {
            currentRow--;
            return abs(fwdUpChange);
        }
    }

    exit(1); // Return an error if no condition are met.
}

int computeLowestElevPath(apmatrix<short> &terrainData, int startRow, ALLEGRO_COLOR color) {

    int totalGreedyElevChange = 0, currentRow = startRow;

    // Determine and draw lowest elevation for a row:
    for (int currentCol = 0; currentCol < terrainData.numcols()-1; currentCol++) {

        totalGreedyElevChange += greedyAlgorithm(terrainData, currentRow, color, currentCol);
        al_draw_filled_rectangle(currentCol, currentRow, (currentCol+1), (currentRow+1), color);
    }

    return totalGreedyElevChange;
}

int computeLowestLowElevPath(apmatrix<short> &terrainData, int startRow, ALLEGRO_COLOR color) {

    int totalLowGreedyElevChange = 0, currentRow = startRow;

    // Determine lowest elevation for a row:
    for (int currentCol = 0; currentCol < terrainData.numcols()-1; currentCol++) {

        totalLowGreedyElevChange += lowGreedyAlgorithm(terrainData, currentRow, color, currentCol);
    }

    return totalLowGreedyElevChange;
}

int computeReverseGreedyElevPath(apmatrix<short> &terrainData, int startRow, ALLEGRO_COLOR color) {

    int totalGreedyElevChange = 0;
    srand(time(0));

    int randCol = (rand() % ((terrainData.numcols()-1) - 0 + 1)) + 0;

    int currentRow = startRow;

    // Determine lowest elevation for a row (west-east):
    for (int currentCol = randCol; currentCol > 0; currentCol--) {

        totalGreedyElevChange += greedyAlgorithm(terrainData, currentRow, color, currentCol);
    }

    currentRow = startRow;

    // Determine lowest elevation for a row (east-west):
    for (int currentCol = randCol; currentCol < terrainData.numcols()-1; currentCol++) {

        totalGreedyElevChange += greedyAlgorithm(terrainData, currentRow, color, currentCol);
    }

    return totalGreedyElevChange;
}

// Using a function pointer determine the row with the lowest elevation change of any path algorithm.
int indexOfLowestElevPath(apmatrix<short> &terrainData, int (*f)(apmatrix<short> &, int, ALLEGRO_COLOR)) {

    int lowestElevPath = 0, lowestChange = INT_MAX, currentChange = 0;
    color.colorGreedyAllRowsRed = al_map_rgb(255, 0, 0);

    for (int i = 0; i < terrainData.numrows()-1; i++) {

        currentChange = (*f)(terrainData, i, color.colorGreedyAllRowsRed );

        if (currentChange < lowestChange) {
            lowestChange = currentChange;
            lowestElevPath = i;
        }
    }

    return lowestElevPath;
}
