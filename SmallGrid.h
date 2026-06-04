#pragma once
#include "Button.h"

class SmallGrid
{
public:
	SmallGrid(Button* smallGrid);

	std::array<Button*, 9>& getMarks() { return m_marks; }

	Button* operator[](size_t index) { return m_marks[index]; }

	enum MarkType {
		Empty,
		Cross,
		Circle
	};

	void setMark(size_t index, MarkType mark);

	std::array<MarkType, 9> getMarkStates() { return m_markStates; }

	void refresh();

private:
	Button* m_button;
	std::array<Button*, 9> m_marks;
	std::array<MarkType, 9> m_markStates{};
};

