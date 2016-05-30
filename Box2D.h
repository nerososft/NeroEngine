#pragma once
#include <Box2D\Box2D.h>
namespace  NeroEngine{
	class Box2D
	{
	public:
		void init();

		Box2D();
		~Box2D();
	private:
		// Define the grivaty vector
		b2Vec2 _gravity;
		// Construct a world object, which will hold and simulate the rigid bodies.
		b2World world();

		// Define the ground body.
		b2BodyDef groundBodyDef;


		// Define the ground box shape.
		b2PolygonShape groundBox;

	};
}

