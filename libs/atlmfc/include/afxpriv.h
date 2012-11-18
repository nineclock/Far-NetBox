// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

// Note: This header file contains useful classes that are documented only
//  in the MFC Technical Notes.  These classes may change from version to
//  version, so be prepared to change your code accordingly if you utilize
//  this header.  In the future, commonly used portions of this header
//  may be moved and officially documented.

#ifndef __AFXPRIV_H__
#define __AFXPRIV_H__

#pragma once

#ifdef _DEBUG
// Special _CLIENT_BLOCK type to identifiy CObjects.
#define _AFX_CLIENT_BLOCK (_CLIENT_BLOCK|(0xc0<<16))
#endif

#ifndef __AFXADV_H__
	#include <afxadv.h>
#endif

#ifndef _INC_MALLOC
	#include <malloc.h>
#endif

#ifndef __AFXEXT_H__
	#include <afxext.h>
#endif

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, off)
#endif 

#ifdef _AFX_PACKING
#pragma pack(push, _AFX_PACKING)
#endif

/////////////////////////////////////////////////////////////////////////////
// AFXPRIV - MFC Private Classes

// Implementation structures
struct AFX_SIZEPARENTPARAMS;    // Control bar implementation
struct AFX_CMDHANDLERINFO;      // Command routing implementation

// Classes declared in this file

	//CDC
		class CPreviewDC;               // Virtual DC for print preview

	//CCmdTarget
		//CWnd
			//CView
				class CPreviewView;     // Print preview view
		//CFrameWnd
			class COleCntrFrameWnd;
			//CMiniFrameWnd
				class CMiniDockFrameWnd;

class CDockContext;                     // for dragging control bars

/////////////////////////////////////////////////////////////////////////////

#undef AFX_DATA
#define AFX_DATA AFX_CORE_DATA

/////////////////////////////////////////////////////////////////////////////
// Global ID ranges (see Technical note TN020 for more details)

// 8000 -> FFFF command IDs (used for menu items, accelerators and controls)
#define IS_COMMAND_ID(nID)  ((nID) & 0x8000)

// 8000 -> DFFF : user commands
// E000 -> EFFF : AFX commands and other things
// F000 -> FFFF : standard windows commands and other things etc
	// E000 -> E7FF standard commands
	// E800 -> E8FF control bars (first 32 are special)
	// E900 -> EEFF standard window controls/components
	// EF00 -> EFFF SC_ menu help
	// F000 -> FFFF standard strings
#define ID_COMMAND_FROM_SC(sc)  (((sc - 0xF000) >> 4) + AFX_IDS_SCFIRST)

// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : user resources
// 7000 -> 7FFF : AFX (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

/////////////////////////////////////////////////////////////////////////////
// Context sensitive help support (see Technical note TN028 for more details)

// Help ID bases
#define HID_BASE_COMMAND    0x00010000UL        // ID and IDM
#define HID_BASE_RESOURCE   0x00020000UL        // IDR and IDD
#define HID_BASE_PROMPT     0x00030000UL        // IDP
#define HID_BASE_NCAREAS    0x00040000UL
#define HID_BASE_CONTROL    0x00050000UL        // IDC
#define HID_BASE_DISPATCH   0x00060000UL        // IDispatch help codes

/////////////////////////////////////////////////////////////////////////////
// Internal AFX Windows messages (see Technical note TN024 for more details)
// (0x0360 - 0x037F are reserved for MFC)

#define WM_QUERYAFXWNDPROC  0x0360  // lResult = 1 if processed by AfxWndProc
#define WM_SIZEPARENT       0x0361  // lParam = &AFX_SIZEPARENTPARAMS
#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
									// lParam = lpszOther (or NULL)
#define WM_IDLEUPDATECMDUI  0x0363  // wParam == bDisableIfNoHandler
#define WM_INITIALUPDATE    0x0364  // (params unused) - sent to children
#define WM_COMMANDHELP      0x0365  // lResult = TRUE/FALSE,
									// lParam = dwContext
#define WM_HELPHITTEST      0x0366  // lResult = dwContext,
									// lParam = MAKELONG(x,y)
#define WM_EXITHELPMODE     0x0367  // (params unused)
#define WM_RECALCPARENT     0x0368  // force RecalcLayout on frame window
									//  (only for inplace frame windows)
