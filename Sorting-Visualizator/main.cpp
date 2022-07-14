#include "Constants.h"
#include <iostream>
#include "GraphicSort.h"
#include "SortAlgoritms.h"

using namespace std;

int main()
{
    std::shared_ptr<GraphicSort> win = make_shared<GraphicSort>();
    win->AddAlgorithm(BubbleSort, "bubble sort");
    win->AddAlgorithm(ShakerSort, "shaker sort");
    win->AddAlgorithm(CombSort, "comb sort");
    win->AddAlgorithm(InsertionSort, "insertion sort");
    win->AddAlgorithm(QuickSort, "quick sort");
    win->Run();


    return 0;
}