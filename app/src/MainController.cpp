//
// Created by ljuba on 5/16/26.
//

#include "../include/MainController.h"

#include "GUIController.h"
#include "spdlog/spdlog.h"

#include <engine/core/App.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>

#include "../include/DirectionalLight.h"

namespace app {
    class MainPlatformEventObserver : public engine::platform::PlatformEventObserver {
    public:
        void on_mouse_move(engine::platform::MousePosition position) override;
    };

    void MainPlatformEventObserver::on_mouse_move(engine::platform::MousePosition position) {
        auto gui_controller = engine::core::Controller::get<GUIController>();
        if(gui_controller->is_enabled()) {
            return;
        }

        auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
        camera->rotate_camera(position.dx, position.dy);
    }

    void MainController::initialize() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        platform->register_platform_event_observer(std::make_unique<MainPlatformEventObserver>());
        engine::graphics::OpenGL::enable_depth_testing();
        engine::graphics::OpenGL::create_framebuffer(platform->window()->width(), platform->window()->height());
        spdlog::info("MainController initialized");
    }

    std::string_view MainController::name() const {
        return "app::MainController";
    }

    bool MainController::loop() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        return !platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down();
    }

    void MainController::draw_shiba() {
        // Model
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto gui_controller = engine::core::Controller::get<GUIController>();

        engine::resources::Model * shiba = resources->model("shiba");
        // Shader
        engine::resources::Shader * shader = resources->shader(lighting_enabled ? "lighting" : "basic");

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        DirectionalLight dir_light = gui_controller->dir_light;

        shader->set_vec3("viewPos", graphics->camera()->Position);
        dir_light.apply(shader);
        shader->set_float("material.ambient", 0.3f);
        shader->set_float("material.diffuse", 1.0f);
        shader->set_float("material.specular", 0.5f);
        shader->set_float("material.shiness", 32.0f);

        spotlight.apply(shader);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.5, 0.31, -1.0));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        model = glm::rotate(model, shiba_rotation_angle, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.3f));
        shader->set_mat4("model", model);

        shiba->draw(shader);
    }

    void MainController::draw_house() {
        // Model
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto gui_controller = engine::core::Controller::get<GUIController>();

        engine::resources::Model * house = resources->model("house");
        // Shader
        engine::resources::Shader * shader = resources->shader(lighting_enabled ? "lighting" : "basic");

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        DirectionalLight dir_light = gui_controller->dir_light;

        shader->set_vec3("viewPos", graphics->camera()->Position);
        dir_light.apply(shader);
        shader->set_float("material.ambient", 0.3f);
        shader->set_float("material.diffuse", 1.0f);
        shader->set_float("material.specular", 0.5f);
        shader->set_float("material.shiness", 32.0f);

        spotlight.apply(shader);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.0, 0.0, 0.0));
        model = glm::scale(model, glm::vec3(0.3f));
        shader->set_mat4("model", model);

        house->draw(shader);
    }

    void MainController::draw_rick() {
        // Model
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto gui_controller = engine::core::Controller::get<GUIController>();

        engine::resources::Model * rick = resources->model("rick");
        // Shader
        engine::resources::Shader * shader = resources->shader(lighting_enabled ? "lighting" : "basic");

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        DirectionalLight dir_light = gui_controller->dir_light;

        shader->set_vec3("viewPos", graphics->camera()->Position);
        dir_light.apply(shader);
        shader->set_float("material.ambient", 0.3f);
        shader->set_float("material.diffuse", 1.0f);
        shader->set_float("material.specular", 0.5f);
        shader->set_float("material.shiness", 32.0f);

        spotlight.apply(shader);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0, 0.0, 0.0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f));
        shader->set_mat4("model", model);

        rick->draw(shader);
    }

    void MainController::draw_griffin() {
        // Model
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto gui_controller = engine::core::Controller::get<GUIController>();

        engine::resources::Model * griffin = resources->model("griffin");
        // Shader
        engine::resources::Shader * shader = resources->shader(lighting_enabled ? "lighting" : "basic");

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        DirectionalLight dir_light = gui_controller->dir_light;

        shader->set_vec3("viewPos", graphics->camera()->Position);
        dir_light.apply(shader);
        shader->set_float("material.ambient", 0.3f);
        shader->set_float("material.diffuse", 1.0f);
        shader->set_float("material.specular", 0.5f);
        shader->set_float("material.shiness", 32.0f);

        spotlight.apply(shader);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0, 0.0, 1.0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        shader->set_mat4("model", model);

        griffin->draw(shader);
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
        engine::graphics::OpenGL::bind_framebuffer();
    }

    void MainController::draw_skybox() {
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto skybox = resources->skybox("anime_skybox");
        auto shader = resources->shader("skybox");
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        graphics->draw_skybox(shader, skybox);
    }

    void MainController::draw() {
        // clear buffers (color buffer, depth buffer)
        draw_skybox();
        draw_shiba();
        draw_house();
        draw_rick();
        draw_griffin();
        // swapBuffers
    }

    void MainController::end_draw() {
        engine::graphics::OpenGL::unbind_framebuffer();

        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        engine::resources::Shader * postprocessing = resources->shader("postprocessing");
        postprocessing->use();
        postprocessing->set_int("screenTexture", 0);

        auto gui_controller = engine::core::Controller::get<GUIController>();
        postprocessing->set_int("postprocessingType", gui_controller->get_postprocessing());

        engine::graphics::OpenGL::draw_framebuffer();

        if(gui_controller->is_enabled()) {
            gui_controller->render();
        }

        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        platform->swap_buffers();
    }

    void MainController::update_camera() {
        auto gui_controller = engine::core::Controller::get<GUIController>();
        if(gui_controller->is_enabled()) {
            return;
        }

        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto camera = graphics->camera();
        float dt = platform->dt();

        if(platform->key(engine::platform::KeyId::KEY_W).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
        }
        if(platform->key(engine::platform::KeyId::KEY_S).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
        }
        if(platform->key(engine::platform::KeyId::KEY_A).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
        }
        if(platform->key(engine::platform::KeyId::KEY_D).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt);
        }
    }

    void MainController::update_spotlight() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto camera = graphics->camera();

        if(platform->key(engine::platform::KeyId::KEY_F).state() == engine::platform::Key::State::JustPressed) {
            spotlight.toggle();
        }

        spotlight.position = camera->Position;
        spotlight.direction = glm::normalize(camera->Front);
    }

    void MainController::update_shiba() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

        if(platform->key(engine::platform::KeyId::KEY_R).state() == engine::platform::Key::State::JustPressed) {
            shiba_rotating ^= 1;
        }

        if(shiba_rotating) {
            shiba_rotation_angle += platform->dt();
        }
    }

    void MainController::update_lighting() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

        if(platform->key(engine::platform::KeyId::KEY_Q).state() == engine::platform::Key::State::JustPressed) {
            lighting_enabled ^= 1;
        }
    }

    void MainController::update() {
        update_camera();
        update_spotlight();
        update_shiba();
        update_lighting();
    }

} // app