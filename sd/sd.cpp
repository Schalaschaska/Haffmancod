// sd.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
using namespace std;

void Expectancy();
long MinK();
void SumUp();
void BuildBits();
void OutputResult(char **Result);
void Clear();

const int MaxK = 1000;
long k[MaxK + 1], a[MaxK + 1], b[MaxK + 1];
char bits[MaxK + 1][40];
char sk[MaxK + 1];
bool Free[MaxK + 1];
char *res[256];
long i, j, n, m, kj, kk1, kk2;
char str[256];

int _tmain(int argc, _TCHAR* argv[])
{
	
	char *BinaryCode;
	Clear();
	cout << "str:";
	cin >> str;
	Expectancy();
	SumUp();
	BuildBits();
	OutputResult(&BinaryCode);
	cout << "encoded str ";
	cout << BinaryCode << endl;
	system("pause");
	return 0;
}
//описание функции обнуления данных в массивах
void Clear() {
	for (i = 0; i < MaxK + 1; i++) {
		k[i] = a[i] = b[i] = 0;
		sk[i] = 0;
		Free[i] = true;
		for (j = 0; j < 40; j++)
			bits[i][j] = 0;
	}
}
/*описание функции вычисления вероятности вхождения каждого символа в тексте*/
void Expectancy() {
	long *s = new long[256];
	for (i = 0; i < 256; i++)
		s[i] = 0;
	for (n = 0; n < strlen(str); n++)
		s[str[n]]++;
	j = 0;
	for (i = 0; i < 256; i++)
		if (s[i] != 0) {
			j++;
			k[j] = s[i];
			sk[j] = i;
		}
	kj = j;
}
/*описание функции нахождения минимальной частоты символа в исходном тексте*/
long MinK() {
	long min;
	i = 1;
	while (!Free[i] && i < MaxK) i++;
	min = k[i];
	m = i;
	for (i = m + 1; i <= kk2; i++)
		if (Free[i] && k[i] < min) {
			min = k[i];
			m = i;
		}
	Free[m] = false;
	return min;
}
//описание функции подсчета суммарной частоты символов
void SumUp() {
	long s1, s2, m1, m2;
	for (i = 1; i <= kj; i++) {
		Free[i] = true;
		a[i] = 0;
		b[i] = 0;
	}
	kk1 = kk2 = kj;
	while (kk1 > 2) {
		s1 = MinK();
		m1 = m;
		s2 = MinK();
		m2 = m;
		kk2++;
		k[kk2] = s1 + s2;
		a[kk2] = m1;
		b[kk2] = m2;
		Free[kk2] = true;
		kk1--;
	}
}
//описание функции формирования префиксных кодов
void BuildBits() {
	strcpy_s(bits[kk2], "1");
	Free[kk2] = false;
	strcpy_s(bits[a[kk2]], bits[kk2]);
	strcat_s(bits[a[kk2]], "0");
	strcpy_s(bits[b[kk2]], bits[kk2]);
	strcat_s(bits[b[kk2]], "1");
	i = MinK();
	strcpy_s(bits[m], "0");
	Free[m] = true;
	strcpy_s(bits[a[m]], bits[m]);
	strcat_s(bits[a[m]], "0");
	strcpy_s(bits[b[m]], bits[m]);
	strcat_s(bits[b[m]], "1");
	for (i = kk2 - 1; i > 0; i--)
		if (!Free[i]) {
			strcpy_s(bits[a[i]], bits[i]);
			strcat_s(bits[a[i]], "0");
			strcpy_s(bits[b[i]], bits[i]);
			strcat_s(bits[b[i]], "1");
		}
}
//описание функции вывода данных 
void OutputResult(char **Result) {
	(*Result) = new char[1000];
	for (int t = 0; i < 1000;i++)
		(*Result)[t] = 0;
	for (i = 1; i <= kj; i++)
		res[sk[i]] = bits[i];
	for (i = 0; i < strlen(str); i++)
		strcat_s((*Result),1000 , res[str[i]]);
}


