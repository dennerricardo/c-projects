#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

#define MIN_SPEED 0
#define MAX_SPEED 9

typedef struct 
{
    int speed;
    bool full;
    bool onBase; 
} Blender ;

static void check_invariant(const Blender *b){
    assert(b->speed >= MIN_SPEED && b->speed <= MAX_SPEED);
    if(b-> speed > 0){
        assert(b-> full);
        assert( b-> onBase);
    }
}

void blender_init(Blender *b){
    b->speed = 0;
    b->full = false;
    b->onBase = false;
    check_invariant(b);
}

int getSpeed(const Blender *b){
    check_invariant(b);
    return b-> speed;
}

bool isFull(const Blender *b){
    check_invariant(b);
    return b-> full;
}
bool onBase(const Blender *b){
    check_invariant(b);
    return b-> onBase;
}

void setSpeed(Blender *b, int x){
    check_invariant(b);
    assert(x >= MIN_SPEED && x <= MAX_SPEED);
    assert(x  == 0 || ( b->full && b-> onBase));
    
    b-> speed = x;

    assert(getSpeed(b) == x);
    check_invariant(b);
}

void fill(Blender *b){
    check_invariant(b);
    assert(!b->full);

    b->full = true;

    assert(isFull(b));
    check_invariant(b);

}

void pour(Blender *b){
    check_invariant(b);
    assert(b->speed == 0);
    assert(b->full);
    b->full = false;
    assert(!isFull(b));
    check_invariant(b);
}

void attach(Blender *b){
    check_invariant(b);
    assert(!b->onBase);
    b->onBase = true;
    assert(onBase(b));
    check_invariant(b);
}

void detach(Blender *b){
    check_invariant(b);
    assert(b->speed == 0);
    b->onBase = false;
    assert(!onBase(b));
    check_invariant(b);
}


void print_blend_sound(int speed, char *out){
    int pos = 0;
    out[pos++] = 'R';
    for(int i = 0; i < speed; i++){
        out[pos++] = 'A';
    }
    out[pos++] = 'M';
    out[pos] = '\0';
}

// char wait_for_key(void){
//     while(!_kbhit()){
//         Sleep(20);
//     }
//     return _getch();
// }


int main(void){
    Blender b;
    blender_init(&b); 

    printf("=== Blender is ready to use ===\n");
    printf("Press 'a' to attach the base\n");
    printf("Press 'f' to fill the jar\n");
    printf("Press 1 to 9 to select the power\n");
    printf("0 to turn off\n");
    printf("Press 'r' to remove the jar from the base\n");
    printf("Press 's' to serve the juice\n");
    printf("Press 'q' to quit\n\n");
    fflush(stdout);

    char sound[16];
    bool running = true; 

    while(running){
        if (_kbhit()){
            char key = _getch();

             if (key == 'a') {
                if (b.onBase) {
                    printf("\nJar is already attached.\n");
                } else {
                    attach(&b);
                    printf("\nJar attached to base.\n");
                }
                fflush(stdout);
            }

            else if (key == 'f') {
                if (b.full) {
                    printf("\nJar is already full.\n");
                } else {
                    printf("\nFilling jar ...\n");
                    fill(&b);
                    printf("\nJar is full\n");
                }
                fflush(stdout);
            }

            if(key >= '1' && key <= '9'){
                int x = key - '0';
                if(!b.onBase || !b.full){
                    printf("\nCan't run: jar must be attached and filled.\n");
                } else {
                    setSpeed(&b, x);
                    printf("\n%d was set:\n", x);    
                }
            }
            else if (key == '0'){
                if(b.speed != 0){
                    setSpeed(&b, 0);
                }
                printf("\n0 was set:\nBlender is off\n\n");
                 fflush(stdout);
            }
            else if (key == 'r'){
                if(b.speed != 0){
                    setSpeed(&b, 0);
                } else if (!b.onBase) {
                    printf("\nJar is already off the base.\n");
                } else {
                    detach(&b);
                    printf("\n'r' was pressed\nJar removed from base.\n");
                }
                 fflush(stdout);
            }
            else if (key == 's') {
                if (b.speed != 0) {
                    printf("\nCan't pour while it's running. Press '0' first.\n");
                } else if (!b.full) {
                    printf("\nNothing to pour, the jar is already empty.\n");
                } else {
                    pour(&b);
                    printf("\n's' was pressed\nServing juice...\nJar is clear to refill\n");
                }
                fflush(stdout);
            }
            else if (key == 'q') {
                printf("\nGoodbye!\n");
                running = false;
            }
        }
        else if (b.speed > 0) {
            print_blend_sound(b.speed, sound);
            printf("%s! \n", sound);
            fflush(stdout);
            Sleep(1000);
        }
        else {
            Sleep(30); 
        }

    }

    return 0;
}