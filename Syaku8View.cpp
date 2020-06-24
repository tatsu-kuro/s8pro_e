// Syaku8View.cpp : CSyaku8View クラスの動作の定義を行います。
//1999 11 4
#include "stdafx.h"
#include "Syaku8.h"
#include "Syaku8Doc.h"
#include "Syaku8View.h"
#include "SaveData.h"
#include <math.h>
#include <mmsystem.h>
#include "tuner.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
////////
#ifdef English
#define S8Title "Auto Tuner with the Fingering charts  Version 3.08 / 2019.03.17"
#define Set_name "Set wave name !"
#define Over_write "Overwrite OK?"
#define Unusable_name "Set another name !"
#define Set_area "Set the recording area by drag !"
#define Delete_ok "Erase OK ?"
#define To_Recording "The sound for calibration seems not to be detected.\nGoto to Recording Control and change the input sourse.\nThen re_check the sound card"
//#define Calibration "If the red needle meter doesn't indicates the center,\npush OK button to calibrate."
#else
#define S8Title "尺八運指チューナー  Version 3.08 / 2019.03.17"
#define Set_name "名前を入力してください !"
#define Over_write "上書きして良いですか ?"
#define Unusable_name "他の名前を使ってください !"
#define Set_area "ドラッグ操作で記録範囲を指定してください ！"
#define Delete_ok "削除して良いですか ?"
#define To_Recording "校正音がモニターできてないようです。録音コントロールなどを変更し校正音を拾える状態にして\n再びサウンドカードチェックを実行してください。"
//#define Calibration "赤の針メータが正中からずれている場合は、\nOKボタンを押して校正してください。"
#endif
#define SRS 5.38//,21.52};//
#define NNN 4096//,1024};//fft number of data
#define DMAX 512//,128};
extern int inst_para[30][10];
extern char* helpst[35];
extern HWAVEIN			hWave;
extern BUFTYPE			*wavebuf;
extern LPWAVEHDR		wh[MAX_BUFFERS];
extern bool			bWaveOpened;
int fftxf=0,fftxy,fftpeakx;
int mycheck=0;//'C'キーで1->2->0と巡回する。debug用
//int mycheckint;//
#define TONE1 37//51;//表示最低周波数
#define TONE2 110//103;//98;//最高周波数
#define N_LINES 9//ずれ表示の行数
const double SENT50=1.0293;
const double R12=1.05946309;
const double PAI=3.141592653589793238;
double Amp[4100],AmpdB[4100],sint[4100],cost[4100];
void MakeWave(double f0,int vol);
static unsigned char snddata[80000+50];
int ct[15][2]={
	0,0, 1,1, 1,0, 2,0, 3,1, 3,0, 4,1, 4,0,	5,0, 6,1, 6,0, 0,1,	0,0,
};
//  nn,x y dx dy    ,on(POI),off(PO),dammy
//  nn,x y dx dy    ,back(P),cu(x y dx dy)  ,cur2(x y),!x,dispFLAG,
//15カーソルのx値
int ci,ci_end=26;//28;//ci<1000
int comt[30][17]={//18 124
 3,554,485,48,22,554,485,20,32, 0, 0,  0,  0,  0,MHB|ROT|INS,0,LEF|UPP|ORG,//楽器
 4,602,485,47,22,602,485,68,32,0, 0,  0,  0,  0,MHB|ROT|INS,0,LEF|UPP|ORG,//楽器
 1,655,485,48,22,655,485,115,32, 0, 0, 0,0,0,ROT|INS,0,LEF|TEN|DOW|ORG,//楽器の調
 2,703,485,47,22,703,485,163,32,0,0,0,0,0,ROT|INS,0,LEF|TEN|DOW|ORG,//楽器の調
11,605,292-14,37,24,605,292-14,260,77,0,0,0,0,  0,ROT|HER|CDE,0,LEF|DOW|ORG,//音程
12,642,292-14,36,24,642,292-14,297,77,0,0,0,0,0,ROT|HER|CDE,0,LEF|DOW|ORG|TEN,//音程
13,678,292-14,36,24,678,292-14,333,77,0,0,0,0,0,ROT|HER|CDE,0,LEF|DOW|ORG|TEN,//音程
14,714,292-14,36,24,714,292-14,369,77,0,0,0,0,0,ROT|HER|CDE,0,LEF|DOW|ORG,//音程
15,605, 205-20,48,24,605,205-20,19,54, 0, 0,  0,  0,  0,0,0,LEF|DOW|FST|ORG,//dispmemory
16,653, 205-20,48,24,653,205-20,67,54, 0, 0,  0,  0,  0,0,0,LEF|DOW|FST|ORG,//dispmemory
17,701, 205-20,49,24,701,205-20,115,54, 0, 0,  0,  0,  0,0,0,LEF|UPP|NEX,//表示停止
17,701, 205-20,49,24,257, 31,306,31, 0, 0,  0,  0,  0,0,0,0,//表示停止
18,554, 206-20,47,23,554,206-20,211,32,0,0,0,0,0,MHB,0,LEF|UPP|ORG,//clear memory
53,554,264-16,196,22,554,264-16,209,101,30,22,241,101,606,0,0,DOW|LEF|UPP|SLD,//音量
91,550,86,203,94, 0,  0,  0,  0, 0, 0, 0,   0,  0,0,0,LEF|DOW|MOV|FST,//dispmemory
92,17,15,510,237, 0,  0,  0,  0, 0, 0, 0,   0,  0,0,0,DOU|LEF|DOW|FST|MOV,//周波数fft
93,17,17,510,235, 0,  0,  0,  0, 0, 0, 0,   0,  0,0,0,RIG|DOW,//disploaddata
105,308,424,19,20,308,424,299,459, 0, 0, 0,   0, 0,A44|HER|ROT,0,    LEF|DOW|FST|ORG,//pitch of A
106,217,424,19,20,217,424,299,478, 0, 0, 0,   0, 0,A44|HER|ROT,0,    LEF|DOW|FST|ORG,
110,553,234-18,95,24,553,234-18,19,100,0,0,0,0,0,  0,0,LEF|UPP|ORG,//書き込み
111,652,234-18,76,24,652,234-18,583,49,0,0,0,0,0,MHB|INS|ROT|A44|CDE|HER,0,LEF|UPP|ORG,//読み込み
112,727,234-18,24,24,727,234-18,659,49,0,0,0,0,0,0,0,LEF|UPP|ORG,//表示非表示
122,553,16,25,17,553,16,583,18, 0, 0, 0,   0, 0,ISV,0,    LEF|DOW|FST|ORG,//dec. referrence Sound V.
124,553,32,25,14,553,32,583,34, 0, 0, 0,   0, 0,ISV,0,    LEF|DOW|FST|ORG,//dec. referrence Sound V.
125,553,45,25,14,553,45,608,18, 0, 0, 0,   0, 0,ISV,0,    LEF|DOW|FST|ORG,//inc. referrence Sound V.
123,553,58,25,17,553,58,608,31, 0, 0, 0,   0, 0,ISV,0,    LEF|DOW|FST|ORG,//inc. referrence Sound V.
OWA,  0,  0, 0, 0,  0,  0,  0,  0, 0, 0,  0,  0,  0,0,0,	0,
};
DATADP DP;
struct WAVE{
	short dB[256];
	POINT xy[256];
	bool  f;
	double  hz;
	char  tone;
	short cent;
	double  volt;
	short overflow;
	char  mode;
#if CHECK!=0
	int chk[10];
#endif
};
WAVE wa[SM+20];//98
POINT PoTemp[256];//,oldPoTemp[256];
//static UINT nTimerId;
//static UINT nMs;
int Lt,SaveStart,waveNow,waveCnt;
char curdir[300];
POINT xynow[256];
int Keys[14];
CPen *RedPen,*Red2Pen,*NotPen;
double tone[TONE2+2+2];//
double dbxn[540],dbyn[540],dtx[540],dty[540];
IMPLEMENT_DYNCREATE(CSyaku8View, CView)
BEGIN_MESSAGE_MAP(CSyaku8View, CView)
	//{{AFX_MSG_MAP(CSyaku8View)
	ON_COMMAND(IDC_UP, OnUp)
	ON_COMMAND(IDC_SITA, OnSita)
	ON_COMMAND(IDC_MIGI, OnMigi)
	ON_COMMAND(IDC_HIDARI, OnHidari)
	ON_COMMAND(ID_RETURN, OnReturn)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_SHIFTRET, OnShiftret)
	ON_COMMAND(ID_CDEF, OnCdef)
	ON_UPDATE_COMMAND_UI(ID_CDEF, OnUpdateCdef)
	ON_COMMAND(ID_DORE, OnDore)
	ON_UPDATE_COMMAND_UI(ID_DORE, OnUpdateDore)
	ON_COMMAND(IDC_FFT1, OnFft1)
	ON_COMMAND(IDC_FFT2, OnFft2)
	ON_UPDATE_COMMAND_UI(IDC_FFT2, OnUpdateFft2)
	ON_UPDATE_COMMAND_UI(IDC_FFT1, OnUpdateFft1)
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDC_A440, OnA440)
	ON_UPDATE_COMMAND_UI(IDC_A440, OnUpdateA440)
	ON_COMMAND(IDC_FFT0, OnFft0)
	ON_UPDATE_COMMAND_UI(IDC_FFT0, OnUpdateFft0)
	ON_COMMAND(IDC_2700, On2700)
	ON_UPDATE_COMMAND_UI(IDC_2700, OnUpdate2700)
	ON_COMMAND(IDC_5400, On5400)
	ON_UPDATE_COMMAND_UI(IDC_5400, OnUpdate5400)
	ON_COMMAND(IDC_W0, OnW0)
	ON_UPDATE_COMMAND_UI(IDC_W0, OnUpdateW0)
	ON_COMMAND(IDC_W1, OnW1)
	ON_UPDATE_COMMAND_UI(IDC_W1, OnUpdateW1)
	ON_COMMAND(IDC_W2, OnW2)
	ON_UPDATE_COMMAND_UI(IDC_W2, OnUpdateW2)
	ON_COMMAND(IDC_20SNT, On20snt)
	ON_UPDATE_COMMAND_UI(IDC_20SNT, OnUpdate20snt)
	ON_COMMAND(IDC_30SNT, On30snt)
	ON_UPDATE_COMMAND_UI(IDC_30SNT, OnUpdate30snt)
	ON_COMMAND(IDC_10SNT, On10snt)
	ON_UPDATE_COMMAND_UI(IDC_10SNT, OnUpdate10snt)
	ON_COMMAND(IDC_NOTESHZ, OnNoteshz)
	ON_UPDATE_COMMAND_UI(IDC_NOTESHZ, OnUpdateNoteshz)
	ON_COMMAND(IDC_altosax, Onaltosax)
	ON_UPDATE_COMMAND_UI(IDC_altosax, OnUpdatealtosax)
	ON_COMMAND(IDC_clarinet, Onclarinet)
	ON_UPDATE_COMMAND_UI(IDC_clarinet, OnUpdateclarinet)
	ON_COMMAND(IDC_flute, Onflute)
	ON_UPDATE_COMMAND_UI(IDC_flute, OnUpdateflute)
	ON_COMMAND(IDC_fullrange, Onfullrange)
	ON_UPDATE_COMMAND_UI(IDC_fullrange, OnUpdatefullrange)
	ON_COMMAND(IDC_horn, Onhorn)
	ON_UPDATE_COMMAND_UI(IDC_horn, OnUpdatehorn)
	ON_COMMAND(IDC_kinko, Onkinko)
	ON_UPDATE_COMMAND_UI(IDC_kinko, OnUpdatekinko)
	ON_COMMAND(IDC_ocarina, Onocarina)
	ON_UPDATE_COMMAND_UI(IDC_ocarina, OnUpdateocarina)
	ON_COMMAND(IDC_recorder, Onrecorder)
	ON_UPDATE_COMMAND_UI(IDC_recorder, OnUpdaterecorder)
	ON_COMMAND(IDC_sinobue, Onsinobue)
	ON_UPDATE_COMMAND_UI(IDC_sinobue, OnUpdatesinobue)
	ON_COMMAND(IDC_tozan, Ontozan)
	ON_UPDATE_COMMAND_UI(IDC_tozan, OnUpdatetozan)
	ON_COMMAND(IDC_trombone, Ontrombone)
	ON_UPDATE_COMMAND_UI(IDC_trombone, OnUpdatetrombone)
	ON_COMMAND(IDC_trumpet, Ontrumpet)
	ON_UPDATE_COMMAND_UI(IDC_trumpet, OnUpdatetrumpet)
	ON_COMMAND(IDC_tenorsax, Ontenorsax)
	ON_UPDATE_COMMAND_UI(IDC_tenorsax, OnUpdatetenorsax)
	ON_COMMAND(IDC_sopranosax, Onsopranosax)
	ON_UPDATE_COMMAND_UI(IDC_sopranosax, OnUpdatesopranosax)
	ON_COMMAND(IDC_bhorn, Onbhorn)
	ON_UPDATE_COMMAND_UI(IDC_bhorn, OnUpdatebhorn)
	ON_COMMAND(IDC_noukan, Onnoukan)
	ON_UPDATE_COMMAND_UI(IDC_noukan, OnUpdatenoukan)
	ON_COMMAND(IDC_00SNT, On00snt)
	ON_UPDATE_COMMAND_UI(IDC_00SNT, OnUpdate00snt)
	ON_COMMAND(IDC_10800, On10800)
	ON_UPDATE_COMMAND_UI(IDC_10800, OnUpdate10800)
	ON_COMMAND(IDC_PAGEDOWN, OnPagedown)
	ON_COMMAND(IDC_PAGEUP, OnPageup)
	ON_COMMAND(IDC_SNDCARD, OnSndcard)
	ON_COMMAND(IDC_just, Onjust)
	ON_UPDATE_COMMAND_UI(IDC_just, OnUpdatejust)
	ON_COMMAND(IDC_2700LOG, On2700log)
	ON_UPDATE_COMMAND_UI(IDC_2700LOG, OnUpdate2700log)
	ON_COMMAND(IDC_5400LOG, On5400log)
	ON_UPDATE_COMMAND_UI(IDC_5400LOG, OnUpdate5400log)
	ON_COMMAND(IDC_10800LOG, On10800log)
	ON_UPDATE_COMMAND_UI(IDC_10800LOG, OnUpdate10800log)
	ON_COMMAND(IDC_oboe, Onoboe)
	ON_UPDATE_COMMAND_UI(IDC_oboe, OnUpdateoboe)
	ON_COMMAND(IDC_S, OnS)
	ON_COMMAND(IDC_JUNS8, OnJuns8)
	ON_UPDATE_COMMAND_UI(IDC_JUNS8, OnUpdateJuns8)
	ON_COMMAND(IDC_C, OnC)
	ON_COMMAND(IDC_NOTESHZLIMIT, OnNoteshzlimit)
	ON_UPDATE_COMMAND_UI(IDC_NOTESHZLIMIT, OnUpdateNoteshzlimit)
	ON_COMMAND(IDC_tin, Ontin)
	ON_UPDATE_COMMAND_UI(IDC_tin, OnUpdatetin)
	ON_COMMAND(IDC_ocarina4, Onocarina4)
	ON_UPDATE_COMMAND_UI(IDC_ocarina4, OnUpdateocarina4)
	ON_COMMAND(IDC_bansuri, Onbansuri)
	ON_UPDATE_COMMAND_UI(IDC_bansuri, OnUpdatebansuri)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyaku8View クラスの構築/消滅
DWORD grayRGB;
void SetgrayRGB(CDC *pDC,CBitmap *bit)//システムのボタンの背景色をセットする。
{
	int x,y;
	CDC MemDC;
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(bit);
	for(x=0;x<800;x++){
		for(y=0;y<600;y++){
			if(RGB(0,0,255)==MemDC.GetPixel(x,y))
				MemDC.SetPixel(x,y,grayRGB);
		}
	}
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}
CSyaku8View::CSyaku8View()
{
//	m_bmp.LoadBitmap(IDB_FRAME);
}

