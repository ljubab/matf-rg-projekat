//
// Created by ljuba on 5/16/26.
//

#include "../include/GUIController.h"

#include <engine/graphics/GraphicsController.hpp>
#include <engine/platform/PlatformController.hpp>
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace app {
    std::string_view GUIController::name() const {
        return "app::GUIController";
    }

    void GUIController::initialize() {
        set_enable(false);
        dir_light = DirectionalLight{
            glm::vec3(-0.94f, 0.5f, 0.0f),
            glm::vec3(0.3f, 0.3f, 0.3f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(0.5f, 0.5f, 0.5f)
        };
    }

    void GUIController::poll_events() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if(platform->key(engine::platform::KeyId::KEY_F2).state() == engine::platform::Key::State::JustPressed) {
            set_enable(!is_enabled());
        }
    }

    void GUIController::draw() {

    }

    void GUIController::render() {
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto camera = graphics->camera();
        graphics->begin_gui();

        ImGui::Begin("Camera info & Lightning");
        ImGui::BeginTabBar("MyTabBarID");

        if(ImGui::BeginTabItem("Lighting")) {
            ImGui::Text("Camera position: (%f, %f, %f)", camera->Position.x, camera->Position.y, camera->Position.z);
            ImGui::Text("Camera front: (%f, %f, %f)", camera->Front.x, camera->Front.y, camera->Front.z);

            glm::vec3 dir = dir_light.direction;
            if(ImGui::SliderFloat3("Direction", glm::value_ptr(dir), -10.0f, 10.0f)) {
                dir_light.direction = dir;
            }

            glm::vec3 ambient = dir_light.ambient;
            if(ImGui::SliderFloat3("Ambient", glm::value_ptr(ambient), 0.0f, 1.0f)) {
                dir_light.ambient = ambient;
            }

            glm::vec3 diffuse = dir_light.diffuse;
            if(ImGui::SliderFloat3("Diffuse", glm::value_ptr(diffuse), 0.0f, 1.0f)) {
                dir_light.diffuse = diffuse;
            }

            glm::vec3 specular = dir_light.specular;
            if(ImGui::SliderFloat3("Specular", glm::value_ptr(specular), 0.0f, 1.0f)) {
                dir_light.specular = specular;
            }

            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Postprocessing")) {
            ImGui::RadioButton("None", reinterpret_cast<int*>(&m_postprocessing_type), PostprocessingType::None);
            ImGui::RadioButton("Inversion", reinterpret_cast<int*>(&m_postprocessing_type), PostprocessingType::Inversion);
            ImGui::RadioButton("Grayscale", reinterpret_cast<int*>(&m_postprocessing_type), PostprocessingType::Grayscale);
            ImGui::RadioButton("Kernel", reinterpret_cast<int*>(&m_postprocessing_type), PostprocessingType::Kernel);
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
        ImGui::End();

        graphics->end_gui();
    }

    int GUIController::get_postprocessing() const {
        return m_postprocessing_type;
    }

} // app