#pragma once
#include "Galapagos/Core/State.hpp"
#include "Galapagos/Utils/Timer.hpp"

class TitleState : public State
{
public:
    TitleState();
    ~TitleState();

    void LoadAssets();
    void Update(float deltaTime);
    void Render() const;

    void Start();
    void Pause();
    void Resume();
private:

    Timer m_timer;
};