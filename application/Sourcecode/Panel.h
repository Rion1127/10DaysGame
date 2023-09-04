#pragma once
#include <vector>
#include <array>
class Panel
{
private:
	enum State {
		NOT_OPEN,
		EMPTY,
		ATTACK,
		NEXT_RELEASE,
		SELECT
	};
private:
	std::vector<std::vector<uint32_t>> panel_;
	std::vector<std::vector<uint32_t>> savePanel_;
	uint32_t maxPanelSize_;
	uint32_t initalSize_;
private:
	int debugSelectX = 0;
	int debugSelectY = 0;
public:
	Panel();
	void Update();
	void Draw();

	void DrawImGui();
};