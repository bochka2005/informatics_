#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(500, 500), "Laba 3");

    int cellSize = 50;
    int gridSize = 10;

    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(i * cellSize, j * cellSize);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);

                if (j % 2 != 0 && i + j >= gridSize ) {
                    cell.setFillColor(sf::Color::Green);
                }
                else {
                    cell.setFillColor(sf::Color::White);
                }

                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}