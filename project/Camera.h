#pragma once

#include "gameObject.h"

class Camera : public GameObject {

public:
	Camera();
private:
	const glm::vec3 DEFAULT_POSITION {40, 31, 4}; // 200, 200, 0
	int windowWidth = 0;
	int windowHeight = 0;
public:

	void update(float _dt, int _windowWidth, int _windowHeight) override;
	
};
