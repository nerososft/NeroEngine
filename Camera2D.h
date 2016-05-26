#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace NeroEngine{
	class Camera2D
	{
	public:
		Camera2D();
		void update();
		void init(int screenWidth,int screenHeight);

		void setScale(float newScale){ _scale = newScale; _needsMatrixUpdate = true; }
		void setPosition(const glm::vec2 newPosition){ _position = newPosition; _needsMatrixUpdate = true; }

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);


		bool isBoxiInView(const glm::vec2& position,const glm::vec2& dimensions);

		float getScale(){ return _scale; }
		glm::vec2 getPosition(){ return _position; }
		glm::mat4 getCameraMatrix(){ return _cameraMatrix; }

		~Camera2D();
	private:
		int _screenWidth;
		int _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};
}

