#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

map<string,int> cmap;
int noOfCourses = 20;
int noOfProfs = 20;


class Faculty{

public:
    int id;
    int category;
    vector<string> preference;
    int remainingLoad;

    Faculty(int id,int category,vector<string>preference){
        this->id = id;
        this->category = category;
        this->preference = preference;
    }
};

void readPreferencesFromFile(vector<Faculty>& facultyArray) {
    ifstream inputFile;
    inputFile.open("pp.csv");
    string line = "";

    if (!inputFile.is_open()) {
    cout << "Error opening file!" << endl;
    return ;  // Exit the program with an error code
    }

    while (getline(inputFile, line)) {

        stringstream inputString(line);

       //id,category,pref1,pref,pref3
        int id;
        int category;
        vector<string>pref;
        string pref1;
        string pref2;
        string pref3;
        string pref4;
        string tempString;

        getline(inputString, tempString, ',');
        category = atoi(tempString.c_str());

        getline(inputString, tempString, ',');
        id = atoi(tempString.c_str());

        getline(inputString, pref1, ',');
        pref.push_back(pref1);

        getline(inputString, pref2, ',');
        pref.push_back(pref2);

        getline(inputString, pref3, ',');
        pref.push_back(pref3);

        getline(inputString, pref4, ',');
        pref.push_back(pref4);
        

        Faculty profs(id, category,pref);
        facultyArray.push_back(profs);
        line = "";
    }
}

void getOutputFile(map<int,int> &courseToAllot,vector<Faculty> &facultyArray, vector<vector<int> >&profToCourse){
    ofstream fileOut;
    fileOut.open("output2.txt");

    for(int i = 1; i<noOfCourses+1; i++){
        fileOut<<"Faculty "<< i << " of category x"<<facultyArray[i].category<< " has been alloted the following Courses:";
        for(auto j:profToCourse[i]){
            if(j == 0) continue;
            fileOut<<j<<" ";
        }
        fileOut<<endl;
    }
    fileOut.close();
}

void display(vector<Faculty>& facultyArray){
    cout<<"start"<<endl;
    cout<<facultyArray.size();
    for(int i = 0; i<facultyArray.size();i++){
        cout<<facultyArray[i].id<<" "<<facultyArray[i].category<<endl;
    }
}


void printCourseStatus(map<int,int>&courseToAllot){

    for(int i = 0; i<noOfCourses+1; i++){
        cout<<i<<"->"<<courseToAllot[i]<<endl;
    }
}

void func(vector<vector<int> > &grid,vector<Faculty>& facultyArray,map<string,int>&cmap,vector<vector<int> >& profToCourse, map<int,int> &courseToAllot){

   for(int i = 0; i < noOfProfs+1; ++i){
        courseToAllot[i] = 0;
    }

    for(int i = 1; i<noOfProfs+1; i++){
        Faculty fac = facultyArray[i];
        int count = 1;
        for(auto s:fac.preference){
            grid[i][cmap[s]] = count;
            count++;
        }
    }

    for(int i = 1; i<noOfProfs+1;i++){
        if(facultyArray[i].category == 2){
            
            int mini = 5;
            
            for(int j = 1; j<noOfCourses+1; j++){
                if(mini > grid[i][j] && courseToAllot[j] == 0 && grid[i][j] != 0){
                    courseToAllot[profToCourse[i][0]] = 0;
                    courseToAllot[j] = 1;
                    profToCourse[i][0] = j;
                    facultyArray[i].remainingLoad = 0;
                    mini = min(mini,grid[i][j]);
                }
            }
        }
    }
    
    for(int i = 1; i<noOfProfs+1;i++){
        if(facultyArray[i].category == 3){
            
            int mini = 5;
            int count = 0;
            for(int j = 1; j<noOfCourses+1; j++){
                if(mini > grid[i][j] && courseToAllot[j] == 0 && grid[i][j] != 0){
                    courseToAllot[profToCourse[i][0]] = 0;
                    courseToAllot[j] = 2;
                    profToCourse[i][count] = j;
                    facultyArray[i].remainingLoad = 0;
                    mini = min(mini,grid[i][j]);
                }
            }
        }
    }


    vector<Faculty> x3Category;
    vector<string> pref10;
    Faculty fac(0,0,pref10);
    x3Category.push_back(fac);

    for(int i = 1; i<noOfProfs+1; i++){
        if(facultyArray[i].category == 3){
            x3Category.push_back(facultyArray[i]);
        }
    }

    for(int i = 1; i<noOfProfs+1; i++){
        if(facultyArray[i].category == 1){

            int mini = 5;
            for(int j = 1; j<noOfCourses+1; j++){
            if(grid[i][j] < mini && grid[i][j] != 0 && courseToAllot[j] == 0) 
            {
                courseToAllot[profToCourse[i][0]] = 0;
                courseToAllot[j] = 3;
                profToCourse[i][0] = j;
                mini = min(mini,grid[i][j]);

                profToCourse[x3Category[x3Category.size()-1].id][1] = j;
                x3Category.pop_back();

                }
            }
        }
    }

}

void displayGrid(vector<vector<int> >&grid){

    for(int i = 0; i<noOfProfs+1; i++){
        for(int j = 0; j<noOfCourses+1;j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"--------------------------------------------------"<<endl;
}

void printAllotment(vector<vector<int> >& profToCourse,vector<Faculty> &facultyArray){


    for(int i = 1; i<21; i++){
        cout<<"Faculty"<< i << " of category x"<<facultyArray[i].category<< " has been alloted Courses ";
        for(auto j:profToCourse[i]){
            cout<<j<<" ";
        }
        cout<<endl;
    }


}

void generatecMap(int noOfCourses,map<string,int>&cmap){


    for (int i = 1; i <= noOfCourses; ++i) {
        string courseName = "Course" + to_string(i);
        cmap[courseName] = i;
    }
}

int main(){

    cout << "Program started." << endl;
    
    vector<vector<int> > grid(noOfProfs+1,vector<int>(noOfCourses+1,0));
    vector<Faculty> facultyArray;
    map<int,int> courseToAllot;
    vector<string> pref;
    vector<vector<int> >profToCourse(noOfProfs+1,vector<int>(2,0));

    Faculty f0(0,0,pref);
    facultyArray.push_back(f0);

    readPreferencesFromFile(facultyArray);

    generatecMap(noOfCourses,cmap);

    func(grid,facultyArray,cmap,profToCourse,courseToAllot);
    
    displayGrid(grid); 
    cout<<endl;

    printAllotment(profToCourse,facultyArray);

    printCourseStatus(courseToAllot);

    getOutputFile(courseToAllot,facultyArray,profToCourse);

    cout << "Program completed successfully." << endl;
    return 0;
}
