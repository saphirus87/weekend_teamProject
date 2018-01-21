#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum playerDirection
{
	LEFT,
	RIGHT
};

enum playerState
{
	PLAYER_RIGHT,
	PLAYER_LEFT,
	PLAYER_JUMP,
	PLAYER_IDLE
};

class player : public gameNode
{
protected:
	progressBar* _hpBar;		//�÷��̾� ü��

	playerState _state;			//�÷��̾� ����
	playerDirection _dir;		//����? ������?

	image* _player;				//�÷��̾� �̹���
	RECT _rc;					//�÷��̾� ��Ʈ

	float _x, _y;				//�÷��̾� ��ǥ (left, top)
	float _speed;				//�÷��̾� �̵��ӵ�
	float _gravity;				//�߷�

	float _jumpPower;			//�÷��̾� ������
	int   _jumpTime;			//�÷��̾� �����ð�
	int   _jumpCount;			//�÷��̾� ���� Ƚ��
	bool  _isJump;				//�÷��̾� ���� �ߴ�?
	bool  _isLeft;				//�÷��̾� �������� �̵��޴�?
	bool  _isRight;				//�÷��̾� ���������� �̵��޴�?
	//�÷��̾� ������ �̹����� ���� ����
	int _currentFrameX;
	int _currentFrameY;
	int _frame;
	/////////////////////////////////

	//�÷��̾� ü�� or ü�¹� ����
	float _currentHP, _maxHP;	//�÷��̾� ü��
	float _width, _height;		//�÷��̾� ü�¹� ����
	string _strkey;				//ü�¹� Ű��
	/////////////////////////////////


	//�浹 �˰�����(�ȼ�), �����ӷ���
	//��ǥ : Left Top
	//WINDOW_SIZE 1280 X 720

public:
	////				�̹��� Ű��        , �̹��� ����   , ��Ʈ��ǥ x,y    ,               ü��           , ü�¹� ���α���, ü�¹� ���α���
	HRESULT init();
	void release();
	void update();
	void render();

	void playerAtk();		//���� �Լ�
	void playerMove();		//������ �Լ�
	void playerDraw();		//�׷��ִ� �Լ�

	player();
	~player();
};
