#include "cocos2d.h"

#ifndef __CardSprite_H_
#define __CardSprite_H_


class CardSprite : public cocos2d::Sprite {
public:
    static CardSprite* createCardSprite(int numbers, int width, int height, float CardSpriteX, float CardSpriteY);
    virtual bool init();

    CREATE_FUNC(CardSprite); //MYNOTE: CREATE_FUNC:  define a create function for a specific type, such as Layer

    int getNumber();
    void setNumber(int num);

private:
    int _number;
    void enemyInit(int numbers, int width, int height, float CardSpriteX, float CardSpriteY);

    cocos2d::LabelTTF* labelCardNumber;

    cocos2d::LayerColor* layerColorBG;

};

#endif //__CardSprite_H_