CSyaku8View::~CSyaku8View()
{
	m_bmp.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CSyaku8View クラスの描画
void CSyaku8View::OnDraw(CDC* pDC)
{
	CSyaku8Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	CDC MemDC;
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	DispIroiro(&MemDC,pDC,ALL);
	DispMeterData(&MemDC,pDC);
	disp1wave(&MemDC,pDC,1);
	AfxGetMainWnd()->SetWindowText(S8Title);
	MemDC.SelectObject(pOldBmp);
}

/////////////////////////////////////////////////////////////////////////////
// CSyaku8View クラスの診断

#ifdef _DEBUG
void CSyaku8View::AssertValid() const
{
	CView::AssertValid();
}

void CSyaku8View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSyaku8Doc* CSyaku8View::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSyaku8Doc)));
	return (CSyaku8Doc*)m_pDocument;
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSyaku8View クラスのメッセージ ハンドラ

void CSyaku8View::Butt(CDC* MemDC,CDC* pDC,int i,int flag)
{
	int com=comt[ci=i][16];
	if(com&DOW)DoCom(MemDC,pDC,ci,flag);
	if(com&DOU)DoCom(MemDC,pDC,ci,flag);
	if(com&SLD)Dispslide(MemDC,pDC,ci);
	if(com&ORG||com&NEX){
		Dispbutton(MemDC,pDC,ci,0);
	}
	DP.bc=0;
}

int Checkcom(CPoint posi,int cur)
{
	int i;
	for(i=0;comt[i][0]!=OWA;i++){
		if(posi.x>=comt[i][1]&&
		(posi.x<=comt[i][1]+comt[i][3])&&
		posi.y>=comt[i][2]&&
		(posi.y<=comt[i][2]+comt[i][4])&&
		(comt[i][16]&cur)&&
		!(comt[i][16]&UDO))break;
	}
	comt[i][15]=posi.x*1000+posi.y;
	return i;
}
int Checkcom1(CPoint posi)
{
	int i;
	for(i=0;comt[i][0]!=OWA;i++){
		if(posi.x>=comt[i][1]&&
		(posi.x<=comt[i][1]+comt[i][3])&&
		posi.y>=comt[i][2]&&
		(posi.y<=comt[i][2]+comt[i][4]))break;
	}
	return i;
}
int Checkpos(CPoint posi,int i)
{
	if(posi.x>=comt[i][1]&&
		(posi.x<=comt[i][1]+comt[i][3])&&
		posi.y>=comt[i][2]&&
		(posi.y<=comt[i][2]+comt[i][4])
		)return 1;
	else	return 0;
}

void DrawInit()
{
	int ix00=18,iy00=133;
	double ktheata=PAI/512.00000;
	int i,j;
	for(i=0;i<12;i++)Keys[i]=0;
	for(i=0;i<WIDTHX;i++){
		xynow[i].x=PoTemp[i].x=ix00+i*2;
		xynow[i].y=PoTemp[i].y=iy00;
	}
	double dbamp=168;
	double mini=130;
	for(i=0;i<514;i++){
		dtx[i]=(double)AMXCENTER-mini*cos(i*ktheata);
		dty[i]=(double)AMYCENTER-mini*sin(i*ktheata);
		dbxn[i]=(double)AMXCENTER-dbamp*cos(i*ktheata);
		dbyn[i]=(double)AMYCENTER-dbamp*sin(i*ktheata);
	}
	for(j=0;j<SM;j++){
		for(i=0;i<256;i++){
			wa[j].xy[i].x=ix00+i*2;
			wa[j].xy[i].y=iy00;
		}
		wa[j].hz=440;
		wa[j].tone=69;
		wa[j].f=0;
		wa[j].volt=0;
		wa[j].overflow=0;
	}
	for(i=0;i<=2048;i++)
	{
		sint[i] = sin( PAI * 2.0 * i / 4096);
		cost[i] = cos( PAI * 2.0 * i / 4096);
	}
	if(DP.A440>1000)DP.A440=1440;
	setA440(0);
}
int fcom(int c)
{
	int i;
	for(i=0;i<=ci_end;i++){
		if(comt[i][0]==c)break;
	}
	return i;
}
void setundo(int *comf,bool f);
void setundo(int *comf,bool f)
{
	if(f)*comf=*comf|UDO;
	else *comf=(*comf|UDO)-UDO;
}
//bool checkinst(int n);
bool checkinst(int n)
{
	if(n==TOZAN||n==KINKO||n==NANAKOU||n==SINOBUE||n==OCARINA||n==FULLRANGE||n==TIN||n==OCARINA4||n==BANSURI)return false;
	return true;
}
void setcomf(void);
void setcomf(void)
{
	setundo(&comt[fcom(1)][16],checkinst(DP.inst));
	setundo(&comt[fcom(2)][16],checkinst(DP.inst));
	setundo(&comt[fcom(15)][16],DP.f==1);
	setundo(&comt[fcom(16)][16],DP.f==1);
	setundo(&comt[fcom(112)][16],DP.loaddata==0||DP.mode>100);
	setundo(&comt[fcom(110)][16],DP.f!=0);
}
int CSyaku8View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	int i;
	char buf[300];
//	hWnd=CSyaku8View::m_hWnd;
	GetCurrentDirectory(300,curdir);
	sprintf(buf,"%s\\data",curdir);
	CreateDirectory(buf,NULL);
	if (CView::OnCreate(lpCreateStruct) == -1)return -1;
	RedPen  =new CPen(PS_SOLID,1,RGB(255,  0,  0));
	Red2Pen  =new CPen(PS_SOLID,2,RGB(255,  0,  0));
	NotPen =new CPen(PS_SOLID,2,RGB(255,255,255));

	CDC *pDC=GetDC();
	m_bmp.LoadBitmap(IDB_FRAME);
	grayRGB=GetSysColor(COLOR_BTNFACE);//Bitmapにシステムのボタンの背景色をセットする。
	SetgrayRGB(pDC,&m_bmp);
	ReleaseDC(pDC);
	readini();

	CRect rect;
	rect.left=DP.winx1;
	rect.top=DP.winy1;
	rect.right=DP.winx2;
	rect.bottom=DP.winy2;
	CWnd* pW=GetParent( ); // 親ウィンドウ(主ウィンドウ)のポインタを得ます。
	
	pW->MoveWindow( &rect ); // 指定した座標のウィンドウを描きます。

#ifdef English
//	if(DP.hzcal<100000)MessageBox("Please do [Check Sound-card] of Option-Menu at the first execution.","s8tuner");
#else
//	if(DP.hzcal<100000)MessageBox("オプションメニューからサウンドカードチェックを行ってください。\nさもないと、正しく周波数測定が出来ないパソコンもあります。","s8tuner");
#endif
	DP.dB=(double(DP.dBx10)/10-100.0);
	DrawInit();
	//for wave
	SaveStart=-1;
	DP.loaddata=0;
	DP.ondo=0;
//	DP.manuauto=1;
	// サンプリングバッファを確保
	wavebuf = (BUFTYPE *) GlobalAlloc( GPTR, BUFSZ * sizeof(BUFTYPE) );
	for(i=0; i<MAX_BUFFERS; i++) wh[i] = NULL;
	// 開始
	if(!bWaveOpened) {
		if(bWaveOpened = OpenWaveInputDevice(m_hWnd))
			StartRecording();
	}
	DP.v=0;
	DP.f=1;
	setcomf();
	waveCnt=0;
	return 0;
}
short mid(short *sp,int len);
short mid(short *sp,int len)
{
	short i,max=-255*100,min=255*100;
	for(i=0;i<len;i++){
		if(*(sp+i)>max)max=*(sp+i);
		if(*(sp+i)<min)min=*(sp+i);
	}
	return (max/2+min/2);
}
void Tone(int n);
void Tone(int n)
{	
	DP.fork=DP.fork+n;
	if(DP.fork<TONE1)DP.fork=TONE1;//38
	if(DP.fork>TONE2)DP.fork=TONE2;//98
	wavetone();//DP.vf=1;
}
//const double SENT25=1.0145;
//const double SENT50=1.0293;
//const double SENT25=1.012;
void Settone(double hz);
void Settone(double hz)
{
	int i;
	for(i=TONE1;i<TONE2;i++){
		if(hz>tone[i]&&hz<=tone[i+1])break;
	}
	if(i==TONE2)return;
	if(hz>tone[i]*SENT50)i++;
	if(DP.tone==i)return;
	DP.tone=i;
}
#define WID1 350
#define WID2 10
double Setsoukan();
double Setsoukan()
{//
	int srate=1;//DP.srate;
	int i,j,maxi,n,wid,wid1;	
	double nd,nd1,hz,max=0,mix=256,ww;
	short *ip,wav[4100];
	if(DP.hzf==0||DP.hz==0)return 0;
	hz=DP.hz;
	wid1=4090;
	ip=wavebuf+2000;
	for(i=0;i<wid1;i++)wav[i]=*(ip+i);
	wid=int(int((wid1-WID1-WID2*2)/(22050/hz))*(22050/hz)-WID2);
	n=int(22050/hz)+1;
	if(n>WID1)n=WID1;
	for(i=0;i<WID2*2;i++){//波形との相関係数
		for(ww=0,j=0;j<n;j++)ww=ww+wav[wid+i+j]*wav[j];
		if(max<ww){max=ww;maxi=wid+i;}
	}
//double SRS[3]={2.69,5.38,10.76};//
	nd=(double)maxi/(22050/hz);
	nd1=nd-int(nd);
	if(nd1<0.5)hz=22050/((double)maxi/int(nd));
	else hz=22050/((double)maxi/int(nd+1));
	if ((DP.hz-hz)*(DP.hz-hz)<SRS*SRS) return hz;
	else return DP.hz;
}
int Chehz(double d[]);//
int Chehz(double d[])//  d[0] の何分の一が基本周波数かを返す
{
	int i,j,ans;
	double dd;
	if(d[1]==0)return 1;
	for(i=1;i<13;i++){//0 番目のi分の一
		for(j=1;d[j]!=0;j++){
			dd=d[j]/(d[0]/i);
			dd=dd-int(dd);
			if(dd>0.05&&dd<0.95)break;
		}
		if(d[j]==0){
			if(dd<=0.05)ans=int(d[j-1]/(d[0]/i));
			else ans=int(d[j-1]/(d[0]/i)+1);
			return (j-1)*1000+ans;
		}
	}
	return 0;
}

double Setf(double a,double b);
double Setf(double a,double b)
{
	double f,g,r;
	if(a!=0&&b!=0){
		f=a/b;
		g=b/a;
		if(f<=0.5)r=0;
		else if(f>0.5&&f<=1.0)r=f-0.5;
		else if(f>1&&f<=2)r=1.5-g;
		else if(f>2) r=1;
	}
	else return 0.5;
	return r;
}

void Setfft();
void Setfft()
{
	int i,j,k,n,step;
	double	max,min,d[11],m[11];
	min=(double)DP.peaklevel;
	step=DMAX/256*5;
	for(i=int(50/SRS),j=0;i<int(5000/SRS+1)&&j<10;i++){//50Hz～3350Hz
		if (Amp[i]>Amp[i-step]+min && Amp[i]>Amp[i+step]+min);
		else continue;
		for(max=0,n=i-step;n<i+step;n++)
			if(Amp[n]>max){max=Amp[n];k=n;}
		i=i+step;
		d[j]=double(k)-0.5+Setf(2*Amp[k]-Amp[k-1]-Amp[k-2],2*Amp[k]-Amp[k+1]-Amp[k+2]);
		m[j]=max;
		d[j]=d[j]*SRS;
		if(d[j]<50)d[j]=0;
		else if(d[j]>(double)DP.low1&&d[j]<(double)DP.high1)d[j]=0;
		else if(d[j]>(double)DP.low2&&d[j]<(double)DP.high2)d[j]=0;
		else j++;
	}
	for(i=j;i<10;i++){d[i]=0;m[i]=0;}
	for(i=0;i<4;i++){//choose big 4
		for(k=0,max=0;d[k]!=0&&k<10;k++){
			if(max<m[k]){max=m[k];n=k;}
		}
		if(max!=0)m[n]=0;
	}
	for(i=0;d[i]!=0&&i<10;i++)if(m[i]!=0)d[i]=0;
	for(i=0;i<4;i++){
		for(k=i;k<10;k++){
			if(k==i&&d[k]!=0)break;
			if(d[k]!=0){d[i]=d[k];d[k]=0;break;}
		}
	}
	for(j=0;j<10;j++)if(d[j]==0)break;

#if CHECK==1
for(i=0;i<8;i++)wa[(waveCnt+BarN)%BarN].chk[i]=int(d[i]*10);
wa[(waveCnt+BarN)%BarN].chk[4]=j;
#endif

	if((n=Chehz(d))&&j!=0){
		DP.hz=d[n/1000]/((n+1000)%1000);
		DP.hzf=1;

#if CHECK==1
wa[(waveCnt+BarN)%BarN].chk[5]=n;
wa[(waveCnt+BarN)%BarN].chk[6]=int(DP.hz*10);
#endif

		DP.hz=Setsoukan();

#if CHECK==1
wa[(waveCnt+BarN)%BarN].chk[7]=int(DP.hz*10);
#endif

	}
	else{
		DP.hzf=0;
		DP.hz=0;
	}
}
char songt[15]={'C','d','D','e','E','F','g','G','a','A','b','B','C'};
void Setwavehz();
void Setwavehz()
{
	int i,j,minusi,mul,sum;
	double bi,dsum,minus=0xffffffffff;
	double lo,adB;
	short *ip,dB[260];
	int wav[520*3],save,max=-0xfff,min=0xfff;//,midline;
	static short oldwave[260];
	static char key[4];
	ip=wavebuf+2000;
	for(i=0,sum=0;i<512*3;i++){
		wav[i]=*(ip+i);
		if(wav[i]>max)max=wav[i];
		if(wav[i]<min)min=wav[i];
		sum+=(int)wav[i];
	}
	save=sum/1536;
	for(i=0;i<1536;i++)wav[i]=wav[i]-save;
	max=max-save;min=min-save;
	FFTWave1Calc(ip);
	Setfft();
	if(DP.hzf==1)DP.hz=DP.hz*(DP.hzcal%100000)/10000;
//	if(DP.hzf==1)DP.hz=DP.hz*DP.hzcal/10000;
	for(i=0,dsum=0;i<1536;i++)dsum=dsum+wav[i]*wav[i];
	dsum=sqrt(dsum/1536);
	DP.volt=20*log10(dsum);//-DP.dB;
	if(DP.mode%10<5){
		mul=DP.mode%10;
		for(i=minusi=2000;i<2256;i++){//直前波形との相関係数
			for(bi=0,j=0;j<32;j++)bi=bi+(wavebuf[i+j]+32768)*oldwave[j]/128;
			if(bi<minus){minusi=i;minus=bi;}
		}
		for(i=0;i<WIDTHX;i++){
			oldwave[i]=(wavebuf[minusi]+32768)/128;
			xynow[i].y=(((int)wavebuf[minusi+i*mul]+32768)/128+1)*234/512;			
			if(xynow[i].y>234)xynow[i].y=234;
			xynow[i].y=xynow[i].y+17;
		}
	}
	else{
		for(i=0,max=-0xffff;i<256;i++){
			int step;
			if     (DP.mode%10==5)step=NNN/2048;
			else if(DP.mode%10==6)step=NNN/1024;//srate=1 middle
			else                  step=NNN/ 512;
			if(DP.mode%100>10){
				for(lo=0,j=0;j<step;j++)if(lo<Amp[i*step+j]){lo=Amp[i*step+j];adB=AmpdB[i*step+j];}
				dB[i]=short(adB*10);
				xynow[i].y=227-(int)lo*2;
			}
			else{
				for(lo=0,j=0;j<step;j++)if(lo<AmpdB[i*step+j])lo=AmpdB[i*step+j];
				dB[i]=short(lo*10);
				xynow[i].y=257-(int)lo*2+(DP.logref-150);
				if(xynow[i].y>max)max=xynow[i].y;
				if(xynow[i].y>227)xynow[i].y=227;
				else if(xynow[i].y<17)xynow[i].y=17;
			}
		}
	}
	waveNow=(waveCnt+SM)%SM;
	for(i=0;i<WIDTHX;i++){
		wa[waveNow].xy[i].y=xynow[i].y;
		wa[waveNow].dB[i]=dB[i];
	}
	wa[waveNow].f=DP.hzf;
	wa[waveNow].hz=DP.hz;
//	if(DP.hzf==1&&DP.manuauto%2==1)Settone(DP.hz);
	if(DP.hzf==1)Settone(DP.hz);
	wa[waveNow].tone=DP.tone;
	wa[waveNow].volt=DP.volt;
	lo=DP.volt;
	if(lo<90.3-6)wa[waveNow].overflow=0;//20*log10(32768)=90.3
	else if(lo<90.3-3)wa[waveNow].overflow=1;
	else wa[waveNow].overflow=2;
	wa[waveNow].mode=DP.mode;
	if(DP.hzf==1)DP.cent=int(2*1200*log(DP.hz/tone[DP.tone])/log(2));//本来の２倍
	else DP.cent=-127*2;
	wa[waveNow].cent=DP.cent;
	if(DP.mode>100){
		if(DP.cent<99&&DP.cent>-99)key[waveCnt%3]=DP.tone%12;
		else key[waveCnt%3]=12;
		if((key[0]==key[1])&&(key[0]==key[2])){
			Keys[key[0]]+=1;
			key[0]=20;
			key[1]=21;
			key[2]=22;
		}
	}

#if CHECK==2
	wa[waveNow].chk[0]=minusi;
	wa[waveNow].chk[1]=int(WAVE_MAPPER);
	wa[waveNow].chk[2]=-1;
	wa[waveNow].chk[3]=1;
	wa[waveNow].chk[4]=DP.dB*10;

//	wa[(waveCnt+BarN)%BarN].chk[5]=20*log(10000);
#endif
}
/*466.16Hzが440Hzの何セント上かは
下のように計算できます。
466.16は440の半音上ですから当然100セントになるはずですが、
実際に関数電卓で計算しましたら99.99セントとなりました。
 
 1200xlog(466.16/440)/log2
=1200xlog(1.05945)/log2
=1200x0.02508/0.3010
=99.99(セント)*/

