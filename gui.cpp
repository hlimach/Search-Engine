#include "SFML/Window.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics.hpp"

using namespace sf;

int main()
{
	sf::RenderWindow windowmain(sf::VideoMode(600, 300), "Search Engine");
  
	sf::Font font;
	font.loadFromFile("../data/arial.ttf");
  
	while (true)
	{
		while (windowmain.isOpen())
		{
			windowmain.clear(Color(255, 255, 255));
      
			sf::Texture title;
			sf::Sprite titleImage;
			title.loadFromFile("../data/title.png");
			titleImage.setPosition(150, 10);
			float titleWidth = titleImage.getLocalBounds().width;
			float titleHeight = titleImage.getLocalBounds().height;
			titleImage.setTexture(title);
      
			sf::Texture searchButton;
			sf::Sprite searchButtonImage;
			searchButton.loadFromFile("../data/button_search.png");
			searchButtonImage.setPosition(460, 100);
			float searchButtonWidth = searchButtonImage.getLocalBounds().width;
			float searchButtonHeight = searchButtonImage.getLocalBounds().height;
			searchButtonImage.setTexture(searchButton);
      
			sf::Event mouseevent;
			while (windowmain.pollEvent(mouseevent))
			{
				switch (mouseevent.type)
				{
				case sf::Event::Closed:
					windowmain.close();
					return 0;
				case sf::Event::MouseMoved:
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(windowmain);
					sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
					if (searchButtonImage.getGlobalBounds().contains(mousePosF))
						searchButtonImage.setColor(sf::Color(100, 100, 100));
					else
						searchButtonImage.setColor(sf::Color(255, 255, 255));
				}
				break;
				}
        
				windowmain.draw(titleImage);
				windowmain.draw(searchButtonImage);
				windowmain.display();
			}
		}
	}
}