#define WM_SIZECHILD        0x0369  // special notify from COleResizeBar
									// wParam = ID of child window
									// lParam = lpRectNew (new position/size)
#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#define WM_QUERYCENTERWND   0x036B  // lParam = HWND to use as centering parent
#define WM_DISABLEMODAL     0x036C  // lResult = 0, disable during modal state
									// lResult = 1, don't disable
#define WM_FLOATSTATUS      0x036D  // wParam combination of FS_* flags below

// WM_ACTIVATETOPLEVEL is like WM_ACTIVATEAPP but works with hierarchies
//   of mixed processes (as is the case with OLE in-place activation)
#define WM_ACTIVATETOPLEVEL 0x036E  // wParam = nState (like WM_ACTIVATE)
									// lParam = pointer to HWND[2]
									//  lParam[0] = hWnd getting WM_ACTIVATE
									//  lParam[1] = hWndOther

#define WM_RESERVED_036F	0x036F  // was WM_QUERY3DCONTROLS (now not used)

// Note: Messages 0x0370, 0x0371, and 0x372 were incorrectly used by
//  some versions of Windows.  To remain compatible, MFC does not
//  use messages in that range.
#define WM_RESERVED_0370    0x0370
#define WM_RESERVED_0371    0x0371
#define WM_RESERVED_0372    0x0372

// WM_SOCKET_NOTIFY and WM_SOCKET_DEAD are used internally by MFC's
// Windows sockets implementation.  For more information, see sockcore.cpp
#define WM_SOCKET_NOTIFY    0x0373
#define WM_SOCKET_DEAD      0x0374

// same as WM_SETMESSAGESTRING except not popped if IsTracking()
#define WM_POPMESSAGESTRING 0x0375

// WM_HELPPROMPTADDR is used internally to get the address of 
//	m_dwPromptContext from the associated frame window. This is used
//	during message boxes to setup for F1 help while that msg box is
//	displayed. lResult is the address of m_dwPromptContext.
#define WM_HELPPROMPTADDR	0x0376

// Constants used in DLGINIT resources for OLE control containers
// NOTE: These are NOT real Windows messages they are simply tags
// used in the control resource and are never used as 'messages'
#define WM_OCC_LOADFROMSTREAM           0x0376
#define WM_OCC_LOADFROMSTORAGE          0x0377
#define WM_OCC_INITNEW                  0x0378
#define WM_OCC_LOADFROMSTREAM_EX        0x037A
#define WM_OCC_LOADFROMSTORAGE_EX       0x037B

// Constant used in DLGINIT resources for MFC controls
#define WM_MFC_INITCTRL                 0x037C

// Marker used while rearranging the message queue
#define WM_QUEUE_SENTINEL   0x0379

// Note: Messages 0x037D - 0x37E reserved for future MFC use.
#define WM_RESERVED_037D    0x037D
#define WM_RESERVED_037E    0x037E

// WM_FORWARDMSG - used by ATL to forward a message to another window for processing
//	WPARAM - DWORD dwUserData - defined by user
//	LPARAM - LPMSG pMsg - a pointer to the MSG structure
//	return value - 0 if the message was not processed, nonzero if it was
#define WM_FORWARDMSG		0x037F

// like ON_MESSAGE but no return value
#define ON_MESSAGE_VOID(message, memberFxn) \
	{ message, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(void (AFX_MSG_CALL CWnd::*)(void))&memberFxn },

// special struct for WM_SIZEPARENT
struct AFX_SIZEPARENTPARAMS
{
	HDWP hDWP;       // handle for DeferWindowPos
	RECT rect;       // parent client rectangle (trim as appropriate)
	SIZE sizeTotal;  // total size on each side as layout proceeds
	BOOL bStretch;   // should stretch to fill all space
};

// flags for wParam in the WM_FLOATSTATUS message
enum {  FS_SHOW = 0x01, FS_HIDE = 0x02,
		FS_ACTIVATE = 0x04, FS_DEACTIVATE = 0x08,
		FS_ENABLE = 0x10, FS_DISABLE = 0x20,
		FS_SYNCACTIVE = 0x40 };

void AFXAPI AfxRepositionWindow(AFX_SIZEPARENTPARAMS* lpLayout,
	HWND hWnd, LPCRECT lpRect);

/////////////////////////////////////////////////////////////////////////////
// Implementation of command routing

