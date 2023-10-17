#pragma once

#define INTRO_SCENE_BACKGROUND_FILEPATH "Output\\res\\Intro_Background.png"
#define INTRO_SHOW_TIME 3.0f

#define MAIN_SCENE_TITLE_FILEPATH "Output\\res\\title.png"
#define MAIN_SCENE_PLAYBUTTON_FILEPATH "Output\\res\\PlayButton.png"
#define MAIN_SCENE_BACKGROUND_FILEPATH "Output\\res\\sky.png"
#define LAND_FILEPATH "Output\\res\\land.png"

#define PIPE_UP_FILEPATH "Output\\res\\PipeUp.png"
#define PIPE_DOWN_FILEPATH "Output\\res\\PipeDown.png"
#define PIPE_MIDDLE_FILEPATH "Output\\res\\InvisibleScoringPipe.png"
#define PIPE_MOVE_SPEED 200.0f
#define PIPE_RAND_VALUE 200.0f
#define PIPE_SPAWN_FREQUENCY 2.0f


// ==================== Bird ====================
#define BIRD_ANIM1_FILEPATH "Output\\res\\bird-01.png" 
#define BIRD_ANIM2_FILEPATH "Output\\res\\bird-02.png" 
#define BIRD_ANIM3_FILEPATH "Output\\res\\bird-03.png" 
#define BIRD_ANIM4_FILEPATH "Output\\res\\bird-04.png"

#define BIRD_ANIMATION_DURATION 0.4f
#define GRAVITY			200.0f
#define FLYING_SPEED	150.0f
#define FLYING_DURATION 0.25f
#define ROTATE_SPEED	100.0f

// =================================================

#define FONT_SCORE_FILEPATH "Output\\fonts\\FlappyFont.ttf"

// =================================================

#define GAME_OVER_BODY_FILEPATH "Output\\res\\Game-Over-Body.png"
#define GAME_OVER_TITLE_FILEPATH "Output\\res\\Game-Over-Title.png"

#define HIT_SOUND_FILEPATH "Output\\audio\\Hit.wav"
#define POINT_SOUND_FILEPATH "Output\\audio\\Point.wav"
#define WING_SOUND_FILEPATH "Output\\audio\\Wing.wav"

#define AI_BIRD "Output\\res\\Bird16.png"
#define AI_SCENE "Output\\res\\Background.png"
#define AI_PIPE "Output\\res\\Pipes16.png"

// bg size
const int SCREEN_HEIGHT = 320;
const int SCREEN_WIDTH = 180;
const int PIPE_SPEED = 1;
const int BIRD_SPEED = 1;
const int GAP_SIZE = 64;
const int PIPE_INDENT = 32;
const int GROUND_Y = 288;
const int BIRD_SIZE = 16;
const int TIMER_DURATION = 128;
const float AI_GRAVITY = 0.25f;
const float FLIP_SPEED = -4.f;
const int BIRD_START_X = 37;

const int TOTAL_INPUT_NODE = 3;
const int TOTAL_HIDDEN_NODE = 4;
const int TOTAL_OUTPUT_NODE = 1;
const int MUTATION_PROBABILITY = 64;
//돌연변이 확률

enum class BIRDSTATE
{
	UP, DOWN, IDLE, FLY, FALL
};