//unsimain
#include "stdafx.h"
#include "Syaku8.h"
#include "Syaku8Doc.h"
#include "Syaku8View.h"
#include "math.h"
#include "tuner.h"
#ifdef English
char *helpst[35]={
	"choose instrument",
	"choose instrument",
	"change key",
	"change key",
	"Down one octave",
	"Down half tone (same as # key)",
	"Up half tone (same as / key)",
	"Up one octave",
	"Display data in memory (same as > key)",
	"Display data in memory (same as < key)",
	"Stop and Restart recording (same as Enter key)  shift+Enter:clear memory and restart",
	"12",
	"Clear data in memory",
	"Sound Volume for tuning",
	"Display data at cursol position ( up.down.left.right keys L.button and drag)",
	"Display Freq. at the cursol position    R.button:loaded data    Page Up and Down keys:Log. FFT",
	"18",
	"Increase Freq. of A",
	"Decrease Freq. of A",
	"Save the recorded data",
	"Load a recorded data from (s8data.txt or *.tx8)",
	"Display or undisplay the loaded wave data",
	"Decrease Reference Sound Volume value (by 1dB)",
	"Decrease Reference Sound Volume value (by 0.1dB)",
	"Increase Reference Sound Volume value (by 0.1dB)",
	"Increase Reference Sound Volume value (by 1dB)",
	"R.button:display the loaded data",
	"Drag to set the saving data range ( up.down.left.right keys L.button and drag)"
};
#else
char *helpst[35]={
	"�y��̕ύX",
	"�y��̕ύX",
	"�y��̒��̕ύX",
	"�y��̒��̕ύX",
	"�I�N�^�[�u������",
	"���������� ( # �L�[�Ɠ���)",
	"�����グ�� ( / �L�[�Ɠ���)",
	"�I�N�^�[�u�グ��",
	"�������f�[�^�\�� ( > �L�[�Ɠ���)",
	"�������f�[�^�\�� ( < �L�[�Ɠ���)",
	"���g������̒�~�ĊJ (Enter �L�[�Ɠ���)  shift + Enter:�������f�[�^�̏����ƍĊJ",
	"12",
	"�������f�[�^�̏���",
	"���q���̉���",
	"�J�[�\���ʒu�̃f�[�^�\�� ( �㉺���E�L�[�ƍ��{�^�� + drag )",
	"�J�[�\���ʒu���g���̕\��  �E�{�^��:�Ǐo�f�[�^�̕\��.��\��  PageUp Down:LogFFT�̕\���㉺",
	"18",
	"(A)�̎��g����",
	"(A)�̎��g������",
	"���g���f�[�^ or �g�`�f�[�^�̋L�^",
	"���g���f�[�^(*.tx8) or �g�`�f�[�^(s8data.txt)�̓Ǐo",
	"�Ǐo�f�[�^�̕\��.��\��",
	"dB�̊�l��1dB������",
	"dB�̊�l��0.1dB������",
	"dB�̊�l��0.1dB�グ��",
	"dB�̊�l��1dB�グ��",
	"�E�{�^��:�Ǐo�g�`�f�[�^�̕\��.��\��",//28
	"�J�[�\���ʒu�f�[�^�̕\��  DRAG�ŋL�^�͈͂̎w�� ( �㉺���E�L�[�ƍ��{�^�� + drag )",//29
};
#endif
char *abc[15]={"c","d$","d","e$","e","f","g$","g","a$","a","b$","b","c",};
extern int ct[15][2];
extern DATADP DP;
int BA[30]={
	0,18,33,49,65,80,94,111,127,139,153,169,184,206,222,239,255,//A-Q
	272,288,302,318,335,352,375,393,410,425,438};
int BAx=20,BAy=189;//675+29;
int printoneb(CDC* MemDC,CDC* pDC,char *p,int x,int y,int f=SRCCOPY);
int printoneb(CDC* MemDC,CDC* pDC,char *p,int x,int y,int f)
{
	int n,dx;//now x
	if(*p>='a'&&*p<='z')n=*p-'a';
	else if(*p>='A'&&*p<='Z') n=*p-'A';
	else if(*p=='[')n='z'-'a'+1;
	else n=0;
	dx=BA[n+1]-BA[n];
	pDC->BitBlt(x,y,dx,15,MemDC,BAx+BA[n],BAy,f);
	return dx;
}
int MA[45]={
	0,12,23,33,42,51,59,69,79,87,95,106,115,125,135,145,155,167,177,//A-S
	187,197,207,219,230,241,252,262,269,279,289,299,308,319,328,338,
	348,358,368,371,380,386,392};