struct AFX_CMDHANDLERINFO
{
	CCmdTarget* pTarget;
	void (AFX_MSG_CALL CCmdTarget::*pmf)(void);
};

/////////////////////////////////////////////////////////////////////////////
// Robust file save support
// opens a temp file if modeCreate specified and enough free space
// renaming, etc occurs automatically if everything succeeds

class CMirrorFile : public CFile
{
// Implementation
public:
	virtual void Abort();
	virtual void Close();
	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);

protected:
	CString m_strMirrorName;
};

/////////////////////////////////////////////////////////////////////////////
// Implementation of PrintPreview

class CPreviewDC : public CDC
{
	DECLARE_DYNAMIC(CPreviewDC)

public:
	virtual void SetAttribDC(HDC hDC);  // Set the Attribute DC
	virtual void SetOutputDC(HDC hDC);

	virtual void ReleaseOutputDC();

// Constructors
	CPreviewDC();

// Implementation
public:
	virtual ~CPreviewDC();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void SetScaleRatio(int nNumerator, int nDenominator);
	void SetTopLeftOffset(CSize TopLeft);
	void ClipToPage();

	// These conversion functions can be used without an output DC

	void PrinterDPtoScreenDP(LPPOINT lpPoint) const;

// Device-Context Functions
	virtual int SaveDC();
	virtual BOOL RestoreDC(int nSavedDC);

public:
	virtual CGdiObject* SelectStockObject(int nIndex);
	virtual CFont* SelectObject(CFont* pFont);

// Drawing-Attribute Functions
	virtual COLORREF SetBkColor(COLORREF crColor);
	virtual COLORREF SetTextColor(COLORREF crColor);

// Mapping Functions
	virtual int SetMapMode(int nMapMode);
	virtual CPoint SetViewportOrg(int x, int y);
	virtual CPoint OffsetViewportOrg(int nWidth, int nHeight);
	virtual CSize SetViewportExt(int x, int y);
	virtual CSize ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom);
	virtual CSize SetWindowExt(int x, int y);
	virtual CSize ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom);

