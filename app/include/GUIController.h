//
// Created by ljuba on 5/16/26.
//

#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H
#include "DirectionalLight.h"
#include <engine/core/Controller.hpp>

namespace app {
enum PostprocessingType {
    None = 0,
    Inversion = 1,
    Grayscale = 2,
    Kernel = 3
};
class GUIController : public engine::core::Controller {
    void initialize() override;

public:
    std::string_view name() const override;
    DirectionalLight dir_light;

    int get_postprocessing() const;
    void render();

private:
    void draw() override;
    void poll_events() override;

    PostprocessingType m_postprocessing_type = None;
};

}// namespace app

#endif//GUICONTROLLER_H
