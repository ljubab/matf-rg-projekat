//
// Created by ljuba on 5/16/26.
//

#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H
#include <engine/core/Controller.hpp>

namespace app {

class GUIController : public engine::core::Controller {
    void initialize() override;

public:
    std::string_view name() const override;

private:
    void draw() override;
    void poll_events() override;
};

} // app

#endif //GUICONTROLLER_H
