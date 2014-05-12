//
//  HSJoystick.h
//  CocosTest
//
//	http://www.cocos2d-x.org/forums/6/topics/2438
//
//  Created by Ken Lee on 1/3/14.
//
//

#ifndef __CocosTest__HSJoystick__
#define __CocosTest__HSJoystick__

#include <iostream>


#include "cocos2d.h"

using namespace cocos2d;

class VJoystick : public Layer
{
	
public:
	VJoystick();
	virtual ~VJoystick();
	
    virtual bool init(Sprite *spriteThumb, Sprite *spriteBg);
	Point getVelocity();
    
	
private:
	
    Point mPointCenter;
    Node *mThumb;
    bool mIsPressed;
	
    Point mVelocity;
	
    void updateVelocity(Point point);
    void resetJoystick();
    bool handleLastTouch();
	void setThumbPos(Point pos);
	
	virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    virtual void onTouchCancelled(Touch *touch, Event *event);
};
#endif /* defined(__CocosTest__HSJoystick__) */
