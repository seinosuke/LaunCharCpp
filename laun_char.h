#ifndef LAUN_CHAR_H
#define LAUN_CHAR_H
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <deque>

//* ###################################################################
//* ./nono/
//* ###################################################################
#include "./nono/common.h"
#include "./nono/game.h"
#include "./nono/texture.h"
#include "./nono/image.h"
#include "./nono/text.h"

//* ###################################################################
//* ./
//* ###################################################################
#include "./common.h"
#include "./config.h"
#include "./char_object.h"


//* ###################################################################
//* 定数
//* ###################################################################
struct LaunCharConst
{

    static const int ALPHABET = 27;
    static const int MAX = 50;   // 表示可能な文字数

    // サウンドキュー
    static const char ALPHABETS[];         // アルファベットを格納
    static const std::string CUES_DRUM[];  // ドラムのサウンドキュー
    static const std::string CUES_PIANO[]; // ピアノのサウンドキュー
    static const std::string SE_WAV;       // 単発SEのサウンドキュー

};

//* ###################################################################
//* ゲームを制御するメインのクラス
//* ###################################################################
class LaunChar : public nono::Game
{
private:
    nono::Text front_font_;  // 前面フォント
    nono::Text back_font_;   // 背面フォント

    int screen_width_;  // 画面の幅
    int screen_height_; // 画面の高さ

    bool alphabets_pressed_[LaunCharConst::ALPHABET]; // 前回押されたか
    int alphabets_pos_[LaunCharConst::ALPHABET];      // 射出位置
    int alphabets_wav_[LaunCharConst::ALPHABET];      // 割り振られた音
    CharObject alphabets_vec_[LaunCharConst::MAX];    // 画面上全ての文字

    Config config_;        // モード等を設定する
    std::mt19937 mt_rand_; // ランダム射出に用いる

public:
    LaunChar();
    virtual ~LaunChar();
    void initialize(HWND hwnd);
    void initialize_params();
    void release_all();
    void reset_all();
    void exit();

    //* ###################################################################
    //* ゲーム関連
    //* ###################################################################
    void update();
    void render();
    void launch(int id, char key);

    //* ###################################################################
    //* セッター
    //* ###################################################################
    void set_screen_width(int w) { screen_width_ = w; }
    void set_screen_height(int h) { screen_height_ = h; }

    //* ###################################################################
    //* ゲッター
    //* ###################################################################
    int get_screen_width() { return screen_width_; }
    int get_screen_height() { return screen_height_; }
    nono::Text* get_front_font() { return &front_font_; }
    nono::Text* get_back_font() { return &back_font_; }
    Config* get_config() { return &config_; }
};

#endif
