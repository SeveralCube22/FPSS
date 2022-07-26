#pragma once

#include "player.hpp"

void Player::strafeLeft(float deltaTime) {
	pos -= (mSpeed * deltaTime * glm::normalize(glm::cross(direction, up)));
}

void Player::strafeRight(float deltaTime) {
	pos += (mSpeed * deltaTime * glm::normalize(glm::cross(direction, up))); // move along span of right vector
}

void Player::moveForward(float deltaTime) {
	auto right = glm::cross(direction, up);
	auto forward = glm::cross(up, right);
	pos += (mSpeed * deltaTime * forward); // move along the span of direction vector
}

void Player::moveBackward(float deltaTime) {
	auto right = glm::cross(direction, up);
	auto forward = glm::cross(up, right);
	pos -= (mSpeed * deltaTime * forward); // move along the span of direction vector
}

void Player::jump(float vSpeed) {
	if (pos.y == 0)
		this->vSpeed = vSpeed;
}

void Player::calculateVertPos(float deltaTime) {
	if (pos.y >= 30) {
		float prevY = pos.y;
		pos.y += (vSpeed * deltaTime + .5 * -9.81 * deltaTime * deltaTime);

		float delta = pos.y - prevY;
		vSpeed = vSpeed * vSpeed + 2 * -9.81 * delta;
	}
	else {
		this->vSpeed = 0;
	}
}

void Player::incrementYaw(float xOffset) {
	yaw += (xOffset * sensitivity);
}

void Player::incrementPitch(float yOffset) {
	pitch += (yOffset * sensitivity);

	if (pitch > 89.0f) // essentially controlling the "height" (direction.y) player can see 
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}

glm::mat4 Player::lookAt() {
	direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)); // multiplying by pitch since x value is effected by both yaw and pitch.
																			  // from top down perspective (x and z axis), yaw
																			  // from side perspective (x and y axis), pitch
	direction.y = glm::sin(glm::radians(pitch));
	direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	direction = glm::normalize(direction);
	
	return glm::lookAt(pos, pos + direction, up); 
}

glm::vec3 Player::hit() {
	return pos + direction * 10.0f;
}