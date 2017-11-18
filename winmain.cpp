#define _CRTDBG_MAP_ALLOC    // ���������[�N���o�p
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>          // ���������[�N���o�p
#include <crtdbg.h>          // ���������[�N���o�p
#include <chrono>
#include "laun_char.h"
#include "resource.h"

using namespace nono;
using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM); 

LaunChar *laun_char = NULL;

//* ###################################################################
//* �A�v���P�[�V�����̊J�n
//* ###################################################################
int WINAPI WinMain(
    HINSTANCE hinstance, HINSTANCE prev_hinstance,
    LPSTR lp_cmd_line, int cmd_show_num)
{

// Debug�Ńr���h����ۂɃ��������[�N���o
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    MSG msg;
    HWND hwnd = NULL;

    // �Q�[���𐧌䂷��I�u�W�F�N�g�𐶐�
    laun_char = new LaunChar();

    // �E�B���h�E�𐶐�
    if (!CreateMainWindow(hwnd, hinstance, cmd_show_num))
        { return 1; }

    try
    {
        // �Q�[���𐧌䂷��I�u�W�F�N�g�̏�����
        laun_char->initialize(hwnd);

        // ���C���̃��b�Z�[�W���[�v
        bool done = false;
        while (!done)
        {
            // PeekMessage() �� GetMessege() �ƈقȂ胁�b�Z�[�W��҂��Ȃ�
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
            {
                // �I�����b�Z�[�W
                if (msg.message == WM_QUIT) { done = true; }

                // ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�Ƀf�R�[�h
                TranslateMessage(&msg);

                // WinProc() �Ƀ��b�Z�[�W��n��
                DispatchMessage(&msg);
            }
            else { laun_char->run(hwnd); }
        }

        safe_delete(laun_char);
        return msg.wParam;
    }
    catch(const nono::EngineError &err)
    {
        laun_char->delete_all();
        DestroyWindow(hwnd);
        MessageBox(NULL, err.get_message(), "EngineError", MB_OK);
    }
    catch(...)
    {
        laun_char->delete_all();
        DestroyWindow(hwnd);
        MessageBox(NULL, "�s���ȃG���[���������܂���", "Error", MB_OK);
    }

    safe_delete(laun_char);
    return 0;
}

//* ###################################################################
//* �E�B���h�E�C�x���g�R�[���o�b�N�֐�
//* ###################################################################
LRESULT WINAPI WinProc( HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param )
{
    return (laun_char->message_handler(hwnd, msg, w_param, l_param));
}

//* ###################################################################
//* �E�B���h�E���쐬����
//* ###################################################################
bool CreateMainWindow(HWND &hwnd, HINSTANCE hinstance, int cmd_show_num) 
{ 
    WNDCLASSEX wcx; 
 
    // ���C���E�B���h�E�̃p�����[�^��ݒ�
    wcx.cbSize = sizeof(wcx);                 // �\���̂̃T�C�Y 
    wcx.style = CS_HREDRAW | CS_VREDRAW;      // �E�B���h�E�T�C�Y�ύX���ɍĕ`�� 
    wcx.lpfnWndProc = WinProc;                // �E�B���h�E�v���V�[�W��
    wcx.cbClsExtra = 0;                       // �g���N���X�������Ȃ�
    wcx.cbWndExtra = 0;                       // �g���E�B���h�E�������Ȃ�
    wcx.hInstance = hinstance;                // �C���X�^���X�ւ̃n���h��
    wcx.hIcon =
        (HICON)LoadImage(
            hinstance, "IDC_CHAR", IMAGE_ICON,
            0, 0, LR_SHARED);                 // �A�C�R��
    wcx.hCursor =
        LoadCursor(NULL,IDC_ARROW);           // ���O�o�^����Ă���J�[�\�� 
    wcx.hbrBackground =
        (HBRUSH)GetStockObject(BLACK_BRUSH);  // �w�i�u���V
    wcx.lpszMenuName =  NULL;                 // ���j���[���\�[�X�̖��O 
    wcx.lpszClassName =
        NonoConst::CLASS_NAME;                // �E�B���h�E�N���X�̖��O 
    wcx.hIconSm = NULL;                       // �������A�C�R��
 
    // �E�B���h�E�N���X��o�^
    if (RegisterClassEx(&wcx) == 0) { return false; }

    // NonoConst::FULLSCREEN �ɉ����ăE�B���h�E�X�^�C�����Z�b�g����
    DWORD style;
    if(NonoConst::FULLSCREEN)
        { style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; }
    else
        //{ style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX; }
        //{ style = WS_OVERLAPPEDWINDOW; }
        { style = WS_POPUP; }
    

    // �E�B���h�E�𐶐�
    //hwnd = CreateWindow(
    hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TRANSPARENT, // ���߂Ń}�E�X�C�x���g�ђ�
        NonoConst::CLASS_NAME,   // �E�B���h�E�N���X�̖��O
        NonoConst::GAME_TITLE,   // �^�C�g���o�[�ɕ\������閼�O
        style,                   // �E�B���h�E�X�^�C��
        CW_USEDEFAULT,           // ���������ʒu���W
        CW_USEDEFAULT,           // ���������ʒu���W
        NonoConst::GAME_WIDTH,   // �E�B���h�E��
        NonoConst::GAME_HEIGHT,  // �E�B���h�E����
        (HWND) NULL,             // �e�E�B���h�E�̃n���h��
        (HMENU) NULL,            // ���j���[�n���h��
        hinstance,               // �A�v���P�[�V�����C���X�^���X�̃n���h��
        (LPVOID) NULL
    );

    if (!hwnd) { return false; }

    // �t���X�N���[�����[�h�łȂ��ꍇ
    if(!NonoConst::FULLSCREEN)
    {
        // �N���C�A���g�̈�̃T�C�Y���擾����
        RECT client_rect;
        GetClientRect(hwnd, &client_rect);

        // �E�B���h�E�����T�C�Y
        // (hwnd, X, Y, ��, ����, true�ōĕ`��)
        MoveWindow(
            hwnd, 0, 0,
            NonoConst::GAME_WIDTH+(NonoConst::GAME_WIDTH-client_rect.right),
            NonoConst::GAME_HEIGHT+(NonoConst::GAME_HEIGHT-client_rect.bottom),
            TRUE);
    }

    // �E�B���h�E�𓧉�
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 128), 0, LWA_COLORKEY);

    // �E�B���h�E��\��
    ShowWindow(hwnd, cmd_show_num);

    return true;
}
