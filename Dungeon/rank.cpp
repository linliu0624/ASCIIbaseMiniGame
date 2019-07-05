#include "pch.h"
#include "rank.h"
using namespace std;

ranking gameRank[RANK_LENGTH];
std::string fileName = "rank.txt";

void InputFile(ranking r[]) {
	//fstream file;
	//file.open("rank.txt", ios::out);寫入文件
	//類似 file.open("....", ios::out) 

	ofstream file; 
	file.open(fileName);
	if (file)
		for (int i = 0; i < RANK_LENGTH - 1; i++)
			if (r[i].score > 0)
				file << r[i].name << " " << r[i].score << " " << r[i].strTime << endl;
	file.close();
}
/*把文件中的資料存進code*/
void OutputFile(ranking r[]) {
	fstream file;
	file.open(fileName, ios::in);
	int n = 0;
	while (!file.eof() && file) {
		file >> r[n].name;
		file >> r[n].score;
		file >> r[n].strTime;
		file << endl;
		n++;
	}
	file.close();
}
/*insert sort*/
void SortRank(ranking r[], ranking newPlayer) {
	if (newPlayer.score > r[RANK_LENGTH - 1].score) {
		r[RANK_LENGTH - 1] = newPlayer;
	}
	for (int i = 0; i < RANK_LENGTH; i++) {
		int n = i;
		ranking tmp = r[n];
		while (i > 0) {
			if (r[n].score > r[n - 1].score && n > 0 && r[n].score >= GOAL_VALUE) {
				r[n] = r[n - 1];
				r[n - 1] = tmp;
				n--;
			}
			else
				break;
		}
	}
}

void MakeFile() {
	fstream file;
	file.open(fileName, ios::in);
	file.close();
}
//void ShowRank(ranking r[]) {
//	cout << "No.  Name          Score      time" << endl;
//	cout << "================================================" << endl;
//	int n = 1;
//	for (int i = 0; i < RANK_LENGTH - 1; i++) {
//		if (r[i].score > 0) {
//			cout << n << ".   " << r[i].name << "          " << r[i].score << "      " << r[i].strTime << endl;
//			if (r[i].score != r[i + 1].score) {
//				n++;
//			}
//		}
//	}
//}