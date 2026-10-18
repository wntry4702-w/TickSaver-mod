#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(TickSaverMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto menu = this->getChildByID("bottom-menu");
        if (!menu)
            return true;

        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("TickSaver"),
            this,
            menu_selector(TickSaverMenu::openTickSaver)
        );

        button->setID("ticksaver-button"_spr);
        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void openTickSaver(CCObject*) {
        FLAlertLayer::create(
            "TickSaver",
            "Playtest Analyzer: not implemented yet.\n\n"
            "Planned analysis range: +/- 4 ticks.\n"
            "Input Correction: coming later.",
            "OK"
        )->show();
    }
};
