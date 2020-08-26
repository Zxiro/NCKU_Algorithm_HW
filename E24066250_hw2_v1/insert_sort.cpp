#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <time.h>
using namespace std;

void PrintSave(vector<int>&array, fstream &file) {
	for (int i = 0; i < array.size(); i++) {
		cout << array[i] << endl;
		file << array[i] << "\n";
	}
}
void InsertionSort(vector<int>&array) {
	for (int i = 1; i < array.size(); i++) {
		int key = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
	}
}
void MakeFile() {
	ofstream file("input.txt");
	srand(time(NULL));
	vector<int> random_data;
	int tmp;
	for (int i = 1; i <= 10000; i++) {
		random_data.push_back(i);
	}
	for (int i = 1; i <= 50; i++) {
		int x = rand() % 9999;
		int y = rand() % 9999;
		tmp = random_data[x];
		random_data[x] = random_data[y];
		random_data[y] = tmp;
	}
	file << 10000 << " ";
	for (int i = 0; i < 10000; i++) {
		file << random_data[i] << " ";
	}
	file.close();

}
int main() {
	fstream file;
	vector<int> data;
	int vec_data;
	int key_amount;
	clock_t start, end;
	MakeFile();
	file.open("input.txt", ios::in);
	file >> key_amount;
	for (int i = 0; i < key_amount; i++) {
		file >> vec_data;
		data.push_back(vec_data);
	}
	file.close();
	start = clock();
	InsertionSort(data);
	end = clock();
	file.open("output.txt", ios::out);
	file << key_amount << "\n";
	PrintSave(data, file);
	double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << "CPU run time is " << cpu_time << "sec" << endl;
}