int MAx=20,MAy=204;
int printonem(CDC* MemDC,CDC* pDC,char *p,int x,int y,int f=SRCCOPY);
int printonem(CDC* MemDC,CDC* pDC,char *p,int x,int y,int f)
{
	int n,dx;//now x
	if(*p>='a'&&*p<='z')n=*p-'a';
	else if(*p>='A'&&*p<='Z') n=*p-'A';
	else if(*p>='0'&&*p<='9')n=*p-'0'+27;
	else if(*p=='-')n=26;
	else if(*p=='.')n=37;
	else if(*p=='#')n=38;
	else if(*p=='$')n=39;
	else n=40;
	dx=MA[n+1]-MA[n];
	pDC->BitBlt(x,y+1,dx,14,MemDC,MAx+MA[n],MAy,f);
	return dx;
}
int SA[78]={
	0,9,15,23,31,38,43,52,59,65,73,80,85,96,105,114,120,130,137,144,152,
	160,166,178,186,193,
	201,208,214,220,226,232,238,244,250,254,259,265,269,277,283,289,295,
	302,306,311,315,321,327,335,342,349,
	354,360,366,372,378,384,390,396,402,408,
	414,420,426,434,//down up < >
	442,446,450,454,//( ) [ ]
	458,462,466,472,478,482,487,491};//: . + -��* space
//int SAx=0,SAy=662;
int SAx=20,SAy=177;//6,662
char *SAP="#/><()[]:.+-$*";

int printones(CDC* MemDC,CDC* pDC,char *p,int x,int y,int f=SRCCOPY);
int printones(CDC* MemDC,CDC* pDC,char *p,int x,int y,int f)
{
	int i,n,dx;
	char *sap;
		 if(*p>='A'&&*p<='Z')n=*p-'A';
	else if(*p>='a'&&*p<='z')n=*p-'a'+26;
	else if(*p>='0'&&*p<='9')n=*p-'0'+26+26;
	else{
		sap=SAP;//������SAP�̍Ō�ɂ�space��u���Ă���B
		for(i=0;*sap!=0;i++,sap++)if(*p==*sap)break;
		n=62+i;
	}
	dx=SA[n+1]-SA[n];
	pDC->BitBlt(x,y,dx,18,MemDC,whiteX,whiteY,f);
	pDC->BitBlt(x,y+6,dx,12,MemDC,SAx+SA[n],SAy,f);
	return dx;//x+=dx;
}
//HGP�ړ�s����
#ifdef English
void printabc(CDC* MemDC,CDC* pDC,char *p,int x,int y,int f)
{
	int dx,pf=0;//now x//
	
	while(*p!=0){
		if(*p=='!'){
			p++;p++;
			if(*(p-1)=='0')pf=0;//small size
			else if(*(p-1)=='1')pf=1;//middle size
			else if(*(p-1)=='2')pf=2;//big size
			else if(*(p-1)<='9'&&*(p-1)>'2'){
				if(f==SRCCOPY)
					pDC->FillSolidRect(x,y,(*(p-1)-'2')*2,15,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,f);
				else pDC->StretchBlt(x,y,(*(p-1)-'2')*2,15,MemDC,whiteX,whiteY,1,1,f);
				x+=(*(p-1)-'2')*2;
			}
			else if(*(p-1)<='z'&&*(p-1)>='a'){
				if(f==SRCCOPY)
					pDC->FillSolidRect(x,y,*(p-1)-'a'+1,15,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,f);
				else pDC->StretchBlt(x,y,*(p-1)-'a'+1,15,MemDC,whiteX,whiteY,1,1,f);
				x+=*(p-1)-'a'+1;
			}
			continue;
		}
		if(pf==0)dx=printones(MemDC,pDC,p,x,y,f);
		else if(pf==1)dx=printonem(MemDC,pDC,p,x,y,f);
		else dx=printoneb(MemDC,pDC,p,x,y,f);
		p++;
		x+=dx;
	}
}

