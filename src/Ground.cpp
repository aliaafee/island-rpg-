#include "Ground.hpp"

Ground::Ground(ResourceManager &rm,
               const Vector3f &position,
               const float &width, const float &height,
               const int &rows, const int &cols,
               WorldConfig &worldConfig,
               RandomGenerator &r) : Entity(rm),
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

    DiagonalIterateGrid gridIterator(rows_ + 2);
    int gi, gj;
    Vector2i origin(floor.getSize().x / 2 - 32, 0);
    while (gridIterator.next(gi, gj))
    {
        int i = gi - 1;
        int j = gj - 1;
        Vector2i cellPos = origin + i_hati * i + j_hati * j;

        // if (cellPos.x >= 0 and cellPos.y >= 0)

        int tileOffsetx = 0;
        if (cellPos.x < 0)
        {
            tileOffsetx = abs(cellPos.x);
            cellPos.x = 0;
        }

        int tileOffsety = 0;
        if (cellPos.y < 0)
        {
            tileOffsety = abs(cellPos.y);
            cellPos.y = 0;
        }

        int d = r.randomInt(0, 4);
        std::string dir = "45";
        if (d == 0)
            dir = "135";
        if (d == 1)
            dir = "225";
        if (d == 2)
            dir = "315";
        d = r.randomInt(0, 4);
        std::string type = "ts_beach0";
        // type = "ts_grass0";

        sf::Image *tile = rm.loadImage("graphics/tiles/" + type + "/straight/" + dir + "/0.png");

        floor.copy(
            *tile,
            cellPos.x,
            cellPos.y,
            sf::IntRect(
                tileOffsetx, tileOffsety, tile->getSize().x - tileOffsetx, tile->getSize().y - tileOffsety),
            true);

        type = "ts_grass0";
        tile = rm.loadImage("graphics/tiles/" + type + "/straight/" + dir + "/0.png");
        grass.copy(
            *tile,
            cellPos.x,
            cellPos.y + 6,
            sf::IntRect(
                tileOffsetx, tileOffsety, tile->getSize().x - tileOffsetx, tile->getSize().y - tileOffsety),
            true);
    }

    Vector3f spriteOrigin(
        floor.getSize().x / 2.f,
        32,
        0);

    // Coastline gen method 1
    Vector2f originf((float)floor.getSize().x / 2.f, 30.f);
    float i_max = (width_ / tileWidth_);
    float j_max = (height_ / tileHeight_);
    for (float i = -1.f; i < i_max + 1.5; i += 0.03f)
    {
        for (float j = -1.f; j < j_max + 1.5; j += 0.02f)
        {
            Vector2f cellPos = originf + i_hat * i + j_hat * j;
            Vector3f cellPosWorld = getPosition() + Vector3f(tileWidth_ * i, tileHeight_ * j, 0);

            float h = worldConfig.getElevation(cellPosWorld);

            float overlap = 0.f;

            float fx = 1;
            float fy = 1;
            if (i < overlap)
            {
                fx = std::max(0.f, 1.f - (overlap - i));
            }
            if (i > i_max - overlap)
            {
                if (i > i_max + (1 - overlap))
                {
                    fx = 0;
                }
                else
                {
                    fx = 1.f - (i - (i_max - overlap));
                }
            }
            if (j < overlap)
            {
                fy = std::max(0.f, 1.f - (overlap - j));
            }
            if (j > j_max - overlap)
            {
                if (j > j_max + (1 - overlap))
                {
                    fy = 0;
                }
                else
                {
                    fy = 1.f - (j - (j_max - overlap));
                }
            }

            int px, py;
            px = (int)cellPos.x;
            py = (int)cellPos.y;

            if (px < floor.getSize().x &&
                py < floor.getSize().y &&
                px >= 0 &&
                py >= 0)
            {
                sf::Color color = floor.getPixel(px, py);

                float alpha = fx * fy;
                if (h < 0)
                {
                    h += 0.8f;
                    h = h * h * h;
                    alpha = std::min(h, alpha * h);
                }
                else
                {
                    h = worldConfig.getElevation(cellPosWorld, 10);
                    h = std::clamp(h * 2.f, 0.f, 1.f);
                    h = h * h;
                    h = h < 0.2 ? 0 : h;
                    h = h * h;
                    color = mixColor(color, grass.getPixel(px, py), h);
                }
                color.a = (alpha * 255.f); // std::min((int)(alpha * 255.f), (int)color.a);

                floor.setPixel(px, py, color);
            }
        }
    }
    // Coastline gen method 1

    // Coastline gen method 2
    // for (unsigned int i = 0; i < floor.getSize().x; i++)
    // {
    //     for (unsigned int j = 0; j < floor.getSize().y; j++)
    //     {
    //         Vector3f screenpos = worldConfig.getCamera()->transform(getPosition());

    //         Vector3f groundPoint = worldConfig.getCamera()->projectGround(
    //             screenpos - spriteOrigin + Vector3f((float)i, (float)j, 0));

    //         float h = worldConfig.getElevation(groundPoint);

    //         sf::Color color = floor.getPixel(i, j);
    //         if (h < 0)
    //         {
    //             h += 0.8f;
    //             h = h * h * h;
    //             color.a = std::min((int)(h * 255), (int)color.a);
    //         }
    //         else
    //         {
    //             h = worldConfig.getElevation(groundPoint, 10);
    //             h = std::clamp(h * 2.f, 0.f, 1.f);
    //             h = h * h;
    //             h = h < 0.3 ? 0 : h;
    //             h = h * h;
    //             color = mixColor(color, grass.getPixel(i, j), h);
    //         }

    //         floor.setPixel(i, j, color);
    //     }
    // }
    // Coastline gen method 2

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
