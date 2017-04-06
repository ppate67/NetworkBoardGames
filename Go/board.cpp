#include <cstdio>
#include <cstring>
#include <cctype>
#include <fstream>

#include "board.h"

//the cpp file
//the main algorithm of Go Game

//clear gui
void Board::Clear()
{
    std::vector<Node>().swap(Tree);
    std::vector<Node>().swap(Tree2);

    Node node;
    node.Turn = BLACK;
    node.Pass = 0;
    Tree.push_back(node);

    Turn = BLACK;
    Mode = 3; // play black and white
    Index = 0;
    Index2 = -1;
    Path = 0;
    Pass = 0;

    memset(Point, 0, sizeof(Point));
    memset(Mark, 0, sizeof(Point));
    memset(Area, 0, sizeof(Point));
}

// reset
void Board::Reset(int x, int y)
{
    if (x > MAX_BOARD) x = MAX_BOARD;
    else if (x < MIN_BOARD) x = MIN_BOARD;
    if (y > MAX_BOARD) y = MAX_BOARD;
    else if (y < MIN_BOARD) y = MIN_BOARD;

    Size = Width = x;
    Height = y;

    int a = 3;
    int b = Size - 4;
    int c = (Size - 1) / 2;

    Star[0] = a; Star[1] = a;
    Star[2] = b; Star[3] = a;
    Star[4] = a; Star[5] = b;
    Star[6] = b; Star[7] = b;
    Star[8] = c; Star[9] = c;
    Star[10] = c; Star[11] = a;
    Star[12] = a; Star[13] = c;
    Star[14] = b; Star[15] = c;
    Star[16] = c; Star[17] = b;

    Clear();
}


int Board::CheckBound(int x, int y)
{
    return (x >= 0 && y >= 0 && x < Width && y < Height);
}

//get the color of chess
int Board::GetColor(int x, int y)
{
    return Point[y][x];
}


void Board::Print()
{
    char Color[3] = {'.', 'X', 'O'};

    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            printf("%c ", Color[GetColor(x, y)]);
        }
        printf("\n");
    }
    printf("\n");
}

int Board::OtherColor(int color)
{
    return (color ^ 3);
}

Board::Property Board::MakeProperty(int label, int value, int x, int y)
{
    Property Prop;

    Prop.Label = label;
    Prop.Value = value;
    Prop.Row = x;
    Prop.Col = y;

    return Prop;
}

void Board::Capture(int x, int y, int color, Node *n)
{
    if (CheckBound(x, y) && GetColor(x, y) == color) {
        Point[y][x] = 0;
        n->Prop.push_back(MakeProperty(TOKEN_TAKE, color, x, y));

        Capture(x - 1, y, color, n);
        Capture(x + 1, y, color, n);
        Capture(x, y - 1, color, n);
        Capture(x, y + 1, color, n);
    }
}

int Board::CheckLiberty(int x, int y, int color)
{
    if (CheckBound(x, y))
    {
        int k = GetColor(x, y);
        if (k == EMPTY) return 1;
        if (k != color || Mark[y][x] == Path) return 0;

        // visit
        Mark[y][x] = Path;

        // found liberty
        if (CheckLiberty(x - 1, y, color)) return 1;
        if (CheckLiberty(x + 1, y, color)) return 1;
        if (CheckLiberty(x, y - 1, color)) return 1;
        if (CheckLiberty(x, y + 1, color)) return 1;
    }

    return 0;
}

// check for capture
void Board::Check(int x, int y, int color, Node *node)
{
    if (CheckBound(x, y) && GetColor(x, y) == color) {
        Path = Path + 1;
        if (CheckLiberty(x, y, color) == 0)
            Capture(x, y, color, node);
    }
}

void Board::CheckAll(int x, int y, int color, Node *node)
{
    int color2 = OtherColor(color);

    // capture other
    Check(x - 1, y, color2, node);
    Check(x + 1, y, color2, node);
    Check(x, y - 1, color2, node);
    Check(x, y + 1, color2, node);

    // capture this
    Check(x, y, color, node);
}

// test play color