void DispInstName(CDC* MemDC,CDC* pDC)
{
	int xx;
	char *p,buf[50];//,*abc[15]={"a","b$","b","c","d$","d","e$","e","f","g$","g","a$","a"};
	pDC->FillSolidRect(nameX,nameY,196,34,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,SRCCOPY);
	if(DP.inst==SINOBUE){
		if(DP.sino==1||DP.sino==6||DP.sino==10||DP.sino==11){
			if(DP.sino>9)sprintf(buf,"!2sinobue!5!1%d!0ponchousi",DP.sino);
			else sprintf(buf,"!2sinobue!7!1%d!5!0ponchousi",DP.sino);
		}
		if(DP.sino==2||DP.sino==4||DP.sino==5||DP.sino==7||DP.sino==8||DP.sino==9||DP.sino==12){
			if(DP.sino>9)sprintf(buf,"!2sinobue!5!1%d!0honchousi",DP.sino);
			else sprintf(buf,"!2sinobue!7!1%d!5!0honchousi",DP.sino);
		}
		if(DP.sino==3||DP.sino==13){
			if(DP.sino>9)sprintf(buf,"!2sinobue!5!1%d!0bonchousi",DP.sino);
			else  sprintf(buf,"!2sinobue!7!1%d!5!0bonchousi",DP.sino);
		}
		p=buf;xx=nameX+8;//562;
	}
	else if(DP.inst==KINKO||DP.inst==TOZAN||DP.inst==NANAKOU){
		if(DP.inst==KINKO)	sprintf(buf,"!2kinko!e!0shaku8 !1%d!0sun!6!1%s",DP.sn,abc[(32-DP.sn)%12]);
		else if(DP.inst==TOZAN)sprintf(buf,"!2tozan!0shaku8 !1%d!0sun!6!1%s",DP.sn,abc[(32-DP.sn)%12]);
		else sprintf(buf,"!17 holes!0shaku8 !1%d!0sun!6!1%s",DP.sn,abc[(32-DP.sn)%12]);
		p=buf;xx=nameX+8;//562;
	}else if(DP.inst==OCARINA4){
		strcpy(buf,"!04!5holes!6!2ocarina!6!1");
		strcat(buf,abc[(DP.oca4+24)%12]);
		p=buf;xx=nameX+5;
	}else if(DP.inst==OCARINA){
		strcpy(buf,"!2ocarina!9!1");
		strcat(buf,abc[(DP.oca+24)%12]);
		p=buf;xx=nameX+26;//580;
	}else if(DP.inst==BANSURI){
		strcpy(buf,"!2bansuri!9!1");
		strcat(buf,abc[(DP.bansuri+24+5)%12]);
		p=buf;xx=nameX+26;//580;
	}else if(DP.inst==TIN){
		strcpy(buf,"!2tin!3whistle!6!1");
		strcat(buf,abc[(DP.tin+21+3)%12]);
		p=buf;xx=nameX+7;//580;
	}
	else if(DP.inst==NOUKAN){p="one !2noukan";xx=nameX+590-554;}
	else if(DP.inst==FLUTE){p="!2flute!0  !1C";xx=nameX+615-554;}//C
	else if(DP.inst==CLARINET){p="!2clarinet!0  !1B$";xx=nameX+590-554;}//Bb
	else if(DP.inst==TRUMPET){p="!2trumpet!0  !1B$";xx=nameX+593-554;}//Bb
	else if(DP.inst==SOPRANOSAX){p="!2sopranosax!0  !1B$";xx=nameX+4;}//Bb
	else if(DP.inst==ALTOSAX){p="!2altosax!0  !1E$";xx=nameX+35;}//Eb
	else if(DP.inst==TENORSAX){p="!2tenorsax!0  !1B$";xx=nameX+30;}//Bb
	else if(DP.inst==TROMBONE){p="!2trombone!0  !1C";xx=nameX+28;}//C
	else if(DP.inst==FHORN){p="!2horn!0  !1F";xx=nameX+615-554;}
	else if(DP.inst==BHORN){p="!2horn!0  !1B$";xx=nameX+615-554;}
	else if(DP.inst==OBOE){p="!2oboe!0  !1C";xx=nameX+615-554;}//C
	else if(DP.inst==RECORDER){
		strcpy(buf,"!2recorder!9!1C");
		p=buf;xx=nameX+580-554;
	}
	else if(DP.inst==FULLRANGE){
		sprintf(buf,"!2CDE!c!0DoReMi  in !1%s",abc[(DP.voca+12)%12]);
		p=buf;xx=nameX+600-554;
	}
	else return;
	printabc(MemDC,pDC,p,xx,nameY+10);
}
#else
short kan[53]={
	0,16,28,46,62,75, 87,100,113,133,
	146,161,170,182,199,217,231,247,261,278,
	296,314,328,347,358,374,388,401,414,430,446,464,475,489,501,//501�͕��F����͎g���Ȃ�
	0,20,40,62,86,103,125,146,169,187,209,230,248,270,291,312,333//
};

