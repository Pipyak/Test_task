#include <iostream>
#include <ctime>
#define MIL 1000000

//creating template for simple moving average function
//for work with 2 datatypes
template <typename T> 
void SimpleMovingAverage(T *input, T *output, int window) {
	double middle = 0;
	for (int i = 0; i < window; i++) {
		middle += input[i];
	}
	middle /= window;
	output[0] = middle;
	for (int i = 1; i < MIL-window+1; i++) {
		output[i] = output[i - 1] - (input[i - 1] / window) + (input[i-1+window] / window);
	}

	for (int i = 0; i < MIL - window + 1; i++) {
		std::cout << output[i] << std::endl;
	}
	std::cout<<'\n';
 }

int main() {
	int window = 4;
	double input1[MIL], output1[MIL];
	float input2[MIL], output2[MIL];

	//full input massives with random numbera
	srand(time(0));
	for (int i = 0; i < MIL; i++) {
		input1[i] = rand() % 100;
		input2[i] = rand() % 100;

		//creating digits of float and double type
		(double)input1[i] /= rand() % 100;
		(float)input2[i] /= rand() % 100;
	}
	
	//output values in console
	for (int i = window, name=1; i <= 128; i *= 2) {
		std::cout << "Massive " << name++ << ':' << std::endl;
		SimpleMovingAverage(input1, output1, window);
		std::cout << "Massive " << name++ << ':' << std::endl;
		SimpleMovingAverage(input2, output2, window);
	}
	
	return 0;
}