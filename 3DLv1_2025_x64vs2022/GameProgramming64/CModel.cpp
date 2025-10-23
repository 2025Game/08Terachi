#include "CModel.h"
#include <stdio.h>
#include "CVector.h"

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
	//頂点データ
	std::vector<CVector> vertex;
	//★法線データを追加
	std::vector<CVector> normal;

	FILE* fp;
	char buf[256];

	//まず mtl ファイルを読む（課題6）
	fp = fopen(mtl, "r");
	if (fp == NULL)
	{
		printf("%s file open error\n", mtl);
		return;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
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
		mTriangles[i].Render();
	}
}
