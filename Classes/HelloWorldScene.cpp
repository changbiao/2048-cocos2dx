#include "HelloWorldScene.h"
#include "CardSprite.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this); // MYNOTE: CC_CALLBACK_2: #define CC_CALLBACK_2	(	 	__selector__, __target__, ... )
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

    return true;

}

//事件监听回调：触摸开始
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event) {
    Vec2 touchPoint = touch->getLocation(); //获取OpenGL坐标（即cocos2d-x坐标，原点在左下角）
    touch->getLocationInView(); // MYNOTE: getLocationInView()
    firstX = touchPoint.x;
    firstY = touchPoint.y;
    return true;
}

//事件监听回调：触摸结束
void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event) {
    Vec2 touchPoint = touch->getLocation();
    endX = firstX - touchPoint.x;
    endY = firstY - touchPoint.y;

    log("endX: %d", abs(endX));
    log("endY: %d", abs(endY));
    if (abs(endX) >abs(endY)) {
        if (endX + 5 > 0) {
            doLeft();
        }
        else
        {
            doRight();
        }
    } else {
        if (endY +5 > 0) {
            doDown();
        }    else {
            doUp();
        }
    }
}


bool HelloWorld::doUp() {
    log("doUp");
    return true;
}

bool HelloWorld::doDown() {
    log("doDown");
    return true;
}

bool HelloWorld::doLeft() {
    log("doLeft");
    return true;
}

bool HelloWorld::doRight() {
    log("doRight");
    return true;
}
