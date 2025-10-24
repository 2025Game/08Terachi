#include "CModel.h"
#include <stdio.h>
#include "CVector.h"

CModel::~CModel()
{
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		delete mpMaterials[i];
	}
}

//文字列比較関数
int strcmp(const char* s1, const char* s2)
{
	int i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return s1[i] - s2[i];
}

//モデルファイルの入力
void CModel::Load(const char* obj, const char* mtl)
{

	//マテリアルインデックス
	int idx = 0;

	//頂点データ
	std::vector<CVector> vertex;
	//★法線データを追加
	std::vector<CVector> normal;

	FILE* fp;
	char buf[256];

	//まず mtl ファイルを読む
	fp = fopen(mtl, "r");
	if (fp == NULL)
	{
		printf("%s file open error\n", mtl);
		return;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		//データを分割する
		char str[4][64] = { "", "", "", "" };
		//文字列からデータを4つ変数へ代入する
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//先頭がnewmtlの時、マテリアルを追加する
		if (strcmp(str[0], "newmtl") == 0) 
		{
			CMaterial* pm = new CMaterial();
			//マテリアル名の設定
			pm->Name(str[1]);
			//マテリアルの可変長配列に追加
			mpMaterials.push_back(pm);
			//配列の長さを取得
			idx = mpMaterials.size() - 1;
		}
		//先頭がKdの時、Diffuseを設定する
		else if (strcmp(str[0], "Kd") == 0) 
		{
			mpMaterials[idx]->Diffuse()[0] = atof(str[1]);
			mpMaterials[idx]->Diffuse()[1] = atof(str[2]);
			mpMaterials[idx]->Diffuse()[2] = atof(str[3]);
		}
		//先頭がdの時、α値を設定する
		else if (strcmp(str[0], "d") == 0) 
		{
			mpMaterials[idx]->Diffuse()[3] = atof(str[1]);
		}
		//先頭がusemtlの時、マテリアルインデックスを取得する
		else if (strcmp(str[0], "usemtl") == 0)
		{
			//可変長配列を後から比較
			for (idx = mpMaterials.size() - 1; idx > 0; idx--)
			{
				//同じ名前のマテリアルがあればループ終了
				if (strcmp(mpMaterials[idx]->Name(), str[1]) == 0) 
				{
					break; //ループから出る
				}
			}

		}


		printf("%s", buf); // コンソールに出力
	}
	fclose(fp); // mtl ファイルを閉じる

	//次に obj ファイルを読む
	fp = fopen(obj, "r");
	if (fp == NULL)
	{
		printf("%s file open error\n", obj);
		return;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL)
	{

		char str[4][64] = { "", "", "", "" };
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);

		//-----------------------------
		// 頂点データ (v)
		//-----------------------------
		if (strcmp(str[0], "v") == 0)
		{
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//-----------------------------
		// ★ 法線データ (vn)
		//-----------------------------
		else if (strcmp(str[0], "vn") == 0)
		{
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//-----------------------------
		// 面データ (f)
		//-----------------------------
		else if (strcmp(str[0], "f") == 0)
		{
			int v[3], n[3];
			// 例: f 1//1 2//2 3//3
			sscanf(str[1], "%d//%d", &v[0], &n[0]);
			sscanf(str[2], "%d//%d", &v[1], &n[1]);
			sscanf(str[3], "%d//%d", &v[2], &n[2]);

			// 三角形の生成
			CTriangle t;
			t.Vertex(
				vertex[v[0] - 1],
				vertex[v[1] - 1],
				vertex[v[2] - 1]
			);

			// ★法線の設定（CTriangleに追加したNormalメソッドを使う）
			if (!normal.empty())
			{
				t.Normal(
					normal[n[0] - 1],
					normal[n[1] - 1],
					normal[n[2] - 1]
				);
			}
			
			mTriangles.push_back(t);
		}

		printf("%s", buf); // コンソール出力
	}

	fclose(fp);
}

//描画
void CModel::Render()
{
	for (int i = 0; i < mTriangles.size(); i++)
	{
		//マテリアルの適用
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled();
		mTriangles[i].Render();
	}
}
