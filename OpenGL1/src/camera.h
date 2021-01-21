#pragma once
#include<glm/glm.hpp>


class Camera {
private:
	glm::vec3 m_CamPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_CamFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CamUp = glm::vec3(0.0f, 0.1f, 0.0f);
	float m_Yaw;
	float m_Pitch;
	float m_Cameraspeed;

public:
	Camera();
	const glm::vec3 GetCameraPosition() { return m_CamPos; }
	const glm::vec3 GetCameraFrontVec() { return m_CamFront; }
	const glm::vec3 GetCameraUpVec() { return m_CamUp; }
	const float GetCameraYaw() { return m_Yaw; }
	const float GetCameraPitch() { return m_Pitch; }
	const float GetCamerSpeed() { return m_Cameraspeed; }

	const void SetCameraPosition(glm::vec3 a);
	const void SetCameraFrontVec(glm::vec3 a);
	const void SetCameraUpVec(glm::vec3 a);
	const void SetCameraYaw(float a);
	const void SetCameraSpeed(float a);
	const void SetCameraPitch(float a);
	
	const void UpdateFront();
	const void UpdatePos(float multiplier = 1.0f);
	const void UpdateCameraSpeed(float DT ,float multiplier = 2.5f);
	const void UpdateUp(float multiplier = 1.0f);

	const void RotateCamera(int a);
};



/*double lastX = 400 , lastY = 300;
double xoff = 0.0f, yoff = 0.0f;

bool firstMouse = true;

float mouse_sensitivity = 0.01f;*/



