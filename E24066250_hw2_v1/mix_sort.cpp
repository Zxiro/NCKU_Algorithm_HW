#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <time.h>
using namespace std;

void makefile() {
	ofstream file("input.txt");
	srand(time(NULL));
	vector<int> list;
	if (!file) {
		cout << "error";
		return;
	}
	for (int i = 1; i <= 10000; i++) {
		list.push_back(i);
	}
	for (int i = 1; i <= 50; i++) {
		int x = rand() % 9999;
		int y = rand() % 9999;
		int tmp = list[x];
		list[x] = list[y];
		list[y] = tmp;
	}
	file << 10000 << " ";
	int count = 0;
	for (int i = 0; i < 10000; i++) {
		file << list[i] << " ";
	}
	file.close();

}

void swap(int& data, int& b) {
	int tmp = data;
	data = b;
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
			swap(data[max_ptr], data[min_ptr]);
		}
	}
	choosen_index = min_ptr + 1;
	data[end] = data[choosen_index];
	data[choosen_index] = choosen_value;
	return choosen_index;
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
void QuickSort(vector<int> &data, int start, int end,int k) {
	int length = end - start + 1;
	if (length > 1 && length <= k) InsertionSort(data);
	if (length > 1) {
		int choosen_index = partition(data, start, end);
		if (length > k) {
			QuickSort(data, start, choosen_index - 1, k);
			QuickSort(data, choosen_index + 1, end, k);
		}
	}
}


int main() {
	srand(time(NULL));
	fstream file;
	vector<int> a;
	double start, end;
	file.open("input.txt", ios::in);
	int list;
	int n = 0;//number of list
	file >> n;
	for (int i = 0; i < n; i++) {
		file >> list;// read list
		a.push_back(list);
	}
	start = clock();
	int k = 0;
	QuickSort(a, 0, n - 1,k);
	end = clock();
	file.open("output.txt", ios::out);
	ofstream outputfile("output.txt");
	for (int i = 0; i < n; i++) {
		outputfile << a[i] << endl;//write array to file
	}
	double cpu_time = ((end - start)) / CLOCKS_PER_SEC;
	cout << "CPU run time is " << cpu_time << endl;
}
