#include "CMatrix.h"
//標準入出力関数のインクルード
#include <stdio.h>

void CMatrix::Print() 
{
	printf("%10f %10f %10f %10f\n",
		mM[0][0], mM[0][1], mM[0][2], mM[0][3]);
	printf("%10f %10f %10f %10f\n",
		mM[1][0], mM[1][1], mM[1][2], mM[1][3]);
	printf("%10f %10f %10f %10\n",
		mM[2][0], mM[2][1], mM[2][2], mM[2][3]);
	printf("%10f %10f %10f %10f\n",
		mM[3][0], mM[3][1], mM[3][2], mM[3][3]);
}

// 行列値の取得
float CMatrix::M(int r, int c) const
{
    return mM[r][c];
}

//デフォルトコンストラクタ
CMatrix::CMatrix()
{
	Identity();
}
//単位行列の作成
CMatrix CMatrix::Identity()
{
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            mM[i][j] = 0.0f;
        }
    }

    // 対角線の要素だけを 1 にする
    mM[0][0] = 1.0f;
    mM[1][1] = 1.0f;
    mM[2][2] = 1.0f;
    mM[3][3] = 1.0f;

    // この行列を返す
    return *this;
}
 
// 拡大縮小行列の作成
CMatrix CMatrix::Scale(float x, float y, float z)
{
    // まず単位行列を作成
    Identity();

    // 対角成分を拡大率に設定
    mM[0][0] = x;
    mM[1][1] = y;
    mM[2][2] = z;

    // この行列を返す
    return *this;
}
