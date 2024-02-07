#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class m_Shape
{
    public:
    float s_sx,s_sy;
    float s_width,s_height,s_radius;
    float s_x,s_y;
    int s_r,s_g,s_b;
    T s_shape;
    sf::Text s_text;
    std::string s_name;
    m_Shape(T shape,sf::Text text,float sx,float sy,std::string& name,float width,float height,float radius,int r,int g,int b,float x,float y)
            : s_shape(std::move(shape)),s_text(std::move(text)),s_sx(sx),s_sy(sy),s_name(name),s_width(width),s_height(height),
              s_radius(radius),s_r(r),s_g(g),s_b(b),s_x(x),s_y(y)
    {
    }
};

int main(int argc,char * argv[])
{
    std::ifstream data("shapedata.txt");
    std::string token;
    int sWidth = 0;
    int sHeight = 0;
    sf::Font font;
    int textSize;
    sf::Color textColor;
    std::vector<m_Shape<sf::RectangleShape>> rectangleShapes;
    std::vector<m_Shape<sf::CircleShape>> circleShapes;
    while(data >> token)
    {
        if(token == "Window")
        {
            data >> sWidth;
            data >> sHeight;
        }
        if(token == "Font")
        {
            data >> token;
            font.loadFromFile(token);
            data >> textSize;
            int r,g,b;
            data >> r >> g >> b;
            textColor.r = r;
            textColor.g = g;
            textColor.b = b;
        }
        if(token == "Rectangle")
        {
            float sx,sy;
            float width,height;
            float x,y;
            int r,g,b;
            std::string name;
            data>>name>>width>>height>>sx>>sy>>r>>g>>b>>x>>y;
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(width,height));
            rectangle.setPosition(x,y);
            rectangle.setFillColor(sf::Color(r,g,b));
            std::cout<<name<<" "<<width<<" "<<height<<" "<< x <<" "<<y<<std::endl;
            std::cout<<rectangle.getSize().x<<std::endl;
            sf::Text text;
            text.setCharacterSize(textSize);
            std::cout<<textSize<<endl;
            text.setFillColor(textColor);
            text.setFont(font);
            text.setString(name);
            rectangleShapes.push_back(m_Shape<sf::RectangleShape>(rectangle,text,sx,sy,name,width,height,0,r,g,b,x,y));
        }
        if(token == "Circle")
        {
            float sx,sy;
            float radius;
            float x,y;
            int r,g,b;
            std::string name;
            data>>name>>radius>>sx>>sy>>r>>g>>b>>x>>y;
            sf::CircleShape circle;
            circle.setRadius(radius);
            circle.setPosition(x,y);
            circle.setFillColor(sf::Color(r,g,b));
            sf::Text text;
            text.setCharacterSize(textSize);
            std::cout<<textSize<<endl;
            text.setFillColor(textColor);
            text.setFont(font);
            text.setString(name);
            circleShapes.push_back(m_Shape<sf::CircleShape>(circle,text,sx,sy,name,0,0,radius,r,g,b,x,y));
        }
    }

    sf::RenderWindow window(sf::VideoMode(sWidth,sHeight),"Shapes");
    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        for(auto& rectangle : rectangleShapes)
        {
            rectangle.s_shape.setPosition(rectangle.s_shape.getPosition().x + rectangle.s_sx,rectangle.s_shape.getPosition().y + rectangle.s_sy);
            if(rectangle.s_shape.getPosition().x <= 0 || rectangle.s_shape.getPosition().x + rectangle.s_width >= sWidth)
            {
                rectangle.s_sx = -rectangle.s_sx;
            }
            if(rectangle.s_shape.getPosition().y <= 0 || rectangle.s_shape.getPosition().y + rectangle.s_height >= sHeight)
            {
                rectangle.s_sy = -rectangle.s_sy;
            }
            rectangle.s_text.setPosition(sf::Vector2f(rectangle.s_shape.getPosition().x + rectangle.s_width / 2 - textSize,rectangle.s_shape.getPosition().y + rectangle.s_height / 2 - textSize));
            window.draw(rectangle.s_shape);
            window.draw(rectangle.s_text);
        }
        for(auto& circle : circleShapes)
        {
            circle.s_shape.setPosition(circle.s_shape.getPosition().x + circle.s_sx,circle.s_shape.getPosition().y + circle.s_sy);
            if(circle.s_shape.getPosition().x <= 0 || circle.s_shape.getPosition().x + circle.s_radius * 2 >= sWidth)
            {
                circle.s_sx = -circle.s_sx;
            }
            if(circle.s_shape.getPosition().y <= 0 || circle.s_shape.getPosition().y + circle.s_radius* 2 >= sHeight)
            {
                circle.s_sy = -circle.s_sy;
            }
            circle.s_text.setPosition(sf::Vector2f(circle.s_shape.getPosition().x + circle.s_radius - textSize,circle.s_shape.getPosition().y + circle.s_shape.getRadius() - textSize));
            window.draw(circle.s_shape);
            window.draw(circle.s_text);
        }

        window.display();
    }

    return 0;
}