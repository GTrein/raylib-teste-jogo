
#include <iostream>
#include <raylib.h>
#include <cmath>
#include <ctime>
Texture2D coinTexture;
Texture2D bird;
Texture2D bird2;
Texture2D bird3;
Sound coinSound;
Sound gameOverSound;
Music song;
using namespace std;
int gamepad = 0;
int score = 0;
const int screen_width = 1280;
const int screen_height = 720;
bool gameOver2 = true;
int i = 0;

const char* difficulty = nullptr;
class Target {
public:
	

	float x, y;
	
	int speed_x, speed_y;
	int radius;
	
	void Draw() {

		if (x == 0 && y == 0) {
			x = rand() % GetScreenHeight();
			y = rand() % GetScreenWidth();
		}
		
		DrawTexture(coinTexture, x-20, y-20, WHITE);

	}

	


	void Update() {

		

		if (y + radius >= GetScreenHeight() ) {
			y = GetScreenHeight() - radius ;
		}
		if (y - radius <= 0) {
			y = radius;
		}
		if (x + radius >= GetScreenWidth()) {
			x = GetScreenWidth() - radius;
		}
		if (x - radius <= 0) {
			x = radius;
		}
		
	

	}


};


class Player {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;
	
	void Draw() {
		
		
		switch (i) {
		case 0:
			DrawTexture(bird, x - 25, y - 25, WHITE);
			break;
		case 1:
			DrawTexture(bird3, x - 25, y - 25, WHITE);
			break;
		case 2:
			DrawTexture(bird2, x - 25, y - 25, WHITE);
			break;

		}
	
			
	}

	void Update() {
		
	

		if (y + radius >= GetScreenHeight() ) {
			y = GetScreenHeight() - radius ;
		}
		if (y - radius <= 0) {
			y = radius;
		}
		if (x + radius >= GetScreenWidth() ) {
			x = GetScreenWidth() - radius;
		}
		if (x - radius <= 0) {
			x = radius;
			
		}
	
		

		if (IsKeyDown(KEY_W) or IsKeyDown(KEY_UP))
		{
			y -= speed_y * GetFrameTime() *60;
		}
		if (IsKeyDown(KEY_S) or IsKeyDown(KEY_DOWN))
		{
			y += speed_y * GetFrameTime() * 60;
		}
		if (IsKeyDown(KEY_D) or IsKeyDown(KEY_RIGHT))
		{
			x += speed_x * GetFrameTime() * 60;
		}
		if (IsKeyDown(KEY_A)or IsKeyDown(KEY_LEFT))
		{
			x -= speed_x * GetFrameTime() * 60;
		}
	

		
	}
	

};
Player player;
Target target;



class Enemy {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;



	void Draw() {
		
		DrawCircleGradient(x, y, radius, RED, BLACK);
		
	}

	void Update() {
		


		if (y + radius >= GetScreenHeight()) {
			y = GetScreenHeight() - radius;
		}
		if (y - radius <= 0) {
			y = radius;
		}
		if (x + radius >= GetScreenWidth()) {
			x = GetScreenWidth() - radius;
		}
		if (x - radius <= 0) {
			x = radius;
		}

		if (player.y < y)
		{
			y -= speed_y * GetFrameTime() * 60;
		}
		if (player.y > y)
		{
			y += speed_y * GetFrameTime() * 60;
		}
		if (player.x > x)
		{
			x += speed_x * GetFrameTime() * 60;
		}
		if (player.x < x)
		{
			x -= speed_x * GetFrameTime() * 60;
		}



	}


};

class Enemy2 {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;



	void Draw() {

		DrawCircleGradient(x, y, radius, BLACK, RED);

	}

	void Update() {

		y += speed_y;
		x += speed_x;
		if (y + radius >= GetScreenHeight()) {
			y = GetScreenHeight() - radius;
		}
		if (y - radius <= 0) {
			y = radius;
		}
		if (x + radius >= GetScreenWidth()) {
			x = GetScreenWidth() - radius;
		}
		if (x - radius <= 0) {
			x = radius;
		}

		if (x + radius >= GetScreenWidth()||x - radius <= 0)
		{
			speed_x *= -1;
		}

		if (y + radius >= GetScreenHeight()||y - radius <= 0)
		{
			speed_y *= -1;
		}




	}


};


Enemy enemy;
Enemy2 enemy2;

int distance2() {
	int distanceX2 = player.x - enemy.x;
	int distanceY2 = player.y - enemy.y;

	return sqrt(distanceX2 * distanceX2 + distanceY2 * distanceY2);
}

bool circleOverlap2() {
	int radius2 = player.radius + enemy.radius;

	if (distance2() < radius2-4) {
		return true;
	}
	else {
		return false;
	}

}


int distance() {
	int distanceX = player.x - target.x;
	int distanceY = player.y - target.y;

	return sqrt(distanceX * distanceX + distanceY * distanceY);
}

bool circleOverlap() {
	int radius = player.radius + target.radius;

	if (distance() < radius){
		return true;
	}
	else{
		return false;
	}

}

int distance3() {
	int distanceX = player.x - enemy2.x;
	int distanceY = player.y - enemy2.y;

	return sqrt(distanceX * distanceX + distanceY * distanceY);
}

bool circleOverlap3() {
	int radius = player.radius + enemy2.radius;

	if (distance3() < radius) {
		return true;
	}
	else {
		return false;
	}

}



