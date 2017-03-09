/*
BIG - O NOTATION CASE STUDY
Coded by : Ayushya Amitabh
Dated : 2 / 22 /2017

MAIN.CPP
*/

#include <iostream>
#include <fstream>	//ofstream
#include <random>	// mt19937, random_device, seed_seq, uniform_int_distribution
#include <climits>	// MAX_INT
#include <stdlib.h>
#include <algorithm> // pow (10, n), log10(n)
#include <string> // to_string (int n)

using namespace std;	
ofstream outputFile; // OUTPUT FILE TO RECORD STEPS TAKEN AND MATCHES FOUND

// STRAIGHT SEQUENCE : 
// INPUT: int *_array, int _arraySize, int *_keys
// _array -> Array to search through | _arraySize -> Size of array to search through | _keys -> Keys to search for
void straightSequence(int *_array, int _arraySize, int *_keys) {
	outputFile <<  "Running Straight Sequential Search..." << "\t";;
	int _stepCount = 0, _matchCount = 0;
	for (int i = 0; i < pow(10,3); i++, _stepCount++) {
		for (int j = 0; j < _arraySize; j++, _stepCount++) {
			if (_keys[i] == _array[j]) {
				_stepCount++;
				_matchCount++;
				break;
			}
		}
	}
	outputFile << _matchCount << endl;
}

