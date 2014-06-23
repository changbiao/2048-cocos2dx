#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

    bool doUp();
    bool doDown();
    bool doLeft();
    bool doRight();

    void autoCreateCardNumber();
    void createCardSprite(cocos2d::Size size);
    void doCheckGameOver();

    //游戏总分
    int score;

    //定义显示分数的控件
    cocos2d::LabelTTF* labelTTFCardNumber;

private:
    int firstX, firstY, endX, endY;
    CardSprite* cards[4][4];
};

#endif // __HELLOWORLD_SCENE_H__
