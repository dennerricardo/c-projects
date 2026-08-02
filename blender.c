#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define MIN_SPEED 0
#define MAX_SPEED 10

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
    int delta = x - b-> speed;
    assert(delta == 1 || delta == -1);
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

// void empty(Blender *b){
//     check_invariant(b);
//     assert(b->speed == 0);

//     b->full = false;

//     assert(!isFull(b));
//     check_invariant(b);
// }

void print_blend_sound(int speed){
    char sound[64];
    int pos = 0;
    sound[pos++] = 'R';
    for(int i = 0; i < speed; i++){
        sound[pos++] = 'A';
    }
    sound[pos++] = 'M';
    sound[pos] = '\0';
    printf(" %2d : %s!\n", speed, sound);

}




int main(void){
    Blender b;
    blender_init(&b); 

    printf("=== Setting up the blender ===\n");
    attach(&b);
    printf("Jar attached to base.\n");
    fill(&b);
    printf("Jar filled with ingredients\n");

    printf(" === Blending (speeding up) === ");
    for(int s = 1; s <= MAX_SPEED; s++){
        setSpeed(&b,s);
        print_blend_sound(s);
    }
    printf(" === Blending (slowing down) === ");
    for(int s = MAX_SPEED -1 ; s >= 0; s--){
        setSpeed(&b,s);
        if(s > 0){
            print_blend_sound(s);           
        }
    }

    printf("  Blender stopped.\n\n");

    printf("=== Serving ===\n");
    detach(&b);
    printf("Jar removed from base.\n");
    pour(&b);
    printf("Contents poured into a glass. Enjoy!\n\n");



    printf("All contract checks passed. \n");
    return 0;
}