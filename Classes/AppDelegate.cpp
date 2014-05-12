#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

#define FPS		30

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void setupResolutionPolicy(float designW, float designH)
{
	GLView *view = Director::getInstance()->getOpenGLView();
	Size screenSize = view->getFrameSize();
    
	float designRatio = designW / designH;
	float screenRatio = screenSize.height / screenSize.width;
	
	ResolutionPolicy resolutionPolicy = screenRatio < designRatio ?
	ResolutionPolicy::FIXED_HEIGHT : ResolutionPolicy::FIXED_WIDTH;
	
    view->setDesignResolutionSize(designW, designH, resolutionPolicy);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

	// Setting the Resolution Policy
	setupResolutionPolicy(480, 320);
	
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / FPS);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
