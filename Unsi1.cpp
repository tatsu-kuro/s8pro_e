//unsi1 760,105 ::4 holes ocarina
#include "stdafx.h"
#include "Syaku8.h"
#include "Syaku8Doc.h"
#include "Syaku8View.h"
#include "math.h"
#include "tuner.h"
extern int ct[15][2];
extern DATADP DP;
extern int lastinst;//last instrment
extern int lasttn;//last tone numb.
extern CPen *RedPen,*Red2Pen,*NotPen;
extern char *abc[15];//={"a","b$","b","c","d$","d","e$","e","f","g$","g","a$","a"};
char horn[45][3]={
1,1,1,  1,0,1,  0,1,1,  1,1,0,  1,0,0,  0,1,0,

0,0,0,  1,1,1,  1,0,1,  0,1,1,  1,1,0,  1,0,0,
0,1,0,  0,0,0,  0,1,1,  1,1,0,  1,0,0,  0,1,0,

0,0,0,  1,1,0,  1,0,0,  0,1,0,  0,0,0,  1,0,0,
0,1,0,  0,0,0,  0,1,1,  1,1,0,  1,0,0,  0,1,0,

0,0,0,  1,1,0,  1,0,0,  0,1,0,  0,0,0,  1,0,0,
0,1,0,  0,0,0,  0,1,1,  1,1,0,  1,0,0,  0,1,0,

0,0,0};
char pet[32][3]={
1,1,1,  1,0,1,  0,1,1,  1,1,0,  1,0,0,  0,1,0,

0,0,0,  1,1,1,  1,0,1,  0,1,1,  1,1,0,  1,0,0,
0,1,0,  0,0,0,  0,1,1,  1,1,0,  1,0,0,  0,1,0,

0,0,0,  1,1,0,  1,0,0,  0,1,0,  0,0,0,  1,0,0,
0,1,0,  0,0,0,  0,1,1,  1,1,0,  1,0,0,  0,1,0,

0,0,0};
char sax[35][23]={
	0,0,0,0,0,0,1,0,1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,
	0,0,0,0,0,1,0,0,1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,
	0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,//do
	0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,
	0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,1,0,0,//re
	0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,1,1,0,
	0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,0,0,0,//mi
	0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,//fa
	0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,1,0,0,0,
	0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,//sol
	0,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,//ra
	0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//ti
	0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,//do
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,//re
	0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,1,0,
	0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,1,1,0,0,0,//mi
	0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,//fa
	0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,
	0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,//sol
	0,0,0,1,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,//ra
	0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,//ti
	0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,//do
	0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,//re
	1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
	1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,//mi
	1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,//fa
	1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,
};
char flute[38][15]={
	1,0,1,1,1,0,0,1,0,1,0,1,0,1,1,
	1,0,1,1,1,0,0,1,0,1,0,1,0,0,1,
	1,0,1,1,1,0,0,1,0,1,0,1,0,0,0,
	1,0,1,1,1,0,0,1,0,1,0,1,1,0,0,
	1,0,1,1,1,0,0,1,0,1,0,0,1,0,0,
	1,0,1,1,1,0,0,1,0,0,0,0,1,0,0,//f
	1,0,1,1,1,0,0,0,0,0,0,1,1,0,0,
	1,0,1,1,1,0,0,0,0,0,0,0,1,0,0,
	1,0,1,1,1,1,0,0,0,0,0,0,1,0,0,
	1,0,1,1,0,0,0,0,0,0,0,0,1,0,0,
	1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,
	1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,
	1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
	0,0,1,1,1,0,0,1,0,1,0,1,0,0,0,
	0,0,1,1,1,0,0,1,0,1,0,1,1,0,0,

	1,0,1,1,1,0,0,1,0,1,0,0,1,0,0,
	1,0,1,1,1,0,0,1,0,0,0,0,1,0,0,//f
	1,0,1,1,1,0,0,0,0,0,0,1,1,0,0,
	1,0,1,1,1,0,0,0,0,0,0,0,1,0,0,
	1,0,1,1,1,1,0,0,0,0,0,0,1,0,0,
	1,0,1,1,0,0,0,0,0,0,0,0,1,0,0,
	1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,
	1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,
	1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,

	0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,
	1,0,1,1,1,1,0,1,0,1,0,1,1,0,0,
	1,0,1,1,0,0,0,1,0,1,0,0,1,0,0,
	1,0,1,0,1,0,0,1,0,0,0,0,1,0,0,//f
	1,0,1,0,1,0,0,0,0,0,0,1,1,0,0,
	1,0,0,1,1,0,0,0,0,0,0,0,1,0,0,
	0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,
	0,0,1,1,0,0,0,1,0,0,0,0,1,0,0,
	0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,
	1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,
	1,0,0,1,1,1,0,1,0,0,0,0,0,0,0
};
char cla[44][18]={
	0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,1,0,1,
	0,0,0,1,1,1,0,1,0,0,0,0,1,1,0,1,0,1,
	0,0,0,1,1,1,0,1,0,0,1,0,1,1,0,1,0,1,
	0,0,0,1,1,1,0,1,0,0,0,0,1,1,0,1,0,0,
	0,0,0,1,1,1,0,1,0,0,0,0,1,1,0,1,1,0,
	0,0,0,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,
	0,0,0,1,1,1,0,1,0,0,0,0,1,0,0,0,0,0,
	0,0,0,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,

	0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,//do
	0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,1,0,0,0,1,1,1,0,1,0,1,
	
	0,0,1,1,1,1,0,1,0,0,0,0,1,1,0,1,0,1,
	0,0,1,1,1,1,0,1,0,0,1,0,1,1,0,1,0,1,
	0,0,1,1,1,1,0,1,0,0,0,0,1,1,0,1,0,0,
	0,0,1,1,1,1,0,1,0,0,0,0,1,1,0,1,1,0,
	0,0,1,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,
	0,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,0,
	0,0,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,
	0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,//sol
	0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,//la
	0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,//
	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,//ti

	0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//do
	0,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0,0,0,
	0,0,1,1,0,1,0,1,0,0,0,0,1,0,0,0,1,0,
	0,0,1,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,
	0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,//mi
	0,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,1,0,
	0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,//fa
	0,0,1,1,0,1,0,0,0,0,0,0,1,1,0,0,1,0,//sol
	0,0,1,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,
	0,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
char oboe[35][18]={
	0,1,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,
	0,1,0,1,1,1,0,1,0,0,0,1,1,0,1,1,0,0,

	0,1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,//do
	0,1,0,1,1,1,0,0,0,0,0,1,1,0,1,0,1,0,
	0,1,0,1,1,1,0,0,0,0,0,1,1,0,1,0,0,0,
	0,1,0,1,1,1,0,0,0,0,0,1,1,0,1,0,0,1,
	0,1,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,
	0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,
	0,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,
	0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,
	0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	
	0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,1,1,1,0,0,0,0,0,1,1,0,1,0,1,0,
	0,0,0,1,1,1,0,0,0,0,0,1,1,0,1,0,0,0,
	0,0,0,1,1,1,0,0,0,0,0,1,1,0,1,0,0,1,
	0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,
	0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,
	0,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,
	0,1,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,2,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,
	1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,
	1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

	1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,//do
	0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,
	0,0,0,1,1,1,0,1,0,0,0,0,1,0,1,0,0,0,
	0,0,1,1,1,1,0,0,1,1,0,0,1,0,1,0,0,0,//mi
	0,0,1,1,1,0,0,0,1,1,0,0,1,0,1,0,0,0,//fa
	0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,1,0,0,
	0,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0//sol
};
#ifdef English
char *nouname[30]={"Satsu!p","Nana!p","Roku!p","Tyu!p",
"Seki!p","Jo!p","Go!p","Ho!p","Ichi!p","Ni!p",
"San!p","Yon!p","Ge!p","Ichiyon","Nityu!p",
" ","IchiGe"," "};
#else
char *nouname[30]={"札 (Satsu)!p","七 (Nana)!p","六 (Roku)!p","中 (Tyu)!p",
"夕 (Seki)!p","上 (Jo)!p","五 (Go)!p","方 (Ho)!p","一 (Ichi)!p","二 (Ni)!p",
"三 (San)!p","四 (Yon)!p","下 (Ge)!p","一四 (Ichiyon)","二中 (Nityu)!p",
" ","一下 (IchiGe)"," "};
#endif
char nou[37][11]={
	//8番目：cent
	//9番目：表示位置 (0:lower) 1 (2:middle) 3 (4:upper) 
	//10番目：運指の名前のポインタ配列番号を示す
	//11番目はkey
	1,1,1,1,1,1,1, 28,3,0,0,//C satsu
	2,2,2,2,2,2,2,  0,2,15,1,
	2,2,2,2,2,2,2,  0,2,15,2,//D
	1,1,1,1,1,0,1, -1,2,2,3,//E♭roku
	2,2,2,2,2,2,2,  0,2,15,4,
	1,1,1,1,0,0,1,  2,2,3,5,//Ftyu
	1,1,1,0,1,1,1, 32,3,11,6,//yon
	1,1,1,0,0,0,1,-20,1,4,7,//Gseki
	1,1,0,1,1,1,1, 28,3,10,8,//san
	1,1,0,0,0,0,1,-27,1,5,9,//Ajo
	1,0,1,1,1,1,1,-16,1,9,10,//ni
	1,0,0,0,0,0,1, 33,4,6,11,//B go 
	1,0,1,1,0,0,1, 20,2,14,11,//B nityu 

	2,2,2,2,2,2,2,  0,2,15,12,//C
	0,1,1,0,1,1,1, 37,2,13,13,//itiyon
	1,1,1,1,1,1,1, 44,4,0,13,//satsu
	0,1,1,1,1,1,1, 45,4,8,14,//D iti
	0,0,0,0,0,0,1, -1,2,7,14,//D hou
	0,1,1,1,1,1,0, 33,3,16,15,//itige
	1,1,1,1,1,1,0,-14,1,1,15,//ge
	1,1,1,1,1,0,1,-32,1,2,16,//E roku
	1,1,1,1,0,0,1,  2,2,3,17,//F tyu
	2,2,2,2,2,2,2,  0,2,15,18,
	1,1,1,0,0,0,1,-28,1,4,19,//g seki
	1,1,0,0,0,0,1,  8,2,5,20,//jou
	1,1,1,0,1,1,1,-12,0,11,20,//yon
	1,1,0,1,1,1,1, 35,4,10,20,// san
	1,0,1,1,1,1,1, 50,4,9,21,//A ni
	1,0,0,0,0,0,1,-29,1,6,22,//go
	2,2,2,2,2,2,2,  0,2,15,23,//b
	
	0,0,0,0,0,0,1, 42,4,7,24,//Chou
	0,1,1,1,1,1,1, -4,2,8,25,//ichi
	0,1,1,0,1,1,1,-43,0,13,26,//Ditiyon
	2,2,2,2,2,2,2,  0,2,15,27,
	2,2,2,2,2,2,2,  0,2,15,28,//e
	1,0,1,1,0,0,1, 44,4,14,29//Fnityu
};

char rec[29][10]={
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,0,1,
	1,1,1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,0,1,0,0,
	1,1,1,1,1,1,0,0,0,0,
	1,1,1,1,1,0,1,1,1,1,
	1,1,1,1,0,1,1,1,0,0,
	1,1,1,1,0,0,0,0,0,0,//sol
	1,1,1,0,1,1,0,1,0,0,
	1,1,1,0,0,0,0,0,0,0,
	1,1,0,1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,0,0,0,
	1,0,1,0,0,0,0,0,0,0,//do
	0,1,1,0,0,0,0,0,0,0,
	0,0,1,0,0,0,0,0,0,0,//re
	0,0,1,1,1,1,1,1,0,0,
	2,1,1,1,1,1,0,0,0,0,//mi
	1,1,1,1,1,0,1,1,0,0,
	2,1,1,1,0,1,0,0,0,0,
	2,1,1,1,0,0,0,0,0,0,//sol
	2,1,1,0,1,0,0,0,0,0,
	2,1,1,0,0,0,0,0,0,0,
	2,1,1,0,1,1,1,1,0,0,
	2,1,1,0,1,1,0,0,0,0,
	2,1,0,0,1,1,0,0,0,0,//do
	2,1,0,1,1,0,1,1,1,1,
	2,1,0,1,1,0,1,1,0,0,
};
int tro[35]={
	7,6,5,4,3,2,1,7,6,5,4,3,2,1,5,4,3,2,1,4,3,2,1,3,2,1,3,2,3,2,1};

void Disp12(CDC* MemDC,CDC* pDC,int a,int b,int da,int db,int n,int x,int y,int x1,int y1,int sx,int sy)
{//                               dest_xy     dx,dy         0-1   sorce_xy    offset1     offset from offset1
	int xx,yy;
	if(n==0){xx=x+x1;yy=y+y1;}
	else {xx=x+x1+sx;yy=y+y1+sy;}
	pDC->BitBlt(a+x1,b+y1,da,db,MemDC,xx,yy,SRCCOPY);
}
void Disp12abs(CDC* MemDC,CDC* pDC,int a,int b,int da,int db,int n,int x,int y,int x1,int y1,int sx,int sy,int sx1,int sy1,int sx2,int sy2)
{//                               dest_xy     dx,dy         0-1   sorce_xy    offset1     offset2
	int xx,yy;
	if(n==0){xx=x+x1;yy=y+y1;}
	else if(n==1) {xx=x+sx;yy=y+sy;}
	else if(n==2){xx=x+sx1;yy=y+sy1;}
	else if(n==3){xx=x+sx2;yy=y+sy2;}
	pDC->BitBlt(a+x1,b+y1,da,db,MemDC,xx,yy,SRCCOPY);
}
/*char *sinosub[40]={
	"0",
	"0",
	"1i",
	"1",
	"2i",
	"2",
	"3i",
	"3",
	"4",
	"5i",
	"5",
	"6i",
	"6",
	"7i",
	"7",
	"1",
	"2i",
	"2",
	"3i",
	"3",
	"4",
	"5i",
	"5",
	"6i",
	"6",-,-,-,
	"7i",-,-,
	"7",-,-,-,
	"1k8j",
	"2i",
	"2",
	"3i",
	"3",
	"4",
	"5i",
	"5",
	"6i",
	"6",
	"7i",
	"7",
};
*/
char *sinosub[13]={
	"1 ",
	"2i",
	"2 ",
	"3i",
	"3 ",
	"4 ",
	"5i",
	"5 ",
	"6i",
	"6 ",
	"7i",
	"7 ",
};
void printsinobue(CDC* MemDC,CDC* pDC,int key)
{
	int x=unX+80,y=unY+10;
	if(key<2)pDC->BitBlt(x,y,16,14,MemDC,0,766,SRCCOPY);
	else if(key<3){
		pDC->BitBlt(x,y,16,14,MemDC,16,766,SRCCOPY);
		pDC->BitBlt(x+17,y,10,14,MemDC,128,766,SRCCOPY);
	}
	else if(key<15)pDC->BitBlt(x,y,16,14,MemDC,16*(sinosub[(key-3)%12][0]-'0'),766,SRCCOPY);
	else pDC->BitBlt(x,y,10,14,MemDC,10*(sinosub[(key-3)%12][0]-'0')+288,204,SRCCOPY);
	if(key>2&&sinosub[(key-3)%12][1]=='i')pDC->BitBlt(x+11+(key<15)*6,y,10,14,MemDC,128,766,SRCCOPY);
	if(key>26)pDC->BitBlt(x+1,y-11,10,10,MemDC,144,766,SRCCOPY);
//	if(key>26)pDC->BitBlt(x+1,y-11,10,10,MemDC,16*9,766,SRCCOPY);
	if(key==13){
		pDC->BitBlt(x+30,y,10,10,MemDC,160,766,SRCCOPY);
		pDC->BitBlt(x+36,y,10,14,MemDC,288,204,SRCCOPY);
	}
	if(key==27){
		pDC->BitBlt(x+13,y,10,10,MemDC,160,766,SRCCOPY);
//		pDC->BitBlt(x+20,y,10,14,MemDC,8*10+288,204,SRCCOPY);
		pDC->BitBlt(x+20,y,10,14,MemDC,368,204,SRCCOPY);
	}
}
//0:inkeytable　運指図の左上のキー表示
//1:junseiroot　純正律のルート
//2:tone_mini　楽器音域の最低音
//3:tone_max　楽器音域の最高音
//4:keychange mini　楽器キーの最低値(0:C 1:Db 2:D) shaku8,sinobue are different.
//5:keychange max　楽器キーの最高値
//6:int pa[27][6]={ の変化域範囲を書き換えること！！！！
//7-9:予備
int inst_para[31][10]={
	{ 3, 0,78,116,11,32,7,8,9,10},//KINKO
	{ 3, 0,78,116,11,32,7,8,9,10},//TOZAN
	{ 3, 0,78,116,11,32,7,8,9,10},//NANAKOU
	{ 6, 7,61, 99, 1,13,7,8,9,10},//SINOBUE
	{ 3, 0,72,101, 0, 0,7,8,9,10},//NOUKAN
	{ 9, 8,48, 68, 7,19,7,8,9,10},//OCARINA
	{ 9, 8,60, 72, 7,19,7,8,9,10},//OCARINA4
	{ 0, 8,60, 96, 5, 6,7,8,9,10},//FLUTE
	{10,10,50, 91, 5, 6,7,8,9,10},//CLARINET
	{10,10,52, 82, 5, 6,7,8,9,10},//TRUMPET

	{10,10,56, 88, 5, 6,7,8,9,10},//SOPRANOSAX
	{ 3, 5,49, 81, 5, 6,7,8,9,10},//ALTOSAX
	{10,10,44, 76, 5, 6,7,8,9,10},//TENORSAX
	{ 0, 8,52, 82, 5, 6,7,8,9,10},//TROMBONE
	{ 5, 3,47, 89, 5, 6,7,8,9,10},//FHORN
	{10,10,52, 94, 5, 6,7,8,9,10},//BHORN
	{ 0, 8,60, 86, 5, 6,7,8,9,10},//RECORDER
	{ 0, 8,58, 91, 5, 6,7,8,9,10},//OBOE
	{ 9, 8,60, 95, 0,19,7,8,9,10},//TIN
	{ 5, 8,48-12, 72-12, 0+11,22+11,7,8,9,10},//BANSURI
	{ 9, 8, 0,200, 0,12,7,8,9,10},//FULLRANGE
};
//上の並びは#define 楽器　どおりにすること
//Syaku8View.cppのvoid NotesHzSave()の中の以下を書き換えること。
//char *gakki[26]={　と
//keychange出来る楽器の場合はchakey()も 
//直下にある　void printinkey()も書き換える。。
//Keychangeできる楽器の場合はさらにDispMeterData()のなかも書き換える
//keychange出来る楽器と出来ない楽器は、各々unsi()とunsi1()に振り分けている。
void printinkey(CDC* MemDC,CDC* pDC,int tn)//,int pos,int f)//左上の C in A
{
	char buf[30];
	int x=unX+10,y=unY+8;
	if(lastinst==OUTKEY){
		printabc(MemDC,pDC,"!2[",unX+90,unY+53);
		return;
	}
	if(DP.inst==FULLRANGE||DP.inst==KINKO||DP.inst==TOZAN||DP.inst==NANAKOU||DP.inst==NOUKAN){//なら表示せず
		return;
	}
	if(DP.inst==SINOBUE){
		tn=tn-DP.sino+8;
		sprintf(buf,"!1%s!8",abc[(tn-inst_para[DP.inst][0]+18)%12]);
		printabc(MemDC,pDC,buf,x,y);
#ifdef English 
		sprintf(buf,"!0in!4!1%s!7",abc[(DP.sino+16)%12]);
		printabc(MemDC,pDC,buf,x+20,y);
#endif
		printsinobue(MemDC,pDC,tn-inst_para[DP.inst][0]-63);
	}
	else if (checkinst(DP.inst)){
		sprintf(buf,"!1%s!8",abc[(tn-inst_para[DP.inst][0]+120)%12]);
		printabc(MemDC,pDC,buf,x,y);
	}
	else{
		if(DP.inst==OCARINA)tn=tn-DP.oca;
		else if(DP.inst==OCARINA4)tn=tn-DP.oca4;
		else if(DP.inst==TIN)tn=tn-DP.tin;
		else if(DP.inst==BANSURI)tn=tn-DP.bansuri-inst_para[DP.inst][0];
		sprintf(buf,"!1%s!6",abc[(tn+12)%12]);
		printabc(MemDC,pDC,buf,x,y);
	}
}
void Nou(CDC* MemDC,CDC* pDC,int a,int b,int x,int y,int tn,int cent);
void Nou(CDC* MemDC,CDC* pDC,int a,int b,int x,int y,int tn,int cent)
{
	char bu[50],buf[50];
	pDC->BitBlt(a,b,170,24,MemDC,x,y,SRCCOPY);
	Disp12abs(MemDC,pDC,a,b,10,10,nou[tn][0],x,y,17,7,74,-38,94,-38);
	Disp12abs(MemDC,pDC,a,b,10,10,nou[tn][1],x,y,43,7,74,-38,94,-38);
	Disp12abs(MemDC,pDC,a,b,10,10,nou[tn][2],x,y,65,7,74,-38,94,-38);
	Disp12abs(MemDC,pDC,a,b,10,10,nou[tn][3] ,x,y,86,7,74,-38,94,-38);
	Disp12abs(MemDC,pDC,a,b,10,10,nou[tn][4],x,y,106,7,74,-38,94,-38);
	Disp12abs(MemDC,pDC,a,b,8,8,nou[tn][5]  ,x,y,125,8,85,-38,105,-38);
	Disp12abs(MemDC,pDC,a,b,8,8,nou[tn][6]  ,x,y,143,8,85,-38,105,-38);
	printabc(MemDC,pDC,nouname[nou[tn][9]],a+1,b-16,SRCAND);
	if(cent<0){strcpy(buf,"-");cent=-cent;}
	else if(cent>0)strcpy(buf,"+");
	if(cent==0)strcpy(buf,"as A:440Hz");
	else{
		sprintf(bu,"%02d cent",cent);
		strcat(buf,bu);
	}
	printabc(MemDC,pDC,buf,a+100,b-16,SRCAND);
}
bool Sax(CDC* MemDC,CDC* pDC,int tn);
bool Sax(CDC* MemDC,CDC* pDC,int tn)
{
	int a=unX+3,b=unY+11,x=0,y=661;//a,bどこへ x,yどこから
	if(DP.inst==SOPRANOSAX){b=unY+1;}
	if(lastinst!=DP.inst){
		if(DP.inst==SOPRANOSAX){
			InsPict(MemDC,pDC,unX,unY,196,121,a,b+50,x,y+50,190,48);
//			pDC->BitBlt(a,b+25,65,98-25,MemDC,x,y+25,SRCCOPY);
			pDC->BitBlt(a,b+25,65,73,MemDC,x,y+25,SRCCOPY);
			pDC->BitBlt(a+126,b+40,64,10,MemDC,x+126,y,SRCCOPY);
		}
		else {//7555
			InsPict(MemDC,pDC,unX,unY,196,121,a,b+23,x,y+23,191,98-23);
			pDC->BitBlt(a+75,b,55,78,MemDC,x+75,y,SRCCOPY);
		}
	}
	Disp12abs(MemDC,pDC,a,b,9,6,sax[tn][0]  ,x,y,4,44,1,2);
	Disp12abs(MemDC,pDC,a,b,11,7,sax[tn][1],x,y,10,34,12,0);
	Disp12abs(MemDC,pDC,a,b,10,6,sax[tn][2],x,y,16,45,25,2);

	Disp12abs(MemDC,pDC,a,b,7,12,sax[tn][3],x,y,39,34,37,2);
	Disp12abs(MemDC,pDC,a,b,6,9,sax[tn][4],x,y,46,28,46,2);
	Disp12abs(MemDC,pDC,a,b,6,9,sax[tn][5],x,y,49,40,54,2);
	Disp12abs(MemDC,pDC,a,b,6,9,sax[tn][6],x,y,55,33,54,2);

	Disp12abs(MemDC,pDC,a,b,12,13,sax[tn][7],x,y,14,58,0,0);
	Disp12abs(MemDC,pDC,a,b,6,6,sax[tn][8],x,y,28,60,37,17);//37 678
	Disp12abs(MemDC,pDC,a,b,5,6,sax[tn][9],x,y,37,59,44,17);
	Disp12abs(MemDC,pDC,a,b,6,6,sax[tn][10],x,y,43,59,37,17);
	Disp12abs(MemDC,pDC,a,b,6,6,sax[tn][11],x,y,52,55,37,17);
	Disp12abs(MemDC,pDC,a,b,10,4,sax[tn][12],x,y,22,88,8,14);//572 322
	Disp12abs(MemDC,pDC,a,b,7,3,sax[tn][13],x,y,121,89,8,14);//
	Disp12abs(MemDC,pDC,a,b,7,3,sax[tn][14],x,y,131,89,8,14);//
	Disp12abs(MemDC,pDC,a,b,7,3,sax[tn][15],x,y,141,89,8,14);//
	Disp12abs(MemDC,pDC,a,b,10,5,sax[tn][16],x,y,140,81,8,14);
	Disp12abs(MemDC,pDC,a,b,9,5,sax[tn][17],x,y,154,81,8,14);
	Disp12abs(MemDC,pDC,a,b,7,7,sax[tn][18],x,y,132,71,0,10);//132,104);//132 765
	Disp12abs(MemDC,pDC,a,b,13,12,sax[tn][19],x,y,143,66,8,9);//0 671

	Disp12abs(MemDC,pDC,a,b,13,12,sax[tn][20],x,y,163,67,8,9);
	Disp12abs(MemDC,pDC,a,b,8,9,sax[tn][21],x,y,163,83,22,10);//163,115);//163 775
	Disp12abs(MemDC,pDC,a,b,8,9,sax[tn][22],x,y,169,87,28,14);//169,119);//22 670
	lastinst=DP.inst;
	return false;
}
void unsi1(CDC* MemDC,CDC* pDC,int tone,int flag)
{
	if(flag)lastinst=0;
	int tn;
	tn=tone-inst_para[DP.inst][2];
	if(!(tone>=inst_para[DP.inst][2]&&tone<=inst_para[DP.inst][3])){
		if(lastinst!=OUTKEY)pDC->FillSolidRect(unX,unY,196,121,RGB(255,255,255));
		lastinst=OUTKEY;
	}
	else if(DP.inst==TROMBONE){
		int tr,a;
		tr=tro[tn];
		int a1=unX+7,b1=unY+25,x=383,y=662;//x=430,y=662;//249,y=871;//a1,b1どこへ x,yどこから
		if(lastinst!=TROMBONE){
			InsPict(MemDC,pDC,unX,unY,196,121,a1,b1,x,y,183,77);
		}
		pDC->BitBlt(a1+65,b1+28,118,20,MemDC,x+65,y+28,SRCCOPY);
		if(tr!=1){
		pDC->FillSolidRect(a1+65,b1+28,23,20,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,SRCCOPY);
		pDC->FillSolidRect(a1+151,b1+28,31,20,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,SRCCOPY);
		pDC->FillSolidRect(a1+65,b1+28,100,5,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,SRCCOPY);
		pDC->FillSolidRect(a1+65,b1+43,100,5,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,SRCCOPY);
		pDC->BitBlt(a1+65,b1+29,110,3,MemDC,x+65,y+77,SRCCOPY);
		pDC->BitBlt(a1+65,b1+44,110,3,MemDC,x+65,y+77,SRCCOPY);
		if(tr==7)a=167;
		else if(tr==6)a=145;
		else if(tr==5)a=124;
		else if(tr==4)a=107;
		else if(tr==3)a=94;
		else if(tr==2)a=83;
		pDC->BitBlt(a1+a,b1+28,5,20,MemDC,x+65,y+28,SRCCOPY);//7 posi//dx:5
		pDC->BitBlt(a1+a+5,b1+28,178-a,5,MemDC,x+70,y+28,SRCCOPY);
		pDC->BitBlt(a1+a+5,b1+43,178-a,5,MemDC,x+70,y+28,SRCCOPY);
		}
		lastinst=TROMBONE;
	}
	else if(DP.inst==CLARINET){
		int a1=unX+3,b1=unY+38,x=191,y=661;//x=244,y=790;//a1,b1どこへ x,yどこから
		if(lastinst!=CLARINET)InsPict(MemDC,pDC,unX,unY,196,121,a1,b1,x,y,190,43);
		Disp12(MemDC,pDC,a1,b1,19,7,cla[tn][1],x,y,10,19,21,54);
		Disp12(MemDC,pDC,a1,b1,3,13,cla[tn][0],x,y,17,15,0,38);
		Disp12(MemDC,pDC,a1,b1,27,6,cla[tn][0],x,y,10,9,0,38);
		Disp12(MemDC,pDC,a1,b1,12,7,cla[tn][2],x,y,6,35,0,38);
		Disp12(MemDC,pDC,a1,b1, 9,9,cla[tn][3],x,y,20,34,0,38);
		Disp12(MemDC,pDC,a1,b1, 7,7,cla[tn][4],x,y,34,19,0,38);
		Disp12(MemDC,pDC,a1,b1,14,13,cla[tn][6],x,y,48,13,0,38);
		Disp12(MemDC,pDC,a1,b1, 7,7,cla[tn][5],x,y,49,19,0,38);
		Disp12(MemDC,pDC,a1,b1,9,20,cla[tn][8],x,y,63,11,0,38);
		Disp12(MemDC,pDC,a1,b1,6,6,cla[tn][7],x,y,63,19,0,38);
		Disp12(MemDC,pDC,a1,b1,55,5,cla[tn][9],x,y,7,29,0,38);
		Disp12(MemDC,pDC,a1,b1,20,8,cla[tn][9],x,y,62,31,0,38);
		if(cla[tn][10]==1){
			Disp12(MemDC,pDC,a1,b1,46,5,cla[tn][11],x,y,77,13,0,38);
			Disp12(MemDC,pDC,a1,b1,42,7,cla[tn][10],x,y,81,8,0,35);
		}
		else{
			Disp12(MemDC,pDC,a1,b1,42,7,cla[tn][10],x,y,81,8,0,35);
			Disp12(MemDC,pDC,a1,b1,46,5,cla[tn][11],x,y,77,13,0,38);
		}
		Disp12(MemDC,pDC,a1,b1,8,8,cla[tn][12],x,y,89,19,0,38);
		Disp12(MemDC,pDC,a1,b1,8,8,cla[tn][13],x,y,100,19,0,38);
		Disp12(MemDC,pDC,a1,b1,4,11,cla[tn][14],x,y,108,19,0,38);
		Disp12(MemDC,pDC,a1,b1,8,8,cla[tn][15],x,y,113,19,0,38);
		if(cla[tn][16]==1){
			Disp12(MemDC,pDC,a1,b1,19,11,cla[tn][17],x,y,128,20,0,25);
			Disp12(MemDC,pDC,a1,b1,9,10,cla[tn][16],x,y,122,21,0,38);
		}else{
			Disp12(MemDC,pDC,a1,b1,9,10,cla[tn][16],x,y,122,21,0,38);
			Disp12(MemDC,pDC,a1,b1,19,11,cla[tn][17],x,y,128,20,0,25);
		}
		lastinst=CLARINET;//312,712
	}
	else if(DP.inst==TRUMPET){//trumpet
		int a=unX+45,b=unY+43,x=411,y=55;//x=0,y=661;//a1,b1どこへ x,yどこから
		if(lastinst!=TRUMPET)InsPict(MemDC,pDC,unX,unY,196,121,a,b,x,y,109,52);
		Disp12abs(MemDC,pDC,a,b,21,31,pet[tn][0],x,y,13,0,75,0);
		Disp12abs(MemDC,pDC,a,b,21,31,pet[tn][1],x,y,44,0,75,0);
		Disp12abs(MemDC,pDC,a,b,21,31,pet[tn][2]+1,x,y,75,0,13,0,75,0);
		lastinst=TRUMPET;
	}
	else if(DP.inst==TENORSAX||DP.inst==SOPRANOSAX||DP.inst==ALTOSAX)Sax(MemDC,pDC,tn);
	else if(DP.inst==BHORN||DP.inst==FHORN){
		int a1=unX+56,b1=unY+13,x=567,y=657;//a1,b1どこへ x,yどこから
		if(lastinst!=BHORN)InsPict(MemDC,pDC,unX,unY,196,121,a1,b1,x,y,100,102);
		Disp12abs(MemDC,pDC,a1,b1,18,67,horn[tn][0]  ,x,y,17,0,69,0);
		Disp12abs(MemDC,pDC,a1,b1,18,67,horn[tn][1]  ,x,y,43,0,69,0);
		Disp12abs(MemDC,pDC,a1,b1,18,67,horn[tn][2]+1,x,y,69,0,17,0,69,0);
		lastinst=DP.inst;
	}
	else if(DP.inst==NOUKAN){//noukan
		int i,a=unX+15,b=unY+53,x=569,y=349;//360-11;//a,bどこへ x,yどこから
		pDC->FillSolidRect(unX,unY,196,121,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,SRCCOPY);
		for(i=0;i<36;i++){
			if(nou[i][10]==tn){
				if(nou[i][8]==4)Nou(MemDC,pDC,a,b-40,x,y,i,nou[i][7]);
				else if(nou[i][8]==3)Nou(MemDC,pDC,a,b-20,x,y,i,nou[i][7]);
				else if(nou[i][8]==2)Nou(MemDC,pDC,a,b,x,y,i,nou[i][7]);
				else if(nou[i][8]==1)Nou(MemDC,pDC,a,b+20,x,y,i,nou[i][7]);
				else if(nou[i][8]==0)Nou(MemDC,pDC,a,b+40,x,y,i,nou[i][7]);
			}
		}
		lastinst=NOUKAN;
	}
	else if(DP.inst==RECORDER){//recorder
		int a1=unX+18,b1=unY+38,x=572,y=311;//322-11;//x=193,y=744;//x=260,y=773;//a1,b1どこへ x,yどこから
		if(lastinst!=RECORDER){
			InsPict(MemDC,pDC,unX,unY,196,121,a1,b1,x,y,22,36);
			pDC->BitBlt(a1,b1+11,163,25,MemDC,x,y+11,SRCCOPY);
			pDC->BitBlt(a1+120,b1+5,43,31,MemDC,x+120,y+5,SRCCOPY);
		}
		Disp12abs(MemDC,pDC,a1,b1,8,8,rec[tn][0]  ,x,y,12,0,34,0,25,0);
		Disp12abs(MemDC,pDC,a1,b1,8,8,rec[tn][1]  ,x,y,19,19,34,0);
		Disp12abs(MemDC,pDC,a1,b1,10,10,rec[tn][2],x,y,37,18,43,0);
		Disp12abs(MemDC,pDC,a1,b1,10,10,rec[tn][3],x,y,58,18,43,0);
		Disp12abs(MemDC,pDC,a1,b1,8,8,rec[tn][4]  ,x,y,80,19,34,0);
		Disp12abs(MemDC,pDC,a1,b1,10,10,rec[tn][5],x,y,99,18,43,0);
		Disp12abs(MemDC,pDC,a1,b1,5,6,rec[tn][6]  ,x,y,123,16,54,0);
		Disp12abs(MemDC,pDC,a1,b1,7,7,rec[tn][7]  ,x,y,121,22,60,0);
		Disp12abs(MemDC,pDC,a1,b1,5,6,rec[tn][8]  ,x,y,142,19,54,0);
		Disp12abs(MemDC,pDC,a1,b1,7,7,rec[tn][9]  ,x,y,140,25,60,0);
		lastinst=RECORDER;
	}
	else if(DP.inst==OBOE){
		int a=unX+3,b=unY+43,x=190,y=750;
		if(lastinst!=OBOE){
			InsPict(MemDC,pDC,unX,unY,196,121,a,b,x,y,190,44);
			pDC->BitBlt(a+113,b+60,70,10,MemDC,x+290,y,SRCCOPY);//480,750
		}
		Disp12(MemDC,pDC,a,b,17,8,oboe[tn][0],x,y,2,4,192,0);
		Disp12(MemDC,pDC,a,b,11,16,oboe[tn][1],x,y,22,16,192,0);
		Disp12(MemDC,pDC,a,b,17,8,oboe[tn][2],x,y,16,34,192,0);
		Disp12(MemDC,pDC,a,b,6,7,oboe[tn][3],x,y,33,19,192,0);
		Disp12(MemDC,pDC,a,b,14,16,oboe[tn][4],x,y,44,15,192,0);
		Disp12(MemDC,pDC,a,b,14,16,oboe[tn][5],x,y,64,15,192,0);
		Disp12(MemDC,pDC,a,b,10,9,oboe[tn][6],x,y,79,1,192,0);
		Disp12(MemDC,pDC,a,b,8,5,oboe[tn][7],x,y,76,5,192,0);
		Disp12(MemDC,pDC,a,b,4,4,oboe[tn][7],x,y,83,7,192,0);
		Disp12(MemDC,pDC,a,b,7,8,oboe[tn][8],x,y,71,8,192,0);
		Disp12(MemDC,pDC,a,b,8,9,oboe[tn][9],x,y,78,11,192,0);
		Disp12(MemDC,pDC,a,b,17,8,oboe[tn][10],x,y,76,34,192,0);
		Disp12(MemDC,pDC,a,b,14,16,oboe[tn][11],x,y,89,16,192,0);//11
		Disp12(MemDC,pDC,a,b,14,16,oboe[tn][12],x,y,108,16,192,0);
		Disp12(MemDC,pDC,a,b,6,14,oboe[tn][13],x,y,124,18,192,0);
		Disp12(MemDC,pDC,a,b,14,16,oboe[tn][14],x,y,131,16,192,0);
		Disp12(MemDC,pDC,a,b,12,22,oboe[tn][15],x,y,148,21,192,0);//15
		Disp12(MemDC,pDC,a,b,13,23,oboe[tn][17],x,y,165,21,192,0);
		Disp12(MemDC,pDC,a,b,9,10,oboe[tn][16],x,y,160,26,192,0);
		lastinst=OBOE;
	}
	else if(DP.inst==FLUTE){
		int a=unX+4,b=unY+43,x=558,y=374;//385-11;
		if(lastinst!=FLUTE){
			InsPict(MemDC,pDC,unX,unY,196,121,a,b,x,y,188,40);
		}
		Disp12abs(MemDC,pDC,a,b,12,13,flute[tn][0],x,y,2,14,96,40);
		Disp12abs(MemDC,pDC,a,b,38,11,flute[tn][1],x,y,5,28,50,40);
		Disp12abs(MemDC,pDC,a,b,33,9,flute[tn][2],x,y,17,31,62,43);
		Disp12abs(MemDC,pDC,a,b,14,15,flute[tn][3],x,y,32,12,109,40);
		Disp12abs(MemDC,pDC,a,b,14,15,flute[tn][4],x,y,47,10,124,40);
		Disp12abs(MemDC,pDC,a,b,15,11,flute[tn][5],x,y,50,0,27,40);
		Disp12abs(MemDC,pDC,a,b, 4,13,flute[tn][5],x,y,61,11,45,40);

		Disp12abs(MemDC,pDC,a,b,16,11,flute[tn][6],x,y,84,19,139,40);
		Disp12abs(MemDC,pDC,a,b,14,15,flute[tn][7],x,y,100,12,109,40);
		Disp12abs(MemDC,pDC,a,b, 6, 7,flute[tn][8],x,y,114,19,156,40);
		Disp12abs(MemDC,pDC,a,b,14,15,flute[tn][9],x,y,121,12,109,40);
		Disp12abs(MemDC,pDC,a,b, 6, 7,flute[tn][10],x,y,135,19,156,40);
		Disp12abs(MemDC,pDC,a,b,14,15,flute[tn][11],x,y,142,12,109,40);
		Disp12abs(MemDC,pDC,a,b,11,14,flute[tn][12],x,y,161,18,163,40);
		Disp12abs(MemDC,pDC,a,b,12, 5,flute[tn][13],x,y,173,18,175,40);
		Disp12abs(MemDC,pDC,a,b,12, 9,flute[tn][14],x,y,173,23,175,45);
		lastinst=FLUTE;
	}
	printinkey(MemDC,pDC,tone);//,lastinst);
	lasttn=tone;
}