//int in[5];
void DispBlue(CDC *MemDC,CDC *pDC,double Hz,int tonen);
void DispBlue(CDC *MemDC,CDC *pDC,double Hz,int tonen)
{
	int flag,f1;
	static int oldflag=0;
	double dd,qhz;
	qhz=tone[tonen];
	if(DP.blue==1)dd=1.0058;
	else if(DP.blue==2)dd=1.0116;
	else if(DP.blue==3)dd=1.0175;
	if(DP.f){//動作中は直前データもしくは現データが範囲内なら青表示
		if(Hz<qhz*dd&&Hz>qhz/dd)f1=1;
		else f1=0;
		if(f1==1||oldflag==1)flag=1;
		else flag=0;
		oldflag=f1;
	}else{//停止中は現データのみ判定
		if(Hz<qhz*dd&&Hz>qhz/dd)flag=1;
		else flag=0;
	}
	pDC->BitBlt(246,299,52,34,MemDC,246,299,SRCCOPY);
	pDC->BitBlt(223,301,27,35,MemDC,223,301,SRCCOPY);
	pDC->BitBlt(293,301,27,35,MemDC,293,301,SRCCOPY);
	pDC->BitBlt(199,305,32,37,MemDC,199,305,SRCCOPY);
	pDC->BitBlt(313,305,32,37,MemDC,313,305,SRCCOPY);
	pDC->BitBlt(167,310,32,37,MemDC,167,310,SRCCOPY);
	pDC->BitBlt(345,310,32,37,MemDC,345,310,SRCCOPY);
	if(DP.blue>0&&flag)pDC->BitBlt(246,299,52,34,MemDC,708,650,SRCCOPY);
	if(DP.blue>1&&flag){
		pDC->BitBlt(223,301,27,35,MemDC,703,684,SRCCOPY);
		pDC->BitBlt(293,301,27,35,MemDC,732,684,SRCCOPY);
	}
	if(DP.blue>2&&flag){
		pDC->BitBlt(199,305,32,37,MemDC,695,721,SRCCOPY);
		pDC->BitBlt(313,305,32,37,MemDC,728,721,SRCCOPY);
	}
}
void junmaru(CDC *MemDC,CDC *pDC,int x,int y,char *p)
{
	if(strlen(p)<4){
		pDC->FillSolidRect(x-7,y-10,5*strlen(p)+4,10,RGB(220,220,220));
		printabc(MemDC,pDC,p,x-5,y-16,SRCAND);
	}
	else{
		pDC->FillSolidRect(x-12,y-10,5*strlen(p)+6,10,RGB(220,220,220));
		printabc(MemDC,pDC,p,x-10,y-16,SRCAND);
	}
	pDC->FillSolidRect(x+1,y,3,5,RGB(255,0,0));
	pDC->FillSolidRect(x,y+1,5,3,RGB(255,0,0));
}
void junkazu(CDC *MemDC,CDC *pDC,char *p,int x,int y)//,char *p,int dx,int dy)
{
	pDC->FillSolidRect(x-1,y+6,5*strlen(p)+3,10,RGB(220,220,220));
	printabc(MemDC,pDC,p,x,y,SRCAND);
}
void DispMeterData(CDC *MemDC,CDC *pDC)//,double Hz,int tonen,int cent)
{	
	CPen *oldpen;
	int i,neo;//,flag;
	double Hz=wa[waveNow].hz;
	int tonen=wa[waveNow].tone;
	int cent=wa[waveNow].cent;
	if(Hz>9999.0||Hz<=0.00)Hz=0;
	if(cent<0)cent=cent+1;
	neo=int(256+(double)cent);
	if(neo<=2||Hz==0)neo=2;
	if(neo>=512)neo=512;
	DispBlue(MemDC,pDC,Hz,tonen);

	oldpen=pDC->SelectObject(NotPen);
	pDC->MoveTo((int)dtx[DP.hzold],(int)dty[DP.hzold]);
	pDC->LineTo((int)dbxn[DP.hzold],(int)dbyn[DP.hzold]);
	pDC->SelectObject(Red2Pen);	
	pDC->MoveTo((int)dtx[neo],(int)dty[neo]);
	pDC->LineTo((int)dbxn[neo],(int)dbyn[neo]);
	pDC->SelectObject(oldpen);
	DP.hzold=neo;
	Num(MemDC,pDC,2,199,454,4,(int)(Hz+0.05),SRCCOPY);//AND);//intへのキャストは切捨てなので
	Num(MemDC,pDC,0,329,477,1,((int)((Hz+0.05)*10))%10,SRCCOPY);//AND);
	i=DP.inst;
	if(i!=NOUKAN&&DP.juns8==1){
		int tn=tonen,sun;
		if(i==KINKO||i==TOZAN||i==NANAKOU)sun=DP.sn+inst_para[i][1];//0
		else if(i==OCARINA)sun=120-DP.oca+inst_para[i][1];//2;
		else if(i==OCARINA4)sun=120-DP.oca4+inst_para[i][1];//2;
		else if(i==FULLRANGE)sun=120-DP.voca+inst_para[i][1];//9;
		else if(i==SINOBUE)sun=120-DP.sino+inst_para[i][1];//7;//+3を取るとCがルート
		else if(i==TIN)sun=120-DP.tin+inst_para[i][1];//2;
		else if(i==BANSURI)sun=120-DP.bansuri+inst_para[i][1];//2;
		else sun=inst_para[i][1];//
//ツ6/5 レ4/3 チ3/2 リ8*2/9
//  ●短３度低い「羽＝中リ」は、５／６～６／７の赤点
//  ●短３度高い「商＝ツ」は、７／６～６／５
//  ●長３度低い「羽＝メリ」は、７／９～４／５の赤点
//  ●長２度低い「羽＝り」は、７／８～※１１／１２●長２度低い「羽＝り」は、７／８～※９／１０（再修正してください）
//  ●短２度低い「羽＝メロ」は、１４／１５～２１／２２ 14/15 20/21
//また、
//  ●短２度高い「商＝メツ」は、２２／２１～１５／１４  21/20 14/13
//  ●長２度高い「商＝中メ」は、１２／１１～８／７●長２度高い「商＝中ツ」は、８／７～１０／９
//  ●長３度高い「商＝メレ」は、５／４～９／７
//		pDC->BitBlt(177,314,25,25,MemDC,177,314,SRCCOPY);
//		pDC->BitBlt(344,314,25,25,MemDC,344,314,SRCCOPY);
//D 9/8
		if((tn+sun+4)%12==3){//ツ
			junmaru(MemDC,pDC,305,314,"6:5");//,"6:5",-4,-16);
			junmaru(MemDC,pDC,193,327,"7:6");//,"7:6",-6,-15);
		}
		else if((tn+sun+4)%12==6){//ウ
			junmaru(MemDC,pDC,230,314,"5:7");
		}
		else if((tn+sun+4)%12==8){
			junmaru(MemDC,pDC,192,328,"7:9");
			junmaru(MemDC,pDC,301,313,"4:5");
		}
		else if((tn+sun+4)%12==9){
			junmaru(MemDC,pDC,234,314,"5:6");
			junmaru(MemDC,pDC,344,326,"6:7");
		}
		else if((tn+sun+4)%12==11){
//B 15/8 34/18
			junmaru(MemDC,pDC,227,316,"14:15");
//			junmaru(MemDC,pDC,250,316,"15:16");
			junmaru(MemDC,pDC,272,311,"17:18");
			junmaru(MemDC,pDC,303,314,"20:21");
		}
		else if((tn+sun+4)%12==4){
			junmaru(MemDC,pDC,239,313,"5:4");
			junmaru(MemDC,pDC,347,327,"9:7");
		}
		else if((tn+sun+4)%12==1){
			junmaru(MemDC,pDC,234,314,"21:20");
			junmaru(MemDC,pDC,333,322,"14:13");
		}
		else if((tn+sun+4)%12==2){
			junmaru(MemDC,pDC,229,316,"10:9");
			junmaru(MemDC,pDC,278,312,"9:8");
			junmaru(MemDC,pDC,339,324,"8:7");
		}
		else if((tn+sun+4)%12==5){//レ
			junmaru(MemDC,pDC,266,311,"4:3");
		}
		else if((tn+sun+4)%12==7){//チ
			junmaru(MemDC,pDC,272,311,"3:2");
		}
		else if((tn+sun+4)%12==10){//り
			junmaru(MemDC,pDC,198,325,"7:8");
			junmaru(MemDC,pDC,261,311,"8:9");
			junmaru(MemDC,pDC,309,315,"9:10");
		}
	}

#if CHECK!=0
	for(int i=7;i>=0;i--){
		char buf[20];
		sprintf(buf,"%06d   ",wa[waveNow].chk[i]);
		printabc(MemDC,pDC,buf,18+i/4*56,268+i%4*11);
	}
#endif
}
#define ZUREX 62
#define ZUREY1 108//五線譜
#define ZUREY 194//CENT表示
void DispNote1(CDC* MemDC,CDC* pDC,int pos,int data){
	int x,y,y1=ZUREY1,type,ps,sc,s,cent;
	x=ZUREX+7*pos;
	sc=wa[data].tone;//sc:69 A 
	cent=wa[data].cent/2;
	if(cent<=50&&cent>=-50){
		if(sc>=56&&sc<=84){
			s=sc-56-4;
				 if(sc==59){y=y1+5;type=0;ps=0;}
			else if(sc==58){y=y1+5;type=1;ps=0;}
			else if(sc==57){y=y1+10;type=0;ps=0;}
			else if(sc==56){y=y1+10;type=1;ps=0;}
		    else if(sc%12==11){y=y1-30;type=0;ps=s/12;}
			else if(sc%12==10){y=y1-30;type=1;ps=s/12;}//b--
			else if(sc%12==9){y=y1-25;type=0;ps=s/12;}
			else if(sc%12==8){y=y1-25;type=1;ps=s/12;}//a
			else if(sc%12==7){y=y1-20;type=0;ps=s/12;}
			else if(sc%12==6){y=y1-20;type=1;ps=s/12;}//g--
			else if(sc%12==5){y=y1-15;type=0;ps=s/12;}//f
			else if(sc%12==4){y=y1-10;type=0;ps=s/12;}
			else if(sc%12==3){y=y1-10;type=1;ps=s/12;}//e--
			else if(sc%12==2){y=y1-5;type=0;ps=s/12;}
			else if(sc%12==1){y=y1-5;type=1;ps=s/12;}//d
			else if(sc%12==0){y=y1;type=0;ps=s/12;}//c--
		}
		else{
			s=0;
		    if(sc%12==11){y=y1-30;type=0;ps=s/12;}//b-- 
			else if(sc%12==10){y=y1-30;type=1;ps=s/12;}//b--b
			else if(sc%12==9){y=y1-25;type=0;ps=s/12;}//a
			else if(sc%12==8){y=y1-25;type=1;ps=s/12;}//a b
			else if(sc%12==7){y=y1-20;type=0;ps=s/12;}//g
			else if(sc%12==6){y=y1-20;type=1;ps=s/12;}//g--b
			else if(sc%12==5){y=y1-15;type=0;ps=s/12;}//f
			else if(sc%12==4){y=y1-45;type=0;ps=s/12;}//e
			else if(sc%12==3){y=y1-45;type=1;ps=s/12;}//e--b
			else if(sc%12==2){y=y1-40;type=0;ps=s/12;}//d
			else if(sc%12==1){y=y1-40;type=1;ps=s/12;}//d b
			else if(sc%12==0){y=y1-35;type=0;ps=s/12;}//c--
		}
	}else{y=y1+20;type=2;}
	if(type==2)pDC->BitBlt(x+1,y,7,11,MemDC,587+(type%4)*8,606,SRCCOPY);//測定不可
	else{
		pDC->BitBlt(x,y-35*ps+1,7,9,MemDC,587+(type%4)*8,607,SRCCOPY);//音符表示
		if(sc<56||sc>84){
			//ト音譜からはみ出たらオクターブ数表示
			pDC->BitBlt(x+1,y1-80,7,9,MemDC,559+(sc/12-1)*8,466,SRCCOPY);
		}
	}
	if(DP.f==0&&data==waveNow)pDC->FillSolidRect(65+pos*7,40,2,208,RGB(200,200,200));
	if(DP.f==0&&data==SaveStart)pDC->FillSolidRect(65+pos*7,40,2,208,RGB(255,200,200));
}

void DispZureall1(CDC* MemDC,CDC* pDC,int pos,int data)
{
	int cent;
	cent=wa[data].cent/2;
	if(cent>=-50&&cent<=50){
		pDC->FillSolidRect(ZUREX+7*pos+1,ZUREY-cent,6,3,RGB(0,0,0));
	}
}
//#define ZUREY1 108//五線譜
//#define ZUREY 194//CENT表示
void DispZureInit(CDC* MemDC,CDC* pDC)
{
	int my=ZUREY,my5=ZUREY-132;//62;
	pDC->FillSolidRect(20,17,504,234,RGB(255,255,255));
	pDC->FillSolidRect(20,my -9,503,1,RGB(200,200,200));
	pDC->FillSolidRect(20,my-19,503,1,RGB(200,200,200));
	pDC->FillSolidRect(20,my-29,503,1,RGB(200,200,200));
	pDC->FillSolidRect(20,my-39,503,1,RGB(200,200,200));
	pDC->FillSolidRect(20,my-49,503,1,RGB(200,200,200));
	pDC->FillSolidRect(20,my+1,503,1,RGB(0,0,0));
	pDC->FillSolidRect(20,my+11,503,1,RGB(200,200,200));
	pDC->FillSolidRect(20,my+21,503,1,RGB(200,200,200));
	pDC->FillSolidRect(20,my+31,503,1,RGB(200,200,200));
	pDC->FillSolidRect(20,my+41,503,1,RGB(200,200,200));
	pDC->FillSolidRect(20,my+51,503,1,RGB(200,200,200));
	pDC->FillSolidRect(20,my5+1,503,1,RGB(0,0,0));//
	pDC->FillSolidRect(20,my5+11,503,1,RGB(0,0,0));
	pDC->FillSolidRect(20,my5+21,503,1,RGB(0,0,0));
	pDC->FillSolidRect(20,my5+31,503,1,RGB(0,0,0));
	pDC->FillSolidRect(20,my5+41,503,1,RGB(0,0,0));
	pDC->FillSolidRect(55,my5+51,468,1,RGB(210,210,210));
	pDC->FillSolidRect(55,my5+61,468,1,RGB(210,210,210));
	pDC->FillSolidRect(55,my5-9,468,1, RGB(210,210,210));
	pDC->FillSolidRect(55,my5-19,468,1,RGB(210,210,210));
	pDC->BitBlt(20,my5-13,30,72,MemDC,552,577,SRCCOPY);
}

