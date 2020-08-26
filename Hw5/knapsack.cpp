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

void init_table() { //�T���}�C �x�s�U���A���`���� �j�p�� (n+1)*(w+1) �`�׬��x�s�ӻ��Ȫ�����զX
	v_table.resize(limit+1);
	for (int i = 0; i <= limit; i++) {
		v_table[i].resize(num+1);
		for (int j = 0; j <= num; j++) {
			v_table[i][j].resize(1);//��l�Ʋ`�׬�1 �����push_back
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
	for (int i = 1; i <= num; i++) { //�M���Ҧ����~
		for (int j = 0; j <=lim; j++) {//�M���Ҧ��i�઺���q
			//v_table[j][i-1] �bj�o�ӭ��q�U�S��i������
			//v_table[j-w[i-1]][i-1] +v[i-1] �b�S�[�Wi�����q�����q�U�[�Wi�H�Ψ䭫�q������ 
			//w[i-1], v[i-1] ��i�Ӫ��~�����q�P����
			if (j - w[i - 1] >= 0) { //��weight�i�H�[�Jitem
				v_table[j][i][0] = max(v_table[j][i - 1][0], (v_table[j - w[i - 1]][i - 1][0] + v[i - 1]));//��ܩ�P�����إi�઺�̨θ�
				if (v_table[j][i][0] == v_table[j - w[i - 1]][i - 1][0] + v[i - 1] && v_table[j][i][0] != v_table[j][i - 1][0]) {
					for (int z = 1; z < v_table[j - w[i - 1]][i - 1].size(); z++) {
						v_table[j][i].push_back(v_table[j - w[i - 1]][i - 1][z]);//�o�`�ש�J�W�Ӫ��A������զX
					}
					v_table[j][i].push_back(i);//��J�����~
				}
				else { 
					for (int z = 1; z < v_table[j][i - 1].size(); z++) {
						v_table[j][i].push_back(v_table[j][i - 1][z]);//�o�`�ש�J�W�Ӫ��A������զX
					}
				}
			}
			else {
				v_table[j][i][0] = v_table[j][i - 1][0]; //��W���ҥH����
				for (int z = 1; z < v_table[j][i - 1].size(); z++) {
					v_table[j][i].push_back(v_table[j][i - 1][z]);//�o�`�ש�J�W�Ӫ��A������զX
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