#include <algorithm>
#include <string>
#include <iostream>
#include "SecondUnit.h"
#include "Unit1.h"

using namespace std;

unsigned int count(string s1)
{
	unsigned int c=0 ;
	char s2=' ';
	size_t cnt = 0;
	for(string::size_type i = 0; i < s1.length(); i++){if(s1[i] == s2)c++;}
	return c+1;
}

string equal(string s1, string s2){
	if (count(s1)<count(s2)){
		for (int i = 0;i<(count(s2)-count(s1)+1); i++) {
			s1 += " a ";//.push_back(' ');
		}
		return s1;
	}
	if (count(s1)>count(s2)){
		for (int i = 0;i<(count(s1)-count(s2)+1); i++) {
			s2 += " a ";//.push_back(' ');
		}
		return s2;
	}
}

string word(string s, int num_word){
	int prev=0, i=0;
	for(;i<s.length();i++){
		if (s[i]==' '){
			num_word--;
			if (num_word==0)
				break;
			prev = i;
		}
	}
	if (prev == 0) prev--;
	return s.substr(prev+1,i-prev);
}

int check(char src, int a, int b){
	 if ((static_cast<int>(src)>a)&&(static_cast<int>(src)<b))
		return 1;
	 return 0;
}

string reduce(string src ){
	string c="";
	char temp;
	setlocale(LC_ALL, "russian_russia.1251");
	int is_space=0;
	for(int i=0;i<src.length();i++)
	{
			if ((check(src[i],64,91))||(check(src[i],96,123))||(check(src[i],-65,0))){
				temp = tolower(src[i]);
				c.push_back(temp);
				is_space=0;
			}
			if (((check(src[i],31,33))||(check(src[i],153-256,151-256))||(check(src[i],161-256,159-256))||(check(src[i],174-256,172-256)))&&(!is_space)){
				c.push_back(' ');
				is_space=1;
			}
			if (check(src[i],47,58))
			{
				temp = src[i];
				c.push_back(temp);
				is_space=0;
			}
		}
	return c;
}


int distanceString(string s, string t) {
	if (count(s)<count(t)) {s = equal(s,t);} else if (count(s)>count(t)) t = equal(s,t);
	cout<<s;
	int n = count(s);
	int m = count(t);
	int **d = new int *[n+1];
	for (int i = 0; i<n+1; i++) {
		d[i] = new int[m+1];
	}
	if (n == 0) {
		return m;
	}
	if (m == 0) {
		return n;
	}
	for (int i = 0; i <= n; i++) {
		d[i][0] = i;
	}
	for (int j = 0; j <= m; j++) {
		d[0][j] = j;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int cost = (word(t,j-1) == word(s,i-1))?0:1;
			d[i][j] = min(min(d[i-1][j]+1,d[i][j-1]+1),d[i-1][j-1]+cost);
		}
	}
	return d[n][m];
}
