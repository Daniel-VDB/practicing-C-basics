#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define BOUND 20
#define g 9.81f
#define ELASTICITY 1
#define num_objects 1
#define UPDATE_FREQUENCY 0.1f

// ALL VALUES MEASURED IN SI UNITS

typedef struct {
    float x_pos;
    float y_pos;
    float y_velo;
    float x_velo;
    float size; // add force components
} object2; 

typedef struct {
    float top;
    float bottom;
    float left;
    float right; 
} worldBox2D;

void move(object2 **objects, int num, float deltatime);
void detect_cols(object2 **objects, int num, worldBox2D world);
float distance(object2 a, object2 b);
void display(object2 **objects, int num, int second);

int main(void){
    clock_t start, end;
    float seconds = 0.0f;
    float deltatime;
    float stopwatch = 0;

    worldBox2D world = {BOUND,-BOUND,BOUND,-BOUND};
    object2 ball = {0.0f,0.0f,0.0f,0.0f,1.0f};

    object2 *objects[num_objects] = {&ball}; // TO DO: let user choose the number of objects they waant

    start = clock();

    while (true){
        end = clock();
        deltatime = ((float) (end-start) / CLOCKS_PER_SEC);
        stopwatch += deltatime;
        
        // Gravity
        for (int i = 0; i < num_objects; i++){
            objects[i]->y_velo -= g * deltatime;
        }

        // Determine positions
        move(objects, num_objects, deltatime);

        // Detect collisions between objects and boundaries and update velocities
        detect_cols(objects, num_objects, world);

        if (stopwatch >= UPDATE_FREQUENCY){
            stopwatch = 0;
            seconds += UPDATE_FREQUENCY;
            display(objects, 1, seconds);
        }

        start = clock();
    }
    return 0;
}

void move(object2 **objects, int num, float deltatime){
    for (int i = 0; i < num; i++){
        objects[i]->x_pos += objects[i]->x_velo * deltatime;
        objects[i]->y_pos += objects[i]->y_velo * deltatime;
    }
}

void detect_cols(object2 **objects, int num, worldBox2D world){ 
    for (int i = 0; i < num; i++){
        // To-Do: change this to be forces instead of directly updating velocity
        // + also include elasticity of collisions in calculation
        if (objects[i]->x_pos > world.right && objects[i]->x_velo > 0){
            objects[i]->x_velo = objects[i]->x_velo * - 1;
        }
        else if (objects[i]->x_pos < world.left && objects[i]->x_velo < 0){
            objects[i]->x_velo = objects[i]->x_velo * - 1;
        }
        if (objects[i]->y_pos > world.top && objects[i]->y_velo > 0){
            objects[i]->y_velo = objects[i]->y_velo * - 1;
        }
        else if (objects[i]->y_pos < world.bottom && objects[i]->y_velo < 0){
            objects[i]->y_velo = objects[i]->y_velo * - 1;
        }
        /*int j = 0;
        while (j != i && j < num){
            if (distance(*(objects[i]), *(objects[j])) <= 0){
                // bounce
                j++;
            }
        }*/
    }
}

float distance(object2 a, object2 b){
    float d;
    d = sqrt(((a.x_pos - b.x_pos) * (a.x_pos - b.x_pos)) + ((a.y_pos - b.y_pos) * (a.y_pos - b.y_pos)));
    d = d - (a.size + b.size); // Assuming circles;
    return d;
}

void display(object2 **objects, int num, int second){
    if (num <= 0) return;
    printf("---- Objects at second: %.1f ----\n", second);
    for (int i = 0; i < num; i++){
        printf("--Object %i:--\n", i+1);
        printf("Position\nX:%f\nY:%f\n", objects[i]->x_pos, objects[i]->y_pos);
        printf("Velocity:\nX:%f\nY:%f\n", objects[i]->x_velo, objects[i]->y_velo);
    }
    return;
}