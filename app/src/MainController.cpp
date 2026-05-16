//
// Created by ljuba on 5/16/26.
//

#include "../include/MainController.h"

#include "spdlog/spdlog.h"

#include <engine/graphics/GraphicsController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>

namespace app {
    void MainController::initialize() {
        spdlog::info("MainController initialized");
        engine::graphics::OpenGL::enable_depth_testing();
    }

    std::string_view MainController::name() const {
        return "app::MainController";
    }

    bool MainController::loop() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        return !platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down();
    }

    void MainController::draw_backpack() {
        // Model
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        engine::resources::Model * backpack = resources->model("backpack");
        // Shader
        engine::resources::Shader * shader = resources->shader("basic");

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0, 0.0, -3.0));
        model = glm::scale(model, glm::vec3(0.3f));
        shader->set_mat4("model", model);

        backpack->draw(shader);
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }


    void MainController::draw() {
        // clear buffers (color buffer, depth buffer)
        draw_backpack();
        // swapBuffers
    }

    void MainController::end_draw() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        platform->swap_buffers();
    }

} // app