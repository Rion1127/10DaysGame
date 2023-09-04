#pragma once
#include <vector>
#include <array>
class Panel
{
private:
	enum State {
		EMPTY,
		ATTACK,
		NEXT_RELEASE,
		SELECT
	};
private:
	std::vector<std::vector<uint32_t>> panel_;
	uint32_t maxPanelSize_;
private:
	int debugSelectX = 0;
	int debugSelectY = 0;
public:
	Panel();
	void Update();
	void Draw();

	void DrawImGui();
};

class Mino
{
private:
	enum Type {
		Omino,
		Tmino,
		Smino,
		Zmino,
		Imino,
		Lmino,
		Jmino
	};
private:
	std::array<std::array<uint32_t,3>,3> panel_;

public:
	Mino();
private:
	void OminoInit();
	void TminoInit();
	void SminoInit();
	void ZminoInit();
	void IminoInit();
	void LminoInit();
	void JminoInit();
};