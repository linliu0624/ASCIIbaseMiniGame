/***************************************
*Rankの処理に関して
*作者：林
***************************************/
#include "ranking.h"
using namespace std;
ranking rank[RANK_LENGTH];
const string fileName = "rank.txt";

void InputFile(ranking r[]) {
	//fstream file;
	//file.open("rank.txt", ios::out);//寫入文件
	ofstream file; //類似 file.open("....", ios::out) 
	file.open(fileName);
	for (int i = 0; i < RANK_LENGTH - 1; i++)
		file <<"     "<< r[i].name << "     " << r[i].score << "      " << r[i].time << endl;
	file.close();
}
void OutputFile(ranking r[], ranking newPlayer) {
	fstream file;
	file.open(fileName, ios::in);
	int n = 0;
	while (true) {
		if (r[n].score == 0) {
			strcpy_s(r[n].name, newPlayer.name);
			r[n].score = newPlayer.score;
			r[n].time = newPlayer.time;
		}
		file >> r[n].name;
		file >> r[n].score;
		file >> r[n].time;
		file << endl;
		n++;
		if (n == RANK_LENGTH - 1) {
			break;
		}
	}
	file.close();
}
/*insert sort*/
void SortRank(ranking r[]) {
	for (int i = 0; i < RANK_LENGTH; i++) {
		int n = i;
		ranking tmp = r[n];
		while (i > 0 && r[i].score > 0) {
			if (r[n].score > r[n - 1].score && n > 0) {
				r[n] = r[n - 1];
				r[n - 1] = tmp;
				n--;
			}
			else
				break;
		}
	}
}

void ShowRank(ranking r[]) {
	cout << "No.  Name      Score      time" << endl;
	cout << "================================================" << endl;
	int n = 1;
	for (int i = 0; i < RANK_LENGTH - 1; i++) {
		if (r[i].score > 0) {
			cout << n << ".      " << r[i].name << "      " << r[i].score << "      " << r[i].time << endl;
			if (r[i].score != r[i + 1].score) {
				n++;
			}
		}
	}
}

void MakeFile() {
	ofstream file; 
	file.open(fileName);
	file.close();
}