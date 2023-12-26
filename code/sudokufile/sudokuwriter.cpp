#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main() {
    // Settings
    string line;
    string diff[]={"easy","intermediate","hard","expert"};

    for(int i=0;i<=3;i++){

        // Open file
        ifstream myFile;
        myFile.open("./diff/"+diff[i]+"sudoku.txt");
        ofstream newFile;
        int tmp=1;
        string line;
        while (getline(myFile, line)) {
            // Create a new file
            newFile.open(diff[i]+to_string(tmp)+".txt");

            // Write to the file
            for(int j=0;j<=80;j++){
                if(line[j] == '.'){
                    line[j]='0';
                }
                newFile << line[j] <<" ";
                if(j%9==8){
                    newFile << "\n";
                }
            }
            newFile.close();
            tmp++;
        }   

        // Close file
        myFile.close();
    
    }
}
