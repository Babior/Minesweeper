#ifndef PJC_PROJECT_1_FIELD_H
#define PJC_PROJECT_1_FIELD_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "setup.h"

using namespace std;
using namespace sf;

class Field {
private:
    int l;
    int m;
    int f;
    int *row;;
    int *col;
    Texture texture;
    Sprite sprite;
    ifstream inputFile;
    ofstream outputFile;
    bool isRunning;
    bool isWon;

    int w = 64;
    int **gridLogic = nullptr;
    int **gridView = nullptr;

    int read_file_size();
    void recursion(int, int);
public:
    Field(int lvl);
    ~Field();
    int getW();
    int getF();
    int getL();
    bool getIsRunning();
    bool getIsWon();
    void set_flags();
    void init_variables();
    void init_field();
    void init_from_file();
    void init_borders();
    void init_mines();
    void draw_opened();
    void add_flag(int, int);
    void open_cell(int, int);
    bool check_win();
    void render(RenderTarget* target);
    void out();
};


#endif //PJC_PROJECT_1_FIELD_H
