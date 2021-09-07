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

namespace MySolution
{
class MySolution
{
public:
    MySolution();
    ~MySolution();
    virtual Int_t Solve();
protected:
    Int_t ex_num = 0;
};
}

#endif /* solution_PlotGraphs_h */
