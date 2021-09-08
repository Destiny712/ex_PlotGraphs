//
//  solution_exercise.cpp
//  ex_PlotGraphs
//
//  Created by 符士洪 on 2021/9/3.
//

#include "solution_exercise.h"

MySolution::Ex_12::Ex_12()
{
    // Constructor
}

MySolution::Ex_12::~Ex_12()
{
    //******** Release section *********
    numberOfHistograms = 0;
    // Destructor
}

Int_t MySolution::Ex_12::Solve()
{
    // From here, it is the real solution to Exercise 12.
    //
    // Plot 1
    
    //******** Initialization section *********
    // Now let's go to a particular directory.
    error_flag = Initialization();
    if (error_flag)
    {
        return -1;
    }
    
    // For the first folder example, I know there are exactly six
    // histograms.  I could use the fancier technique that I use in
    // example3; in fact, I'd prefer to do so.  But let's keep it simple
    // for the first example.
    numberOfHistograms = 6;

    canvas->SetLogx();
    
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
        example->GetObject(name, histogram);
        
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
        x = 0.5 * pow(10, i - 1);
        
        error_flag = Loop_Kernel();
        if (error_flag)
        {
            return -1;
        }
    }
    
    //******** Wrap-up section *********
    error_flag = Wrap_up();
    if (error_flag)
    {
        return -1;
    }
    graph->SetName("PunPlot");
    graph->SetTitle("Number of charged atoms in 'Nights in the Gardens of Spain'");
    // Set the axis labels. Note the use of TLatex on the y-axis title.
    graph->GetXaxis()->SetTitle("t [secs]");
    graph->GetYaxis()->SetTitle("#frac{n_{ions}}{d#left(Falla#right)}");

    // Draw the graph on the canvas.
    graph->Draw("AP");
    canvas->Update();
    
    std::cout << "Exercise " << ex_num << " has been solved~~~" << std::endl;
    // The above is the solution to Exercise 12.
    
    return 0;
}

MySolution::Ex_13::Ex_13()
{
    // Constructor
}

MySolution::Ex_13::~Ex_13()
{
    //******** Release section *********
    histogramNumber = 0;
    delete xBranch;
    xBranch = nullptr;
    delete histogramNumberBranch;
    histogramNumberBranch = nullptr;
    numberOfEntries = 0;
    delete histogramList;
    histogramList = nullptr;
    // Destructor
}

Int_t MySolution::Ex_13::Solve()
{
    // From here, it is the real solution to Exercise 13.
    //
    // Plot 2
    
    //******** Initialization section *********
    // On to the next folder.
    error_flag = Initialization();
    if (error_flag)
    {
        return -1;
    }
    example->GetObject("histogramList", histogramList);
    if (histogramList == nullptr)
    {
        std::cout << "Error: TTree histogramList not found..." << std::endl;
        return -2;
    }
    numberOfEntries = (Int_t)histogramList->GetEntriesFast();
    
    // Connect the variables with the branches.
    histogramList->SetBranchAddress("histNumber", &histogramNumber, &histogramNumberBranch);
    histogramList->SetBranchAddress("x", &x, &xBranch);
    
    //******** Loop section *********
    // For each entry in the tree...
    for (Int_t i = 0; i != numberOfEntries; i++)
    {
        // Get the i-th entry in the tree. Because of the
        // "SetBranchAddress" calls above, this will automatically
        // set the values of histogramNumber and x.
        histogramList->GetEntry(i);
        
        // Derive the histogram name.
        name = "hist";
        name += histogramNumber;
        
        // Fetch the histogram.
        example->GetObject(name, histogram);
        if (histogram == nullptr)
        {
            std::cout << "Error: histogram '" << name << "' not found" << std::endl;
            continue; // go to the next cycle of the loop
        }
        
        error_flag = Loop_Kernel();
        if (error_flag)
        {
            return -1;
        }
    }
    
    //******** Wrap-up section *********
    error_flag = Wrap_up();
    if (error_flag)
    {
        return -1;
    }
    graph->SetName("Example2Plot");
    graph->SetTitle("Results of fits to example2 histograms");
    // Set the axis labels.
    graph->GetXaxis()->SetTitle("x; units unknown");
    graph->GetYaxis()->SetTitle("value from fit");

    // Draw the graph on the canvas.
    graph->Draw("AP");
    canvas->Update();
    
    std::cout << "Exercise " << ex_num << " has been solved~~~" << std::endl;
    // The above is the solution to Exercise 13.
    
    return 0;
}

MySolution::Ex_14::Ex_14()
{
    // Constructor
}

MySolution::Ex_14::~Ex_14()
{
    //******** Release section *********
    title = "";
    delete key;
    key = nullptr;
    // Destructor
}

Int_t MySolution::Ex_14::Solve()
{
    // From here, it is the real solution to Exercise 14.
    //
    // Plot 3
    
    //******** Initialization section *********
    // The final folder.
    error_flag = Initialization();
    if (error_flag)
    {
        return -1;
    }
    
    // For the third example, there's no particular guide to the
    // histogram names. Let's start by getting a list of everything in
    // the folder. I had to hunt a bit through the web pages and the
    // tutorials, but this seems to be the way to go through all the
    // objects in the folder:
    TIter next(example->GetListOfKeys());
    
    //******** Loop section *********
    while ((key = (TKey*)next())) // for each object in the folder
    {
        histogram = (TH1*)key->ReadObj();
        // Is this object a histogram?
        if (histogram != nullptr) // if the object is a histogram
        {
            // It's a histogram.  We only want to look at those
            // histogram whose names begin with the text
            // "plotAfterCuts".
            name = histogram->GetName();
            if (name.BeginsWith("plotAfterCuts"))
            {
                // We're going to work with this histogram.  The value
                // of x is contained in the histogram title.
                title = histogram->GetTitle();
                
                // How do we convert the text into a number?
                // Fortunately, there's already a TString method that
                // does just that.
                x = title.Atof();
                
                error_flag = Loop_Kernel();
                if (error_flag)
                {
                    return -1;
                }
            }
        }
    }
    
    //******** Wrap-up section *********
    error_flag = Wrap_up();
    if (error_flag)
    {
        return -1;
    }
    graph->SetName("Example3Plot");
    graph->SetTitle("Results of fits to example3 after-cut histograms");
    // Set the axis labels.
    graph->GetXaxis()->SetTitle("x; units unknown");
    graph->GetYaxis()->SetTitle("value from fit");

    // Draw the graph on the canvas.
    graph->Draw("AP");
    canvas->Update();
    
    std::cout << "Exercise " << ex_num << " has been solved~~~" << std::endl;
    // The above is the solution to Exercise 14.
    
    return 0;
}
