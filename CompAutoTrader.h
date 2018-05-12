// CompAutoTrader.h : COMPAUTOTRADER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_COMPAUTOTRADER_H__B5A34C2C_6B7F_4643_A1B1_15E39448297E__INCLUDED_)
#define AFX_COMPAUTOTRADER_H__B5A34C2C_6B7F_4643_A1B1_15E39448297E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CCompAutoTraderApp:
// このクラスの動作の定義に関しては CompAutoTrader.cpp ファイルを参照してください。
//

class CCompAutoTraderApp : public CWinApp
{
public:
	CCompAutoTraderApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCompAutoTraderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CCompAutoTraderApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_COMPAUTOTRADER_H__B5A34C2C_6B7F_4643_A1B1_15E39448297E__INCLUDED_)
