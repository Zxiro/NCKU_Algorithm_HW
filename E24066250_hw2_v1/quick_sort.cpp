#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <time.h>
using namespace std;

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

void Swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int partition(vector<int> &data, int start, int end) {
	int length = end - start + 1;
	int choosen_index = rand() % length + start;
	int min_ptr = start - 1;
	int choosen_value = data[choosen_index];
	data[choosen_index] = data[end];
	for (int max_ptr = start; max_ptr < end; max_ptr++)
	{
		if (data[max_ptr] < choosen_value) {
			min_ptr++;
			Swap(data[max_ptr], data[min_ptr]);
		}
	}
	choosen_index = min_ptr + 1;
	data[end] = data[choosen_index];
	data[choosen_index] = choosen_value;
	return choosen_index;
}

void PrintSave(vector<int>&array, fstream &file) {
	for (int i = 0; i < array.size(); i++) {
		cout << array[i] << endl;
		file << array[i] << "\n";
	}
}

void QuickSort(vector<int> &data, int start, int end) {
	int length = end - start + 1;
	if (length > 1) {
		int choosen_index = partition(data, start, end);
		QuickSort(data, start, choosen_index - 1);
		QuickSort(data, choosen_index + 1, end);
	}
}

int main() {
	srand(time(NULL));
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
	QuickSort(data, 0, key_amount - 1);
	end = clock();
	file.open("output.txt", ios::out);
	file << key_amount << "\n";
	PrintSave(data, file);
	double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << "CPU run time is " << cpu_time << "sec" << endl;
}