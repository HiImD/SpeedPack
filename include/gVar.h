#ifndef GVAR_H_
#define GVAR_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
/*
	Header chua:
	+ Cac bien toan cuc
	+ Ten cac Class
	+ Kich co mac dinh
	+ Duong dan den cac img
*/


#include <string>
#include <cmath>
#define PI 3.14159265

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;
extern SDL_Texture* gTexture;
extern SDL_Event events;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;





enum OBJTYPE {
	MYTEXTURE,
	GAMESPEEDPACK,
	COMPONENT,
    BASEOBJ,
    PACK,
    BLOCK,
	PACK2X4_2,
	PACK3_3x2,
    PICKABLEBLOCK,
    FIXEDBLOCK,
	BUTTON,
	MENU
};

namespace SIZE{
    namespace BLOCK{
		static const int UNIT_SIZE = 92;
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

static const char* FONTPATH = "resrc/font/arialbd.ttf";

namespace IMGPATH{
    static const std::string BACKGROUNG = std::string("resrc/img_src/Background.png");
    namespace BLOCK{
        static const std::string CAMERA = "resrc/img_src/camera_92x92.png";
        static const std::string PICKABLE= std::string("resrc/img_src/active_block_92x92.png");
        static const std::vector<std::string> BLOCK1X1 = {
            "resrc/img_src/block1x1/block1x1_1_92x92.png",
            "resrc/img_src/block1x1/block1x1_2_142x142.png",
            "resrc/img_src/block1x1/block1x1_3_142x142.png",
            "resrc/img_src/block1x1/block1x1_4_142x142.png",
            "resrc/img_src/block1x1/block1x1_5_142x142.png",
            "resrc/img_src/block1x1/block1x1_6_142x142.png",
            "resrc/img_src/block1x1/block1x1_7_142x142.png"
        };
        static const std::vector<std::string> BLOCK1X2 = {
            "resrc/img_src/block1x2/block1x2_1_286x142.png",
            "resrc/img_src/block1x2/block1x2_2_286x142.png"
        };
        static const std::vector<std::string> BLOCK2X1 = {
            "resrc/img_src/block2x1/block2x1_1_92x185.png",
            "resrc/img_src/block2x1/block2x1_2_142x286.png"
        };
    };
    namespace PACK{
        namespace PACK2X4{
            static std::string ALL = "resrc/img_src/pack2x4/pack2x4_3_split_625x802.png";
            static std::string UP = "resrc/img_src/pack2x4/pack2x4_up_400x255.png";
            static std::string DOWN = "resrc/img_src/pack2x4/pack2x4_down_400x255.png";
            static std::string CLOSE = "resrc/img_src/pack2x4/pack2x4_close_400x255.png";
        }
		namespace PACK3_3X2 {
			static const std::string UPLEFT = "resrc/img_src/Pack3x2_3/pack3_3X2_1_split_218x349.png";
			static const std::string UPLEFT_CLOSE = "resrc/img_src/Pack3x2_3/pack3_3X2_1_close_split_218x349.png";
            static const std::string BOTTOMLEFT = "resrc/img_src/Pack3x2_3/pack3_3X2_2_split_257x312.png";
			static const std::string BOTTOMRIGHT = "resrc/img_src/Pack3x2_3/pack3_3X2_3_split_257x312.png";
			static const std::string BOTTOMRIGHT_CLOSE = "resrc/img_src/Pack3x2_3/pack3_3X2_3_close_split_257x312.png";
		}
    };
	namespace ANSWER{
		static const std::string RIGHT = "resrc/img_src/Answer/Right_92x92.png";
		static const std::string WRONG = "resrc/img_src/Answer/Wrong_92x92.png";
	};
	namespace ICON {
		static const std::string PLAY = "";
	}
};



#else
#endif