#include "afxwin.h"

class CMyWindow : public CFrameWnd {
public:

	CMyWindow() { // Начало определения конструктора класса

		RECT myRect; // Создание структуры RECT для определения размеров и положения окна
		myRect.left = 0; // Установка левой координаты окна
		myRect.right = 800; // Установка правой координаты окна
		myRect.top = 0; // Установка верхней координаты окна
		myRect.bottom = 600; // Установка нижней координаты окна

		Create(NULL, "Задача со скобками", WS_OVERLAPPEDWINDOW, myRect, nullptr, nullptr, WS_EX_WINDOWEDGE, nullptr);
		// Создание окна с заданными параметрами, включая заголовок и стиль окна

		RECT buttonRect; // Создание структуры RECT для определения размеров и положения кнопки
		buttonRect.left = 10; // Установка левой координаты кнопки
		buttonRect.top = 100; // Установка верхней координаты кнопки
		buttonRect.right = 100; // Установка правой координаты кнопки
		buttonRect.bottom = 140; // Установка нижней координаты кнопки

		myButton.Create("Проверка", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, buttonRect, this, 1);
		// Создание кнопки с заданными параметрами

		CRect editRect(10, 10, 200, 30); // Создание объекта CRect для задания размеров и положения поля ввода
		editBox.Create(
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
			editRect,
			this,
			3);

		// Создание текстового поля с заданными параметрами и стилями

	} // Конец определения конструктора класса

protected: // Область видимости для защищённых членов класса

	void OnButtonClicked() { // Начало определения функции-обработчика нажатия кнопки

		CString text; // Объявление переменной типа CString для хранения текста из текстового поля
		editBox.GetWindowTextA(text); // Получение текста из текстового поля и сохранение в переменной text

		int length = text.GetLength(); // Получение длины строки CString
		char* buffer = new char[length + 1]; // Выделение памяти под буфер +1 для завершающего нулевого символа

		// Копирование содержимого CString в буфер
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

		// Вывод сообщения с текстом из текстового поля

	} // Конец определения функции-обработчика нажатия кнопки

	CButton myButton; // Создание кнопки
	CEdit editBox; // Создание текстового поля

	DECLARE_MESSAGE_MAP(); // Объявление таблицы соответствий сообщений

};

BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd) // Начало определения таблицы соответствий сообщений для класса CMyWindow
	ON_COMMAND(1, &CMyWindow::OnButtonClicked) // Определение обработчика нажатия кнопки
END_MESSAGE_MAP() // Конец определения таблицы соответствий сообщений

class CMyApp : CWinApp { // Определение класса CMyApp, управляющего созданием и инициализацией главного окна
	virtual BOOL InitApplication() { // Переопределение функции инициализации приложения

		this->m_pMainWnd = new CMyWindow(); // Создание экземпляра главного окна приложения
		this->m_pMainWnd->ShowWindow(SW_SHOW); // Отображение главного окна
		this->m_pMainWnd->UpdateWindow(); // Обновление содержимого главного окна

		return TRUE; // Успешное завершение инициализации приложения

	} // Конец определения функции инициализации приложения

};

CMyApp myApplication; // Создание экземпляра класса CMyApp, запускающего приложение
