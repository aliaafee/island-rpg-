#include "Ground.hpp"

Ground::Ground(ResourceManager &rm,
               const Vector3f &position,
               const float &width, const float &height,
               const int &rows, const int &cols,
               WorldConfig &worldConfig) : Entity(rm),
                                           width_(width),
                                           height_(height),
                                           rows_(rows),
                                           cols_(cols),
                                           tileWidth_(width / (float)cols),
                                           tileHeight_(height / (float)rows),
                                           noise_()
{
    setPosition(position);

    tiles_.resize(cols_ * rows_);

    for (int i = 0; i < worldConfig.subCols(); i++)
    {
        for (int j = 0; j < worldConfig.subRows(); j++)
        {
            Vector3f point(
                (float)i / (float)cols_ * width_ + getPosition().x,
                (float)j / (float)rows_ * height_ + getPosition().y,
                0);
            float elev = worldConfig.getElevation(point);
            if (elev > -0.f)
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
                // if (elev > 0.3f)
                //     type = "ts_grass0";

                tiles_[i + cols_ * j] = rm.loadTexture("graphics/tiles/" + type + "/straight/" + dir + "/0.png");
            }
            else
            {
                tiles_[i + cols_ * j] = nullptr;
            }
        }
    }

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
            if (tiles_[i + cols_ * j] != nullptr)
            {
                sprite_.setTexture(*(tiles_[i + cols_ * j]));
                sprite_.setPosition(pos + i_hat * (float)i + j_hat * (float)j);
                // float x = (tileWidth_ * (float)i + getPosition().x) * 0.0009f;
                // float y = (tileHeight_ * (float)j + getPosition().y) * 0.0009f;
                // float h = 255.f * (noise_.fractal(6, x, y));
                // if (h > 0.f)
                screen->draw(sprite_);
            }
        }
    }
}
