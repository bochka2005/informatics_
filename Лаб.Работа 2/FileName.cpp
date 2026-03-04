#include <SFML/Graphics.hpp>
#include <functional> 
#include <cmath> 
#include <string>

void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);
    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x);
        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;
        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }
    window.draw(graph);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "app for graf");

    sf::CircleShape userPoint(5);
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::Black);
    coordinatesText.setPosition(10, 10);

    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(0, 300); xAxis[0].color = sf::Color::Black;
    xAxis[1].position = sf::Vector2f(800, 300); xAxis[1].color = sf::Color::Black;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 0); yAxis[0].color = sf::Color::Black;
    yAxis[1].position = sf::Vector2f(400, 600); yAxis[1].color = sf::Color::Black;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                float mathX = (mousePos.x - 400) / 30.0f;
                float mathY = -(mousePos.y - 300) / 30.0f;

                userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                userPointExists = true;

                float yLower = mathX - 3.0f;
                float yUpper = mathX + 5.0f;
                std::string region;
                const float EPS = 0.15f;

                if (std::abs(mathY - yLower) < EPS) region = "Granitsa: y = x - 3";
                else if (std::abs(mathY - yUpper) < EPS) region = "Granitsa: y = x + 5";
                else if (mathY > yUpper) region = "Oblast 1 vishe";
                else if (mathY < yLower) region = "Oblast 3 nije";
                else region = "Oblast 2 mejdu";

                coordinatesText.setString("X: " + std::to_string(mathX).substr(0, 5) +
                    ", Y: " + std::to_string(mathY).substr(0, 5) + "\n" + region);
            }
        }

        window.clear(sf::Color::White);
        window.draw(xAxis);
        window.draw(yAxis);

        for (int i = -12; i <= 12; ++i) {
            if (i == 0) continue;
            sf::Text n; n.setFont(font); n.setCharacterSize(12); n.setFillColor(sf::Color(150, 150, 150));
            n.setString(std::to_string(i));
            n.setPosition(400 + i * 30 - 7, 305); window.draw(n);
            n.setPosition(405, 300 - i * 30 - 8); window.draw(n);
        }

        float xMin = -15.0f, xMax = 15.0f;
        drawGraph(window, [](float x) { return x - 3.0f; }, xMin, xMax, 30, 30, sf::Color::Blue);
        drawGraph(window, [](float x) { return -x + 5.0f; }, xMin, xMax, 30, 30, sf::Color::Red);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }
        window.display();
    }
    return 0;

}
