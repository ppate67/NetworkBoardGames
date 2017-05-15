#include <cstdio>
#include <cstring>
#include <cctype>
#include <fstream>

#include "gogame.h"

//the achievement of algorithm
gogame::Board gogame::makeBoard(int label, int value, int x, int y)
{
    Board board;
    board.label = label;  board.value = value;
    board.row = x; board.col = y;
    return board;
}

int gogame::getBoard(QString &buffer, int i, int j)
{
    QString string = buffer.mid(i+1, j-i-1);
    string = string.toUpper();
    if(string=="B")  return TOKEN_BLACK;
    if(string=="W") return TOKEN_WHITE;
    if(string=="C") return TOKEN_COMMENT;
    if(string=="SZ") return TOKEN_SIZE;
    if(string=="PB") return TOKEN_PLAY_BLACK;
    if(string == "PW") return TOKEN_PLAY_WHITE;
    if(string == "AB") return TOKEN_ADD_BLACK;
    if(string == "AW") return TOKEN_ADD_WHITE;
    if(string == "EV" || string == "TE") return TOKEN_EVENT;
    if(string == "LB") return TOKEN_LABEL;
    if(string == "MA") return TOKEN_MARK;
    if(string == "TR") return TOKEN_TRIANGLE;
    if(string == "CR") return TOKEN_CIRCLE;
    if(string == "SQ") return TOKEN_SQUARE;
    if(string == "DT" || string == "RD") return TOKEN_DATE;
    if(string == "KM" || string == "KO") return TOKEN_KOMI;
    if (string == "RE") return TOKEN_RESULT;
    return TOKEN_NONE;
}

int gogame::checkBound(int x, int y)
{
    return (x>=0&&y>=0&&x<width&&y<height);
}

void gogame::treeCut()
{
    if(int n= tree1.size()-index1-1){
        if(mode==3&&index2<0&&!BOARD_FILE.isEmpty()){
            tree2=tree1;
            index2=index1;
        }
        while(n--) tree1.pop_back();
    }
}

int gogame::add(int x, int y, int color)
{
    if (checkBound(x, y)&&getColor(x, y) == EMPTY) {
           points[y][x] = color;
           Node *node = &tree1[index1];
           node->board.push_back(makeBoard(TOKEN_ADD, color, x, y));
           checkAll(x, y, color, node);
           return 1;
       }
       return 0;
}

int gogame::otherColor(int color)
{
 return color^3;
}

int gogame::getAlpha(int x, int y)
{
    if (index2 >= 0) {
        for (int i = index2 + 1; i <= index1; i++) {
            Board board = tree1[i].board[0];
            if (board.label == TOKEN_PLAY) {
                if (x == board.row && y == board.col) {
                    if (board.value == BLACK) return 224;
                    return 192;
                }
            }
        }
    }
    return 255;
}

int gogame::checkLiberty(int x, int y, int color)
{
    if(checkBound(x,y)){
        int k=getColor(x,y);
        if(k==EMPTY) return 1;
        if(k!=color||marks[y][x]==path) return 0;
        marks[y][x]=path;
        if(checkLiberty(x-1, y, color)) return 1;
        if(checkLiberty(x+1, y, color)) return 1;
        if(checkLiberty(x, y-1, color)) return 1;
        if(checkLiberty(x, y+1, color)) return 1;
    }
    return 0;
}
void gogame::capture(int x, int y, int color, Node *node)
{
    if(checkBound(x, y)&&getColor(x,y)==color){
        points[y][x]=0;
        node->board.push_back(makeBoard(TOKEN_TAKE, color, x, y));
        capture(x-1, y, color, node);
        capture(x+1, y, color, node);
        capture(x, y-1, color, node);
        capture(x, y+1, color, node);
    }
}

void gogame::check(int x, int y, int color, Node *node)
{
    if(checkBound(x, y)&&getColor(x,y)==color){
        path=path+1;
        if(checkLiberty(x,y,color)==0) capture(x, y, color, node);
    }
}

