//
//
////** Postprocessing Example
////**
////** This software is provided 'as-is' without any express or implied warranty.
////** Use at your own risk.
////**
//
//#include <irrlicht.h>
//#include <iostream>
//
//// Irrlicht's 'media' directory
//#define IRRMEDIA "../../../../irrlicht-1.8.1/media/"
//
//using namespace irr;
//
//#ifdef _MSC_VER
//#pragma comment(lib, "Irrlicht.lib")
//#endif
//
////**
////** Postprocessing code
////**
//
//// the shader code
//const c8* vs_pp =
//"void main(void)\n"
//"{\n"
//"   vec2 tCoords;\n"
//"   gl_Position = vec4(gl_Vertex.x, gl_Vertex.y, 0.0, 1.0);\n"
//"   tCoords.x = 0.5*(1.0 + gl_Vertex.x);\n"
//"   tCoords.y = 0.5*(1.0 + gl_Vertex.y);\n"
//"   gl_TexCoord[0].xy = tCoords.xy;\n"
//"}\n";
//
//const c8* ps_pp =
//"uniform sampler2D render;\n"
//"uniform sampler2D effect;\n"
//"void main(void)\n"
//"{\n"
//"   vec4 color1 = texture2D(render, gl_TexCoord[0].xy);\n"
//"   vec4 color2 = texture2D(effect, gl_TexCoord[0].xy);\n"
//"   vec4 final = color2.r*color1;\n"
//"   if (color1.r > 0.75)\n"
//"       final = 1.0*color1;\n"
//"   gl_FragColor = final;\n"
//"}\n";
//
//// the callback - called by Irrlicht before the screen quad is rendered
//class PPShaderCallback : public video::IShaderConstantSetCallBack
//{
//public:
//
//	virtual void OnSetConstants(video::IMaterialRendererServices* services,
//		s32 userData)
//	{
//		video::IVideoDriver* vid = services->getVideoDriver();
//
//		// just set the textures
//		s32 TextureLayerID = 0;
//		// this is where the scne was rendered
//		services->setPixelShaderConstant("render", &TextureLayerID, 1);
//		TextureLayerID = 1;
//		// just a texture to create an effect
//		services->setPixelShaderConstant("effect", &TextureLayerID, 1);
//	}
//};
//
//// a class to hold our screen quad and render-target texture
//class Postprocess
//{
//public:
//	Postprocess(IrrlichtDevice* device)
//	{
//		dev = device;
//		vid = device->getVideoDriver();
//
//		// render target
//		rtt = vid->addRenderTargetTexture(core::dimension2d<u32>(512, 512));
//
//		// material for screen quad
//		material.Wireframe = false;
//		material.Lighting = false;
//		material.ZWriteEnable = false;
//
//		// screen quad
//		vert[0] = video::S3DVertex(-1, -1, 0, 0, 0, 1, video::SColor(0), 0, 1);
//		vert[1] = video::S3DVertex(-1, 1, 0, 0, 0, 1, video::SColor(0), 0, 0);
//		vert[2] = video::S3DVertex(1, 1, 0, 0, 0, 1, video::SColor(0), 1, 0);
//		vert[3] = video::S3DVertex(1, -1, 0, 0, 0, 1, video::SColor(0), 1, 1);
//		// drawing order
//		index[0] = 0;
//		index[1] = 1;
//		index[2] = 2;
//		index[3] = 0;
//		index[4] = 2;
//		index[5] = 3;
//	}
//
//	~Postprocess()
//	{
//		if ((rtt))
//			vid->removeTexture(rtt);
//		dev->drop();
//	}
//
//	void render()
//	{
//		vid->setMaterial(material);
//		vid->setTransform(video::ETS_WORLD, core::matrix4());
//		vid->drawIndexedTriangleList(vert, 4, index, 2);
//	}
//
//	video::SMaterial& getMaterial()
//	{
//		return material;
//	}
//
//	IrrlichtDevice* dev;
//	video::IVideoDriver* vid;
//	video::ITexture* rtt;
//	video::SMaterial material;
//	video::S3DVertex vert[4];
//	u16 index[6];
//};
//
////**
////** SCENE
////**
//
///* shader code */
//const c8* vs_tex =
//"uniform mat4 mWorldViewProj;\n"
//"void main(void)\n"
//"{\n"
//"   gl_Position = mWorldViewProj*gl_Vertex;\n"
//"   gl_TexCoord[0] = gl_MultiTexCoord0;\n"
//"}\n";
//const c8* ps_tex =
//"uniform sampler2D myTexture;\n"
//"void main(void)\n"
//"{\n"
//"   gl_FragColor = texture2D(myTexture, vec2(gl_TexCoord[0]));\n"
//"}\n";
//
//class TextureShaderCallback : public video::IShaderConstantSetCallBack
//{
//public:
//
//	virtual void OnSetConstants(video::IMaterialRendererServices* services,
//		s32 userData)
//	{
//		video::IVideoDriver* vid = services->getVideoDriver();
//
//		core::matrix4 worldViewProj;
//		worldViewProj = vid->getTransform(video::ETS_PROJECTION);
//		worldViewProj *= vid->getTransform(video::ETS_VIEW);
//		worldViewProj *= vid->getTransform(video::ETS_WORLD);
//
//		services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);
//		s32 TextureLayerID = 0;
//		services->setPixelShaderConstant("myTexture", &TextureLayerID, 1);
//	}
//};
//
//// handle keystrokes
//class MyEventReceiver : public IEventReceiver
//{
//public:
//	MyEventReceiver() : ppEffect(0) {}
//
//	virtual bool OnEvent(const SEvent& event)
//	{
//		if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
//			event.KeyInput.PressedDown)
//			switch (event.KeyInput.Key)
//		{
//			case 27:    // ESC
//				ppEffect = -1;  // signal to quit
//				break;
//			case '0':   // no effect
//			case '1':   // effect
//				ppEffect = event.KeyInput.Key - '0';
//				break;
//		}
//		return false;
//	}
//
//	int ppEffect;
//};
//
//int main()
//{
//	std::cout << "main" << std::endl;
//	// create an OpenGL instance
//	IrrlichtDevice* device = createDevice(video::EDT_OPENGL,
//		core::dimension2d<u32>(800, 800));
//	if (device == 0)
//	{
//		std::cout << "Could not create an OpenGL context" << std::endl;
//		return 1; // could not create selected driver.
//	}
//	video::IVideoDriver* driver = device->getVideoDriver();
//	video::ITexture* theTex = driver->getTexture(IRRMEDIA "wall.bmp");
//	if (theTex == 0)
//	{
//		std::cout << "Could not create a texture from 'wall.bmp'" << std::endl;
//		std::cout << "Check your setting of IRRMEDIA" << std::endl;
//		return 2;
//	}
//
//	//**
//	//** Postprocessing code
//	//**
//
//	// create material
//	video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
//	if (gpu == 0)
//	{
//		std::cout << "Could not access the GPU" << std::endl;
//		return 3;
//	}
//
//	s32 ppShader;
//	PPShaderCallback* ppcb = new PPShaderCallback();
//
//	// create the shaders (GLSL)
//	ppShader = gpu->addHighLevelShaderMaterial(
//		vs_pp, "vertexMain", video::EVST_VS_1_1,
//		ps_pp, "pixelMain", video::EPST_PS_1_1,
//		ppcb, video::EMT_SOLID, 0, video::EGSL_DEFAULT);
//	if (ppShader < 0)
//	{
//		std::cout << "Could not create the postprocessing shader" << std::endl;
//		return 4;
//	}
//
//	ppcb->drop();
//
//	// instantiate the postprocessing class
//	Postprocess pp(device);
//	pp.getMaterial().MaterialType = (video::E_MATERIAL_TYPE) ppShader;
//	pp.getMaterial().setTexture(0, pp.rtt);
//	pp.getMaterial().setTexture(1, theTex);
//
//	//** End postprocessing code
//
//	MyEventReceiver receiver;
//	device->setEventReceiver(&receiver);
//	scene::ISceneManager* smgr = device->getSceneManager();
//
//	// create material
//	s32 texShader;
//	TextureShaderCallback* texcb = new TextureShaderCallback();
//
//	// create the shaders (GLSL)
//	texShader = gpu->addHighLevelShaderMaterial(
//		vs_tex, "vertexMain", video::EVST_VS_1_1,
//		ps_tex, "pixelMain", video::EPST_PS_1_1,
//		texcb, video::EMT_SOLID, 0, video::EGSL_DEFAULT);
//	if (texShader < 0)
//	{
//		std::cout << "Could not create the material shader" << std::endl;
//		return 5;
//	}
//
//	texcb->drop();
//
//	// create a test scene node with the shader material
//	scene::ISceneNode* node = smgr->addCubeSceneNode(50);
//	node->setPosition(core::vector3df(0, 0, 0));
//	node->setMaterialTexture(0, theTex);
//	node->setMaterialFlag(video::EMF_LIGHTING, false);
//	node->setMaterialType((video::E_MATERIAL_TYPE) texShader);
//
//	// rotate the cube
//	scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(
//		core::vector3df(0, 0.3f, 0));
//	node->addAnimator(anim);
//	anim->drop();
//
//	// add a camera and disable the mouse cursor
//	scene::ICameraSceneNode* cam = smgr->addCameraSceneNode();
//	cam->setPosition(core::vector3df(-100, 50, 100));
//	cam->setTarget(core::vector3df(0, 0, 0));
//	device->getCursorControl()->setVisible(false);
//
//	// draw the scene
//
//	int lastFPS = -1;
//
//	while (device->run())
//	if (device->isWindowActive())
//	{
//		if (receiver.ppEffect < 0)
//			break;  // ESC
//
//		if (receiver.ppEffect > 0)
//		{
//			// render into the texture
//			driver->beginScene(true, true, video::SColor(255, 0, 200, 0));
//			driver->setRenderTarget(pp.rtt, true, true, video::SColor(255, 230, 200, 50));
//		}
//		else
//		{
//			// render into the frame buffer
//			driver->beginScene(true, true, video::SColor(255, 230, 200, 50));
//		}
//
//		smgr->drawAll();
//
//		if (receiver.ppEffect > 0)
//		{
//			// get access to the render image and set the framebuffer as
//			// the render target
//			driver->setRenderTarget(0, true, true, video::SColor(0));
//			// and render the screen rectangle (quadrilateral) to the
//			// framebuffer
//			pp.render();
//		}
//
//		// that's all - swap buffers
//		driver->endScene();
//
//		int fps = driver->getFPS();
//		if (lastFPS != fps)
//		{
//			core::stringw str = L"Postprocessing example [OpenGL] FPS: ";
//			str += fps;
//			device->setWindowCaption(str.c_str());
//			lastFPS = fps;
//		}
//	}
//
//	std::cout << "Postprocessing example is ending" << std::endl;
//	return 0;
//}
