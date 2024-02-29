#include "afxwin.h"

class CMyWindow : public CFrameWnd {
public:

	CMyWindow() {

		RECT myRect;
		myRect.left = 0;
		myRect.right = 800;
		myRect.top = 0;
		myRect.bottom = 600;

		Create(NULL, "Задача со скобками", WS_OVERLAPPEDWINDOW, myRect, nullptr, nullptr, WS_EX_WINDOWEDGE, nullptr);

		RECT buttonRect;
		buttonRect.left = 10;
		buttonRect.top = 100;
		buttonRect.right = 100;
		buttonRect.bottom = 140;

		myButton.Create("Проверка", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, buttonRect, this, 1);

		CRect editRect(10, 10, 200, 30);
		editBox.Create(
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
			editRect,
			this,
			3);

	}

protected:

	void OnButtonClicked() {

		CString text;
		editBox.GetWindowTextA(text);

		int length = text.GetLength();
		char* buffer = new char[length + 1];

		strcpy_s(buffer, length + 1, text);

		if (length == 0)
		{
			return;
		}

		int openBrackets = 0;
		int closedBrackets = 0;
		bool isBracketsCorrect = true;

		for (int i = 0; i < length; i++)
		{
			if (buffer[i] == '(')
			{
				openBrackets++;
			}
			else if (buffer[i] == ')')
			{
				closedBrackets++;
			}

			if (closedBrackets > openBrackets)
			{
				isBracketsCorrect = false;
				break;
			}
			if (i == length - 1 && openBrackets != closedBrackets)
			{
				isBracketsCorrect = false;
				break;
			}
		}

		MessageBox(isBracketsCorrect ? "Верно" : "Неверно", "Проверка", MB_OK);

	}

	CButton myButton;
	CEdit editBox;

	DECLARE_MESSAGE_MAP();

};

BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd)
	ON_COMMAND(1, &CMyWindow::OnButtonClicked)
END_MESSAGE_MAP()

class CMyApp : CWinApp {
	virtual BOOL InitApplication() {

		this->m_pMainWnd = new CMyWindow();
		this->m_pMainWnd->ShowWindow(SW_SHOW);
		this->m_pMainWnd->UpdateWindow();

		return TRUE;

	}

};

CMyApp myApplication;
