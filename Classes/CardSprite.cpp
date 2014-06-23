#import "CCPlatformMacros.h"//
// Created by Allen LSY on 22/6/14.
//

#include "CardSprite.h"

USING_NS_CC;

CardSprite *CardSprite::createCardSprite(int numbers, int width, int height, float CardSpriteX, float CardSpriteY) {
    log("numbers %d, width %d, height %d, x %f, y %f", numbers, width, height, CardSpriteX, CardSpriteY);
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
    log("enemyInit() called " + numbers);

    _number = numbers;

    //加入游戏的背景颜色
    auto layerColorBG = LayerColor::create(Color4B(200, 190, 180, 255), width - 15, height - 15);
    layerColorBG->setPosition(CardSpriteX, CardSpriteY);
    log("layerColorBG: %d", layerColorBG);

    //判断如果大于0就显示，否则显示空
    if (numbers > 0)
    {
        log("called this");
        //加入中间字体
        labelCardNumber = LabelTTF::create(String::createWithFormat("%i", numbers)->getCString(), "HiraKakuProN-W6", 100);
        labelCardNumber->setPosition(layerColorBG->getContentSize().width/2, layerColorBG->getContentSize().height/2);
        labelCardNumber->setTag(8);
        log("labelCardNumber: %p", labelCardNumber);
        layerColorBG->addChild(labelCardNumber);
    } else {
        log("called that");
        labelCardNumber = LabelTTF::create("", "HiraKakuProN-W6", 100);
        labelCardNumber->setPosition(layerColorBG->getContentSize().width/2, layerColorBG->getContentSize().height/2);
        labelCardNumber->setTag(8);
        log("labelCardNumber: %p", labelCardNumber);
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
