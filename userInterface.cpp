// User Interface (UI) CPP File - Nifty Mountains Assignment - Deniz Jasarbasic:

#include "functions.h"
#include <iomanip>

extern FONT font;
extern ALLEGRO_BITMAP* elevScale;
extern COLOR color;

/*************OUTPUT**************/

int mapMenu() {

    int userResponse = 0;

    cout << "Please select a map type: " << endl << endl;
    cout << "    1. Detailed Terrain Map (shows elevation heights by color)" << endl;
    cout << "    2. Interpolated Colored Map (shows reletive elevation heights)" << endl;
    cout << "    3. GrayScale Map" << endl << endl;

    cout << " (Enter 1, 2, or 3): ";
    cin >> userResponse;

    system("cls");

    return userResponse;
}


void drawMap(apmatrix<short> &terrainData, int minValue, int maxValue, int userSelection) {

    int color, r = 0, g = 0, b = 0;

    for (int i = 0; i < terrainData.numrows(); i++) {
        for (int j = 0; j < terrainData.numcols(); j++) {

        // Intilize color:
        color = (float(terrainData[i][j]) - minValue) / (maxValue - minValue) * 256;

        if (userSelection == 1) {

            if (terrainData[i][j] < 3000) {
                r = 40, g = color, b = 40;
            } else      if (terrainData[i][j] > 3000 && terrainData[i][j] < 3100) {
                r = 255, g = 255, b = 60;
            } else if (terrainData[i][j] > 3100 && terrainData[i][j] < 3400) {
                r = 160, g = 90, b = 55;
            } else if (terrainData[i][j] > 3400 && terrainData[i][j] < 3600) {
                r = 150, g = 82, b = 45;
            } else if (terrainData[i][j] > 3600 && terrainData[i][j] < 4300) {
                r = 120, g = 50, b = 19;
            } else if (terrainData[i][j] > 4300) {
                r = 40, g = 0, b = 0;
            }
        }

        else if (userSelection == 2) {

            float pct = (float(terrainData[i][j]) - minValue) / (maxValue - minValue);

            r = (155 - 0) * pct + 0;
            g = (0-155) * pct + 155;
            b = 0;
        }

        else if (userSelection == 3) {

            r = color;
            g = color;
            b = color;
        }

        ALLEGRO_COLOR c = al_map_rgb(r, g, b);
        al_draw_filled_rectangle(j, i, (j+1), (i+1), c);

        }
    }
}

void drawLegend(apmatrix<short> &terrainData) {

    // Elevation scale values:
    int minScale = findMin(terrainData);
    int maxScale = findMax(terrainData);

    // Set and intializing of allegro colors after allegro has been intilized
    color_init(color);

    // Draw divider line:
    al_draw_line(display_width, 483, 0, 483, al_map_rgb(255,255,255), 3);

    // Title:
    al_draw_text(font.title, al_map_rgb(255, 255, 255), 276, 500, 0, "NIFTY MOUNTAIN MAP LEGEND");
    al_draw_text(font.body, al_map_rgb(255, 255, 255), 620, 503, 0, "PRESS ESC TO EXIT");

    // Body Text of moutain paths:
    al_draw_text(font.title, al_map_rgb(255, 255, 255), 20, 540, 0, "Mountain Paths: ");
    al_draw_text(font.body, color.colorBestGreedyCyan, 40, 582, 0, "■  Best Greedy Walking Path (Greedy Algorithm)");
    al_draw_text(font.body, color.colorGreedyAllRowsRed, 40, 612, 0, "■   Greedy Walking Path for each row (Greedy Algorithm)");
    al_draw_text(font.body, color.colorBestLowGreedyGreen, 40, 637, 0, "■   Best Low Greedy Walking Path (Low Greedy Algorithm)");
    al_draw_text(font.body, color.colorBestImprovedGreedyPurple, 40, 667, 0, "■   Best Greedy Walking Path (Improved Greedy Algorithm)");

    // Color-coded lines:
    al_draw_line(360, 592, 812, 592, color.colorBestGreedyCyan, 4);
    al_draw_line(415, 621, 812, 621, color.colorGreedyAllRowsRed, 2);
    al_draw_line(420, 647, 812, 647, color.colorBestLowGreedyGreen, 4);
    al_draw_line(425, 677, 812, 677, color.colorBestImprovedGreedyPurple, 5);

    // Body Text of moutain elevation scale:
    al_draw_text(font.title, al_map_rgb(255, 255, 255), 20, 705, 0, "Mountain Elevation Scale: ");
    al_draw_bitmap(elevScale, 200, 663, 0); // Custom elevation scale image.

    al_draw_textf(font.body, al_map_rgb(255, 255, 255), 220, 747, 0, "+%d m", minScale);
    al_draw_textf(font.body, al_map_rgb(255, 255, 255), 590, 747, 0, "+%d m", maxScale);
}

