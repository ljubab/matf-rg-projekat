//
// Created by ljuba on 5/16/26.
//

#include "../include/MainController.h"

#include "spdlog/spdlog.h"

namespace app {
    void MainController::initialize() {
        spdlog::info("MainController initialized");
    }

    std::string_view MainController::name() const {
        return "app::MainController";
    }
} // app