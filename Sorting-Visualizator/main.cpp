#include "Constants.h"
#include <iostream>
#include "GraphicSort.h"
#include "SortAlgoritms.h"

using namespace std;

int main()
{
    std::shared_ptr<GraphicSort> win = make_shared<GraphicSort>();
    win->AddAlgorithm(BubbleSort);
    win->Run();

    return 0;
}