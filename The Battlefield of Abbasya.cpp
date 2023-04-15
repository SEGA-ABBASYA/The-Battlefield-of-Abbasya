#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/window.hpp>
#include <vector>
#include <time.h>
using namespace sf;
using namespace std;

// 0 -> MainMenu
// 1 -> Choose Your Hero 
// 2 -> Options
// 3 -> Credits 
// # -> PauseMenu
// 4 -> Close



//Global Variables
float Gravity = -20.0;
float Jumpheight = 150.0f;
float deltatime = 0;
int playerindex = 0;
float timer = 0.0;
float delay = 0.15;
int attackindex = 0;
float attacktimer = 0.0;
float attackdelay = 0.1;
int index2 = 0;
float timer2 = 0.0;
float delay2 = 0.15;
int attackindex2 = 0;
float attacktimer2 = 0.0;
float attackdelay2 = 0.1;
int pagenum = 0;

struct cursor {
    Texture texture;
    Sprite sprite;

    cursor() {
        // Load the cursor texture
        texture.loadFromFile("cursor.png");

        // Create the cursor sprite
        sprite.setTexture(texture);
        sprite.setScale(2, 2);
        sprite.setOrigin(texture.getSize().x / 15, texture.getSize().y / 15);
    }

    void draw(RenderWindow& window) {
        // Set the cursor sprite's position to the mouse position
        sprite.setPosition(Vector2f(Mouse::getPosition(window)));
        // Set the mouse cursor to be hidden
        window.setMouseCursorVisible(false);
        // Draw the cursor sprite
        window.draw(sprite);
    }
}cur;

int cursor_select(Text* arr, RenderWindow& mywindow)
{
    Mouse mouse;
    for (int i = 0; i < 6; i++)
    {

        if (arr[i].getGlobalBounds().contains(mouse.getPosition(mywindow).x, mouse.getPosition(mywindow).y))
        {
            arr[i].setFillColor(Color::Red);

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                arr[i].setFillColor(Color::White);
                return i;
            }
        }
        else
        {
            arr[i].setFillColor(Color::White);
        }
    }
    return 0;
}

void MainMenu(RenderWindow& mainwindow)
{
    // Create the menu items
    Font menufont;
    menufont.loadFromFile("ArcadeClassic.ttf");

    Text select[6];
    select[0].setFont(menufont);
    select[0].setString("The Battlefield of Abbasya");
    select[0].setCharacterSize(60);
    select[0].setFillColor(Color{ 255,204,0 });
    select[0].setPosition(300, 100);

    select[1].setFont(menufont);
    select[1].setFillColor(Color{ 255,204,0 });
    select[1].setString("FIGHT!");
    select[1].setCharacterSize(60);
    select[1].setPosition(300, 200);

    select[2].setFillColor(Color{ 255,204,0 });
    select[2].setString("Options");
    select[2].setCharacterSize(60);
    select[2].setFont(menufont);
    select[2].setPosition(300, 250);

    select[3].setFont(menufont);
    select[3].setFillColor(Color{ 255,204,0 });
    select[3].setString("Credits");
    select[3].setCharacterSize(60);
    select[3].setPosition(300, 300);

    select[4].setFont(menufont);
    select[4].setFillColor(Color{ 255,204,0 });
    select[4].setString("Exit");
    select[4].setCharacterSize(60);
    select[4].setPosition(300, 350);

    while (mainwindow.isOpen())
    {

        //cout << pagenum << "\n";

        // Handle events
        sf::Event event;
        while (mainwindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mainwindow.close();
            }

        }

        // select which window
        pagenum = cursor_select(select, mainwindow);

        if (pagenum != 0) { return; }

        // Clear the window
        mainwindow.clear();

        // Draw the menu items
        for (int i = 0; i < 5; i++)
        {
            mainwindow.draw(select[i]);
        }

        // Draw the cursor sprite in the struct;
        cur.draw(mainwindow);

        // Display the window
        mainwindow.display();

    }
}

//p1 -> 0
//p2 -> 0

void game(int win1, int win2, RenderWindow& window);

