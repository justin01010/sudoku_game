#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <QApplication>
using namespace std;

class puzzle{
    public:

        vector<vector<int>> vtr;
        vector<vector<int>> sheet;
        vector<vector<int>> sol;
        int hint;
        QString difficulty;
        bool startStatus;

        puzzle(QString difficulty);
        //function for generating sukodu(unused)
        bool columnCheck(int col, int num);
        bool rowCheck(int row, int num);
        bool boxCheck(int rStart,int cStart,int num);

        bool findEmpty(int &row,int &col);
        bool check(int row,int col,int num);
        bool generateSol();

        //initialize three vectors
        void initialize(string difficulty);

        //for testing
        void printsol();
        void printvtr();


};
#endif // PUZZLE_H
