#include <raylib.h>

const Color light_blue = {238, 255, 255, 255};

class Ball {
    public:
        int x, y;
        float radius;
        int speed_x, speed_y;

    void Draw() {
        DrawCircle(x, y, radius, light_blue);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if(x + radius >= GetScreenWidth() || x - radius <= 0) {
            speed_x *= -1;
        }
    }
};

class Platform: public Ball {
    public:
        int x, y, width, height, speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{(float)x, (float)y, (float)width, (float)height}, 0.8, 0, WHITE);
    }

    void Update(int ball_y) {
        if(y + height/2 > ball_y) {
            y = y - speed;
        }
        if(y + height/2 <= ball_y) {
            y = y + speed;
        }
    }
};

Ball ball;
Platform platform;

int main() {
    const int screen_width = 600;
    const int screen_height = 500;

    InitWindow(screen_width, screen_height, "First Pong");
    SetTargetFPS(60);

    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.radius = 18.5;
    ball.speed_x = 7;
    ball.speed_y = 7;

    platform.x = screen_width * 0.95;
    platform.y = screen_height * 0.4 - platform.height/2;
    platform.width = 20;
    platform.height = 90;
    platform.speed = 5;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Update
        ball.Update();
        platform.Update(ball.y);

        // Check collision
        if(CheckCollisionCircleRec(Vector2{(float)ball.x, (float)ball.y}, ball.radius, Rectangle{(float)platform.x, (float)platform.y, (float)platform.width, (float)platform.height})) {
            ball.speed_x *= -1; // Reverse the ball speed
        }

        // Draw
        ClearBackground(BLACK);
        ball.Draw();
        platform.Draw();

        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}
