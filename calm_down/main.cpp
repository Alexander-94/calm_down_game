/** Example 010 Shaders

This tutorial shows how to use shaders for D3D8, D3D9, OpenGL, and Cg with the
engine and how to create new material types with them. It also shows how to
disable the generation of mipmaps at texture loading, and how to use text scene
nodes.

This tutorial does not explain how shaders work. I would recommend to read the
D3D, OpenGL, or Cg documentation, to search a tutorial, or to read a book about
this.

At first, we need to include all headers and do the stuff we always do, like in
nearly all other tutorials:
*/
#include <irrlicht.h>
#include <iostream>
#include "driverChoice.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

/*
Because we want to use some interesting shaders in this tutorials, we need to
set some data for them to make them able to compute nice colors. In this
example, we'll use a simple vertex shader which will calculate the color of the
vertex based on the position of the camera.
For this, the shader needs the following data: The inverted world matrix for
transforming the normal, the clip matrix for transforming the position, the
camera position and the world position of the object for the calculation of the
angle of light, and the color of the light. To be able to tell the shader all
this data every frame, we have to derive a class from the
IShaderConstantSetCallBack interface and override its only method, namely
OnSetConstants(). This method will be called every time the material is set.
The method setVertexShaderConstant() of the IMaterialRendererServices interface
is used to set the data the shader needs. If the user chose to use a High Level
shader language like HLSL instead of Assembler in this example, you have to set
the variable name as parameter instead of the register index.
*/

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

#define SPEED 2
extern bool fullscreen = false;


IrrlichtDevice* device = 0;  // окно которое выдает движок для работы с трехмерным миром
IVideoDriver* driver;    // то через что выводится вся графика
ISceneManager* smgr;     // менеджер сцены - через него делается почти вся работа над объектами
IGUIEnvironment* guienv;    // графический интерфейс


//создаем ландшафт
ITerrainSceneNode* oCreateTerrain()
{ 
	ITerrainSceneNode* o = smgr->addTerrainSceneNode(
		"img/terrain/map.png",
		0,						// родительский объект
		-1,						// id узла
		vector3df(0,-100,0),    // позиция
		vector3df(0,0,0),       // поворот
		vector3df(5,0.5,5),       //масштаб
		SColor (255, 255, 255, 255), //цвет вершин
		5,                      // максимум LOD - level of details for the node (детализация)
		ETPS_17,                // размер патча
		4,                       // коэф-т размытия of the nodes
		false
	);
	                      //указываем слой и файл текстуры
	o->setMaterialTexture(0, driver->getTexture("img/terrain/texture.png"));
	o->setMaterialType(EMT_DETAIL_MAP); // типа материала 
	return o;
}


class MyEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	    //??? irr::EMIE_MOUSE_WHEEL
		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	MyEventReceiver()
	{
		for (u32 i = 0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

irr::f32 mouseWheel;

int main()
{
	//The event receiver for keeping the pressed keys is ready, the actual responses will be made inside the render loop, right before drawing the scene.
	MyEventReceiver receiver;
	//the root object for doing anything with the engine
	//EDT_SOFTWARE - renders the img/terrain/texture.png, other - EDT_OPENGL - doesn't
	device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(1080, 720), 32, fullscreen, false, false, &receiver);
	if (!device)
		return 1;
	device->setWindowCaption(L"Hello World! - Irrlicht CALM DOWN Demo");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	guienv->addStaticText(L"Q - Up, E - Down, WASD - movement, ESC - exit",rect<s32>(10, 10, 260, 22), true);
	
	//                                    X   Y  Z      //look at
	smgr->addCameraSceneNode(0, vector3df(0, 30, 1000), vector3df(0, -100, 0));

	//camera creation
	ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100, 0.4);
	camera->setPosition(vector3df(20, 0, 20));

	//objects creation
	ITerrainSceneNode* terrain = oCreateTerrain();

	//The game cycle:
	//We run the device in a while() loop, until the device does not want to run any more. 
	//This would be when the user closes the window
	while (device->run())
	{
		core::vector3df nodePosition = camera->getPosition();
		if (receiver.IsKeyDown(irr::KEY_KEY_W))
			nodePosition.Z += SPEED;
		else if (receiver.IsKeyDown(irr::KEY_KEY_S))
			nodePosition.Z -= SPEED;

		if (receiver.IsKeyDown(irr::KEY_KEY_A))
			nodePosition.X -= SPEED;
		else if (receiver.IsKeyDown(irr::KEY_KEY_D))
			nodePosition.X += SPEED;

		if (receiver.IsKeyDown(irr::KEY_KEY_Q))
			nodePosition.Y -= SPEED;
		else if (receiver.IsKeyDown(irr::KEY_KEY_E))
			nodePosition.Y += SPEED;

		if (receiver.IsKeyDown(irr::KEY_ESCAPE))
		{
			device->drop();
			exit(0);
		}
		camera->setPosition(nodePosition);

		driver->beginScene(true, true, SColor(255, 157, 212, 140));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}

	device->drop();
	return 0;
}

/*
Compile and run this, and I hope you have fun with your new little shader
writing tool :).
**/
