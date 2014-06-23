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

    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this); // MYNOTE: CC_CALLBACK_2: #define CC_CALLBACK_2	(	 	__selector__, __target__, ... )
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

    //加入游戏的背景颜色
    auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(180,170,160,255));
    this->addChild(layerColorBG);

    createCardSprite(visibleSize);

    //创建2张自动生成卡片
    autoCreateCardNumber();
    autoCreateCardNumber();

    return true;

}

//事件监听回调：触摸开始
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    Vec2 touchPoint = touch->getLocation(); //获取OpenGL坐标（即cocos2d-x坐标，原点在左下角）
    touch->getLocationInView(); // MYNOTE: getLocationInView()
    firstX = (int) touchPoint.x;
    firstY = (int) touchPoint.y;
    return true;
}

//事件监听回调：触摸结束
void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event) {
    Vec2 touchPoint = touch->getLocation();
    endX = firstX - touchPoint.x;
    endY = firstY - touchPoint.y;

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

    doCheckGameOver();
//    autoCreateCardNumber();
}


bool HelloWorld::doUp() {
    log("doUp");
    bool isdo = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 3; y >= 0; y--) {

            for (int y1 = y - 1; y1 >= 0; y1--) {
                if (cards[x][y1]->getNumber() > 0) {
                    if (cards[x][y]->getNumber() <= 0) {
                        cards[x][y]->setNumber(cards[x][y1]->getNumber());
                        cards[x][y1]->setNumber(0);

                        y++;
                        isdo = true;
                    }else if(cards[x][y]->getNumber() == cards[x][y1]->getNumber()){
                        cards[x][y]->setNumber(cards[x][y]->getNumber()*2);
                        cards[x][y1]->setNumber(0);

                        isdo = true;
                    }
                    break;
                }
            }

        }
    }
    return isdo;
}

bool HelloWorld::doDown() {
    log("doDown");
    bool isdo = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {

            for (int y1 = y + 1; y1 < 4; y1++) {
                if (cards[x][y1]->getNumber() > 0) {
                    if (cards[x][y]->getNumber() <= 0) {
                        cards[x][y]->setNumber(cards[x][y1]->getNumber());
                        cards[x][y1]->setNumber(0);

                        y--;
                        isdo = true;
                    }else if(cards[x][y]->getNumber() == cards[x][y1]->getNumber()){
                        cards[x][y]->setNumber(cards[x][y]->getNumber()*2);
                        cards[x][y1]->setNumber(0);

                        isdo = true;
                    }
                    break;
                }
            }

        }
    }
    return isdo;
}

bool HelloWorld::doLeft() {
    log("doLeft");

    bool isDo = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            // 如果右边的数等于左边的数，那么左边的数乘以2，然后把右边的数设置为0，也就变为了空。
            for (int x1 = x + 1; x1 < 4; x1++) {
                if (cards[x1][y]->getNumber() > 0) {
                    if (cards[x][y]->getNumber() <= 0) {
                        cards[x][y]->setNumber(cards[x1][y]->getNumber());
                        cards[x1][y]->setNumber(0);

                        x--;
                        isDo = true;
                    }else if(cards[x][y]->getNumber() == cards[x1][y]->getNumber()){
                        cards[x][y]->setNumber(cards[x][y]->getNumber()*2);
                        cards[x1][y]->setNumber(0);

                        isDo = true;
                    }
                    break;
                }
            }
        }
    }
    return isDo;
}

bool HelloWorld::doRight() {
    log("doRight");
    bool isdo = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 3; x >= 0; x--) {

            for (int x1 = x - 1; x1 >= 0; x1--) {
                if (cards[x1][y]->getNumber() > 0) {
                    if (cards[x][y]->getNumber() <= 0) {
                        cards[x][y]->setNumber(cards[x1][y]->getNumber());
                        cards[x1][y]->setNumber(0);

                        x++;
                        isdo = true;
                    }else if(cards[x][y]->getNumber() == cards[x1][y]->getNumber()){
                        cards[x][y]->setNumber(cards[x][y]->getNumber()*2);
                        cards[x1][y]->setNumber(0);

                        isdo = true;
                    }
                    break;
                }
            }

        }
    }
    return isdo;
}

//创建卡片
void HelloWorld::createCardSprite(cocos2d::Size size)
{
    //求出单元格的宽度和高度
    int unitSize = (size.height-28)/4;

    //4*4的单元格
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            CardSprite* card = CardSprite::createCardSprite(0, unitSize, unitSize, unitSize*i+140, unitSize*j+20);
            cards[i][j] = card;
            addChild(card);
        }
    }
}

//自动生成卡片
void HelloWorld::autoCreateCardNumber()
{

    int i = CCRANDOM_0_1()*4;
    int j = CCRANDOM_0_1()*4;

    //判断是否这个位置已存在卡片
    if(cards[i][j]->getNumber() > 0)
    {
        log("(%d,%d): exist", i, j);
        // autoCreateCardNumber();
    }
    else
    {
        cards[i][j]->setNumber(CCRANDOM_0_1()*10 < 1 ? 2: 4);
        log("(%d,%d): %d", i, j, cards[i][j]);
    }
}

//判断游戏是否还能继续
void HelloWorld::doCheckGameOver(){
    bool isGameOver = true;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (cards[x][y]->getNumber() == 0||
                    (x>0&&(cards[x][y]->getNumber() == cards[x-1][y]->getNumber()))||
                    (x<3&&(cards[x][y]->getNumber() == cards[x+1][y]->getNumber()))||
                    (y>0&&(cards[x][y]->getNumber() == cards[x][y-1]->getNumber()))||
                    (y<3&&(cards[x][y]->getNumber() == cards[x][y+1]->getNumber()))) {
                isGameOver = false;
            }
        }
    }

    if (isGameOver) {
        //游戏结束，重新开始游戏
        log("游戏结束");
        Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
    } else {
        autoCreateCardNumber();
    }
}