
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
        auto range = Mod::get()->getSettingValue<int64_t>("analysis-range");

        auto message = fmt::format(
            "Playtest Analyzer: not implemented yet.\n\n"
            "Current analysis range: +/- {} ticks.\n"
            "Input Correction: coming later.",
            range
        );

        FLAlertLayer::create(
            "TickSaver",
            message,
            "OK"
        )->show();
    }
};
