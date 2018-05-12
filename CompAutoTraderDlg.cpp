// CompAutoTraderDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "CompAutoTrader.h"
#include "CompAutoTraderDlg.h"

#include <Msiquery.h>
#include <UNLHA32.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompAutoTraderDlg ダイアログ

CCompAutoTraderDlg::CCompAutoTraderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompAutoTraderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompAutoTraderDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCompAutoTraderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompAutoTraderDlg)
		// メモ: この場所には ClassWizard によって DDX と DDV の呼び出しが追加されます。
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCompAutoTraderDlg, CDialog)
	//{{AFX_MSG_MAP(CCompAutoTraderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompAutoTraderDlg メッセージ ハンドラ

BOOL CCompAutoTraderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO2);
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CCompAutoTraderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CCompAutoTraderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCompAutoTraderDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください

	int i;

	int nPackageMode = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3) - IDC_RADIO1;

//	char szPersonalDPath[_MAX_PATH];
//	SHGetSpecialFolderPath(m_hWnd, szPersonalDPath, CSIDL_PERSONAL, FALSE);

//	CString strPersonalDPath = szPersonalDPath;
	CString strPersonalDPath = "D:\\home";
	CString strVisualStudioProjectsDPath = strPersonalDPath + "\\Visual Studio Projects";
	CString strAutoTraderDPath = strVisualStudioProjectsDPath + "\\AutoTrader";

	CString strVer;
	try {
		CString strVerHFPath = strAutoTraderDPath + "\\AutoTraderVer.h";

		CString strKey0 = "#define THIS_VER	";
		int nKeyLen0 = strKey0.GetLength();

		CStdioFile Sf(strVerHFPath, CFile::modeRead);
		CString strLine;
		while (Sf.ReadString(strLine)) {
			if (strLine.Left(nKeyLen0) == strKey0) {
				char pszThisVer[MAX_PATH];
				if (sscanf(strLine, "%*s %*s %s", pszThisVer) == 1)
					strVer = pszThisVer;
				break;
			}
		}
		Sf.Close();
	}
	catch (CException* pEx) {
		MessageBox(GetExceptionErrorMessage(pEx), NULL, MB_ICONSTOP);
		pEx->Delete();
		return;
	}
	int nVerLen = strVer.GetLength();
	CString strMajorVer = strVer.Left(nVerLen - 4);
	CString strMinorVer = strVer.Mid(nVerLen - 4, 2);
	CString strRevVer = strVer.Right(2);
	int nVer = atoi(strVer);
	int nMajorVer = atoi(strMajorVer);
	int nMinorVer = atoi(strMinorVer);
	int nRevVer = atoi(strRevVer);

	CString strOutputDPath;
	CString strDisk1DPath;