void gogame::checkAll(int x, int y, int color, Node *node)
{
    int color2 = otherColor(color);
    check(x-1, y, color2, node);
    check(x+1, y, color2, node);
    check(x, y-1, color2, node);
    check(x, y+1, color2, node);
    check(x, y, color, node);
}

int gogame::plays(int x, int y, int color1)
{
    Node node;
    int color2 = otherColor(color1);
    if(checkBound(x, y)){
        if (getColor(x, y) == EMPTY) {
            treeCut();   points[y][x] = color1;   index1++;
            node.board.push_back(makeBoard(TOKEN_PLAY, color1, x, y));
            checkAll(x, y, color1, &node);
            turn = color2;   pass = 0;
            node.turn = turn;
            node.pass = pass;
            tree1.push_back(node);
            return 1;
        }
    }
    else{
        treeCut();  index1++;  pass++;
        node.board.push_back(makeBoard(TOKEN_PASS, color1, 0, 0));
        turn = color2;
        node.turn = turn;
        node.pass = pass;
        tree1.push_back(node);
        return 1;
    }
    return 0;
}

int gogame::getColor(int x, int y)
{
    return points[y][x];
}

int gogame::getNumber(QString &buffer, int i, int j)
{
    return buffer.mid(i+1, j-i-1).toInt();
}

QString gogame::getText(QString &buffer, int i, int j)
{
    return buffer.mid(i+1, j-i-1);
}

int gogame::read(QString path, int k)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)) return 0;
    QTextStream stream(&file);
    QString buffer = stream.readAll();
    file.close();
    int size = buffer.size();
    if(size<=0) return 0;
    int token = TOKEN_NONE;
    int v1 = -1, v2 = 0;
    int p = -1, q = -2;
    reset();
    BOARD_FILE = path;
    BOARD_EVENT.clear(); BOARD_DATE.clear();
    PLAYER_BLACK.clear(); PLAYER_WHITE.clear();
    BLACK_LEVEL.clear(); WHITE_LEVEL.clear();
    BOARD_RESULT.clear(); BOARD_KOMI.clear();
    BOARD_HANDICAP.clear();
    for (int i = 0; i < size; i++) {
        QChar c = buffer[i];
        if (c == '[' && v1 < 0) {
            v1 = i;
        }
        else if (c == ')' && v1 < 0) {
            break;
        }
        else if (c == '\\') {
            if (q >= 0 && i == q + 1) q = -2;
            else q = i;
        }
        else if (c == ']' && i != q + 1 && v1 >= 0) {
            v2 = i;
            if (p >= 0) token = getBoard(buffer, p, v1);
            if (token == TOKEN_BLACK || token == TOKEN_WHITE) {
                int color = (token == TOKEN_BLACK ? BLACK : WHITE);
                if (v2 - v1 == 3) {
                    plays(buffer[v1 + 1].toLower().toLatin1() - 'a', buffer[v1 + 2].toLower().toLatin1() - 'a', color);
                }
                else plays(-1, -1, color);
                if (--k == 0) return 1;
            }
            else if (token == TOKEN_ADD_BLACK || token == TOKEN_ADD_WHITE) {
                int color = (token == TOKEN_ADD_BLACK ? BLACK : WHITE);
                if (v2 - v1 == 3) {
                    add(buffer[v1 + 1].toLower().toLatin1() - 'a', buffer[v1 + 2].toLower().toLatin1() - 'a', color);
                }
            }
            else if (token == TOKEN_LABEL) {
                if (v2 - v1 >= 5 && buffer[v1 + 3] == ':') {
                    Board b;
                    b.label = TOKEN_LABEL;
                    b.value = buffer[v1 + 4].toLatin1();
                    b.row = buffer[v1 + 1].toLower().toLatin1() - 'a';
                    b.col = buffer[v1 + 2].toLower().toLatin1() - 'a';
                    tree1[index1].board.push_back(b);
                }
            }
            else if (token == TOKEN_MARK || token == TOKEN_TRIANGLE || token == TOKEN_CIRCLE || token == TOKEN_SQUARE) {
                if (v2 - v1 == 3) {
                    Board b;
                    b.label = token;
                    b.row = buffer[v1 + 1].toLower().toLatin1() - 'a';
                    b.col = buffer[v1 + 2].toLower().toLatin1() - 'a';
                    tree1[index1].board.push_back(b);
                }
            }
            else if (token == TOKEN_SIZE) {
                size = getNumber(buffer, v1, v2);
                reset(size, size);
            }
            else if (token == TOKEN_COMMENT)
               tree1[index1].text += getText(buffer, v1, v2);
            else if (token == TOKEN_EVENT)
               BOARD_EVENT = getText(buffer, v1, v2);
            else if (token == TOKEN_DATE)
               BOARD_DATE = getText(buffer, v1, v2);
            else if (token == TOKEN_KOMI)
               BOARD_KOMI = getText(buffer, v1, v2);
            else if (token == TOKEN_RESULT)
               BOARD_RESULT = getText(buffer, v1, v2);
            else if (token == TOKEN_PLAY_BLACK)
               PLAYER_BLACK = getText(buffer, v1, v2);
            else if (token == TOKEN_PLAY_WHITE)
               PLAYER_WHITE = getText(buffer, v1, v2);
            p = v1 = -1;
        }
        else if (c == ' ' || c == '(' || c == ')' || c == ';' || c == '\n' || c == '\r' || c == '\f') { }
        else {
            if (p < 0 && v1 < 0) { p = i; } }
    }
    firstNode();
    return 1;
}

