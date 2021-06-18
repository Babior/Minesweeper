#include <iostream>
#include <sstream>
#include "Field.h"

using namespace std;
using namespace sf;

Field::Field(int lvl) {
    switch (lvl)
    {
        case 0:
            l = 12;
            m = 10;
            break;
        case 1:
            l = 18;
            m = 40;
            break;
        case 2:
            l = 25;
            m = 99;
            break;
        case 3:
            inputFile.open("input.txt");
            if (!inputFile)
            {
                std::cout << "Error, file couldn't be opened" << endl;
                exit(0);
            }
            l = read_file_size() + 2;
            break;
        default:
            break;;
    }

    init_variables();

    row = {new int[8]{-1, -1, -1, 0, 0, 1, 1, 1}};
    col = {new int[8]{-1, 0, 1, -1, 1, -1, 0, 1}};

    texture.loadFromFile("../images/tiles.png");
    sprite.setTexture(texture);

    this->gridLogic = new int *[l];
    this->gridView = new int *[l];
    for (int i = 0; i < l; ++i)
    {
        this->gridLogic[i] = new int[l];
        this->gridView[i] = new int[l];
    }
}

Field::~Field() {

}

int Field::getW() {
    return w;
}

int Field::getF() {
    return f;
}

int Field::getL() {
    return l;
}

bool Field::getIsRunning() {
    return isRunning;
}

bool Field::getIsWon() {
    return isWon;
}

void Field::set_flags() {
    f -= 1;
}

void Field::init_variables() {
    isRunning = true;
    isWon = false;
    f = m;
}

void Field::init_field() {
    for (int i = 0; i < l; ++i)
    {
        for (int j = 0; j < l; ++j)
        {
            this->gridLogic[i][j] = 0;
            this->gridView[i][j] = 10;
        }
    }
}

void Field::init_from_file() {
    inputFile.open("input.txt");
    string line;
    string token;
    stringstream iss;
    int i = 1, val;
    while (getline(inputFile, line))
    {
        iss << line;
        istringstream ss(line);
        int j = 1;
        while (getline(iss, token, ' '))
        {
            stringstream ss;
            ss << token;
            ss >> val;
            this->gridLogic[i][j] = val;
            ++j;
        }
        iss.clear();
        ++i;
    }
    inputFile.close();
}

int Field::read_file_size() {
    std::ifstream fin("input.txt");
    int val = 0, cols = 0, numItems = 0;

    while (fin.peek() != '\n' && fin >> val)
        ++numItems;
    cols = numItems;// # of columns found

    return cols;
}

void Field::init_borders() {
    for (int i = 0; i < l; ++i)
    {
        this->gridLogic[0][i] = -1;
        this->gridLogic[i][0] = -1;
        this->gridLogic[l - 1][i] = -1;//l-1
        this->gridLogic[i][l - 1] = -1;//b-1
    }
}

void Field::init_mines() {
    srand(time(nullptr));
    int mines = 0;
    while (mines < m)
    {
        int x = rand() % (l - 3) + 1;
        int y = rand() % (l - 3) + 1;
        if (this->gridLogic[x][y] != 9)
        {
            this->gridLogic[x][y] = 9;
            for (int i = 0; i < 8; ++i)
            {
                if (this->gridLogic[x + row[i]][y + col[i]] != -1 && this->gridLogic[x + row[i]][y + col[i]] != 9)
                    this->gridLogic[x + row[i]][y + col[i]]++;
            }
            mines++;
        }
    }
}

void Field::recursion(int move_row, int move_col) {
    this->gridView[move_row][move_col] = this->gridLogic[move_row][move_col];
    for (int i = 0; i < 8; ++i)
    {
        if (this->gridView[move_row + row[i]][move_col + col[i]] == 10)
        {
            if (this->gridLogic[move_row + row[i]][move_col + col[i]] > 0 &&
                this->gridLogic[move_row + row[i]][move_col + col[i]] < 9)
            {
                this->gridView[move_row + row[i]][move_col + col[i]] = this->gridLogic[move_row + row[i]][move_col +
                                                                                                          col[i]];
            } else if (this->gridLogic[move_row + row[i]][move_col + col[i]] == 0)
            {
                recursion(move_row + row[i], move_col + col[i]);
            }
        }
    }
}

void Field::add_flag(int x, int y) {
    if (getIsRunning())
    {
        gridView[x][y] = 11;
        set_flags();
    }
}

void Field::open_cell(int x, int y) {
    if (gridLogic[x][y] == 9)
    {
        this->isRunning = false;
        draw_opened();
    } else if (gridLogic[x][y] == 0)
    {
        recursion(x, y);
    } else
    {
        gridView[x][y] = gridLogic[x][y];
    }

    if (check_win())
    {
        this->isWon = true;
        this->isRunning = false;
    }
}

bool Field::check_win() {
    int opened = 0;
    for (int i = 1; i <= this->l - 1; ++i)
    {
        for (int j = 1; j <= this->l - 1; ++j)
        {
            if (this->gridView[i][j] != 10 && this->gridView[i][j] != 11)
            {
                opened++;
            }
        }
    }
    if (opened == (l - 2) * (l - 2) - m)
    {
        return true;
    }
    return false;
}

void Field::draw_opened() {
    for (int i = 1; i < l - 1; i++)
    {
        for (int j = 1; j < l - 1; j++)
        {
            gridView[i][j] = gridLogic[i][j];
        }
    }
}

void Field::render(RenderTarget *target) {
    for (int i = 1; i < l - 1; i++)
    {
        for (int j = 1; j < l - 1; j++)
        {
            sprite.setTextureRect(IntRect(gridView[i][j] * getW(), 0, getW(), getW()));
            sprite.setPosition(j * getW(), i * getW() + 10);
            target->draw(sprite);
        }
    }
}

void Field::out() {
    for (int i = 0; i <= this->l - 1; ++i)
    {
        for (int j = 0; j <= this->l - 1; ++j)
        {
            std::cout << this->gridLogic[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << "\n";
}