void Options(RenderWindow& optionwindow)
{
    Font optionfont;
    optionfont.loadFromFile("ArcadeClassic.ttf");
    Text option;
    option.setFont(optionfont);
    option.setString("The Battlefield of Abbasya");
    option.setCharacterSize(60);
    option.setFillColor(Color{ 255,204,0 });
    option.setPosition(300, 100);

    while (optionwindow.isOpen())
    {

        //cout << pagenum << "\n";

        // Handle events
        sf::Event event;
        while (optionwindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                optionwindow.close();
            }

        }

        // select which window
        //pagenum = cursor_select(select, optionwindow);

        if (pagenum != 2) { return; }

        // Clear the window
        optionwindow.clear();

        // Draw the menu items
        optionwindow.draw(option);
        // Draw the cursor sprite in the struct;
        cur.draw(optionwindow);

        // Display the window
        optionwindow.display();
    }
}

void PauseMenu(RenderWindow& mainwindow) {}
void Credits(RenderWindow& mainwindow) {}

struct Hitbox
{
    RectangleShape attack;
    RectangleShape player;

    //function for setting the properties of a hitbox
    void sethitbox(Sprite& w, RectangleShape& x, float y, float z, Color l) {
        x.setSize(Vector2f(y, z));
        x.setFillColor(l);
        x.setPosition(w.getPosition().x, w.getPosition().y + 10);
        x.setOrigin(y / 2, -6);
    }
};
struct player {
    string name;
    int health = 100;
    Vector2f velocity{ 0,0 };
    Sprite sprite;
    Hitbox hitbox;
    bool grounded = false, attackbool = false, hitbool = false;

}player1, player2;
struct plates {
    RectangleShape platrec;

    //function for setting the properties of the plates
    void plat_set(Texture& imag, RectangleShape& sh_1, float x1, float x2, int x3, int x4, int x5, int x6) {
        sh_1.setSize(Vector2f(x1, x2));
        sh_1.setPosition(x3, x4);
        sh_1.setTexture(&imag);
        sh_1.setScale(x5, x6);
    }

}plt1, plt2, plt3, plt4,plt5,plt6;

//function for defining health bar textures
void init_health_bar();

//function for updating health bar according to player's health
int update_healthbar(int health);

//function for setting setting initial properties to a player
void setprop(Sprite&, Texture&, int, int, int);

//function for checking the colliding the hitbox of attack with the hitbox of player
bool intersection(RectangleShape&, RectangleShape&);

//function for checking the colliding the hitbox of player and the plates
bool platecoliode_1(RectangleShape&, RectangleShape&);

Texture hp_bar[6];

int main()
{
    RenderWindow get_window(VideoMode(1280, 720), "The Battlefield of Abbasya");
    get_window.setFramerateLimit(60);

    while (get_window.isOpen())
    {
        cout << pagenum << "\n\n";

        MainMenu(get_window);
        if (pagenum == 0) { MainMenu(get_window); }
        else if (pagenum == 1) { game(0, 0, get_window); }
        else if (pagenum == 2) { Options(get_window); }
        //else if (pagenum == ) { PauseMenu(get_window); }
        //else if (pagenum == 3) { Credits(get_window); }
        else if (pagenum == 4) { get_window.close(); }
    }
    return 0;
}

//function definition above

void init_health_bar()
{
    Texture Hp100;
    Texture Hp80;
    Texture Hp60;
    Texture Hp40;
    Texture Hp20;
    Texture Hp00;

    Hp100.loadFromFile("health_bar/health100.png");
    Hp80.loadFromFile("health_bar/health80.png");
    Hp60.loadFromFile("health_bar/health60.png");
    Hp40.loadFromFile("health_bar/health40.png");
    Hp20.loadFromFile("health_bar/health20.png");
    Hp00.loadFromFile("health_bar/health00.png");

    hp_bar[0] = Hp00;
    hp_bar[1] = Hp20;
    hp_bar[2] = Hp40;
    hp_bar[3] = Hp60;
    hp_bar[4] = Hp80;
    hp_bar[5] = Hp100;
}

int update_healthbar(int health)
{
    if (health == 80)
    {
        return 4;
    }
    else if (health == 60)
    {
        return 3;
    }
    else if (health == 40)
    {
        return 2;
    }
    else if (health == 20)
    {
        return 1;
    }
    else if (health == 0)
    {
        return 0;
    }
    return -1;
}

void setprop(Sprite& x, Texture& y, int z, int l, int m) {

    x.setTexture(y);
    x.setOrigin(60, 40);
    x.setPosition(l, m);
    x.setTextureRect(IntRect(0, 0, 120, 80));
    x.setScale(z, 3);
}

