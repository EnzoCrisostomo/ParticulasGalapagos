#include "MainMenuState.hpp"

#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Components/StaticSprite.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Components/CameraFollower.hpp"
#include "Galapagos/Components/Text.hpp"
#include "Galapagos/Utils/ParticlePresets.hpp"
#include "Galapagos/Utils/Random.h"
#include "Galapagos/Components/Sound.hpp"
#include "Galapagos/Core/Game.hpp"

#include "StageState.hpp"
#include "Components/UI/Button.h"

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
    m_music.Stop(300);
    m_objectArray.clear();
}

void MainMenuState::LoadAssets()
{
    m_music.Open("res/audio/mainMenu.mp3");

    GameObject *titleImage = new GameObject();

    AnimatedSprite *background = new AnimatedSprite(*titleImage, "res/img/MainMenu.png", 40, 0.084f, true, 7, 6);
    titleImage->AddComponent(background);

    CameraFollower *cameraFollower = new CameraFollower(*titleImage);
    titleImage->AddComponent(cameraFollower);
    background->SetDist(0, 0, 1440 , 810);
    m_objectArray.emplace_back(titleImage);


    GameObject* emmiterObject = new GameObject();
    ParticleEmmiter* partEmm = new ParticleEmmiter(*emmiterObject, 30000, ParticleEmmiter::Type::Texture, "res/img/meteor.png");
    emmiterObject->AddComponent(partEmm);

    m_emmiter = partEmm;
    m_particleConfig = ParticlePreset::Snow;
    //m_particleConfig.lifeTime = 5.f;
    //m_particleConfig.startColor = { 0, 150, 200, 100 };
    //m_particleConfig.startSize = 20;
    //m_particleConfig.sizeVariation = 10;
    //m_particleConfig.velocity = { 0, 50 };
    //m_particleConfig.velocityVariation = { 100, 100 };
    //m_particleConfig.rate = 0.02;
    m_objectArray.emplace_back(emmiterObject);


    GameObject* buttonStartObject = new GameObject();
    Button* startButton = new Button(*buttonStartObject, [&]() {Game::Push(new StageState()); }, "Novo Jogo", "res/img/UI/Novo jogo.png");
    buttonStartObject->AddComponent(startButton);
    m_objectArray.emplace_back(buttonStartObject);
    buttonStartObject->m_box.SetCenter({ 720, 300 });

    //GameObject* buttonConfigObject = new GameObject();
    //Button* configButton = new Button(*buttonConfigObject, [&]() {Game::Push(new StageState()); }, "Config", "res/img/UI/botao.png");
    //buttonConfigObject->AddComponent(configButton);
    //m_objectArray.emplace_back(buttonConfigObject);
    //buttonConfigObject->m_box.y = 150;

    GameObject* leaveButtonObject = new GameObject();
    Button* leaveButton = new Button(*leaveButtonObject, [&]() {m_quitRequested = true; }, "Sair", "res/img/UI/Sair.png");
    leaveButtonObject->AddComponent(leaveButton);
    m_objectArray.emplace_back(leaveButtonObject);
    leaveButtonObject->m_box.SetCenter({ 720, 500 });
}

void MainMenuState::Update(float deltaTime)
{
    UpdateArray(deltaTime);
    if (InputManager::QuitRequested())
    {
        m_quitRequested = true;
    }
    m_particleConfig.position = { static_cast<float>(Random::Double()) * (1440 + m_particleConfig.velocityVariation.x), -50};
    m_emmiter->Emit(m_particleConfig);
    if (m_emmiter && InputManager::IsMouseDown(MouseButton::Left)) {
        ParticleConfig fire = ParticlePreset::Fire;
        fire.position = InputManager::GetMousePos();
        m_emmiter->Emit(fire);
    }
    if (m_emmiter && InputManager::MousePress(MouseButton::Right)) {
        ParticleConfig explosion = ParticlePreset::Explosion;
        explosion.position = InputManager::GetMousePos();
        GameObject* soundGo = new GameObject();

        Sound* sound = new Sound(*soundGo, "res/audio/boom.wav");
        soundGo->AddComponent(sound);
        sound->Play();
        Game::GetCurrentState().AddObject(soundGo);

        for (int i = 0; i < 300; i++) {
            m_emmiter->EmitVector(explosion);
        }
    }
    if (m_emmiter && InputManager::KeyPress(Key::K)) {
        GameObject* meteor = new GameObject();
        meteor->m_angleDeg = Random::Double() * 180 + 180;

        StaticSprite* sprite = new StaticSprite(*meteor, "res/img/meteor.png");
        meteor->AddComponent(sprite);
        sprite->SetScale(0.06);
        meteor->m_box.SetCenter({ static_cast<float>(Random::Double()) * 1000 + 400, -100});

        Game::GetCurrentState().AddObject(meteor);
        m_meteorList.push_back(meteor);
    }
    for (auto meteor : m_meteorList) {
        Vec2 center = meteor->m_box.GetCenter();
        center.x -= 500 * deltaTime;
        center.y += 800 * deltaTime;
        meteor->m_box.SetCenter(center);
        ParticleConfig fire = ParticlePreset::Fire;
        fire.position.x = meteor->m_box.GetCenter().x + (static_cast<float>(Random::Double()) - 0.5f) * meteor->m_box.w;
        fire.position.y = meteor->m_box.GetCenter().y + (static_cast<float>(Random::Double()) - 0.5f)* meteor->m_box.h;
        m_emmiter->Emit(fire);
        m_emmiter->Emit(fire);
        m_emmiter->Emit(fire);
    }
    for (size_t i = 0; i < m_objectArray.size(); i++)
    {
        if (m_objectArray.at(i)->IsDead())
        {
            m_objectArray.erase(m_objectArray.begin() + i);
        }
    }
}

void MainMenuState::Render() const
{
    RenderArray();
}

void MainMenuState::Start()
{
    Camera::position = { 0, 0 };
    LoadAssets();
    StartArray();
    m_music.Play(-1);
}

void MainMenuState::Pause()
{
    m_music.Stop(0);
}

void MainMenuState::Resume()
{
    Camera::position = { 0, 0 };
    m_music.Play(-1);
}