// Declared the general frame of the solution class
//
//  solution_PlotGraphs.h
//  ex_PlotGraphs
//
//  Created by 符士洪 on 2021/9/3.
//

#ifndef solution_PlotGraphs_h
#define solution_PlotGraphs_h

#include <iostream> // C++ header
#include <TApplication.h> // ROOT header
#include <TFile.h>
#include <TF1.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TGraphErrors.h>

namespace MySolution
{
class MySolution
{
public:
    MySolution();
    MySolution(Int_t ex_num, TFile* inputFile, TString folder);
    ~MySolution();
    virtual Int_t Solve();
protected:
    Int_t Initialization();
    Int_t Loop_Kernel();
    Int_t Wrap_up();
    Bool_t error_flag = kFALSE;
    Int_t ex_num = 0;
    TFile* inputFile = nullptr;
    TString folder = "";
    
    //******** Definition section *********
    TDirectory* example = nullptr;
    // Create the vectors that will hold the information to be displayed on the plot.
    std::vector<Double_t> xValue;
    std::vector<Double_t> yValue;
    std::vector<Double_t> xError;
    std::vector<Double_t> yError;
    TF1* myFunction = nullptr;
    TString name = "";
    Double_t x = 0.0;
    TH1* histogram = nullptr;
    TCanvas* canvas = nullptr;
    TGraphErrors* graph = nullptr;
};
}

#endif /* solution_PlotGraphs_h */
