//
// Created by ljuba on 5/16/26.
//

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <engine/core/Controller.hpp>

namespace app {

class MainController : public engine::core::Controller {
    void initialize() override;

public:
    std::string_view name() const override;

private:
    bool loop() override;
};

} // app

#endif //MAINCONTROLLER_H
