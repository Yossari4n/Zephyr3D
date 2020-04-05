#ifndef Model_h
#define Model_h

#include "Mesh.h"
#include "../../resources/RawModel/RawModel.h"

#include <vector>

namespace zephyr::rendering {

class Model {
public:
    explicit Model(const RawModel& raw_model);

    Model() = delete;
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    Model(Model&&) = default;
    Model& operator=(Model&&) = default;
    ~Model() = default;

    const std::vector<Mesh>& Meshes() const { return m_Meshes; }

private:
    std::vector<Mesh> m_Meshes;
};

}

#endif
