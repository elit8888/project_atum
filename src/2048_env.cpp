﻿#include "2048_env.h"

Game2048Env::Game2048Env(){
	__asm__ __volatile__("rdtsc" : "=a" (m_seed));
	std::srand(m_seed);
	m_input_size = 16;
	m_output_size = 1;
}

Game2048Env::~Game2048Env(){
	
}

double Game2048Env::evaluate_agent(Agent& agent){
	// play an episode
	int score = 0;
	m_board.init();

	while (true) {
		// try to find a best move
		State current_state(m_board);

		
		//current_state.PrintState();
		double best_val = -10000000;
		int best_move = 0;
		for(int i = 1; i < 4; i++){
			State tmp_state = current_state;
			int reward = tmp_state.move(i);
			if (reward == -1) continue;
			mat A = zeros(16);
			for(int j = 0; j < 16; j++) A(j) = tmp_state.get_board().at(j);
			double val = (double)agent.predict(A.t())(0) + reward;
			if (val > best_val){
				best_val = val;
				best_move = i;
			}
		}

		State best_next_state = current_state;
		best_next_state.move(best_move);

		if (best_next_state.get_reward() != -1) {
			m_board = best_next_state.get_board();
			score += best_next_state.get_reward();
			m_board.add_random_tile();
		}
		// game over
		else 
			break;
	}
	return (double)score;
}
	
mat Game2048Env::get_observation(){

} 
void Game2048Env::do_action(mat action){
	
}