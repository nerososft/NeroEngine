#pragma once
#include <string>
#include <GL\glew.h>
namespace NeroEngine{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();
		void complieShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void linkShaders();
		void addAttribute(const std::string& attributeName);
		GLint getUniformLocation(const std::string& uniformLocationName);
		void use();
		void unuse();
	private:
		int _numAttributes;
		void complieShader(const std::string& filePath, GLuint& id);
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};

}