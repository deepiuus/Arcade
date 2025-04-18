/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sfml
*/

#include "sfml.hpp"

arcade::SfmlLib::SfmlLib() : width(800), height(600), window(), 
    event(), font(), texture(), sprite(), text(), buffer(), song(), currentSound("") {}

arcade::SfmlLib::~SfmlLib() {}

void arcade::SfmlLib::Init()
{
    window.create(sf::VideoMode(width, height), "Arcade SFML");
    if (!font.loadFromFile("assets/fonts/upheavtt.ttf")) {
        throw Error("Failed to load font");
    }
    window.setFramerateLimit(60);
}

arcade::KeyBind arcade::SfmlLib::getKey()
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return KeyBind::ESC;
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::A:
                    return KeyBind::A_KEY;
                case sf::Keyboard::Z:
                    return KeyBind::Z_KEY;
                case sf::Keyboard::Q:
                    return KeyBind::Q_KEY;
                case sf::Keyboard::S:
                    return KeyBind::S_KEY;
                case sf::Keyboard::Up:
                    return KeyBind::UP_KEY;
                case sf::Keyboard::Down:
                    return KeyBind::DOWN_KEY;
                case sf::Keyboard::Left:
                    return KeyBind::LEFT_KEY;
                case sf::Keyboard::Right:
                    return KeyBind::RIGHT_KEY;
                case sf::Keyboard::Space:
                    return KeyBind::SPACE;
                case sf::Keyboard::Enter:
                    return KeyBind::ENTER;
                case sf::Keyboard::Escape:
                    return KeyBind::ESC;
                default:
                    break;
            }
        }
    }
    return KeyBind::NONE;
}

void arcade::SfmlLib::Display(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities)
{
    for (const auto &[entity, pos] : entities) {
        if (!entity.empty() && entity.rfind("assets/", 0) == 0) {
            size_t lastSlash = entity.find_last_of('/');
            if (lastSlash != std::string::npos)
                renderImage(entity, pos);
        } else {
            renderText(entity, pos);
        }
    }
    window.display();
}

void arcade::SfmlLib::renderImage(const std::string &entity, const std::pair<std::pair<int, int>, std::pair<int, int>> &pos)
{
    static std::vector<std::string> failedEntities;

    if (std::find(failedEntities.begin(), failedEntities.end(), entity) != failedEntities.end())
        return;

    if (!texture.loadFromFile(entity)) {
        failedEntities.push_back(entity);
        throw Error("Failed to load image: " + entity);
    }
    const int originalWidth = texture.getSize().x;
    const int originalHeight = texture.getSize().y;
    imgW = (pos.second.first == 0) ? originalWidth : pos.second.first;
    imgH = (pos.second.second == 0) ? originalHeight : pos.second.second;
    if (imgW <= 0 || imgH <= 0) {
        throw Error("Invalid dimensions for image: " + entity);
    }
    sprite.setTexture(texture);
    sprite.setPosition(pos.first.first, pos.first.second);
    sprite.setTextureRect(sf::IntRect(0, 0, originalWidth, originalHeight));
    sprite.setScale(static_cast<float>(imgW) / originalWidth, static_cast<float>(imgH) / originalHeight);
    window.draw(sprite);
}

void arcade::SfmlLib::renderText(const std::string &entity, const std::pair<std::pair<int, int>, std::pair<int, int>> &pos)
{
    text.setFont(font);
    text.setString(entity);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    txtW = pos.second.first == 0 ? text.getGlobalBounds().width : pos.second.first;
    txtH = pos.second.second == 0 ? text.getGlobalBounds().height : pos.second.second;
    if (txtW <= 0 || txtH <= 0) {
        throw Error("Invalid dimensions for text: " + entity);
    }
    text.setPosition(pos.first.first, pos.first.second);
    window.draw(text);
}

void arcade::SfmlLib::PlaySound(std::string sound)
{
    if (currentSound != sound) {
        song.stop();
        if (!buffer.loadFromFile(sound)) {
            throw Error("Failed to load sound: " + sound);
        }
        song.setBuffer(buffer);
        currentSound = sound;
    }
    song.setLoop(true);
    if (song.getStatus() != sf::Sound::Playing) {
        song.play();
    }
}

void arcade::SfmlLib::Clear()
{
    window.clear();
}

void arcade::SfmlLib::Nuke()
{
    song.stop();
    window.close();
}
