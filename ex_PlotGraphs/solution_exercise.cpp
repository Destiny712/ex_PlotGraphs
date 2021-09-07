//
//  solution_exercise.cpp
//  ex_PlotGraphs
//
//  Created by 符士洪 on 2021/9/3.
//

#include "solution_exercise.h"

MySolution::Ex_12::Ex_12(Int_t ex_num, TFile* inputFile, TString folder)
{
    this->ex_num = ex_num;
    this->inputFile = inputFile;
    this->folder = folder;
    // Constructor
}

MySolution::Ex_12::~Ex_12()
{
    // Destructor
}

Int_t MySolution::Ex_12::Solve()
{
    // From here, it is the real solution to Exercise 12.
    //
    // Plot 1

    //******** Definition section *********
    TDirectory* example1 = nullptr;
    Int_t numberOfHistograms = 0;
    // Create the vectors that will hold the information to be displayed on the plot.
    std::vector<Double_t> xValue;
    std::vector<Double_t> yValue;
    std::vector<Double_t> xError;
    std::vector<Double_t> yError;
    TF1* myFunction = nullptr;
    TString name = "";
    TH1* histogram = nullptr;
    TCanvas* canvas1 = nullptr;
    TGraphErrors* graph1 = nullptr;
    
    //******** Initialization section *********
    // Now let's go to a particular directory.
    example1 = inputFile->GetDirectory(folder);
    if (example1 == nullptr)
    {
        std::cout << "Fatal error: folder " << folder << " does not exist..." << std::endl;
        return -1;
    }
    example1->cd();
    
    // For the first folder example, I know there are exactly six
    // histograms.  I could use the fancier technique that I use in
    // example3; in fact, I'd prefer to do so.  But let's keep it simple
    // for the first example.
    numberOfHistograms = 6;
    
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
    
    canvas1 = new TCanvas("canvas1", "canvas1", 20, 20, 775, 646);
    canvas1->Range(0.01, -3.85618, 4.12408, 10000.0);
    canvas1->SetBorderSize(2);
    canvas1->SetLogx();
    canvas1->SetGridx();
    canvas1->SetGridy();
    canvas1->SetLeftMargin(0.119326);
    
    //******** Loop section *********
    // For each histogram in the folder:
    for (Int_t i = 0; i != numberOfHistograms; i++)
    {
        // We have to derive the name of the histogram as stored in the
        // folder. String manipulation in C++ can be a little tricky.
        // Fortunately, ROOT's TString class is defined in such a way
        // that if you add a number to a string, it appends the text
        // version of that number to the end of the string.
        name = "hist";
        name += i;
        
        // Get an object with this name from the current directory in the file.
        example1->GetObject(name, histogram);
        
        // What if there's some kind of problem; for example, the object
        // with the name "hist456" may not be a histogram after all, or
        // maybe it doesn't exist. In either case, the value of the
        // histogram pointer will be 0.
        if (histogram == nullptr)
        {
            std::cout << "Error: histogram '" << name << "' not found..." << std::endl;
            continue; // go to the next cycle of the loop
        }
        
        // How do we get the value of x given this histogram? In this
        // case, I've given the students no other way other than to
        // display each histogram, look at the description, and derive
        // the following formula.
        xValue.push_back(0.5 * pow(10, i - 1));
        
        // For all the plots, there is no error in x.
        xError.push_back(0);
        
        // The value and error in y comes from the histograms.
        // Actually, I've constructed the histograms so that you can bet
        // these values from the mean and RMS of the histograms. But
        // let's use a gaussian fit. Before fitting, set the initial
        // values of the gaussian function from the histogram statistics.
        myFunction->SetParameters(histogram->GetMaximum(), histogram->GetMean(), histogram->GetRMS());
        // "Q" means quiet; otherwise we get text printed for every fit.
        // "N" means do not plot the function after we're done.
        histogram->Fit("myFunction", "QN");
        
        yValue.push_back(myFunction->GetParameter(1));
        yError.push_back(myFunction->GetParameter(2));
    }
    
    //******** Wrap-up section *********
    canvas1->cd();
    
    // We want to create the graph with error bars. We have a problem;
    // I stored the numbers in the form std::vector<Double_t>, but the
    // ROOT web site says that TGraphErrors needs Double_t*, which is
    // the pointer to the first element of an array.

    // There's a C++ trick that let's us get at the underlying array
    // within a vector: if v is of type std::vector<T>, then v.data() is
    // the same as a pointer to the first element of an array of T.
    graph1 = new TGraphErrors(numberOfHistograms, xValue.data(), yValue.data(), xError.data(), yError.data());
    
    graph1->SetName("PunPlot");
    graph1->SetTitle("Number of charged atoms in 'Nights in the Gardens of Spain'");
    graph1->SetFillColor(1);
    graph1->SetMarkerColor(4);
    graph1->SetMarkerStyle(21);
    graph1->SetMarkerSize(1.3);
    
    // Set the axis labels. Note the use of TLatex on the y-axis title.
    graph1->GetXaxis()->SetTitle("t [secs]");
    graph1->GetXaxis()->CenterTitle(kTRUE);
    graph1->GetXaxis()->SetTitleOffset(1.2);

    graph1->GetYaxis()->SetTitle("#frac{n_{ions}}{d#left(Falla#right)}");
    graph1->GetYaxis()->CenterTitle(kTRUE);
    graph1->GetYaxis()->SetTitleOffset(1.2);

    // Draw the graph on the canvas.
    graph1->Draw("AP");
    canvas1->Update();
    
    std::cout << "Exercise " << ex_num << " has been solved~~~" << std::endl;
    // The above is the solution to Exercise 12.
    
    //******** Release section *********
//    delete graph1;
//    graph1 = nullptr;
//    delete canvas1;
//    canvas1 = nullptr;
    delete histogram;
    histogram = nullptr;
    name = "";
    delete myFunction;
    myFunction = nullptr;
    xValue.clear();
    yValue.clear();
    xError.clear();
    yError.clear();
    numberOfHistograms = 0;
    delete example1;
    example1 = nullptr;
    
    return 0;
}
