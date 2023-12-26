#include "puzzle.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <QDir>
using namespace std;

puzzle::puzzle(QString diff){
    difficulty = diff;
    hint = 0;
    //set vector size
    vector<vector<int>>* tmp = new vector<vector<int>>(9, vector<int>(9,0));
    vtr= *tmp;
    sheet = *tmp;
    sol = *tmp;
    //initialize
    initialize(diff.toStdString());
}
bool puzzle::columnCheck(int col, int num){ //check whether num is present in col or not
   for (int row = 0; row < 9; row++)
      if (sol[row][col] == num)
         return true;
   return false;
}
bool puzzle::rowCheck(int row, int num){ //check whether num is present in row or not
   for (int col = 0; col < 9; col++)
      if (sol[row][col] == num)
         return true;
   return false;
}
bool puzzle::boxCheck(int rStart, int cStart, int num){
//check whether num is present in 3x3 box or not
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (sol[row+rStart][col+cStart] == num)
            return true;
   return false;
}

void puzzle::printvtr(){ //print the sudoku sol after solve
    for (int row = 0; row < 9; row++){
          qDebug()<< vtr[row][0]<<vtr[row][1]<<vtr[row][2]<<vtr[row][3]<<vtr[row][4]<<vtr[row][5]<<vtr[row][6]<<vtr[row][7]<<vtr[row][8];
    }
}

void puzzle::printsol(){ //print the sudoku sol after solve
   for (int row = 0; row < 9; row++){
      qDebug()<< sol[row][0]<<sol[row][1]<<sol[row][2]<<sol[row][3]<<sol[row][4]<<sol[row][5]<<sol[row][6]<<sol[row][7]<<sol[row][8];
   }
   qDebug();
}
bool puzzle::findEmpty(int &row, int &col){ //get empty location and update row and column
   for (row = 0; row < 9; row++)
      for (col = 0; col < 9; col++)
         if (sol[row][col] == 0) //marked with 0 is empty
            return true;
   return false;
}
bool puzzle::check(int row, int col, int num){
   //when item not found in col, row and current 3x3 box
   return !rowCheck(row, num) && !columnCheck(col, num) && !boxCheck(row - row%3 ,col - col%3, num);
}
bool puzzle::generateSol(){
   int row, col;
   if (!findEmpty(row, col))
      return true; //when all places are filled
   for (int num = 1; num <= 9; num++){ //valid numbers are 1 - 9
      if (check(row, col, num)){ //check validation, if yes, put the number in the sol
         sol[row][col] = num;
         if (generateSol()) //recursively go for other rooms in the sol ;
            return true;
         sol[row][col] = 0; //turn to unassigned space when conditions are not satisfied
      }
   }
   return false;
}

void puzzle::initialize(string difficulty){
    srand(time(NULL));
    string filename = "./debug/sudokufile/"+ difficulty + to_string(rand()%100+1) +".txt";
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
    }
    int tmp1=0,tmp2=0,number;
    while (input_file >> number) {
        vtr[tmp1][tmp2]=number;
        if(tmp2==8){
            tmp1++;
            tmp2=0;
        }else{
            tmp2++;
        }
    }
    input_file.close();
    sheet = vtr;
    sol = vtr;
    generateSol();
}
