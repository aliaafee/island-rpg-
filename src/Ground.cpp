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

    sf::Image w;
    w.loadFromFile("graphics/test/mask.png");

    i_hat = worldConfig.getCamera()->transform2(Vector3f(tileWidth_, 0, 0), 0);
    j_hat = worldConfig.getCamera()->transform2(Vector3f(0, tileHeight_, 0), 0);

    transform(*(worldConfig.getCamera()));

    Vector2f screen_position = getScreenPosition2();
    for (int i = 0; i < worldConfig.subCols(); i++)
    {
        for (int j = 0; j < worldConfig.subRows(); j++)
        {
            Vector3f world_point(
                (float)i / (float)cols_ * width_ + getPosition().x,
                (float)j / (float)rows_ * height_ + getPosition().y,
                0);
            Vector2f screen_point = screen_position + i_hat * (float)(i) + j_hat * (float)(j);

            float elev = worldConfig.getElevation(world_point);
            if (elev > -0.5f)
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

                // sf::Texture *src = rm.loadTexture("graphics/tiles/" + type + "/straight/" + dir + "/0.png");

                sf::Image *s = rm.loadImage("graphics/tiles/" + type + "/straight/" + dir + "/0.png");

                type = "ts_grass0";
                sf::Image *g = rm.loadImage("graphics/tiles/" + type + "/straight/" + dir + "/0.png");

                sf::Image im; //= s->copyToImage();
                im.create(w.getSize().x, w.getSize().y, sf::Color::Black);
                // im.loadFromFile("graphics/tiles/" + type + "/straight/" + dir + "/0.png");

                for (int image_i = 0; image_i < im.getSize().x; image_i++)
                {
                    for (int image_j = 0; image_j < im.getSize().y; image_j++)
                    {
                        // sf::Color asrc = w.getPixel(i, j);
                        // sf::Color atarg = s->getPixel(i, j);

                        // pixel_elev = 0.f;
                        //  sf::Color atarg = im.getPixel(i, j);
                        // atarg.a =

                        sf::Color src = s->getPixel(image_i, image_j);

                        if (src.a > 0)
                        {

                            float pixel_elev = worldConfig.getElevation(
                                worldConfig.getCamera()->projectGround(
                                    screen_point + Vector2f((float)image_i, (float)image_j)));

                            if (pixel_elev < 0)
                            {
                                src.a = 0;
                                // pixel_elev = (pixel_elev + 1.f) / 2.f;
                                // pixel_elev *= pixel_elev;
                                // src.a = std::min((int)src.a, (int)(pixel_elev * 255.f));
                            }
                            else
                            {
                                sf::Color grass = g->getPixel(image_i, image_j - 5);
                                float f = pixel_elev;
                                f = f - 0.1;
                                f = f * f;
                                if (f > 0.2)
                                    f = 1;
                                if (f < 0)
                                    f = 0;

                                Vector3f orginal((float)src.r / 255.f, (float)src.g / 255.f, (float)src.b / 255.f);
                                Vector3f target((float)grass.r / 255.f, (float)grass.g / 255.f, (float)grass.b / 255.f);
                                Vector3f out = orginal + (target - orginal) * f;
                                src.r = (int)(out.x * 255);
                                src.g = (int)(out.y * 255);
                                src.b = (int)(out.z * 255);
                            }
                        }
                        // ;

                        im.setPixel(image_i, image_j, src);
                    }
                }

                sf::Texture *newTex = new sf::Texture();
                newTex->loadFromImage(im);

                tiles_[i + cols_ * j] = newTex;
                // tiles_[i + cols_ * j] = nullptr;

                // tiles_[i + cols_ * j]
                //     ->update(w.getPixelsPtr(), 64, 64, 0, 0);
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
