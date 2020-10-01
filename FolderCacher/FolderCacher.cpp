// FolderCacher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <string>
#include <Windows.h>
#include <filesystem>

#include "MainWindow.h"

constexpr LPCWSTR CLASS_NAME =  L"FolderCacher";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void GetFolderSize(std::string folder, unsigned long long& f_size);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
//#if !_DEBUG
//    FreeConsole();
//#endif

    //WNDCLASS wc = {};

    //wc.lpfnWndProc = WindowProc;
    //wc.hInstance = hInstance;
    //wc.lpszClassName = CLASS_NAME;

    //RegisterClass(&wc);

    //// Create the window

    //HWND hwnd = CreateWindowExW(0, CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    //if (hwnd == NULL)
    //{
    //    return 0;
    //}

    MainWindow win;

    if (!win.Create(L"FolderCacher", WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;

    /*std::string folder;

    if (argc == 2)
    {
        folder = std::string(argv[1]);

        WIN32_FILE_ATTRIBUTE_DATA fInfo;

        if (GetFileAttributesExA(folder.c_str(), GetFileExInfoStandard, &fInfo))
        {
            uint64_t size;
            std::cout << "Iterating over folder... (this may take a while)" << std::endl;
            GetFolderSize(folder, size);
            std::cout << "Done." << std::endl;
        }
        else
        {
            std::cout << "Folder not found" << std::endl;
        }
    }*/
    //std::cout << "Hello World!\n";
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        if (MessageBox(hwnd, L"Do you really want to quit?", CLASS_NAME, MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
        }
        return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

void GetFolderSize(std::string folder, unsigned long long& f_size)
{
    std::filesystem::path folderPath(folder);
    if (std::filesystem::exists(folderPath))
    {
        std::filesystem::directory_iterator end_itr;
        for (std::filesystem::directory_iterator dirIte(folder); dirIte != end_itr; ++dirIte)
        {
            std::filesystem::path filePath(dirIte->path());
            try
            {
                if (!is_directory(dirIte->status()))
                {
                    f_size = f_size + std::filesystem::file_size(filePath);
                }
                else
                {
                    GetFolderSize(filePath.string(), f_size);
                }
            }
            catch (std::exception& e)
            {
            }
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
