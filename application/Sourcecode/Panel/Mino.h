#pragma once
#include <array> 
#include <vector>

enum class MinoType {
	Omino,
	Tmino,
	Smino,
	Zmino,
	Imino,
	Lmino,
	Jmino
};

struct Mino {
	std::vector<std::vector<uint32_t>> panel_;
};

class MinoList
{
private:
	
private:
	static std::array<Mino, 7> minoList_;

public:
	MinoList();
private:
	Mino OminoInit();
	Mino TminoInit();
	Mino SminoInit();
	Mino ZminoInit();
	Mino IminoInit();
	Mino LminoInit();
	Mino JminoInit();
public:
	static Mino GetMinoList(MinoType type) { return minoList_.at((size_t)type); }
};