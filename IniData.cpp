#include "stdafx.h"
#include "Syaku8.h"
#include "Syaku8Doc.h"
#include "Syaku8View.h"
//#include "SaveData.h"
#include "tuner.h"

extern DATADP DP;
extern char curdir[];
int paran=27;
char *ptext[]={
	"Tuning fork pitch(CDEFGABC...);",
//	"sound type:",
	"instrument:",
	"key of bamboo S8(11-32):",
	"key of sinobue(1-13):",
	"key of whistle(C-G):",
	"key of ocarina(GÅ|G):",
	"key of 4hole ocarina(G-G):",
	"key of bansuri(C-Bb):",
	"key of vocal(GÅ|G):",
	"Wave(11/22/44ms) FFT(2.7/5.4hz) Notes-cent(0-8):",
	"CDE/Do Re Mi:",
	"Zone Cut Filter 1 Lower Limit(0-5000):",
	"Zone Cut Filter 1 Upper Limit(0-5000):",
	"Zone Cut Filter 2 Lower Limit(0-5000):",
	"Zone Cut Filter 2 Upper Limit(0-5000):",
	"FFT peak cutting Level(2-90):",
	"speed:",
	"Pitch of A(375-470):",
	"level of tuning(0-3):",
	"reference of dB(0-200):",
	"temporizing Hz amending fraction*10000(9900-11000):",
	"reference of FFT dB(0-300):",
	"Junsei(0-1):",
	"Winx1:",
	"Winy1:",
	"Winx2:",
	"Winy2:",
};
int *ppara[]={&DP.fork,&DP.inst,&DP.sn,&DP.sino,
		&DP.tin,&DP.oca,&DP.oca4,&DP.bansuri,&DP.voca,
		&DP.mode,&DP.cdedore,&DP.low1,&DP.high1,&DP.low2,
		&DP.high2,&DP.peaklevel,&DP.speed,&DP.A440,&DP.blue,
		&DP.dBx10,&DP.hzcal,&DP.logref,&DP.juns8,&DP.winx1,&DP.winy1,&DP.winx2,&DP.winy2};

//int defau[]={69,0,18,8,6,5,5,5,5,16,0,0,0,0,0,20,2,440,0,1000,10000,150,1};
int defau[]={69,0,18,8,6,5,5,5,5,16,0,0,0,0,0,20,2,440,0,1000,10000,150,1,10,10,780,590};

void SetIniStr(char *str,char *buf,int n){
	int i;
	strcpy(str,&buf[n]);
	for(i=0;str[i]!='\n';)i++;
	str[i]=0;
}

bool readini()
{
	int i;
	char buf[300],buf1[300];
	CStdioFile ff;
	SetCurrentDirectory(curdir);
	if(!ff.Open("s8tuner.ini",CFile::modeRead|CFile::typeText))
	{
		ff.Open("s8tuner.ini",CFile::modeCreate|
				CFile::modeWrite|CFile::modeRead|CFile::typeText);
		for(i=0;i<paran;i++){//writeini
			*ppara[i]=defau[i];
			strcpy(buf,ptext[i]);
			sprintf(buf1,"%d\n",*ppara[i]);
			strcat(buf,buf1);
			ff.WriteString(buf);
		}
		ff.Abort();
		return false;
	}
	else{
		while(ff.ReadString(buf,299)){
			for(i=0;i<paran;i++){
				if(strstr(buf,ptext[i])){
					sscanf(&buf[strlen(ptext[i])],"%d\n",ppara[i]);
				}
			}
		}
		ff.Abort();
		return true;
	}
}
void writeini()
{
	CStdioFile ff;
	char buf[300],buf1[300];
	int i;
	ff.Open("s8tuner.ini",CFile::modeCreate|
				CFile::modeWrite|CFile::modeRead|CFile::typeText);
	for(i=0;i<paran;i++){//writeini
		strcpy(buf,ptext[i]);
		sprintf(buf1,"%d\n",*ppara[i]);
		strcat(buf,buf1);
		ff.WriteString(buf);
	}
	ff.Abort();
}