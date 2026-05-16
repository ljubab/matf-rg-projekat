//
// Created by ljuba on 5/16/26.
//

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <engine/core/Controller.hpp>

namespace app {

class MainController : public engine::core::Controller {
public:
    std::string_view name() const override;

private:
    void initialize() override;
    bool loop() override;
    void draw() override;
    void draw_backpack();
    void begin_draw() override;
    void end_draw() override;
};

} // app

#endif //MAINCONTROLLER_H
