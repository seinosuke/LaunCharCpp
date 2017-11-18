#ifndef CHAR_OBJECT_H
#define CHAR_OBJECT_H
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <random>

//* ###################################################################
//* ./nono/
//* ###################################################################
#include "./nono/common.h"
#include "./nono/game.h"
#include "./nono/texture.h"
#include "./nono/image.h"
#include "./nono/text.h"

class LaunChar;

//* ###################################################################
//* 定数
//* ###################################################################
struct CharObjectConst
{
    static const int GRAVITY = -1;
};

//* ###################################################################
//* 射出する文字列を管理するクラス
//* ###################################################################
class CharObject
{
private:
    LaunChar* laun_char_;
    nono::Text* front_font_;  // 前面フォント
    nono::Text* back_font_;   // 背面フォント
    std::string alphabet_;   // 表示するアルファベット

    int screen_width_;     // スクリーンの幅
    int screen_height_;    // スクリーンの高さ

    float x_;           // X座標
    float y_;           // Y座標
    float dx_;          // X方向の増分
    float prev_y_;      // 前回のY座標
    float jump_power_;  // ジャンプ力ぅ
    bool active_;       // true で位置更新など

    float timer_;
    float delay_;

public:
    CharObject();
    virtual ~CharObject();
    void initialize(LaunChar* laun_char);

    void update(float frame_time);
    void draw();

    //* ###################################################################
    //* ゲッター
    //* ###################################################################
    float get_x() { return x_; }
    float get_y() { return y_; }
    bool get_active() { return active_; }

    //* ###################################################################
    //* セッター
    //* ###################################################################
    void set_char(char alphabet, int x, int dx);
    void set_active(bool a) { active_ = a; }
};

#endif