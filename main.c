#include <raylib.h>

#define CORNFLOWERBLUE (Color){ 100, 149, 237 }

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 500

#define BEAT_COUNT    4

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "metronome");
    InitAudioDevice();
    Sound tick_sound = LoadSound(TextFormat("%s/assets/wet.wav", GetApplicationDirectory()));

    int bpm = 60;
    double beat_interval = 60.0 / bpm;
    int current_beat = 0;
    
    // Used to transform the center thing
    float wide = 100.0f, narrow = 10.0f;
    float cur_w = wide, cur_h = narrow;
    float tgt_w = narrow, tgt_h = wide;


    SetTargetFPS(60);

    double time_begin = GetTime();

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        // Beat time
        if (GetTime() - time_begin >= beat_interval) {
            PlaySound(tick_sound);
            time_begin = GetTime();

            float tmp = tgt_w;
            tgt_w = tgt_h;
            tgt_h = tmp;

            current_beat = (current_beat + 1) % BEAT_COUNT;
        }
        
        // Center animation
        float anim_time = bpm * 0.1f;
        cur_w += (tgt_w - cur_w) * anim_time * dt;
        cur_h += (tgt_h - cur_h) * anim_time * dt;

        Rectangle arm = {
            .x      = WINDOW_WIDTH  / 2.0f - cur_w / 2.0f,
            .y      = WINDOW_HEIGHT / 2.0f - cur_h / 2.0f,
            .width  = cur_w,
            .height = cur_h,
        };

        if (IsKeyPressed(KEY_UP) && bpm < 300) {
            bpm ++;
            beat_interval = 60.0 / bpm;
        }
        if (IsKeyPressed(KEY_DOWN) && bpm > 30) {
            bpm --;
            beat_interval = 60.0 / bpm;
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            if (bpm >= 290) {
                bpm = 300;
            } else {
                bpm += 10;
            }
            beat_interval = 60.0 / bpm;
        }
        if (IsKeyPressed(KEY_LEFT) && bpm > 30) {
            if (bpm <= 40) {
                bpm = 30;
            } else {
                bpm -= 10;
            }
            beat_interval = 60.0 / bpm;
        }

        BeginDrawing();
            ClearBackground(CORNFLOWERBLUE);
            
            // BPM display
            const char *bpm_text = TextFormat("%i", bpm);
            int text_width = MeasureText(bpm_text, 60);
            DrawText(bpm_text, WINDOW_WIDTH / 2 - text_width / 2, 100, 60, WHITE);
            
            // Center thing display
            DrawRectangleRec(arm, WHITE);
            
            // Beat counts display
            int circle_r = 10;
            int dash_w   = 20;
            int dash_h   = 4;
            int spacing  = 40;
            int total_w  = BEAT_COUNT * dash_w + (BEAT_COUNT - 1) * spacing;
            int start_x  = WINDOW_WIDTH / 2 - total_w / 2;
            int indicator_y = 400;

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
