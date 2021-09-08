//
//  solution_PlotGraphs.cpp
//  ex_PlotGraphs
//
//  Created by 符士洪 on 2021/9/3.
//

#include "solution_PlotGraphs.h"

MySolution::MySolution::MySolution()
{
    // Constructor
}

MySolution::MySolution::MySolution(Int_t ex_num, TFile* inputFile, TString folder)
{
    this->ex_num = ex_num;
    this->inputFile = inputFile;
    this->folder = folder;
    // Constructor
}

MySolution::MySolution::~MySolution()
{
    //******** Release section *********
//    delete graph;
//    graph = nullptr;
//    delete canvas;
//    canvas = nullptr;
    delete histogram;
    histogram = nullptr;
    x = 0.0;
    name = "";
    delete myFunction;
    myFunction = nullptr;
    xValue.clear();
    yValue.clear();
    xError.clear();
    yError.clear();
    delete example;
    example = nullptr;
    
    folder = "";
    inputFile = nullptr;
    ex_num = 0;
    error_flag = kFALSE;
    // Destructor
}

Int_t MySolution::MySolution::Solve()
{
    // This is a default output method, only output the number of the exercise.
    std::cout << "The number of the exercise is: " << ex_num << " ." << std::endl;
    std::cout << "If you see this output, it means that the real solution program has not been established yet..." << std::endl;
    
    return 0;
}

Int_t MySolution::MySolution::Initialization()
{
    example = inputFile->GetDirectory(folder);
    if (example == nullptr)
    {
        std::cout << "Fatal error: folder " << folder << " does not exist..." << std::endl;
        return -1;
    }
    example->cd();
    
    // A gaussian function to fit the histograms. One more time: not
    // all of physics is fit with gaussian distributions! I'm using
    // them here because they're a simple example!
    myFunction = new TF1("myFunction", "gaus");
    
    // Create a canvas on which to draw the graph.

    // How did I figure out all the options and values to put on the
    // graph? It was a combination of two things:

    // 1) I looked in $ROOTSYS/tutorials and hunted around for a simple
    // example of TGraphErrors. I found one in
    // $ROOTSYS/tutorials/graphs/gerrors.C.

    // 2) After creating an initial graph, I saved it as a .C file.
    // Then I looked at the commands, copied them, and adjusted the
    // settings.
    
    name = "Canvas for Exercise ";
    name += ex_num;
    canvas = new TCanvas(name, name, (ex_num - 10) * 40, (ex_num - 11) * 40, 775, 646);
    name = "";
    canvas->Range(0.01, -3.85618, 4.12408, 10000.0);
    canvas->SetBorderSize(2);
    canvas->SetGridx();
    canvas->SetGridy();
    canvas->SetLeftMargin(0.119326);
    
    return 0;
}

Int_t MySolution::MySolution::Loop_Kernel()
{
    //******** Loop section *********
    // The value and error in y comes from the histograms.
    // Actually, I've constructed the histograms so that you can bet
    // these values from the mean and RMS of the histograms. But
    // let's use a gaussian fit. Before fitting, set the initial
    // values of the gaussian function from the histogram statistics.
    myFunction->SetParameters(histogram->GetMaximum(), histogram->GetMean(), histogram->GetRMS());
    // "Q" means quiet; otherwise we get text printed for every fit.
    // "N" means do not plot the function after we're done.
    histogram->Fit("myFunction", "QN");
    
    // Add the results to the end of the list of numbers.
    xValue.push_back(x);
    // For all the plots, there is no error in x.
    xError.push_back(0);
    yValue.push_back(myFunction->GetParameter(1));
    yError.push_back(myFunction->GetParameter(2));
    
    return 0;
}

Int_t MySolution::MySolution::Wrap_up()
{
    //******** Wrap-up section *********
    canvas->cd();
    
    // We want to create the graph with error bars. We have a problem;
    // I stored the numbers in the form std::vector<Double_t>, but the
    // ROOT web site says that TGraphErrors needs Double_t*, which is
    // the pointer to the first element of an array.

    // There's a C++ trick that let's us get at the underlying array
    // within a vector: if v is of type std::vector<T>, then v.data() is
    // the same as a pointer to the first element of an array of T.
    graph = new TGraphErrors((Int_t)xValue.size(), xValue.data(), yValue.data(), xError.data(), yError.data());
    
    graph->SetFillColor(1);
    graph->SetMarkerColor(4);
    graph->SetMarkerStyle(21);
    graph->SetMarkerSize(1.3);
    
    graph->GetXaxis()->CenterTitle(kTRUE);
    graph->GetXaxis()->SetTitleOffset(1.2);
    
    graph->GetYaxis()->CenterTitle(kTRUE);
    graph->GetYaxis()->SetTitleOffset(1.2);
    
    return 0;
}