int gogame::firstNode()
{
    if(index1>0){
        while(preNode()){}
        return 1;
    }
    return 0;
}

int gogame::preNode(int k)
{
    if (index1 <= 0) return 0;

       while (index1 && k) {
           int total = tree1[index1].board.size();

           for (int i = 0; i < total; i++) {
               Board board = tree1[index1].board[i];
               if (board.label == TOKEN_PLAY || board.label == TOKEN_ADD)
                   points[board.col][board.row] = 0;
               else if (board.label == TOKEN_TAKE)
                   points[board.col][board.row] = board.value;
           }
           index1--; k--;
           turn = tree1[index1].turn;
           pass = tree1[index1].pass;
           if(index1== index2) {
               tree1 = tree2; // restore from test play
               index2 = -1;
           }
       }
       return 1;
}

int gogame::lastNode()
{
    if (index1 < tree1.size() - 1) {
        while(nextNode()) {}
        return 1;}
    return 0;
}

int gogame::nextNode(int k)
{
    int last = tree1.size() - 1;
    if (index1 >= last) return 0;
    while (index1 < last && k) {
        index1++;
        int total = tree1[index1].board.size();
        turn = tree1[index1].turn;
        pass = tree1[index1].pass;
        for (int i = 0; i < total; i++) {
            Board board = tree1[index1].board[i];
            if (board.label == TOKEN_PLAY || board.label == TOKEN_ADD)
                points[board.col][board.row] = board.value;
            else if (board.label == TOKEN_TAKE)
                points[board.col][board.row] = 0;
        }
        k--;
    }
    return 1;
}

void gogame::reset(int x, int y)
{
    if(x>MAX_DIST) x=MAX_DIST;
    else if(x<MIN_DIST) x=MIN_DIST;
    if(y>MAX_DIST) y=MAX_DIST;
    else if(y<MAX_DIST) y=MIN_DIST;

    size=width=x;
    height=y;

    int a=3;
    int b=size-4;
    int c=(size-1)/2;

    star[0]=star[1]=star[3]=star[4]=star[11]=star[12]=a;
    star[2]=star[5]=star[6]=star[7]=star[14]=star[17]=b;
    star[8]=star[9]=star[10]=star[13]=star[15]=star[16]=c;

    clear();
}

void gogame::clear()
{
    vector<Node>().swap(tree1);
    vector<Node>().swap(tree2);

    Node node;
    node.turn = BLACK;
    node.pass = 0;
    tree1.push_back(node);

    turn = BLACK;
    mode = 3;
    index1 = 0;
    index2 = -1;
    path = 0;
    pass = 0;

    memset(points, 0, sizeof(points));
    memset(marks, 0, sizeof(points));
    memset(areas, 0, sizeof(points));
}

