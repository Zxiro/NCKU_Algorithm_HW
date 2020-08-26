#include<iostream>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<fstream>
#include<math.h>
using namespace std;

void printarr(vector<int>&v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i]<<" ";
	}
	cout << endl;
}
int partition(vector<int> &v, int key, int start, int end) {
	int index;
	int min_ptr = start -1;
	int value = key;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == key) {
			index = i;
			break;
		}
	}
	v[index] = v[end];
	for (int max_ptr = start; max_ptr < end; max_ptr++)
	{
		if (v[max_ptr] < value) {
			min_ptr++;
			swap(v[max_ptr], v[min_ptr]);
		}
	}
	index = min_ptr + 1;
	v[end] = v[index];
	v[index] = value;
	return index;
}
void insertion_sort(vector<int> &v, int start, int end) {
	for (int i = start + 1; i <= end; i++) {
		int key = v[i];
		int j = i - 1;
		while (j >= 0 && v[j] > key) {
			v[j + 1] = v[j];
			j = j - 1;
		}
		v[j + 1] = key;
	}
}
int median_of_medians(vector<int>&v,int key,float d, int start, int end) {
	//key �ĴX�p���Ʀr divide �C�X�Ӥ����@��
	float g = ceil((end -start + 1) / d); //�̦h���X��
	vector<int>mid;
	int s, e;
	for (int i = 0; i < g; i++) {
		s = i * d;
		e = (i + 1)*d - 1;
		if (e < v.size()) {
			insertion_sort(v, s, e);
			mid.push_back(v[(s + e) / 2]);
		}
		else {
			insertion_sort(v, s, v.size()-1);
			mid.push_back(v[(s + v.size()-1) / 2]);
		}
	}
	if (g == 1) {
		return v[key - 1 + start];
	}
	int midnum = median_of_medians(mid, mid.size()/2, d, 0, mid.size() - 1);
	//���j�I�s������Ƥ��������
	int pivot = partition(v, midnum, start, end);
	//partitio���sn
	if (pivot - start + 1 == key) {
		return v[pivot];
	};
	if (pivot > key) { 
		return median_of_medians(v, key, d, start, pivot);
		//��i<k���a�軼�j
	};
	return median_of_medians(v, key - pivot + start - 1,d, pivot + 1, v.size() - 1);
		//��i>k���a�軼�j
	}
int main(void) {
	int num,key,size,ans;
	float divide =3.0;
	fstream file;
	vector<int>vec;
	file.open("input.txt", ios::in);
	if (!file) {
		cout << "err";
		system("pause");
		return 0;
	}
	file >> size;
	file >> key;
	for (int i = 0; i < size; i++) {
		file >> num;
		vec.push_back(num);
	}
	file.close();
	ans = median_of_medians(vec, key, divide, 0, vec.size()-1);
	file.open("output.txt", ios::out);
	file << size << "\n";
	file << key << "\n";
	file << ans << "\n";
	file.close();
}