#include "pch.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GE {

	OrthCamera::OrthCamera(float left, float right, float bottom, float top)
	{
		_camMat.project = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		_camMat.view = glm::mat4(1.0f);
		_camMat.view_project = _camMat.project * _camMat.view;
	}

	void OrthCamera::updateCamMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position);
		transform = glm::rotate(transform, glm::radians(_rotationDeg), glm::vec3(0, 0, 1));

		_camMat.view = glm::inverse(transform);
		_camMat.view_project = _camMat.project * _camMat.view;
	}

}