// Using a function pointer, draw any path algorithm:
int drawLowestElevPath(apmatrix<short> &terrainData, int startRow, ALLEGRO_COLOR color, int (*f)(apmatrix<short> &, int &, ALLEGRO_COLOR, int)) {

    int totalGreedyElevChange = 0, currentRow = startRow;

    for (int currentCol = 0; currentCol < terrainData.numcols()-1; currentCol++) {

        totalGreedyElevChange += (*f)(terrainData, currentRow, color, currentCol);
        al_draw_filled_rectangle(currentCol, currentRow, (currentCol+3), (currentRow+3), color);
    }

    return totalGreedyElevChange;
}

// Draw specific reverse Greedy Algorithm:
int drawReverseGreedyElevPath(apmatrix<short> &terrainData, int startRow, ALLEGRO_COLOR color) {

    int totalGreedyElevChange = 0;
    srand(time(0));

    int randCol = (rand() % ((terrainData.numcols()-1) - 0 + 1)) + 0;

    int currentRow = startRow;

    for (int currentCol = randCol; currentCol > 0; currentCol--) {

        totalGreedyElevChange += greedyAlgorithm(terrainData, currentRow, color, currentCol);
        al_draw_filled_rectangle(currentCol, currentRow, (currentCol+3), (currentRow+3), color);
    }

    currentRow = startRow;

    for (int currentCol = randCol; currentCol < terrainData.numcols()-1; currentCol++) {

        totalGreedyElevChange += greedyAlgorithm(terrainData, currentRow, color, currentCol);
        al_draw_filled_rectangle(currentCol, currentRow, (currentCol+3), (currentRow+3), color);
    }

    return totalGreedyElevChange;
}

// Output path results, meaningful analysis, and insighful statistics (efficiency metric):
void outputResults(int bestGreedyElevation, int bestLowElevation, int bestImprovedElevation, int indexBestGreedyRow, int indexLowGreedyRow, int indexImprovedGreedyRow) {

    cout << "Elevation Results: " << endl << endl;

    cout << "    Best Total Change in Elevation (Greedy Algorithm): " << bestGreedyElevation << "m" << endl;
    cout << "    Best Greedy Path Row: " << indexBestGreedyRow << endl << endl;
    cout << "    Best Total Change in Elevation (Low Greedy Algorithm): " << bestLowElevation << "m" << endl;
    cout << "    Best Low Greedy Path Row: " << indexLowGreedyRow << endl << endl;
    cout << "    Best Total Change in Elevation (Improved Greedy Algorithm): " << bestImprovedElevation << "m" << endl;
    cout << "    Best Improved Greedy Path Row: " << indexImprovedGreedyRow << endl << endl;

    // Calculates percentage of effiecency:
    cout << "    The Low Greedy Alogrithm was " << fixed << setprecision(2) << 100 - (float(bestLowElevation)/bestGreedyElevation * 100) << "% more efficent than the Greedy Algorithm." << endl;
    cout << "    The Improved Greedy Alogrithm was " << fixed << setprecision(2) << 100 - (float(bestImprovedElevation)/bestGreedyElevation * 100) << "% more efficent than the Greedy Algorithm." << endl;
}
