#ifndef PerspectiveCamera_h
#define PerspectiveCamera_h

#include "ICamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace zephyr::rendering {

class PerspectiveCamera : public ICamera {
public:
    PerspectiveCamera(float fovy, float aspect, float near, float far);

    glm::mat4 View() override;
    glm::mat4 Projection() override;
    glm::vec3 Position() override;

    void Update(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up);

private:
    glm::mat4 m_View;
    glm::mat4 m_Projection;
    glm::vec3 m_Position;
};

}

#endif