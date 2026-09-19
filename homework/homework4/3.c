#include<stdio.h>
#include<string.h>

int main() {
	int n;
	scanf_s("%d", &n);
	
	char secret[1000];
	char guess[1000];

	scanf_s("%s", secret,1000);//最后还得加入缓冲区大小
	scanf_s("%s", guess,1000);

	int bulls=0;
	int cows = 0;

	int state[1000] = { 0 };
	int num[1000] = { 0 };
	for (int i = 0; i < n; i++) {
		if (secret[i] == guess[i]) {
			bulls++;
			state[i] = 1;
		}
		else {
			num[secret[i]-'0']++;
		}
	}
	for (int i = 0; i < n; i++) {
		if (state[i] == 0 && num[guess[i]-'0']>0) {
			num[guess[i]-'0']--;
            state[i]=1;
			cows++;
		}
	}
	printf("%dA%dB", bulls, cows);
	return 0;
}

