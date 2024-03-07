//
// Created by jpnsantos on 06/03/24.
//

#include "Node.h"

int Node::getId() const {
    return this->id;
}

const string &Node::getCode() const {
    return this->code;
}

void Node::setId(int id) {
    this->id = id;
}

void Node::setCode(const std::string &code) {
    this->code = code;
}