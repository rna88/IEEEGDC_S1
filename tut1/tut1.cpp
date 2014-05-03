#include <iostream>
#include <irrlicht.h>
#include <irrKlang.h>

using namespace std;
using namespace irr;


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "IrrKlang.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

double deltaTime = 0;


int main()
{

	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, 0, 1, 0);
	if (!device)
		return 1;

	irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
	if (!soundEngine)
		return 1;

	soundEngine->play2D("../../../../irrlicht-1.8.1/media/irrlichtTheme.ogg");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	device->setWindowCaption(L"Pong");

	//guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", core::rect<s32>(10, 10, 260, 22), true);
	//smgr->addCameraSceneNode(0, core::vector3df(0, 30, -40), core::vector3df(0, 5, 0));

	gui::IGUIFont *font = guienv->getFont("../../../../irrlicht-1.8.1/media/bigfont.png");

	double fps = 0;
	double now = 0;
	double then = device->getTimer()->getTime();


	while (device->run())
	{
		now = device->getTimer()->getTime();
		deltaTime = /*(f32)*/ (now - then) / 1000; //<- timers give us time in ms, not seconds, so we divide by 1000 to get time in seconds.
		then = now;
		fps = 1 / deltaTime;
	
		
		
		driver->beginScene(true, true, video::SColor(255, 100, 101, 140));

		smgr->drawAll();

		font->draw(core::stringc(fps), core::rect<s32>(10, 10, 0, 0), video::SColor(255, 255, 255, 255)); // fonts must be drawn after the scene, because they end up on top.
		guienv->drawAll();
		driver->endScene();



		/*core::stringw (L"Movement Example - Irrlicht Engine [");
		tmp += driver->getName();
		tmp += L"] fps: ";
		tmp += fps;
		device->setWindowCaption(tmp.c_str());

		guienv -> add*/
	}

	device->drop();

	return 0;
}