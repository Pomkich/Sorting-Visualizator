#include "Constants.h"
#include <iostream>
#include "GraphicSort.h"
#include "SortAlgoritms.h"

using namespace std;

int main()
{
    std::shared_ptr<GraphicSort> win = make_shared<GraphicSort>();
    win->AddAlgorithm(BubbleSort, "bubble sort", true);
    win->AddAlgorithm(ShakerSort, "shaker sort", true);
    win->AddAlgorithm(CombSort, "comb sort", false);
    win->AddAlgorithm(InsertionSort, "insertion sort", true);
    win->AddAlgorithm(QuickSort, "quick sort", false);
    win->AddAlgorithm(MergeSort, "merge sort", false);
    win->Run();


    return 0;
}