// Text Functions
	virtual BOOL TextOut(int x, int y, LPCTSTR lpszString, int nCount);
	virtual BOOL ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect,
				LPCTSTR lpszString, UINT nCount, LPINT lpDxWidths);
	virtual CSize TabbedTextOut(int x, int y, LPCTSTR lpszString, int nCount,
				int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
	virtual int _AFX_FUNCNAME(DrawText)(LPCTSTR lpszString, int nCount, LPRECT lpRect,
				UINT nFormat);
	virtual int _AFX_FUNCNAME(DrawTextEx)(_In_count_(nCount) LPTSTR lpszString, int nCount, LPRECT lpRect,
				UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
#pragma push_macro("DrawText")
#pragma push_macro("DrawTextEx")
#undef DrawText
#undef DrawTextEx
	int DrawText(LPCTSTR lpszString, int nCount, LPRECT lpRect,
				UINT nFormat)
	{
		return _AFX_FUNCNAME(DrawText)(lpszString, nCount, lpRect, nFormat);
	}
	int DrawTextEx(_In_count_(nCount) LPTSTR lpszString, int nCount, LPRECT lpRect,
				UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
	{
		return _AFX_FUNCNAME(DrawTextEx)(lpszString, nCount, lpRect, nFormat, lpDTParams);
	}
#pragma pop_macro("DrawText")
#pragma pop_macro("DrawTextEx")
	virtual BOOL GrayString(CBrush* pBrush,
				BOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, int),
					LPARAM lpData, int nCount,
					int x, int y, int nWidth, int nHeight);

// Printer Escape Functions
	virtual int Escape(int nEscape, int nCount, LPCSTR lpszInData, LPVOID lpOutData);

// Implementation
protected:
	void MirrorMappingMode(BOOL bCompute);
	void MirrorViewportOrg();
	void MirrorFont();
	void MirrorAttributes();

	CSize ComputeDeltas(int& x, _In_z_ LPCTSTR lpszString, UINT& nCount, _In_ BOOL bTabbed,
					_In_ UINT nTabStops, _In_count_(nTabStops) LPINT lpnTabStops, _In_ int nTabOrigin,
					_Pre_notnull_ _Post_z_ LPTSTR lpszOutputString, int* pnDxWidths, int& nRightFixup);

protected:
	int m_nScaleNum;    // Scale ratio Numerator
	int m_nScaleDen;    // Scale ratio Denominator
	int m_nSaveDCIndex; // DC Save index when Screen DC Attached
	int m_nSaveDCDelta; // delta between Attrib and output restore indices
	CSize m_sizeTopLeft;// Offset for top left corner of page
	HFONT m_hFont;      // Font selected into the screen DC (NULL if none)
	HFONT m_hPrinterFont; // Font selected into the print DC

	CSize m_sizeWinExt; // cached window extents computed for screen
	CSize m_sizeVpExt;  // cached viewport extents computed for screen
};

// Zoom States
#define _AFX_ZOOM_OUT    0
#define _AFX_ZOOM_MIDDLE 1
#define _AFX_ZOOM_IN     2

#ifndef _AFX_USE_OLD_ZOOM
#define _AFX_USE_OLD_ZOOM 1
#endif

#if _AFX_USE_OLD_ZOOM
#define ZOOM_OUT    _AFX_ZOOM_OUT
#define ZOOM_MIDDLE _AFX_ZOOM_MIDDLE
#define ZOOM_IN     _AFX_ZOOM_IN
#endif

/////////////////////////////////////////////////////////////////////////////
// mirroring support

// some mirroring stuff will be in wingdi.h someday
#ifndef LAYOUT_LTR
#define LAYOUT_LTR								 0x00000000	
#endif

/////////////////////////////////////////////////////////////////////////////
// toolbar docking support

class CDockContext
{
public:
// Construction
	explicit CDockContext(CControlBar* pBar);

// Attributes
	CPoint m_ptLast;            // last mouse position during drag
	CRect m_rectLast;
	CSize m_sizeLast;
	BOOL m_bDitherLast;

	// Rectangles used during dragging or resizing
	CRect m_rectDragHorz;
	CRect m_rectDragVert;
	CRect m_rectFrameDragHorz;
	CRect m_rectFrameDragVert;

	CControlBar* m_pBar;        // the toolbar that created this context
	CFrameWnd* m_pDockSite;     // the controlling frame of the CControlBar
	DWORD m_dwDockStyle;        // allowable dock styles for bar
	DWORD m_dwOverDockStyle;    // style of dock that rect is over
	DWORD m_dwStyle;            // style of control bar
	BOOL m_bFlip;               // if shift key is down
	BOOL m_bForceFrame;         // if ctrl key is down

	CDC* m_pDC;                 // where to draw during drag
	BOOL m_bDragging;
	int m_nHitTest;

	UINT m_uMRUDockID;
	CRect m_rectMRUDockPos;

	DWORD m_dwMRUFloatStyle;
	CPoint m_ptMRUFloatPos;

// Drag Operations
	virtual void StartDrag(CPoint pt);
	void Move(CPoint pt);       // called when mouse has moved
	void EndDrag();             // drop
	void OnKey(int nChar, BOOL bDown);

// Resize Operations
	virtual void StartResize(int nHitTest, CPoint pt);
	void Stretch(CPoint pt);
	void EndResize();

// Double Click Operations
	virtual void ToggleDocking();

// Operations
	void InitLoop();
	void CancelLoop();

// Implementation
public:
	virtual ~CDockContext();
	BOOL Track();
	void DrawFocusRect(BOOL bRemoveRect = FALSE);
		// draws the correct outline
	void UpdateState(BOOL* pFlag, BOOL bNewValue);
	DWORD CanDock();
	CDockBar* GetDockBar(DWORD dwOverDockStyle);
};

/////////////////////////////////////////////////////////////////////////////
// CControlBarInfo - used for docking serialization

class CControlBarInfo
{
public:
// Implementation
	CControlBarInfo();

// Attributes
	UINT m_nBarID;      // ID of this bar
	BOOL m_bVisible;    // visibility of this bar
	BOOL m_bFloating;   // whether floating or not
	BOOL m_bHorz;       // orientation of floating dockbar
	BOOL m_bDockBar;    // TRUE if a dockbar
	CPoint m_pointPos;  // topleft point of window

	UINT m_nMRUWidth;   // MRUWidth for Dynamic Toolbars
	BOOL m_bDocking;    // TRUE if this bar has a DockContext
	UINT m_uMRUDockID;  // most recent docked dockbar
	CRect m_rectMRUDockPos; // most recent docked position
	DWORD m_dwMRUFloatStyle; // most recent floating orientation
	CPoint m_ptMRUFloatPos; // most recent floating position

	CUIntArray m_arrBarID;   // bar IDs for bars contained within this one
	CControlBar* m_pBar;    // bar which this refers to (transient)

	void Serialize(CArchive& ar, CDockState* pDockState);
	BOOL LoadState(LPCTSTR lpszProfileName, int nIndex, CDockState* pDockState);
	BOOL SaveState(LPCTSTR lpszProfileName, int nIndex);
};

/////////////////////////////////////////////////////////////////////////////
// CDialogTemplate

class CDialogTemplate
{
// Constructors
public:
	/* explicit */ CDialogTemplate(const DLGTEMPLATE* pTemplate = NULL);
	explicit CDialogTemplate(HGLOBAL hGlobal);

// Attributes
	BOOL HasFont() const;
	BOOL SetFont(LPCTSTR lpFaceName, WORD nFontSize);
	BOOL SetSystemFont(WORD nFontSize = 0);
	BOOL GetFont(CString& strFaceName, WORD& nFontSize) const;
	void GetSizeInDialogUnits(SIZE* pSize) const;
	void GetSizeInPixels(SIZE* pSize) const;

	static BOOL AFX_CDECL GetFont(const DLGTEMPLATE* pTemplate,
		CString& strFaceName, WORD& nFontSize);

// Operations
	BOOL Load(LPCTSTR lpDialogTemplateID);
	HGLOBAL Detach();

// Implementation
public:
	~CDialogTemplate();

	HGLOBAL m_hTemplate;
	DWORD m_dwTemplateSize;
	BOOL m_bSystemFont;

protected:
	static BYTE* AFX_CDECL GetFontSizeField(const DLGTEMPLATE* pTemplate);
	static UINT AFX_CDECL GetTemplateSize(const DLGTEMPLATE* pTemplate);
	BOOL SetTemplate(const DLGTEMPLATE* pTemplate, UINT cb);
};

/////////////////////////////////////////////////////////////////////////////
// WM_NOTIFY support

struct AFX_NOTIFY
{
	LRESULT* pResult;
	NMHDR* pNMHDR;
};


////////////////////////////////////////////////////////////////////////////
// other global state
class CPushRoutingFrame
{
protected:
	CFrameWnd* pOldRoutingFrame;
	_AFX_THREAD_STATE* pThreadState;
   CPushRoutingFrame* pOldPushRoutingFrame;

public:
	explicit CPushRoutingFrame(CFrameWnd* pNewRoutingFrame)
	{ 
		pThreadState = AfxGetThreadState();
	  pOldPushRoutingFrame = pThreadState->m_pPushRoutingFrame;
		pOldRoutingFrame = pThreadState->m_pRoutingFrame;
		pThreadState->m_pRoutingFrame = pNewRoutingFrame;
	  pThreadState->m_pPushRoutingFrame = this;
	}
	~CPushRoutingFrame()
	{ 
	  if (pThreadState != NULL)
	  {
		 ASSERT( pThreadState->m_pPushRoutingFrame == this );
		 pThreadState->m_pRoutingFrame = pOldRoutingFrame;
		 pThreadState->m_pPushRoutingFrame = pOldPushRoutingFrame;
	  }
   }
   void Pop()
   {
	  ENSURE( pThreadState != NULL );
	  ASSERT( pThreadState->m_pPushRoutingFrame == this );
	  pThreadState->m_pRoutingFrame = pOldRoutingFrame;
	  pThreadState->m_pPushRoutingFrame = pOldPushRoutingFrame;
	  pThreadState = NULL;
   }
};

/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
void AFXAPI AfxHookWindowCreate(CWnd* pWnd);
BOOL AFXAPI AfxUnhookWindowCreate();
void AFXAPI AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

// string helpers
void AFXAPI AfxSetWindowText(HWND hWndCtrl, LPCTSTR lpszNew);
int AFXAPI AfxLoadString(_In_ UINT nIDS, _Out_z_cap_post_count_(nMaxBuf, return + 1) LPSTR lpszBuf, _In_ UINT nMaxBuf = 256);
int AFXAPI AfxLoadString(_In_ UINT nIDS, _Out_z_cap_post_count_(nMaxBuf, return + 1) LPWSTR lpszBuf, _In_ UINT nMaxBuf = 256);

// registry helpers

/// <summary>
/// Creates the specified registry key.</summary>
/// <returns> 
/// If the function succeeds, the return value is ERROR_SUCCESS. If the function fails, the return value is a nonzero error code defined in Winerror.h</returns>
/// <param name="hKey">A handle to an open registry key.</param>
/// <param name="lpSubKey">The name of a key that this function opens or creates.</param>
/// <param name="phkResult">A pointer to a variable that receives a handle to the opened or created key.</param>
/// <param name="pTM">Pointer to CAtlTransactionManager object</param>
LONG AFXAPI AfxRegCreateKey(HKEY hKey, LPCTSTR lpSubKey, PHKEY phkResult, CAtlTransactionManager* pTM = NULL);

/// <summary>
/// Opens the specified registry key.</summary>
/// <returns> 
/// If the function succeeds, the return value is ERROR_SUCCESS. If the function fails, the return value is a nonzero error code defined in Winerror.h</returns>
/// <param name="hKey">A handle to an open registry key.</param>
/// <param name="lpSubKey">The name of a key that this function opens or creates.</param>
/// <param name="phkResult">A pointer to a variable that receives a handle to the created key.</param>
/// <param name="pTM">Pointer to CAtlTransactionManager object</param>
LONG AFXAPI AfxRegOpenKey(HKEY hKey, LPCTSTR lpSubKey, PHKEY phkResult, CAtlTransactionManager* pTM = NULL);

/// <summary>
/// Opens the specified registry key.</summary>
/// <returns> 
/// If the function succeeds, the return value is ERROR_SUCCESS. If the function fails, the return value is a nonzero error code defined in Winerror.h</returns>
/// <param name="hKey">A handle to an open registry key.</param>
/// <param name="lpSubKey">The name of a key that this function opens or creates.</param>
/// <param name="ulOptions">This parameter is reserved and must be zero.</param>
/// <param name="samDesired">A mask that specifies the desired access rights to the key.</param>
/// <param name="phkResult">A pointer to a variable that receives a handle to the openedkey.</param>
/// <param name="pTM">Pointer to CAtlTransactionManager object</param>
LONG AFXAPI AfxRegOpenKeyEx(HKEY hKey, LPCTSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult, CAtlTransactionManager* pTM = NULL);

LONG AFXAPI AfxRegQueryValue(HKEY hKey, LPCTSTR lpSubKey, LPTSTR lpValue, PLONG lpcbValue);
LONG AFXAPI AfxRegSetValue(HKEY hKey, LPCTSTR lpSubKey, DWORD dwType,  LPCTSTR lpData, DWORD cbData);

/// <summary>
/// Deletes the specified registry key.</summary>
/// <returns> 
/// If the function succeeds, the return value is ERROR_SUCCESS. If the function fails, the return value is a nonzero error code defined in Winerror.h</returns>
/// <param name="hKey">A handle to an open registry key.</param>
/// <param name="lpSubKey">The name of the key to be deleted.</param>
/// <param name="pTM">Pointer to CAtlTransactionManager object</param>
LONG AFXAPI AfxRegDeleteKey(HKEY hKey, LPCTSTR lpSubKey, CAtlTransactionManager* pTM = NULL);

HDC AFXAPI AfxCreateDC(HGLOBAL hDevNames, HGLOBAL hDevMode);

void AFXAPI AfxGetModuleFileName(HINSTANCE hInst, CString& strFileName);
void AFXAPI AfxGetModuleShortFileName(HINSTANCE hInst, CString& strShortName);

// Failure dialog helpers
void AFXAPI AfxFailMaxChars(CDataExchange* pDX, int nChars);
void AFXAPI AfxFailRadio(CDataExchange* pDX);

// 2008 Feature Pack Support
BOOL AFXAPI AfxIsExtendedFrameClass(CWnd* pWnd);
BOOL AFXAPI AfxIsMFCToolBar(CWnd* pWnd);

#ifndef __AFXCONV_H__
#include <afxconv.h>
#endif

/////////////////////////////////////////////////////////////////////////////

#ifdef _AFX_PACKING
#pragma pack(pop)
#endif

#undef AFX_DATA
#define AFX_DATA

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, on)
#endif

#endif // __AFXPRIV_H__

/////////////////////////////////////////////////////////////////////////////

#ifndef __AFXPRIV2_H__
#include <afxpriv2.h>
#endif