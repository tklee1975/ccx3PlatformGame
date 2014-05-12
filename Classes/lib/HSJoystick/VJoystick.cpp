//
//  HSJoystick.cpp
//  CocosTest
//
//  Created by Ken Lee on 1/3/14.
//
//

#include "VJoystick.h"

#define JOYSTICK_OFFSET_X 5.0f
#define JOYSTICK_OFFSET_Y 5.0f

#define JOYSTICK_RADIUS 30.0f

#define THUMB_RADIUS 15.0f


VJoystick::VJoystick()
: mThumb(NULL)
{
	
}

bool VJoystick::init(Sprite *spriteThumb, Sprite *spriteBg)
{
	
	if(Layer::init() == false) {
		return false;
	}
	
	// Adding the background
	if(spriteBg == NULL) {
		float size = JOYSTICK_RADIUS*2;
		LayerColor *layer = LayerColor::create(Color4B(100, 100, 100, 100), size, size);
		layer->setPosition(Point(-size/2, -size/2));
		addChild(layer);
	} else {
		
	}
	
	// Adding the thumb
	if(spriteThumb == NULL) {
		float size = THUMB_RADIUS*2;
		LayerColor *layer = LayerColor::create(Color4B(100, 100, 255, 100), size, size);
		layer->setAnchorPoint(Point(0, 0));
		addChild(layer);
		mThumb = layer;
	} else {
		addChild(spriteThumb);
		mThumb = spriteThumb;
	}

	setThumbPos(Point(0, 0));
//	addChild(sprite);
//	mThumb = sprite;
	
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);	// ???
	
	return true;
}


VJoystick::~VJoystick()
{
	
}



void VJoystick::setThumbPos(Point pos)
{
	Point anchorPoint = mThumb->getAnchorPoint();
	float size = THUMB_RADIUS;
	float offsetX = size * 2 * (anchorPoint.x - 0.5);
	float offsetY = size * 2 * (anchorPoint.y - 0.5);
	
	mThumb->setPosition(Point(pos.x + offsetX, pos.y + offsetY));
}

void VJoystick::updateVelocity(Point point)
{
	// calculate Angle and length
    float dx = point.x;
    float dy = point.y;
	
    float distance = sqrt(dx*dx + dy*dy);
    float angle = atan2(dy,dx); // in radians
	
    if(distance > JOYSTICK_RADIUS){
        dx = cos(angle) * JOYSTICK_RADIUS;
        dy = sin(angle) * JOYSTICK_RADIUS;
    }
	
    mVelocity = Point(dx/JOYSTICK_RADIUS, dy/JOYSTICK_RADIUS);
	
	
    if(distance>JOYSTICK_RADIUS)
    {
        point.x = cos(angle) * JOYSTICK_RADIUS;
        point.y = sin(angle) * JOYSTICK_RADIUS;
    }
	
	//log("dx=%f dy=%f point.x=%f point.y=%f", dx, dy, point.x, point.y);
	
	setThumbPos(point);
}

bool VJoystick::onTouchBegan(Touch *touch, Event *event)
{
	Point posGL = touch->getLocation();			// from bottom
	Point nodeLoc = convertToNodeSpace(posGL);
	
	mIsPressed = true;
	
	log("posGL=%f,%f nodeLoc=%f,%f", posGL.x, posGL.y, nodeLoc.x, nodeLoc.y);
	
	updateVelocity(nodeLoc);
//	CCTouch *touch = (CCTouch*)pTouches->anyObject();
//    CCPoint point = touch->locationInView(touch->view());
//    point = convertCoordinate(point);
//	
//    if(isPointInCircle(point,kCenter,JOYSTICK_RADIUS)){
//        isPressed = true;
//        this->updateVelocity(point);
//    }
	
	return true;
}

void VJoystick::resetJoystick()
{
    this->updateVelocity(Point(0, 0));
}

bool VJoystick::handleLastTouch()
{
    bool wasPressed = mIsPressed;
    if(wasPressed){
        this->resetJoystick();
        mIsPressed = false;
    }
    return (wasPressed ? true : false);
}

Point VJoystick::getVelocity()
{
	return mVelocity;
}

void VJoystick::onTouchMoved(Touch *touch, Event *event)
{
	if(mIsPressed){
		Point posGL = touch->getLocation();			// from bottom
		Point nodeLoc = convertToNodeSpace(posGL);
		updateVelocity(nodeLoc);
    }
	return;
}

void VJoystick::onTouchEnded(Touch *touch, Event *event)
{
	handleLastTouch();
	return;
}

void VJoystick::onTouchCancelled(Touch *touch, Event *event)
{
	handleLastTouch();
	return;
}