void spawnTarget() {
	

	do {
		target.x = rand() % GetScreenWidth();
		target.y = rand() % GetScreenHeight();
	} while (distance() < 200);
	

}


void gameOver() {
	i = rand() % 3;
	PlaySound(gameOverSound);
		while(!IsKeyPressed(KEY_SPACE)){
			BeginDrawing();
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), DARKGRAY);
		DrawText("Game Over", GetScreenWidth() / 3, GetScreenHeight() / 2 - 60, 40, ORANGE);
		DrawText(difficulty, GetScreenWidth() / 3, GetScreenHeight() / 2 +110, 40, ORANGE);
		DrawText("Press SPACE BAR to continue", GetScreenWidth() / 3, GetScreenHeight() / 2, 30, ORANGE);
		DrawText(TextFormat("Score: %03i", score), GetScreenWidth() / 3, GetScreenHeight() / 2 + 60, 30, ORANGE);
		EndDrawing();
	};
		player.radius = 20;
		player.x = screen_width / 2;
		player.y = screen_height / 2;
		player.speed_x = 10;
		player.speed_y = 10;
		target.radius = 20;
		target.speed_x = 10;
		target.speed_y = 10;
		enemy.radius = 20;
		enemy2.radius = 20;
		enemy2.speed_x = 1;
		enemy2.speed_y = 1;
		gameOver2 = true;
		score = 0;
		return;


		
		
		


}

int main() {
	float timePlayed = 0.0f;

	
	
	srand(time(0));
	player.radius = 20;
	player.x = screen_width / 2;
	player.y = screen_height / 2;
	player.speed_x = 10;
	player.speed_y = 10;
	target.radius = 20;
	target.speed_x = 10;
	target.speed_y = 10;
	enemy.radius = 20;
	
	enemy2.radius = 20;
	enemy2.speed_x = 1;
	enemy2.speed_y = 1;
	
	SetTargetFPS(200);

	
	InitWindow(screen_width, screen_height, "Passaro de 1 real"); 
	InitAudioDevice();

	song = LoadMusicStream("assets/song.ogg");
	coinSound = LoadSound("assets/coin.mp3");
	gameOverSound = LoadSound("assets/gameover.mp3");
	coinTexture = LoadTexture("assets/coin.png");
	bird = LoadTexture("assets/player.png");
	bird2 = LoadTexture("assets/player2.png");
	bird3 = LoadTexture("assets/player3.png");
	bool pause = false;
	while (!WindowShouldClose()){
		
		
		
		timePlayed = GetMusicTimePlayed(song) / GetMusicTimeLength(song);

		if (timePlayed > 1.0f) timePlayed = 1.0f;

		BeginDrawing();
		if (gameOver2 == true) {
			bool keyPressed = false;
			int escolha = 0;
			
			while (!keyPressed) {
				BeginDrawing();
				DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), DARKGRAY);
				DrawText("Get the coins and avoid the enemy", GetScreenWidth() / 3, GetScreenHeight() / 2 - 60, 40, ORANGE);
				DrawText("Press E to start a game in EASY mode", GetScreenWidth() / 3, GetScreenHeight() / 2 + 50, 30, ORANGE);
				DrawText("Press M to start a game in MEDIUM mode", GetScreenWidth() / 3, GetScreenHeight() / 2 + 100, 30, ORANGE);
				DrawText("Press H to start a game in HARD mode", GetScreenWidth() / 3, GetScreenHeight() / 2 + 150, 30, ORANGE);
				EndDrawing();

				if (IsKeyPressed(KEY_E) || IsKeyPressed(KEY_M) || IsKeyPressed(KEY_H)) {
					keyPressed = true;
					if (IsKeyPressed(KEY_E))
						escolha = 1;
						if (IsKeyPressed(KEY_M))
							escolha = 2;
							if (IsKeyPressed(KEY_H))
								escolha = 3;
				} 
				
			}

			
			switch (escolha)
			{
			case 1:
				enemy.speed_x = 4;
				enemy.speed_y = 4;
				difficulty = "Easy mode";
				break;
			case 2:
				enemy.speed_x = 6;
				enemy.speed_y = 6;
				difficulty = "Medium mode";
				break;
			case 3:
				enemy.speed_x = 8;
				enemy.speed_y = 8;
				difficulty = "Hard mode";
				break;
			}
			gameOver2 = false;

			do {
				
				enemy2.x = rand() % GetScreenHeight();
				enemy2.y = rand() % GetScreenWidth();
			} while(distance3() < 400);

			enemy.x = 20;
			enemy.y = GetScreenHeight() / 2;
		}

		UpdateMusicStream(song);
		PlayMusicStream(song);
		
		
		ClearBackground(DARKGRAY);
		enemy2.Update();
		enemy2.Draw();
		
		target.Draw();
		target.Update();
		player.Update();
		player.Draw();
		enemy.Update();
		enemy.Draw();
		
		
		DrawText(TextFormat("Score: %03i", score), 20, 20, 20, ORANGE);


		if (circleOverlap() == true) {
			spawnTarget();
			score++;
			PlaySound(coinSound);
		}

		if (circleOverlap2() == true|| circleOverlap3() == true) {
			gameOver();
		}

			
			
			
			
		

	

		EndDrawing();
	}
	UnloadMusicStream(song);
	CloseAudioDevice();
	UnloadTexture(coinTexture);
	UnloadSound(coinSound);
	UnloadTexture(bird);
	UnloadTexture(bird2);
	CloseWindow();
	return 0;
}


