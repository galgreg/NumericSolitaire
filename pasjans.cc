#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

unsigned playSolitaire(
		unsigned sizeOfSeries,
		const std::vector<unsigned> &series);	
std::vector<std::vector<unsigned>> createPermutations(
		unsigned sizeOfSeries);
std::vector<unsigned> computeAllResults(
		const std::vector<std::vector<unsigned>> &permutations,
		const std::vector<unsigned> &series);
unsigned computeSingleResult(
		const std::vector<unsigned> &permutation,
		std::vector<unsigned> series);		
unsigned findMaxResult(std::vector<unsigned> results);

int main() {
	auto beginTime = std::chrono::high_resolution_clock::now();
	std::string inputLine;
	while (std::getline(std::cin, inputLine)) {
		unsigned element = 0, sizeOfSeries = 0;
		std::vector<unsigned> series;
		std::istringstream inputStream(inputLine);
		inputStream >> sizeOfSeries;
		
		if (sizeOfSeries < 3) {
			break;
		}
		while(inputStream >> element) {
			series.push_back(element);
		}
		
		unsigned result = playSolitaire(sizeOfSeries, series);
		std::cout << "result: " << result << std::endl;
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> executionTime = endTime - beginTime;
	std::cout << "Execution time: " << executionTime.count()
			<< " seconds." << std::endl;
	return EXIT_SUCCESS;
}

unsigned playSolitaire(
		unsigned sizeOfSeries,
		const std::vector<unsigned> &series) {
	unsigned maxResult = 0;
	unsigned currentResult = 0;

	std::vector<unsigned> currentPermutation;
	unsigned i = 1;
	while (i < sizeOfSeries-1) {
		currentPermutation.push_back(i);
		++i;
	}
	
	do {
		currentResult = computeSingleResult(
				currentPermutation,
				series);
		if (currentResult > maxResult) {
			maxResult = currentResult;
		}
	} while (std::next_permutation(
				currentPermutation.begin(),
				currentPermutation.end())
			);

	return maxResult;
}

unsigned computeSingleResult(
		const std::vector<unsigned> &permutation,
		std::vector<unsigned> series) {
	unsigned result = 0;
	
	for (unsigned index : permutation) {
		result += series.at(index);
		series.at(index) = 0;

		unsigned leftIndex = index - 1;		
		while (series.at(leftIndex) == 0) {
			--leftIndex;
		}
		result += series.at(leftIndex);
		
		unsigned rightIndex = index + 1;
		while (series.at(rightIndex) == 0) {
			++rightIndex;
		}
		result += series.at(rightIndex);
	}
	return result;
}
