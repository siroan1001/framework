#ifndef __SCENE_ROOT_H__
#define __SCENE_ROOT_H__

#include "SceneBase.hpp"
#include "ShaderManager.h"

class SceneRoot : public SceneBase
{
public:
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();

private:
	void ChangeScene();

private:
	int m_index;
	//ShaderManager& ShaderMane;
};

#endif // __SCENE_ROOT_H__