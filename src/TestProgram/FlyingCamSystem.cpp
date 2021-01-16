#include "FlyingCamSystem.h"

#include <NobleEngine/InputManager.h>
#include <NobleEngine/Transform.h>
#include <NobleEngine/Application.h>
#include <NobleEngine/Entity.h>
#include <NobleEngine/Camera.h>

SetupComponentList(FlyingCam);

void FlyingCamSystem::OnUpdate(std::shared_ptr<FlyingCam> comp)
{
	UpdateControls(comp);
	UpdateCameraRotation(comp);
}

void FlyingCamSystem::UpdateControls(std::shared_ptr<FlyingCam> cam)
{
	std::shared_ptr<Transform> tr = GetApplication()->GetEntity(cam->entityID)->GetComponent<Transform>();
	std::shared_ptr<Camera> ca = GetApplication()->GetEntity(cam->entityID)->GetComponent<Camera>();
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	if (InputManager::IfKeyDown(SDL_SCANCODE_W))
	{
		tr->position += cam->movementSpeed * ca->forward;
	}
	if (InputManager::IfKeyDown(SDL_SCANCODE_S))
	{
		tr->position -= cam->movementSpeed * ca->forward;
	}
	if (InputManager::IfKeyDown(SDL_SCANCODE_A))
	{
		glm::vec3 direction = glm::cross(ca->forward, up);
		tr->position -= cam->movementSpeed * direction;
	}
	if (InputManager::IfKeyDown(SDL_SCANCODE_D))
	{
		glm::vec3 direction = glm::cross(ca->forward, up);
		tr->position += cam->movementSpeed * direction;
	}
	if (InputManager::IfKeyDown(SDL_SCANCODE_SPACE))
	{
		tr->position += cam->movementSpeed * up;
	}
	if (InputManager::IfKeyDown(SDL_SCANCODE_X))
	{
		tr->position -= cam->movementSpeed * up;
	}
}

void FlyingCamSystem::UpdateCameraRotation(std::shared_ptr<FlyingCam> cam)
{
	if (InputManager::IfMouseButtonDown(0))
	{
		std::shared_ptr<Camera> ca = GetApplication()->GetEntity(cam->entityID)->GetComponent<Camera>();
		cam->newMousePos = glm::vec2(InputManager::mouseX, InputManager::mouseY);

		if (cam->firstMouse)
		{
			cam->oldMousePos = cam->newMousePos;
			cam->firstMouse = false;
		}

		float xoffset = cam->newMousePos.x - cam->oldMousePos.x;
		float yoffset = cam->oldMousePos.y - cam->newMousePos.y; // reversed since y-coordinates go from bottom to top
		cam->oldMousePos = cam->newMousePos;

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		cam->yaw += xoffset;
		cam->pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (cam->pitch > 89.0f)
			cam->pitch = 89.0f;
		if (cam->pitch < -89.0f)
			cam->pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
		front.y = sin(glm::radians(cam->pitch));
		front.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
		ca->forward = glm::normalize(front);
	}
	else
	{
		cam->firstMouse = true;
	}
}