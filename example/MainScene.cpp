#include "MainScene.h"

#include <Zephyr3D/Engine.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void MainScene::CreateScene() {
    FrameRateLimit(60);
    Skybox(LoadTexture("../../assets/skyboxes/basic_blue/right.png"),
           LoadTexture("../../assets/skyboxes/basic_blue/left.png"),
           LoadTexture("../../assets/skyboxes/basic_blue/top.png"),
           LoadTexture("../../assets/skyboxes/basic_blue/bottom.png"),
           LoadTexture("../../assets/skyboxes/basic_blue/back.png"),
           LoadTexture("../../assets/skyboxes/basic_blue/front.png"));

    auto light = CreateObject("Light"); {
        light->CreateComponent<DirectionalLight>(glm::vec3(-1.0f, -0.5f, -0.5f),
                                                 glm::vec3(0.05f),
                                                 glm::vec3(0.7f, 0.68f, 0.68f),
                                                 glm::vec3(0.8f, 0.78f, 0.78f));
    }

    auto camera = CreateObject("Camera"); {
        camera->Root().Move(glm::vec3(-10.0f, 4.0f, -2.0f));
        camera->Root().Rotate(glm::vec3(0.0f, 0.0f, glm::radians(-25.0f)));
        camera->Root().Rotate(glm::vec3(0.0f, glm::radians(-20.0f), 0.0f));

        auto comp = camera->CreateComponent<Camera>(glm::radians(45.0f), 
                                                    static_cast<float>(zephyr::Engine::Instance().GetWindow().Width()) / static_cast<float>(zephyr::Engine::Instance().GetWindow().Height()),
                                                    0.1f, 
                                                    500.0f);
        camera->Connect(camera->Root().This, comp->TransformIn);

        auto fpc = camera->CreateComponent<FirstPersonController>();
        camera->Connect(camera->Root().This, fpc->TransformIn);
    }

    for (auto i = 0; i < 3; i++) {
        for (auto j = 0; j < 3; j++) {
            for (auto k = 0; k < 3; k++) {
                auto cube = CreateObject("Cube"); {
                    cube->Root().Position(glm::vec3(i, j, k));

                    auto comp = cube->CreateComponent<Cube>(glm::vec3((float)i / 5.0f, (float)j / 5.0f, (float)k / 5.0f));
                    cube->Connect(cube->Root().This, comp->TransformIn);

                    auto rb = cube->CreateComponent<RigidBody>(10.0f, new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));
                    cube->Connect(cube->Root().This, rb->TransformIn);
                }
            }
        }
    }

    auto ground = CreateObject("Ground"); {
        ground->Root().Position(glm::vec3(0.0f, -5.0f, 0.0f));
        ground->Root().Scale(glm::vec3(20.0f, 1.0f, 20.0f));

        auto cube = ground->CreateComponent<Cube>(glm::vec3(1.0f));
        ground->Connect(ground->Root().This, cube->TransformIn);

        auto rb = ground->CreateComponent<RigidBody>(0, new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));
        ground->Connect(ground->Root().This, rb->TransformIn);
    }

    auto gui = CreateObject("gui"); {
        auto title = gui->CreateComponent<TextRenderer>(zephyr::rendering::IGUIWidget::EAlign::CENTER, zephyr::rendering::IGUIWidget::EAlign::BEGIN, 0.0f);
        title->Text("Zephyr3D Demo Scene");
    }
}