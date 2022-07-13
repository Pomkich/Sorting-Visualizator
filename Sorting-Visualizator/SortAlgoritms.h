#pragma once
#include <memory>
#include <vector>
#include "AlgorithmObs.h"

void BubbleSort(std::shared_ptr<AlgorithmObs> obs, std::vector<int>& elements) {
    for (int idx_i = 0; idx_i + 1 < elements.size(); ++idx_i) {
        for (int idx_j = 0; idx_j + 1 < elements.size() - idx_i; ++idx_j) {
            if (elements[idx_j + 1] < elements[idx_j]) {
                std::swap(elements[idx_j], elements[idx_j + 1]);
                obs->StepDone(idx_j, idx_j + 1);
            }
        }
    }
}