// Data Manipulation CPP File - Nifty Mountains Assignment - Deniz Jasarbasic:

#include "functions.h"

/*************DATA INPUT**************/

void readData(string fileName, apmatrix<short> &terrainData, int dataRows, int dataCols) {

    // Input file object declared which contains a message and a keyword.
    ifstream dataFile(fileName);

    if (!dataFile.is_open()) {
        cout << "Error! No file found." << endl;
        exit(1); // Exit program when file cannot open.
    }

    else {

        for (int i = 0; i < dataRows; i++) {

            for (int j = 0; j < dataCols; j++) {

                dataFile >> terrainData[i][j];
            }
        }

        dataFile.close();
    }
}

/*************DATA PROCESS**************/

short findMax(apmatrix<short> &terrainData) {

    // Initializing max element as INT_MIN
    int maxElement = terrainData[0][0];

    // If an element is greater than maxElement, update maxElement.
    for (int i = 0; i < terrainData.numrows(); i++) {
        for (int j = 0; j < terrainData.numcols(); j++) {
            if (terrainData[i][j] > maxElement) {
                maxElement = terrainData[i][j];
            }
        }
    }

    /*************DATA OUTPUT**************/
    return maxElement;
}

/*************DATA PROCESS**************/

short findMin(apmatrix<short> &terrainData) {

    // Initializing max element as INT_MIN
    int minElement = terrainData[0][0];

    // If an element is greater than maxElement, update maxElement.
    for (int i = 0; i < terrainData.numrows(); i++) {
        for (int j = 0; j < terrainData.numcols(); j++) {
            if (minElement > terrainData[i][j]) {
                minElement = terrainData[i][j];
            }
        }
    }

    /*************DATA OUTPUT**************/
    return minElement;
}
