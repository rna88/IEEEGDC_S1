#include <iostream>
#include <irrlicht.h>

using namespace std;
using namespace irr;


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, false, true, 0);

	if (!device)
		return 1;

	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", core::rect<s32>(10, 10, 260, 22), true);

	scene::IAnimatedMesh* mesh = smgr->getMesh("../../../../irrlicht-1.8.1/media/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	
	scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

	if (node)
	{
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("../../../../irrlicht-1.8.1/media/sydney.bmp"));
	}

	smgr->addCameraSceneNode(0, core::vector3df(0, 30, -40), core::vector3df(0, 5, 0));


	while (device->run())
	{
		driver->beginScene(true, true, video::SColor(255, 100, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}

	device->drop();

	return 0;
}