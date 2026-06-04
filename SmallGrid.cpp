#include "SmallGrid.h"

SmallGrid::SmallGrid(Button* smallGrid)
	: m_button{smallGrid}, m_marks{} {

}

void SmallGrid::setMark(size_t index, MarkType mark) {
	m_markStates[index] = mark;
}

void SmallGrid::refresh() {
	for (int i{ 0 }; i < 9; ++i) {
		switch (m_markStates[i]) {
		case Circle:
			m_marks[i]->setTexture("Textures/Circle.png");
			break;
		case Cross:
			m_marks[i]->setTexture("Textures/Cross.png");
			break;
		case Empty:
			m_marks[i]->removeTexture();
		}
	}
}