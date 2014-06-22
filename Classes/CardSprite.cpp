//
// Created by Allen LSY on 22/6/14.
//

#include "CardSprite.h"

CardSprite *CardSprite::createCardSprite(int numbers, int width, int height, float CardSpriteX, float CardSpriteY) {
    CardSprite*enemy = new CardSprite();
    if (enemy && enemy->init()) {
        enemy->enemyInit(numbers, width, height, CardSpriteX, CardSpriteY);

        return enemy;

    }

    CC_SAFE_DELETE(enemy); // MYNOTE: CC_SAFE_DELETE: do { delete (p); (p) = nullptr; } while(0)
    return NULL;
}

bool CardSprite::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}


void CardSprite::enemyInit(int numbers, int width, int height, float CardSpriteX, float CardSpriteY) {
    _number = numbers;

    //加入游戏的背景颜色
    layerColorBG = LayerColor::create(Color4B(200, 190, 180, 255), width - 15, height - 15);
    layerColorBG->setPosition(CardSpriteX, CardSpriteY);

    //判断如果大于0就显示，否则显示空
    if (numbers > 0)
    {
        //加入中间字体
        labelCardNumber = Label::create(String::createWithFormat("%i", numbers)->getCString(), "HiraKakuProN-W6", 100);
        labelCardNumber->setPosition(layerColorBG->getContentSize().width/2, layerColorBG->getContentSize().height/2);
        labelCardNumber->setTag(8);
        layerColorBG->addChild(labelCardNumber);
    } else {
        labelCardNumber = Label::create("", "HiraKakuProN-W6", 100);
        labelCardNumber->setPosition(layerColorBG->getContentSize().width/2, layerColorBG->getContentSize().height/2);
        labelCardNumber->setTag(8);
        layerColorBG->addChild(labelCardNumber);
    }

    this->addChild(layerColorBG);
}

int CardSprite::getNumber() {
    return _number;
}

void CardSprite::setNumber(int num) {
    _number = num;

    if (_number > 0) {
        labelCardNumber->setString(String::createWithFormat("%i", _number)->getCString());
    } else {
        labelCardNumber->setString("");
    }
}
