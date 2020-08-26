#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
vector<int>weight, value, res;
vector<vector<vector<int>>> v_table;
int num, limit;

void get_file(){
	fstream file;
	int tmp;
	file.open("input.txt", ios::in);
	file >> num;
	file >> limit;
	if (!file) { 
		cout << "file_read_error!" << endl; 
	}
	else
		for (int i = 0; i < num; i++) {
			file >> tmp;
			value.push_back(tmp);
			file >> tmp;
			weight.push_back(tmp);
		}
		file.close();
}

void init_table() { //三維陣列 儲存各狀態的總價值 大小為 (n+1)*(w+1) 深度為儲存該價值的物件組合
	v_table.resize(limit+1);
	for (int i = 0; i <= limit; i++) {
		v_table[i].resize(num+1);
		for (int j = 0; j <= num; j++) {
			v_table[i][j].resize(1);//初始化深度為1 之後用push_back
		}
	}
	for (int i = 0; i <= limit; i++) {
		for (int j = 0; j <= num; j++) {
			v_table[i][j][0] = 0;
		}
	}
}

int knapsack(vector<int>&v, vector<int>&w, int num, int lim)
{
	for (int i = 1; i <= num; i++) { //遍歷所有物品
		for (int j = 0; j <=lim; j++) {//遍歷所有可能的重量
			//v_table[j][i-1] 在j這個重量下沒放i的價值
			//v_table[j-w[i-1]][i-1] +v[i-1] 在沒加上i的重量的重量下加上i以及其重量的價值 
			//w[i-1], v[i-1] 第i個物品的重量與價值
			if (j - w[i - 1] >= 0) { //當weight可以加入item
				v_table[j][i][0] = max(v_table[j][i - 1][0], (v_table[j - w[i - 1]][i - 1][0] + v[i - 1]));//選擇放與不放兩種可能的最佳解
				if (v_table[j][i][0] == v_table[j - w[i - 1]][i - 1][0] + v[i - 1] && v_table[j][i][0] != v_table[j][i - 1][0]) {
					for (int z = 1; z < v_table[j - w[i - 1]][i - 1].size(); z++) {
						v_table[j][i].push_back(v_table[j - w[i - 1]][i - 1][z]);//這深度放入上個狀態的物件組合
					}
					v_table[j][i].push_back(i);//放入此物品
				}
				else { 
					for (int z = 1; z < v_table[j][i - 1].size(); z++) {
						v_table[j][i].push_back(v_table[j][i - 1][z]);//這深度放入上個狀態的物件組合
					}
				}
			}
			else {
				v_table[j][i][0] = v_table[j][i - 1][0]; //當超重所以不放
				for (int z = 1; z < v_table[j][i - 1].size(); z++) {
					v_table[j][i].push_back(v_table[j][i - 1][z]);//這深度放入上個狀態的物件組合
				}
			}
		}
	}
	return v_table[lim][num][0];
}

void output_file() {
	fstream file;
	file.open("output.txt", ios::out);
	int result = knapsack(value, weight, num, limit);
	file << "Total revenue = " << result << "\n";
	file << "Selected item: ";
	for (int i = 1; i < v_table[limit][num].size(); i++) {
		file << v_table[limit][num][i] << " ";
	}
	file.close();
}
int main(void){
	get_file();
	init_table();
	output_file();
}