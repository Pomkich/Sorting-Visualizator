#pragma once

// observer for notifying about algoritm step
class AlgorithmObs {
public:
	// function gets positions of swaped elements
	virtual void StepDone(int first, int second) = 0;
};