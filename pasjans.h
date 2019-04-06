#include <chrono>
#include <string>
#include <utility>
#include <vector>

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
