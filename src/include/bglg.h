#ifndef INCLUDE_BGLG_H
#define INCLUDE_BGLG_H

#include "renderer.h"
#include "keyboard.h"
#include "def.h"
#include "vec.h"
#include <vector>
#include <chrono>
#include <SDL2/SDL_ttf.h>

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
    // ivec bc tetramino pos might be -1 or -2 
	ivec2 pos;
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
	TTF_Font *font;
	
	uint64_t score;
	uint64_t score_per_level;
	uint64_t score_per_row;
	uint64_t score_per_instant_fall;
	uint64_t current_level;
    uint64_t brick_size;
    uvec2 field_pos;
    uvec2 field_size;
    std::vector<std::vector<BrickGameBrick>> field;
    std::chrono::duration<double> tick_time;
    std::chrono::duration<double> tick_time_change;
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
	
	/** Applies gravity for every brick in every row above specified row
	  * @param row -- apply gravity for each above that row */
	void apply_gravity_for_all_above(uint64_t row);
    
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
    
    /** Checks if row is filled with bricks
      * @param row - row to check
      * @return bool */
    bool is_row_filled(uint64_t row);
    
    /** Cuts row from field 
      * @param row - row to cut*/
    void cut_row(uint64_t row);
    
    /** Checks all the rows if they are filled, if true -- cuts them */
    void check_rows();
    
    /** Checks if all tetramino orientation's yvectrs sizes are the same
      * @param TetraminoOrientation orintation -- orientation to check */
    void check_tetramino_orientation(TetraminoOrientation tetramino_orientation);
	
	/** Pushes game onto the next level */
	void next_level();
	
	void draw_level();
public:
    class MoreThenOneObjectExists{};

    /** Moves current_tetramino in specified direction
      * @param d - direction to move tetramino in */
    void move_current_tetramino(Direction d);
    
    /** Handles input */
    void handle_input();
    

    bool is_current_tetramino_able_to_rotate();
    void rotate_current_tetramino();
	
	/** Constructor 
	  * @param Renderer *renderer -- display renderer
	  * @param TTF_Font *font -- ttf font to print info with
	  * @param KeyboardHandler *kbdhandl -- keyboard handler
	  * @param uint64_t brick_size -- brick size in pixels
	  * @param uvec2 field_offset -- brick game field offset on screen in pixels
	  * @param uvec2 field_size -- brick game field size in bicks
	  * @param double tick_time -- time between ticks in seconds 
	  * @param double tick_time_change -- how time between changes between levels 
	  * @param uint64_t score_per_level -- amount of score that is nedded for each level 
	  * @param uint64_t score_per_row -- amount of score that is filling one row gives
	  * @parma uint64_t score_per_instant_fall -- amount of score to add if player
	  * pressed SPACE and makes tetramino instantly fall */
    BrickGameLG(Renderer *renderer, TTF_Font *font,
	KeyboardHandler *kbdhandl, uint64_t brick_size, uvec2 field_offset, 
	uvec2 field_size, double tick_time, double tick_time_change, uint64_t score_per_level,
	uint64_t score_per_row, uint64_t score_per_instant_fall);

	/** Destructor */
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
