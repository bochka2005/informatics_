#include <SFML/Graphics.hpp>
#include <functional> 
#include <cmath> 
#include <string>

// Функция графиков
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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Regions App");

    sf::CircleShape userPoint(5);
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(18);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition(10, 10);

    // Оси коорд
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(0, 300); xAxis[0].color = sf::Color(200, 200, 200);
    xAxis[1].position = sf::Vector2f(800, 300); xAxis[1].color = sf::Color(200, 200, 200);

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 0); yAxis[0].color = sf::Color(200, 200, 200);
    yAxis[1].position = sf::Vector2f(400, 600); yAxis[1].color = sf::Color(200, 200, 200);

    const float scale = 30.0f; // Пикселей\ 1 единицу

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // координаты в математику
                float mathX = (mousePos.x - 400) / scale;
                float mathY = -(mousePos.y - 300) / scale;

                userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                userPointExists = true;

                float line1 = mathX - 3.0f;    // y = x - 3
                float line2 = -mathX + 5.0f;   // y = -x + 5

                std::string region;
                const float EPS = 0.2f;

                // Логика 4 областей
                if (std::abs(mathY - line1) < EPS) {
                    region = "Na linii: y = x - 3";
                }
                else if (std::abs(mathY - line2) < EPS) {
                    region = "Na linii: y = -x + 5";
                }
                else {
                    if (mathY > line1 && mathY > line2) {
                        region = "Oblast 1 Verh";
                    }
                    else if (mathY < line1 && mathY < line2) {
                        region = "Oblast 2 Niz";
                    }
                    else if (mathX > 4.0f && mathY < line2 && mathY > line1) {
                        // точка пересечения 
                        region = "Oblast 3 Pravo";
                    }
                    else if (mathY > line1 && mathY < line2) {
                        region = "Oblast 4 Levo";
                    }
                    else {
                        // проверка для правой части, для уточнения
                        region = "Oblast 3 Pravo";
                    }
                }

                infoText.setString("X: " + std::to_string(mathX).substr(0, 5) +
                    "  Y: " + std::to_string(mathY).substr(0, 5) +
                    "\nResult: " + region);
            }
        }

        window.clear(sf::Color::White);

        // Сетку и оси
        window.draw(xAxis);
        window.draw(yAxis);
        for (int i = -12; i <= 12; ++i) {
            if (i == 0) continue;
            sf::Text n; n.setFont(font); n.setCharacterSize(10); n.setFillColor(sf::Color(180, 180, 180));
            n.setString(std::to_string(i));
            n.setPosition(400 + i * scale - 5, 305); window.draw(n);
            n.setPosition(405, 300 - i * scale - 7); window.draw(n);
        }

        // Рисунок функций
        float xMin = -15.0f, xMax = 15.0f;
        drawGraph(window, [](float x) { return x - 3.0f; }, xMin, xMax, scale, scale, sf::Color::Blue);
        drawGraph(window, [](float x) { return -x + 5.0f; }, xMin, xMax, scale, scale, sf::Color::Red);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(infoText);
        }

        window.display();
    }
    return 0;
}
