//	CMainSession.cpp
//
//	CMainSession class
//	Copyright (c) 2015 by Kronosaur Productions, LLC. All Rights Reserved.

#include "PreComp.h"

CMainSession::CMainSession (CHumanInterface &HI, CTransmuterModel &model) : IHISession(HI),
	m_Model(model),
	m_Panel(CPanel(this, 0, 0, HI.GetScreen().GetWidth(), HI.GetScreen().GetHeight())),
	m_IsRButtonDown(0)
	//	CMainSession constructor
	{
	CPanel *pEmptyPanel = m_Panel.InternalPanels.AddPanel(0, 0, 200, m_Panel.PanelRect.GetHeight(), false);

	CContextSession *pExtensionNavigatorSession = new CContextSession(HI, *pEmptyPanel, m_Model.GetExtensionsArray());
	m_aSubSessions.Insert(pExtensionNavigatorSession);
	}

CMainSession::~CMainSession(void)
	{
	m_aSubSessions.DeleteAll();

	delete &m_Panel;
	}

void CMainSession::OnLButtonDown(int x, int y, DWORD dwFlags, bool *retbCapture)
	{
	TArray <CTransmuterSession *> RelevantSessions = m_Panel.GetSessionsContainingPoint(x, y);

	for (int i = 0; i < RelevantSessions.GetCount(); i++)
		{
		RelevantSessions[i]->OnLButtonDown(x, y, dwFlags, retbCapture);
		}
	}

void CMainSession::OnLButtonUp(int x, int y, DWORD dwFlags)
	{
	TArray <CTransmuterSession *> RelevantSessions = m_Panel.GetSessionsContainingPoint(x, y);

	for (int i = 0; i < RelevantSessions.GetCount(); i++)
		{
		RelevantSessions[i]->OnLButtonUp(x, y, dwFlags);
		}
	}

void CMainSession::OnRButtonDown(int x, int y, DWORD dwFlags)
	{
	TArray <CTransmuterSession *> RelevantSessions = m_Panel.GetSessionsContainingPoint(x, y);

	for (int i = 0; i < RelevantSessions.GetCount(); i++)
		{
		RelevantSessions[i]->OnRButtonDown(x, y, dwFlags);
		}
	}

void CMainSession::OnRButtonUp(int x, int y, DWORD dwFlags)
	{
	TArray <CTransmuterSession *> RelevantSessions = m_Panel.GetSessionsContainingPoint(x, y);

	for (int i = 0; i < RelevantSessions.GetCount(); i++)
		{
		RelevantSessions[i]->OnRButtonUp(x, y, dwFlags);
		}
	}

void CMainSession::OnPaint(CG32bitImage &Screen, const RECT &rcInvalid)
	{
	//	paint the background GRAY: 32, 32, 32
	Screen.Fill(0, 0, Screen.GetWidth(), Screen.GetHeight(), CG32bitPixel(32, 32, 32));

	RECT rcClip;
	//	call paint functions of all subsessions
	for (int i = 0; i < m_aSubSessions.GetCount(); i++)
		{
		CTransmuterSession *pSubSession = m_aSubSessions[i];
		rcClip = (m_aSubSessions[i]->GetAssociatedPanel()).PanelRect.GetAsRect();
		Screen.SetClipRect(rcClip);
		m_aSubSessions[i]->OnPaint(Screen, rcInvalid);
		}
	Screen.ResetClipRect();
	} 