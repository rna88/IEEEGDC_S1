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

IrrlichtDevice *device = NULL;
video::IVideoDriver* driver = NULL;
scene::ISceneManager* smgr = NULL;
gui::IGUIEnvironment* guienv = NULL;




f32 deltaTime = 0;



video::ITexture* ball;
core::vector2d<f32> position;
core::vector2d<f32> target;
core::vector2d<f32> direction;

f32 speed = .2f * 1000.0f;
s32 screenWidth = 640/*driver->getScreenSize().Width*/;
s32 screenHeight = 480/*driver->getScreenSize().Height*/;


class MyEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_MOUSE_INPUT_EVENT)
		{
			if (event.MouseInput.isLeftPressed())
			{
				target.X = (f32)event.MouseInput.X;
				target.Y = (f32)event.MouseInput.Y;
				direction = target - position;
				direction.normalize();
			}
		}

		if (event.EventType == EET_KEY_INPUT_EVENT)
		{
			if (event.KeyInput.Key == KEY_KEY_W)
			{
				direction.set(0, 0);
			}
			else if (event.KeyInput.Key == KEY_KEY_D)
			{
				direction.set(0, 0);
			}

			if (event.KeyInput.Key == KEY_KEY_O)
			{
				direction.set(0, 0);
			}
			else if (event.KeyInput.Key == KEY_KEY_K)
			{
				direction.set(0, 0);
			}
		}



		return false;
	}
};


void updateBallPosition(f32 deltaTime)
{
	position += (speed * deltaTime) * direction;

	if (position.X > screenWidth - ball->getSize().Width || position.X < 0)
	{
		direction.X *= -1;
	}
		
	if (position.Y > screenHeight - ball->getSize().Height || position.Y < 0)
	{
		direction.Y *= -1;
	}
}






int main()
{

	device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, 0, 1, 0);
	if (!device)
		return 1;

	irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
	if (!soundEngine)
		return 1;
	soundEngine->play2D("../../../../irrlicht-1.8.1/media/irrlichtTheme.ogg");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	device->setWindowCaption(L"Pong");

	MyEventReceiver pongEventReceiver;
	device->setEventReceiver(&pongEventReceiver);

	//guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", core::rect<s32>(10, 10, 260, 22), true);
	//smgr->addCameraSceneNode(0, core::vector3df(0, 30, -40), core::vector3df(0, 5, 0));

	gui::IGUIFont *font = guienv->getFont("../../../../irrlicht-1.8.1/media/bigfont.png");



	ball = driver->getTexture("../../../../irrlicht-1.8.1/media/pong_squareBall.png");
	position.set(220, 220);
	direction.set(1, 1);




	s32 fps = 0;
	s32 now = 0;
	s32 then = device->getTimer()->getTime();


	while (device->run())
	{
		now = device->getTimer()->getTime();
		deltaTime = f32(now - then) / 1000.0f; //<- timers give us time in ms, not seconds, so we divide by 1000 to get time in seconds.
		then = now;
		fps = 1.0f / deltaTime;
	
		updateBallPosition(deltaTime);
		
		driver->beginScene(true, true, video::SColor(255, 100, 101, 140));

		smgr->drawAll();

		
		driver->draw2DImage(
							ball, 
							core::position2d<s32>((s32)position.X, (s32)position.Y),
							core::rect<s32>(0, 0, 32, 32), 0, video::SColor(255, 255, 255, 255),
							true);

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