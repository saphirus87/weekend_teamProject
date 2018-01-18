#pragma once
#include <vector>

class image;

class animation
{
public:
	typedef vector<POINT>	vFrameList;	//프레임 번호 리스트
	typedef vector<int>		vPlayList;	//애니메이션 플레이 리스트 번호

	//public에 왜!?
	//접근이 쉽게 되어야 하니까~

private:
	int			_frameNum;
	vFrameList	_frameList;
	vPlayList	_playList;

	int			_frameWidth;
	int			_frameHeight;

	BOOL		_loop;

	float		_frameUpdateSec;
	float		_elapsedSec;

	DWORD		_nowPlayIndex;
	BOOL		_play;


public:
	animation();
	~animation();

	HRESULT init(BOOL allInit);
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	//디폴트 애니메이션 재생
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	//배열 애니메이션 재생
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	//구간 애니메이션 재생
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);

	//애니메이션 프레임 셋팅
	void setFPS(int framePerSec);

	//프레임 감을 함수
	void frameUpdate(float elapsedTime);

	void start(void);
	void stop(void);
	void pause(void);
	void resume(void);
	void setAnotherAnimation(image* img, int startFrameNum, int endFrameNum, BOOL isStart = FALSE, BOOL isReverse = FALSE, BOOL isLoop = FALSE);

	inline BOOL isPlay(void) { return _play; }
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth(void) { return _frameWidth; }
	inline int getFrameHeight(void) { return _frameHeight; }
	inline int getCurFramePos(void) { return _playList[_nowPlayIndex]; }
	inline int getCurPlayIndex(void) { return _nowPlayIndex; }
	inline int getPlayListSize(void) { return _playList.size(); }
	inline void resetPlayIndex(void) { _nowPlayIndex = 0; }
	inline void setPlayIndex(int setPlayIndex) { _nowPlayIndex = setPlayIndex; }
};

