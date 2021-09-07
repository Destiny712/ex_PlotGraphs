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
#include <TFile.h> // ROOT header
#include <TF1.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TTree.h>
#include "solution_PlotGraphs.h" // my header

namespace MySolution
{
class Ex_12 : public MySolution
{
public:
    Ex_12(Int_t ex_num, TFile* inputFile, TString folder);
    ~Ex_12();
    Int_t Solve();
protected:
    TFile* inputFile = nullptr;
    TString folder = "";
};

class Ex_13 : public MySolution
{
public:
    Ex_13(Int_t ex_num, TFile* inputFile, TString folder);
    ~Ex_13();
    Int_t Solve();
protected:
    TFile* inputFile = nullptr;
    TString folder = "";
};
}

#endif /* solution_exercise_h */
