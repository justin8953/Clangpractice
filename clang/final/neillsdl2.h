#ifndef __PARSESDL__H__
#define __PARSESDL__H__

#include<math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#define WWIDTH 800
#define WHEIGHT 600

/* Font stuff */
typedef unsigned short fntrow;
#define FNTWIDTH (sizeof(fntrow)*8)
#define FNTHEIGHT 18
#define FNTCHARS 96
#define FNT1STCHAR 32
#define SDL_8BITCOLOUR 256

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



/* All info required for windows / renderer & event loop */

struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
   SDL_Texture *display;
   SDL_Texture *font_texture;
   SDL_Surface *text;
   TTF_Font *font;
};
typedef struct SDL_Simplewin SDL_Simplewin;
void Neill_SDL_Init(SDL_Simplewin *sw);
void Neill_SDL_Events(SDL_Simplewin *sw);
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b);
void Neill_SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r);
void Neill_SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r);
void Neill_SDL_DrawChar(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT],
                        unsigned char chr, int ox, int oy);
void Neill_SDL_DrawString(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT],
                          char *str, int ox, int oy);
void Neill_SDL_ReadFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname);
void Neill_SDL_UpdateScreen(SDL_Simplewin *sw);
void LOAD_FONT (SDL_Simplewin *sw, char *s , int R, int G, int B);

#endif
