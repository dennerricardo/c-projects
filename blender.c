#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define MIN_SPEED 0
#define MAX_SPEED 10

typedef struct 
{
    int speed;
    bool full;
} Blender ;

static void check_invariant(const Blender *b){
    assert(b->speed >= MIN_SPEED && b->speed <= MAX_SPEED);
    assert(b->full || b->speed == 0);
}

void blender_init(Blender *b){
    b->speed = 0;
    b->full = false;
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

void setSpeed(Blender *b, int x){
    check_invariant(b);
    assert(x >= MIN_SPEED && x <= MAX_SPEED);
    int delta = x - b->speed;
    assert(delta == 1 || delta == -1);
    assert(x  == 0 || b->full);
    
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

void empty(Blender *b){
    check_invariant(b);
    assert(b->speed == 0);

    b->full = false;

    assert(!isFull(b));
    check_invariant(b);
}

int main(void){
    Blender b;
    blender_init(&b); 

    fill(&b);
    setSpeed(&b,1);
    setSpeed(&b,2);
    setSpeed(&b,3);
    setSpeed(&b,2);
    setSpeed(&b,1);
    setSpeed(&b,0);

    printf("All contract checks passed. \n");
    return 0;
}