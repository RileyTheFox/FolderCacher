#include "MainWindow.h"

PCWSTR MainWindow::ClassName() const
{
	return L"FolderCacher";
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        AddControls();
        return 0;
    case WM_CLOSE:
        if (MessageBox(m_hwnd, L"Do you really want to quit?", ClassName(), MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(m_hwnd);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(m_hwnd, &ps);
    }
    return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE; 
}

void MainWindow::AddControls()
{
    HWND hwndButton = CreateWindowW(L"Button", L"Open File", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 10, 150, 36, m_hwnd, (HMENU)OPEN_FILE_BUTTON, NULL, NULL);
    SendMessageW(hwndButton, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
}