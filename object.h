// #ifndef
//
// You have seen a #define for making simple constants, but the CPP can also do 
// logic and remove sections of code. This #ifndef is "if not defined" and checks
// if there is already a #define _object_h and if there is it skips all of this code.
// I do this so that we can include this file anytime we want and not worry about
// it defining things multiple times.

// #define
//
// With the above #ifndef shielding this file from we then add the
// _object_h define so that any attempts to include it later cause 
// the above skip

#ifndef _object_h
#define _object_h
typedef enum {
  NORTH, SOUTH, EAST, WEST
} Direction;

typedef struct {
  char *description;
  int (*init) (void *self);
  void (*describe) (void *self);
  void (*destroy) (void *self);
  void *(*move) (void *self, Direction direction);
  int (*attack) (void *self, int damage);
} Object;

int Object_init(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);
void *Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);
void *Object_new(size_t size, Object proto, char *description);

// #define NEW(T,N)
//
// This makes a macro, and it works like a template function that spits out the code on the right,
// whenever you write use the macro on the left. This one is simply making a short version of the
// normal way we will call Object_new and avoids potential errors with calling ir wrong. The way
// the macro works is the T and N parameters to NEW are "injected" into the line of code on the right
// The syntax T##Proto says to "concat Proto at the end of T", so if you had NEW(Room, "Hello.") then it
// would make RoomProto there.

// #define _(N) 
//
// This macro is a bit "syntactic sugar" for the objet system and basically helps you write 
// obj->proto.blah as simply obj->_(blah). It is not necessary, but it is a fun little trick that I will 
// use later
#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

#endif
