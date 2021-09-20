/** 
  * @file bglg.h
  * @author Peter Sukhov
  * @version 1.0
*/

#ifndef INCLUDE_BGLG_H
#define INCLUDE_BGLG_H

#include "renderer.h"
#include "keyboard.h"
#include "def.h"
#include "vec.h"
#include <vector>
#include <chrono>

enum BrickGameBrickType {
    nothing = 0,
    brick
};

struct BrickGameBrick {
    color clr;
    BrickGameBrickType type;
};

struct TetraminoOrientation {
	//BrickGameBrick map[5][5];
    std::vector<std::vector<BrickGameBrick>> map;
};



struct Tetramino {
	std::vector<TetraminoOrientation> orientations;
    uint64_t current_orientation;
	uvec2 pos;
};

enum Direction {
    up = 0,
	right,
	left,
	down
};



class BrickGameLG
{
private:
    Renderer *renderer;
    KeyboardHandler *kbdhandl;

    uint64_t brick_size;
    uvec2 field_pos;
    uvec2 field_size;
    std::vector<std::vector<BrickGameBrick>> field;
    std::chrono::duration<double> tick_time;
    std::chrono::system_clock::time_point last_tick;
    
    
	Tetramino stick_tetramino;
	Tetramino L_r_tetramino;
	Tetramino L_l_tetramino;
	Tetramino block_tetramino;
	Tetramino S_tetramino;
	Tetramino T_tetramino;
	Tetramino Z_tetramino;

    Tetramino current_tetramino;
    

    /** Indicates if there is only one class instance */
	static bool was_created;
    
    /** Indicates if key was released */
    bool can_input;
    

    /** Generates field at field_pos with field_size 
      * @param field_pos - field screen offset 
      * @param field_size - size of Brick Game field */
    void create_field(uvec2 field_pos, uvec2 field_size);
   
    /** Apllies gravity for brick in field at pos 
      * @param pos - position of brick to apply gravity to */
    void apply_gravity(uvec2 pos);
    
    /** Applies gravity for every brick in the field */
    void apply_gravity_for_all();
    
    /** Makes Renderer to draw brick at pos 
      * @param brick - brick to draw
      * @param pos - postion to draw brick at */
    void drawBrick(BrickGameBrick brick, uvec2 pos);

    /** Puts brick at pos
      * @param brick - brick to put
      * @param pos - position to put brick in */
    void put_brick(uvec2 pos, BrickGameBrick brick);

    /** Sets current_tetramino to randomly chosen */
    void generate_current_tetramino();

    /** Cuts current_tetramino from field */
    void cut_current_tetramino();

    /** Spawns current_tetramino in field */
    void spawn_current_tetramino();

    /** Checks if brick at pos able to move in direction d
      * @param pos - brick position
      * @param d - direction 
      * @return bool */
    bool is_brick_able_to_move(uvec2 pos, Direction d);

    /** Checks if current_tetramino able to move in direction d 
      * @param d - direction 
      * @return bool */
    bool is_current_tetramino_able_to_move(Direction d);

public:
    class MoreThenOneObjectExists{};

    /** Moves current_tetramino in specified direction
      * @param d - direction to move tetramino in */
    void move_current_tetramino(Direction d);
    
    /** Handles input */
    void handle_input();

    
    BrickGameLG(Renderer *renderer, KeyboardHandler *kbdhandl, uint64_t brick_size, uvec2 field_offset, uvec2 field_size, std::chrono::duration<double> tick_time);
    ~BrickGameLG();

    /** Necessary to run the game */
    void start();

	/** Check if timer of tick passed. Use in pair with tick() 
      * @return bool */
    bool should_tick();

    /** Logic update. |Run only when should_tick() return true| */
    void tick();

    /** Draw field screen */
    void update();
};

#endif
