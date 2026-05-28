#include <raylib.h>
#define CORNFLOWERBLUE (Color){ 100, 149, 237 }
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 500
#define LERP_SPEED    4.0f
#define BEAT_COUNT    4

typedef struct {
    int bpm;
} Metronome;

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "metronome");
    InitAudioDevice();
    Sound tick_sound = LoadSound("tick.mp3");

    Metronome metronome = { .bpm = 60 };
    double beat_interval = 60.0 / metronome.bpm;

    float wide = 100.0f, narrow = 10.0f;
    float cur_w = wide, cur_h = narrow;
    float tgt_w = narrow, tgt_h = wide;

    int current_beat = 0;

    SetTargetFPS(60);

    double time_begin = GetTime();

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (GetTime() - time_begin >= beat_interval) {
            PlaySound(tick_sound);
            time_begin = GetTime();

            float tmp = tgt_w;
            tgt_w = tgt_h;
            tgt_h = tmp;

            current_beat = (current_beat + 1) % BEAT_COUNT;
        }

        cur_w += (tgt_w - cur_w) * LERP_SPEED * dt;
        cur_h += (tgt_h - cur_h) * LERP_SPEED * dt;

        Rectangle arm = {
            .x      = WINDOW_WIDTH  / 2.0f - cur_w / 2.0f,
            .y      = WINDOW_HEIGHT / 2.0f - cur_h / 2.0f,
            .width  = cur_w,
            .height = cur_h,
        };

        if (IsKeyPressed(KEY_UP) && metronome.bpm < 300) {
            metronome.bpm ++;
            beat_interval = 60.0 / metronome.bpm;
        }
        if (IsKeyPressed(KEY_DOWN) && metronome.bpm > 30) {
            metronome.bpm --;
            beat_interval = 60.0 / metronome.bpm;
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            if (metronome.bpm >= 290) {
                metronome.bpm = 300;
            } else {
                metronome.bpm += 10;
            }
            beat_interval = 60.0 / metronome.bpm;
        }
        if (IsKeyPressed(KEY_LEFT) && metronome.bpm > 30) {
            if (metronome.bpm <= 40) {
                metronome.bpm = 30;
            } else {
                metronome.bpm -= 10;
            }
            beat_interval = 60.0 / metronome.bpm;
        }

        BeginDrawing();
            ClearBackground(CORNFLOWERBLUE);

            const char *bpm_text = TextFormat("%i", metronome.bpm);
            int text_width = MeasureText(bpm_text, 60);
            DrawText(bpm_text, WINDOW_WIDTH / 2 - text_width / 2, 100, 60, WHITE);

            DrawRectangleRec(arm, WHITE);

            int   circle_r  = 10;
            int   dash_w    = 20;
            int   dash_h    = 4;
            int   spacing   = 40;
            int   total_w   = BEAT_COUNT * dash_w + (BEAT_COUNT - 1) * spacing;
            int   start_x   = WINDOW_WIDTH / 2 - total_w / 2;
            int   indicator_y = 400;

            for (int i = 0; i < BEAT_COUNT; i++) {
                int cx = start_x + i * (dash_w + spacing) + dash_w / 2;
                if (i == current_beat) {
                    DrawCircle(cx, indicator_y, circle_r, WHITE);
                } else {
                    DrawRectangle(cx - dash_w / 2, indicator_y - dash_h / 2, dash_w, dash_h, LIGHTGRAY);
                }
            }

        EndDrawing();
    }

    UnloadSound(tick_sound);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
