#define _CRTDBG_MAP_ALLOC    // メモリリーク検出用
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>          // メモリリーク検出用
#include <crtdbg.h>          // メモリリーク検出用
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
//* アプリケーションの開始
//* ###################################################################
int WINAPI WinMain(
    HINSTANCE hinstance, HINSTANCE prev_hinstance,
    LPSTR lp_cmd_line, int cmd_show_num)
{

// Debugでビルドする際にメモリリーク検出
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    MSG msg;
    HWND hwnd = NULL;

    // ゲームを制御するオブジェクトを生成
    laun_char = new LaunChar();

    // ウィンドウを生成
    if (!CreateMainWindow(hwnd, hinstance, cmd_show_num))
        { return 1; }

    try
    {
        // ゲームを制御するオブジェクトの初期化
        laun_char->initialize(hwnd);

        // メインのメッセージループ
        bool done = false;
        while (!done)
        {
            // PeekMessage() は GetMessege() と異なりメッセージを待たない
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
            {
                // 終了メッセージ
                if (msg.message == WM_QUIT) { done = true; }

                // 仮想キーメッセージを文字メッセージにデコード
                TranslateMessage(&msg);

                // WinProc() にメッセージを渡す
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
        MessageBox(NULL, "不明なエラーが発生しました", "Error", MB_OK);
    }

    safe_delete(laun_char);
    return 0;
}

//* ###################################################################
//* ウィンドウイベントコールバック関数
//* ###################################################################
LRESULT WINAPI WinProc( HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param )
{
    return (laun_char->message_handler(hwnd, msg, w_param, l_param));
}

//* ###################################################################
//* ウィンドウを作成する
//* ###################################################################
bool CreateMainWindow(HWND &hwnd, HINSTANCE hinstance, int cmd_show_num) 
{ 
    WNDCLASSEX wcx; 
 
    // メインウィンドウのパラメータを設定
    wcx.cbSize = sizeof(wcx);                 // 構造体のサイズ 
    wcx.style = CS_HREDRAW | CS_VREDRAW;      // ウィンドウサイズ変更時に再描画 
    wcx.lpfnWndProc = WinProc;                // ウィンドウプロシージャ
    wcx.cbClsExtra = 0;                       // 拡張クラスメモリなし
    wcx.cbWndExtra = 0;                       // 拡張ウィンドウメモリなし
    wcx.hInstance = hinstance;                // インスタンスへのハンドル
    wcx.hIcon =
        (HICON)LoadImage(
            hinstance, "IDC_CHAR", IMAGE_ICON,
            0, 0, LR_SHARED);                 // アイコン
    wcx.hCursor =
        LoadCursor(NULL,IDC_ARROW);           // 事前登録されているカーソル 
    wcx.hbrBackground =
        (HBRUSH)GetStockObject(BLACK_BRUSH);  // 背景ブラシ
    wcx.lpszMenuName =  NULL;                 // メニューリソースの名前 
    wcx.lpszClassName =
        NonoConst::CLASS_NAME;                // ウィンドウクラスの名前 
    wcx.hIconSm = NULL;                       // 小さいアイコン
 
    // ウィンドウクラスを登録
    if (RegisterClassEx(&wcx) == 0) { return false; }

    // NonoConst::FULLSCREEN に応じてウィンドウスタイルをセットする
    DWORD style;
    if(NonoConst::FULLSCREEN)
        { style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; }
    else
        //{ style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX; }
        //{ style = WS_OVERLAPPEDWINDOW; }
        { style = WS_POPUP; }
    

    // ウィンドウを生成
    //hwnd = CreateWindow(
    hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TRANSPARENT, // 透過でマウスイベント貫通
        NonoConst::CLASS_NAME,   // ウィンドウクラスの名前
        NonoConst::GAME_TITLE,   // タイトルバーに表示される名前
        style,                   // ウィンドウスタイル
        CW_USEDEFAULT,           // 水平方向位置座標
        CW_USEDEFAULT,           // 垂直方向位置座標
        NonoConst::GAME_WIDTH,   // ウィンドウ幅
        NonoConst::GAME_HEIGHT,  // ウィンドウ高さ
        (HWND) NULL,             // 親ウィンドウのハンドル
        (HMENU) NULL,            // メニューハンドル
        hinstance,               // アプリケーションインスタンスのハンドル
        (LPVOID) NULL
    );

    if (!hwnd) { return false; }

    // フルスクリーンモードでない場合
    if(!NonoConst::FULLSCREEN)
    {
        // クライアント領域のサイズを取得する
        RECT client_rect;
        GetClientRect(hwnd, &client_rect);

        // ウィンドウをリサイズ
        // (hwnd, X, Y, 幅, 高さ, trueで再描画)
        MoveWindow(
            hwnd, 0, 0,
            NonoConst::GAME_WIDTH+(NonoConst::GAME_WIDTH-client_rect.right),
            NonoConst::GAME_HEIGHT+(NonoConst::GAME_HEIGHT-client_rect.bottom),
            TRUE);
    }

    // ウィンドウを透過
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 128), 0, LWA_COLORKEY);

    // ウィンドウを表示
    ShowWindow(hwnd, cmd_show_num);

    return true;
}
