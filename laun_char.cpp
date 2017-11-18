#include "laun_char.h"

using namespace nono;
using namespace nono::gui;
using namespace std;

//* ###################################################################
//* �萔�̏�����
//* �e�萔�̈Ӗ��ɂ��Ă͐錾����Ă���w�b�_�t�@�C�����Q��
//* ###################################################################
// nono/common.h �Ő錾
const char NonoConst::CLASS_NAME[] = "LaunChar";
const char NonoConst::GAME_TITLE[] = "LaunChar";
const bool NonoConst::FULLSCREEN = false;
const UINT NonoConst::GAME_WIDTH = 640;
const UINT NonoConst::GAME_HEIGHT = 480;
const bool NonoConst::VSYNC = false;
const float NonoConst::FRAME_RATE = 240.0f;
const float NonoConst::MIN_FRAME_RATE = 10.0f;
const float NonoConst::MIN_FRAME_TIME = 1.0f / NonoConst::FRAME_RATE;
const float NonoConst::MAX_FRAME_TIME = 1.0f / NonoConst::MIN_FRAME_RATE;

// ./laun_char.h �Ő錾
const string LaunCharConst::SE_WAV = "se";

const char LaunCharConst::ALPHABETS[] = {
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
     'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
      'Z', 'X', 'C', 'V', 'B', 'N', 'M'
};
const string LaunCharConst::CUES_DRUM[] = {
    "drum_01", "drum_02", "drum_03", "drum_04", "drum_05",
    "drum_06", "drum_07", "drum_08", "drum_09", "drum_10",
    "drum_11", "drum_12", "drum_13", "drum_14"
};
const string LaunCharConst::CUES_PIANO[] = {
    "piano_01", "piano_02", "piano_03", "piano_04", "piano_05",
     "piano_06", "piano_07"
};

// nono/audio.h�Ő錾
const char AudioConst::WAVE_BANK[]  = "./resources/audio/Win/Wave Bank.xwb";
const char AudioConst::SOUND_BANK[] = "./resources/audio/Win/Sound Bank.xsb";

// nono/graphics.h �Ő錾
const COLOR_ARGB GraphicsConst::BACK_COLOR = GraphicsConst::NAVY;
const COLOR_ARGB GraphicsConst::TRANSCOLOR = GraphicsConst::MAGENTA;

// nono/input.h �Ő錾
// �T���X�e�B�b�N�̃f�b�h�]�[�����ő�ړ��͈͂�20���ɃZ�b�g
const short InputConst::GAMEPAD_THUMBSTICK_DEADZONE = (short)(0.20f * 0X7FFF);
// �g���K�[�̃f�b�h�]�[��20�ɃZ�b�g(0~255)
const short InputConst::GAMEPAD_TRIGGER_DEADZONE = 20;
const UCHAR InputConst::CONSOLE_KEY = '`';
const UCHAR InputConst::ESC_KEY = VK_ESCAPE;
const UCHAR InputConst::ALT_KEY = VK_MENU;
const UCHAR InputConst::ENTER_KEY = VK_RETURN;

// nono/gui/console.h �Ő錾
const UINT ConsoleConst::WIDTH = 500;
const UINT ConsoleConst::HEIGHT = 400;
const UINT ConsoleConst::X = 5;
const UINT ConsoleConst::Y = 5;
const UINT ConsoleConst::MARGIN = 4;
const char ConsoleConst::FONT[] = "Courier New";
const int ConsoleConst::FONT_HEIGHT = 14;
const COLOR_ARGB ConsoleConst::FONT_COLOR = GraphicsConst::WHITE;
const COLOR_ARGB ConsoleConst::BACK_COLOR = SETCOLOR_ARGB(192, 128, 128, 128);
const int ConsoleConst::MAX_LINES = 256;

// nono/gui/message_dialog.h �Ő錾
const UINT MessageDialogConst::WIDTH = 300;
const UINT MessageDialogConst::HEIGHT = 100;
const UINT MessageDialogConst::BORDER = 5;
const UINT MessageDialogConst::MARGIN = 5;
const char MessageDialogConst::FONT[] = "Arial";
const int  MessageDialogConst::FONT_HEIGHT = 18;
const COLOR_ARGB MessageDialogConst::FONT_COLOR = GraphicsConst::WHITE;
const COLOR_ARGB MessageDialogConst::BORDER_COLOR = D3DCOLOR_ARGB(192, 192, 192, 192);
const COLOR_ARGB MessageDialogConst::BACK_COLOR = SETCOLOR_ARGB(255, 100, 100, 192);
const UINT MessageDialogConst::X = (NonoConst::GAME_WIDTH / 2) - (MessageDialogConst::WIDTH / 2);
const UINT MessageDialogConst::Y = (NonoConst::GAME_HEIGHT / 2) - (MessageDialogConst::HEIGHT / 2);
const UINT MessageDialogConst::BUTTON_WIDTH = (UINT)(MessageDialogConst::FONT_HEIGHT * 4.5);
const UINT MessageDialogConst::BUTTON_HEIGHT = MessageDialogConst::FONT_HEIGHT + 4;
const char* MessageDialogConst::BUTTON1_TEXT[MessageDialogConst::MAX_TYPE] = { "OK", "YES" };
const char* MessageDialogConst::BUTTON2_TEXT[MessageDialogConst::MAX_TYPE] = { "CANCEL", "NO" };
const byte MessageDialogConst::DIALOG_CLOSE_KEY = VK_RETURN;
const COLOR_ARGB MessageDialogConst::BUTTON_COLOR = GraphicsConst::GRAY;
const COLOR_ARGB MessageDialogConst::BUTTON_FONT_COLOR = GraphicsConst::WHITE;

