#include "my_headers.h"

/*----------------------------- GLOBAL NUMERICS -----------------------------*/
float	d[WORD_NUMBER][TOTAL_FRAME][DIMENSION] = { };
float	g[WORD_NUMBER][TOTAL_FRAME][DIMENSION] = { };

struct {
	float	DATA;
	int		NUM;
}MIN;

typedef struct echo {
	int		FRAME;
	float	DATA[100][15];
}echo_data;

echo_data	DATA1[100] = {};
echo_data	DATA2[100] = {};
/*----------------------------- GLOBAL NUMERICS -----------------------------*/

int main()
{
/*-------------------------------- NUMERICS ---------------------------------*/
	int		tmp = 0;								//一時読み出し用
	int		frame = 0;								//一時読み出し用
	int		cnt = 0;
	int		i = 0;
	int		j = 0;
	int		k = 0;
	int		x = 0;
	int		y = 0;
	char	load_directory[TXT_CAPACITY] = {  };	//一時読み出し用
	char	answer = 0;
	const char	*buff_frame;
	FILE	*fp1 = { };
	ostringstream directory;
/*-------------------------------- NUMERICS ---------------------------------*/



/*-------------------------------- PROGRAMS ---------------------------------*/

	/*
	*** ファイル選択アルゴリズム ***
	①ファイルが存在するところまでのパスを数値化する
	②ファイル名は数値のみがインクリメントされているため、対応する場所の数値を変数とする
	③数値化したパスにインクリメントされた変数を付け足す
	④数値化されていたパスを文字列に戻す
	⑤ファイルオープン関数で対象テキストを開く
	*/

/*-------------------------------- DATA READ --------------------------------*/

	for (cnt = 0; cnt < 200; cnt++) {
		directory.str("");						//directory内のバッファをクリアする
		directory.clear(stringstream::goodbit);	//directory内のストリーム状態をクリアする。
		directory << "C:\\Users\\Atsuya\\Documents\\Visual Studio 2015\\Projects\\DPmatching\\DPmatching\\";	//ファイルが存在する場所までのパスを数値化
		if (cnt < 100) {
			directory << FILEA;	//ファイル選択①
		}
		else if (cnt < 200) {
			directory << FILED;	//ファイル選択②
		}
		else {
			/*何もしない*/
		}

		if ((cnt % 100) < 9) {
			directory << "00";
		}
		else if ((cnt % 100) < 99) {
			directory << "0";
		}
		else {
			/*何もしない*/
		}

		directory << (cnt % 100) + 1;
		directory << ".txt\0";

		if ((fp1 = fopen(directory.str().c_str(), "r")) == NULL) {	//対象ファイルを開く。開けなかったらエラーを返す
			exit(EXIT_FAILURE);
		}
		fscanf(fp1, "%s", load_directory);			//ファイル名読み出し(No USE)
		fscanf(fp1, "%s", load_directory);			//単語名読み出し(No USE)
		if (cnt < 100) {
			fscanf(fp1, "%d", &DATA1[cnt % 100].FRAME);	//フレーム長さ読み出し
			for (i = 0; i < DATA1[cnt % 100].FRAME; i++) {
				for (j = 0; j < 15; j++) {
					fscanf(fp1, "%f", &DATA1[cnt % 100].DATA[i][j]);
				}
			}
		}
		else if (cnt < 200) {
			fscanf(fp1, "%d", &DATA2[cnt % 100].FRAME);	//フレーム長さ読み出し
			for (i = 0; i < DATA2[cnt % 100].FRAME; i++) {
				for (j = 0; j < 15; j++) {
					fscanf(fp1, "%f", &DATA2[cnt % 100].DATA[i][j]);
				}
			}
		}
		else {
			/*何もしない*/
		}
		fclose(fp1);//対象ファイルを閉じる。
	}
	/*--------------------------------表用--------------------------------*/
	cout << "Template" << "," << "Target" << "" << ", d, T or F" << endl;


/*-------------------------------- DATA READ --------------------------------*/
	for (y = 0; y < 100; y++) {
		for (x = 0; x < 100; x++) {						//SAMPLE WORD B (FULL WORDs)

			/*------------------ 局所距離計算 --------------------*/

			for (i = 0; i < DATA1[y].FRAME; i++) {
				Metrizable_Calc( &d[x][i][0] , & DATA1[y].DATA[i][0] , DATA2[x].DATA , DATA2[x].FRAME);
				
			}

			/*------------------- 単語間距離 ---------------------*/
			g[x][0][0] = d[x][0][0];
			for ( i = 1; i < DATA1[y].FRAME; i++) {
				g[x][i][0] = g[x][i - 1][0] + d[x][i][0];
			}
			for ( j = 1; j < DATA2[x].FRAME; j++) {
				g[x][0][j] = g[x][0][j - 1] + d[x][0][j];
			}
			for (i = 1; i < DATA1[y].FRAME; i++) {
				for (j = 1; j < DATA2[x].FRAME; j++) {
					g[x][i][j] = Min(g[x][i][j - 1] + d[x][i][j], g[x][i - 1][j] + d[x][i][j], g[x][i - 1][j - 1] + 2 * d[x][i][j]);
				}
			}

			g[x][DATA1[y].FRAME - 1][DATA2[x].FRAME - 1] /= ( DATA1[y].FRAME + DATA2[x].FRAME );	//単語間距離 ＝ 累積距離　/　総合フレーム数

			/*--------------- 単語間最短距離算出 -----------------*/

			if (x == 0) {
				MIN.DATA = g[x][DATA1[y].FRAME - 1][DATA2[x].FRAME - 1];
				MIN.NUM = x;
			}
			else {
				if (MIN.DATA > g[x][DATA1[y].FRAME - 1][DATA2[x].FRAME - 1]) {
					MIN.DATA = g[x][DATA1[y].FRAME - 1][DATA2[x].FRAME - 1];
					MIN.NUM = x;
				}
			}
		}
		printf("%3d, %3d, %f , ", y + 1, MIN.NUM + 1, MIN.DATA);
		if (y == MIN.NUM) {
			printf("〇\n\r");
			answer++;
		}
		else {
			printf("×\n\r");
		}
		//dとgの初期化

		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 200; j++) {
				for (int k = 0; k < 200; k++) {
					g[i][j][k] = 0; d[i][j][k] = 0;
				}
			}
		}
	}
	printf("正答率：%d%% \n\r", answer);
/*-------------------------------- DATA CALC --------------------------------*/
/*-------------------------------- PROGRAMS ---------------------------------*/
	printf("SUCCESS\n\r");
	return (EXIT_SUCCESS);
}
/*-----------------------------------------------------------------------------
*	最小数値を返す関数
*	Input	:	double x1 , x2 , x3
*	Output	:	double tmp;
*----------------------------------------------------------------------------*/
float Min(float x1, float x2, float x3)
{ 
	float tmp = x1;
	if (tmp > x2) tmp = x2;
	if (tmp > x3) tmp = x3;
	return tmp;
}
/*-----------------------------------------------------------------------------
*	計算関数
*----------------------------------------------------------------------------*/

void Metrizable_Calc( float *result , float *data1 , float data2[100][15] ,size_t para_value )
{
	/*------------------- 局所距離計算 --------------------*/
	
	parallel_for(size_t(0), para_value, [&](int value ) {
		int i = 0;

		for (i = 0; i < 15; i++) {
			result[value] += pow(data1[i] - data2[value][i], 2.0);	//局所点 2乗
		}
		result[value] = sqrt(result[value]);
	});
}
/*-----------------------------copyright-------------------------------------
* 16c1051 小池 篤哉
---------------------------------------------------------------------------*/
