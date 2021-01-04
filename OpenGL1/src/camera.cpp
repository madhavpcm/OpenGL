#include "camera.h"

const void Camera::SetCameraPosition(glm::vec3 a)
{
    m_CamPos = a;
}

const void Camera::SetCameraFrontVec(glm::vec3 a)
{
    m_CamFront = a;
}
const void Camera::SetCameraUpVec(glm::vec3 a)
{
    m_CamUp = a;
}
const void Camera::SetCameraYaw(float a)
{
    m_Yaw = a;
}
const void Camera::SetCameraSpeed(float a)
{
    m_Cameraspeed = a;
}
const void Camera::SetCameraPitch(float a)
{
    m_Pitch = a;
}

const void Camera::UpdateFront() {
    m_CamFront.x = cos(glm::radians(m_Yaw));
    m_CamFront.z = sin(glm::radians(m_Yaw));
    m_CamFront = glm::normalize(m_CamFront);
}
const void Camera::UpdatePos(float multiplier)
{
    m_CamPos += m_Cameraspeed * multiplier * m_CamFront ;
}
const void Camera::UpdateCameraSpeed(float multiplier , float DT) {
    m_Cameraspeed = multiplier * DT;
}
const void Camera::UpdateUp(float multiplier) {
    m_CamPos += glm::normalize(-m_CamUp) * m_Cameraspeed * multiplier;
}
const void Camera::RotateCamera(int a)
{
    SetCameraYaw(m_Yaw + m_Cameraspeed * a);
    UpdateFront();
}
Camera::Camera()
    :m_Yaw(0.0f), m_Pitch(-89.0f),m_CamPos(glm::vec3(0.0f, 0.0f ,3.0f)),
    m_CamFront(glm::vec3(0.0f, 0.0f, -1.0f)),m_CamUp(glm::vec3(0.0f, 0.1f, 0.0f)),m_Cameraspeed(1.0f)
{
}