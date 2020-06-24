//tuner.h
#define English
#define IROIRO 1//)DispIroiro(&MemDC,pDC,n);
#define DISPNOW 2//)Dispnow(&MemDC,pDC);
#define HIDARI 4//)HidariMigi(&MemDC,pDC,n);
#define RETURN1 8//)OnReturn1(&MemDC,pDC);
#define CHECK 0//1:周波数関連 2:wav[i]の最大最小
#define BarN 64
#define SM 1100
#define AMXCENTER 272//146;
#define AMYCENTER 502 //260;
#define WIDTHX 255
#define KINKO 0
#define TOZAN 1
#define NANAKOU 2
#define SINOBUE 3
#define NOUKAN 4
#define OCARINA 5
#define OCARINA4 6
#define FLUTE 7
#define CLARINET 8
#define TRUMPET 9
#define SOPRANOSAX 10
#define ALTOSAX 11
#define TENORSAX 12
#define TROMBONE 13
#define FHORN 14
#define BHORN 15
#define RECORDER 16
#define OBOE 17
#define TIN 18
#define BANSURI 19
#define FULLRANGE 20
#define OUTKEY 999
#define romaX 591 
#define romaY 115
#define abcX 559 
#define abcY 442
#define unX 554
#define unY 311
#define nameX 554
#define nameY 450-8
#define blueX 557
#define blueY 166
#define whiteX 555
#define whiteY 110
#define blackX 553
#define blackY 82
#define grayX 551
#define grayY 80
#define redX 554
#define redY 83
#define yellowX 517
#define yellowY 32
#define DOW 1//downで実行
#define UPP 2//upで実行
#define MOV 4//moveで実行、
#define SLD 8//スライド表示
#define TEN 16//DP.c>10で実行slow
#define FST 32//DP.c>10で実行fast
#define LEF 64//leftで実行
#define RIG 128//rightで実行
#define DOU 256//doubleclickで実行
#define ORG 512//そこのボタン表示
#define NEX 1024//次のボタン表示
#define UDO 2048//なにもしない
#define OWA 999999//the end
/////////
#define FRA 1//frame
#define ISV 2//input sound vol
#define CDE 8//cdefgabc
#define HER 32//herz
#define ROT 64//roture
#define INS 128//instrument
#define MHB 256//button
#define BTN 512//button
#define VOL 1024//volume
#define A44 2048//pitch of A
#define LUF 4096//clear Left Upper Frame
#define NUM 8192//for check
#define ALL 0xFFFFF

#define NYQUIST			11025
#define BUFSZ			8192			// DRAWWIDTH よりも十分に大きい 2^n
#define BUFDIV			(BUFSZ/1024)	// サンプリングの際のbuf分割数
#define MAX_BUFFERS		8				// BUFDIV よりも十分に大きい 2^n
typedef	SHORT BUFTYPE;					// 量子化ビット数=16bits/sample
//*******************************************************************
// グローバル変数
//*******************************************************************

struct DATADP{
	int logref;
	int hzcal;
	double dB;
	int dBx10;//=dB*10
	bool hzf;//Hz disp f
	int hzold;//hz hari meter old
	short cent;
	double hz;
	double volt;
	int A440;//A=442 440
	int v;//WAVE音量
	int tone;//音高
	int fork;//Tuning fork の音高
//	int wavetype;//ウェーブ音の種類
	int inst;//楽器
	int sn;//syaku8 key寸
	int oca;//ocarina key
	int oca4;
	int bansuri;
	int reco;//recorder key
	int voca;//full range key
	int sino;//sinobue 調子
	int tin;//tin whistle key
	int bc;//button count
	int f;//disp flag
//	int manuauto;//calc mode
	int mode;
	int low1;
	int high1;
	int low2;
	int high2;
	int peaklevel;
	int speed;//サンプリングレート
	int cdedore;
	int loaddata;
	int blue;
	int juns8;
	int ondo;
	int winx1;
	int winy1;
	int winx2;
	int winy2;
};

bool checkinst(int n);
void unsi(CDC* MemDC,CDC* pDC,int tn,int flag);
void unsi1(CDC* MemDC,CDC* pDC,int tn,int flag);
void FFTWave1Calc(short *intp);
void DrawInit();
int fcom(int n);
void Num(CDC* MemDC,CDC* pDC,int n,int x,int y,int keta,int numb,int f=SRCCOPY);
void DispMeterData(CDC *MemDC,CDC *pDC);
void DispHelp(CDC *pDC,int hlp);
void DispDB(CDC* MemDC,CDC* pDC,double volt=99.9);
void DispBarall(CDC* MemDC,CDC* pDC,double *volt);
void Dispiro(CDC *MemDC,CDC *pDC,int xy=0,int n=0);
void disp1wave(CDC *MemDC,CDC *pDC,int flag=0);
void InsPict(CDC* MemDC,CDC* pDC,int a1,int b1,int da,int db,int a3,int b3,int x,int y,int dx,int dy);
void writeini();
int Checkcom(CPoint posi,int c=LEF);
int Checkpos(CPoint posi,int i);
int Checkcom1(CPoint posi);
int Checkhlp(CPoint posi);
void Dispslide(CDC* MemDC,CDC *pDC,int coi);
void Dispbutton(CDC* MemDC,CDC *pDC,int coi,int df);
void disptemp(CDC *pDC,int f);
void Dispundisp(CDC *pDC); 
void Loaddata(CDC *MemDC,CDC *pDC); 
void Savedata(void); 
void setA440(int a);
bool TestOpenInputDevice();
void wavetone();
void NotesHzSave();
void printinkey(CDC* MemDC,CDC* pDC,int tn);
void DispInstName(CDC* MemDC,CDC* pDC);
void Disp12abs(CDC* MemDC,CDC* pDC,int a,int b,int da,int db,int n,int x,int y,int x1,int y1,int sx,int sy,int sx1=0,int sy1=0,int sx2=0,int sy2=0);
void Disp12(CDC* MemDC,CDC* pDC,int a,int b,int da,int db,int n,int x,int y,int x1,int y1,int sx,int sy);
void printabc(CDC* MemDC,CDC* pDC,char *p,int x,int y,int f=SRCCOPY);
bool OpenWaveInputDevice(HWND);
void CloseWaveInputDevice(void);
void StartRecording(void);
void writeini();
bool readini();
