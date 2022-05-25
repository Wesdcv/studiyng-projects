#include <Windows.h>

long width = 0, height = 0; // ������ � ������ ��������
HBITMAP hPicture = NULL;
DWORD *data = NULL; // ��������� �� ������� ������, ��� ����� ������ ��������
HDC hScreenDC = NULL, hMemoryDC = NULL; // ��������� ��������� - ��. ����

bool drag = false;
POINT anchor;

// ������������� ���������� ���������, �������� "������" � ������ ��� ��������� �� ���
bool InitializeGraphics(HWND hw)
{
// �������� ����
if(!IsWindow(hw))
    return false;

// ���� ��������� ������� ��� ��-�������������, ��������� ������������ �������
if(hPicture)
    DeleteObject(hPicture);
if(hMemoryDC)
    DeleteDC(hMemoryDC);
if(hScreenDC)
    ReleaseDC(hw, hScreenDC);

// ������ ������� "����" ��� ���������
RECT rect;
GetClientRect(hw, &rect);

width = rect.right - rect.left;
height = rect.bottom - rect.top;

// ������ ��������� ���������� ���� (���������� �������)
hScreenDC = GetDC(hw);
if(hScreenDC == NULL)
    return false;

// �������� ������������ ��������� ���������� � ������ - ������� �����
hMemoryDC = CreateCompatibleDC(hScreenDC);
if(hMemoryDC == NULL)
{
    ReleaseDC(hw, hScreenDC);
    return false;
}

// �������� BITMAP ��� ���������
LPBITMAPINFO lpbi;
lpbi = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER) + (3 * sizeof(RGBQUAD))];
BITMAPINFO &MSbi = *lpbi;
ZeroMemory(&MSbi, sizeof(BITMAPINFO));

// ��������� �������� �������� � ������
MSbi.bmiHeader.biBitCount = 32; // 32 ��� �� ����� - ���� ����� - ���� 32-������ �����
MSbi.bmiHeader.biClrImportant = 0;
MSbi.bmiHeader.biClrUsed = 0;
MSbi.bmiHeader.biCompression = BI_RGB; // ��� ����������
MSbi.bmiHeader.biHeight = -height;  // ���� "-" ����� ����� ������ �� ��� "����������" -
                                    // ��� "+" ������� � ������ ���� ��������� ������� �������
MSbi.bmiHeader.biPlanes = 1;// ���������� �������� ����������, ��� RGB ������ 1
MSbi.bmiHeader.biSize = sizeof(BITMAPINFO);
MSbi.bmiHeader.biSizeImage = 0;
MSbi.bmiHeader.biWidth = width;
MSbi.bmiHeader.biXPelsPerMeter = 0;
MSbi.bmiHeader.biYPelsPerMeter = 0;

// ������� ����������-����������� ������-������ (Device-Independent Bitmap, DIB)
hPicture = CreateDIBSection(hMemoryDC, &MSbi, DIB_RGB_COLORS, (void**)&(data), NULL, NULL);
if(hPicture == NULL)
{
    DWORD k = GetLastError();
    ReleaseDC(hw, hScreenDC);
    DeleteDC(hMemoryDC);
    return false;
}

// �������� ��������� ������ �� memoryDC - �.�. ��� ������
SelectObject(hMemoryDC, hPicture);

delete lpbi;
lpbi = NULL;

return true;
}

LRESULT CALLBACK WndProc(HWND hw, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
// ������� ����� �������� ��� ��������� �����
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
case WM_CREATE: // ��� ��������
case WM_SIZE:   // ������������/��������������
case WM_MOVE:   // �����������/��������� �������� ����
    if(InitializeGraphics(hw)) // (����)�������������� �������
    {
        // � �������� ����� �������� �� ��� ��������� ����������
        SelectObject(hScreenDC, whitepen);
        SelectObject(hMemoryDC, whitepen);
    }
    if(uMsg != WM_CREATE)   // ���� ���� ��� ���� �������
        InvalidateRect(hw, NULL, false); // ����������
    break;
case WM_MOUSEMOVE: // ��� �������� ����
    if(data)
    {
        if(!drag) // ���� ����� ������ ���� �� ������
        {
            int x = LOWORD(lParam); // ���������� �������
            int y = HIWORD(lParam);
            data[width * y + x] = (rand() << 9) | rand();   // �������� ����� ���������� ����� (� ������,
                                                            // ������ ��������� "� ������")
            InvalidateRect(hw, NULL, false); // ����������
        }
        else // ���� ������
        {
            BitBlt(hScreenDC, 0, 0, width, height, hMemoryDC, 0, 0, SRCCOPY); // ���������� �����
            MoveToEx(hScreenDC, anchor.x, anchor.y, NULL);  // �������� �� ������ (�� � ������!)
            LineTo(hScreenDC, LOWORD(lParam), HIWORD(lParam)); // ����� �����
        }
    }
    break;
case WM_LBUTTONDOWN: // ������ ����� ������
    anchor.x = LOWORD(lParam); // �������� ���������� �������
    anchor.y = HIWORD(lParam);
    drag = true; // ��������� ���� ������� ����� ������
    break;
case WM_LBUTTONUP: // ��������� ����� ������
    drag = false; // �������� ���� �������
    MoveToEx(hMemoryDC, anchor.x, anchor.y, NULL); // ���������� ����� ����� (� ������! - �.�. ���������)
    LineTo(hMemoryDC, LOWORD(lParam), HIWORD(lParam));
    InvalidateRect(hw, NULL, false); // ������������ �����
    break;
case WM_PAINT: // ���������� ������������ ���� - ��������������
    BitBlt(hScreenDC, 0, 0, width, height, hMemoryDC, 0, 0, SRCCOPY); // �������� �� ������ �� �����
    ValidateRect(hw, NULL); // ������������� "��� ����� � �����������"
    return false;
default:
    return DefWindowProc(hw, uMsg, wParam, lParam);
}

return false;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lpCmd, int nShowCmd)
{
// ������������ ����� ����
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

// ������� ����
HWND wnd = CreateWindow(TEXT("SPW"), TEXT("Simple Paint"), WS_VISIBLE | WS_OVERLAPPEDWINDOW,
    0, 0, 800, 600, NULL, NULL, hInst, NULL);
// ShowWindow(wnd, SW_SHOW);

// ��������� ������� ���������
MSG msg;

while(GetMessage(&msg, wnd, 0, 0) > 0)
{
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}

return msg.lParam;
}
