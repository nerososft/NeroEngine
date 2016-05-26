#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>

namespace NeroEngine{
	GLSLProgram::GLSLProgram() :
		_numAttributes(0),
		_programID(0),
		_vertexShaderID(0),
		_fragmentShaderID(0){
	}


	GLSLProgram::~GLSLProgram()
	{
	}
	void GLSLProgram::complieShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
		_programID = glCreateProgram();

		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0){
			fatalError("VertexShader fail to create!");
		}
		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0){
			fatalError("FragmentShader fail to create!");
		}
		complieShader(vertexShaderFilePath, _vertexShaderID);
		complieShader(fragmentShaderFilePath, _fragmentShaderID);
	}
	void GLSLProgram::linkShaders(){
		if (_programID == 0){
			fatalError("Program failed to create!");
		}
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);
		//Link our program
		glLinkProgram(_programID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(_programID);
			//Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);
			//Use the infoLog as you see fit.
			//In this simple program, we'll just leave
			printf("%s\n", &(infoLog[0]));
			fatalError("Link shader failed!");
		}
		//Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}
	void GLSLProgram::complieShader(const std::string& filePath, GLuint& id){
		std::fstream vertexFile(filePath);
		if (vertexFile.fail()){
			perror(filePath.c_str());
			fatalError("Failed to open" + filePath);
		}
		std::string fileContents = "";
		std::string line;
		while (std::getline(vertexFile, line)){
			fileContents += line + "\n";
		}
		vertexFile.close();
		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);//load GLSL string

		glCompileShader(id);//compile GLSL
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(id); // Don't leak the shader.

			printf("%s\n", &(errorLog[0]));
			fatalError("Shader" + filePath + " failed to complie!");
		}
	}
	void GLSLProgram::addAttribute(const std::string& attributeName){
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}
	GLint GLSLProgram::getUniformLocation(const std::string& uniformLocationName){
		GLint location = glGetUniformLocation(_programID, uniformLocationName.c_str());
		if (location == GL_INVALID_INDEX){
			fatalError("uniform" + uniformLocationName + "not found!");
		}
		return location;
	}
	void GLSLProgram::use(){
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++){
			glEnableVertexAttribArray(i);
		}
	}
	void GLSLProgram::unuse(){
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++){
			glDisableVertexAttribArray(i);
		}
	}
}