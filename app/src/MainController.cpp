//
// Created by ljuba on 5/16/26.
//

#include "../include/MainController.h"

#include "spdlog/spdlog.h"

#include <engine/platform/PlatformController.hpp>

namespace app {
    void MainController::initialize() {
        spdlog::info("MainController initialized");
    }

    std::string_view MainController::name() const {
        return "app::MainController";
    }

    bool MainController::loop() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        return !platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down();
    }
} // app