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
                                           tileWidth_(width_ / (float)cols),
                                           tileHeight_(height_ / (float)rows)
{
    setPosition(position);

    Vector2f i_hat = worldConfig.getCamera()->transform2(Vector3f(tileWidth_, 0, 0), 0);
    Vector2f j_hat = worldConfig.getCamera()->transform2(Vector3f(0, tileHeight_, 0), 0);

    Vector2i i_hati(
        int(i_hat.x),
        int(i_hat.y));

    Vector2i j_hati(
        int(j_hat.x),
        int(j_hat.y));

    sf::Image floor;
    floor.create(cols_ * 64, rows_ * 32 + 32, sf::Color::Transparent);

    sf::Image grass;
    grass.create(cols_ * 64, rows_ * 32 + 32, sf::Color::Transparent);

    DiagonalIterateGrid gridIterator(rows_);
    int i, j;
    Vector2i origin(floor.getSize().x / 2 - 32, 0);
    while (gridIterator.next(i, j))
    {
        Vector2i cellPos = origin + i_hati * i + j_hati * j;

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
        // type = "ts_grass0";

        sf::Image *tile = rm.loadImage("graphics/tiles/" + type + "/straight/" + dir + "/0.png");

        floor.copy(
            *tile,
            cellPos.x,
            cellPos.y,
            sf::IntRect(
                0, 0, tile->getSize().x, tile->getSize().y),
            true);

        type = "ts_grass0";
        tile = rm.loadImage("graphics/tiles/" + type + "/straight/" + dir + "/0.png");
        grass.copy(
            *tile,
            cellPos.x,
            cellPos.y + 6,
            sf::IntRect(
                0, 0, tile->getSize().x, tile->getSize().y),
            true);
    }

    Vector3f spriteOrigin(
        floor.getSize().x / 2.f,
        32,
        0);

    for (unsigned int i = 0; i < floor.getSize().x; i++)
    {
        for (unsigned int j = 0; j < floor.getSize().y; j++)
        {
            Vector3f screenpos = worldConfig.getCamera()->transform(getPosition());

            Vector3f groundPoint = worldConfig.getCamera()->projectGround(
                screenpos - spriteOrigin + Vector3f((float)i, (float)j, 0));

            float h = worldConfig.getElevation(groundPoint);

            sf::Color color = floor.getPixel(i, j);
            if (h < 0)
            {
                h += 0.8f;
                h = h * h * h;
                color.a = std::min((int)(h * 255), (int)color.a);
            }
            else
            {
                h = worldConfig.getElevation(groundPoint, 10);
                h = std::clamp(h * 2.f, 0.f, 1.f);
                h = h * h;
                h = h < 0.3 ? 0 : h;
                h = h * h;
                color = mixColor(color, grass.getPixel(i, j), h);
            }

            floor.setPixel(i, j, color);
        }
    }

    floor_.loadFromImage(floor);

    floorSprite_.setTexture(floor_);
    floorSprite_.setOrigin(
        Vector2f(
            spriteOrigin.x,
            spriteOrigin.y));

    // floor_.setSmooth(true);
}

void Ground::transform(Camera &camera)
{
    Entity::transform(camera);

    floorSprite_.setPosition(getScreenPosition2());
}

void Ground::draw(sf::RenderTarget *screen)
{

    screen->draw(floorSprite_);
}
