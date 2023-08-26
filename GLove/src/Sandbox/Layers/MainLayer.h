#pragma once

#include <GLove.h>

class MainLayer : public Layer
{
public:
	MainLayer();
	~MainLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnEvent(Event& e) override;
private:
	GameObject* m_Cube;
	GameObject* m_Camera;
};