bool checkrange(int i)
{
	int tn=wa[i].tone;
	if(DP.inst==KINKO||DP.inst==TOZAN||DP.inst==NANAKOU)tn=tn+DP.sn;
	else if(DP.inst==SINOBUE)tn=tn-DP.sino;
	else if(DP.inst==OCARINA)tn=tn-DP.oca;
	else if(DP.inst==OCARINA4)tn=tn-DP.oca4;
	else if(DP.inst==TIN)tn=tn-DP.tin;
	if(tn>=inst_para[DP.inst][2]&&tn<=inst_para[DP.inst][3])return true;
	else return false;
}
void DispZureall(CDC* MemDC,CDC* pDC);
void DispZureall(CDC* MemDC,CDC* pDC)
{
	int i,j,tsm[15],sm1,sm2,ch1,ch2;
	if(waveCnt<BarN){
		DispZureInit(MemDC,pDC);
		for(i=0;i<=waveCnt;i++){
			if(DP.mode<200||checkrange(i)){
				DispZureall1(MemDC,pDC,i,i);
				DispNote1(MemDC,pDC,i,i);
			}else{
				pDC->BitBlt(63+7*i,128,7,11,MemDC,603,606,SRCCOPY);//測定不可
			}
		}
	}else{
		DispZureInit(MemDC,pDC);
		for(i=0;i<BarN;i++){
			if(DP.f)j=(i+waveCnt-BarN+1)%SM;
			else j=(i+Lt)%SM;
			if(DP.mode<200||checkrange(j)){
				DispZureall1(MemDC,pDC,i,j);
				DispNote1(MemDC,pDC,i,j);
			}else{
				pDC->BitBlt(63+7*i,128,7,11,MemDC,603,606,SRCCOPY);//測定不可
			}
		}
	}
	int x,len,Lt1,Lt2,L=BarN*7;
	if(DP.f==1)Lt1=(waveCnt-BarN+SM)%SM;
	else Lt1=Lt;
	pDC->FillSolidRect(62,249,L+2,1,RGB(255,255,255));
	if(waveCnt>BarN){
		if(waveCnt<SM){
			len=L*BarN/waveCnt;
			x=(L-len)*Lt1/(waveCnt-BarN);
		}else{
			len=L*BarN/SM;
			Lt2=(SM+Lt1-waveCnt%SM)%SM;
			x=(L-len)*Lt2/(SM-BarN);
		}
		pDC->FillSolidRect(62+x,249,len,1,RGB(100,100,100));
	}
	if(DP.speed!=2)return;
	for(ch1=12,ch2=12,sm1=0,sm2=0,i=0;i<12;i++){
		if(mycheck==1)tsm[i]=2*Keys[i%12]+Keys[(i+2)%12]+2*Keys[(i+4)%12]+Keys[(i+5)%12]+2*Keys[(i+7)%12]+2*Keys[(i+9)%12]+Keys[(i+11)%12];
		else tsm[i]=Keys[i%12]+Keys[(i+2)%12]+Keys[(i+4)%12]+Keys[(i+5)%12]+Keys[(i+7)%12]+Keys[(i+9)%12]+Keys[(i+11)%12];
		if(tsm[i]>sm1){sm2=sm1;sm1=tsm[i];ch2=ch1;ch1=i;}
		else if(tsm[i]>sm2){sm2=tsm[i];ch2=i;}
	}
	char buf[10],ch[14][3]={"C ","D$","D ","E$","E ","F ","F#","G ","A$","A ","B$","B ","  "};
	char k[14][3]={"C","","D","","E","F","","G","","A","","B",""};
#ifdef _DEBUG
	if(mycheck==0){
		int x1=20,y1=109;
		Num(MemDC,pDC,1,x1,y1-5*0,3,Keys[0],SRCCOPY);//C
		Num(MemDC,pDC,1,x1+20,y1-5*8+2,3,Keys[1],SRCCOPY);//Db
		Num(MemDC,pDC,1,x1,y1-5*8,3,Keys[2],SRCCOPY);//D
		Num(MemDC,pDC,1,x1+20,y1-5*2+2,3,Keys[3],SRCCOPY);//Eb
		Num(MemDC,pDC,1,x1,y1-5*2,3,Keys[4],SRCCOPY);//E
		Num(MemDC,pDC,1,x1,y1-5*10,3,Keys[5],SRCCOPY);//F
		Num(MemDC,pDC,1,x1+20,y1-5*4+2,3,Keys[6],SRCCOPY);//F#
		Num(MemDC,pDC,1,x1,y1-5*4,3,Keys[7],SRCCOPY);//G
		Num(MemDC,pDC,1,x1+20,y1+5*2-5*14+2,3,Keys[8],SRCCOPY);//Ab
		Num(MemDC,pDC,1,x1,y1+5*2-5*14,3,Keys[9],SRCCOPY);//A
		Num(MemDC,pDC,1,x1+20,y1-5*6+2,3,Keys[10],SRCCOPY);//Bb
		Num(MemDC,pDC,1,x1,y1-5*6,3,Keys[11],SRCCOPY);//B
		sprintf(buf,"!1%s!3%s",ch[ch1],ch[ch2]);
		printabc(MemDC,pDC,buf,22,125);	
	}
	if(mycheck==1){
		int x1=20,y1=109;
		Num(MemDC,pDC,1,x1,y1-5*0,3,tsm[0],SRCCOPY);//C
		Num(MemDC,pDC,1,x1+20,y1-5*8+2,3,tsm[1],SRCCOPY);//Db
		Num(MemDC,pDC,1,x1,y1-5*8,3,tsm[2],SRCCOPY);//D
		Num(MemDC,pDC,1,x1+20,y1-5*2+2,3,tsm[3],SRCCOPY);//Eb
		Num(MemDC,pDC,1,x1,y1-5*2,3,tsm[4],SRCCOPY);//E
		Num(MemDC,pDC,1,x1,y1-5*10,3,tsm[5],SRCCOPY);//F
		Num(MemDC,pDC,1,x1+20,y1-5*4+2,3,tsm[6],SRCCOPY);//F#
		Num(MemDC,pDC,1,x1,y1-5*4,3,tsm[7],SRCCOPY);//G
		Num(MemDC,pDC,1,x1+20,y1+5*2-5*14+2,3,tsm[8],SRCCOPY);//Ab
		Num(MemDC,pDC,1,x1,y1+5*2-5*14,3,tsm[9],SRCCOPY);//A
		Num(MemDC,pDC,1,x1+20,y1-5*6+2,3,tsm[10],SRCCOPY);//Bb
		Num(MemDC,pDC,1,x1,y1-5*6,3,tsm[11],SRCCOPY);//B
		sprintf(buf,"!1%s!3%s",ch[ch1],ch[ch2]);
		printabc(MemDC,pDC,buf,22,125);	
	}
#endif
	sprintf(buf,"!1%s",ch[ch1]);
	printabc(MemDC,pDC,buf,30,25);	
}

void DispBarall(CDC* MemDC,CDC* pDC,double *volt,short *oflow,int now);
void DispBarall(CDC* MemDC,CDC* pDC,double *volt,short *oflow,int now)//volt最大値100
{
	int i,v,h=93,dx=3,x=556,y=84;//41+65-22;
	for(i=0;i<BarN;i++){
		v=int(volt[i]*h/100);
		if(v>93)v=93;
		else if(v<0)v=0;//522 268
		pDC->BitBlt(x+dx*i,y    ,dx,h-v,MemDC,522,280,SRCCOPY);//white
		if(oflow[i]==2)pDC->BitBlt(x+dx*i,y+h-v,dx,  v,MemDC,523,30,SRCCOPY);
		else if(oflow[i]==1)pDC->BitBlt(x+dx*i,y+h-v,dx,  v,MemDC,521,30,SRCCOPY);
		else pDC->BitBlt(x+dx*i,y+h-v,dx,  v,MemDC,541,11,SRCCOPY);//gray
	}
	if(DP.f==0)
		pDC->BitBlt(1+x+dx*now,y,int(dx/2),h,MemDC,523,33,SRCCOPY);
	int len,Lt1,Lt2,L=BarN*3;
	if(DP.f==1)Lt1=(waveCnt-BarN+SM)%SM;
	else Lt1=Lt;
	pDC->FillSolidRect(556,178,L+2,1,RGB(255,255,255));
	if(waveCnt>BarN){
		if(waveCnt<SM){
			len=L*BarN/waveCnt;
			x=(L-len)*Lt1/(waveCnt-BarN);
		}else{
			len=L*BarN/SM;
			Lt2=(SM+Lt1-waveCnt%SM)%SM;
			x=(L-len)*Lt2/(SM-BarN);
		}
		pDC->FillSolidRect(556+x,178,len,1,RGB(0,0,0));
	}
//	if(DP.mode==8)DispZureall(MemDC,pDC);
}


void CSyaku8View::DispIroiro(CDC *MyDC,CDC *pDC,int DN,int loca,int locan)
{
	int i;
	char tonen;
	if(DP.f)tonen=DP.tone;
	else tonen=wa[waveNow].tone;
	char buf[50];
	if(DN&FRA){//full frame 625 45 125 27
		pDC->BitBlt(0,0,760,18,MyDC,0,0,SRCCOPY);//全体 上
		pDC->BitBlt(0,297,760,228,MyDC,0,297,SRCCOPY);//全体　下
		pDC->BitBlt(0,18,18,280,MyDC,0,18,SRCCOPY);//全体　中左
		pDC->BitBlt(525,18,240,280,MyDC,525,18,SRCCOPY);//全体　中右
		for(i=0;i<5;i++)pDC->BitBlt(18+i*85,252,85,16,MyDC,330,136,SRCCOPY);
		pDC->BitBlt(18+i*85,252,83,16,MyDC,330,136,SRCCOPY);
		pDC->FillSolidRect(583,17,101,56,RGB(255,255,255));//dB frame
		pDC->FillSolidRect(554,105-22,196,94,RGB(255,255,255));//volume graph
		pDC->FillSolidRect(unX,unY,196,120,RGB(255,255,255));//fingerring
	}
	if(DN&LUF&&!(DN&FRA)){
		pDC->FillSolidRect(18,17,508,235,RGB(255,255,255));
		pDC->FillSolidRect(526,18,1,233,RGB(255,255,255));
	}
	if(DN&VOL){
		int vol=534+DP.v;
		int c=fcom(53);
		if(vol>720)vol=720;
		pDC->BitBlt(comt[c][1],comt[c][2],comt[c][3],comt[c][4],MyDC,comt[c][1],comt[c][2],SRCCOPY);
		if(DP.v==0)pDC->BitBlt(comt[c][1],comt[c][2],comt[c][9],comt[c][10],MyDC,comt[c][11],comt[c][12],SRCCOPY);
		else pDC->BitBlt(vol,comt[c][2],comt[c][9],comt[c][10],MyDC,comt[c][7],comt[c][8],SRCCOPY);
	}
	if(DN&HER){	//メーターの周波数
		
		sprintf(buf,"!1%04d!3",(int)(tone[tonen-1]+0.5));
		printabc(MyDC,pDC,buf,34,422);
		if(tone[tonen]<1000){
			sprintf(buf,"!1%03d.%01d  ",(int)(tone[tonen]+0.05),(int((tone[tonen]+0.05)*10))%10);
			printabc(MyDC,pDC,buf,252,278);
		}
		else{
			sprintf(buf,"!1%04d  ",(int)(tone[tonen]+0.5));
			printabc(MyDC,pDC,buf,252,278);
		}
		sprintf(buf,"!1%04d ",(int)(tone[tonen+1]+0.5));
		printabc(MyDC,pDC,buf,469,422);
	}
	if(DN&A44){
		int sx=333,sy=427,dx=sx+29,dy=sy+7;
		sprintf(buf,"!1%3d!a",DP.A440%1000);
		printabc(MyDC,pDC,buf,267,426);
		pDC->FillSolidRect(sx,sy+5,42,15,grayRGB);//RGB(192,192,192));
		if(DP.ondo==1){//4どで3Hz
			double d;
			d=20+(DP.A440%1000-440.0)/3*4;;
			if(d>=0)sprintf(buf,"%02d.%01d!4C",int(d),(int(d*10))%10);
			else sprintf(buf,"%02d.%01d!4C",int(d),(int(-d*10))%10);
			printabc(MyDC,pDC,buf,sx,sy,SRCAND);
			pDC->FillSolidRect(dx-(d>-10)*6,dy,1,1,RGB(0,0,0));
			pDC->FillSolidRect(dx+2-(d>-10)*6,dy,1,1,RGB(0,0,0));
			pDC->FillSolidRect(dx+1-(d>-10)*6,dy-1,1,1,RGB(0,0,0));
			pDC->FillSolidRect(dx+1-(d>-10)*6,dy+1,1,1,RGB(0,0,0));
		}
	}

	if(DN&ISV){	//音圧メータ
		double Max=0,Min=0,vol[100],v[100],t[100];
		short oflow[100];
		int j,now=BarN-1;
		if(waveCnt<BarN){
			for(i=0,Max=0,Min=100;i<=waveCnt;i++){
				v[i]=wa[i].volt;
				oflow[i]=wa[i].overflow;
				if(Max<v[i])Max=v[i];
				if(Min>v[i])Min=v[i];
				if(i==waveNow)now=i;
			}
			for(;i<BarN;i++){v[i]=0;oflow[i]=0;}
		}else{
			for(i=0,Max=0,Min=100;i<BarN;i++){
				if(DP.f)j=(i+waveCnt-BarN+1)%SM;
				else j=(i+Lt)%SM;
				if(j==waveNow)now=i;
				v[i]=wa[j].volt;
				oflow[i]=wa[j].overflow;
				if(Max<v[i])Max=v[i];
				if(Min>v[i])Min=v[i];
			}
		}
		if(Max>100)for(i=0;i<BarN;i++)t[i]=vol[i]=v[i]*100/Max;
		else for(i=0;i<BarN;i++)t[i]=vol[i]=v[i]*100/91;
		DispBarall(MyDC,pDC,vol,oflow,now);
		DispDB(MyDC,pDC,wa[waveNow].volt);
	}
	if(DN&CDE){	//CDEFGABC
		int a,b,d,aa=abcX,bb=abcY;
		if(DP.cdedore==1){a=206;b=55;d=22;}
		else {a=abcX;b=abcY;d=23;}
		pDC->BitBlt(258,392,37,23,MyDC,258,393,SRCCOPY);//white erase
		pDC->BitBlt(258,392,24,d,MyDC,a+25*(ct[(tonen+3)%12][0]),b,SRCCOPY);
		if(ct[(tonen+3)%12][1])pDC->BitBlt(282,392,13,18,MyDC,aa+25*7,bb,SRCAND);
		if(tonen!=0)Num(MyDC,pDC,4,292,404,1,tonen/12-1);//qhz/1.06
		a=20;b=189;d=23;
		pDC->BitBlt(554,276,46,30,MyDC,554,276,SRCCOPY);//white erase
		if(ct[(DP.fork+3)%12][0]<5)pDC->BitBlt(560,283,16,15,MyDC,a+16*(ct[(DP.fork+3)%12][0]),b,SRCAND);
		else pDC->BitBlt(560,283,16,15,MyDC,a+16*(ct[(DP.fork+3)%12][0])-2,b,SRCAND);//ABC・・が均等でないので
		if(ct[(DP.fork+3)%12][1])pDC->BitBlt(555+18+3,278+4,13,18,MyDC,aa+25*7,bb+5,SRCAND);//♭
		Num(MyDC,pDC,4,587,287,1,DP.fork/12-1,SRCAND);//qhz/1.06
	}
	if(DN&INS)DispInstName(MyDC,pDC);
	if(DN&ROT){//運指表示
		if(checkinst(DP.inst))unsi1(MyDC,pDC,tonen,DN&FRA);
		else unsi(MyDC,pDC,tonen,DN&FRA);//KINKO,TOZAN,NANAKOU,SINOBUE,OCARINA,TIN,OCARINA4,FULLRANGE)
	}
	if(DN&MHB){
		setcomf();
		if(checkinst(DP.inst))//key
			 pDC->BitBlt(662,484,82,24,MyDC,357,31,SRCCOPY);
		else pDC->BitBlt(662,484,82,24,MyDC,662,484,SRCCOPY);
		pDC->BitBlt(605,278,140,24,MyDC,605,278,SRCCOPY);
		if(DP.f==0){//18,99
			pDC->BitBlt(605,185,90,24,MyDC,605,185,SRCCOPY);
			pDC->BitBlt(553,216,94,23,MyDC,553,216,SRCCOPY);
		}
		else{//116 99
			pDC->BitBlt(605,185,90,24,MyDC,19,77,SRCCOPY);//358,271,SRCCOPY);
			pDC->BitBlt(553,216,94,23,MyDC,113,100,SRCCOPY);
		}
		if(DP.loaddata==0||DP.mode>100)pDC->BitBlt(727,216,23,23,MyDC,659,25,SRCCOPY);
		else pDC->BitBlt(727,216,23,23,MyDC,727,216,SRCCOPY);
	}
	if(DN&BTN){
		int c=fcom(17);
		if(comt[c+1][16]==0)
			pDC->BitBlt(comt[c][1],comt[c][2],comt[c][3],comt[c][4],
					MyDC,comt[c][5],comt[c][6],SRCCOPY);
		else
			pDC->BitBlt(comt[c+1][1],comt[c+1][2],comt[c+1][3],comt[c+1][4],
					MyDC,comt[c+1][5],comt[c+1][6],SRCCOPY);
	}
}
void chakey(int n);
void chakey(int n)
{
	int *pi;
	if(DP.inst==KINKO||DP.inst==TOZAN||DP.inst==NANAKOU)pi=&DP.sn;
	else if(DP.inst==SINOBUE)pi=&DP.sino;
	else if(DP.inst==OCARINA)pi=&DP.oca;
	else if(DP.inst==OCARINA4)pi=&DP.oca4;
	else if(DP.inst==TIN)pi=&DP.tin;
	else if(DP.inst==FULLRANGE)pi=&DP.voca;
	else if(DP.inst=BANSURI)pi=&DP.bansuri;	
	*pi=*pi+n;
	if(*pi<inst_para[DP.inst][4])*pi=inst_para[DP.inst][4];//11;
	if(*pi>inst_para[DP.inst][5])*pi=inst_para[DP.inst][5];//32;
/*
	if(DP.inst==KINKO||DP.inst==TOZAN||DP.inst==NANAKOU){
		DP.sn=DP.sn+n;
		if(DP.sn<inst_para[DP.inst][4])DP.sn=inst_para[DP.inst][4];//11;
		if(DP.sn>inst_para[DP.inst][5])DP.sn=inst_para[DP.inst][5];//32;
	}
	else if(DP.inst==SINOBUE){
		DP.sino=DP.sino+n;
		if(DP.sino<inst_para[DP.inst][4])DP.sino=inst_para[DP.inst][4];//1;
		if(DP.sino>inst_para[DP.inst][5])DP.sino=inst_para[DP.inst][5];//13;
	}
	else if(DP.inst==OCARINA4){
		DP.oca4=DP.oca4+n;
		if(DP.oca4<inst_para[DP.inst][4])DP.oca4=inst_para[DP.inst][4];//1;
		if(DP.oca4>inst_para[DP.inst][5])DP.oca4=inst_para[DP.inst][5];//13;
	}
	else if(DP.inst==OCARINA){
		DP.oca=DP.oca+n;
		if(DP.oca<inst_para[DP.inst][4])DP.oca=inst_para[DP.inst][4];//1;
		if(DP.oca>inst_para[DP.inst][5])DP.oca=inst_para[DP.inst][5];//13;
	}
	else if(DP.inst==TIN){
		DP.tin=DP.tin+n;
		if(DP.tin<inst_para[DP.inst][4])DP.tin=inst_para[DP.inst][4];//6;
		if(DP.tin>inst_para[DP.inst][5])DP.tin=inst_para[DP.inst][5];//25;
	}
	else if(DP.inst==FULLRANGE){
		DP.voca=DP.voca+n;
		if(DP.voca<inst_para[DP.inst][4])DP.voca=inst_para[DP.inst][4];//1;
		if(DP.voca>inst_para[DP.inst][5])DP.voca=inst_para[DP.inst][5];//13;
	}
*/
}
void instr(int n);
void instr(int n)
{
	DP.inst=DP.inst+n;
	if(DP.inst<0)DP.inst=0;
	else if(DP.inst>=FULLRANGE)DP.inst=FULLRANGE;
	wavetone();
}

