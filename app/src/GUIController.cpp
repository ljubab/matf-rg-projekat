//
// Created by ljuba on 5/16/26.
//

#include "../include/GUIController.h"

#include <engine/graphics/GraphicsController.hpp>
#include <engine/platform/PlatformController.hpp>
#include <imgui.h>

namespace app {
    std::string_view GUIController::name() const {
        return "app::GUIController";
    }

    void GUIController::initialize() {
        set_enable(false);
    }

    void GUIController::poll_events() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if(platform->key(engine::platform::KeyId::KEY_F2).state() == engine::platform::Key::State::JustPressed) {
            set_enable(!is_enabled());
        }
    }


    void GUIController::draw() {
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto camera = graphics->camera();
        graphics->begin_gui();

        ImGui::Begin("Camera info");
        ImGui::Text("Camera position: (%f, %f, %f)", camera->Position.x, camera->Position.y, camera->Position.z);

        ImGui::End();

        graphics->end_gui();
    }
} // app