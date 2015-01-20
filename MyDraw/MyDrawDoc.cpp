// MyDrawDoc.cpp : implementation of the CMyDrawDoc class
//

#include "stdafx.h"
#include "MyDraw.h"

#include "MyDrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDrawDoc

IMPLEMENT_DYNCREATE(CMyDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDrawDoc, CDocument)
END_MESSAGE_MAP()


// CMyDrawDoc construction/destruction

CMyDrawDoc::CMyDrawDoc()
{
	// TODO: add one-time construction code here

}

CMyDrawDoc::~CMyDrawDoc()
{
}

BOOL CMyDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMyDrawDoc serialization

void CMyDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMyDrawDoc diagnostics

#ifdef _DEBUG
void CMyDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyDrawDoc commands
