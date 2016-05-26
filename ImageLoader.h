#pragma once
#include "GLTexture.h"
#include <string>
namespace NeroEngine{
	class ImageLoader{
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}