//
// Created by ljuba on 5/16/26.
//

#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H
#include <engine/core/Controller.hpp>
#include "DirectionalLight.h"
#include <../../engine/libs/glm/glm/glm.hpp>

namespace app {

class GUIController : public engine::core::Controller {
    void initialize() override;

public:
    std::string_view name() const override;
    DirectionalLight dir_light;

private:
    void draw() override;
    void poll_events() override;
};

} // app

#endif //GUICONTROLLER_H
