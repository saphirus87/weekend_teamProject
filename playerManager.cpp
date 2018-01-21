#include "stdafx.h"
#include "playerManager.h"


playerManager::playerManager()
{
}


playerManager::~playerManager()
{

}

//초기화를 하자!
//								이미지 키값        , 이미지 파일   , 렉트좌표 x,y    ,               체력           , 체력바 가로길이, 체력바 세로길이
HRESULT playerManager::init(const char* imageName, string strKey, float x, float y, float currentHP, float maxHP, float width, float height)
{
	_strkey = strKey;						//이미지 키값
	_currentHP = currentHP;					//체력
	_maxHP = maxHP;							//체력
	_width = width;							//체력바 길이
	_height = height;						//체력바 길이
	_x = x;									//플레이어 좌표 (left)
	_y = y;									//플레이어 좌표 (top)

	_speed = 3.5f;							//플레이어 이동속도
	_gravity = 0;							//중력
	
	_jumpPower = 0;							//플레이어 점프력
	_jumpTime = 0;							//플레이어 점프시간
	_jumpCount = 0;							//플레이어 점프 횟수
	_isJump = false;						//플레이어 점프 했니?

	_currentFrameX = 0;						//플레이어 프레임
	_currentFrameY = 0;						//플레이어 프레임
	_frame = 0;								//플레이어 프레임

	//렉트
	_rc = RectMake(x, y, _player->getFrameWidth(), _player->getFrameHeight());

	//플레이어 이미지
	_player = IMAGEMANAGER->findImage(imageName);

	//플레이어 체력바 (체력바 키값, 체력바 위치, 체력바 길이)
	_hpBar = new progressBar;
	_hpBar->init(_strkey, _rc.left, _rc.bottom, _width, _height);
	_hpBar->setGauge(_currentHP, _maxHP);

	return S_OK;
}

void playerManager::release()
{

}

void playerManager::update()
{
	//프레임을 돌리자
	_frame++;					//프레임 카운트

	if (_frame % 5 == 0)
	{
		if (_currentFrameX >= _player->getMaxFrameX())
		{
			_currentFrameX = 0;
		}

		_player->setFrameX(_currentFrameX);
		_currentFrameX++;

		_frame = 0;
	}

	_hpBar->setX(_rc.left);					//플레이어 아래에다가 체력바 그려주기
	_hpBar->setY(_rc.bottom);				//플레이어 아래에다가 체력바 그려주기
	_hpBar->setGauge(_currentHP, _maxHP);	//플레이어 아래에다가 체력바 그려주기
	_hpBar->update();						//플레이어 아래에다가 체력바 그려주기
	
	playerAtk();							//플레이어 기본공격 함수
	playerMove();							//플레이어 움직임 함수					
}

void playerManager::render()
{
	playerDraw();							//그려주는 함수
}

//공격 함수
void playerManager::playerAtk()
{

}

//움직임 함수
void playerManager::playerMove()
{
	//플레이어 왼쪽 이동
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= _speed;
	}
	
	//플레이어 오른쪽 이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += _speed;
	}

	//점프
	if (_isJump)
	{
		_y -= _jumpPower;

		_jumpPower -= _gravity;
	}

	//플레이어 점프
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_jumpCount == 0)
		{
			_isJump = true;
			_jumpPower = 6.0f;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		_gravity = 0.3f;
	}

}


//그려주는 함수
void playerManager::playerDraw()
{
	//플레이어 그려주기
	_player->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);

	//체력바 그려주기
	_hpBar->render();
}
