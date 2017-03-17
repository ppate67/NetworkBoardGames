#ifndef DATABASE_H
#define DATABASE_H
#include "string"
#include "dataline.h"
using namespace  std;

class Database
{
public:
    Database();
    void inputData();
    dataLine fetchData(int key);
    void deleteData(int key);
    string searchQuery();
};

#endif // DATABASE_H
