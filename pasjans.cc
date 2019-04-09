#include "pasjans.h"
#include <iostream>
#include <sstream>
#include <omp.h>

#define PRINT_DEBUG 0

int main() {
	auto inputData = getInputData();
	
	#if PRINT_DEBUG == 1
	print(inputData);
	#endif
	
	auto beginTime = Clock::now();
	auto results = playSolitaire(inputData);
	auto endTime = Clock::now();
	printResults(results);
	
	TimeMeasure executionTime = endTime - beginTime;	
	std::cout << "Execution time: " << executionTime.count()
			<< " seconds." << std::endl;
	return EXIT_SUCCESS;
}

InputData getInputData() {
	std::string inputLine;
	InputData inputData;
	while (std::getline(std::cin, inputLine) && !inputLine.empty()) {
		std::istringstream inputStream(inputLine);
		size_t sequenceSize;
		inputStream >> sequenceSize;
		
		if (sequenceSize == 0) {
			break;
		}
		
		auto sequence = vector<unsigned>(sequenceSize);
		unsigned sequenceElement = 0;
		size_t sequenceIndex = 0;
		
		while (inputStream >> sequenceElement) {
			sequence[sequenceIndex++] = sequenceElement;
		}		
		inputData.push_back(std::move(DataRow(sequenceSize, sequence)));
	}
	return std::move(inputData);
}

void print(const InputData &inputData) {
	for (const auto &row: inputData) {
		std::cout << row.first << " ";
		for (const auto element : row.second) {
			std::cout << element << " ";
		}
		std::cout << "\n";
	}
}

ProgramResults playSolitaire(const InputData &inputData) {
	const size_t inputSize = inputData.size();
	ProgramResults results(inputSize);
	
	for (size_t i = 0; i < inputSize; ++i) {
		unsigned result = calculateResult(inputData[i]);
		results[i] = result;
	}
	return std::move(results);
}

unsigned calculateResult(const DataRow &dataRow) {
	size_t sequenceSize = dataRow.first;
	const auto &sequence = dataRow.second;
	
	SumMatrix maxSums(sequenceSize-1, MatrixRow());
	
	unsigned rowSize = sequenceSize;
	maxSums[0].resize(--rowSize, 0);
	maxSums[1].resize(--rowSize);
	
	#pragma omp parallel if(sequenceSize > 100)
	{
		#pragma omp for nowait
		for (unsigned i = 0; i < sequenceSize-2; ++i) {
			unsigned k = i+1, j = i+2;
			auto &matrixRow = maxSums[1];
			matrixRow[i] = sequence[i] + sequence[k] + sequence[j];
		}
	}
	
	for (unsigned r = 3; r < sequenceSize; ++r) {
		maxSums[r-1].resize(--rowSize);
		
		#pragma omp parallel if(sequenceSize > 100)
		{
			#pragma omp for nowait
			for (unsigned i = 0; i < sequenceSize - r; ++i) {
				unsigned j = i + r;
				maxSums[r-1][i] = maxSum(sequence, maxSums, i, j);
			}
		}
	}
	
	unsigned maxResult = maxSums[sequenceSize-2][0];
	return maxResult;
}

unsigned maxSum(
		const vector<unsigned> &sequence,
		const SumMatrix &maxSums,
		unsigned i,
		unsigned j) {
	unsigned result = 0;
	
	for (unsigned k = i+1; k < j; ++k) {
		unsigned temp = maxSums[k-i-1][i] +
				maxSums[j-k-1][k] +
				sequence[i] +
				sequence[k] +
				sequence[j];
		
		temp > result ? result = temp : 0;
	}
	return result;
}

void printResults(const ProgramResults &results) {
	for (auto result : results) {
		std::cout << result << "\n";
	}
}
