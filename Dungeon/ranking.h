//#include <stdio.h>
//#include "define.h"
//#include <string.h>
//
//int main()
//{
//FILE *fp;
//int n;
//
//char name[10][100];//名前の配列(10人*100文字まで)
//int point[10];//数字の配列(10人分)
//char time[10][100];
//
//int i,j;//ソート部用
//char boxname[100];//ソート部一時文字列
//int boxpoint;//ソート部一時変数
//char boxtime;//ソート部一時変数
//
//if ((fp = fopen("score.txt", "r")) == NULL) {
//printf("fopen failed\n");
//return 0;
//}
//
////配列に全員分の名前と数字を入る
//for (n=0; n<10; n++) {
//fscanf(fp, "%s %d %s", name[n], point[n], &time[n]);
//printf("%s %d 万円 %s \n\n", name[n], point[n], time[n]);
//}
//
////ソート部。
//for(i = 0; i < 10; i++)
//{
//for(j = 0;j < 10; j++)
//{
//if(point[i] < point[j])
//{
////得点入れ替え
//boxpoint = point[i];
//point[i] = point[j];
//point[j] = boxpoint;
////名前入れ替え
//strcpy(boxname,name[i]);
//strcpy(name[i],name[j]);
//strcpy(name[j],boxname);
//
//strcpy(boxtime,time[i]);
//strcpy(time[i],time[j]);
//strcpy(time[j],boxtime);
//}}}
//
////順位表示
//for(n=0;n<10;n++)
//printf("%d 位 : %s %d 万円 %s\n", n + 1, name[n], point[n]);
//
//fclose(fp);
//
//return 0;
//}