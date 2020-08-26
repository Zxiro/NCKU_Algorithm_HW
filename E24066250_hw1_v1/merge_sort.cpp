#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<cstdlib>
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
		int x = rand()%9999;
		int y = rand()%9999;
		tmp = random_data[x];
		random_data[x] = random_data[y];
		random_data[y] = tmp;
	}
	file << 10000 <<" ";
	for (int i = 0; i < 10000; i++) {
		file << random_data[i] << " ";
	}
	file.close();
}

void Merge(vector<int>&array, int front, int mid, int end){
    int left_index = 0 ; 
    int right_index = 0 ;
    vector<int>left(array.begin()+front, array.begin()+mid+1);
    vector<int>right(array.begin()+mid+1, array.begin()+end+1);
    for (int i = front; i <= end; i++ ){
            if( left[left_index] <= right[right_index]&&left_index!=-1||right_index ==-1){
                array[i] = left[left_index];
                if(left_index+1 == left.size()){
                    left_index = -1;
                    continue;
                }
                else
                    left_index++;
            }
            else{
                array[i] = right[right_index];
                if(right_index+1 == right.size()){
                    right_index = -1;
                    continue;
                }
                else
                    right_index++;
            }
        
    }
}
void MergeSort(vector<int> &array, int front, int end){
    if(front<end){
    int mid = (front+end)/2; //divide
    MergeSort(array, front, mid);
    MergeSort(array, mid+1, end);
    Merge(array, front, mid, end);
    }
}

void PrintSave(vector<int>&array, fstream &file){
    for(int i = 0 ; i<array.size(); i++){
        cout<<array[i]<<endl;
        file<<array[i]<<"\n";
    }
}

int main(void){
    fstream file;
    vector<int> data;
    string tmp;
    int vec_data;
    int key_amount;
    clock_t start, end;
    file.open("input.txt", ios::in);
    file>> key_amount;
    for (int i = 0; i < key_amount; i++) {
        file >> vec_data;
        data.push_back(vec_data);
    }
    file.close();
    start = clock();
    MergeSort(data, 0, key_amount-1);
    end = clock();
    file.open("output.txt", ios::out);
    PrintSave(data, file);
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "CPU run time is " << cpu_time << "sec" << endl;
}

