//
// Created by ljuba on 5/16/26.
//

#include "../include/MyApp.h"

#include "spdlog/spdlog.h"

namespace app {
    void MyApp::app_setup() {
        spdlog::info("App setup completed!");
    }
} // app