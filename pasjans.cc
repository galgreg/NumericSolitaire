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

// I/O functions
InputData getInputData();

// Debug purpose functions
void print(const InputData &inputData);

// Exact algorithm's functions
ProgramResults playSolitaire(const InputData &inputData);
unsigned calculateResult(const DataRow &dataRow);
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

unsigned calculateResult(const DataRow & /*dataRow*/) {
	return 0;
}

void printResults(const ProgramResults &results) {
	for (auto result : results) {
		std::cout << result << "\n";
	}
}
