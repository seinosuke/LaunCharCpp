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
//* �萔
//* ###################################################################
struct CharObjectConst
{
    static const int GRAVITY = -1;
};

//* ###################################################################
//* �ˏo���镶������Ǘ�����N���X
//* ###################################################################
class CharObject
{
private:
    LaunChar* laun_char_;
    nono::Text* front_font_;  // �O�ʃt�H���g
    nono::Text* back_font_;   // �w�ʃt�H���g
    std::string alphabet_;   // �\������A���t�@�x�b�g

    int screen_width_;     // �X�N���[���̕�
    int screen_height_;    // �X�N���[���̍���

    float x_;           // X���W
    float y_;           // Y���W
    float dx_;          // X�����̑���
    float prev_y_;      // �O���Y���W
    float jump_power_;  // �W�����v�͂�
    bool active_;       // true �ňʒu�X�V�Ȃ�

    float timer_;
    float delay_;

public:
    CharObject();
    virtual ~CharObject();
    void initialize(LaunChar* laun_char);

    void update(float frame_time);
    void draw();

    //* ###################################################################
    //* �Q�b�^�[
    //* ###################################################################
    float get_x() { return x_; }
    float get_y() { return y_; }
    bool get_active() { return active_; }

    //* ###################################################################
    //* �Z�b�^�[
    //* ###################################################################
    void set_char(char alphabet, int x, int dx);
    void set_active(bool a) { active_ = a; }
};

#endif