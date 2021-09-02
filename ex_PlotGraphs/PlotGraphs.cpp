// Making plots from the histograms in folders.root.
// Doing all three exercises in a single program.
//
//  PlotGraphs.cpp
//  ex_PlotGraphs
//
//  Created by 符士洪 on 2021/9/2.
//

#include <iostream>
#include "TApplication.h"
#include "TFile.h"

int main(int argc, char * argv[])
{
    // insert code here...
    
    //******** Definition section *********
    TApplication* myApp = nullptr;
    TString fileName = "";
    TFile* inputFile = nullptr;
    /*The folders in which we'll navigate. I could do this with an
     array, but I like vectors. I don't even have to use a vector of
     TStrings, but (a) it makes it easier if I ever decide to add more
     folders to the file; (b) it defines the folder names near the top
     of the program, where I can see them if I need to change them.*/
    std::vector<TString> folder;
    TString exampleName = "";
    std::map<Int_t, Bool_t> exSwitch;
    
    //******** Initialization section *********
    // As the beginning, creat my application.
    myApp = new TApplication("myApp", &argc, argv);
    
    // First, open the file.
    fileName = "folders.root";
    inputFile = new TFile(fileName);
    for (Int_t i = 0; i < 3; i++) // push_back(elem) Add element at the end of the vector
    {
        exampleName = "example";
        exampleName += i + 1;
        folder.push_back(exampleName);
    }
    
    // Fiddle with the file and folder names to get the absolute path to
    // each folder within the file.
    for (std::vector<TString>::iterator iter = folder.begin(); iter != folder.end(); iter++)
    {
        *iter = fileName + ":/" + *iter;
//        std::cout << *iter << ", ";
    }
    // Set statuses for different exercises.
    exSwitch.insert(std::map<Int_t, Bool_t>::value_type(12, 1)); // exercise 12
    exSwitch.insert(std::map<Int_t, Bool_t>::value_type(13, 0)); // exercise 13
    exSwitch.insert(std::map<Int_t, Bool_t>::value_type(14, 0)); // exercise 14
    
    //******** Loop section *********
    for (std::map<Int_t, Bool_t>::iterator iter = exSwitch.begin(); iter != exSwitch.end(); iter++)
    {
        if (iter->second)
        {
            std::cout << "The status of exercise " << iter->first << " is: " << iter->second << " ." << std::endl;
        }
    }
    
    //******** Wrap-up section *********
    // Make my application run.
//    myApp->Run();
    std::cout << "Hello, World!\n";
    
    //******** Release section *********
    exSwitch.clear();
    exampleName = "";
    folder.clear();
    inputFile->Close();
    delete inputFile;
    fileName = "";
    delete myApp;
    
    return 0;
}
