#include "include/bglg.h"

bool BrickGameLG::was_created = false;


BrickGameLG::
BrickGameLG(Renderer *renderer, TTF_Font *font,
KeyboardHandler *kbdhandl, uint64_t brick_size,
uvec2 field_offset, uvec2 field_size, double tick_time, double tick_time_change,
uint64_t score_per_level, uint64_t score_per_row) {
    
   	if(this->was_created) {
        throw MoreThenOneObjectExists();
	}
	
	this->renderer = renderer;
	this->font = font;
    this->kbdhandl = kbdhandl;
    this->brick_size = brick_size;
    this->tick_time = std::chrono::duration<double>(tick_time);
    this->tick_time_change = std::chrono::duration<double>(tick_time_change);
	this->score_per_level = score_per_level;
	this->score_per_row = score_per_row;
	score = 0;
	current_level = 0;
    was_created = true;
    can_input = true;
    
    const BrickGameBrick rb = {clr_red, brick};
    const BrickGameBrick gb = {clr_green, brick};
    const BrickGameBrick bb = {clr_blue, brick};
    const BrickGameBrick nb = {clr_black, nothing};

    TetraminoOrientation tmp_orientation1;
    TetraminoOrientation tmp_orientation2;
    TetraminoOrientation tmp_orientation3;
    TetraminoOrientation tmp_orientation4;
    
    /** Important: tetramino orientations must be reversed when adding
      * when adding new tetramino. IDK why. */

	tmp_orientation1 =                     {{{nb, nb, nb, nb, nb},
											 {nb, nb, rb, nb, nb},
											 {nb, nb, rb, nb, nb}, 
											 {nb, nb, rb, nb, nb},
											 {nb, nb, rb, nb, nb}}};

	tmp_orientation2 =                     {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {rb, rb, rb, rb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation3 =                     {{{nb, nb, rb, nb, nb},
											 {nb, nb, rb, nb, nb},
											 {nb, nb, rb, nb, nb}, 
											 {nb, nb, rb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation4 =                     {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, rb, rb, rb, rb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};
 
	this->stick_tetramino = {{tmp_orientation4, tmp_orientation3, tmp_orientation2, tmp_orientation1}, 0, {5, 0}};
    
	tmp_orientation4 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, gb, nb},
											 {nb, nb, gb, nb, nb}, 
											 {nb, nb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};
    
	tmp_orientation3 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, nb, nb, gb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation2 ={{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, nb, nb},
											 {nb, nb, gb, nb, nb}, 
											 {nb, gb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation1 ={{{nb, nb, nb, nb, nb},
											 {nb, gb, nb, nb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

    this->L_r_tetramino = {{tmp_orientation1, tmp_orientation2, tmp_orientation3, tmp_orientation4}, 0, {5, 0}};

	tmp_orientation4 =					   {{{nb, nb, nb, nb, nb},
											 {nb, gb, gb, nb, nb},
											 {nb, nb, gb, nb, nb}, 
											 {nb, nb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};
    
	tmp_orientation3 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, gb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation2 =                     {{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, nb, nb},
											 {nb, nb, gb, nb, nb}, 
											 {nb, nb, gb, gb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation1 =                     {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, gb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};
    this->L_l_tetramino = {{tmp_orientation1, tmp_orientation2, tmp_orientation3, tmp_orientation4}, 0, {5, 0}};

	tmp_orientation1 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, nb, bb, bb, nb}, 
											 {nb, nb, bb, bb, nb},
											 {nb, nb, nb, nb, nb}}};
    this->block_tetramino = {{tmp_orientation1}, 0, {5, 0}};
    
    
	tmp_orientation4 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, rb, rb, nb, nb}, 
											 {nb, nb, rb, rb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation3 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, rb, nb, nb},
											 {nb, rb, rb, nb, nb}, 
											 {nb, rb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

    
	tmp_orientation2 =					   {{{nb, nb, nb, nb, nb},
											 {nb, rb, rb, nb, nb},
											 {nb, nb, rb, rb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation1 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, rb, nb},
											 {nb, nb, rb, rb, nb}, 
											 {nb, nb, rb, nb, nb},
											 {nb, nb, nb, nb, nb}}};
   
    
	this->Z_tetramino = {{{tmp_orientation1, tmp_orientation2, tmp_orientation3, tmp_orientation4}}, 0, {5, 0}};

	tmp_orientation4 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, nb, rb, rb, nb}, 
											 {nb, rb, rb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation3 =					   {{{nb, nb, nb, nb, nb},
											 {nb, rb, nb, nb, nb},
											 {nb, rb, rb, nb, nb}, 
											 {nb, nb, rb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation2 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, rb, rb, nb},
											 {nb, rb, rb, nb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation1 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, rb, nb, nb},
											 {nb, nb, rb, rb, nb}, 
											 {nb, nb, nb, rb, nb},
											 {nb, nb, nb, nb, nb}}};
    
	this->S_tetramino = {{{tmp_orientation1, tmp_orientation2, tmp_orientation3, tmp_orientation4}}, 0, {5, 0}};

	tmp_orientation4 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, nb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation3 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, nb, nb},
											 {nb, gb, gb, nb, nb}, 
											 {nb, nb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation2 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, nb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation1 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, nb, nb},
											 {nb, nb, gb, gb, nb}, 
											 {nb, nb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};
    
	this->T_tetramino = {{{tmp_orientation1, tmp_orientation2, tmp_orientation3, tmp_orientation4}}, 0, {5, 0}};

    this->last_tick = std::chrono::system_clock::now();

    create_field(field_offset, field_size);
}

BrickGameLG::
~BrickGameLG() {
    was_created = false;
}

void BrickGameLG::
next_level() {
	current_level++;
	tick_time -= tick_time_change;
}

#include <SDL2/SDL.h>
void BrickGameLG::
draw_level() {
	renderer->drawLine(
	{field_pos[_x], field_pos[_y]}, 
	{field_pos[_x], (field_size[_y]) * brick_size + field_pos[_y]}, clr_white);
	
	/* Level */
	
	SDL_Surface *text_surface = TTF_RenderText_Blended(font, (std::string("Level:") 
	+ std::to_string(current_level)).c_str(),
	 {255, 255, 255, 255});
	
	if(text_surface == NULL) {
		printf("Error: cannot create surface from text: %s\n", TTF_GetError());
		exit(-1);
	}

	SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer->getSDLRenderer(), text_surface);

	if(text_texture == NULL) {
		printf("Error: cannot create texture from surface: %s\n", TTF_GetError());
		exit(-1);
	}
	
	const uint64_t font_vertical_spacing = 8;
	

	SDL_Rect dest_rect;
	dest_rect.x = 0;
	dest_rect.y = field_pos[_y];
	dest_rect.h = text_surface->h;
	dest_rect.w = text_surface->w;
	
	renderer->drawTexture(text_texture, NULL, &dest_rect);
	
	uint64_t first_surface_h = text_surface->h;
	
	text_surface = NULL;
	text_texture = NULL;
	
	/* Score */
	text_surface = TTF_RenderText_Blended(font, (std::string("Score:") 
	+ std::to_string(score)).c_str(), {255, 255, 255, 255});

	text_texture = SDL_CreateTextureFromSurface(renderer->getSDLRenderer(), text_surface);

	if(text_texture == NULL) {
		printf("Error: cannot create texture from surface: %s\n", TTF_GetError());
		exit(-1);
	}
	
	dest_rect.x = 0;
	dest_rect.y += first_surface_h + font_vertical_spacing;
	dest_rect.h = text_surface->h;
	dest_rect.w = text_surface->w;


	renderer->drawTexture(text_texture, NULL, &dest_rect);

}

void BrickGameLG::
check_tetramino_orientation(TetraminoOrientation tetramino_orientation) {
    uint64_t yvectr_size = tetramino_orientation.map[0].size();
    for(auto yvectr = tetramino_orientation.map.begin(); 
        yvectr < tetramino_orientation.map.end();
        yvectr++) {
        if(yvectr->size() != yvectr_size) {
            printf("Error: unmatching sizes of y vectors\n");
            printf("| This probably happend because of different sizes of y");
            printf("in tetramino.\n");
            printf("|>Please make sure that the y sizes of tetramino are all the same\n");
            exit(-1);
        }
    }

}

void BrickGameLG::
rotate_current_tetramino() {
    if(!is_current_tetramino_able_to_rotate()) {
        return;
    }
    cut_current_tetramino();
    if(current_tetramino.current_orientation < current_tetramino.orientations.size() - 1) {
        current_tetramino.current_orientation++;
    }else {
        current_tetramino.current_orientation = 0;
    }
    spawn_current_tetramino();
}

bool BrickGameLG::
is_current_tetramino_able_to_rotate() {
    uint64_t next_orientation_n = 0;
    if(current_tetramino.current_orientation < current_tetramino.orientations.size() - 1) {
        next_orientation_n = current_tetramino.current_orientation + 1;
    }
    TetraminoOrientation next_orientation = current_tetramino
        .orientations[next_orientation_n];
    TetraminoOrientation current_orientation = current_tetramino.
        orientations[current_tetramino.current_orientation];
    
    check_tetramino_orientation(next_orientation);
    check_tetramino_orientation(current_orientation);
    
    for(uint64_t x = 0; x < next_orientation.map.size(); x++) {
        for(uint64_t y = 0; y < next_orientation.map[0].size(); y++) {
            ivec2 absolute_pos = current_tetramino.pos + uvec2({x,y});
            if((absolute_pos[_x] >= (int64_t)field_size[_x]
               || absolute_pos[_y] >= (int64_t)field_size[_y]) && next_orientation.map[x][y].type == brick) {
                return false;
            }
            if((absolute_pos[_x] < 0
               || absolute_pos[_y] < 0) && next_orientation.map[x][y].type == brick) {
                return false;
            }
            if((absolute_pos[_x] < 0) || (absolute_pos[_y] < 0)
               || (absolute_pos[_x] > (int64_t)field_size[_x] - 1) 
               || (absolute_pos[_y] > (int64_t)field_size[_y])) {
                continue;
            }
            //FIXME: Segmentation fault below
            if(field[absolute_pos[_x]][absolute_pos[_y]].type == brick) {
                if(current_orientation.map[x][y].type != brick) {
                    if(next_orientation.map[x][y].type == brick) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool BrickGameLG::
is_brick_able_to_move(uvec2 pos, Direction d) {
    if(pos[_x] >= field_size[_x] && pos[_y] >= field_size[_y]) {
        printf("Brick position out of bounds!\n");
        printf("| In function %s\n", __func__);
        printf("| Brick position: {%lu, %lu}\n", pos[_x], pos[_y]);
        exit(-1);
    }

    if(field[pos[_x]][pos[_y]].type == nothing) return false;

    switch(d) {
        case down: 
            if(pos[_y] == field_size[_y] - 1) return false;
            if(field[pos[_x]][pos[_y] + 1].type == brick) return false;
            break;
        case right: 
            if(pos[_x] == field_size[_x] - 1) return false;
            if(field[pos[_x] + 1][pos[_y]].type == brick) return false;
            break;
        case left: 
            if(pos[_x] == 0) return false;
            if(field[pos[_x] - 1][pos[_y]].type == brick) return false;
            break;
        case up: 
            if(pos[_y] == 0) return false;
            if(field[pos[_x]][pos[_y] - 1].type == brick) return false;
            break;
    }

    return true;
}

bool BrickGameLG::
is_row_filled(uint64_t row) {
    for(uint64_t col = 0; col < field_size[_x]; col++) {
        if(field[col][row].type != brick) {
            return false;
        }
    }
    return true;
}

void BrickGameLG::
cut_row(uint64_t row) {
    for(uint64_t col = 0; col < field_size[_x]; col++) {
        field[col][row] = {clr_black, nothing};
    }
}

void BrickGameLG::
check_rows() {
    for(uint64_t row = 0; row < field_size[_y]; row++) {
        if(is_row_filled(row)) {
            cut_row(row);
            apply_gravity_for_all_above(row);
			score += score_per_row;
			if(score >= score_per_level * (current_level + 1)) {
				next_level();
			}
        }
    }
}

void BrickGameLG::
drawBrick(BrickGameBrick brick, uvec2 pos) {
    renderer->drawRect(pos, {brick_size, brick_size}, brick.clr, 1);
}

void BrickGameLG::
apply_gravity(uvec2 brick_pos) {
	if(!is_brick_able_to_move(brick_pos, down)) return;

    field[brick_pos[_x]][brick_pos[_y] + 1] = field[brick_pos[_x]][brick_pos[_y]];
    field[brick_pos[_x]][brick_pos[_y]] = {clr_black, nothing};
}


void BrickGameLG::
apply_gravity_for_all() {
    for(uint64_t xptr = 0; xptr < field_size[_x]; xptr++) {
        for(uint64_t yptr = field_size[_y]; yptr > 0; yptr--) {
            apply_gravity({xptr, yptr});
        }
    }
}

void BrickGameLG::
apply_gravity_for_all_above(uint64_t row) {
    for(uint64_t xptr = 0; xptr < field_size[_x]; xptr++) {
        for(uint64_t yptr = row; yptr > 0; yptr--) {
            apply_gravity({xptr, yptr});
        }
    }
}

void BrickGameLG::
create_field(uvec2 field_pos, uvec2 field_size) {
    this->field_pos = field_pos;
    this->field_size = field_size;
    
    /* create everything needed */
    for(uint64_t vecdx = 0; vecdx < field_size[_x]; vecdx++) {
		field.push_back(std::vector<BrickGameBrick>());
		for(uint64_t vecdy = 0; vecdy < field_size[_y]; vecdy++) {
        	field[vecdx].push_back({clr_black, nothing});
        }
    }
}

void BrickGameLG::
update() {
    uint64_t brick_posx = 0;
    uint64_t brick_posy = 0;
    for(auto ptr1 = field.begin(); ptr1 < field.end(); ptr1++) {
        for(auto ptr2 = ptr1->begin(); ptr2 < ptr1->end(); ptr2++) {
	    	uvec2 real_pos = {(brick_posx) * brick_size + field_pos[_x], (brick_posy) * brick_size + field_pos[_y]};
            drawBrick({ptr2->clr, ptr2->type}, real_pos);
	    	brick_posy++;
        }
		brick_posx++;
        brick_posy = 0;
    }
	draw_level();
}

void BrickGameLG::
handle_input() {
    
    if(should_tick()) return;

    if(can_input) {
        if(kbdhandl->isPressed(SDLK_RIGHT) 
           || kbdhandl->isPressed(SDLK_l)) {
            if(is_current_tetramino_able_to_move(right))
                move_current_tetramino(right);
        }
        else if(kbdhandl->isPressed(SDLK_LEFT)
                || kbdhandl->isPressed(SDLK_h)) {

            if(is_current_tetramino_able_to_move(left))
                move_current_tetramino(left);
        }
        else if(kbdhandl->isPressed(SDLK_DOWN)
                || kbdhandl->isPressed(SDLK_j)) {

            if(is_current_tetramino_able_to_move(down))
                move_current_tetramino(down);
        }
        else if(kbdhandl->isPressed(SDLK_UP)
                || kbdhandl->isPressed(SDLK_k)) {
            //add check
            rotate_current_tetramino();
        }
        can_input = false;
    }

    /* Long condition to make sure every key is released */
    if(kbdhandl->isReleased(SDLK_RIGHT) && kbdhandl->isReleased(SDLK_LEFT)
       && kbdhandl->isReleased(SDLK_DOWN) && kbdhandl->isReleased(SDLK_UP) 
       && kbdhandl->isReleased(SDLK_h) && kbdhandl->isReleased(SDLK_j)
       && kbdhandl->isReleased(SDLK_l) && kbdhandl->isReleased(SDLK_k)) {
        can_input = true;
    }
}

void BrickGameLG::
put_brick(uvec2 pos, BrickGameBrick brick) {
    field[pos[_x]][pos[_y]] = brick;
}

void BrickGameLG::
move_current_tetramino(Direction d) {
    switch(d) {
        case up:
            if(is_current_tetramino_able_to_move(d)) {
                cut_current_tetramino();
                current_tetramino.pos[_y] -= 1;
                spawn_current_tetramino();
            }
        break;
        case right:
            if(is_current_tetramino_able_to_move(d)) {
                cut_current_tetramino();
                current_tetramino.pos[_x] += 1;
                spawn_current_tetramino();
            }
        break;
        case left:
            if(is_current_tetramino_able_to_move(d)) {
                cut_current_tetramino();
                current_tetramino.pos[_x] -= 1;
                spawn_current_tetramino();
            }
        break;
        case down:
            if(is_current_tetramino_able_to_move(d)) {
                cut_current_tetramino();
                current_tetramino.pos[_y] += 1;
                spawn_current_tetramino();
            }
        break;
    }
}

bool BrickGameLG::
is_current_tetramino_able_to_move(Direction d) {

    if(current_tetramino.orientations.size() == 0) {
        printf("current_tetramino was not initialized!\n");
        printf("| This happend in %s function\n", __func__);
        printf("| This was probably caused by not calling BrickGameLG::\
                start() function\n");
        exit(-1);
    }
    
    TetraminoOrientation tetramino = current_tetramino.
        orientations[current_tetramino.current_orientation];
    uvec2 tetramino_size = {tetramino.map.size(), tetramino.map[0].size()};
    check_tetramino_orientation(tetramino);


	switch(d) {
        case up: 
            return [&]() -> bool{
                for(uint64_t xptr = 0; xptr < tetramino_size[_x]; xptr++) {
                    uvec2 uppest_y_brick = tetramino_size - uvec2({1, 1});
					bool row_has_bricks = false;
                	for(uint64_t yptr = 0; yptr < tetramino_size[_y]; yptr++) {
						if(tetramino.map[xptr][yptr].type == brick) {
							row_has_bricks = true;
                            if(yptr < uppest_y_brick[_y]) {
                                uppest_y_brick = {xptr, yptr};
                            }
						}
					}
                    if(row_has_bricks && !is_brick_able_to_move(uppest_y_brick + current_tetramino.pos, down)) {
                        return false;
                    }
				}
                return true;
			}();
			break;
		case right: 
            return [&](){
                for(uint64_t yptr = 0; yptr < tetramino_size[_y]; yptr++) {
					uvec2 rightest_x_brick = {0, 0};
					bool col_has_bricks = false;
                	for(uint64_t xptr = 0; xptr < tetramino_size[_x]; xptr++) {
						if(tetramino.map[xptr][yptr].type == brick) {
							col_has_bricks = true;
                            if(xptr > rightest_x_brick[_x]) {
                                rightest_x_brick = {xptr, yptr};
							}
						}
					}
					if(col_has_bricks && !is_brick_able_to_move(rightest_x_brick + current_tetramino.pos, right)) {
						return false;
					}
				}
				return true;
			}();
			break;
		case left: 
            return [&](){
                for(uint64_t yptr = 0; yptr < tetramino_size[_y]; yptr++) {
					uvec2 leftest_x_brick = tetramino_size - uvec2({1, 1});
					bool col_has_bricks = false;
                	for(uint64_t xptr = 0; xptr < tetramino_size[_x]; xptr++) {
						if(tetramino.map[xptr][yptr].type == brick) {
							col_has_bricks = true;
                            if(xptr < leftest_x_brick[_x]) {
                                leftest_x_brick = {xptr, yptr};
							}
						}
					}
					if(col_has_bricks && !is_brick_able_to_move(leftest_x_brick + current_tetramino.pos, left)) {
						return false;
					}
				}
				return true;
			}();
    
			break;
		case down: 
            return [&]() -> bool{
                for(uint64_t xptr = 0; xptr < tetramino_size[_x]; xptr++) {
                    uvec2 lowest_y_brick = {0, 0};
					bool row_has_bricks = false;
                	for(uint64_t yptr = 0; yptr < tetramino_size[_y]; yptr++) {
						if(tetramino.map[xptr][yptr].type == brick) {
							row_has_bricks = true;
                            if(yptr > lowest_y_brick[_y]) {
                                lowest_y_brick = {xptr, yptr};
                            }
						}
					}
                    if(row_has_bricks && !is_brick_able_to_move(lowest_y_brick + current_tetramino.pos, down)) {
                        return false;
                    }
				}
                return true;
			}();
			break;
	}

    /* It should never get here */
    printf("Something bad happend in `%s` function. It should never reached this point\n", __func__);
    printf("| Probably, this happend because of passing uninitialized or\n \
            | wrong Direction\n");
    exit(-1);
}


void BrickGameLG::
start() {
    generate_current_tetramino();
    spawn_current_tetramino();
    update();
}

void BrickGameLG::
cut_current_tetramino() {
    TetraminoOrientation current_tetramino_orientation 
        = current_tetramino.orientations[current_tetramino.current_orientation]; 
    check_tetramino_orientation(current_tetramino_orientation);

    for(uint64_t xptr = 0; xptr < current_tetramino_orientation.map.size(); xptr++) {
        for(uint64_t yptr = 0; yptr < current_tetramino_orientation.map[0].size(); yptr++) {
            if(current_tetramino_orientation.map[xptr][yptr].type == brick) {
                /* Brick position in the field */
                uvec2 absolute_brick_pos = current_tetramino.pos + uvec2({xptr, yptr});
                field[absolute_brick_pos[_x]][absolute_brick_pos[_y]] = {clr_black, nothing};
			}
		}
	}
}

void BrickGameLG::
spawn_current_tetramino() {
    TetraminoOrientation current_tetramino_orientation 
        = current_tetramino.orientations[current_tetramino.current_orientation]; 
    check_tetramino_orientation(current_tetramino_orientation);
    for(uint64_t xptr = 0; xptr < current_tetramino_orientation.map.size(); xptr++) {
        for(uint64_t yptr = 0; yptr < current_tetramino_orientation.map[0].size(); yptr++) {
            if((current_tetramino
					.orientations[current_tetramino.current_orientation])
					.map[xptr][yptr].type == brick) {
                /* Brick position in the field */
                uvec2 absolute_brick_pos = current_tetramino.pos + uvec2({xptr, yptr});
                field[absolute_brick_pos[_x]][absolute_brick_pos[_y]] = 
					current_tetramino
					.orientations[current_tetramino.current_orientation]
					.map[xptr][yptr];
			}
		}
	}
}


void BrickGameLG::
generate_current_tetramino() {
    auto NES_random = []()->uint16_t {
        /* Initial seed */
        srand(time(NULL));
        static uint16_t seed = /*8988*/ rand();

        bool seed_bit_1 = ((seed << 14)>>15);
        bool seed_bit_9 = ((seed << 6)>>15);
    
	    auto non_bit_xor = [](bool first, bool second)->bool{
		    return ((!first && second) || (first && !second));
	    };
    
    
	    seed >>= 1;
        seed |= (non_bit_xor(seed_bit_1, seed_bit_9) << 15);

    
        return seed;
    };

    uint16_t tetramino_index = NES_random() % 7;
	Tetramino tetraminos[7] = {stick_tetramino, L_r_tetramino,
								L_l_tetramino, block_tetramino,
								S_tetramino, T_tetramino, Z_tetramino};
    current_tetramino = tetraminos[tetramino_index];
}


bool BrickGameLG::
should_tick() {
    return ((std::chrono::system_clock::now() - last_tick) >= tick_time);
}

void BrickGameLG::
tick() {
    if(is_current_tetramino_able_to_move(down)) {
        move_current_tetramino(down);
    }
    else {
		check_rows();
        generate_current_tetramino();
        spawn_current_tetramino();
    }
    last_tick = std::chrono::system_clock::now();
}
