#include <SFML/Graphics.hpp>
#include <functional> 
#include <cmath> 
#include <sstream>
#include <iomanip>

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

void drawCoordinateSystem(sf::RenderWindow& window) {
    // Основные оси
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(0, 300);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].position = sf::Vector2f(800, 300);
    xAxis[1].color = sf::Color::Black;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 0);
    yAxis[0].color = sf::Color::Black;
    yAxis[1].position = sf::Vector2f(400, 600);
    yAxis[1].color = sf::Color::Black;

    window.draw(xAxis);
    window.draw(yAxis);

    // Сетка и подписи по оси x
    for (int x = -10; x <= 10; x += 1) {
        if (x == 0) continue;

        float screenX = 400 + x * 30;

        // Линии сетки
        sf::VertexArray gridLine(sf::Lines, 2);
        gridLine[0].position = sf::Vector2f(screenX, 0);
        gridLine[0].color = sf::Color(200, 200, 200);
        gridLine[1].position = sf::Vector2f(screenX, 600);
        gridLine[1].color = sf::Color(200, 200, 200);
        window.draw(gridLine);

        // Подписи
        sf::Font font;
        if (font.loadFromFile("arial.ttf")) {
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(x));
            text.setCharacterSize(12);
            text.setFillColor(sf::Color::Black);
            text.setPosition(screenX - 5, 305);
            window.draw(text);
        }
    }

    // Сетка и подписи по оси y
    for (int y = -10; y <= 10; y += 1) {
        if (y == 0) continue;

        float screenY = 300 - y * 30;

        // Линии сетки
        sf::VertexArray gridLine(sf::Lines, 2);
        gridLine[0].position = sf::Vector2f(0, screenY);
        gridLine[0].color = sf::Color(200, 200, 200);
        gridLine[1].position = sf::Vector2f(800, screenY);
        gridLine[1].color = sf::Color(200, 200, 200);
        window.draw(gridLine);

        // Подписи
        sf::Font font;
        if (font.loadFromFile("arial.ttf")) {
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(y));
            text.setCharacterSize(12);
            text.setFillColor(sf::Color::Black);
            text.setPosition(405, screenY - 10);
            window.draw(text);
        }
    }

    // Подписи осей
    sf::Font font;
    if (font.loadFromFile("arial.ttf")) {
        sf::Text xText;
        xText.setFont(font);
        xText.setString("X");
        xText.setCharacterSize(16);
        xText.setFillColor(sf::Color::Black);
        xText.setPosition(780, 305);
        window.draw(xText);

        sf::Text yText;
        yText.setFont(font);
        yText.setString("Y");
        yText.setCharacterSize(16);
        yText.setFillColor(sf::Color::Black);
        yText.setPosition(405, 10);
        window.draw(yText);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Приложение для вывода графиков");

    sf::CircleShape userPoint(5);
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
    }

    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::Black);
    coordinatesText.setPosition(10, 10);

    sf::Text zoneText;
    zoneText.setFont(font);
    zoneText.setCharacterSize(20);
    zoneText.setFillColor(sf::Color::Black);
    zoneText.setPosition(10, 40);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    float mathX = (mousePos.x - 400) / 30.0f;
                    float mathY = -(mousePos.y - 300) / 30.0f;

                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true;

                    std::string zone = "";
                    float y1 = mathX - 3;
                    float y2 = mathX + 5;

                    if (std::abs(mathY - y1) < 0.1f) {
                        zone = "Граница: y = x - 3";
                    }
                    else if (std::abs(mathY - y2) < 0.1f) {
                        zone = "Граница: y = x + 5";
                    }
                    else if (mathY > y2) {
                        zone = "Зона 1: Выше обеих прямых";
                    }
                    else if (mathY > y1 && mathY < y2) {
                        zone = "Зона 2: Между прямыми";
                    }
                    else if (mathY < y1) {
                        zone = "Зона 3: Ниже обеих прямых";
                    }

                    std::stringstream coordStream;
                    coordStream << std::fixed << std::setprecision(2) << "Координаты: (" << mathX << ", " << mathY << ")";
                    coordinatesText.setString(coordStream.str());
                    zoneText.setString(zone);
                }
            }
        }

        window.clear(sf::Color::White);

        drawCoordinateSystem(window);

        drawGraph(window, [](float x) { return x - 3; }, -10, 10, 30, 30, sf::Color::Blue);
        drawGraph(window, [](float x) { return x + 5; }, -10, 10, 30, 30, sf::Color::Red);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
            window.draw(zoneText);
        }

        window.display();
    }

    return 0;
}