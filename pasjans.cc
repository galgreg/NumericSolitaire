#include <vector>
#include <utility>
#include <string>
#include <chrono>
#include <iostream>
#include <sstream>

#define PRINT_DEBUG 0

// Type aliases
using std::vector;
using std::pair;
using DataRow = pair<size_t, vector<unsigned>>;
using InputData = vector<DataRow>;
using Clock = std::chrono::high_resolution_clock;
using TimeMeasure = std::chrono::duration<double>;
using ProgramResults = vector<unsigned>;
using SumMatrix = vector<vector<unsigned>>;
using MatrixRow = vector<unsigned>;

// I/O functions
InputData getInputData();

// Debug purpose functions
void print(const InputData &inputData);

// Exact algorithm's functions
ProgramResults playSolitaire(const InputData &inputData);
unsigned calculateResult(const DataRow &dataRow);
unsigned maxSum(
		const vector<unsigned> &sequence,
		const SumMatrix &maxSums,
		unsigned i,
		unsigned j);
void printResults(const ProgramResults &results);

// main
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
			sequence.at(sequenceIndex++) = sequenceElement;
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
	
	for (size_t i = 0; i != inputSize; ++i) {
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
	maxSums.at(0).resize(--rowSize, 0);
	maxSums.at(1).resize(--rowSize);
	
	for (unsigned i = 0, k = i+1, j = i+2; i < sequenceSize-2; ++i, ++k, ++j) {
		auto &matrixRow = maxSums.at(1);
		matrixRow.at(i) = sequence.at(i) + sequence.at(k) + sequence.at(j);
	}
	
	for (unsigned r = 3; r < sequenceSize; ++r) {
		maxSums.at(r-1).resize(--rowSize);
		
		for (unsigned i = 0; i < sequenceSize - r; ++i) {
			unsigned j = i + r;
			maxSums.at(r-1).at(i) = maxSum(sequence, maxSums, i, j);
		}
	}
	unsigned maxResult = maxSums.at(sequenceSize-2).at(0);
	return maxResult;
}

unsigned maxSum(
		const vector<unsigned> &sequence,
		const SumMatrix &maxSums,
		unsigned i,
		unsigned j) {
	unsigned result = 0;
	
	for (unsigned k = i+1; k < j; ++k) {
		unsigned temp = maxSums.at(k-i-1).at(i) +
				maxSums.at(j-k-1).at(k) +
				sequence.at(i) +
				sequence.at(k) +
				sequence.at(j);
		
		if (temp > result) {
			result = temp;
		}
	}
	return result;
}

void printResults(const ProgramResults &results) {
	for (auto result : results) {
		std::cout << result << "\n";
	}
}
