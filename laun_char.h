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
//* �萔
//* ###################################################################
struct LaunCharConst
{

    static const int ALPHABET = 27;
    static const int MAX = 50;   // �\���\�ȕ�����

    // �T�E���h�L���[
    static const char ALPHABETS[];         // �A���t�@�x�b�g���i�[
    static const std::string CUES_DRUM[];  // �h�����̃T�E���h�L���[
    static const std::string CUES_PIANO[]; // �s�A�m�̃T�E���h�L���[
    static const std::string SE_WAV;       // �P��SE�̃T�E���h�L���[

};

//* ###################################################################
//* �Q�[���𐧌䂷�郁�C���̃N���X
//* ###################################################################
class LaunChar : public nono::Game
{
private:
    nono::Text front_font_;  // �O�ʃt�H���g
    nono::Text back_font_;   // �w�ʃt�H���g

    int screen_width_;  // ��ʂ̕�
    int screen_height_; // ��ʂ̍���

    bool alphabets_pressed_[LaunCharConst::ALPHABET]; // �O�񉟂��ꂽ��
    int alphabets_pos_[LaunCharConst::ALPHABET];      // �ˏo�ʒu
    int alphabets_wav_[LaunCharConst::ALPHABET];      // ����U��ꂽ��
    CharObject alphabets_vec_[LaunCharConst::MAX];    // ��ʏ�S�Ă̕���

    Config config_;        // ���[�h����ݒ肷��
    std::mt19937 mt_rand_; // �����_���ˏo�ɗp����

public:
    LaunChar();
    virtual ~LaunChar();
    void initialize(HWND hwnd);
    void initialize_params();
    void release_all();
    void reset_all();
    void exit();

    //* ###################################################################
    //* �Q�[���֘A
    //* ###################################################################
    void update();
    void render();
    void launch(int id, char key);

    //* ###################################################################
    //* �Z�b�^�[
    //* ###################################################################
    void set_screen_width(int w) { screen_width_ = w; }
    void set_screen_height(int h) { screen_height_ = h; }

    //* ###################################################################
    //* �Q�b�^�[
    //* ###################################################################
    int get_screen_width() { return screen_width_; }
    int get_screen_height() { return screen_height_; }
    nono::Text* get_front_font() { return &front_font_; }
    nono::Text* get_back_font() { return &back_font_; }
    Config* get_config() { return &config_; }
};

#endif