void CSyaku8View::Dispnow(CDC *MemDC,CDC *pDC)
{
	disp1wave(MemDC,pDC);
	DispIroiro(MemDC,pDC,ISV|CDE|HER|ROT);
	DispMeterData(MemDC,pDC);
}

void CSyaku8View::HidariMigi(CDC* MemDC,CDC* pDC,int n)
{
	if(DP.f!=0)return;
	if(waveCnt<BarN){
		waveNow+=n;
		if(waveNow<0)waveNow=0;
		else if(waveNow>waveCnt)waveNow=waveCnt;
		Lt=0;
	}else if(waveCnt<SM){//バッファサイズ以下なら
		if(waveNow+n>=0&&waveNow+n<=waveCnt){//移動後の位置が範囲内なら
			waveNow+=n;
			if(n>0){
				if(waveNow-Lt>=BarN)Lt=waveNow-BarN+1;//表示範囲を右にはみ出たら
			}
			else if(waveNow-Lt<0)Lt=waveNow;//左にはみ出たら
		}else if(waveNow+n<0){
			waveNow=0;
			Lt=0;
		}else{
			waveNow=waveCnt;
			Lt=waveNow-BarN+1;
		}
	}else{
		int wc,wn;
		wc=waveCnt%SM;
		wn=waveNow;
		if(n>0){//右への移動
			if(wn+n<SM){//移動してもはみ出ない
				if(wn<=wc){//移動前は最後より左
					if(wn+n<=wc){//移動後も最後より左
						waveNow+=n;
						if(Lt<=wn&&(Lt+BarN<=waveNow))Lt=waveNow-BarN+1;
						else if(Lt>wn&&(BarN+Lt<=SM+waveNow))Lt=(waveNow-BarN+1+SM)%SM;
					}else waveNow=wc;
				}else{//移動前は最後より右
					waveNow+=n;
					if(Lt+BarN<=waveNow)Lt=waveNow-BarN+1;
				}
			}else{//はみ出る
				if(wn<=wc){//移動前は最後より左
					waveNow=wc;
				}else{//移動前は最後より右
					if((wn+n)%SM<=wc){//移動後は最後より左
						waveNow=(wn+n)%SM;
						if(wn+n>Lt+BarN)Lt=(waveNow-BarN+1+SM)%SM;
					}else {
						waveNow=wc;
					}
				}
			}
			if(waveNow==wc)Lt=(wc+SM-BarN+1)%SM;
		}else{//左への移動
			if(wn+n>=0){//移動してもはみ出ない
				if(wn>wc){//移動前は最後より右
					if(wn+n>wc){//移動後も最後より右
						waveNow+=n;
						if(Lt<=wn&&waveNow<Lt)Lt=waveNow;
					}else {
						waveNow=(wc+1)%SM;
						Lt=waveNow;
					}
				}else{
					waveNow+=n;
					if(Lt<=wn&&waveNow<Lt)Lt=waveNow;
				}
			}else{//はみ出る
				if(wn>wc){//移動前は最後より右
					waveNow=(wc+1)%SM;
					Lt=waveNow;
				}else{//移動前は最後より左
					if((wn+n+SM)<=wc){//移動後も最後より左
						waveNow=(wc+1)%SM;
						Lt=waveNow;
					}else {
						waveNow=wn+n+SM;
						if(Lt<=wn)Lt=waveNow;
						else if(Lt>wn&&waveNow<Lt)waveNow;
					}
				}
			}
		}
	}
	Dispnow(MemDC,pDC);
}

void CSyaku8View::OnHidari() 
{
	ComTable(HIDARI,-1);//HidariMigi(&MemDC,pDC,-1);
}
void CSyaku8View::OnMigi() 
{
	ComTable(HIDARI,1);
}

void disp1wave(CDC *MyDC,CDC *pDC,int flag)//,POINT *po,int numf) 
{
	int i,m,a,mode;
	static int oldmd=-1,oldwa=-1;
	char *p1,*p2,*p3,*p4,*p5;
	CPen *oldpen;
	if(DP.mode>100){
		DispZureall(MyDC,pDC);
	}else{
		if(DP.f==1)mode=DP.mode%10;
		else mode=wa[waveNow].mode%10;
		if(flag||oldmd!=DP.mode||oldwa!=wa[waveNow].mode){
			oldmd=DP.mode;
			oldwa=wa[waveNow].mode;
			pDC->FillSolidRect(18,17,526-18,251-17,RGB(255,255,255));
			if(mode==5||mode==6||mode==7){//fft
				if(mode%10==5){p1="0.5!bKHz";p2="1.0";p3="1.5";p4="2.0";p5="2.5  ";}
				else if(mode%10==6){p1="1.0!bKHz";p2="2.0";p3="3.0";p4="4.0";p5="5.0  ";}
				else {p1="2.0!bKHz";p2="4.0";p3="6.0";p4="8.0";p5="10.0  ";}
				printabc(MyDC,pDC,p1,95,232,SRCCOPY);
				printabc(MyDC,pDC,p2,95+8+93*1,232,SRCCOPY);
				printabc(MyDC,pDC,p3,95+8+93*2,232,SRCCOPY);
				printabc(MyDC,pDC,p4,95+8+93*3,232,SRCCOPY);
				printabc(MyDC,pDC,p5,95+8+93*4,232,SRCCOPY);
				pDC->BitBlt(18,232-4,508,4+4,MyDC,18,17,SRCCOPY);//fft の目盛り
		
				if(DP.low1<DP.high1){
					if(mode%10==5)a=1;
					else if(mode%10==6)a=2;
					else a=4;
					i=int(DP.low1/5.38/a+18);
					m=int(DP.high1/5.38/a+18);
					if(i<525&&m<525)pDC->FillSolidRect(i,229,m-i,2,RGB(100,100,100));
				}
				if(DP.low2<DP.high2){
					i=int(DP.low2/5.38/(mode%10-4)+18);
					m=int(DP.high2/5.38/(mode%10-4)+18);
					if(i<525&&m<525)pDC->FillSolidRect(i,229,m-i,2,RGB(100,100,100));
				}
			}
		}
		if(mode>4){
			pDC->FillSolidRect(18,17,509,212,RGB(255,255,255));
			if(fftxf){Dispiro(MyDC,pDC,fftxy,fftpeakx);fftxf=0;}
		}else{//wave
			pDC->FillSolidRect(18,17,509,235,RGB(255,255,255));
		}
		if(DP.loaddata==2){
			oldpen=(CPen*)pDC->SelectStockObject(BLACK_PEN);
			pDC->Polyline(PoTemp,WIDTHX);
			pDC->SelectObject(oldpen);	
		}
		oldpen=pDC->SelectObject(RedPen);	
		pDC->Polyline(wa[waveNow].xy ,WIDTHX);
		pDC->SelectObject(oldpen);
	}
}
void wavetone()
{
	double hz;
	hz=tone[DP.fork];
	if(hz==0)return;
	if(DP.v!=0){
		if(DP.f!=0)PlaySound(NULL,NULL,SND_PURGE);
		MakeWave(hz,DP.v);
		if(DP.f!=0){
			PlaySound((char*)snddata,NULL,SND_MEMORY|SND_ASYNC|SND_LOOP);
		}
	}
	else if(DP.v==0){
		PlaySound(NULL,NULL,SND_PURGE);
	}
}
int calf=0;

LRESULT CSyaku8View::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
		case WIM_DATA:
			CDC MemDC,*pDC=GetDC();
			int com;
			CPoint po;
			MSG		 msg;
			MMRESULT rc;
			CBitmap *pOldBmp;
			MemDC.CreateCompatibleDC(pDC);
			pOldBmp=MemDC.SelectObject(&m_bmp);
			if(wavebuf != NULL && bWaveOpened) {
				int i,j;
				SYSTEMTIME st;
				int sec;
				static int oldsec=0;
				GetLocalTime(&st);

				for(i=0; i<MAX_BUFFERS; i++) {
					if(((LPWAVEHDR)lParam)->lpData == wh[i]->lpData) break;
				}
				for(j=0; j<BUFDIV; j++) {
					CopyMemory(wavebuf+BUFSZ/BUFDIV*j,
						   wh[(i-(BUFDIV-1)+j)&(MAX_BUFFERS-1)]->lpData,
						   BUFSZ/BUFDIV*sizeof(BUFTYPE));
				}

				// データバッファブロックを再利用する
				rc = waveInPrepareHeader(hWave, (LPWAVEHDR)lParam, sizeof(WAVEHDR));
				if (rc == MMSYSERR_NOERROR)
					rc = waveInAddBuffer(hWave, (LPWAVEHDR)lParam, sizeof(WAVEHDR));
				if (rc != MMSYSERR_NOERROR) {
					CloseWaveInputDevice();
				}
				// 描画処理
				DP.bc++;
				if(DP.bc%3!=0)goto skip;
				GetCursorPos(&po);
				ScreenToClient(&po);
				com=comt[ci][16];
				if(!Checkpos(po,ci)&&ci!=ci_end){//位置がずれてたら
					if(com&ORG||com&NEX||com&UPP){//ボタンなら
						if(com&ORG||com&NEX)Dispbutton(&MemDC,pDC,ci,1);
						ci=ci_end;
					}
				}
				else if((com&TEN)&&DP.bc>5&&DP.bc%2==0&&ci!=ci_end)DoCom(&MemDC,pDC,ci,TEN);
				else if((com&FST)&&DP.bc>5            &&ci!=ci_end)DoCom(&MemDC,pDC,ci,FST);
skip:
				if(calf!=0){
					calf--;
					static bool hzf=0;
					static double hz=0;
					if(calf==22){hzf=DP.hzf;hz=DP.hz;}
					else if(calf==20){
						if(hzf==1&&DP.hzf==1&&DP.hz>tone[DP.tone]*0.9&&
							DP.hz<tone[DP.tone]*1.1&&hz<DP.hz*1.01&&hz>0.99){
								DP.hzcal=int(tone[DP.tone]/DP.hz*10000);
//								DP.hzcal=int(tone[DP.tone]/DP.hz*10000)+100000;
						}
						else{
							MessageBox(To_Recording,"to Recording control",MB_OK);
							DP.v=0;
							DispIroiro(&MemDC,pDC,VOL);
							wavetone();
						}
					}else if(calf==0){
						DP.v=0;
						DispIroiro(&MemDC,pDC,VOL);
						wavetone();
					}
				}
				if(DP.speed==2)sec=st.wMilliseconds/100;
				else if(DP.speed==1)sec=st.wMilliseconds/200;
				else if(DP.speed==0)sec=st.wMilliseconds/500;
				if(oldsec==sec)goto skip1;
				else oldsec=sec;
				if(DP.f==1){
					waveCnt++;
					Setwavehz();
					if(DP.hzf==1){//						settone();
						DispIroiro(&MemDC,pDC,ISV|ROT|HER|CDE);
					}
					else DispIroiro(&MemDC,pDC,ISV);
					disp1wave(&MemDC,pDC);//,xynow,DP.mode);
					DispMeterData(&MemDC,pDC);//,DP.hz,DP.tone,DP.cent);
				}
skip1:
				// 描画処理中に溜まった描画要求を削除する
				while( PeekMessage(&msg,m_hWnd, WIM_DATA, WIM_DATA, PM_REMOVE) ) {
					// データバッファブロックを再利用する
					rc = waveInPrepareHeader(hWave, (LPWAVEHDR)msg.lParam, sizeof(WAVEHDR));
					if (rc == MMSYSERR_NOERROR)
						rc = waveInAddBuffer(hWave, (LPWAVEHDR)msg.lParam, sizeof(WAVEHDR));
					if (rc != MMSYSERR_NOERROR) {
						CloseWaveInputDevice();
						break;
					}
				}
			}
			MemDC.SelectObject(pOldBmp);
			ReleaseDC(pDC);
			break;
	}
	return CView::WindowProc(message, wParam, lParam);
}
void delfile(char * file);
void delfile(char * file)
{
	CStdioFile f;
	if(f.Open(file,CFile::modeRead)){
		f.Close();
		CFile::Remove(file);
	}
}
void CSyaku8View::OnDestroy() 
{
	CView::OnDestroy();
	CStdioFile fr;
	delete RedPen;
	delete Red2Pen;
	delete NotPen;
	SetCurrentDirectory(curdir);
	delfile("s8data.$$$");
	PlaySound(NULL,NULL,SND_PURGE);
	if(bWaveOpened)CloseWaveInputDevice();
	// 確保していたメモリを開放
	GlobalFree( wavebuf );
	DP.dBx10=int((DP.dB+100.0)*10);
	writeini();
//	if (nTimerId){
//		timeKillEvent(nTimerId);
//		timeEndPeriod(nMs);
//	}
}

