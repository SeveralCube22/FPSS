#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Player {
private:
	glm::vec3 pos, up, target, direction;
	float mSpeed, vSpeed, yaw, pitch, sensitivity;

public:
	Player(float mSpeed, glm::vec3 pos, glm::vec3 target, glm::vec3 up, float sensitivity) : pos(pos), target(target), up(up),
																						mSpeed(mSpeed), sensitivity(sensitivity) {
		direction = glm::normalize(pos - target);
		yaw = -90;
		pitch = 0;
	}

	void strafeLeft(float deltaTime);
	void strafeRight(float deltaTime);
	void moveForward(float deltaTime);
	void moveBackward(float deltaTime);
	void jump(float vSpeed);
	void calculateVertPos(float deltaTime);

	glm::vec3 hit();

	void incrementYaw(float xOffset);
	void incrementPitch(float yOffset);

	glm::mat4 lookAt();
};