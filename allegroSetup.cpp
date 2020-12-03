// Allegro Setup CPP File - Nifty Mountains Assignment - Deniz Jasarbasic:

#include "functions.h"

extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* elevScale;
extern FONT font;

/*************INPUT**************/

// Modular function that test all allegro functions and addons before running the program.
void must_init(bool test, const char *description) {

    if(test)
        return;

    //If allegro and its addons cannot be intizalized, returns error and name of troubled function or addon.
    cout << endl << "ERROR! Couldn't initialize " << description;
    exit(1);
}

void display_init() {

    // Anti-aliasing (makes primitives and images smoother)
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    // Allegro Display:
    disp = al_create_display(display_width, display_height);
    must_init(disp, "display");
}

void keyboard_init() {

    // Allegro Keyboard:
    must_init(al_install_keyboard(), "keyboard");
}

// Allegro Primitives and Images:

void primitive_init() {

    must_init(al_init_primitives_addon(), "primitives");
}

void scale_init() {

    must_init(al_init_image_addon(), "image addon");
    elevScale = al_load_bitmap("images/elevationScale.png");
    must_init(elevScale, "elevation scale");
}

void font_init() {

    al_init_font_addon();
    al_init_ttf_addon();

    // Title Font:
    font.title = al_load_font("fonts/arial.ttf", 20, 0);
    must_init(font.title, "Title font");

    // Body/Text Font:
    font.body = al_load_font("fonts/arial.ttf", 14, 0);
    must_init(font.body, "Textbody font");
}

void display_deinit() {

    al_destroy_display(disp);
}

void scale_deinit() {

   al_destroy_bitmap(elevScale);
}

void font_deinit() {

    al_destroy_font(font.title);
    al_destroy_font(font.body);
}

void color_init(COLOR &color) {

    color.colorBestGreedyCyan = al_map_rgb(0, 255, 255);
    color.colorGreedyAllRowsRed = al_map_rgb(255, 0, 0);
    color.colorBestLowGreedyGreen = al_map_rgb(57, 255, 20);
    color.colorBestImprovedGreedyPurple =  al_map_rgb(255,0,255);
}

bool escapeProgram() {

    ALLEGRO_KEYBOARD_STATE key_state;

    al_get_keyboard_state(&key_state);

    return al_key_down(&key_state, ALLEGRO_KEY_ESCAPE);
}
