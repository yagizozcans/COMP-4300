//
// Created by Yağız Özcan on 13.02.2024.
//

#include "Components.h"
#include <string>
class Entity {
    bool e_isActive = true;
    std::string e_tag = "Default";
    const size_t e_id = 0;
public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CLifespan> cLifespan;
    const std::string tag() const;
    bool isActive() const;
    const void destroy();
    Entity(const std::string& tag, size_t id);

    const void set_tag(const std::string &tag);
};