void Dispbutton(CDC *MemDC,CDC *pDC,int coi,int df)
{
	int *co,com=comt[coi][16];
	if(com&NEX&&comt[coi+1][16])co=comt[coi+1];
	else co=comt[coi];
	if(df==1)pDC->BitBlt(co[1],co[2],co[3],co[4],MemDC,co[5],co[6],SRCCOPY);
	else	 pDC->BitBlt(co[1],co[2],co[3],co[4],MemDC,co[7],co[8],SRCCOPY);
}

void Dispslide(CDC* MemDC,CDC *pDC,int coi)
{
	if(comt[ci][0]>=80)return;
	int temp,*co=comt[coi];
	temp=co[15]/1000-co[9]/2;
	if(temp<co[1])temp=co[1];
	else if(temp>co[1]+co[3]-co[9])temp=co[1]+co[3]-co[9];
	pDC->BitBlt(co[1],co[2],co[3],co[4],MemDC,co[5],co[6],SRCCOPY);
	if(temp==co[13])pDC->BitBlt(temp,co[2],co[9],co[10],MemDC,co[11],co[12],SRCCOPY);
	else pDC->BitBlt(temp,co[2],co[9],co[10],MemDC,co[7],co[8],SRCCOPY);
}

void CSyaku8View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int i;
	if(comt[i=Checkcom(point,LEF)][0]!=OWA){
		CDC MemDC,*pDC;
		pDC=GetDC();
		CBitmap *pOldBmp;
		MemDC.CreateCompatibleDC(pDC);
		pOldBmp=MemDC.SelectObject(&m_bmp);
		Butt(&MemDC,pDC,i,LEF);
		MemDC.SelectObject(pOldBmp);
		ReleaseDC(pDC);
	}
	CView::OnLButtonDown(nFlags, point);
}
void CSyaku8View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int i;
	if(comt[i=Checkcom(point,RIG)][0]!=OWA){
		CDC MemDC,*pDC;
		pDC=GetDC();
		CBitmap *pOldBmp;
		MemDC.CreateCompatibleDC(pDC);
		pOldBmp=MemDC.SelectObject(&m_bmp);
		Butt(&MemDC,pDC,i,RIG);
		MemDC.SelectObject(pOldBmp);
		ReleaseDC(pDC);
	}
	CView::OnRButtonDown(nFlags, point);
}
void CSyaku8View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDC MemDC,*pDC=GetDC();
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	int com=comt[ci][16];
	if(com&NEX||com&ORG)Dispbutton(&MemDC,pDC,ci,1);
	if(com&UPP)DoCom(&MemDC,pDC,ci,UPP);
	if(com&NEX||com&ORG)Dispbutton(&MemDC,pDC,ci,1);
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);
	ci=ci_end;
	CView::OnLButtonUp(nFlags, point);
}
void CSyaku8View::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CDC MemDC,*pDC=GetDC();
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	int com=comt[ci][16];
	if(com&RIG){
		if(com&NEX||com&ORG)Dispbutton(&MemDC,pDC,ci,1);
		if(com&UPP)DoCom(&MemDC,pDC,ci,RIG);
	}
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);
	ci=ci_end;
	CView::OnRButtonUp(nFlags, point);
}
void CSyaku8View::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int i;
	CDC MemDC,*pDC;
	pDC=GetDC();
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	if(comt[i=Checkcom(point,DOU)][0]!=OWA){
		Butt(&MemDC,pDC,i,DOU);
	}
	else if(comt[i=Checkcom(point,LEF)][0]!=OWA){
		Butt(&MemDC,pDC,i,LEF);
	}
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);
	CView::OnLButtonDblClk(nFlags, point);
}



void CSyaku8View::OnSita()
{
	if(DP.mode>100&&DP.f==0)ComTable(HIDARI,10);//HidariMigi(&MemDC,pDC,10);
	else if(DP.f==0){
		ComTable(HIDARI,10);
	}else{
		Tone(-1);
		ComTable(IROIRO,CDE|HER|ROT);//DispIroiro(&MemDC,pDC,CDE|HER|ROT);
	}
}
void CSyaku8View::OnUp()
{
	if(DP.mode>100&&DP.f==0)ComTable(HIDARI,-10);//HidariMigi(&MemDC,pDC,-10);
	else if(DP.f==0){
		ComTable(HIDARI,-10);
	}else{
		Tone(+1);
		ComTable(IROIRO,CDE|HER|ROT);
	}
}
void DispHelp(CDC* MemDC,CDC *pDC,int hlp)
{
	int static oldhlp=1000;
	if(hlp==oldhlp)return;
	oldhlp=hlp;
	pDC->BitBlt(14,507,530,17,MemDC,14,507,SRCCOPY);
	if(hlp>=ci_end)return;//17,29,30
	if(hlp==16){//
		if(DP.mode%10<5)hlp=27;
		if(DP.mode>100){
			hlp=28;
			if(DP.f==1)return;
		}
	}
#ifdef English
	printabc(MemDC,pDC,helpst[hlp],14,504,SRCAND);
#else
	printabc(MemDC,pDC,helpst[hlp],14,506,SRCAND);
#endif
//	char buf[100];
//	sprintf(buf,"%d      ",hlp);
//	printabc(MemDC,pDC,buf,1,40,SRCCOPY);
//	oldhlp=hlp;
}

void Dispiro(CDC *MemDC,CDC *pDC,int xy,int n)
{
	int tx,ty,tmx,tmy;
	short dB;
	char buf[100];
	if(xy==0)return;
	dB=wa[waveNow].dB[int((xy%10000-17)/2)];
	ty=wa[waveNow].xy[int((xy%10000-17)/2)].y;
	pDC->BitBlt(15,2,526,13,MemDC,15,2,SRCCOPY);//erase Hz
	tx=xy%10000;
	if(tx<18)tx=18;
	else if(tx>525)tx=525;
	if(ty<17)ty=17;
	if(ty<24)tmy=24;
	else if(ty>224)tmy=224;
	else tmy=ty;
	if(tx+25>525)tmx=485;//525-40;
	else if(tx-15<18)tmx=18;
	else tmx=tx-15;
	pDC->BitBlt(60,ty,466,1,MemDC,18,8,SRCCOPY);//line horizon
	sprintf(buf,"%04d!aHz",n);
	printabc(MemDC,pDC,buf,tmx,0,SRCAND);
	sprintf(buf,"%03d.%01d!adB",dB/10,dB%10);
	if(dB/10>=0)printabc(MemDC,pDC,buf,18,tmy-11,SRCAND);
	else printabc(MemDC,pDC,"-0000dB",18,tmy-11,SRCAND);
	pDC->BitBlt(tx,20,1,208,MemDC,538,19,SRCAND);//line vertical
}

void CSyaku8View::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDC MemDC,*pDC;
	pDC=GetDC();
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	int i,com=comt[ci][16];
	comt[ci][15]=point.x*1000+point.y;
	if(!((nFlags&MK_LBUTTON)||nFlags&MK_RBUTTON)){
		ci=ci_end;
		DispHelp(&MemDC,pDC,Checkcom1(point));
		for(i=0;comt[i][0]!=OWA;i++){
			if(Checkpos(point,i)){
				if(comt[i][16]&MOV&&!(comt[i][16]&DOW)){
					DoCom(&MemDC,pDC,i,MOV);
				}
			}
		}
		if(!Checkpos(point,fcom(92))){
			pDC->BitBlt(15,2,526,13,&MemDC,15,2,SRCCOPY);//erase Hz
		}
	}
	if(Checkpos(point,ci)&&ci!=ci_end){//ボタン位置がそのままなら
		if(com&MOV)DoCom(&MemDC,pDC,ci,MOV);
		if(com&SLD)Dispslide(&MemDC,pDC,ci);
	}
	else if(ci!=ci_end){//button位置が外れていたら
		if(com&ORG||com&NEX){
			Dispbutton(&MemDC,pDC,ci,1);
			ci=ci_end;
		}
		DispHelp(&MemDC,pDC,ci);
	}
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);
	CView::OnMouseMove(nFlags, point);
}

int Checkhlp(CPoint posi)
{
	int i;
	for(i=0;comt[i][0]!=0;i++){
		if(posi.x>=comt[i][1]&&
		(posi.x<=comt[i][1]+comt[i][3])&&
		posi.y>=comt[i][2]&&
		(posi.y<=comt[i][2]+comt[i][4]))break;
	}
	return i;
}
void setA440(int a)
{
	int i,A440;
	A440=(DP.A440+1000)%1000+a;
	if(A440>470)A440=470;
	else if(A440<375)A440=375;
	if(DP.A440>1000)DP.A440=1000+A440;
	else DP.A440=A440;
	tone[33]=double(A440)/2/2/2;
	for(i=33;i<TONE2+2;i++)tone[i+1]=R12*tone[i];
}
int peakx,peaky,oldpeakx,oldpeaky;
void CSyaku8View::DoCom(CDC *MyDC,CDC *pDC,int coi,int flag)
{
	int i,x=comt[coi][15]/1000,y=comt[coi][15]%1000,tvol;
	switch (comt[coi][0]){
		case  1:chakey(-1);break;
		case  2:chakey( 1);break;
		case 3:instr(-1);break;
		case 4:instr(1);break;
		case  18:
			for(i=0;i<12;i++)Keys[i]=0;//調さんの初期化
			for(i=0;i<BarN;i++)wa[i].volt=0;
			waveNow=waveCnt=0;
			DispIroiro(MyDC,pDC,ISV|LUF);
			disp1wave(MyDC,pDC,1);
			break;
		case 11:Tone(-12);break;
		case 12:Tone(-1);break;
		case 13:Tone(1);break;
		case 14:Tone( 12);break;
		case 15:
			HidariMigi(MyDC,pDC,-1);
			break;
		case 16:
			HidariMigi(MyDC,pDC,1);
			break;
		case 17:OnReturn1(MyDC,pDC);break;
		case 53:
			tvol=x-554;
			if(tvol<16)tvol=0;
			if(DP.v!=tvol){
				DP.v=tvol;
				wavetone();
			}
			break;
		case 93:
			if(DP.loaddata==1)DP.loaddata=2;
			else if(DP.loaddata==2)DP.loaddata=1;
			disp1wave(MyDC,pDC);	
			break;
		case 92:
			if(DP.mode>100&&DP.f==0){
				if(x-63<0)HidariMigi(MyDC,pDC,-10);
				else if((x-63)/7>63)HidariMigi(MyDC,pDC,10);
				else{
					waveNow=Lt+(x-63)/7;
					if(waveNow>waveCnt)waveNow=waveCnt;
					Dispnow(MyDC,pDC);
				}
				if(flag==LEF)SaveStart=waveNow;
			}else if(DP.mode%10>4&&DP.mode<100){
				if     (DP.mode%10==5)peakx=int((x-17)*5.38);
				else if(DP.mode%10==6)peakx=int((x-17)*5.38*2);
				else                  peakx=int((x-17)*5.38*4);
				if(DP.f==0){
					disp1wave(MyDC,pDC);
					Dispiro(MyDC,pDC,y*10000+x,peakx);
				}
				else{
					fftxf=1;
					fftxy=y*10000+x;
					fftpeakx=peakx;
				}
			}
			break;
		case 91:
			if(DP.f==0){//&&DP.mode!=8){
				if(x-558<0)HidariMigi(MyDC,pDC,-10);
				else if((x-552)/3>63)HidariMigi(MyDC,pDC,10);
				else{
					waveNow=Lt+(x-555)/3;
					if(waveNow>waveCnt)waveNow=waveCnt;
					Dispnow(MyDC,pDC);
				}
			}
			break;
		case 122:
			if(DP.dB>=-99)DP.dB-=1;
			else if(DP.dB>-100)DP.dB=-100;
			break;
		case 123:
			if(DP.dB<=99)DP.dB+=1;
			else if(DP.dB<100)DP.dB=100;
			break;
		case 124:if(DP.dB>-100)DP.dB-=0.1;break;
		case 125:if(DP.dB<100)DP.dB+=0.1;break;
		case 105:setA440(1);wavetone();break;
		case 106:setA440(-1);wavetone();break;
		case 110:
			if(DP.mode>100)NotesHzSave();
			else Savedata();
			break;
		case 111:
			if(DP.mode>100)Loadhzdata(MyDC,pDC);
			else Loaddata(MyDC,pDC);
			break;
		case 112:	
			if(DP.loaddata==1)DP.loaddata=2;
			else if(DP.loaddata==2)DP.loaddata=1;
			disp1wave(MyDC,pDC);
			break;
		default:
			break;
	}
	if(comt[coi][14]!=0){
		DispIroiro(MyDC,pDC,comt[coi][14]);
	}
}
void FFTWave1Calc(short *intp)
{ 
	int i,j,k,L,m,q,g,n2,n3,L2,L4,ave,wav[4096+4];
	double yreal[4096+4],yimage[4096+4],yampdata[4096+4];
	double a,b,c,s,a2,b1,dbMax;
	int nn=1;
//	int srate=DP.srate;//1:middle
//	NNn=NNN[srate];
//	NNn=4096;
	for(i=0,ave=0;i<NNN;i++){
		wav[i+1]=*(intp+i);
		ave+=wav[i+1];
	}
	ave=ave/NNN;
	for(i=0;i<NNN;i++){
		yreal[i+1]=(wav[i+1]-ave)*(0.5-0.5*cost[i]); // Hanning window
	}
//	for(i=0;i<NNn;i++){
//		yreal[i+1]=(*(intp+i))*(0.5-0.5*cost[srate][i]); // Hanning window
//		yreal[i+1]=*(intp+i) -128; // rectangle window
//	}
	yreal[i+1]=0;
	for(i=0;i<=NNN;i++)yimage[i]=0.0;
	m=(int)(log10(NNN)/log10(2));
    L=NNN;
	b1=PAI*2.00/NNN;
	nn=1;    
    for(g=1;g<=m;g++){
	 	L2=L;L=L/2;a2=0;
		for(q=1;q<=L;q++){
			c=cost[(q-1)*nn];
			s=sint[(q-1)*nn];
			a2=a2+b1;
			for(L4=L2;L4<=NNN;L4=L4+L2){
		   		i=L4-L2+q;
				j=i+L;
				a=yreal[i]-yreal[j];
				b=yimage[i]-yimage[j];
               	yreal[i]=yreal[i]+yreal[j];
				yimage[i]=yimage[i]+yimage[j];
				yreal[j]=a*c+b*s;   
				yimage[j]=b*c-a*s;
			}
        }
        b1=b1+b1;
		nn=2*nn;
    }
    // bit reversal 
    j=1;
	n2=NNN/2;
	n3=NNN-1;
    for(i=1;i<=n3;i++){
    	if(i<j){
    		a=yreal[j];
			b=yimage[j];
            yreal[j]=yreal[i];
			yimage[j]=yimage[i];
			yreal[i]=a;
			yimage[i]=b;
            k=n2;
		}
		else k=n2;
        while(k<j){
        	j=j-k;
            k=k/2;
        }
		j=j+k;
    }
    for(i=1;i<NNN/2+1;i++){
    	yreal[i]=yreal[i+1];
		yimage[i]=yimage[i+1];
    }
    for(i=1;i<NNN/2+1;i++){
		yampdata[i]=(yreal[i]*yreal[i]+yimage[i]*yimage[i]);
	}
	for(i=1,dbMax=0;i<NNN/2+1;i++)if(dbMax<yampdata[i])dbMax=yampdata[i];
	if(dbMax*1.0<=0.01)dbMax=1.0;
	b=sqrt(dbMax);
	for(i=1;i<NNN/2+1;i++){
		Amp[i]=(a=sqrt(yampdata[i]))/b*100;
		AmpdB[i]=20*log10(a);
	}
}

