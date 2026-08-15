//
// Created by ljuba on 5/16/26.
//

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <engine/core/Controller.hpp>

#include "DirectionalLight.h"
#include "SpotLight.h"

namespace app {

class MainController : public engine::core::Controller {
public:
    std::string_view name() const override;

private:
    bool shiba_rotating = true;
    float shiba_rotation_angle = 0.0f;
    bool lighting_enabled = true;

    SpotLight spotlight;

    void initialize() override;
    bool loop() override;
    void draw() override;
    void draw_backpack();
    void draw_shiba();
    void begin_draw() override;
    void end_draw() override;
    void update_camera();
    void draw_skybox();
    void draw_house();
    void draw_rick();
    void draw_griffin();
    void update() override;
    void update_spotlight();
    void update_shiba();
    void update_lighting();
};

}// namespace app

#endif//MAINCONTROLLER_H
