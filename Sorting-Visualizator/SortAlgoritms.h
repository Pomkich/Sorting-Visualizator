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

void ShakerSort(std::shared_ptr<AlgorithmObs> obs, std::vector<int>& values) {
    if (values.empty()) {
        return;
    }
    int left = 0;
    int right = values.size() - 1;
    while (left <= right) {
        for (int i = right; i > left; --i) {
            if (values[i - 1] > values[i]) {
                std::swap(values[i - 1], values[i]);
                obs->StepDone(i - 1, i);
            }
        }
        ++left;
        for (int i = left; i < right; ++i) {
            if (values[i] > values[i + 1]) {
                std::swap(values[i], values[i + 1]);
                obs->StepDone(i, i + 1);
            }
        }
        --right;
    }
}

void CombSort(std::shared_ptr<AlgorithmObs> obs, std::vector<int>& values) {
    const double factor = 1.247; // Фактор уменьшения
    double step = values.size() - 1;

    while (step >= 1) {
        for (int i = 0; i + step < values.size(); ++i) {
            if (values[i] > values[i + step]) {
                std::swap(values[i], values[i + step]);
                obs->StepDone(i, i + step);
            }
        }
        step /= factor;
    }
    // сортировка пузырьком
    for (size_t idx_i = 0; idx_i + 1 < values.size(); ++idx_i) {
        for (size_t idx_j = 0; idx_j + 1 < values.size() - idx_i; ++idx_j) {
            if (values[idx_j + 1] < values[idx_j]) {
                std::swap(values[idx_j], values[idx_j + 1]);
                obs->StepDone(idx_j, idx_j + 1);
            }
        }
    }
}