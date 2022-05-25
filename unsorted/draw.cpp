#include <Windows.h>

long width = 0, height = 0; // ширина и высота картинки
HBITMAP hPicture = NULL;
DWORD *data = NULL; // указатель на область памяти, где будет лежать картинка
HDC hScreenDC = NULL, hMemoryDC = NULL; // контексты устройств - см. ниже

bool drag = false;
POINT anchor;

// инициализация контекстов устройств, создание "буфера" в памяти для рисования на нем
bool InitializeGraphics(HWND hw)
{
// проверка окна
if(!IsWindow(hw))
    return false;

// если процедура вызвана для РЕ-инициализации, освободим существующие объекты
if(hPicture)
    DeleteObject(hPicture);
if(hMemoryDC)
    DeleteDC(hMemoryDC);
if(hScreenDC)
    ReleaseDC(hw, hScreenDC);

// найдем размеры "окна" для рисования
RECT rect;
GetClientRect(hw, &rect);

width = rect.right - rect.left;
height = rect.bottom - rect.top;

// захват контекста устройства окна (клиентской области)
hScreenDC = GetDC(hw);
if(hScreenDC == NULL)
    return false;

// создание совместимого контекста устройства в памяти - будущий буфер
hMemoryDC = CreateCompatibleDC(hScreenDC);
if(hMemoryDC == NULL)
{
    ReleaseDC(hw, hScreenDC);
    return false;
}

// создание BITMAP для рисования
LPBITMAPINFO lpbi;
lpbi = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER) + (3 * sizeof(RGBQUAD))];
BITMAPINFO &MSbi = *lpbi;
ZeroMemory(&MSbi, sizeof(BITMAPINFO));

// параметры хранения картинки в памяти
MSbi.bmiHeader.biBitCount = 32; // 32 бит на точку - одна точка - одно 32-битное слово
MSbi.bmiHeader.biClrImportant = 0;
MSbi.bmiHeader.biClrUsed = 0;
MSbi.bmiHeader.biCompression = BI_RGB; // без компрессии
MSbi.bmiHeader.biHeight = -height;  // знак "-" нужен чтобы битмап не был "перевернут" -
                                    // при "+" первыми в буфере идут последние строчки битмапа
MSbi.bmiHeader.biPlanes = 1;// количество цветовых плоскостей, для RGB всегда 1
MSbi.bmiHeader.biSize = sizeof(BITMAPINFO);
MSbi.bmiHeader.biSizeImage = 0;
MSbi.bmiHeader.biWidth = width;
MSbi.bmiHeader.biXPelsPerMeter = 0;
MSbi.bmiHeader.biYPelsPerMeter = 0;

// создаем устройство-независимую битмап-секцию (Device-Independent Bitmap, DIB)
hPicture = CreateDIBSection(hMemoryDC, &MSbi, DIB_RGB_COLORS, (void**)&(data), NULL, NULL);
if(hPicture == NULL)
{
    DWORD k = GetLastError();
    ReleaseDC(hw, hScreenDC);
    DeleteDC(hMemoryDC);
    return false;
}

// выбираем созданную секцию на memoryDC - т.е. для буфера
SelectObject(hMemoryDC, hPicture);

delete lpbi;
lpbi = NULL;

return true;
}

LRESULT CALLBACK WndProc(HWND hw, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
// создаем белый карандаш для рисования линий
static HPEN whitepen = CreatePen(PS_SOLID, 2, 0xFFFFFF);

switch(uMsg)
{
case WM_CLOSE:
    if(hPicture)
        DeleteObject(hPicture);
    if(hMemoryDC)
        DeleteDC(hMemoryDC);
    if(hScreenDC)
        ReleaseDC(hw, hScreenDC);
    DestroyWindow(hw);
    break;
case WM_DESTROY:
    PostQuitMessage(0);
    break;
case WM_CREATE: // при создании
case WM_SIZE:   // сворачивании/разворачивании
case WM_MOVE:   // перемещении/изменении размеров окна
    if(InitializeGraphics(hw)) // (пере)инициализируем графику
    {
        // и выбираем белый карандаш на оба контекста устройства
        SelectObject(hScreenDC, whitepen);
        SelectObject(hMemoryDC, whitepen);
    }
    if(uMsg != WM_CREATE)   // если окно уже было создано
        InvalidateRect(hw, NULL, false); // перерисуем
    break;
case WM_MOUSEMOVE: // при движении мыши
    if(data)
    {
        if(!drag) // если левая кнопка мыши не нажата
        {
            int x = LOWORD(lParam); // координаты курсора
            int y = HIWORD(lParam);
            data[width * y + x] = (rand() << 9) | rand();   // поместим точку случайного цвета (в буфере,
                                                            // прямое рисование "в памяти")
            InvalidateRect(hw, NULL, false); // перерисуем
        }
        else // если нажата
        {
            BitBlt(hScreenDC, 0, 0, width, height, hMemoryDC, 0, 0, SRCCOPY); // перерисуем экран
            MoveToEx(hScreenDC, anchor.x, anchor.y, NULL);  // нарисуем на экране (не в буфере!)
            LineTo(hScreenDC, LOWORD(lParam), HIWORD(lParam)); // белую линию
        }
    }
    break;
case WM_LBUTTONDOWN: // нажали левую кнопку
    anchor.x = LOWORD(lParam); // запомним координаты курсора
    anchor.y = HIWORD(lParam);
    drag = true; // установим флаг нажатой левой кнопки
    break;
case WM_LBUTTONUP: // отпустили левую кнопку
    drag = false; // сбросили флаг нажатия
    MoveToEx(hMemoryDC, anchor.x, anchor.y, NULL); // нарисовали белую линию (в буфере! - т.е. сохранили)
    LineTo(hMemoryDC, LOWORD(lParam), HIWORD(lParam));
    InvalidateRect(hw, NULL, false); // перерисовали экран
    break;
case WM_PAINT: // необходимо перерисовать окно - перерисовываем
    BitBlt(hScreenDC, 0, 0, width, height, hMemoryDC, 0, 0, SRCCOPY); // копируем из буфера на экран
    ValidateRect(hw, NULL); // устанавливаем "нет нужды в перерисовке"
    return false;
default:
    return DefWindowProc(hw, uMsg, wParam, lParam);
}

return false;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lpCmd, int nShowCmd)
{
// регистрируем класс окна
WNDCLASSEX wc;
ZeroMemory(&wc, sizeof(WNDCLASSEX));
wc.cbSize = sizeof(WNDCLASSEX);
wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
wc.hCursor = LoadCursor(NULL, IDC_ARROW);
wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
wc.hInstance = hInst;
wc.lpfnWndProc = WndProc;
wc.lpszClassName = TEXT("SPW");
wc.lpszMenuName = NULL;
wc.style = CS_VREDRAW | CS_HREDRAW;
RegisterClassEx(&wc);

// создаем окно
HWND wnd = CreateWindow(TEXT("SPW"), TEXT("Simple Paint"), WS_VISIBLE | WS_OVERLAPPEDWINDOW,
    0, 0, 800, 600, NULL, NULL, hInst, NULL);
// ShowWindow(wnd, SW_SHOW);

// запускаем очередь сообщений
MSG msg;

while(GetMessage(&msg, wnd, 0, 0) > 0)
{
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}

return msg.lParam;
}
