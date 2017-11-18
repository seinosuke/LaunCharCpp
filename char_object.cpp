#include "./laun_char.h"
#include "./config.h"
#include "./char_object.h"

using namespace nono;
using namespace std;


//* ###################################################################
//* デフォルトコンストラクタ
//* ###################################################################
CharObject::CharObject()
{
    alphabet_ = "";
    x_ = 0.0f;
    y_ = 0.0f;
    jump_power_ = 0.0f;
    prev_y_ = 0.0f;
    dx_ = 0.0f;
    timer_ = 0.0f;
    delay_ = 0.0f;
    active_ = false;
}

//* ###################################################################
//* デストラクタ
//* ###################################################################
CharObject::~CharObject()
{
}

//* ###################################################################
//* 初期化する
//* ###################################################################
void CharObject::initialize(LaunChar* laun_char)
{
    laun_char_ = laun_char;
    Graphics* graphics = laun_char_->get_graphics();

    // 文字の大きさやジャンプ力ぅを画面サイズから設定
    screen_width_ = laun_char_->get_screen_width();
    screen_height_ = laun_char_->get_screen_height();

    // 前面背面フォントを取得
    front_font_ = laun_char_->get_front_font();
    back_font_ = laun_char_->get_back_font();
}

//* ###################################################################
//* 射出する文字と画面上でのX座標をセットする
//* @param alphabet 射出するアルファベット
//* @param x        射出する位置
//* @param dx       射出する方向
//* ###################################################################
void CharObject::set_char(char alphabet, int x, int dx)
{
    alphabet_ = { alphabet };
    x_ = x;
    y_ = screen_height_;
    prev_y_ = y_;
    dx_ = dx;
    delay_ = 0.015f;
    jump_power_ = laun_char_->get_config()->get_jump_power() * 10;
    active_ = true;
}

//* ###################################################################
//* 飛び出した文字の位置を更新する
//* ###################################################################
void CharObject::update(float frame_time)
{
    if (active_)
    {
        timer_ += frame_time;
        if (timer_ > delay_)
        {
            // X方向
            x_ += dx_;

            // Y方向
            float tmp_y = y_;
            y_ += (y_ - prev_y_) - jump_power_;
            prev_y_ = tmp_y;

            if (jump_power_ > 0)
                { jump_power_ = CharObjectConst::GRAVITY; }
            timer_ = 0.0f;
        }
    }
}

//* ###################################################################
//* 飛び出した文字を描画する
//* ###################################################################
void CharObject::draw()
{
    if (active_)
    {
        back_font_->print(alphabet_, x_ + 4, y_ + 4);
        front_font_->print(alphabet_, x_, y_);
    }
}
