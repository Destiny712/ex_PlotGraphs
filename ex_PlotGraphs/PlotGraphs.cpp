// Making plots from the histograms in folders.root.
// Doing all three exercises in a single program.
// All the files from web site: http://www.nevis.columbia.edu/~seligman/root-class/files/
//
// To compile this:
//   g++ PlotGraphs.cpp solution_exercise.cpp solution_PlotGraphs.cpp -o PlotGraphs.exe `root-config --glibs --cflags`
//
//  PlotGraphs.cpp
//  ex_PlotGraphs
//
//  Created by 符士洪 on 2021/9/2.
//

#include <iostream> // C++ header
#include <TApplication.h> // ROOT header
#include <TFile.h>
#include "solution_exercise.h" // my header

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
    exSwitch.insert(std::map<Int_t, Bool_t>::value_type(13, 1)); // exercise 13
    exSwitch.insert(std::map<Int_t, Bool_t>::value_type(14, 1)); // exercise 14
    
    //******** Loop section *********
    for (std::map<Int_t, Bool_t>::const_iterator iter = exSwitch.begin(); iter != exSwitch.end(); iter++)
    {
        if (iter->second)
        {
            switch (iter->first)
            {
                case 12:
                {
                    MySolution::Ex_12* myEx_12 = nullptr;
                    myEx_12 = new MySolution::Ex_12(iter->first, inputFile, folder[0]);
                    myEx_12->Solve();
                    delete myEx_12;
                    myEx_12 = nullptr;
                    break;
                }
                    
                case 13:
                {
                    MySolution::Ex_13* myEx_13 = nullptr;
                    myEx_13 = new MySolution::Ex_13(iter->first, inputFile, folder[1]);
                    myEx_13->Solve();
                    delete myEx_13;
                    myEx_13 = nullptr;
                    break;
                }
                    
                case 14:
                {
                    MySolution::Ex_14* myEx_14 = nullptr;
                    myEx_14 = new MySolution::Ex_14(iter->first, inputFile, folder[2]);
                    myEx_14->Solve();
                    delete myEx_14;
                    myEx_14 = nullptr;
                    break;
                }
                    
                default:
                    std::cout << "The solution program of exercise " << iter->first << " has not been established yet..." << std::endl;
                    break;
            }
//            std::cout << "The status of exercise " << iter->first << " is: " << iter->second << " ." << std::endl;
        }
    }
    
    //******** Wrap-up section *********
//    std::cout << "Hello, World!\n";
    // Make my application run.
    myApp->Run();
    
    //******** Release section *********
    exSwitch.clear();
    exampleName = "";
    folder.clear();
    inputFile->Close();
    delete inputFile;
    inputFile = nullptr;
    fileName = "";
    delete myApp;
    myApp = nullptr;
    
    return 0;
}
