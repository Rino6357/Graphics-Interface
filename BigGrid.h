#pragma once
#include <array>
#include <memory>
#include "Button.h"
#include "SmallGrid.h"

class BigGrid
{
public:
	BigGrid();

	std::array<std::unique_ptr<SmallGrid>, 9>& getGrids() { return m_grids; }

	void assignButton(Button* bigGrid) { m_button = bigGrid; }

	SmallGrid& operator[](int grid) { return *m_grids[grid]; }

private:
	Button* m_button;
	std::array<std::unique_ptr<SmallGrid>, 9> m_grids{};
};

