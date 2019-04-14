#ifndef GVAR_H_
#define GVAR_H_

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

#include <cmath>
#define PI 3.14159265


extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* gTexture;
extern SDL_Event events;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;

enum OBJTYPE{
    BASEOBJ,
    PACK,
    BLOCK,
    PACK2x4,
    PICKABLEBLOCK,
    FIXEDBLOCK
};

namespace SIZE{
    namespace BLOCK{
        static SDL_Rect PICKABLEBLOCK = {0, 0, 92, 92};
        static SDL_Rect BLOCK1X1 = {0, 0, 92, 92};
        static SDL_Rect BLOCK2X1 = {0, 0, 92, 185};
        static SDL_Rect BLOCK1X2 = {0, 0 , 185, 92};
    }
    namespace PACK{
        namespace PACK2X4{
            static SDL_Rect UP =  {0, 0, 400, 255};
            static SDL_Rect BOTTOM = {0, 0, 400, 255};
        }
    }
}

namespace IMGPATH{
    static const std::string BACKGROUNG = std::string("src/img_src/Screenshot_2019-03-31-12-00-20.png");
    namespace BLOCK{
        static const std::string CAMERA = "src/img_src/camera_92x92.png";
        static const std::string PICKABLE= std::string("src/img_src/active_block_92x92.png");
        static const std::vector<std::string> BLOCK1X1 = {
            "src/img_src/block1x1_1_92x92.png",
            "src/img_src/block1x1_2_142x142.png",
            "src/img_src/block1x1_3_142x142.png",
            "src/img_src/block1x1_4_142x142.png",
            "src/img_src/block1x1_5_142x142.png",
            "src/img_src/block1x1_6_142x142.png",
            "src/img_src/block1x1_7_142x142.png"
        };
        static const std::vector<std::string> BLOCK1X2 = {
            "src/img_src/block1x2_1_286x142.png",
            "src/img_src/block1x2_2_286x142.png"
        };
        static const std::vector<std::string> BLOCK2X1 = {
            "src/img_src/block2x1_1_92x185.png",
            "src/img_src/block2x1_2_142x286.png"
        };
    };
    namespace PACK{
        namespace PACK2X4{
            static std::string ALL = "src/img_src/pack2x4/pack2x4_3_split_625x802.png";
            static std::string UP = "src/img_src/pack2x4/pack2x4_up_400x255.png";
            static std::string DOWN = "src/img_src/pack2x4/pack2x4_down_400x255.png";
            static std::string CLOSE = "src/img_src/pack2x4/pack2x4_close_400x255.png";
        }
    };
};

#else
#endif