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

void InsertionSort(std::shared_ptr<AlgorithmObs> obs, std::vector<int>& values) {
    for (size_t i = 1; i < values.size(); ++i) {
        int x = values[i];
        size_t j = i;
        while (j > 0 && values[j - 1] > x) {
            values[j] = values[j - 1];
            obs->StepDone(j, j - 1);
            --j;
        }
        values[j] = x;
        obs->StepDone(i, j);
    }
}


// Quick Sort start
int Partition(std::vector<int>& values, int l, int r, std::shared_ptr<AlgorithmObs> obs) {
    int x = values[r];
    int less = l;

    for (int i = l; i < r; ++i) {
        if (values[i] <= x) {
            std::swap(values[i], values[less]);
            obs->StepDone(i, less);
            ++less;
        }
    }
    std::swap(values[less], values[r]);
    obs->StepDone(less, r);
    return less;
}

void QuickSortImpl(std::vector<int>& values, int l, int r, std::shared_ptr<AlgorithmObs> obs) {
    if (l < r) {
        int q = Partition(values, l, r, obs);
        QuickSortImpl(values, l, q - 1, obs);
        QuickSortImpl(values, q + 1, r, obs);
    }
}

void QuickSort(std::shared_ptr<AlgorithmObs> obs, std::vector<int>& values) {
    if (!values.empty()) {
        QuickSortImpl(values, 0, values.size() - 1, obs);
    }
}
// quick sort end