int KAx=20,KAy=218,kanx=18+54,kany=272,kanakazu=34;//32;
char *KAP="�I�H�G�A�J�N�L�R�T�\�X�g�b�e�i�l�z�t�{�y�o���������������[�_�v�m�C�B���ڐ����J�ՌÓs�R�\�ǓV�����E��";//���͎g��Ȃ�����
int Kax=19,Kay=237;
char *Kanp="�ʒu�͈͉���y��������E�����㉺���͋L�^�����ؑ֐ώZ���q�I��ڐ���\�����g����~���ԍČ��ݎ�Ǐo�ύX���������J�`���łƂɂ̂ւ�����[�C�I�@�J�L�N�\�^�f�b�t�u�{�������������ʉ�����S�{�h���~����O�l�ܘZ�������D�[�R�������������w�_��l";
//int KAx=20,KAy=218,kanx=18+54,kany=272,kanakazu=32;//18 272
//char *KAP="dammy";//���͎g��Ȃ�����
//int Kax=19,Kay=237;
//char *Kanp="dammy";
int printonekan(CDC* MemDC,CDC* pDC,char *p,int x,int y,int pf,int f=SRCCOPY);
int printonekan(CDC* MemDC,CDC* pDC,char *p,int x,int y,int pf,int f)
{
	int i,dx;
	char *kap;
	if(pf==0)kap=Kanp;
	else kap=KAP;//������SAP�̍Ō�ɂ�space��u���Ă���B
	for(i=0;*kap!=0;i++,kap+=2)if(*p==*kap&&*(p+1)==*(kap+1))break;
	if(pf==0){//����������
		pDC->BitBlt(x,y+4,12,11,MemDC,Kax+13*(i%39),Kay+12*(i/39),f);
		return 12;
	}
	else{//�啶������
		dx=kan[i+1]-kan[i];
		if(i<kanakazu)pDC->BitBlt(x,y,dx,19,MemDC,KAx+kan[i],KAy,f);
		else pDC->BitBlt(x,y-4,dx,24,MemDC,kanx+kan[i],kany,f);
		if(f==SRCCOPY)
			pDC->FillSolidRect(x+dx,y-2,3,20,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,f);
		else pDC->StretchBlt(x+dx,y-2,3,20,MemDC,whiteX,whiteY,1,1,f);
		return dx+3;//x+=dx;
	}
}
void printabc(CDC* MemDC,CDC* pDC,char *p,int x,int y,int f)
{
	int dx,pf=0;//now x//
	
	while(*p!=0){
		if(*p=='!'){
			p++;p++;
			if(*(p-1)=='0')pf=0;//small size
			else if(*(p-1)=='1')pf=1;//middle size
			else if(*(p-1)=='2')pf=2;//big size
			else if(*(p-1)<='9'&&*(p-1)>'2'){
				if(f==SRCCOPY)
					pDC->FillSolidRect(x,y,(*(p-1)-'2')*2,15,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,f);
				else pDC->StretchBlt(x,y,(*(p-1)-'2')*2,15,MemDC,whiteX,whiteY,1,1,f);
				x+=(*(p-1)-'2')*2;
			}
			else if(*(p-1)<='z'&&*(p-1)>='a'){
				if(f==SRCCOPY)
					pDC->FillSolidRect(x,y,*(p-1)-'a'+1,15,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,f);
				else pDC->StretchBlt(x,y,*(p-1)-'a'+1,15,MemDC,whiteX,whiteY,1,1,f);
				x+=*(p-1)-'a'+1;
			}
			continue;
		}
		if(_ismbblead(*p)){dx=printonekan(MemDC,pDC,p,x,y,pf,f);p++;}
		else if(pf==0)dx=printones(MemDC,pDC,p,x,y,f);
		else if(pf==1)dx=printonem(MemDC,pDC,p,x,y,f);
		else dx=printoneb(MemDC,pDC,p,x,y,f);
		p++;
		x+=dx;
	}
}
void DispInstName(CDC* MemDC,CDC* pDC)
{
	int xx;
	char *p,buf[50];//,*abc[15]={"a","b$","b","c","d$","d","e$","e","f","g$","g","a$","a"};
	pDC->FillSolidRect(nameX,nameY,196,34,RGB(255,255,255));//MemDC,whiteX,whiteY,1,1,SRCCOPY);
	if(DP.inst==SINOBUE){
		sprintf(buf,"!2�J!9!1%d!0�{���q!4!1-!4!1%s!4",DP.sino,abc[(DP.sino+16)%12]);
		p=buf;xx=nameX+36;//600-554-10;
	}
	else if(DP.inst==KINKO||DP.inst==TOZAN||DP.inst==NANAKOU){
		if(DP.inst==KINKO)	sprintf(buf,"!2�ՌÎڔ�!8!1%d%d��!6%s",DP.sn/10,DP.sn%10,abc[(32-DP.sn)%12]);
		else if(DP.inst==TOZAN)sprintf(buf,"!2�s�R�ڔ�!9!1%d%d��!6%s",DP.sn/10,DP.sn%10,abc[(32-DP.sn)%12]);
		else sprintf(buf,"!2���E�ڔ�!9!1%d%d��!6%s",DP.sn/10,DP.sn%10,abc[(32-DP.sn)%12]);
		p=buf;xx=nameX+565-554;
	}
	else if(DP.inst==OCARINA4){
		strcpy(buf,"!14!2�E!4�I�J���i!9!1");
		strcat(buf,abc[(DP.oca4+24)%12]);
		p=buf;xx=nameX+30;
	}
	else if(DP.inst==OCARINA){
		strcpy(buf,"!2�I�J���i!9!1");
		strcat(buf,abc[(DP.oca+24)%12]);
		p=buf;xx=nameX+610-554;
	}else if(DP.inst==TIN){
		strcpy(buf,"!2�e�B���z�C�b�X��!9!1");
		strcat(buf,abc[(DP.tin+24)%12]);
		p=buf;xx=nameX+15;//580;
	}else if(DP.inst==BANSURI){
		strcpy(buf,"!2�o���X��!9!1");
		strcat(buf,abc[(DP.bansuri+24+5)%12]);
		p=buf;xx=nameX+56;//580;
	}
	else if(DP.inst==NOUKAN){p="�R��������������!2�\��";xx=nameX+580-554;}
	else if(DP.inst==FLUTE){p="!2�t���[�g!0  !1C";xx=nameX+60;}
	else if(DP.inst==CLARINET){p="!2�N�����l�b�g!0  !1B$";xx=nameX+50;}
	else if(DP.inst==TRUMPET){p="!2�g�����y�b�g!0  !1B$";xx=nameX+50;}
	else if(DP.inst==SOPRANOSAX){p="!2�\�v���m�T�b�N�X!0  !1B$";xx=nameX+20;}
	else if(DP.inst==ALTOSAX){p="!2�A���g�T�b�N�X!0  !1E$";xx=nameX+25;}
	else if(DP.inst==TENORSAX){p="!2�e�i�[�T�b�N�X!0  !1B$";xx=nameX+25;}
	else if(DP.inst==TROMBONE){p="!2�g�����{�[��!0  !1C";xx=nameX+45;}
	else if(DP.inst==FHORN){p="!2�z����!0 in !1F";xx=nameX+55;}
	else if(DP.inst==BHORN){p="!2�z����!0 in !1B$";xx=nameX+55;}
	else if(DP.inst==OBOE){p="!2�I�[�{�G!0  !1C";xx=nameX+55;}
	else if(DP.inst==RECORDER){
		strcpy(buf,"!2���R�[�_�[!9!1C");
		p=buf;xx=nameX+610-554;
	}
	else if(DP.inst==FULLRANGE){
		sprintf(buf,"!2CDE!0�h���~  in !1%s",abc[(DP.voca+26)%12]);
		p=buf;xx=nameX+600-554;
	}
	else return;
	printabc(MemDC,pDC,p,xx,nameY+10);
}
#endif