// nono/gui/inpu_dialog.h �Ő錾
const COLOR_ARGB InputDialogConst::TEXT_BACK_COLOR = GraphicsConst::WHITE;
const COLOR_ARGB InputDialogConst::TEXT_COLOR = GraphicsConst::BLACK;



//* ###################################################################
//* �f�t�H���g�R���X�g���N�^
//* ###################################################################
LaunChar::LaunChar()
{
    screen_height_ = 0;
    screen_width_ = 0;

    std::random_device seed;
    mt_rand_ = std::mt19937(seed());

    alphabets_pressed_[LaunCharConst::ALPHABET] = { false };
    alphabets_pos_[LaunCharConst::ALPHABET] = { 0 };
    alphabets_wav_[LaunCharConst::ALPHABET] = { 0 };
}

//* ###################################################################
//* �f�X�g���N�^
//* ###################################################################
LaunChar::~LaunChar()
{
    release_all();
}

//* ###################################################################
//* LaunChar �̏�����
//* �e�Q�[���A�C�e���ɂ��� initialize() ���Ăяo��
//* ReversiError�AEngineError �𓊂���
//* ###################################################################
void LaunChar::initialize(HWND hwnd)
{
    nono::Game::initialize(hwnd);

    // �ݒ�I�u�W�F�N�g�̏�����
    config_.initialize(this);

    // �X�N���[���T�C�Y���擾
    RECT rect;
    HWND dhwnd = GetDesktopWindow();
    GetWindowRect(dhwnd, &rect);
    screen_height_ = (int)rect.bottom;
    screen_width_ = (int)rect.right;
    int font_size = screen_width_ / 20;

    // �O�ʃt�H���g�̏�����
    if (!front_font_.initialize(graphics_, font_size, true, false, "Arial"))
    {
        throw(EngineError(
            EngineErrorConst::FATAL_ERROR,
            "DirectX �t�H���g���������ɃG���[���������܂���"));
    }
    front_font_.set_font_color(GraphicsConst::WHITE);

    // �w�ʃt�H���g�̏�����
    if (!back_font_.initialize(graphics_, font_size, true, false, "Arial"))
    {
        throw(EngineError(
            EngineErrorConst::FATAL_ERROR,
            "DirectX �t�H���g���������ɃG���[���������܂���"));
    }
    back_font_.set_font_color(GraphicsConst::BLACK);

    // �ˏo�����I�u�W�F�N�g�̏�����
    for (int i = 0; i < LaunCharConst::MAX; ++i)
    {
        alphabets_vec_[i] = CharObject();
        alphabets_vec_[i].initialize(this);
    }

    // �X�N���[���Ɠ����T�C�Y�ɂ���
    MoveWindow(
        hwnd, 0, 0,
        screen_width_ + (screen_width_ - rect.right),
        screen_height_ + (screen_height_ - rect.bottom),
        TRUE);

    // �E�B���h�E����ɍőO�ʂɂ���
    // SWP_NOMOVE �� SWP_NOSIZE�ɂ����
    // �E�B���h�E�̈ʒu��T�C�Y�Ɋւ�������𖳎�������
    SetWindowPos(
        hwnd, HWND_TOPMOST,
        0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE
    );

    // �X�N���[���T�C�Y�ɉ����������̎ˏo�ʒu���Z�b�g����
    alphabets_pos_[LaunCharConst::ALPHABET] = { 0 };
    int dx = screen_width_ / 10;
    alphabets_pos_[0] = dx / 4;
    for (int i = 1; i < 10; ++i)
        { alphabets_pos_[i] = alphabets_pos_[0] + dx*i; }
    alphabets_pos_[10] = dx / 3;
    for (int i = 11; i < 19; ++i)
        { alphabets_pos_[i] = alphabets_pos_[10] + dx*(i-10); }
    alphabets_pos_[19] = dx / 2;
    for (int i = 20; i < 27; ++i)
        { alphabets_pos_[i] = alphabets_pos_[19] + dx*(i-19); }

    // �����o�ϐ��̏�����
    initialize_params();

    return;
}

