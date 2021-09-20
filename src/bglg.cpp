#include "include/bglg.h"

bool BrickGameLG::was_created = false;

BrickGameLG::
BrickGameLG(Renderer *renderer, KeyboardHandler *kbdhandl, uint64_t brick_size, uvec2 field_offset, uvec2 field_size, std::chrono::duration<double> tick_time) {
    
   	if(this->was_created) {
        throw MoreThenOneObjectExists();
	}

	this->renderer = renderer;
    this->kbdhandl = kbdhandl;
    this->brick_size = brick_size;
    this->tick_time = tick_time;
    was_created = true;
    can_input = true;
    
    const BrickGameBrick rb = {clr_red, brick};
    const BrickGameBrick gb = {clr_green, brick};
    const BrickGameBrick bb = {clr_blue, brick};
    const BrickGameBrick nb = {clr_black, nothing};

	TetraminoOrientation tmp_orientation1 ={{{nb, nb, rb, nb, nb},
											 {nb, nb, rb, nb, nb},
											 {nb, nb, rb, nb, nb}, 
											 {nb, nb, rb, nb, nb},
											 {nb, nb, rb, nb, nb}}};
	TetraminoOrientation tmp_orientation2 ={{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {rb, rb, rb, rb, rb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};
 
	this->stick_tetramino = {{tmp_orientation1, tmp_orientation2}, 0, {5, 0}};
    
	tmp_orientation1 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, gb, nb},
											 {nb, nb, gb, nb, nb}, 
											 {nb, nb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};
    
	tmp_orientation2 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, nb, nb, gb, nb},
											 {nb, nb, nb, nb, nb}}};

	TetraminoOrientation tmp_orientation3 ={{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, nb, nb},
											 {nb, nb, gb, nb, nb}, 
											 {nb, gb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	TetraminoOrientation tmp_orientation4 ={{{nb, nb, nb, nb, nb},
											 {nb, gb, nb, nb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

    this->L_r_tetramino = {{tmp_orientation1, tmp_orientation2, tmp_orientation3, tmp_orientation4}, 0, {5, 0}};

	tmp_orientation1 =					   {{{nb, nb, nb, nb, nb},
											 {nb, gb, gb, nb, nb},
											 {nb, nb, gb, nb, nb}, 
											 {nb, nb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};
    
	tmp_orientation2 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, gb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation3 ={{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, nb, nb},
											 {nb, nb, gb, nb, nb}, 
											 {nb, nb, gb, gb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation4 ={{{nb, nb, nb, nb, nb},
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
    
    
	tmp_orientation1 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, rb, rb, nb, nb}, 
											 {nb, nb, rb, rb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation2 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, rb, nb, nb},
											 {nb, rb, rb, nb, nb}, 
											 {nb, rb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation3 =					   {{{nb, nb, nb, nb, nb},
											 {nb, rb, rb, nb, nb},
											 {nb, nb, rb, rb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation4 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, nb, rb, rb, nb}, 
											 {nb, rb, rb, nb, nb},
											 {nb, nb, nb, nb, nb}}};
    
	this->Z_tetramino = {{{tmp_orientation1, tmp_orientation2, tmp_orientation3, tmp_orientation4}}, 0, {5, 0}};

	tmp_orientation1 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, nb, rb, rb, nb}, 
											 {nb, rb, rb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation2 =					   {{{nb, nb, nb, nb, nb},
											 {nb, rb, nb, nb, nb},
											 {nb, rb, rb, nb, nb}, 
											 {nb, nb, rb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation3 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, rb, rb, nb},
											 {nb, rb, rb, nb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation4 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, rb, rb, nb, nb}, 
											 {nb, nb, rb, rb, nb},
											 {nb, nb, nb, nb, nb}}};
    
	this->S_tetramino = {{{tmp_orientation1, tmp_orientation2, tmp_orientation3, tmp_orientation4}}, 0, {5, 0}};

	tmp_orientation1 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, nb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation2 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, nb, nb},
											 {nb, gb, gb, nb, nb}, 
											 {nb, nb, gb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation3 =					   {{{nb, nb, nb, nb, nb},
											 {nb, nb, gb, nb, nb},
											 {nb, gb, gb, gb, nb}, 
											 {nb, nb, nb, nb, nb},
											 {nb, nb, nb, nb, nb}}};

	tmp_orientation4 =					   {{{nb, nb, nb, nb, nb},
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

void BrickGameLG::
drawBrick(BrickGameBrick brick, uvec2 pos) {
    renderer->drawRect(pos, {brick_size, brick_size}, brick.clr, 1);
}

void BrickGameLG::
apply_gravity(uvec2 brick_pos) {
    if(brick_pos[_x] > field_size[_x] - 1 || brick_pos[_y] > field_size[_y] - 1) return;
    if(brick_pos[_y] == field_size[_y] - 1) return;

	BrickGameBrick &currentBrick = (field[brick_pos[_x]][brick_pos[_y]]);
	BrickGameBrick &nextBrick = (field[brick_pos[_x]][brick_pos[_y] + 1]);

    if(currentBrick.type == nothing) return;
//    printf("In the %s, %d mark passed\n", __func__, 2);
    if(nextBrick.type != nothing) return;
//    printf("In the %s, %d mark passed; GRAVITY WILL BE APPLIED\n", __func__, 3);
    

    field[brick_pos[_x]][brick_pos[_y] + 1] = field[brick_pos[_x]][brick_pos[_y]];
    field[brick_pos[_x]][brick_pos[_y]] = {clr_black, nothing};
}

void BrickGameLG::
apply_gravity_for_all() {
    uvec2 brick_pos = field_size - uvec2({1, 1});
    for(auto ptr1 = field.end(); ptr1 > field.begin(); ptr1--) {
        for(auto ptr2 = ptr1->end(); ptr2 > ptr1->begin(); ptr2--) {

            apply_gravity(brick_pos);
            
            if(brick_pos[_y]) brick_pos[_y]--;
            else break;
        }
        if(brick_pos[_x]) { 
			brick_pos[_x]--; 
            brick_pos[_y] = field_size[_y] - 1;
		}
        else break;
    }
}

void BrickGameLG::
create_field(uvec2 field_pos, uvec2 field_size) {
    this->field_pos = field_pos;
    this->field_size = field_size;
    
    //create everything needed
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
	    	uvec2 real_pos = {(brick_posx) * brick_size + field_pos[_x], (brick_posy) * brick_size + field_pos[_x]};
            drawBrick({ptr2->clr, ptr2->type}, real_pos);
	    	brick_posy++;
        }
		brick_posx++;
        brick_posy = 0;
    }
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
            /* OR */ 
            // tick();
        }
        else if(kbdhandl->isPressed(SDLK_UP)
                || kbdhandl->isPressed(SDLK_k)) {

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
    uint64_t yvectr_size = tetramino.map[0].size();
    for(auto yvectr = tetramino.map.begin(); 
        yvectr < tetramino.map.end();
        yvectr++) {
        if(yvectr->size() != yvectr_size) {
            printf("Error: unmatching sizes of y vectors\n");
            printf("| In function `%s`\n", __func__);
            printf("| This probably happend because of different sizes of y");
            printf("in tetramino.\n");
            printf("|>Please make sure that the y sizes of tetramino are all the same\n");
            exit(-1);
        }
    }


	switch(d) {
        case up: 
            return [](BrickGameLG *lg) -> bool{
                TetraminoOrientation tetramino = lg->current_tetramino.
						orientations[lg->current_tetramino.current_orientation];
                uvec2 tetramino_size = {tetramino.map.size(), tetramino.map[0].size()};
				uvec2 uppest_brick = {4, 4};
                for(uint64_t xptr = 0; xptr < tetramino_size[_x]; xptr++) {
                	for(uint64_t yptr = 0; yptr < tetramino_size[_y]; yptr++) {
						if(tetramino.map[xptr][yptr].type == brick) {
                            if(uppest_brick[_y] > yptr) {
                                /* New uppest brick */
                                uppest_brick = {xptr, yptr};
							}
						}
					}
				}
                return lg->is_brick_able_to_move(
                           uppest_brick + lg->current_tetramino.pos,
                           up);
			}(this);
			break;
		case right: 
            return [](BrickGameLG *lg){
                TetraminoOrientation tetramino = lg->current_tetramino.
						orientations[lg->current_tetramino.current_orientation];
                uvec2 tetramino_size = {tetramino.map.size(), tetramino.map[0].size()};
				uvec2 rightest_brick = {0, 0};
                for(uint64_t xptr = 0; xptr < tetramino_size[_x]; xptr++) {
                	for(uint64_t yptr = 0; yptr < tetramino_size[_y]; yptr++) {
						if(tetramino.map[xptr][yptr].type == brick) {
                            if(rightest_brick[_x] < xptr) {
                                /* New rightest brick */
                                rightest_brick = {xptr, yptr};
							}
						}
					}
				}
                return lg->is_brick_able_to_move(
                           rightest_brick + lg->current_tetramino.pos,
                           right);
			}(this);
			break;
		case left: 
            return [](BrickGameLG *lg){
                TetraminoOrientation tetramino = lg->current_tetramino
					.orientations[lg->current_tetramino.current_orientation];
                uvec2 tetramino_size = {tetramino.map.size(), tetramino.map[0].size()};
				uvec2 leftest_brick = {4, 4};
                for(uint64_t xptr = 0; xptr < tetramino_size[_x]; xptr++) {
                	for(uint64_t yptr = 0; yptr < tetramino_size[_y]; yptr++) {
						if(tetramino.map[xptr][yptr].type == brick) {
                            if(leftest_brick[_x] > xptr) {
                                /* New leftest brick */
                                leftest_brick = {xptr, yptr};
							}
						}
					}
				}
                return lg->is_brick_able_to_move(
                           leftest_brick + lg->current_tetramino.pos,
                           left);
			}(this);
    
			break;
		case down: 
            return [](BrickGameLG *lg) -> bool{
                TetraminoOrientation tetramino = lg->current_tetramino
					.orientations[lg->current_tetramino.current_orientation];
                uvec2 tetramino_size = {tetramino.map.size(), tetramino.map[0].size()};
				uvec2 lowest_brick = {0, 0};
                
                for(uint64_t xptr = 0; xptr < tetramino_size[_x]; xptr++) {
                	for(uint64_t yptr = 0; yptr < tetramino_size[_y]; yptr++) {
						if(tetramino.map[xptr][yptr].type == brick) {
                            if(yptr > lowest_brick[_y]) {
                                /* New lowest brick */
                                lowest_brick = {xptr, yptr};
							}
						}
					}
				}
                return lg->is_brick_able_to_move(
                           lowest_brick + lg->current_tetramino.pos,
                           down);
			}(this);
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
    for(uint64_t xptr = 0; xptr < 5; xptr++) {
        for(uint64_t yptr = 0; yptr < 5; yptr++) {
            if((current_tetramino
					.orientations[current_tetramino.current_orientation])
					.map[xptr][yptr].type == brick) {
                /* Brick position in the field */
                uvec2 absolute_brick_pos = current_tetramino.pos + uvec2({xptr, yptr});
                field[absolute_brick_pos[_x]][absolute_brick_pos[_y]] = {clr_black, nothing};
			}
		}
	}
}

void BrickGameLG::
spawn_current_tetramino() {
    for(uint64_t xptr = 0; xptr < 5; xptr++) {
        for(uint64_t yptr = 0; yptr < 5; yptr++) {
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
        generate_current_tetramino();
        spawn_current_tetramino();
    }
    last_tick = std::chrono::system_clock::now();
}
