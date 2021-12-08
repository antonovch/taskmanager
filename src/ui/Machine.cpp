//
// Created by Anton O. on 11/26/21.
//

#include "Machine.h"

Machine::Machine() {
    context_.setStep(factory_->getStep(Factory::State::HOME));
}

Machine::Machine(const Factory::State &s) {
    context_.setStep(factory_->getStep(s));
}

Machine::Machine(const std::shared_ptr<Factory> &f, const Factory::State &s) : factory_(f) {
    context_.setStep(factory_->getStep(s));
}

Context Machine::run() {

    while (context_.getStep()){
        auto act = context_.getStep()->execute(context_);
        if (act) {
            controller_.Accept(model_, context_, act);
            context_.getOldStep()->process(context_);
        }
    }
    return context_;
}

TaskManager Machine::model() const {
    return model_;
}