#include "Func.h"

void Func::log(std::string mgs, void* from, bool error, std::ostream &os) {

}

bool Func::init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        success = false;
        SDL_Log("Fail to init! %s", SDL_GetError());
    } else {
        gWindow = SDL_CreateWindow("Speed Pack", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            success = false;
            SDL_Log("Fail created window! %s", SDL_GetError());
        }
        else {
            int imgFlag = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlag) & imgFlag)){
                SDL_Log("Init IMG failed! %s", SDL_GetError());
                success = false;
            } else {
                gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
                if (gRenderer == NULL) {
                    success = false;
                    SDL_Log("Fail created gRenderer! %s", SDL_GetError());
                }
                else {
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                }
				
            }
            if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            {
                printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                success = false;
            }
			if (TTF_Init() < 0)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
        }
    }
    return success;
}

void Func::Close() {
    if (gRenderer != NULL) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = NULL;
    }
    if (gWindow != NULL) {
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
    }
    if (gTexture != NULL) {
        SDL_DestroyTexture(gTexture);
    }
	TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* Func::loadImg(std::string path){
    SDL_Surface* tmp_sur = IMG_Load(path.c_str());
    SDL_Texture* texture = NULL;
    if(tmp_sur == NULL){
        SDL_Log("Surface .. %s", SDL_GetError());
    } else {
        texture = SDL_CreateTextureFromSurface(gRenderer, tmp_sur);
        if(texture ==  NULL){
            SDL_Log("Texture .. %s", SDL_GetError());
        }
    }
    SDL_FreeSurface(tmp_sur);
    return texture;
}

SDL_Texture* Func::loadFromRenderText(std::string textureText, SDL_Color textColor) {
	SDL_Texture* textTexture = nullptr;
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (textTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{

		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	return textTexture;
}
// void Func::log(std::string mgs, bool error, std::ostream &os){
//     if(error){
//         os << mgs << SDL_GetError() <<std::endl;
//     } else {
//         os << mgs << std::endl;
//     }
// }

bool Func::inRange(int x, int a, int b){
    int min = a < b ? a : b;
    x = x - min; 
    return ( x > 0 && x < abs(b - a) );
}

bool Func::inRect(int x, int y, SDL_Rect* rect) {
	if (rect == nullptr)
		return false;
	return (x >= rect->x && x <= rect->x + rect->w && y >= rect->y && y <= rect->y + rect->h);
}

bool Func::inRange(int x, int y,  int a, int b){
    int min = a < b ? a : b;
    x = x - min;
    y = y - min; 
    return ( x >= 0 && x <= abs(b - a) ) && ( y >= 0 && y <= abs(b - a) );
}

bool Func::avaiIndex(int i, int r,  int j, int c){
    return i >= 0 && i < r && j >= 0 && j < c;
}

//Ham sinh ngau nhien vi tri cac block trong pack
//Tra ve vector kich thuoc RxC + 1x2 trong do:
// RxC la map
// 1x2 chua thong tin [so FixedBlock][]
std::vector< std::vector<int>> Func::randUnion(int r, int c){
    UnitVec unitVec; //Dung de mo rong ra cac block lon
   std::vector< std::vector<char> > table(r, std::vector<char>(c, 1)); //in dau cac vi tri chua su dung
                     // 1 chua su dung
                     // 0 da su dung
    std::vector<std::vector<int>> init_table(r, std::vector<int>(c, -1));   
    //map vi tri cac block
    /*
       -1 o khong chua block
        1 o chua block 1 x 1 
        2 o chua block 1 x 2
       -2 o chua block 2 x 1
        0 o chua pickable block
    */
    
    std::vector<int> info(2, 0); //chua thong tin ve so fixblock
    int ra; //bien chua gia tri random 
    
    //random cac vi tri cua pickable block
    int i0 = rand() % r;
    int j0 = rand() % c;
    table[i0][j0] = 0;
    init_table[i0][j0] = 0;
    int n_emptyBlock;
    ra = rand() % 100;
    if( ra >= 0 && ra < 30){
        n_emptyBlock = 0;
    } else if (ra >= 31 && ra < 90){
        n_emptyBlock = 1;
    } else {
        n_emptyBlock = 2;
    }
    info[0] = r*c - n_emptyBlock - 1;
    for(int i = 0; i < n_emptyBlock; i++){
        i0 = rand() % r;
        j0 = rand() % c;
        if(table[i0][j0]){
            init_table[i0][j0] = 0;
            table[i0][j0] = 0;
        } else {
            
            i--;
        }
    }
    
    //sinh ngau nhien cac o con lai
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(!table[i][j]){
                continue;
            }
            table[i][j] = -1;
            Vector point(i, j);
            ra = rand() % 8 + 2;  
            Vector nextPoint = point + unitVec[ra];
            if(avaiIndex(nextPoint.x, r, nextPoint.y , c) && table[nextPoint.x][nextPoint.y] == 1){
                init_table[i][j] = unitVec[ra].x == 1 ? -2: 2;
                table[nextPoint.x][nextPoint.y] = 0;
            } else {
                init_table[i][j] = 1;
            }
        }
    }
    init_table.push_back(info);
    return init_table;
}


