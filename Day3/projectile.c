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
    float x;
    float y;
} vector2;

typedef struct {
    vector2 position;
    vector2 velocity;
    float mass;
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
float mag(vector2 vector);
float theta(vector2 pos_a, vector2 pos_b);

int main(void){
    clock_t start, end;
    float seconds = 0.0f;
    float deltatime;
    float stopwatch = 0;

    worldBox2D world = {BOUND,-BOUND,-BOUND,BOUND};
    object2 ball = {{0.0f, 0.0f}, {5.0f, 0.0f}, 5.0f, 1.0f};

    object2 *objects[num_objects] = {&ball}; // TO DO: let user choose the number of objects they waant

    start = clock();

    while (true){
        end = clock();
        deltatime = ((float) (end-start) / CLOCKS_PER_SEC);
        stopwatch += deltatime;
        
        // Gravity
        for (int i = 0; i < num_objects; i++){
            objects[i]->velocity.y -= g * deltatime;
        }

        // Detect collisions between objects and boundaries & update velocities
        detect_cols(objects, num_objects, world);

        // Update positions using velocities
        move(objects, num_objects, deltatime);

        if (stopwatch >= UPDATE_FREQUENCY){
            stopwatch = 0;
            seconds += UPDATE_FREQUENCY;
            display(objects, num_objects, seconds);
        }

        start = clock();
    }
    return 0;
}

void move(object2 **objects, int num, float deltatime){
    for (int i = 0; i < num; i++){
        objects[i]->position.x += objects[i]->velocity.x * deltatime;
        objects[i]->position.y += objects[i]->velocity.y * deltatime;
    }
}

void detect_cols(object2 **objects, int num, worldBox2D world){ 
    for (int i = 0; i < num; i++){
        if (objects[i]->position.x > world.right && objects[i]->velocity.x > 0){
            objects[i]->velocity.x = objects[i]->velocity.x * - 1 * ELASTICITY;
        }
        else if (objects[i]->position.x < world.left && objects[i]->velocity.x < 0){
            objects[i]->velocity.x = objects[i]->velocity.x * -1 * ELASTICITY;
        }
        if (objects[i]->position.y > world.top && objects[i]->velocity.y > 0){
            objects[i]->velocity.y = objects[i]->velocity.y * - 1 * ELASTICITY;
        }
        else if (objects[i]->position.y < world.bottom && objects[i]->velocity.y < 0){
            objects[i]->velocity.y = objects[i]->velocity.y * - 1 * ELASTICITY;
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
    d = sqrt(((a.position.x - b.position.x) * (a.position.x - b.position.x)) + ((a.position.y - b.position.y) * (a.position.y - b.position.y)));
    d = d - (a.size + b.size); // Assuming circles;
    return d;
}

void display(object2 **objects, int num, int second){
    if (num <= 0) return;
    printf("---- Objects at second: %.1f ----\n", second);
    for (int i = 0; i < num; i++){
        printf("--Object %i:--\n", i+1);
        printf("Position\nX:%f\nY:%f\n", objects[i]->position.x, objects[i]->position.y);
        printf("Velocity:\nX:%f\nY:%f\n", objects[i]->velocity.x, objects[i]->velocity.y);
    }
    return;
}

float theta(vector2 pos_a, vector2 pos_b){ // Returns angle from a to b
    // Not calculus, just differences
    float dx = pos_b.x - pos_a.x;
    float dy = pos_b.y - pos_a.y;

    float theta = atan2f(dy,dx); // In rad
    return theta;
}