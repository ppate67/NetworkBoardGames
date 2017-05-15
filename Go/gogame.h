#ifndef GOGAME_H
#define GOGAME_H

#define MIN_DIST 2
#define MAX_DIST 19

#define BLACK 1
#define WHITE 2
#define EMPTY 0

#include <vector>
#include <QtCore>

using namespace std;

// the algorithm class of Go Game
// use node structure
class gogame
{
public:
    struct Board
    {
        int label, value;
        int row, col;
    };

    struct Node
    {
        vector<Board> board;
        int turn, pass, ok;
        QString text;
    };

    enum{
      TOKEN_NONE, TOKEN_BLACK, TOKEN_WHITE, TOKEN_ADD, TOKEN_ADD_BLACK, TOKEN_ADD_WHITE, TOKEN_PLAY,
      TOKEN_TAKE, TOKEN_PASS, TOKEN_LABEL, TOKEN_NUMBER, TOKEN_MARK, TOKEN_TRIANGLE, TOKEN_CIRCLE,
      TOKEN_SQUARE, TOKEN_PLAY_BLACK, TOKEN_PLAY_WHITE, TOKEN_COMMENT, TOKEN_TIME, TOKEN_EVENT,
      TOKEN_PLACE, TOKEN_DATE, TOKEN_RESULT, TOKEN_SIZE, TOKEN_KOMI, TOKEN_HANDICAP
    };

    //some functions of node
    int firstNode();
    int lastNode();
    int preNode(int k=1);
    int nextNode(int k=1);

    int points[MAX_DIST][MAX_DIST];
    int marks[MAX_DIST][MAX_DIST];
    int areas[MAX_DIST][MAX_DIST];

    int width, height, size;
    int turn, pass, mode, path;
    int index1, index2;
    int star[18];

    vector<Node> tree1, tree2;
    QString BOARD_EVENT, BOARD_DATE;
    QString PLAYER_BLACK, PLAYER_WHITE;
    QString BLACK_LEVEL, WHITE_LEVEL;
    QString BOARD_HANDICAP, BOARD_KOMI;
    QString BOARD_RESULT, BOARD_FILE;

    int read(QString path, int k=0);
    void reset(int x = 19, int y = 19);
    void clear();
    int getBoard(QString &buffer, int i, int j);
    int plays(int x, int y, int color);
    int add(int x, int y, int color);
    int otherColor(int  color);
    int checkBound(int x, int y);
    int getColor(int x, int y);
    int getAlpha(int x, int y);
    void treeCut();
    Board makeBoard(int label, int value, int x, int y);

    void check(int x, int y, int color, Node *node);
    void checkAll(int x, int y, int color, Node *node);
    int checkLiberty(int x, int y, int color);
    void capture(int x, int y, int color, Node *node);
    int getNumber(QString &buffer, int i, int j);
    QString getText(QString &buffer, int i, int j);
};
#endif // GOGAME_H
