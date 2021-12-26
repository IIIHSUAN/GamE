#pragma once

namespace GE {

	// "Camera": view matrix(transform) * projection matrix(translate)     * model matrix * vertex position

	struct CamMatrix
	{
		glm::mat4 view;
		glm::mat4 project;
		glm::mat4 view_project;
	};

	class OrthCamera
	{
	public:
		OrthCamera(float left, float right, float bottom, float top);
		
		const glm::vec3 getPosition() const { return _position; }
		const float getRotationDeg() const { return _rotationDeg; }

		void setPosition(const glm::vec3& pos) { _position = pos; updateCamMatrix(); }
		void setRotate(float rotation) { _rotationDeg = rotation; updateCamMatrix(); }

		const CamMatrix& getMatrix() const { return _camMat; }
	private:
		CamMatrix _camMat;

		glm::vec3 _position;
		float _rotationDeg = 0.0f;  // along z-axis

		void updateCamMatrix();
	};

}