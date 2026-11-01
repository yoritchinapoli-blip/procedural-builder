#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <fstream>
#include <sstream>

using namespace geode::prelude;

class $modify(MyEditorLayer, LevelEditorLayer) {
    bool init(GJGameLevel* level) {
        if (!LevelEditorLayer::init(level)) return false;

        auto menu = this->getChildByID("editor-button-menu");
        if (menu) {
            auto spr = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");
            spr->setScale(0.4f);

            auto btn = CCMenuItemSpriteExtra::create(
                spr,
                this,
                menu_selector(MyEditorLayer::onProceduralImport)
            );
            btn->setID("procedural-builder-btn");

            menu->addChild(btn);
            menu->updateLayout();
        }

        return true;
    }

    void onProceduralImport(CCObject*) {
        std::ifstream file("/sdcard/Download/level_data.txt");
        if (!file.is_open()) {
            FLAlertLayer::create("Error", "Could not find level_data.txt in Downloads!", "OK")->show();
            return;
        }

        std::string levelString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        if (levelString.empty()) {
            FLAlertLayer::create("Error", "Level data file is empty!", "OK")->show();
            return;
        }

        this->createObjectsFromString(levelString);
        FLAlertLayer::create("Success!", "Procedural objects spawned successfully!", "OK")->show();
    }
};
