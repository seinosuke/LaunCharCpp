#include "./laun_char.h"
#include "./config.h"

using namespace nono;
using namespace std;

//* ###################################################################
//* �f�t�H���g�R���X�g���N�^
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
//* �f�X�g���N�^
//* ###################################################################
Config::~Config()
{
}


//* ###################################################################
//* ����������
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

    // �O�ʃt�H���g�̏�����
    if (!front_font_.initialize(graphics, 40, true, false, "Arial"))
    {
        throw(EngineError(
            EngineErrorConst::FATAL_ERROR,
            "DirectX �t�H���g���������ɃG���[���������܂���"));
    }
    front_font_.set_font_color(GraphicsConst::WHITE);

    // �w�ʃt�H���g�̏�����
    if (!back_font_.initialize(graphics, 40, true, false, "Arial"))
    {
        throw(EngineError(
            EngineErrorConst::FATAL_ERROR,
            "DirectX �t�H���g���������ɃG���[���������܂���"));
    }
    back_font_.set_font_color(GraphicsConst::BLACK);
}

//* ###################################################################
//* �X�V����
//* ###################################################################
void Config::update(float frame_time)
{
    // Alt + M : ���[�h�ؑ�
    if (input_->is_key_down(InputConst::ALT_KEY) &&
        input_->was_key_pressed('M'))
    {
        switch_mode();
        visible_ = true;
        timer_ = 0.0f;
    }

    // Alt + J : �W�����v�͒���
    if (input_->is_key_down(InputConst::ALT_KEY) &&
        input_->was_key_pressed('J'))
    {
        jump_power_++;
        if (jump_power_ > ConfigConst::JUMP_MAX) { jump_power_ = 0; }
        visible_ = true;
        timer_ = 0.0f;
    }

    // Alt + Q : �A�v���P�[�V�����I��
    if (input_->is_key_down(InputConst::ALT_KEY) &&
        input_->was_key_pressed('Q'))
    {
        laun_char_->exit();
    }

    // delay_ �̊Ԃ����\������
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
//* ���݂̐ݒ�ɂ��ĕ\������
//* ###################################################################
void Config::draw()
{
    if (visible_)
    {
        // ��ʍ���ɕ\�����錻�݂̐ݒ��
        text_ = "";

        // ���[�h
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

        // �W�����v�͂�
        string vol = "  ";
        for (int i = 0; i < jump_power_; ++i)
            { vol = vol + "|"; }

        // ���s�Ōq����
        text_ = "Alt + M : " + text_ + " MODE\n";
        text_ = text_ + "Alt + J : JUMP POWER " +
            to_string(jump_power_) + vol + "\n";
        text_ = text_ + "Alt + Q : EXIT\n";

        // �\��
        back_font_.print(text_, 12, 12);
        front_font_.print(text_, 10, 10);
    }
}

//* ###################################################################
//* ���[�h��؂�ւ���
//* ###################################################################
void Config::switch_mode()
{
    mode_cnt_++;
    if (mode_cnt_ > ConfigConst::MODE_MAX) { mode_cnt_ = 0; }
    mode_ = static_cast<SoundMode>(mode_cnt_);
    laun_char_->initialize_params();
}

//* ###################################################################
//* ���������̋t���� on_lost_device() ���Ăяo��
//* ###################################################################
void Config::on_lost_device()
{
    back_font_.on_lost_device();
    front_font_.on_lost_device();
}

//* ###################################################################
//* ���������� on_reset_device() ���Ăяo��
//* ###################################################################
void Config::on_reset_device()
{
    front_font_.on_reset_device();
    back_font_.on_reset_device();
}
