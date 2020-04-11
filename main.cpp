#include <SFML/Graphics.hpp>
#include "Obj.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <sstream>

void gravityForce(Obj *o1, Obj *o2)
{

    const float scale = 5;
    sf::Vector2f poz1 = o1->getPosition();
    sf::Vector2f poz2 = o2->getPosition();
    float m1 = o1->getMass();
    float m2 = o2->getMass();
    float k;
    sf::Vector2f result;
    k=(m2/(pow(poz2.x-poz1.x,2)+pow(poz2.y-poz1.y,2)))/scale;
    result=sf::Vector2f((poz2.x-poz1.x)*k,(poz2.y-poz1.y)*k);
    o1->addVelocity(result);
    k=((m1*m2)/(pow(poz1.x-poz2.x,2)+pow(poz1.y-poz2.y,2)))/(m2*scale);
    result=sf::Vector2f((poz1.x-poz2.x)*k,(poz1.y-poz2.y)*k);
    o2->addVelocity(result);
}
bool colisions(Obj *o1, Obj *o2)
{
    if(pow(o1->getPosition().x-o2->getPosition().x,2)+pow(o1->getPosition().y-o2->getPosition().y,2)>pow(o1->getRadius()+o2->getRadius(),2))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void makeBound(Obj *o1, Obj *o2)
{
    sf::Vector2f v1 = o1->getVelocity();
    sf::Vector2f v2 = o2->getVelocity();
    float m1 = o1->getMass();
    float m2 = o2->getMass();

    o1->setVelocity(sf::Vector2f((((m1-m2)/(m1+m2))*v1.x)+(((2*m2)/(m1+m2))*v2.x),(((m1-m2)/(m1+m2))*v1.y)+(((2*m2)/(m1+m2))*v2.y)));
    o2->setVelocity(sf::Vector2f((((m2-m1)/(m2+m1))*v2.x)+(((2*m1)/(m2+m1))*v1.x),(((m2-m1)/(m2+m1))*v2.y)+(((2*m1)/(m2+m1))*v1.y)));


}

int main()
{
    //Add vaalues
    bool presed = 0;
    bool pause = 1;
    bool check = 0;
    int mouseX = 0;
    int mouseY = 0;
    int mouseXnow = 0;
    int mouseYnow = 0;

    float massM = 100;
    sf::Font roboto;
    roboto.loadFromFile("Roboto-Light.ttf");
    sf::Text zapisText;
    zapisText.setFont(roboto);
    zapisText.setCharacterSize(30);
    zapisText.setStyle(zapisText.Bold);
    zapisText.setColor(sf::Color(255,122,55));


    // Create the main window
    sf::Vector2f viewsize(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height);
    sf::RenderWindow app(sf::VideoMode(viewsize.x,viewsize.y), "SFML window",sf::Style::None);
    app.setFramerateLimit(30);


    // View
    sf::View camera(sf::Vector2f(0,0),viewsize);////320   200
    app.setView(camera);

    float viewScale = 1;
    // Background
    //sf::Texture texture;
    //texture.loadFromFile("background.png");
    //sf::Sprite background;
    //texture.setRepeated(true);
    //background.setTexture(texture);
    //background.setTextureRect(sf::IntRect(0, 0, 100000, 100000));

    //background.setPosition(-500000,-500000);
    // Sprites
    std::vector<Obj> vek;

/*
    Obj sprite(10, 3);
    Obj sprite1(10, 3);
    Obj sun(10, 300);

    sprite.setPosition(-150,0);
    sun.setPosition(0,0);
    sprite1.setPosition(150,0);

    sprite.addVelocity(sf::Vector2f(0,10));
    sprite1.addVelocity(sf::Vector2f(0,-10));

    sprite.setFillColor(sf::Color::Green);
    sprite1.setFillColor(sf::Color::Green);

    vek.push_back(sprite1);
    vek.push_back(sprite);
    vek.push_back(sun);
*/



    ///TESTS
// create an empty shape
sf::ConvexShape convex;

// resize it to 5 points
convex.setPointCount(5);

// define the points


    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            app.close();
        }
        // Mass counter
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            massM++;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            if(massM>1)massM--;
        }
        // Moving camera
        if (sf::Mouse::getPosition().y < 1 || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            camera.move(0,-10*viewScale);
        }
        if (sf::Mouse::getPosition().y > sf::VideoMode::getDesktopMode().height-2 || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            camera.move(0,10*viewScale);
        }
        if (sf::Mouse::getPosition().x < 1 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            camera.move(-10*viewScale,0);
        }
        if (sf::Mouse::getPosition().x > sf::VideoMode::getDesktopMode().width-2 || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            camera.move(10*viewScale,0);
        }

        //Zooming camera
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            viewScale *= 0.9;
            camera.zoom(0.9);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            viewScale *= 1.1;
            camera.zoom(1.1);
        }
        // Clear objects
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            vek.clear();
        }
        // Pause
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if(!check)
            {
            if(pause)
            {
                pause = 0;
            }else
            {
                pause = 1;
            }
            check = 1;
            }
        }
        //Make new object
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(!presed)
            {
                Obj p(sqrt(massM)*10,massM);
                p.setFillColor(sf::Color::Green);
                p.addVelocity(sf::Vector2f(0,0));
                mouseX = (int)(camera.getCenter().x - viewsize.x/2*viewScale) + sf::Mouse::getPosition(app).x*viewScale;
                mouseY = (int)(camera.getCenter().y - viewsize.y/2*viewScale) + sf::Mouse::getPosition(app).y*viewScale;
                p.setPosition((float)mouseX,(float)mouseY);
                if(!vek.empty()){
                bool good = 1;
                for(int a = 0; a<vek.size(); a++)
                {
                    if(good){
                        good = !colisions(&p,&vek[a]);
                    }
                }
                if(good){
                vek.push_back(p);
                }}else{
                    vek.push_back(p);
                    }
            }
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            presed = 1;

        }
        if(presed)
        {
            mouseXnow = (int)(camera.getCenter().x - viewsize.x/2*viewScale) + sf::Mouse::getPosition(app).x*viewScale - mouseX;
            mouseYnow = (int)(camera.getCenter().y - viewsize.y/2*viewScale) + sf::Mouse::getPosition(app).y*viewScale - mouseY;
            vek.back().setVelocity(sf::Vector2f(mouseXnow/10,mouseYnow/10));
            convex.setPoint(0, sf::Vector2f((int)(camera.getCenter().x - viewsize.x/2*viewScale) + sf::Mouse::getPosition(app).x*viewScale, (int)(camera.getCenter().y - viewsize.y/2*viewScale) + sf::Mouse::getPosition(app).y*viewScale));
            convex.setPoint(1, sf::Vector2f(mouseX+5, mouseY+5));
            convex.setPoint(2, sf::Vector2f(mouseX-5, mouseY-5));
            convex.setPoint(3, sf::Vector2f(mouseX+5, mouseY-5));
            convex.setPoint(4, sf::Vector2f(mouseX-5, mouseY+5));

        }

        if(!presed && !pause)
        {
            // Move zone
            for(int b = 0; b<vek.size(); b++)
            {
                for(int a=b+1; a<vek.size(); a++)
                {
                    gravityForce(&vek[a],&vek[b]);
                }
            }
            for(int a = 0; a<vek.size(); a++)
            {
                bool good = 1;
                for(int b = 0; b<vek.size(); b++)
                {
                    if(colisions(&vek[a],&vek[b]) && a!=b){
                        makeBound(&vek[a],&vek[b]);
                    }
                }
                vek[a].makeMove();


            }
        }

        std::ostringstream ss;
        ss << massM;
        zapisText.setString(ss.str());

        //background.setScale(5*viewScale,5*viewScale);
        // Clear screen
        app.clear(sf::Color::Black);
        //app.draw(background);
        // Font
        app.draw(zapisText);
        zapisText.setPosition(camera.getCenter().x-viewsize.x/2*viewScale,camera.getCenter().y-viewsize.y/2*viewScale);
        zapisText.setScale(viewScale,viewScale);
        // Draw the sprite
        if(presed)
        {
            app.draw(convex);
        }

        for(int a = 0; a<vek.size(); a++)
        {
            app.draw(vek[a]);
        }
        //View
        app.setView(camera);

        // Update the window
        app.display();


        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) presed = 0;
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) check = 0;
    }

    return EXIT_SUCCESS;
}
