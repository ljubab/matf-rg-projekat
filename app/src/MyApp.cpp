//
// Created by ljuba on 5/16/26.
//

#include "../include/MyApp.h"

#include "MainController.h"
#include "spdlog/spdlog.h"

namespace app {
    void MyApp::app_setup() {
        spdlog::info("App setup completed!");
        auto main_controller = register_controller<app::MainController>();
        main_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
    }
} // app