void CSyaku8View::OnReturn1(CDC* MemDC,CDC* pDC)//よばれるだけ
{
	int i;
	if(DP.f==0){
		for(i=0;i<12;i++)Keys[i]=0;//調さんの初期化
		DP.f=1;
		wavetone();
		comt[fcom(17)+1][16]=0;
		Dispnow(MemDC,pDC);
		DispIroiro(MemDC,pDC,CDE|HER|ROT|MHB|BTN);
	}
	else {
		DP.f=0;
		waveNow=waveCnt%SM;
		PlaySound(NULL,NULL,SND_PURGE);
		comt[fcom(17)+1][16]=1;
		if(waveCnt<BarN)Lt=0;
		else Lt=(waveNow-BarN+1+SM)%SM;
		if(waveCnt<SM){
			for(i=0;i<256;i++){
				wa[0].xy[i].y=wa[1].xy[i].y;
			}
			wa[0].cent=wa[1].cent;
			wa[0].hz=wa[1].hz;
			wa[0].tone=wa[1].tone;
			wa[0].volt=wa[1].volt;
			wa[0].mode=wa[1].mode;
		}
		Dispnow(MemDC,pDC);
		DispIroiro(MemDC,pDC,MHB|BTN);
	}
}
void CSyaku8View::OnReturn() {ComTable(RETURN1,0);}
void CSyaku8View::OnShiftret() 
{
	if(DP.f==0){
		for(int i=0;i<BarN;i++)wa[i].volt=0;
		waveNow=waveCnt=0;
		ComTable(IROIRO|RETURN1,LUF);
	}
	else ComTable(RETURN1,0);
}

void CSyaku8View::OnCdef() 
{
	DP.cdedore=0;
	ComTable(IROIRO,CDE|ROT);
}

void CSyaku8View::OnUpdateCdef(CCmdUI* pCmdUI) 
{
	if(DP.cdedore==1)pCmdUI->SetCheck(false);
	else pCmdUI->SetCheck(true);
}

void CSyaku8View::OnDore() 
{
	DP.cdedore=1;	
	ComTable(IROIRO,CDE|ROT);
}

void CSyaku8View::OnUpdateDore(CCmdUI* pCmdUI) 
{
	if(DP.cdedore==0)pCmdUI->SetCheck(false);
	else pCmdUI->SetCheck(true);
}


void CSyaku8View::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	OnRButtonDown(nFlags,point);	
	CView::OnRButtonDblClk(nFlags, point);
}

bool existname(char *n);
bool existname(char *n)
{
	CStdioFile fr;
	char buf[1000];
	int i;
	if(!fr.Open("s8data.txt",CFile::modeRead|CFile::typeText))return 0;
	for(i=0;fr.ReadString(buf,900);i++){
		if((i+9)%9==0){
			if(strstr(buf,n)&&strlen(buf)==strlen(n))return true;
		}
	}
	fr.Abort();
	return 0;
}

void delname(char *n);
void delname(char *n)
{
	CStdioFile fw,fr;
	int i;
	char buf[1000];
	if(!fr.Open("s8data.txt",CFile::modeRead|CFile::typeText))return;
	fw.Open("temp.txt",CFile::modeCreate|
				CFile::modeWrite|CFile::modeRead|CFile::typeText);
	while(fr.ReadString(buf,900)){
		if(strstr(buf,n)&&strlen(buf)==strlen(n)){
			for(i=0;i<8;i++)fr.ReadString(buf,900);
		}
		else fw.WriteString(buf);
	}
	fr.Abort();
	fw.Abort();
	CFile::Remove("s8data.txt");
	CFile::Rename("temp.txt","s8data.txt");
}
int gety(int i,char *buf);
int gety(int i,char *buf)
{
	int a,b;
	a=buf[i*2]-0x30;
	b=buf[i*2+1]-0x30;
	if(a>9)a=buf[i*2]-'a'+10;
	if(b>9)b=buf[i*2+1]-'a'+10;
	return a*16+b;
}
void Savedata(void)
{
	CStdioFile fw,f;
	int i,j;
	char buf[300],b[100],name[300];
	CSaveData dlg;
	SetCurrentDirectory(curdir);
	strcpy(name,curdir);
	strcat(name,"\\data\\");
	dlg.m_title="Set the name of Wave-FFT";
	while(1){
		if(dlg.DoModal()==IDOK){
			if(strlen(LPCTSTR(dlg.m_WAVENAME))<1){
				MessageBox(NULL,Unusable_name,"caution",MB_OK);
				continue;
			}
			sprintf(name,"%s\\data\\%s.s8w",curdir,LPCTSTR(dlg.m_WAVENAME));
			if(f.Open(name,CFile::modeRead)){
				if(MessageBox(NULL,Over_write,"caution",MB_OKCANCEL)==IDOK){
					f.Close();
					CFile::Remove(name);
					break;
				}
				else continue;
			}
			else break;
		}
		else return;
	}
	if(fw.Open(name,CFile::modeCreate|
		CFile::modeWrite|CFile::modeRead|CFile::typeText)){
		for(i=0;i<256/32;i++){
			buf[0]=0;
			for(j=0;j<32;j++){
				sprintf(b,"%02x",wa[waveNow].xy[i*32+j].y);
				strcat(buf,b);
			}
			strcat(buf,"\n");
			fw.WriteString(buf);
		}
	}else return;
	fw.Abort();
}

void CSyaku8View::Loadhzdata(CDC* MemDC,CDC *pDC)
{
	int i,j,k=0,i1,i2,len,result;
	char c,fn[300],buf[130];
	CString str;
	CStdioFile fr;
	sprintf(fn,"%s\\data",curdir);
	SetCurrentDirectory(fn);
	CFileDialog fdlg(TRUE,NULL,NULL,OFN_LONGNAMES,"sounddata(*.s8d)|*.s8d||",NULL);
	result=fdlg.DoModal();
	if(result==IDOK){
		strcpy(fn,LPCTSTR(fdlg.GetPathName()));
	}
	else return;
	fr.Open(fn,CFile::modeRead|CFile::typeText);
	fr.ReadString(buf,127);
	sscanf(buf,"A:%d Inst:%d Sun:%d Oca:%d Sino:%d",&DP.A440,&DP.inst,&DP.sn,&DP.oca,&DP.sino);
	setA440(0);
	while(fr.ReadString(buf,127)){
		len=strlen(buf);
		for(i=0;(i*7+2)<len;i++){
			if(buf[i*7]=='o'){wa[k].tone=20;wa[k].hz=0;wa[k].cent=-127*2;}
			else{
				sscanf(&buf[i*7],"%c%d:%d",&c,&i1,&i2);
				for(j=0;j<12;j++)if(songt[j]==c)break;
				j=j+(i1+1)*12;
				wa[k].tone=j;
				wa[k].cent=i2*2;
				wa[k].hz=int(1000*tone[j]*pow(1.00057779,i2));
			}
			k++;
		}
	}
	waveCnt=k-1;
	waveNow=0;
	SaveStart=-1;
	DP.tone=wa[waveNow].tone;
	if(DP.f==1)OnReturn1(MemDC,pDC);
	DispIroiro(MemDC,pDC,LUF);
	Lt=0;
	Dispnow(MemDC,pDC);
}
void Loaddata(CDC* MemDC,CDC *pDC) 
{
	int i,j,m,result;
	char fn[300],buf[300];
	CStdioFile fr;
	sprintf(fn,"%s\\data",curdir);
	SetCurrentDirectory(fn);
	CFileDialog fdlg(TRUE,NULL,NULL,OFN_LONGNAMES,"sounddata(*.s8w)|*.s8w||",NULL);
	result=fdlg.DoModal();
	if(result==IDOK){
		strcpy(fn,LPCTSTR(fdlg.GetPathName()));
	}
	else return;
	fr.Open(fn,CFile::modeRead|CFile::typeText);
	for(i=0;i<256/32;i++){
		fr.ReadString(buf,295);
		for(j=0;j<32;j++){
			m=i*32+j;
			PoTemp[m].y=gety(j,buf);	
		}
	}
	fr.Abort();
	DP.loaddata=2;
	if(DP.f==0)disp1wave(MemDC,pDC);
}
void CSyaku8View::OnA440() 
{
	if(DP.A440>1000)DP.A440-=1000;
	else DP.A440+=1000;
}

void CSyaku8View::OnUpdateA440(CCmdUI* pCmdUI) 
{
	if(DP.A440>1000)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}

void CSyaku8View::OnFft0() 
{
	DP.speed=0;	
}

void CSyaku8View::OnFft1() 
{
	DP.speed=1;	
}

void CSyaku8View::OnFft2() 
{
	DP.speed=2;
}

