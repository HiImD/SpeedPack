void BaseObj::setRect(int x, int y, int w, int h, int id){
    if(arr_texture.size() > id){
        arr_texture[id].rect = {x, y, w, h};
    }
}

void BaseObj::setRect(const SDL_Rect &rect, int id){
    if(arr_texture.size() > id){
        arr_texture[id].rect = rect;
    }
}

void BaseObj::setPos(int x, int y, int id){
    if(arr_texture.size() > id){
        arr_texture[id].rect.x = x;
        arr_texture[id].rect.y = y;
    }
}

void BaseObj::setWH(int w, int h, int id){
    if(arr_texture.size() > id){
        arr_texture[id].rect.w = w;
        arr_texture[id].rect.h = h;
    }
}

SDL_Rect BaseObj::getRect(int id){
    if(arr_texture.size() > id){
        return arr_texture[id].rect;
    }
    return {0,0,0,0};
}

int BaseObj::getX(int id){
    if(arr_texture.size() > id){
        return arr_texture[id].rect.x;
    }
    return -1;
}

int BaseObj::getY(int id){
    if(arr_texture.size() > id){
        return arr_texture[id].rect.y;
    }
    return -1;
}

int BaseObj::getH(int id){
    if(arr_texture.size() > id){
        return arr_texture[id].rect.h;
    }
    return -1;
}

int BaseObj::getW(int id){
    if(arr_texture.size() > id){
        return arr_texture[id].rect.w;
    }
    return -1;
}

void BaseObj::loadImg(std::string path, int id){
    if(arr_texture.size(int id)){
        arr_texture[id].texture = Func::loadImg(path);
    }
}

void BaseObj::Show(int id){
    if(arr_texture.size() > id){
        SDL_RenderCopy(gRenderer, arr_texture[id].texture, NULL, &arr_texture[id].rect);
    }
}

void BaseObj::ShowEx(int angle, SDL_Point* center, SDL_RendererFlip flip, int id){
    if(arr_texture.size() > id){
        SDL_RenderCopyEx(gRenderer, arr_texture[id].texture, NULL, &arr_texture[id].rect, angle, center, flip);
    }
}

