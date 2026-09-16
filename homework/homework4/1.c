#include<stdio.h>
#include<stdlib.h>
int main() {
	int n;
	scanf_s("%d", &n);
	int city[50][50];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf_s("%d", &city[i][j]);
		}
	}
	int hang[50];
	int lie[50];
	int temp=-1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (city[i][j] > temp)
				temp = city[i][j];
		}
		hang[i] = temp;
		temp = -1;
	}
	temp = -1;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			if (city[i][j] > temp)
				temp = city[i][j];
		}
		lie[j] = temp;
		temp = -1;
	}
	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res += (((hang[i] < lie[j]) ? hang[i] : lie[j]) - city[i][j]);
		}
	}
	printf("%d", res);
}