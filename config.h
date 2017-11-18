#ifndef CONFIG_H
#define CONFIG_H
#define WIN32_LEAN_AND_MEAN

//* ###################################################################
//* ./nono/
//* ###################################################################
#include "./nono/common.h"
#include "./nono/game.h"
#include "./nono/texture.h"
#include "./nono/image.h"
#include "./nono/text.h"
#include "./nono/input.h"

class LaunChar;

//* ###################################################################
//* サウンドモード
//* ###################################################################
enum struct SoundMode
{
    NORMAL, // 単発SEモード
    DRUM,   // ドラムモード
    PIANO,  // ピアノモード
    SILENT, // サイレント
};

//* ###################################################################
//* 定数
//* ###################################################################
struct ConfigConst
{
    static const int MODE_MAX = 3; // モード数
    static const int JUMP_MAX = 5; // ジャンプ力最大値
};

//* ###################################################################
//* モードの設定などに関するクラス
//* ###################################################################
class Config
{
private:
    LaunChar* laun_char_;
    nono::Input* input_;
    nono::Text front_font_;  // 前面フォント
    nono::Text back_font_;   // 背面フォント

    SoundMode mode_;   // 現在のモード
    int mode_cnt_;     // 現在のモードの番号
    std::string text_; // 表示するテキスト
    bool visible_;     // trueで表示
    int jump_power_;   // 射出する力

    float timer_;
    float delay_;

public:
    Config();
    virtual ~Config();
    void initialize(LaunChar* laun_char);
    void on_lost_device();
    void on_reset_device();

    void update(float frame_time);
    void draw();
    SoundMode get_mode() { return mode_; }
    void switch_mode();
    int get_jump_power() { return jump_power_; }

};

#endif
