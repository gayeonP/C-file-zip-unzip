#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10000

int zip(FILE* fp, FILE* fw) {
	char str[MAX_SIZE + 1]; 

	if ((fp = fopen("data.txt", "rt")) == NULL) { // file open & error checking
		printf("unable to open file\n");
		return -1;
	}

	if ((fw = fopen("datazip.txt", "wt")) == NULL) { // file write & error checking
		printf("unable to write file\n");
		return -1;
	}

	int cnt = 0; // count var
	char ch = 0; // checking var
	while (fgets(str, sizeof(str), fp) != NULL) { 
		ch = str[0];
		for (unsigned int i = 0; i < strlen(str); i++) {
			if (ch == str[i]) {
				cnt++;

				// 파일의 끝이 마지막인것을 검사
				if ((strlen(str) != MAX_SIZE) && (i == strlen(str) - 1)) {
					fprintf(fw, "%c%d", ch, cnt);
					ch = str[i];
					cnt = 1;
				}
			}
			else {
				fprintf(fw, "%c%d", ch, cnt);
				ch = str[i];
				cnt = 1;
			}
		}
	}

	fclose(fp);
	fclose(fw);

	return 0;
}

int unzip(FILE* fp, FILE* fw) {
	if ((fp = fopen("datazip.txt", "rt")) == NULL) { // file open & error checking
		printf("unable to open file\n");
		return -1;
	}

	if ((fw = fopen("datanew.txt", "wt")) == NULL) { // file write & error checking
		printf("unable to write file\n");
		return -1;
	}

	char c = 0; // 알파벳을 담을 변수
	int d = 0; // count, 숫자를 담을 변수
	while (fscanf(fp, "%c%d", &c, &d) != EOF) {
		for (int i = 0; i < d; i++) {
			fputc(c, fw);
		}
	}

	fclose(fp);
	fclose(fw);

	return 0;
}

int main(int argc, char* argv[]) {

	FILE* fp = NULL; // open
	FILE* fw = NULL; // write

	// 0 입력: 압축
	// 1 입력: 압축 해제
	int a = 0;
	printf("압축: 0\n압축해제: 1\n입력: ");
	int res = scanf("%d", &a);

	if (a) res = unzip(fp, fw);
	else res = zip(fp, fw);

	if (res == 0) printf("성공\n");
	else printf("실패\n");

	return 0;
}