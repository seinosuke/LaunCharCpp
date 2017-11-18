#include "./laun_char.h"
#include "./config.h"

using namespace nono;
using namespace std;

//* ###################################################################
//* デフォルトコンストラクタ
//* ###################################################################
Config::Config()
{
    mode_ = SoundMode::NORMAL;
    mode_cnt_ = 0;
    jump_power_ = 0;
    visible_ = true;
    timer_ = 0.0f;
    delay_ = 0.0f;
}

//* ###################################################################
//* デストラクタ
//* ###################################################################
Config::~Config()
{
}


//* ###################################################################
//* 初期化する
//* ###################################################################
void Config::initialize(LaunChar* laun_char)
{
    Graphics* graphics = laun_char->get_graphics();

    laun_char_ = laun_char;
    input_ = laun_char_->get_input();
    mode_ = SoundMode::NORMAL;
    mode_cnt_ = 0;
    jump_power_ = 3;
    delay_ = 6.0f;

    // 前面フォントの初期化
    if (!front_font_.initialize(graphics, 40, true, false, "Arial"))
    {
        throw(EngineError(
            EngineErrorConst::FATAL_ERROR,
            "DirectX フォント初期化中にエラーが発生しました"));
    }
    front_font_.set_font_color(GraphicsConst::WHITE);

    // 背面フォントの初期化
    if (!back_font_.initialize(graphics, 40, true, false, "Arial"))
    {
        throw(EngineError(
            EngineErrorConst::FATAL_ERROR,
            "DirectX フォント初期化中にエラーが発生しました"));
    }
    back_font_.set_font_color(GraphicsConst::BLACK);
}

//* ###################################################################
//* 更新する
//* ###################################################################
void Config::update(float frame_time)
{
    // Alt + M : モード切替
    if (input_->is_key_down(InputConst::ALT_KEY) &&
        input_->was_key_pressed('M'))
    {
        switch_mode();
        visible_ = true;
        timer_ = 0.0f;
    }

    // Alt + J : ジャンプ力調整
    if (input_->is_key_down(InputConst::ALT_KEY) &&
        input_->was_key_pressed('J'))
    {
        jump_power_++;
        if (jump_power_ > ConfigConst::JUMP_MAX) { jump_power_ = 0; }
        visible_ = true;
        timer_ = 0.0f;
    }

    // Alt + Q : アプリケーション終了
    if (input_->is_key_down(InputConst::ALT_KEY) &&
        input_->was_key_pressed('Q'))
    {
        laun_char_->exit();
    }

    // delay_ の間だけ表示する
    if (visible_)
    {
        timer_ += frame_time;
        if (timer_ > delay_) {
            timer_ = 0.0f;
            visible_ = false;
        }
    }
}

//* ###################################################################
//* 現在の設定について表示する
//* ###################################################################
void Config::draw()
{
    if (visible_)
    {
        // 画面左上に表示する現在の設定状況
        text_ = "";

        // モード
        switch (mode_)
        {
        case SoundMode::NORMAL:
            text_ = "NORMAL";
            break;
        case SoundMode::DRUM:
            text_ = "DRUM";
            break;
        case SoundMode::PIANO:
            text_ = "PIANO";
            break;
        case SoundMode::SILENT:
            text_ = "SILENT";
            break;
        }

        // ジャンプ力ぅ
        string vol = "  ";
        for (int i = 0; i < jump_power_; ++i)
            { vol = vol + "|"; }

        // 改行で繋げる
        text_ = "Alt + M : " + text_ + " MODE\n";
        text_ = text_ + "Alt + J : JUMP POWER " +
            to_string(jump_power_) + vol + "\n";
        text_ = text_ + "Alt + Q : EXIT\n";

        // 表示
        back_font_.print(text_, 12, 12);
        front_font_.print(text_, 10, 10);
    }
}

//* ###################################################################
//* モードを切り替える
//* ###################################################################
void Config::switch_mode()
{
    mode_cnt_++;
    if (mode_cnt_ > ConfigConst::MODE_MAX) { mode_cnt_ = 0; }
    mode_ = static_cast<SoundMode>(mode_cnt_);
    laun_char_->initialize_params();
}

//* ###################################################################
//* 初期化時の逆順に on_lost_device() を呼び出す
//* ###################################################################
void Config::on_lost_device()
{
    back_font_.on_lost_device();
    front_font_.on_lost_device();
}

//* ###################################################################
//* 初期化順に on_reset_device() を呼び出す
//* ###################################################################
void Config::on_reset_device()
{
    front_font_.on_reset_device();
    back_font_.on_reset_device();
}
