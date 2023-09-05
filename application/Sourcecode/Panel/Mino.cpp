#include "Mino.h"

std::array<Mino, 7> MinoList::minoList_;

MinoList::MinoList()
{
	for (uint32_t i = 0; i < minoList_.size(); i++) {
		//ƒ~ƒm‰Šú‰»
		if (i == (uint32_t)MinoType::Omino) {
			minoList_[i] = OminoInit();
		}
		else if (i == (uint32_t)MinoType::Tmino) {
			minoList_[i] = TminoInit();
		}
		else if (i == (uint32_t)MinoType::Smino) {
			minoList_[i] = SminoInit();
		}
		else if (i == (uint32_t)MinoType::Zmino) {
			minoList_[i] = ZminoInit();
		}
		else if (i == (uint32_t)MinoType::Imino) {
			minoList_[i] = IminoInit();
		}
		else if (i == (uint32_t)MinoType::Lmino) {
			minoList_[i] = LminoInit();
		}
		else if (i == (uint32_t)MinoType::Jmino) {
			minoList_[i] = JminoInit();
		}
	}
}

Mino MinoList::OminoInit()
{
	Mino result{};

	result.panel_.resize(2);
	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		result.panel_[y].resize(2);
	}

	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		for (uint32_t x = 0; x < result.panel_[y].size(); x++) {
			result.panel_[y][x] = 1;
		}
	}

	return result;
}

Mino MinoList::TminoInit()
{
	Mino result{};

	result.panel_.resize(2);
	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		result.panel_[y].resize(3);
	}

	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		for (uint32_t x = 0; x < result.panel_[y].size(); x++) {
			if (y == 0 && x == 1) {
				result.panel_[y][x] = 1;
			}
			else if (y == 1) {
				result.panel_[y][x] = 1;
			}
		}
	}

	return result;
}

Mino MinoList::SminoInit()
{
	Mino result{};

	result.panel_.resize(2);
	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		result.panel_[y].resize(3);
	}

	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		for (uint32_t x = 0; x < result.panel_[y].size(); x++) {
			if (y == 0 && x >= 1) {
				result.panel_[y][x] = 1;
			}
			if (y == 1 && x <= 1) {
				result.panel_[y][x] = 1;
			}
		}
	}

	return result;
}

Mino MinoList::ZminoInit()
{
	Mino result{};

	result.panel_.resize(2);
	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		result.panel_[y].resize(3);
	}

	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		for (uint32_t x = 0; x < result.panel_[y].size(); x++) {
			if (y == 0 && x <= 1) {
				result.panel_[y][x] = 1;
			}
			if (y == 1 && x >= 1) {
				result.panel_[y][x] = 1;
			}
		}
	}

	return result;
}

Mino MinoList::IminoInit()
{
	Mino result{};

	result.panel_.resize(4);
	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		result.panel_[y].resize(1);
	}

	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		for (uint32_t x = 0; x < result.panel_[y].size(); x++) {
			result.panel_[y][x] = 1;
		}
	}

	return result;
}

Mino MinoList::LminoInit()
{
	Mino result{};

	result.panel_.resize(2);
	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		result.panel_[y].resize(3);
	}

	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		for (uint32_t x = 0; x < result.panel_[y].size(); x++) {
			if (x == 2) {
				result.panel_[y][x] = 1;
			}
			if (y == 1) {
				result.panel_[y][x] = 1;
			}
		}
	}

	return result;
}

Mino MinoList::JminoInit()
{
	Mino result{};

	result.panel_.resize(2);
	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		result.panel_[y].resize(3);
	}

	for (uint32_t y = 0; y < result.panel_.size(); y++) {
		for (uint32_t x = 0; x < result.panel_[y].size(); x++) {
			if (x == 0) {
				result.panel_[y][x] = 1;
			}
			if (y == 1) {
				result.panel_[y][x] = 1;
			}
		}
	}

	return result;
}