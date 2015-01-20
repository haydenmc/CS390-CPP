// MyDrawDoc.h : interface of the CMyDrawDoc class
//


#pragma once

#include "Drawing.h"

class CMyDrawDoc : public CDocument
{
protected: // create from serialization only
	CMyDrawDoc();
	DECLARE_DYNCREATE(CMyDrawDoc)

// Attributes
public:
	Drawing drawing;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMyDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