// QUICK SORT : 
// INPUT: int arr[], int left, int right
// arr[] -> Array to search through | left -> Low bound / Left bound | right -> Right bound / High Bound
void quickSort(int arr[], int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

// ORDERED SEQUENCE : 
// INPUT: int *_array, int _arraySize, int *_keys
// _array -> Array to search through | _arraySize -> Size of array to search through | _keys -> Keys to search for
void orderedSequence(int *_array, int _arraySize, int *_keys) {
	outputFile << "Running Ordered Sequential Search..." << "\t";;
	int _stepCount = 0, _matchCount = 0;
	quickSort(_array, 0, _arraySize-1);	//SORTING THE ARRAY BEFORE STARTING SEARCH
	for (int i = 0; i < pow(10, 3); i++, _stepCount++) {
		for (int j = 0; j < _arraySize; j++, _stepCount++) {
			if (_keys[i] == _array[j]) {
				_matchCount++;
				break;
			}
		}
	}
	outputFile << _matchCount << endl;
}

// INDEXED SEQUENCE : 
// INPUT: int *_array, int _arraySize, int *_keys
// _array -> Array to search through | _arraySize -> Size of array to search through | _keys -> Keys to search for
void indexedSequence(int *_array, int _arraySize, int _exp, int *_keys) {
	outputFile << "Running Indexed Sequential Search..." << "\t";;
	int _stepCount = 0, _matchCount = 0;
	quickSort(_array, 0, _arraySize - 1);
	for (int i = 0; i < pow(10, 3); i++, _stepCount++) {
		for (int j = 0; j < _arraySize; j+=log10(_arraySize), _stepCount++) {
			if (_array[j] > _keys[i]){
				for (int k = j-1; k > j - log10(_arraySize); k--) {
					if (_array[k] == _keys[i]) {
						_matchCount++;
						break;
					}
					else
					{
						break;
					}
				}
			}
			else if (_array[j] == _keys[i]) {
				_matchCount++;
				break;
			}
		}
	}
	outputFile << _matchCount << endl;
}

// FIRST SWAP SEQUENCE : 
// INPUT: int *_array, int _arraySize, int *_keys
// _array -> Array to search through | _arraySize -> Size of array to search through | _keys -> Keys to search for
void firstSequence(int *_array, int _arraySize, int *_keys) {
	outputFile <<"Running Straight Sequential Search with First Element Swap..." << "\t"; ;
	int _stepCount = 0, _matchCount = 0;
	for (int i = 0; i < pow(10, 3); i++, _stepCount++) {
		for (int j = 0; j < _arraySize; j++, _stepCount++) {
			if (_keys[i] == _array[j]) {
				_matchCount++;
				_stepCount++;
				if (j != 0) {
					int temp = _array[0];
					_array[0] = _array[j];
					_array[j] = temp;
					_stepCount++;
				}
				break; //this
			}
		}
	}
	outputFile << _matchCount << endl;
}

// PREVIOUS SWAP SEQUENCE : 
// INPUT: int *_array, int _arraySize, int *_keys
// _array -> Array to search through | _arraySize -> Size of array to search through | _keys -> Keys to search for
void swapSequence(int *_array, int _arraySize, int *_keys) {
	outputFile << "Running Straight Sequential Search with Previous Element Swap..." << "\t";
	int _stepCount = 0, _matchCount = 0;
	for (int i = 0; i < pow(10, 3); i++, _stepCount++) {
		for (int j = 0; j < _arraySize; j++, _stepCount++) {
			if (_keys[i] == _array[j]) {
				_matchCount++;
				_stepCount++;
				if (j != 0) {
					int temp = _array[j-1];
					_array[j-1] = _array[j];
					_array[j] = temp;
					_stepCount++;
				}
				break; //this
			}
		}
	}
	outputFile << _matchCount << endl;
}

int _binaryStepCount = 0;
// BINARY SEARCH : 
// INPUT: int *arr[], int value, int left, int right
// arr[] -> Array to search through | value -> Value to search for
// left -> Left most value of array | right -> Right most value of array
int binarySearch(int arr[], int value, int left, int right) {
	while (left <= right) {
		int middle = (left + right) / 2;
		if (arr[middle] == value) {
			_binaryStepCount++;
			return middle;
		}
		else if (arr[middle] > value) {
			_binaryStepCount++;
			right = middle - 1;
		}
		else {
			left = middle + 1;
			_binaryStepCount++;
		}
	}
	return -1;
}

// BINARY HANDLER: 
// INPUT: int *_array, int _arraySize, int *_keys
// _array -> Array to search through | _arraySize -> Size of array to search through | _keys -> Keys to search for
// HANDLES / HANDS OFF SEARCH TO "-----void binarySearch(int[], int, int, int)--------"
void binary(int *_array, int _arraySize, int *_keys) {
	outputFile << "Running Binary Search..." << "\t";
	int _matchCount = 0;
	quickSort(_array, 0, _arraySize - 1);
	for (int i = 0; i < pow(10, 3); i++, _binaryStepCount++) {
		if (-1 != binarySearch(_array, _keys[i], 0, _arraySize)) {
			_matchCount++;
		}
	}
	outputFile <<_matchCount << endl;
}

// ONE SET OF ARRAY AND SEARCH KEYS BEING PUT THROUGH ALL ALGORITHMS
// CYCLE:
// INPUT: int _userSize, int run
// _userSize -> Value of n, the exponent to 10 | run -> Number of times to run the algorithms
void cycle(int _userSize, int _run) {
	//Random Number Generator Engine for the Search Array
	random_device r;
	seed_seq seed{ r() };
	mt19937 eng(seed);

	//Random Number Generator Engine for the Search Array
	random_device r2;
	seed_seq seed2{ r2() };
	mt19937 eng2(seed2);
	int *_toSearchArray, _pow10size, *_searchKeys;

	outputFile << "\nRun " << _run << "\n";

	if (_userSize >= 6) {
		_pow10size = INT_MAX / 2;
	}
	else
	{
		_pow10size = pow(10, _userSize * 2);
	}
	_userSize = pow(10, _userSize);
	_toSearchArray = new (nothrow) int[_userSize];

	//Makes sure there was no problem in allocating the memory for the array
	if (_toSearchArray == nullptr) {
		cout << "Failed to allocate memory." << endl;
	}

	//Random integers are inserted into the _toSearchArray 
	uniform_int_distribution<> dist{ 0, _pow10size };
	for (int i = 0; i < _userSize; i++) {
		_toSearchArray[i] = dist(eng);
	}

	outputFile << "Array of size : " << _userSize << "\n";

	int searchSize = pow(10, 3);

	//Generating integers to search for
	std::uniform_int_distribution<> searchDist{ 0 , searchSize };
	_searchKeys = new int[searchSize];
	for (int i = 0; i < 1000; i++) {
		_searchKeys[i] = searchDist(eng2);
	}

	straightSequence(_toSearchArray, _userSize, _searchKeys);
	orderedSequence(_toSearchArray, _userSize, _searchKeys);
	indexedSequence(_toSearchArray, _userSize, log10(_userSize), _searchKeys);
	firstSequence(_toSearchArray, _userSize, _searchKeys);
	swapSequence(_toSearchArray, _userSize, _searchKeys);
	binary(_toSearchArray, _userSize, _searchKeys);
}

int main() {

	int values[] = {2, 4, 6, 8}; //POWERS OF 10 - USED TO PASS TO "----------void cycle(int, int)-----------"

	for (int i = 0; i < 4; i++) { // GOES THROUGH 100 ITERATIONS FOR EACH ARRAY
		string fileName = to_string(values[i]) + ".txt"; // CREATING THE FILE NAME TO BE USED
		outputFile.open(fileName); // OPENS THE FILE FOR EDITING
		for (int j = 0; j < 100; j++) {
			cycle(values[i], j);
		}
		outputFile.close(); // CLOSES THE FILE FOR THE POWER OR 10, I.E. values[i], i being any of the elements in the array
	}
	return 0;
}