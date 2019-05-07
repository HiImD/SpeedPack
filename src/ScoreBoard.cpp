#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() : score_texture(mRenderer, pTexture->getTexture()), added_score_texture(mRenderer, pTexture->getTexture()), added_score_texture_show(false), added_score_time_show(0){
	added_score_str = "+0";
	ss.str("");
	ss << std::setfill('0') << std::setw(4) << score;
	Render();
	PushBack(&score_texture);
	PushBack(&added_score_texture);
}

ScoreBoard::~ScoreBoard() {
	ss.clear();
}
void ScoreBoard::StartOver() {
	score = 0;
	ss.str("");
	ss << std::setfill('0') << std::setw(4) << score;
	Render();
	added_score_texture_show = false;
}

void ScoreBoard::AddPoint(const short& added_point) {
	if (added_point > 0) {
		score+= added_point;
		ss.str("");
		ss << std::setfill('0') << std::setw(4) << score ;
		added_score_str = std::string("+") + std::to_string(added_point);
		Render();
		added_score_texture_show = true;
		added_score_time_show = 255;
	}
	//SDL_Log(std::to_string(scoreBoard).c_str());

}

short ScoreBoard::GetScore() {
	return score;
}

void ScoreBoard::Resize() {
	SetComponentSize(margin.left + score_texture.getRectPointer()->w + margin.right, margin.top + 2 * score_texture.getRectPointer()->h + margin.between + margin.bottom);
}

void ScoreBoard::Render(SDL_Renderer* renderer, const double angle, SDL_Point* center, SDL_RendererFlip flip) {
	score_texture.RenderTextSolid(ss.str(), { 255, 255, 255 }, true);
	added_score_texture.RenderTextSolid(added_score_str, { 255, 255, 255}, true);
}

void ScoreBoard::ShowBoard() {
	SDL_SetRenderTarget(gRenderer, nullptr);
	SDL_RenderCopy(gRenderer, score_texture.getTexture(), nullptr, score_texture.getRectPointer());

	if (added_score_texture_show) {
		SDL_Log(std::to_string(added_score_time_show).c_str());
		SDL_SetTextureAlphaMod(added_score_texture.getTexture(), added_score_time_show );
		added_score_time_show -= 3;
		SDL_RenderCopy(gRenderer, added_score_texture.getTexture(), nullptr, added_score_texture.getRectPointer());
		if (added_score_time_show < 0) {
			added_score_texture_show = false;
		}
	}
}

void ScoreBoard::PreparResult() {
	setBGColor({ 255, 255, 255,255 });
	if (score > 300) 
			score_texture.RenderTextBlended("Fanstatic! You earned", { 0, 0, 0 }, true);
	else if(score > 100)
		score_texture.RenderTextBlended("Good play! You earned", {0, 0, 0}, true);
	else if(score > 0)
		score_texture.RenderTextBlended("Well done! You earned", { 0, 0, 0 }, true);
	else 
		score_texture.RenderTextBlended("Too bad! You earned", { 0, 0, 0 }, true);
	
	added_score_texture.RenderTextBlended(std::to_string(score) + std::string(" points"), { 0, 0, 0 }, true);
	margin = { 30, 30, 40, 40, 20 };
	pTexture->getRectPointer()->w = margin.left + score_texture.getRectPointer()->w + margin.right;
	AutoSort();
	ParseAllToComp();
	
}