//	CString strPatchingDPath = strPersonalDPath + "\\ARC\\NonBackup\\Release\\Patching";
	CString strPatchingDPath = "E:\\ARC\\NonBackup\\Release\\Patching";
	CString strPatchingAutoTraderDPath = strPatchingDPath + "\\AutoTrader";
	CString strMsiFName = "AutoTraderInstaller.msi";
	CString strSql;
	CString strParameters;

	char pszFromFPath[MAX_PATH + 1];
	char pszToFPath[MAX_PATH + 1];

	SHFILEOPSTRUCT fileop;
	fileop.hwnd = m_hWnd;
	fileop.pFrom = pszFromFPath;
	fileop.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;

	MSIHANDLE hDatabase;
	MSIHANDLE hView;
	MSIHANDLE hRec;

	UINT uiRet;
	CString strRet;

	CFileStatus FileStatus;

	CString strSetupDName;
	strSetupDName.Format("AutoTrader%06d", nVer);
	CString strSetupDNameA = strSetupDName + "a";

	DWORD dwWaitForSingleObject;

	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;

	ZeroMemory(&sInfo, sizeof(sInfo));
	sInfo.cb = sizeof(sInfo);

	strOutputDPath = strVisualStudioProjectsDPath + "\\AutoTraderInstaller\\Output";
	strDisk1DPath = strOutputDPath + "\\DISK_1";
	CString strRedistFPath = strDisk1DPath + "\\Redist";

	CString strPackageCodeFPath = strAutoTraderDPath + "\\PackageCode.txt";
	CString strPackageCode;

	BOOL bNotCompress = CFile::GetStatus(strRedistFPath, FileStatus);
	if (nPackageMode == 2  ||  bNotCompress) {
		if (CreateGuid(strPackageCode)) {
			MessageBox("CreateGuid(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
		try {
			CStdioFile SfPackageCode(strPackageCodeFPath, CFile::modeCreate | CFile::modeWrite);
			SfPackageCode.WriteString(strPackageCode);
			SfPackageCode.WriteString("\n");
			SfPackageCode.Close();
		}
		catch (CException* pEx) {
			MessageBox(GetExceptionErrorMessage(pEx), NULL, MB_ICONSTOP);
			pEx->Delete();
			return;
		}
	} else
		try {
			CStdioFile SfPackageCode(strPackageCodeFPath, CFile::modeRead);
			SfPackageCode.ReadString(strPackageCode);
			SfPackageCode.Close();
		}
		catch (CException* pEx) {
			MessageBox(GetExceptionErrorMessage(pEx), NULL, MB_ICONSTOP);
			pEx->Delete();
			return;
		}

	CString strProductCode;
	try {
		CString strProductCodeFPath = strAutoTraderDPath + "\\ProductCode.txt";
		CStdioFile SfProductCode(strProductCodeFPath, CFile::modeRead);
		SfProductCode.ReadString(strProductCode);
		SfProductCode.Close();
	}
	catch (CException* pEx) {
		MessageBox(GetExceptionErrorMessage(pEx), NULL, MB_ICONSTOP);
		pEx->Delete();
		return;
	}

	char szUpgradeCode[MAX_PATH] = {0};
	DWORD dwUpgradeCodeSize = MAX_PATH;

	char szWfpFile[MAX_PATH] = {0};
	DWORD dwWfpFileSize;

	hDatabase = 0;
	hView = 0;
	hRec = 0;

	uiRet = ERROR_SUCCESS;

	CString strProductVersion;

	CString strMsiFPath = strDisk1DPath + '\\' + strMsiFName;
	do {
		if (ERROR_SUCCESS != (uiRet = MsiOpenDatabase(strMsiFPath, MSIDBOPEN_TRANSACT, &hDatabase)))
			break;
		strSql.Format("UPDATE `Property` SET `Value`='%s' WHERE `Property`='ProductCode'", strProductCode);
		if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, strSql, &hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "SELECT `Value` FROM `Property` WHERE `Property`='UpgradeCode'", &hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewFetch(hView, &hRec)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiRecordGetString(hRec, 1, szUpgradeCode, &dwUpgradeCodeSize)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hRec)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		strProductVersion.Format("%d.%d.%d.1", nMajorVer, nMinorVer, nRevVer);
		strSql.Format("UPDATE `Property` SET `Value`='%s' WHERE `Property`='ProductVersion'", strProductVersion);
		if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, strSql, &hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `Property` (`Property`, `Value`) VALUES ('SecureCustomProperties', 'OLDAPPFOUND')",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"CREATE TABLE `Upgrade` ("
								"`UpgradeCode` CHAR(38) NOT NULL, "
								"`VersionMin` CHAR(20), "
								"`VersionMax` CHAR(20), "
								"`Language` CHAR(255), "
								"`Attributes` LONG NOT NULL, "
								"`Remove` CHAR(255), "
								"`ActionProperty` CHAR(72) "
								"PRIMARY KEY `UpgradeCode`, `VersionMin`, `VersionMax`, `Language`, `Attributes`"
							")",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		strSql.Format(
			"INSERT INTO `Upgrade` ("
				"`UpgradeCode`, `VersionMin`, `VersionMax`, `Language`, `Attributes`, `Remove`, `ActionProperty`"
			") VALUES ("
				"'%s', '1.0.0.1', '%s', '1041', 261, '', 'OLDAPPFOUND'"
			")",
			szUpgradeCode, strProductVersion
		);
		if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, strSql, &hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `InstallExecuteSequence` (`Action`, `Condition`, `Sequence`) VALUES ('FindRelatedProducts', '', 362)",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `InstallExecuteSequence` (`Action`, `Condition`, `Sequence`) VALUES ('MigrateFeatureStates', '', 1200)",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `InstallExecuteSequence` (`Action`, `Condition`, `Sequence`) VALUES ('RemoveExistingProducts', '', 6700)",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `InstallUISequence` (`Action`, `Condition`, `Sequence`) VALUES ('FindRelatedProducts', '', 200)",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `InstallUISequence` (`Action`, `Condition`, `Sequence`) VALUES ('MigrateFeatureStates', '', 1200)",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `Property` (`Property`, `Value`) VALUES ('APPS_TEST', 'TRUE')",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"CREATE TABLE `RegLocator` ("
								"`Signature_` CHAR(72) NOT NULL, "
								"`Root` SHORT NOT NULL, "
								"`Key` CHAR(255) NOT NULL, "
								"`Name` CHAR(255), "
								"`Type` SHORT "
								"PRIMARY KEY `Signature_`"
							")",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `RegLocator` ("
								"`Signature_`, `Root`, `Key`, `Name`, `Type`"
							") VALUES ("
								"'AppFolder', 2, 'SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\[OLDAPPFOUND]', 'InstallLocation', 2"
							")",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"CREATE TABLE `AppSearch` ("
								"`Property` CHAR(72) NOT NULL, "
								"`Signature_` CHAR(72) NOT NULL "
								"PRIMARY KEY `Property`, `Signature_`"
							")",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `AppSearch` (`Property`, `Signature_`) VALUES ('OLDAPPFOLDER', 'AppFolder')",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `CustomAction` ("
								"`Action`, `Type`, `Source`, `Target`"
							") VALUES ("
								"'SetOldTargetDir', 51, 'TARGETDIR', '[OLDAPPFOLDER]'"
							")",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `InstallExecuteSequence` (`Action`, `Condition`, `Sequence`) VALUES ('SetOldTargetDir', 'OLDAPPFOLDER', 450)",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `InstallUISequence` (`Action`, `Condition`, `Sequence`) VALUES ('SetOldTargetDir', 'OLDAPPFOLDER', 450)",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `CustomAction` ("
								"`Action`, `Type`, `Source`, `Target`"
							") VALUES ("
								"'SetInstallLocation', 51, 'ARPINSTALLLOCATION', '[TARGETDIR]'"
							")",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `InstallExecuteSequence` (`Action`, `Sequence`) VALUES ('SetInstallLocation', 1250)",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `InstallUISequence` (`Action`, `Sequence`) VALUES ('SetInstallLocation', 1250)",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"CREATE TABLE `Signature` ("
								"`Signature` CHAR(72) NOT NULL, "
								"`FileName` CHAR(255) NOT NULL, "
								"`MinVersion` CHAR(20), "
								"`MaxVersion` CHAR(20), "
								"`MinSize` LONG, "
								"`MaxSize` LONG, "
								"`MinDate` LONG, "
								"`MaxDate` LONG, "
								"`Languages` CHAR(255) "
								"PRIMARY KEY `Signature`"
							")",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (
			ERROR_SUCCESS !=
				(
					uiRet =
						MsiDatabaseOpenView(
							hDatabase,
							"INSERT INTO `Property` (`Property`, `Value`) VALUES ('ALLUSERS', '2')",
							&hView
						)
				)
		)
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "SELECT `Component_` FROM `File` WHERE `FileName`='msvcrt.dll'", &hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewFetch(hView, &hRec)))
			break;
		dwWfpFileSize = MAX_PATH;
		if (ERROR_SUCCESS != (uiRet = MsiRecordGetString(hRec, 1, szWfpFile, &dwWfpFileSize)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hRec)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		strSql.Format("UPDATE `Component` SET `Condition`='Version9X>=400' WHERE `Component`='%s'", szWfpFile);
		if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, strSql, &hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "SELECT `Component_` FROM `File` WHERE `FileName`='mfc42.dll'", &hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewFetch(hView, &hRec)))
			break;
		dwWfpFileSize = MAX_PATH;
		if (ERROR_SUCCESS != (uiRet = MsiRecordGetString(hRec, 1, szWfpFile, &dwWfpFileSize)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hRec)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		strSql.Format("UPDATE `Component` SET `Condition`='Version9X>=400' WHERE `Component`='%s'", szWfpFile);
		if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, strSql, &hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
			break;
		if (ERROR_SUCCESS != (uiRet = MsiDatabaseCommit(hDatabase)))
			break;
	} while (0);
	if (ERROR_SUCCESS != uiRet) {
		strRet.Format("%d, %s", uiRet, GetLastErrorMessage());
		MessageBox("Msi.dll: " + strRet);
	}
	if (hRec)
		MsiCloseHandle(hRec);
	if (hView)
		MsiCloseHandle(hView);
	if (hDatabase)
		MsiCloseHandle(hDatabase);
	if (ERROR_SUCCESS != uiRet)
		return;

	CString strMsiInfoFPath = "C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0\\Bin\\MsiInfo.Exe";
	strParameters = strMsiFName + " /v " + strPackageCode;
	if (! CreateProcess(NULL, (LPTSTR)(LPCTSTR)('\"' + strMsiInfoFPath + "\" " + strParameters), NULL, NULL, FALSE, 0, NULL, strDisk1DPath, &sInfo, &pInfo)) {
		MessageBox("CreateProcess(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
		return;
	}
	for (i = 0; (dwWaitForSingleObject = WaitForSingleObject(pInfo.hProcess, 250)) == WAIT_TIMEOUT; i ++) {
		if (dwWaitForSingleObject == WAIT_FAILED) {
			MessageBox("WaitForSingleObject(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
		if (i >= 80) {
			MessageBox("WaitForSingleObject(): WAIT_TIMEOUT", NULL, MB_ICONSTOP);
			return;
		}
		PumpWaitingMessages();
	}

	if (nPackageMode <= 1  &&  bNotCompress) {
		CString strSetupDPath = strPatchingAutoTraderDPath + '\\' + strSetupDName;
		if (CFile::GetStatus(strSetupDPath, FileStatus)) {
			fileop.wFunc = FO_DELETE;
			fileop.pTo = NULL;
			strcpy(pszFromFPath, strSetupDPath);
			pszFromFPath[strSetupDPath.GetLength() + 1] = '\0';
			if (SHFileOperation(&fileop))
				return;
		}
		fileop.wFunc = FO_MOVE;
		fileop.pTo = pszToFPath;
		strcpy(pszToFPath, strSetupDPath);
		pszToFPath[strSetupDPath.GetLength() + 1] = '\0';
		strcpy(pszFromFPath, strDisk1DPath);
		pszFromFPath[strDisk1DPath.GetLength() + 1] = '\0';
		if (SHFileOperation(&fileop))
			return;
		if (! RemoveDirectory(strOutputDPath)) {
			MessageBox("RemoveDirectory(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
		CDialog::OnOK();
		return;
	}

	CString strSetupBaseDPath = nPackageMode <= 1  ? strPersonalDPath : strPatchingAutoTraderDPath;
	CString strSetupDPath = strSetupBaseDPath + '\\' + strSetupDName;
	CString strSetupDPathA = strSetupBaseDPath + '\\' + strSetupDNameA;
	CString* pstrSetupDPath[] = {&strSetupDPath, &strSetupDPathA, NULL};

	for (i = 0; pstrSetupDPath[i]; i ++)
		if (CFile::GetStatus(*pstrSetupDPath[i], FileStatus)) {
			fileop.wFunc = FO_DELETE;
			fileop.pTo = NULL;
			strcpy(pszFromFPath, *pstrSetupDPath[i]);
			pszFromFPath[pstrSetupDPath[i]->GetLength() + 1] = '\0';
			if (SHFileOperation(&fileop))
				return;
		}

	if (! MoveFile(strDisk1DPath, strSetupDPath)) {
		MessageBox("MoveFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
		return;
	}
	if (! RemoveDirectory(strOutputDPath)) {
		MessageBox("RemoveDirectory(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
		return;
	}

	CString strDocFName = "AutoTrader 説明書.txt";
	CString strDocFPath = strAutoTraderDPath + '\\' + strDocFName;
	CString strDocFPathC = strSetupDPath + '\\' + strDocFName;
	if (! CopyFile(strDocFPath, strDocFPathC, TRUE)) {
		MessageBox("CopyFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
		return;
	}
	DWORD dwFileAttributes = GetFileAttributes(strDocFPathC);
	if (dwFileAttributes == -1) {
		MessageBox("GetFileAttributes(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
		return;
	}
	if (! SetFileAttributes(strDocFPathC, dwFileAttributes | FILE_ATTRIBUTE_READONLY)) {
		MessageBox("CreateDirectory(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
		return;
	}

	CString strSetupFPath = strPersonalDPath + "\\LIB\\setup.exe";
	CString strSetupFPathC = strSetupDPath + "\\setup.exe";
	CString strMsiStuffFPath = strPersonalDPath + "\\BIN\\msistuff";

	if (nPackageMode <= 1) {
		char pszSystemDPath[MAX_PATH];
		if (GetSystemDirectory(pszSystemDPath, MAX_PATH) == 0) {
			MessageBox("GetSystemDirectory(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
		CString strShFolderFName = "shfolder.dll";
		CString strShFolderFPath = (CString)pszSystemDPath + '\\' + strShFolderFName;
		CString strShFolderFPathC = strSetupDPath + '\\' + strShFolderFName;
		if (! CopyFile(strShFolderFPath, strShFolderFPathC, TRUE)) {
			MessageBox("CopyFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
	} else {
		static const char* ppszMsmJpnExtract[] = {"mfc42.dll", "mscc2jp.dll", "mscomct2.ocx", "msmapi32.ocx", "msmpijp.dll", "msvcrt.dll", NULL};

		CString strPatchingMsmJpnExtractDPath = strPatchingDPath + "\\msmjpn-extract";

		CString strMsmJpnExtract;
		CString strMsmJpnExtractC;
		for (i = 0; ppszMsmJpnExtract[i]; i ++) {
			strMsmJpnExtract = strPatchingMsmJpnExtractDPath + '\\' + ppszMsmJpnExtract[i];
			strMsmJpnExtractC = strSetupDPath + "\\Redist\\MS\\System\\" + ppszMsmJpnExtract[i];
			if (! CopyFile(strMsmJpnExtract, strMsmJpnExtractC, FALSE)) {
				MessageBox("CopyFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
				return;
			}
		}
	}

	if (! CopyFile(strSetupFPath, strSetupFPathC, TRUE)) {
		MessageBox("CopyFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
		return;
	}

	strParameters = "setup.exe /d " + strMsiFName + " /n AutoTrader /v 200 /i http://hashikun0.hp.infoseek.co.jp/lib /a InstMsiA.exe /w InstMsiW.exe /c 1 /j 1";
	if (! CreateProcess(NULL, (LPTSTR)(LPCTSTR)('\"' + strMsiStuffFPath + "\" " + strParameters), NULL, NULL, FALSE, 0, NULL, strSetupDPath, &sInfo, &pInfo)) {
		MessageBox("CreateProcess(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
		return;
	}
	for (i = 0; (dwWaitForSingleObject = WaitForSingleObject(pInfo.hProcess, 250)) == WAIT_TIMEOUT; i ++) {
		if (dwWaitForSingleObject == WAIT_FAILED) {
			MessageBox("WaitForSingleObject(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
		if (i >= 80) {
			MessageBox("WaitForSingleObject(): WAIT_TIMEOUT", NULL, MB_ICONSTOP);
			return;
		}
		PumpWaitingMessages();
	}

	CString strLzhFPath0 = strSetupDPath;
	CString strLzhAFPath0 = strSetupDPath + "a";

	CString strLzhFPath = strLzhFPath0 + ".EXE";
	CString strLzhAFPath = strLzhAFPath0 + ".EXE";

	if (CFile::GetStatus(strLzhFPath, FileStatus))
		if (! DeleteFile(strLzhFPath)) {
			MessageBox("DeleteFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
	if (CFile::GetStatus(strLzhAFPath, FileStatus))
		if (! DeleteFile(strLzhAFPath)) {
			MessageBox("DeleteFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}

	CString strCmdLine;
	char szOutput[256];

	if (nPackageMode)
		strCmdLine.Format("a -gw4 -d -gye%s/SETUP -gyq1 -zcab \"%s\" \"%s\\\" %s", strSetupDName, strLzhFPath0, strSetupBaseDPath, strSetupDName);
	else
		strCmdLine.Format("a -gw4 -d -gye%s/SETUP -gyq1 -zmsi \"%s\" \"%s\\\" %s", strSetupDName, strLzhFPath0, strSetupBaseDPath, strSetupDName);
	if (Unlha(m_hWnd, strCmdLine, szOutput, 256)) {
		MessageBox("Unlha()", NULL, MB_ICONSTOP);
		return;
	}

	CFileFind Ff;
	BOOL bFfFound;

	CStringArray SaPatchingFPath;

	bFfFound = Ff.FindFile(strPatchingAutoTraderDPath + "\\AutoTrader??????");
	while (bFfFound) {
		bFfFound = Ff.FindNextFile();
		if (Ff.IsDirectory()) {
			strMsiFPath = Ff.GetFilePath() + '\\' + strMsiFName;
			if (CFile::GetStatus(strMsiFPath, FileStatus))
				SaPatchingFPath.Add(strMsiFPath);
		}
	}
	Ff.Close();

	CString strPatchGUIDFPath = strAutoTraderDPath + "\\PatchGUID.txt";

	if (SaPatchingFPath.GetSize() <= 1) {
		if (CFile::GetStatus(strPatchGUIDFPath, FileStatus))
			if (! DeleteFile(strPatchGUIDFPath)) {
				MessageBox("DeleteFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
				return;
			}
	} else {
		if (! CreateDirectory(strSetupDPathA, NULL)) {
			MessageBox("CreateDirectory(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}

		CString strPcpFName = "AutoTraderInstaller.PCP";
		CString strMspFName = "AutoTraderInstaller.msp";

		CString strPcpFPath = "C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0\\Bin\\msitools\\Schemas\\MSI\\template.pcp";
		CString strPcpFPathC = strSetupDPathA + '\\' + strPcpFName;
		if (! CopyFile(strPcpFPath, strPcpFPathC, TRUE)) {
			MessageBox("CopyFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}

		CString strPatchGUID;
		if (CreateGuid(strPatchGUID)) {
			MessageBox("CreateGuid(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
		try {
			CStdioFile SfPatchGUID(strPatchGUIDFPath, CFile::modeCreate | CFile::modeWrite);
			SfPatchGUID.WriteString(strPatchGUID);
			SfPatchGUID.WriteString("\n");
			SfPatchGUID.Close();
		}
		catch (CException* pEx) {
			MessageBox(GetExceptionErrorMessage(pEx), NULL, MB_ICONSTOP);
			pEx->Delete();
			return;
		}

		hDatabase = 0;
		hView = 0;

		uiRet = ERROR_SUCCESS;

		do {
			if (ERROR_SUCCESS != (uiRet = MsiOpenDatabase(strPcpFPathC, MSIDBOPEN_TRANSACT, &hDatabase)))
				break;
			strSql.Format("UPDATE `Properties` SET `Value`='%s' WHERE `Name`='PatchGUID'", strPatchGUID);
			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, strSql, &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "UPDATE `Properties` SET `Value`='0' WHERE `Name`='DontRemoveTempFolderWhenFinished'", &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

/*
			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "UPDATE `PatchMetadata` SET `Value`='AutoTrader Patch' WHERE `Property`='Description'", &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "UPDATE `PatchMetadata` SET `Value`='AutoTrader' WHERE `Property`='DisplayName'", &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "UPDATE `PatchMetadata` SET `Value`='Hashikun' WHERE `Property`='ManufacturerName'", &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "UPDATE `PatchMetadata` SET `Value`='http://hp.vector.co.jp/authors/VA030717/' WHERE `Property`='MoreInfoURL'", &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "UPDATE `PatchMetadata` SET `Value`='AutoTrader' WHERE `Property`='TargetProductName'", &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			COleDateTime dt = COleDateTime::GetCurrentTime();
			strSql.Format("UPDATE `PatchMetadata` SET `Value`='%d/%d/%d %d:%02d' WHERE `Property`='CreationTimeUTC'", dt.GetDay(), dt.GetMonth(), dt.GetYear(), dt.GetHour(), dt.GetMinute());
			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, strSql, &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;
*/

			if (
				ERROR_SUCCESS !=
					(
						uiRet =
							MsiDatabaseOpenView(
								hDatabase,
								"INSERT INTO `ImageFamilies` ("
									"`Family`, `MediaSrcPropName`, `MediaDiskId`, `FileSequenceStart`"
								") VALUES ("
									"'AutoTraders', 'AutoTraderSrcPropName', 2, 1000"
								")",
								&hView
							)
					)
			)
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			strSql.Format(
				"INSERT INTO `UpgradedImages` ("
					"`Upgraded`, `MsiPath`, `Family`"
				") VALUES ("
					"'AutoTrader%d', '%s', 'AutoTraders'"
				")",
				SaPatchingFPath.GetSize(),
				SaPatchingFPath[SaPatchingFPath.GetUpperBound()]
			);
			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, strSql, &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			for (i = 0; i < SaPatchingFPath.GetSize() - 1; i ++) {
				strSql.Format(
					"INSERT INTO `TargetImages` ("
						"`Target`, `MsiPath`, `Upgraded`, `Order`, `IgnoreMissingSrcFiles`"
					") VALUES ("
						"'AutoTrader%d', '%s', 'AutoTrader%d', %d, 0"
					")",
					i + 1,
					SaPatchingFPath[i],
					SaPatchingFPath.GetSize(),
					i + 1
				);
				if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, strSql, &hView)))
					break;
				if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
					break;
				if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
					break;
			}
			if (ERROR_SUCCESS != uiRet)
				break;

			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "DROP TABLE `ExternalFiles`", &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "DROP TABLE `UpgradedFilesToIgnore`", &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "DROP TABLE `PatchMetadata`", &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			if (ERROR_SUCCESS != (uiRet = MsiDatabaseOpenView(hDatabase, "DROP TABLE `PatchSequence`", &hView)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiViewExecute(hView, 0)))
				break;
			if (ERROR_SUCCESS != (uiRet = MsiCloseHandle(hView)))
				break;

			if (ERROR_SUCCESS != (uiRet = MsiDatabaseCommit(hDatabase)))
				break;
		} while (0);
		if (ERROR_SUCCESS != uiRet) {
			strRet.Format("%d, %s", uiRet, GetLastErrorMessage());
			MessageBox("Msi.dll: " + strRet);
		}
		if (hView)
			MsiCloseHandle(hView);
		if (hDatabase)
			MsiCloseHandle(hDatabase);
		if (ERROR_SUCCESS != uiRet)
			return;

		CString strLogFName = "AutoTraderInstaller.log";
		CString strLogFPath = strSetupDPathA + '\\' + strLogFName;

		CString strMsiMspFPath = "C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0\\Bin\\MsiMsp.Exe";
		strParameters = "/s " + strPcpFName + " /p " + strMspFName + " /l " + strLogFName;
		if (! CreateProcess(NULL, (LPTSTR)(LPCTSTR)('\"' + strMsiMspFPath + "\" " + strParameters), NULL, NULL, FALSE, 0, NULL, strSetupDPathA, &sInfo, &pInfo)) {
			MessageBox("CreateProcess(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
		while ((dwWaitForSingleObject = WaitForSingleObject(pInfo.hProcess, 250)) == WAIT_TIMEOUT) {
			if (dwWaitForSingleObject == WAIT_FAILED) {
				MessageBox("WaitForSingleObject(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
				return;
			}
			PumpWaitingMessages();
		}
		fileop.wFunc = FO_DELETE;
		fileop.pTo = NULL;
		strcpy(pszFromFPath, strPcpFPathC);
		pszFromFPath[strPcpFPathC.GetLength() + 1] = '\0';
		if (SHFileOperation(&fileop))
			return;
		strcpy(pszFromFPath, strLogFPath);
		pszFromFPath[strLogFPath.GetLength() + 1] = '\0';
		if (SHFileOperation(&fileop))
			return;

		CString strDocFPathA = strSetupDPathA + '\\' + strDocFName;
		if (! CopyFile(strDocFPathC, strDocFPathA, TRUE)) {
			MessageBox("CopyFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}

		CString strSetupFPathA = strSetupDPathA + "\\setup.exe";
		if (! CopyFile(strSetupFPath, strSetupFPathA, TRUE)) {
			MessageBox("CopyFile(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
		strParameters = "setup.exe /m " + strMspFName + " /n AutoTrader /v 200 /i http://hashikun0.hp.infoseek.co.jp/lib /a InstMsiA.exe /w InstMsiW.exe /c 1 /j 1";
		if (! CreateProcess(NULL, (LPTSTR)(LPCTSTR)('\"' + strMsiStuffFPath + "\" " + strParameters), NULL, NULL, FALSE, 0, NULL, strSetupDPathA, &sInfo, &pInfo)) {
			MessageBox("CreateProcess(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
			return;
		}
		for (i = 0; (dwWaitForSingleObject = WaitForSingleObject(pInfo.hProcess, 250)) == WAIT_TIMEOUT; i ++) {
			if (dwWaitForSingleObject == WAIT_FAILED) {
				MessageBox("WaitForSingleObject(): " + GetLastErrorMessage(), NULL, MB_ICONSTOP);
				return;
			}
			if (i >= 80) {
				MessageBox("WaitForSingleObject(): WAIT_TIMEOUT", NULL, MB_ICONSTOP);
				return;
			}
			PumpWaitingMessages();
		}

		if (nPackageMode)
			strCmdLine.Format("a -gw4 -d -gye%s/SETUP -gyq1 \"%s\" \"%s\\\" %s", strSetupDNameA, strLzhAFPath0, strSetupBaseDPath, strSetupDNameA);
		else
			strCmdLine.Format("a -gw4 -d -gye%s/SETUP -gyq1 \"%s\" \"%s\\\" %s", strSetupDNameA, strLzhAFPath0, strSetupBaseDPath, strSetupDNameA);
		if (Unlha(m_hWnd, strCmdLine, szOutput, 256)) {
			MessageBox("Unlha()", NULL, MB_ICONSTOP);
			return;
		}
	}
	
	CDialog::OnOK();
}

CString GetLastErrorMessage(DWORD dwLastError)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwLastError ? dwLastError : GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);
	// Process any inserts in lpMsgBuf.
	CString strMsg((LPCTSTR)lpMsgBuf);
	// Free the buffer.
	LocalFree( lpMsgBuf );

	return strMsg;
}

CString GetExceptionErrorMessage(CException* pEx)
{
	TCHAR   szCause[255];

	pEx->GetErrorMessage(szCause, 255);
	return szCause;
}

void PumpWaitingMessages()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (msg.message == WM_QUIT)
			break;
		::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		::TranslateMessage(&msg);
		::DispatchMessage (&msg);
	}
}

int CreateGuid(CString& strGuid)
{
	int nRv = -1;

	GUID guid = GUID_NULL;

	if (CoCreateGuid(&guid) == S_OK) {
		strGuid.Format(
			"{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]
		);
		nRv = 0;
	}

	return nRv;
}
