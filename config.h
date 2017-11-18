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
//* �T�E���h���[�h
//* ###################################################################
enum struct SoundMode
{
    NORMAL, // �P��SE���[�h
    DRUM,   // �h�������[�h
    PIANO,  // �s�A�m���[�h
    SILENT, // �T�C�����g
};

//* ###################################################################
//* �萔
//* ###################################################################
struct ConfigConst
{
    static const int MODE_MAX = 3; // ���[�h��
    static const int JUMP_MAX = 5; // �W�����v�͍ő�l
};

//* ###################################################################
//* ���[�h�̐ݒ�ȂǂɊւ���N���X
//* ###################################################################
class Config
{
private:
    LaunChar* laun_char_;
    nono::Input* input_;
    nono::Text front_font_;  // �O�ʃt�H���g
    nono::Text back_font_;   // �w�ʃt�H���g

    SoundMode mode_;   // ���݂̃��[�h
    int mode_cnt_;     // ���݂̃��[�h�̔ԍ�
    std::string text_; // �\������e�L�X�g
    bool visible_;     // true�ŕ\��
    int jump_power_;   // �ˏo�����

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
