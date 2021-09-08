// Declared specific solutions derived class from different exercises
//
//  solution_exercise.h
//  ex_PlotGraphs
//
//  Created by 符士洪 on 2021/9/3.
//

#ifndef solution_exercise_h
#define solution_exercise_h

//#include <stdio.h> // C++ header
#include <TTree.h> // ROOT header
#include <TKey.h>
#include "solution_PlotGraphs.h" // my header

namespace MySolution
{
class Ex_12 : public MySolution
{
public:
    Ex_12();
    using MySolution::MySolution;
    ~Ex_12();
    Int_t Solve();
private:
    //******** Definition section *********
    Int_t numberOfHistograms = 0;
};

class Ex_13 : public MySolution
{
public:
    Ex_13();
    using MySolution::MySolution;
    ~Ex_13();
    Int_t Solve();
private:
    //******** Definition section *********
    // For the second example, the correspondence between the histograms
    // and the x-values is in a TTree. I told the students to use
    // histogramList->MakeSelector() to create the code to read the tree.
    // But since I know what I'm doing (OK, you can stop laughing now)
    // I'll just read the tree directly.
    TTree* histogramList = nullptr;
    Int_t numberOfEntries = 0;
    
    // Define the branches of the tree.
    TBranch* histogramNumberBranch = nullptr;
    TBranch* xBranch = nullptr;

    // The variables we'll read from those branches.
    Int_t histogramNumber = 0;
};

class Ex_14 : public MySolution
{
public:
    Ex_14();
    using MySolution::MySolution;
    ~Ex_14();
    Int_t Solve();
private:
    //******** Definition section *********
    TKey* key = nullptr;
    TString title = "";
};
}

#endif /* solution_exercise_h */
