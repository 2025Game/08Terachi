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
	printf("Loading background: %s %s\n", obj, mtl);

	//マテリアルインデックス
	int idx = 0;

	//頂点データ
	std::vector<CVector> vertex;
	//法線データ
	std::vector<CVector> normal;
	//テクスチャマッピング
	std::vector<CVector> uv;

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
		char str[4][64] = { "", "", "", "" };
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);

		if (strcmp(str[0], "newmtl") == 0)
		{
			CMaterial* pm = new CMaterial();
			pm->Name(str[1]);
			mpMaterials.push_back(pm);
			idx = mpMaterials.size() - 1;
		}
		else if (strcmp(str[0], "Kd") == 0)
		{
			mpMaterials[idx]->Diffuse()[0] = atof(str[1]);
			mpMaterials[idx]->Diffuse()[1] = atof(str[2]);
			mpMaterials[idx]->Diffuse()[2] = atof(str[3]);
		}
		else if (strcmp(str[0], "d") == 0)
		{
			mpMaterials[idx]->Diffuse()[3] = atof(str[1]);
		}
		//map_Kdの追加（テクスチャ読み込み）
		else if (strcmp(str[0], "map_Kd") == 0)
		{
			mpMaterials[idx]->Texture()->Load(str[1]);
		}

		printf("%s", buf); // コンソール出力
	}
	fclose(fp);

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

		// 頂点
		if (strcmp(str[0], "v") == 0)
		{
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		// 法線
		else if (strcmp(str[0], "vn") == 0)
		{
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		// テクスチャマッピング
		else if (strcmp(str[0], "vt") == 0)
		{
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}
		// 面データ
		else if (strcmp(str[0], "f") == 0)
		{
			int v[3], n[3], u[3];

			//テクスチャマッピングの有無を判定
			if (strstr(str[1], "//"))
			{
				// 頂点//法線形式
				sscanf(str[1], "%d//%d", &v[0], &n[0]);
				sscanf(str[2], "%d//%d", &v[1], &n[1]);
				sscanf(str[3], "%d//%d", &v[2], &n[2]);

				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				t.MaterialIdx(idx);
				mTriangles.push_back(t);
			}
			else
			{
				// 頂点/テクスチャ/法線形式
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]);
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);

				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				t.UV(uv[u[0] - 1], uv[u[1] - 1], uv[u[2] - 1]); // ★追加
				t.MaterialIdx(idx);
				mTriangles.push_back(t);
			}
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
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled();
		mTriangles[i].Render();
		//マテリアルを無効
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}