//* ###################################################################
//* �����o�ϐ��̏�����������
//* ��ɃA���t�@�x�b�g�z�񓙂�����������
//* �T�E���h���[�h�ؑ֎��ɖ���Ă΂��
//* ###################################################################
void LaunChar::initialize_params()
{
    alphabets_wav_[LaunCharConst::ALPHABET] = { 0 };
    alphabets_pressed_[LaunCharConst::ALPHABET] = { false };
    int cues_num = 0;

    // ���[�h�ɉ����ēK�؂ȃT�E���h�L���[���Z�b�g����
    switch (config_.get_mode())
    {
    case SoundMode::SILENT:
    case SoundMode::NORMAL:
        for (int i = 0; i < LaunCharConst::ALPHABET; ++i)
        {
            alphabets_wav_[i] = 0;
        }
        break;
    case SoundMode::DRUM:
        cues_num =
            sizeof(LaunCharConst::CUES_DRUM) /
            sizeof(LaunCharConst::CUES_DRUM[0]);
        for (int i = 0; i < LaunCharConst::ALPHABET; ++i)
        {
            alphabets_wav_[i] = mt_rand_() % cues_num;
        }
        break;
    case SoundMode::PIANO:
        cues_num =
            sizeof(LaunCharConst::CUES_PIANO) /
            sizeof(LaunCharConst::CUES_PIANO[0]);
        for (int i = 0; i < LaunCharConst::ALPHABET; ++i)
        {
            alphabets_wav_[i] = mt_rand_() % cues_num;
        }
        break;
    }
}

//* ###################################################################
//* �S�ẴQ�[���A�C�e�����X�V����
//* ###################################################################
void LaunChar::update()
{
    // �ݒ�I�u�W�F�N�g���X�V
    config_.update(frame_time_);

    // �S�Ă̕����̈ʒu���X�V
    for (int i = 0; i < LaunCharConst::MAX; ++i)
    {
        alphabets_vec_[i].update(frame_time_);
    }

    // �ł��Â���������ʊO�ɏo�Ă�����񊈐���
    for (int i = 0; i < LaunCharConst::MAX; ++i)
    {
        if (alphabets_vec_[i].get_y() > screen_height_)
            { alphabets_vec_[i].set_active(false); }
    }

    // �L�[��������Ă��邩�m�F
    for (int i = 0; i < LaunCharConst::ALPHABET; ++i)
    {
        char key = LaunCharConst::ALPHABETS[i];

        if (GetAsyncKeyState(key))
        {
            if (!alphabets_pressed_[i])
            {
                // �L�[�̃A���t�@�x�b�g���ˏo
                launch(i, key);
                alphabets_pressed_[i] = true;
            }
        } else
        {
            alphabets_pressed_[i] = false;
        }
    }

}

//* ###################################################################
//* �S�ẴQ�[���A�C�e����`�悷��
//* ###################################################################
void LaunChar::render()
{
    graphics_->sprite_begin();

    // �ݒ��ʂ�`��
    config_.draw();

    // �S�Ă̕�����`��
    for (int i = 0; i < LaunCharConst::MAX; ++i)
        { alphabets_vec_[i].draw(); }

    graphics_->sprite_end();
}

//* ###################################################################
//* �������ˏo����
//* @param id  �L�[�{�[�h��̕�����ID
//* @param key �����ꂽ�L�[�̃A���t�@�x�b�g
//* ###################################################################
void LaunChar::launch(int id, char key)
{
    // ����炷
    switch (config_.get_mode())
    {
    case SoundMode::NORMAL:
        audio_->play_cue(LaunCharConst::SE_WAV.c_str());
        break;
    case SoundMode::DRUM:
        audio_->play_cue(
            LaunCharConst::CUES_DRUM[alphabets_wav_[id]].c_str());
        break;
    case SoundMode::PIANO:
        audio_->play_cue(
            LaunCharConst::CUES_PIANO[alphabets_wav_[id]].c_str());
        break;
    case SoundMode::SILENT:
        break;
    default:
        break;
    }

    if (config_.get_jump_power() > 0)
    {
        // ��\���ɂȂ��Ă�����̂�T��������������
        for (int i = 0; i < LaunCharConst::MAX; ++i)
        {
            if (!alphabets_vec_[i].get_active())
            {
                alphabets_vec_[i].set_char(
                    key, alphabets_pos_[id],
                    (mt_rand_() % 10) - 5);
                break;
            }
        }
    }
}


//* ###################################################################
//* OpeningMaster �� Exit �{�^���̃N���b�N�C�x���g�n���h��
//* WM_CLOSE���b�Z�[�W�𔭍s���ăQ�[�����I��������
//* ###################################################################
void LaunChar::exit()
{
    SendMessage(hwnd_, WM_CLOSE, 0, 0);
}

//* ###################################################################
//* ���������̋t���� on_lost_device() ���Ăяo��
//* ###################################################################
void LaunChar::release_all()
{
    back_font_.on_lost_device();
    front_font_.on_lost_device();
    config_.on_lost_device();

    nono::Game::release_all();
    return;
}

//* ###################################################################
//* ���������� on_reset_device() ���Ăяo��
//* ###################################################################
void LaunChar::reset_all()
{
    config_.on_reset_device();
    front_font_.on_reset_device();
    back_font_.on_reset_device();

    nono::Game::reset_all();
    return;
}