void CSyaku8View::OnUpdateFft0(CCmdUI* pCmdUI) 
{
	if(DP.speed==0)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void CSyaku8View::OnUpdateFft1(CCmdUI* pCmdUI) 
{
	if(DP.speed==1)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void CSyaku8View::OnUpdateFft2(CCmdUI* pCmdUI) 
{
	if(DP.speed==2)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}



void CSyaku8View::OnW0() 
{
	DP.mode=1;
	ComTable(IROIRO|DISPNOW,LUF|MHB);
}
void CSyaku8View::OnUpdateW0(CCmdUI* pCmdUI) 
{
	if(DP.mode==1)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}

void CSyaku8View::OnW1() 
{
	DP.mode=2;
	ComTable(IROIRO|DISPNOW,LUF|MHB);
}

void CSyaku8View::OnUpdateW1(CCmdUI* pCmdUI) 
{
	if(DP.mode==2)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void CSyaku8View::OnW2() 
{
	DP.mode=4;
	ComTable(IROIRO|DISPNOW,LUF|MHB);
}

void CSyaku8View::OnUpdateW2(CCmdUI* pCmdUI) 
{
	if(DP.mode==4)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}

void CSyaku8View::On00snt() {DP.blue=0;}
void CSyaku8View::OnUpdate00snt(CCmdUI* pCmdUI) 
{
	if(DP.blue==0)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void CSyaku8View::On10snt() {DP.blue=1;}
void CSyaku8View::OnUpdate10snt(CCmdUI* pCmdUI) 
{
	if(DP.blue==1)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void CSyaku8View::On20snt() {DP.blue=2;}
void CSyaku8View::OnUpdate20snt(CCmdUI* pCmdUI) 
{
	if(DP.blue==2)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void CSyaku8View::On30snt(){DP.blue=3;}
void CSyaku8View::OnUpdate30snt(CCmdUI* pCmdUI) 
{
	if(DP.blue==3)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void NotesHzSave()
{
	char sc,name[300],name_sub[300],name_sub1[300],data[100],data1[50];
	char *gakki[26]={"KINKO","TOZAN","NANAKOU","SINOBUE","NOUKAN","OCARINA","OCARINA4","FLUTE","CLARINET",
					"TRUMPET","SOPRANOSAX","ALTOSAX","TENORSAX","TROMBONE","F-HORN",
					"B-HORN","RECORDER","OBOE","TIN_WHISTLE","BANSURI","FULLRANGE","??","??"};
	CStdioFile f;
	int i,j,cent,st,en;
	CSaveData dlg;
	if(SaveStart==-1||SaveStart==waveNow){
		MessageBox(NULL,Set_area,"caution",MB_OK);
		return;
	}
//	SetCurrentDirectory(curdir);
	dlg.m_title="Set the name of Notes";
	while(1){
		if(dlg.DoModal()==IDOK){
			if(strlen(LPCTSTR(dlg.m_WAVENAME))<1){
				MessageBox(NULL,Unusable_name,"caution",MB_OK);
				continue;
			}
			sprintf(name,"%s\\data\\%s.s8d",curdir,LPCTSTR(dlg.m_WAVENAME));
			sprintf(name_sub,"%s\\data\\%s.txt",curdir,LPCTSTR(dlg.m_WAVENAME));
			sprintf(name_sub1,"%s\\data\\%s_hz.txt",curdir,LPCTSTR(dlg.m_WAVENAME));
			if(f.Open(name,CFile::modeRead)){
				if(MessageBox(NULL,Over_write,"caution",MB_OKCANCEL)==IDOK){
					f.Close();
					CFile::Remove(name);
					break;
				}
				else continue;
			}
			else break;
		}
		else return;
	}
	if(waveCnt<SM){
		if(SaveStart<waveNow){st=SaveStart;en=waveNow;}
		else {en=SaveStart;st=waveNow;}
	}else{
		int wc=waveCnt%SM;
		if((SaveStart<=wc&&waveNow<=wc)||(SaveStart>wc&&waveNow>wc)){
			if(SaveStart<waveNow){st=SaveStart;en=waveNow;}
			else {en=SaveStart;st=waveNow;}
		}else{
			if(SaveStart<waveNow){en=SaveStart;st=waveNow;}
			else {st=SaveStart;en=waveNow;}
			en=SM+en;
		}
	}

	if(f.Open(name,CFile::modeCreate|
		CFile::modeWrite|CFile::modeRead|CFile::typeText)){
		if(checkinst(DP.inst)){
			sprintf(data,"A:%d Inst:%s\n",DP.A440,gakki[DP.inst]);
		}else{
			int key;
			if(DP.inst==OCARINA)key=DP.oca;
			else if(DP.inst==OCARINA4)key=DP.oca4;
			else if(DP.inst==KINKO||DP.inst==TOZAN||DP.inst==NANAKOU)key=DP.sn;
			else if(DP.inst==SINOBUE)key=DP.sino;
			else if(DP.inst==TIN)key=DP.tin;
			else key=DP.voca;
			sprintf(data,"A:%d Inst:%s Key:%d\n",DP.A440,gakki[DP.inst],key);
		}
		f.WriteString(data);
		j=0;data[0]=0;
		for(i=st;i<=en;i++){
			cent=wa[(i+SM)%SM].cent/2;
			sc=wa[(i+SM)%SM].tone;//songtone[i];
			if(cent<0&&cent>-99)
				sprintf(data1,"%c%d:-%02d ",songt[sc%12],sc/12-1,-cent);
			else if(cent>=0&&cent<99)
				sprintf(data1,"%c%d:+%02d ",songt[sc%12],sc/12-1,cent);
			else 
				strcpy(data1,"oo:ooo ");
			strcat(data,data1);
			j++;
			if(j>=10||i==en){
				strcat(data,"\n");
				f.WriteString(data);
				j=0;data[0]=0;
			}
		}
		f.Abort();
	}else MessageBox(NULL,strcat(name," can't be open"),"Shakuhachi tuner",MB_OK);
	if(f.Open(name_sub,CFile::modeCreate|
		CFile::modeWrite|CFile::modeRead|CFile::typeText)){
		if(checkinst(DP.inst)){
			sprintf(data,"A:%d Inst:%s\n",DP.A440,gakki[DP.inst]);
		}else{
			int key;
			if(DP.inst==OCARINA)key=DP.oca;
			else if(DP.inst==OCARINA4)key=DP.oca4;
			else if(DP.inst==KINKO||DP.inst==TOZAN||DP.inst==NANAKOU)key=DP.sn;
			else if(DP.inst==SINOBUE)key=DP.sino;
			else if(DP.inst==TIN)key=DP.tin;
			else key=DP.voca;
			sprintf(data,"A:%d Inst:%s Key:%d\n",DP.A440,gakki[DP.inst],key);
		}
		f.WriteString(data);
		j=0;data[0]=0;
		for(i=st;i<=en;i++){
			cent=wa[(i+SM)%SM].cent/2;
			sc=wa[(i+SM)%SM].tone;//songtone[i];
			if(cent<99&&cent>-99)sprintf(data1,"%c%d ",songt[sc%12],sc/12-1);
			else	strcpy(data1,"oo ");
			strcat(data,data1);
			j++;
			if(j>=10||i==en){
				strcat(data,"\n");
				f.WriteString(data);
				j=0;data[0]=0;
			}
		}
		f.Abort();
	}else MessageBox(NULL,strcat(name_sub," can't be open"),"Shakuhachi tuner",MB_OK);
	if(f.Open(name_sub1,CFile::modeCreate|
		CFile::modeWrite|CFile::modeRead|CFile::typeText)){
		f.WriteString("Herz:dB\n");
		for(i=st;i<=en;i++){
			j=(i+SM)%SM;
			sprintf(data,"%04d:%03d ",int(wa[j].hz),int(wa[j].volt));
			if((j-st)%10==0)f.WriteString("\n");//strcat(data,"\n");
			f.WriteString(data);
		}
		f.Abort();
	}else MessageBox(NULL,strcat(name_sub1," can't be open"),"Shakuhachi tuner",MB_OK);
}

void CSyaku8View::On2700() 
{
	DP.mode=5;
	ComTable(IROIRO|DISPNOW,LUF|MHB);
}

void CSyaku8View::OnUpdate2700(CCmdUI* pCmdUI) 
{
	if(DP.mode==5)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}

void CSyaku8View::On5400() 
{
	DP.mode=6;
	ComTable(IROIRO|DISPNOW,LUF|MHB);
}

void CSyaku8View::OnUpdate5400(CCmdUI* pCmdUI) 
{
	if(DP.mode==6)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}

void CSyaku8View::On10800() 
{
	DP.mode=7;
	ComTable(IROIRO|DISPNOW,LUF|MHB);
}

void CSyaku8View::OnUpdate10800(CCmdUI* pCmdUI) 
{
	if(DP.mode==7)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void CSyaku8View::On2700log() 
{
	DP.mode=15;
	ComTable(IROIRO|DISPNOW,LUF|MHB);
}
void CSyaku8View::OnUpdate2700log(CCmdUI* pCmdUI) 
{
	if(DP.mode==15)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void CSyaku8View::On5400log() 
{
	DP.mode=16;
	ComTable(IROIRO|DISPNOW,LUF|MHB);
}
void CSyaku8View::OnUpdate5400log(CCmdUI* pCmdUI) 
{
	if(DP.mode==16)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void CSyaku8View::On10800log() 
{
	DP.mode=17;
	ComTable(IROIRO|DISPNOW,LUF|MHB);
}
void CSyaku8View::OnUpdate10800log(CCmdUI* pCmdUI) 
{
	if(DP.mode==17)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}
void CSyaku8View::OnPagedown() 
{
	if(DP.f==0){
		CDC MemDC,*pDC=GetDC();
		CBitmap *pOldBmp;
		MemDC.CreateCompatibleDC(pDC);
		pOldBmp=MemDC.SelectObject(&m_bmp);
		HidariMigi(&MemDC,pDC,60);
		MemDC.SelectObject(pOldBmp);
		ReleaseDC(pDC);
	}else{
		DP.logref++;
		if(DP.logref>300)DP.logref=300;
	}
}

void CSyaku8View::OnPageup() 
{
	if(DP.f==0){
		CDC MemDC,*pDC=GetDC();
		CBitmap *pOldBmp;
		MemDC.CreateCompatibleDC(pDC);
		pOldBmp=MemDC.SelectObject(&m_bmp);
		HidariMigi(&MemDC,pDC,-60);
		MemDC.SelectObject(pOldBmp);
		ReleaseDC(pDC);
	}	else{
		DP.logref--;
		if(DP.logref<0)DP.logref=0;
	}
}

/*
void CSyaku8TunerView::OnSoundcard() 
{
	CCalibrate dlg;
	DP.f=true;
	SetButtons();
	DP.A440=440;
	MakeWave(440.0);
	PlaySound((char*)snddata,NULL,SND_MEMORY|SND_ASYNC|SND_LOOP);
	if(dlg.DoModal()==IDOK){

	}
	PlaySound(NULL,NULL,SND_PURGE);
}
void CCalibrate::OnCaliCali() 
{
	DP.hzcal=10000;
	SetTimer(1,200,NULL);
}

void CCalibrate::OnResetcali() 
{
	DP.hzcal=10000;
}

BOOL CCalibrate::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if(zDelta>0)DP.hzcal+=1;
	else DP.hzcal-=1;
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CCalibrate::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==1){
		KillTimer(1);
		DP.hzcal=int(tone[DP.tone]/DP.hz*10000);
		if(DP.hzcal>11000)DP.hzcal=11000;
		else if(DP.hzcal<9000)DP.hzcal=9000;
	}
	CDialog::OnTimer(nIDEvent);
}
*/
void CSyaku8View::OnSndcard() 
{
	DP.f=1;
	DP.v=100;
	DP.tone=69;
	DP.fork=69;
	DP.hzcal=10000;
	DP.mode=16;
	DP.speed=2;
	DP.inst=KINKO;
	wavetone();
	ComTable(IROIRO,CDE|HER|ROT|MHB|VOL|INS);
	calf=40;
}
void CSyaku8View::ComTable(int nani,int n)
{
	CDC MemDC,*pDC=GetDC();
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	if(nani&IROIRO)DispIroiro(&MemDC,pDC,n);
	if(nani&DISPNOW)Dispnow(&MemDC,pDC);
	if(nani&HIDARI)HidariMigi(&MemDC,pDC,n);
	if(nani&RETURN1)OnReturn1(&MemDC,pDC);
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);
}
void CSyaku8View::setinst(int inst)
{
	DP.inst=inst;
	ComTable(IROIRO,MHB|ROT|INS);
	wavetone();
}
void updateinst(int inst,CCmdUI* cmdui);
void updateinst(int inst,CCmdUI* cmdui)
{
	if(DP.inst==inst)cmdui->SetCheck(true);
	else cmdui->SetCheck(false);
}
void CSyaku8View::Onjust() {setinst(NANAKOU);}
void CSyaku8View::OnUpdatejust(CCmdUI* pCmdUI) {updateinst(NANAKOU,pCmdUI);}

void CSyaku8View::Onnoukan(){setinst(NOUKAN);} 
void CSyaku8View::OnUpdatenoukan(CCmdUI* pCmdUI){updateinst(NOUKAN,pCmdUI);} 

void CSyaku8View::Onbhorn(){setinst(BHORN);} 
void CSyaku8View::OnUpdatebhorn(CCmdUI* pCmdUI) {updateinst(BHORN,pCmdUI);}

void CSyaku8View::Ontenorsax(){setinst(TENORSAX);} 
void CSyaku8View::OnUpdatetenorsax(CCmdUI* pCmdUI){updateinst(TENORSAX,pCmdUI);} 

void CSyaku8View::Onsopranosax(){setinst(SOPRANOSAX);} 
void CSyaku8View::OnUpdatesopranosax(CCmdUI* pCmdUI){updateinst(SOPRANOSAX,pCmdUI);} 

void CSyaku8View::Ontrumpet(){setinst(TRUMPET);} 
void CSyaku8View::OnUpdatetrumpet(CCmdUI* pCmdUI){updateinst(TRUMPET,pCmdUI);} 

void CSyaku8View::Ontrombone(){setinst(TROMBONE);} 
void CSyaku8View::OnUpdatetrombone(CCmdUI* pCmdUI){updateinst(TROMBONE,pCmdUI);} 

void CSyaku8View::Ontozan(){setinst(TOZAN);}
void CSyaku8View::OnUpdatetozan(CCmdUI* pCmdUI){updateinst(TOZAN,pCmdUI);} 

void CSyaku8View::Onaltosax() {setinst(ALTOSAX);}
void CSyaku8View::OnUpdatealtosax(CCmdUI* pCmdUI){updateinst(ALTOSAX,pCmdUI);} 

void CSyaku8View::Onclarinet() {setinst(CLARINET);}
void CSyaku8View::OnUpdateclarinet(CCmdUI* pCmdUI){updateinst(CLARINET,pCmdUI);} 

void CSyaku8View::Onflute(){setinst(FLUTE);} 
void CSyaku8View::OnUpdateflute(CCmdUI* pCmdUI){updateinst(FLUTE,pCmdUI);} 

void CSyaku8View::Onhorn(){setinst(FHORN);} 
void CSyaku8View::OnUpdatehorn(CCmdUI* pCmdUI){updateinst(FHORN,pCmdUI);} 

void CSyaku8View::Onkinko(){setinst(KINKO);}  
void CSyaku8View::OnUpdatekinko(CCmdUI* pCmdUI){updateinst(KINKO,pCmdUI);}  

void CSyaku8View::Onocarina(){setinst(OCARINA);}  
void CSyaku8View::OnUpdateocarina(CCmdUI* pCmdUI){updateinst(OCARINA,pCmdUI);}  

void CSyaku8View::Onrecorder(){setinst(RECORDER);}  
void CSyaku8View::OnUpdaterecorder(CCmdUI* pCmdUI){updateinst(RECORDER,pCmdUI);}  

void CSyaku8View::Onsinobue(){setinst(SINOBUE);}  
void CSyaku8View::OnUpdatesinobue(CCmdUI* pCmdUI) {updateinst(SINOBUE,pCmdUI);} 

void CSyaku8View::Onoboe(){setinst(OBOE);} 
void CSyaku8View::OnUpdateoboe(CCmdUI* pCmdUI){updateinst(OBOE,pCmdUI);}  

void CSyaku8View::Onfullrange(){setinst(FULLRANGE);} 
void CSyaku8View::OnUpdatefullrange(CCmdUI* pCmdUI){updateinst(FULLRANGE,pCmdUI);} 
void CSyaku8View::OnS() 
{
	CDC MemDC,*pDC=GetDC();
	CBitmap *pOldBmp;
	if(DP.ondo==1)DP.ondo=0;
	else DP.ondo=1;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	DispIroiro(&MemDC,pDC,A44);
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);
}

void CSyaku8View::OnJuns8() 
{
	if(DP.juns8==1)DP.juns8=0;
	else DP.juns8=1;
}

void CSyaku8View::OnUpdateJuns8(CCmdUI* pCmdUI) 
{
	if(DP.juns8==1)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);	
}

void CSyaku8View::OnC() 
{
mycheck++;
if(mycheck==2)mycheck=0;	
}
void CSyaku8View::OnNoteshz() 
{
	CDC MemDC,*pDC=GetDC();
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	DispIroiro(&MemDC,pDC,LUF);
	DP.mode=DP.mode%100+100;
	DispIroiro(&MemDC,pDC,MHB);
	Dispnow(&MemDC,pDC);
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);
	setcomf();
}

void CSyaku8View::OnUpdateNoteshz(CCmdUI* pCmdUI) 
{
	if(DP.mode>100&&DP.mode<200)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);	
}
void CSyaku8View::OnNoteshzlimit() 
{
	CDC MemDC,*pDC=GetDC();
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	DispIroiro(&MemDC,pDC,LUF);
	DP.mode=DP.mode%100+200;
	DispIroiro(&MemDC,pDC,MHB);
	Dispnow(&MemDC,pDC);
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);
	setcomf();
}

void CSyaku8View::OnUpdateNoteshzlimit(CCmdUI* pCmdUI) 
{
	if(DP.mode>200)pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);	
}
void CSyaku8View::Ontin(){setinst(TIN);}
void CSyaku8View::OnUpdatetin(CCmdUI* pCmdUI) {updateinst(TIN,pCmdUI);}

void CSyaku8View::Onocarina4(){setinst(OCARINA4);}
void CSyaku8View::OnUpdateocarina4(CCmdUI* pCmdUI) {updateinst(OCARINA4,pCmdUI);}

void CSyaku8View::Onbansuri(){setinst(BANSURI);}
void CSyaku8View::OnUpdatebansuri(CCmdUI* pCmdUI) {updateinst(BANSURI,pCmdUI);}
typedef struct
{
	int fs; // 標本化周波数 //
	int bits; // 量子化精度 //
	int length; // 音データの長さ //
	double *s; // 音データ //
} MONO_PCM;

void mwrite(void* buffer, int size, int count);
void mwrite(void* buffer, int size, int count)
{
	int i;
	unsigned char* ucp;
	static int pt;
	if(size==0){
		pt=0;
		return;
	}
	ucp=(unsigned char*)buffer;
	for(i=0;i<size*count;i++)snddata[pt++]=ucp[i];
}
void mono_wave_write(MONO_PCM *pcm)
{
	int n;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char riff_form_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short fmt_wave_format_type;
	short fmt_channel;
	long fmt_samples_per_sec;
	long fmt_bytes_per_sec;
	short fmt_block_size;
	short fmt_bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	short data;
	double s;
  
	riff_chunk_ID[0] = 'R';
	riff_chunk_ID[1] = 'I';
	riff_chunk_ID[2] = 'F';
	riff_chunk_ID[3] = 'F';
	riff_chunk_size = 36 + pcm->length * 2;
	riff_form_type[0] = 'W';
	riff_form_type[1] = 'A';
	riff_form_type[2] = 'V';
	riff_form_type[3] = 'E';
  
	fmt_chunk_ID[0] = 'f';
	fmt_chunk_ID[1] = 'm';
	fmt_chunk_ID[2] = 't';
	fmt_chunk_ID[3] = ' ';
	fmt_chunk_size = 16;
	fmt_wave_format_type = 1;
	fmt_channel = 1;
	fmt_samples_per_sec = pcm->fs; /* 標本化周波数 */
	fmt_bytes_per_sec = pcm->fs * pcm->bits / 8;
	fmt_block_size = pcm->bits / 8;
	fmt_bits_per_sample = pcm->bits; /* 量子化精度 */
  
	data_chunk_ID[0] = 'd';
	data_chunk_ID[1] = 'a';
	data_chunk_ID[2] = 't';
	data_chunk_ID[3] = 'a';
	data_chunk_size = pcm->length * 2;

	mwrite(riff_chunk_ID, 0, 0);//reset pointer

	mwrite(riff_chunk_ID, 1, 4);
	mwrite(&riff_chunk_size, 4, 1);
	mwrite(riff_form_type, 1, 4);
	mwrite(fmt_chunk_ID, 1, 4);
	mwrite(&fmt_chunk_size, 4, 1);
	mwrite(&fmt_wave_format_type, 2, 1);
	mwrite(&fmt_channel, 2, 1);
	mwrite(&fmt_samples_per_sec, 4, 1);
	mwrite(&fmt_bytes_per_sec, 4, 1);
	mwrite(&fmt_block_size, 2, 1);
	mwrite(&fmt_bits_per_sample, 2, 1);
	mwrite(data_chunk_ID, 1, 4);
	mwrite(&data_chunk_size, 4, 1);
  
	for (n = 0; n < pcm->length; n++)
	{
		s = (pcm->s[n] + 1.0) / 2.0 * 65536.0;
    
		if (s > 65535.0)
		{
		  s = 65535.0; /* クリッピング */
		}
		else if (s < 0.0)
		{
		  s = 0.0; /* クリッピング */
		}
    
		data = (short)(s + 0.5) - 32768; /* 四捨五入とオフセットの調節 */
	//  fwrite(&data, 2, 1, fp); /* 音データの書き出し */
		mwrite(&data, 2, 1);
	}
	//  fclose(fp);
}
//	vol=vol-16;if(vol<1)vol=1;if(vol>127)vol=127;

void MakeWave(double f0,int vol) 
{
	MONO_PCM pcm;
	int n;
	double A;//, f0;
  
	pcm.fs = 8000;// 標本化周波数/
	pcm.bits = 16; // 量子化精度 
	pcm.length = 40000; // 音データの長さ //
	pcm.s =(double*) calloc(pcm.length, sizeof(double)); // メモリの確保 
	vol=vol-16;
	if(vol<1)vol=1;
	else if(vol>180)vol=180;
	A=double(vol)/180.0;
//	A = 0.8; // 振幅 //
//	f0 = 440.0; // 基本周波数 //
  
	// サイン波 //
	for (n = 0; n < pcm.length; n++)
	{
		pcm.s[n] = A * sin(2.0 * 3.141592653589793238 * f0 * n / pcm.fs);
	}
  
	mono_wave_write(&pcm); // WAVE配列にモノラルの音データを出力する //
  
	free(pcm.s); // メモリの解放 //
}
