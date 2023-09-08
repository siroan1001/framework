#ifndef __SCENE_ROOT_H__
#define __SCENE_ROOT_H__

#include "SceneBase.hpp"

class SceneRoot : public SceneBase
{
public:
	enum SceneKind
	{
		SCENE_TITLE,
		SCENE_GAME,
		SCENE_MAX
	};

public:
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();

	static void SetNextScene(SceneKind kind);

	static void PlayMusic(const char* file, bool loop);

private:
	void ChangeScene();

private:
	static SceneKind m_index;
	static SceneKind m_nextindex;
};

#endif // __SCENE_ROOT_H__