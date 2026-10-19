
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

#include <array>
#include <cstddef>

using namespace geode::prelude;

namespace TickSaver {
    struct InputEvent {
        float attemptTime;
        int button;
        bool down;
        bool player1;
    };

    constexpr std::size_t MAX_EVENTS = 256;

    static std::array<InputEvent, MAX_EVENTS> events{};
    static std::size_t eventCount = 0;
    static float lastAttemptTime = 0.f;
    static bool playerDead = false;
    static unsigned int timeUpdateCount = 0;

    static void clearAttempt() {
        eventCount = 0;
        lastAttemptTime = 0.f;
        playerDead = false;
        timeUpdateCount = 0;

        log::info("[TickSaver] Attempt data cleared");
    }

    static void recordInput(bool down, int button, bool player1) {
        if (playerDead || eventCount >= MAX_EVENTS)
            return;

        events[eventCount++] = {
            lastAttemptTime,
            button,
            down,
            player1
        };

        log::info(
            "[TickSaver] Input #{}: time={:.4f}, button={}, down={}, player1={}",
            eventCount,
            lastAttemptTime,
            button,
            down,
            player1
        );
    }
}

class $modify(TickSaverPlayLayer, PlayLayer) {
    void updateAttemptTime(float attemptTime) {
        TickSaver::lastAttemptTime = attemptTime;
        ++TickSaver::timeUpdateCount;

        if (TickSaver::timeUpdateCount <= 5) {
            log::info(
                "[TickSaver] Time update #{}: {:.4f}",
                TickSaver::timeUpdateCount,
                attemptTime
            );
        }

        PlayLayer::updateAttemptTime(attemptTime);
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        TickSaver::playerDead = true;
        PlayLayer::destroyPlayer(player, object);
    }

    void resetLevel() {
        TickSaver::clearAttempt();
        PlayLayer::resetLevel();
    }
};

class $modify(TickSaverGameLayer, GJBaseGameLayer) {
    void handleButton(bool down, int button, bool isPlayer1) {
        auto layer = PlayLayer::get();

        if (layer &&
            static_cast<GJBaseGameLayer*>(layer) ==
                static_cast<GJBaseGameLayer*>(this) &&
            !layer->m_isPlatformer) {
            TickSaver::recordInput(down, button, isPlayer1);
        }

        GJBaseGameLayer::handleButton(down, button, isPlayer1);
    }
};
