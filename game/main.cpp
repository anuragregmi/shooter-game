#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

// Create the main window
RenderWindow window(sf::VideoMode(800, 600), "Shooter");

int HEIGHT,WIDTH;
bool fired;  // variable to store status of bullet fired or not
static int score;
static int life;

// shape declaration

CircleShape target;

ConvexShape gun;

CircleShape bullet;

Text scoreBoard;

Text lifeBoard;

// animates the target
void animate_target(){
    int speed = 40;
    Clock clk;
    while(window.isOpen())
    {
        // wait for 100 ms between transitions
        if(clk.getElapsedTime().asMilliseconds() > 100){
            if(target.getPosition().x + target.getRadius() > WIDTH)
            {
                target.setPosition(0-target.getRadius(),target.getPosition().y);
            }
            else{
                target.move(speed,0);
            }

            clk.restart();
        }
    }
}

// detects collision
bool checkCollision(){

    bool status = false;

    // loading positions
    int target_x = target.getPosition().x;
    int target_y = target.getPosition().y;
    int bullet_x = bullet.getPosition().x;
    int bullet_y = bullet.getPosition().y;

    // collision condition
    if(bullet_x <= target_x + target.getRadius() && bullet_x >= target_x - target.getRadius()
    && bullet_y - bullet.getRadius() <= target_y + target.getRadius() && bullet_y + bullet.getRadius()>= target_y - target.getRadius()){
        status = true;
        target.setPosition(0,target.getPosition().y);
    }
    return status;
}

// fire control
void fire(){
    Clock clk;
    bool collided = false;
    lifeBoard.setString(to_string(life));
    lifeBoard.setPosition(WIDTH - 100 ,400);
    while(bullet.getPosition().y > 100){
        // wait for 100 ms between transitions
        if(clk.getElapsedTime().asMilliseconds() > 100){

            if( bullet.getPosition().y > 100)
            {
               bullet.setPosition(bullet.getPosition().x,bullet.getPosition().y -40 );
            }

            if( checkCollision()){
                score++;
                collided = true;
            }

            clk.restart();
        }
    }
    if(!collided){
        life--;
        if(life == 0){
            lifeBoard.setString("GAME OVER");
            lifeBoard.setPosition(WIDTH - 400 ,400);
            life = 3;
        }
        else{
            lifeBoard.setString(to_string(life));
        }
    }
    bullet.setPosition(WIDTH/2,HEIGHT);
    fired = false;

}

int main()
{
    life = 3;
    fired = false;
    HEIGHT = window.getSize().y;
    WIDTH = window.getSize().x;

    // target defination
    target = CircleShape(30);
    target.setFillColor(Color::Green);
    target.setPosition(0,100);

    Thread t(&animate_target);
    t.launch();

    // gun defination
    gun = ConvexShape();
    gun.setPointCount(8);

    int gn_height = 70;
    int gn_width = 80;

    gun.setPoint(0,Vector2f(WIDTH/2 - gn_width/2,HEIGHT-gn_height));
    gun.setPoint(1,Vector2f(WIDTH/2 + gn_width/2,HEIGHT-gn_height));
    gun.setPoint(2,Vector2f(WIDTH/2 + gn_width/2,HEIGHT-gn_height/2));
    gun.setPoint(3,Vector2f(WIDTH/2 + gn_width,HEIGHT-gn_height/2));
    gun.setPoint(4,Vector2f(WIDTH/2 + gn_width,HEIGHT));
    gun.setPoint(5,Vector2f(WIDTH/2 - gn_width,HEIGHT));
    gun.setPoint(6,Vector2f(WIDTH/2 - gn_width,HEIGHT-gn_height/2));
    gun.setPoint(7,Vector2f(WIDTH/2 - gn_width/2,HEIGHT-gn_height/2));

    gun.setFillColor(Color::Green);

    // bullet defination
    bullet = CircleShape(10);
    bullet.setPosition(WIDTH/2,HEIGHT);
    bullet.setFillColor(Color::Green);
    Thread f(&fire);

    // scoreboard defination
    Font font;
    if(! font.loadFromFile("BebasNeue Bold.ttf")){
        cout << "error loading font";
    }
    scoreBoard = Text();
    scoreBoard.setFont(font);
    scoreBoard.setFillColor(Color::Green);
    scoreBoard.setCharacterSize(100);
    scoreBoard.setString("0");
    scoreBoard.setPosition(0,400);

    // lifeboard defination
    lifeBoard = Text();
    lifeBoard.setFont(font);
    lifeBoard.setFillColor(Color::Green);
    lifeBoard.setCharacterSize(100);
    lifeBoard.setString("3");
    lifeBoard.setPosition(WIDTH - 100 ,400);


    // run the program as long as window is open
    while(window.isOpen())
    {
        Event event;

        // listen to all events
        while(window.pollEvent(event))
        {

            switch(event.type)
            {
                // check if event is closed
                case Event::Closed:
                    window.close();
                    break;
                // check if any key is pressed
                case Event::KeyPressed:
                    // cout << "Key Pressed";
                    if(event.key.code == Keyboard::Space){
                        // cout << "Space";
                        if(! fired){
                            f.launch();
                            fired = true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        // set background to black
        window.clear(Color::Black);

        // drawing components
        window.draw(target);
        window.draw(gun);
        window.draw(bullet);
        window.draw(scoreBoard);
        window.draw(lifeBoard);

        scoreBoard.setString(to_string(score));
        // displaying components
        window.display();

    }

    return EXIT_SUCCESS;
}
