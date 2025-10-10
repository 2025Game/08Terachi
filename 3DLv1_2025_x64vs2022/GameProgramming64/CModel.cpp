#include "CModel.h"
//標準入出力のインクルード
#include <stdio.h>

//文字列s1と文字列s2の比較
//s1とs2が等しければ0を
//等しくなければ0以外を返す
int strcmp(const char* s1, const char* s2)
{
	int i = 0;
	//文字が同じ間は繰り返し
	//どちらかの文字が終わりになるとループの終わり
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	//同じなら引いて0
	return s1[i] - s2[i];
}

//モデルファイルの入力
//Load(モデルファイル名, マテリアルファイル名)
void CModel::Load(const char* obj, const char* mtl) {
	//ファイルポインタ変数の作成
	FILE* fp;
	//ファイルからデータを入力
	//入力エリアを作成する
	char buf[256];

	//ファイルのオープン
	//fopen(ファイル名,モード)
	//オープンできない時はNULLを返す
	fp = fopen(mtl, "r");
	//ファイルオープンエラーの判定
	//fpがNULLの時はエラー
	if (fp == NULL) {
		//コンソールにエラー出力して戻る
		printf("%s file open error￥n", mtl);
		return;
	}

	//ファイルから1行入力
	//fgets(入力エリア,エリアサイズ,ファイルポインタ)
	//ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//入力した値をコンソールに出力する
		printf("%s", buf);
	}
	fp = fopen(obj, "r");
	if (fp == NULL) {
		printf("%s file open error\n", obj);
		return;
	}

	// objファイルを1行ずつ読み込んで表示
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		printf("%s", buf);
	}
	//ファイルのクローズ
	fclose(fp);
}
