#include "ranking.h"
using namespace std;
ranking rank[RANK_LENGTH];
string fileName = "rank.txt";

void inputFile(ranking r[], int size) {
	//fstream file;
	//file.open("rank.txt", ios::out);//寫入文件
	ofstream file; //類似 file.open("....", ios::out) 
	file.open(fileName);
	for (int i = 0; i < size - 1; i++)
		file << r[i].name << " " << r[i].score << endl;
	file.close();
}
void outputFile(ranking r[], ranking newguy) {
	fstream file;
	file.open(fileName, ios::in);
	int n = 0;
	while (true) {
		file >> r[n].name;
		file >> r[n].score;
		cout << r[n].name << " " << r[n].score << endl;
		file << endl;
		n++;
		if (n == RANK_LENGTH - 1) {
			strcpy_s(r[n].name, newguy.name);
			r[n].score = newguy.score;
			break;
		}
	}
	file.close();
}
/*insert sort*/
void sortRank(ranking r[], int size) {
	for (int i = 0; i < size; i++) {
		int n = i;
		ranking tmp = r[n];
		while (i > 0) {
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