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
irrklang::ISoundEngine* soundEngine = NULL;



f32 deltaTime = 0;



video::ITexture* ball = NULL;
video::ITexture* paddle1 = NULL;
video::ITexture* paddle2 = NULL;
video::ITexture* background = NULL;

core::vector2d<f32> ballPosition;
core::vector2d<f32> target;
core::vector2d<f32> direction;
core::vector2d<f32> paddle1Position;
core::vector2d<f32> paddle2Position;
s32 player1Score = 0;
s32 player2Score = 0;


f32 speed = .2f * 1000.0f;
f32 paddle1Speed = .5f * 1000.0f;
f32 paddle2Speed = .5f * 1000.0f;
s32 screenWidth = 640/*driver->getScreenSize().Width*/;
s32 screenHeight = 480/*driver->getScreenSize().Height*/;


class MyEventReceiver : public IEventReceiver
{
public:
	MyEventReceiver()
	{
		for (u32 i = 0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}
	
	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_MOUSE_INPUT_EVENT)
		{
			if (event.MouseInput.isLeftPressed())
			{
				target.X = (f32)event.MouseInput.X;
				target.Y = (f32)event.MouseInput.Y;
				direction = target - ballPosition;
				direction.normalize();
			}
		}

		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


void updateBallballPosition(f32 deltaTime)
{
	ballPosition += (speed * deltaTime) * direction;
		
	// ball bouncing off the top and bottom walls
	if (ballPosition.Y > screenHeight - ball->getSize().Height || ballPosition.Y < 0)
	{
		direction.Y *= -1;
		soundEngine->play2D("../../../../irrlicht-1.8.1/media/impact.wav");
	}

	// ball passes goal line of player 1
	if (ballPosition.X < 0)
	{
		player2Score++;
		direction.X = 0;
		direction.Y = 0;
		ballPosition.X = 320;
		ballPosition.Y = 240;
		soundEngine->play2D("../../../../irrlicht-1.8.1/media/ball.wav");
	}
	
	// ball passes goal line of player 2
	if (ballPosition.X > screenWidth - ball->getSize().Width)
	{
		player1Score++;
		direction.X = 0;
		direction.Y = 0;
		ballPosition.X = 320;
		ballPosition.Y = 240;
		soundEngine->play2D("../../../../irrlicht-1.8.1/media/ball.wav");
	}
	
	
	/*if (ballPosition.X > screenWidth - ball->getSize().Width || ballPosition.X < 0)
	{
		direction.X *= -1;
		soundEngine->play2D("../../../../irrlicht-1.8.1/media/impact.wav");
	}*/


}



int main()
{

	device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, 0, 0, 1, 0);
	if (!device)
		return 1;

	soundEngine = irrklang::createIrrKlangDevice();
	if (!soundEngine)
		return 1;

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	device->setWindowCaption(L"Pong");

	MyEventReceiver pongEventReceiver;
	device->setEventReceiver(&pongEventReceiver);

	gui::IGUIFont *font = guienv->getFont("../../../../irrlicht-1.8.1/media/SF_SquareHead.bmp");

	ball = driver->getTexture("../../../../irrlicht-1.8.1/media/pong_squareBall.png");
	ballPosition.set(220, 220);
	direction.set(1, 1);

	paddle1 = driver->getTexture("../../../../irrlicht-1.8.1/media/pong_squarePaddle.png");
	paddle1Position.set(10, 240);

	paddle2 = driver->getTexture("../../../../irrlicht-1.8.1/media/pong_squarePaddle.png");
	paddle2Position.set(610, 240);

	background = driver->getTexture("../../../../irrlicht-1.8.1/media/background.png");
	

	s32 fps = 0;
	s32 now = 0;
	s32 then = device->getTimer()->getTime();


	while (device->run())
	{
		now = device->getTimer()->getTime();
		deltaTime = f32(now - then) / 1000.0f; //<- timers give us time in ms, not seconds, so we divide by 1000 to get time in seconds.
		then = now;
		fps = 1.0f / deltaTime;
	
		updateBallballPosition(deltaTime);


		if (pongEventReceiver.IsKeyDown(KEY_KEY_W))
		{
			paddle1Position.Y += (paddle1Speed * deltaTime);
		}
		else if (pongEventReceiver.IsKeyDown(KEY_KEY_D))
		{
			paddle1Position.Y -= (paddle1Speed * deltaTime);
		}
		if (pongEventReceiver.IsKeyDown(KEY_KEY_O))
		{
			paddle2Position.Y += (paddle2Speed * deltaTime);
		}
		else if (pongEventReceiver.IsKeyDown(KEY_KEY_K))
		{
			paddle2Position.Y -= (paddle2Speed * deltaTime);
		}
		if (pongEventReceiver.IsKeyDown(KEY_ESCAPE))
		{
			device->closeDevice();
		}
		
		driver->beginScene(true, true, video::SColor(255, 100, 101, 140));

		smgr->drawAll();

		driver->draw2DImage(
							background, 
							core::position2d<s32>(0, 0), 
							core::rect<s32>(0, 0, 640, 480),
							0, 
							video::SColor(255, 255, 255, 255),
							true); 
		
		driver->draw2DImage(
							ball, 
							core::position2d<s32>((s32)ballPosition.X, (s32)ballPosition.Y),
							core::rect<s32>(0, 0, 32, 32), 0, video::SColor(255, 255, 255, 255),
							true);

		driver->draw2DImage(
			paddle1,
			core::position2d<s32>((s32)paddle1Position.X, (s32)paddle1Position.Y),
			core::rect<s32>(0, 0, 15, 64), 0, video::SColor(255, 255, 255, 255),
			true);

		driver->draw2DImage(
			paddle2,
			core::position2d<s32>((s32)paddle2Position.X, (s32)paddle2Position.Y),
			core::rect<s32>(0, 0, 15, 64), 0, video::SColor(255, 255, 255, 255),
			true);


		font->draw((core::stringc(fps) + " FPS"), core::rect<s32>(10, 10, 0, 0), video::SColor(255, 255, 255, 255)); // fonts must be drawn after the scene, because they end up on top.
		font->draw(core::stringc(player1Score), core::rect<s32>(300, 220, 0, 0), video::SColor(255, 255, 0, 0));
		guienv->drawAll();
		
		driver->endScene();
	}

	device->drop();

	return 0;
}