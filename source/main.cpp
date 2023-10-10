#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>

const int MIL = 1000000;

//using vector for not have stack overflow
std::vector<double>input1;
std::vector<double>output1;
std::vector<float>input2;
std::vector<float>output2;

//creating template for simple moving average function
//for work with 2 datatypes

template <typename T> 
void SimpleMovingAverage(T input, T output, int window) {
	double middle = 0;

	for (int i = 0; i < window; i++) {
		middle += input[i];
	}
	middle /= window;
	output[0] = middle;

	//calculating time
	auto start = std::chrono::steady_clock::now();
	for (int i = 1; i < MIL-window+1; i++) {
		output[i] = output[i - 1] - (input[i - 1] / window) + (input[i-1+window] / window);
	}
	auto end = std::chrono::steady_clock::now();
	auto result = end - start;

	/*for (int i = 0; i < MIL - window + 1; i++) {
		std::cout << output[i] << std::endl;
	}*/

	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microsec";
	std::cout<<'\n';
 }

int main() {
	int window = 4;

	input1.reserve(MIL);
	input2.reserve(MIL);
	output1.reserve(MIL);
	output2.reserve(MIL);
	
	//full input massives with random numbera
	srand(time(0));
	for (int i = 0; i < MIL; i++) {
		input1.push_back(rand() % 100);
		input2.push_back(rand() % 100);

		//creating digits of float and double type
		(double)input1[i] /= (rand() % 100)+1;//+1 is for not divide to 0
		(float)input2[i] /= (rand() % 100)+1;
		
		//initialization output massives for correct work
		output1.push_back(0);
		output2.push_back(0);
	}
	
	//output values in console
	for (int i = window, name=1; i <= 128; i *= 2) {
		std::cout << "Window is " << i << " and type is double:";
		SimpleMovingAverage(input1, output1, i);
		std::cout<<std::endl;
		std::cout << "Window is " << i << " and type is float:";
		SimpleMovingAverage(input2, output2, i);
		std::cout << std::endl;
	}
	
	return 0;
}