bool intersection(RectangleShape& x, RectangleShape& y) {
    if (x.getGlobalBounds().intersects(y.getGlobalBounds()))
        return true;
    else
        return false;
}

bool platecoliode_1(RectangleShape& player_x, RectangleShape& plat_y1) {
    if (player_x.getGlobalBounds().intersects(plat_y1.getGlobalBounds()) &&
        player_x.getGlobalBounds().top + player_x.getGlobalBounds().height - 15 < plat_y1.getGlobalBounds().top)
    {
        return true;
    }
    else {
        return false;
    }
}

void game(int win1, int win2, RenderWindow& window)
{

    Clock gameclock;
    int arr_index = 5;

    srand(time(0));

    //Textures
    Texture Floor;
    Texture Jumping;
    Texture Jumping2;
    Texture Running2;
    Texture Running;
    Texture Idle;
    Texture Idle2;
    Texture Fall;
    Texture Fall2;
    Texture Back[2];
    Texture Attacking;
    Texture Attacking2;
    Texture Hit;
    Texture Hit2;
    Texture P1_HealthBar_Texture;
    Texture P2_HealthBar_Texture;
    Font ourFont;
    Texture plateform_1;
    Texture plateform_2;
    Texture plateform_3;

    // call init_health_bar once in the beginning of the game
    init_health_bar();
    ourFont.loadFromFile("ArcadeClassic.ttf");
    Back[0].loadFromFile("Background.jpg");
    Back[1].loadFromFile("background2.jpg");
    Idle.loadFromFile("_Idle.png");
    Idle2.loadFromFile("Idle2.png");
    Running2.loadFromFile("Run2.png");
    Running.loadFromFile("Running Animation.png");
    Jumping.loadFromFile("_Jump.png");
    Jumping2.loadFromFile("Jump2.png");
    Fall.loadFromFile("_Fall.png");
    Fall2.loadFromFile("_Fall2.png");
    Hit.loadFromFile("_Hit.png");
    Hit2.loadFromFile("Hit2.png");
    Floor.loadFromFile("Bricks_01.png");
    Floor.setRepeated(true);
    Attacking.loadFromFile("_Attack.png");
    Attacking2.loadFromFile("Attack2.png");
    plateform_1.loadFromFile("firstplate.png");
    plateform_2.loadFromFile("secondplate.png");
    plateform_3.loadFromFile("thirdplate.png");

    Event e;

    Sprite background(Back[win1+win2]);

    //setting prop to plates
    plt1.plat_set(plateform_1, plt1.platrec, 150, 50, 1000, 450, 1, 1);
    plt2.plat_set(plateform_2, plt2.platrec, 450, 50, 400, 400, 1, 1);
    plt3.plat_set(plateform_3, plt3.platrec, 150, 50, 100, 450, 1, 1);
    plt4.plat_set(plateform_2, plt4.platrec, 1280, 50, 0, 650, 1, 1);
    if (win1 + win2 == 1) {
        plt1.plat_set(plateform_1, plt1.platrec, 150, 50, 1000, 450, 1, 1);
        plt2.plat_set(plateform_2, plt2.platrec, 450, 50, 400, 400, 1, 1);
        plt3.plat_set(plateform_3, plt3.platrec, 150, 50, 100, 450, 1, 1);
    }
    if (win1 + win2 == 2) {
        plt1.plat_set(plateform_1, plt1.platrec, 150, 50, 500, 450, 1, 1);
        plt2.plat_set(plateform_2, plt2.platrec, 450, 50, 300, 400, 1, 1);
        plt3.plat_set(plateform_3, plt3.platrec, 150, 50, 50, 450, 1, 1);
    }

    //Player 1 health bar prop
    RectangleShape p1_healthBar(Vector2f(305.f, 100.f));
    p1_healthBar.setScale(0.8f, 0.7f);
    p1_healthBar.setPosition(50, 50);
    p1_healthBar.setOrigin(p1_healthBar.getPosition().x / 2, p1_healthBar.getPosition().y / 2);
    P1_HealthBar_Texture = hp_bar[arr_index];
    p1_healthBar.setTexture(&P1_HealthBar_Texture);
    player1.health = 100;

    //Player 2 health bar prop
    RectangleShape p2_healthBar(Vector2f(305.f, 100.f));
    p2_healthBar.setScale(-0.8f, 0.7f);
    p2_healthBar.setPosition(895, 50);
    p2_healthBar.setOrigin(p2_healthBar.getPosition().x / 2, p2_healthBar.getPosition().y / 2);
    P2_HealthBar_Texture = hp_bar[arr_index];
    p2_healthBar.setTexture(&P2_HealthBar_Texture);
    player2.health = 100;

    //Players initial prop
    setprop(player1.sprite, Idle, 3, 320, 480);
    setprop(player2.sprite, Idle2, -3, 960, 480);

    //Hitboxes initial prop
    player1.hitbox.sethitbox(player1.sprite, player1.hitbox.attack, 140.f, 40.f, Color::Yellow);
    player2.hitbox.sethitbox(player2.sprite, player2.hitbox.attack, 140.f, 40.f, Color::Yellow);
    player1.hitbox.sethitbox(player1.sprite, player1.hitbox.player, 30.f, 115.f, Color::Blue);
    player2.hitbox.sethitbox(player2.sprite, player2.hitbox.player, 30.f, 115.f, Color::Blue);
    player1.hitbox.attack.setOrigin(0, 0);
    player2.hitbox.attack.setOrigin(0, 0);



    window.setFramerateLimit(60);


    while (window.isOpen()) {
        gameclock.restart();

        //Gravity movement
        player1.sprite.move(0, player1.velocity.y);
        player2.sprite.move(0, player2.velocity.y);

        //Hitboxes live positioning
        player1.hitbox.player.setPosition(player1.sprite.getPosition().x, player1.sprite.getPosition().y);
        player1.hitbox.attack.setPosition(player1.sprite.getPosition().x, player1.sprite.getPosition().y);
        player2.hitbox.player.setPosition(player2.sprite.getPosition().x, player2.sprite.getPosition().y);
        player2.hitbox.attack.setPosition(player2.sprite.getPosition().x, player2.sprite.getPosition().y);

        //Player 1 Gravity and Plates
        if  (( (platecoliode_1(player1.hitbox.player, plt1.platrec))
            || (platecoliode_1(player1.hitbox.player, plt2.platrec))
            || (platecoliode_1(player1.hitbox.player, plt3.platrec))
            || (platecoliode_1(player1.hitbox.player, plt4.platrec)))
            && player1.velocity.y >= 0)
        {
            player1.velocity.y = 0;
            player1.grounded = true;
            player1.sprite.setTexture(Idle);
            if (timer < 0) {
                playerindex++;
                playerindex = playerindex % 10;
                player1.sprite.setTextureRect(IntRect((playerindex * 120), 0, 120, 80));
                timer = delay;
            }
            else
                timer -= deltatime;
        }
        else
        {
            player1.grounded = false;
            player1.velocity.y -= Gravity * deltatime;
        }

        //player 2 gravity and plates
        if  (( (platecoliode_1(player2.hitbox.player, plt1.platrec))
            || (platecoliode_1(player2.hitbox.player, plt2.platrec))
            || (platecoliode_1(player2.hitbox.player, plt3.platrec))
            || (platecoliode_1(player2.hitbox.player, plt4.platrec)))
            && player2.velocity.y >= 0)
        {
            player2.velocity.y = 0;
            player2.grounded = true;
            player2.sprite.setTexture(Idle2);
            // animation breath player 2
            if (timer2 < 0) {
                index2++;
                index2 = index2 % 10;
                player2.sprite.setTextureRect(IntRect((index2 * 120), 0, 120, 80));
                timer2 = delay;
            }
            else
                timer2 -= deltatime;
        }
        else
        {
            player2.grounded = false;
            player2.velocity.y -= Gravity * deltatime;
        }

        //Player 1 falling animation
        if (player1.velocity.y >= 0 && !player1.grounded) {
            player1.sprite.setTexture(Fall);
            if (timer < 0) {
                playerindex++;
                playerindex = playerindex % 3;
                player1.sprite.setTextureRect(IntRect((playerindex * 120), 0, 120, 80));
                timer = delay + 0.15;
            }
            else
                timer -= deltatime;
        }

        //Player 1 jumping animation
        if (player1.velocity.y < 0) {
            player1.sprite.setTexture(Jumping);
            if (timer < 0) {
                playerindex++;
                playerindex = playerindex % 3;
                player1.sprite.setTextureRect(IntRect((playerindex * 120), 0, 120, 80));
                timer = delay + 0.15;
            }
            else
                timer -= deltatime;
        }

        //Player 2 jumping animation
        if (player2.velocity.y < 0) {
            player2.sprite.setTexture(Jumping2);
            if (timer2 < 0) {
                index2++;
                index2 = index2 % 3;
                player2.sprite.setTextureRect(IntRect((index2 * 120), 0, 120, 80));
                timer2 = delay2 + 0.15;
            }
            else
                timer2 -= deltatime;
        }

        //Player 2 falling animation
        if (player2.velocity.y >= 0 && !player2.grounded) {
            player2.sprite.setTexture(Fall2);
            if (timer2 < 0) {
                index2++;
                index2 = index2 % 3;
                player2.sprite.setTextureRect(IntRect((index2 * 120), 0, 120, 80));
                timer2 = delay2 + 0.15;
            }
            else
                timer2 -= deltatime;
        }


        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
            {
                window.close();
            }
            if (e.type == Event::KeyPressed)
            {

                //player 1 Jumping button
                if (e.key.code == Keyboard::W && player1.grounded == true && !player1.attackbool && !player1.hitbool) {

                    player1.velocity.y = -10;
                    player1.sprite.move(0, player1.velocity.y - Jumpheight);
                }

                //Player 1 Attacking button
                if (e.key.code == Keyboard::X && player1.grounded == true && !player1.attackbool) {
                    player1.attackbool = true;
                    //Attacksound.play();
                    if (intersection(player1.hitbox.attack, player2.hitbox.player) && player1.attackbool && !player1.hitbool) {
                        player2.health -= 20;
                        player2.hitbool = true;
                        timer2 = 0.5f;
                        arr_index = update_healthbar(player2.health);
                        if (arr_index != -1)
                        {
                            P2_HealthBar_Texture = hp_bar[arr_index];
                            p2_healthBar.setTexture(&P2_HealthBar_Texture);
                        }
                        if (player2.health == 0 && win2 < 2 && win1 < 2)
                        {
                            cout << "p1 wins this round\n";
                            win1++;
                            game(win1, win2, window);
                        }
                    }
                }
                //player 2 Jumping button
                if (e.key.code == Keyboard::Up && player2.grounded == true && !player2.attackbool && !player2.hitbool) {

                    player2.velocity.y = -10;
                    player2.sprite.move(0, player2.velocity.y - Jumpheight);
                }

                //Player 2 Attacking button
                if (e.key.code == Keyboard::J && player2.grounded == true && !player2.attackbool && !player2.hitbool) {
                    player2.attackbool = true;
                    //Attacksound.play();
                    if (intersection(player2.hitbox.attack, player1.hitbox.player) && player2.attackbool) {
                        player1.health -= 20;
                        player1.hitbool = true;
                        timer = 0.5f;
                        arr_index = update_healthbar(player1.health);
                        if (arr_index != -1)
                        {
                            P1_HealthBar_Texture = hp_bar[arr_index];
                            p1_healthBar.setTexture(&P1_HealthBar_Texture);
                        }
                        if (player1.health == 0 && win1 < 2 && win2 < 2)
                        {
                            cout << "p2 wins this round\n";
                            win2++;
                            game(win1, win2, window);
                        }
                    }
                }
            }

        }
        if (player1.hitbool == true) {
            player1.sprite.setTexture(Hit);
            player1.sprite.setTextureRect(IntRect(0,0,120,80));
            if (timer < 0)
            {
                player1.hitbool = false;
            }
            else
                timer -= deltatime;
        }
        //I put everything in else so it cannot be done at the same time
        else
        {
            //Player 1 Attack & Movement
            if (player1.attackbool == true) {
                player1.sprite.setTexture(Attacking);

                //Player 1 Attacking Animation
                if (attacktimer < 0) {
                    attackindex++;
                    attackindex = attackindex % 4;
                    player1.sprite.setTextureRect(IntRect((attackindex * 120), 0, 120, 80));
                    attacktimer = attackdelay;
                    if (attackindex == 0)
                        player1.attackbool = false;
                }
                else {
                    attacktimer -= deltatime;
                }
            }
            //I put everything in else so it cannot be done at the same time
            else
            {
                //Player 1 moving right
                if (Keyboard::isKeyPressed(Keyboard::D) && player1.sprite.getPosition().x < (window.getSize().x - player1.sprite.getGlobalBounds().width / 100)) {
                    player1.sprite.setScale(3, 3);
                    player1.hitbox.attack.setScale(1, 1);
                    if (player1.grounded == true) {
                        player1.sprite.setTexture(Running);
                        if (timer < 0)
                        {
                            playerindex++;
                            playerindex = playerindex % 10;
                            player1.sprite.setTextureRect(IntRect((playerindex * 120), 0, 120, 80));
                            timer = delay - 0.05f;
                        }
                        else
                            timer -= deltatime;
                    }
                    player1.sprite.move(500 * deltatime, 0);
                }
                //Player 1 moving left
                if (Keyboard::isKeyPressed(Keyboard::A) && player1.sprite.getPosition().x > 0) {
                    player1.sprite.setScale(-3, 3);
                    player1.hitbox.attack.setScale(-1, 1);
                    if (player1.grounded == true) {
                        player1.sprite.setTexture(Running);
                        if (timer < 0)
                        {
                            playerindex++;
                            playerindex = playerindex % 10;
                            player1.sprite.setTextureRect(IntRect((playerindex * 120), 0, 120, 80));
                            timer = delay - 0.05f;
                        }
                        else
                            timer -= deltatime;
                    }
                    player1.sprite.move(-500 * deltatime, 0);
                }
            }
        }

        if (player2.hitbool == true) {
            player2.sprite.setTexture(Hit2);
            player2.sprite.setTextureRect(IntRect(0, 0, 120, 80));
            if (timer2 < 0)
            {
                player2.hitbool = false;
            }
            else
                timer2 -= deltatime;
        }
        else
        {
            //Player 2 Attack & Movement
            if (player2.attackbool == true) {
                player2.sprite.setTexture(Attacking2);

                //Player 2 Attacking Animation
                if (attacktimer2 < 0) {
                    attackindex2++;
                    attackindex2 = attackindex2 % 4;
                    player2.sprite.setTextureRect(IntRect((attackindex2 * 120), 0, 120, 80));
                    attacktimer2 = attackdelay2;
                    if (attackindex2 == 0) {
                        player2.attackbool = false;
                    }

                }
                else {
                    attacktimer2 -= deltatime;
                }
            }
            //I put everything in else so it cannot be done at the same time
            else
            {
                //Player 2 moving right
                if (Keyboard::isKeyPressed(Keyboard::Right) && player2.sprite.getPosition().x < (window.getSize().x - player2.sprite.getGlobalBounds().width / 100)) {
                    player2.sprite.setScale(3, 3);
                    player2.hitbox.attack.setScale(1, 1);
                    if (player2.grounded == true) {
                        player2.sprite.setTexture(Running2);
                        if (timer2 < 0)
                        {
                            index2++;
                            index2 = index2 % 10;
                            player2.sprite.setTextureRect(IntRect((index2 * 120), 0, 120, 80));
                            timer2 = delay2 - 0.05f;
                        }
                        else
                            timer2 -= deltatime;
                    }
                    player2.sprite.move(500 * deltatime, 0);
                }
                //Player 2 moving left
                if (Keyboard::isKeyPressed(Keyboard::Left) && player2.sprite.getPosition().x > 0) {
                    player2.sprite.setScale(-3, 3);
                    player2.hitbox.attack.setScale(-1, 1);
                    if (player2.grounded == true) {
                        player2.sprite.setTexture(Running2);
                        if (timer2 < 0)
                        {
                            index2++;
                            index2 = index2 % 10;
                            player2.sprite.setTextureRect(IntRect((index2 * 120), 0, 120, 80));
                            timer2 = delay2 - 0.05f;
                        }
                        else
                            timer2 -= deltatime;
                    }
                    player2.sprite.move(-500 * deltatime, 0);
                }
            }
        }
        window.clear();
        window.draw(player1.hitbox.attack);
        window.draw(player2.hitbox.attack);
        window.draw(player1.hitbox.player);
        window.draw(player2.hitbox.player);
        window.draw(background);
        window.draw(plt1.platrec);
        window.draw(plt2.platrec);
        window.draw(plt3.platrec);
        window.draw(plt4.platrec);
        window.draw(p1_healthBar);
        window.draw(p2_healthBar);
        window.draw(player1.sprite);
        window.draw(player2.sprite);
        window.display();
        deltatime = gameclock.getElapsedTime().asSeconds();
    }
}
