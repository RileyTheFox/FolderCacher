#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 350

#include <vector>
#include <iostream>
#include <string>
#include <Windows.h>
#include <filesystem>

#include "MainWindow.h"

void GetFolderSize(std::string folder, unsigned long long& f_size);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
//#if !_DEBUG
//    FreeConsole();
//#endif

    MainWindow win;

    int x = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2;

    if (!win.Create(L"FolderCacher", WS_OVERLAPPEDWINDOW, 0UL, x, y, WINDOW_WIDTH, WINDOW_HEIGHT))
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
