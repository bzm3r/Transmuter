//	BasicPanelContents.cpp
//
//	Definitions of the basic sessions declared in BasicPanelContents.h
//	Copyright (c) 2015 by Kronosaur Productions, LLC. All Rights Reserved.

#include "PreComp.h"

#pragma once

IPanelContent::IPanelContent(CString sContentName, CHumanInterface &HI, CPanel &AssociatedPanel) : IHISession(HI),
m_AssociatedPanel(AssociatedPanel),
m_rgbBackgroundColor(CG32bitPixel(0, 0, 0)),
m_rgbPanelOutlineColor(CG32bitPixel(255, 255, 255))
	{
	}

void IPanelContent::DrawPanelOutline(CG32bitImage &Screen)
	{
	RECT PanelRect = this->GetAssociatedPanel().PanelRect.GetAsRect();

	//  corners are numbered starting from top left hand corner being zero, and then going counter clockwise

	int c0x = PanelRect.left;
	int c0y = PanelRect.top;

	int c1x = PanelRect.right;
	int c1y = c0y;

	int c2x = c1x;
	int c2y = PanelRect.bottom;

	int c3x = c0x;
	int c3y = c2y;

	Screen.DrawLine(c0x, c0y, c1x, c1y, 1, m_rgbPanelOutlineColor);
	Screen.DrawLine(c1x, c1y, c2x, c2y, 1, m_rgbPanelOutlineColor);
	Screen.DrawLine(c2x, c2y, c3x, c3y, 1, m_rgbPanelOutlineColor);
	Screen.DrawLine(c3x, c3y, c0x, c0y, 1, m_rgbPanelOutlineColor);
	}

//  =======================================================================

CTransmuterPanelContent::CTransmuterPanelContent (CString sContentName, CHumanInterface &HI, CPanel &AssociatedPanel, CTransmuterModel &model) : IPanelContent(sContentName, HI, AssociatedPanel),
	m_HeaderPanelContent(NULL),
	m_sContentName(m_sContentName),
	m_model(model)
	{
	};

CTransmuterPanelContent::~CTransmuterPanelContent(void)
	{
	if (m_HeaderPanelContent != NULL)
		{
		delete m_HeaderPanelContent;
		}
	}

//  =======================================================================

CHeaderPanelContent::CHeaderPanelContent(CString sParentSessionName, CHumanInterface & HI, CPanel &AssociatedPanel, CTransmuterPanelContent &AssociatedSession) : IPanelContent(strCat(sParentSessionName, CONSTLIT(".Header")), HI, AssociatedPanel),
	m_font((g_pHI->GetVisuals()).GetFont(fontConsoleMediumHeavy)),
	m_rgbTextColor(CG32bitPixel(255,255,255)),
	m_rgbBackgroundColor(CG32bitPixel(110,110,110))
	{
	};

CHeaderPanelContent::~CHeaderPanelContent(void)
	{
	}

void CHeaderPanelContent::OnPaint(CG32bitImage &Screen, const RECT &rcInvalid)
	{
	CPanel &refAssociatedPanel = this->GetAssociatedPanel();
	Screen.Fill(0, 0, refAssociatedPanel.PanelRect.GetWidth(), refAssociatedPanel.PanelRect.GetWidth(), m_rgbBackgroundColor);

	CG32bitPixel TextColor = CG32bitPixel(255, 255, 255);

	const CVisualPalette &VI = g_pHI->GetVisuals();
	const CG16bitFont &font = VI.GetFont(fontConsoleMediumHeavy);

	Screen.DrawText(Screen.GetWidth() / 2, Screen.GetHeight() / 2, m_font, m_rgbTextColor, CONSTLIT("Loading..."));
	}

