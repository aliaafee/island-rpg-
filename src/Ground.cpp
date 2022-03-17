#include "Ground.hpp"

Ground::Ground(ResourceManager &rm,
               const float &width, const float &height,
               const int &rows, const int &cols) : Entity(rm),
                                                   width_(width),
                                                   height_(height),
                                                   rows_(rows),
                                                   cols_(cols),
                                                   tileWidth_(width / (float)cols),
                                                   tileHeight_(height / (float)rows)
{
    tiles_.resize(cols_ * rows_);
    for (auto &tile : tiles_)
    {
        int d = randi(0, 4);
        std::string dir = "45";
        if (d == 0)
            dir = "135";
        if (d == 1)
            dir = "225";
        if (d == 2)
            dir = "315";
        d = randi(0, 4);
        std::string type = "ts_beach0";
        tile = rm.loadTexture("graphics/tiles/" + type + "/straight/" + dir + "/0.png");
    }
    sf::Texture *w = rm.loadTexture("graphics/tiles/ts_beach0/straight/45/0.png");
    sprite_.setTexture(*w);
    sprite_.setOrigin(32, 32);
}

void Ground::transform(Camera &camera)
{
    Entity::transform(camera);

    i_hat = camera.transform2(Vector3f(tileWidth_, 0, 0), 0);
    j_hat = camera.transform2(Vector3f(0, tileHeight_, 0), 0);
}

void Ground::draw(sf::RenderTarget *screen)
{
    Vector2f pos = getScreenPosition2();

    for (int i = 0; i < cols_; i++)
    {
        for (int j = 0; j < rows_; j++)
        {
            sprite_.setTexture(*(tiles_[i + cols_ * j]));
            sprite_.setPosition(pos + i_hat * (float)i + j_hat * (float)j);
            screen->draw(sprite_);
        }
    }
}
