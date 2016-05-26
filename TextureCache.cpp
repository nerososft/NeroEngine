#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
namespace NeroEngine{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}


	GLTexture TextureCache::getTexture(std::string texturePath){

		//auto  mit =  _textureMap.find(texturePath);
		//在map中查找texture
		std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);

		if (mit == _textureMap.end()){
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			std::pair<std::string, GLTexture> newPair(texturePath, newTexture);

			//_textureMap.insert(make_pair(texturePath,newTexture));
			_textureMap.insert(newPair);

			std::cout << "读取贴图:" + texturePath + "\n";
			return newTexture;
		}
		//std::cout << "使用缓存贴图\n";
		return mit->second;


	}
}