#include "Display.h"
#include <SFML/Graphics/RectangleShape.hpp>


namespace Display {

	sf::RenderWindow window;
	sf::Color clearColor;
	void init(){
		window.create(sf::VideoMode(DEF_WIDTH, DEF_HEIGHT), "Gra", sf::Style::Default);
	}


	void draw(sf::Drawable& object){
		window.draw(object);
	}

	void update() {
		window.display();
	}

	void clear() {
		window.clear({ 0, 0, 0 });
	}
	sf::Vector2u getSize(){
		return window.getSize();
	}

	bool isOpen() {
		return window.isOpen();
	}

	void checkIfClose(sf::Event& e) {
		if (sf::Event::Closed == e.type)
			window.close();
	}

	void pollEvents(State::BaseState& CurrentState){
		sf::Event e;
		while (window.pollEvent(e)) {
			CurrentState.input(e);
			checkIfClose(e);
		}
	}

	void setClearColor(sf::Color& color)
	{
		clearColor = color;
	}

	sf::Vector2f getTileSize() {
		 auto s = Display::getSize();
		 return { s.x / 10.f, s.y / 10.f };
	}


}