SDL_Texture* Func::creatTransparentTexture(const Uint32& format, const int& w, const int& h){
    SDL_Texture* blankTexture = SDL_CreateTexture(gRenderer, format , SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    SDL_SetRenderTarget(gRenderer, blankTexture);
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_NONE);
    SDL_SetTextureBlendMode(blankTexture, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(gRenderer, NULL);
    SDL_SetRenderTarget(gRenderer, NULL);
    return blankTexture;
}

SDL_Texture* Func::convertTextureToTarget(SDL_Texture* texture, SDL_Rect* rect, bool destroy){
    
    int access, w, h;
    Uint32 format;

    SDL_QueryTexture(texture, &format, &access, &w, &h);
    if(access == SDL_TEXTUREACCESS_TARGET && rect == NULL)  
        return texture;

    SDL_Texture* convertTexture;
    if(rect == NULL){
        convertTexture = creatTransparentTexture(format, w, h);
    } else {
        convertTexture = creatTransparentTexture(format, rect->w, rect->h);
    }
    SDL_SetRenderTarget(gRenderer, convertTexture);
    SDL_RenderCopy(gRenderer, texture, NULL, NULL);
    SDL_SetRenderTarget(gRenderer, NULL);
    if(destroy){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    if(convertTexture == NULL){
        
        return NULL;
    }
    texture = convertTexture;
    return convertTexture;    
}

void Func::parseToTexture(SDL_Texture* dsTexture , const SDL_Rect*  dsRect, SDL_Texture* srcTexture, const SDL_Rect* srcRect){
    dsTexture = convertTextureToTarget(dsTexture,nullptr,  true);
    SDL_SetRenderTarget(gRenderer, dsTexture);
    SDL_RenderCopy(gRenderer, srcTexture, srcRect, dsRect);
    SDL_SetRenderTarget(gRenderer, NULL);
}

void Func::parseToTextureEx(SDL_Texture* dsTexture,const SDL_Rect*  dsRect, SDL_Texture* srcTexture, const SDL_Rect* srcRect, const double angle, const SDL_Point* center,const SDL_RendererFlip flip){
    dsTexture = convertTextureToTarget(dsTexture, nullptr, true);
    SDL_SetRenderTarget(gRenderer, dsTexture);
    SDL_RenderCopyEx(gRenderer, srcTexture, srcRect, dsRect, angle, center, flip);
    SDL_SetRenderTarget(gRenderer, NULL);
   
}

SDL_Texture* Func::resizeTexture(SDL_Texture* origin, int w, int h, bool destroy){
    int access;
    Uint32 format;
    SDL_QueryTexture(origin, &format, &access, NULL, NULL);
    SDL_Texture* resizedTexture = creatTransparentTexture(format, w, h);
    SDL_SetRenderTarget(gRenderer, resizedTexture);
    SDL_RenderCopy(gRenderer, origin, NULL, NULL);
    SDL_SetRenderTarget(gRenderer, NULL);
    if(destroy){
        SDL_DestroyTexture(origin);
        origin = resizedTexture;
    }
    return resizedTexture;
}



// origin: Texture* can reshape
// len: Do dai sau khi resize cua canh duoc quy dinh boi direct va orient
// direct: = 0 neu resize theo chieu ngang   orirent: >= 0 len ung voi canh phai
//													   < 0 len ung canh trai
//		   = 1 new resize theo chieu doc              >= 0 len ung voi canh duoi
//													  <0   len ung voi canh tren
SDL_Texture* Func::resizeTextureWithTrapeZoidShape(SDL_Texture* origin,const int& len,const int& direct, int orient,const bool& destroy){
    orient = orient >= 0 ? 1 : -1;
    int  w, h;
    Uint32 format;
    SDL_QueryTexture(origin, &format, nullptr, &w, &h);
    SDL_Texture* resizeTexture = nullptr;
    int lange;
    if(direct == 0){
        lange = h > len ? h : len;
        resizeTexture = creatTransparentTexture(format, w, lange);
        SDL_SetRenderTarget(gRenderer, resizeTexture);
        int y = abs(len - h) / 2;
        int x0 = (w - orient*w) / 2;
        int relate = round(w*1.0 / y);
        
        SDL_Rect srcRect = { x0 , 0, 1, h};
        SDL_Rect dsRect = { x0 , y, 1, h};
        for(; inRange(srcRect.x, -1, w + 1); dsRect.x += orient, srcRect.x+= orient){
            SDL_RenderCopy(gRenderer, origin, &srcRect, &dsRect );
            if(1 + 2*((dsRect.h - h) *1.0/2  - abs((dsRect.x - x0 + orient)*1.0/relate)) < 0 ){
                dsRect.h+=2;
                dsRect.y--;
            }
        } 
        SDL_SetRenderTarget(gRenderer, NULL);
    } else if(direct == 1){
        lange = w > len ? w : len;
        resizeTexture = creatTransparentTexture(format, lange, h);
        SDL_SetRenderTarget(gRenderer, resizeTexture);
        int x = abs(len - w) / 2;
        double relate = (h*1.0 / x);
        int y0 = (h - orient*h) / 2;
        SDL_Rect srcRect = {0, y0, w, 1};
        SDL_Rect dsRect = {x, y0, w, 1};
        for(; inRange(srcRect.y, -1, h + 1); dsRect.y+= orient, srcRect.y += orient){
            SDL_RenderCopy(gRenderer, origin, &srcRect, &dsRect );
            if(1 + 2*((dsRect.w - w) *1.0/2  - abs((dsRect.y - y0 + orient)*1.0/relate)) < 0 ){
                dsRect.w+=2;
                dsRect.x--;
            }
        }
        SDL_SetRenderTarget(gRenderer, NULL);
    }

    if(destroy){
        SDL_DestroyTexture(origin);
        origin = nullptr;
    }    
    return resizeTexture;
}