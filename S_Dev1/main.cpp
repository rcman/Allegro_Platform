// Date December 9th 2004
// Franco Gaetan
// Updated Apr 04, 2008
// Use left and right arrows to move
// Press ESC to Quit


#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#define REMOVEGAMERESOURCE(b) if(b!=NULL){destroy_bitmap(b);}
#define MAPWIDTH        20  // width of map in tiles
#define MAPHEIGHT       15  // height of map in tiles
#define TILECOUNT       2


//Sprite Notes for default.bmp
// First box starts at Jewels, dynamote, etc at 160,5
// Spike at 1,69
// Man 5, 105 and 1st 2 rows are 4 the next 2 are 6
// Enemies 6,258 - 8 per row


#define BUFFERSIZE 128
#define WHITE makecol(255, 255, 255)

char    edittext[BUFFERSIZE];
char hud_messages[5][80];
int     caret  = 0;
int value,t,tm;
int w = 16;    //player width-
int TILEHEIGHT = 32;
int TILEWIDTH = 32;

int SPRITEHEIGHT = 32;
int SPRITEWIDTH = 32;
int cv;



int TileSeq=0;
int iCOLS=9;
int iROWS=5;
int locx,locy;
int startx=10,starty=50;
int tilenum=0;
int sprite_index=0, x=200, y=32,j,s=0;
int ripx,ripy,counter=0,indexx,indexy;
int i,a,b,c;
BITMAP* spriteset[300];
BITMAP* manset[100];
BITMAP* BackBuffer;
BITMAP* Blocks1;
BITMAP* man1;
BITMAP* enemy1;
BITMAP* enemy2;
BITMAP* enemy4;
BITMAP* def;
BITMAP* Tiles[TILECOUNT]; // ALLEGRO
//BITMAP* Blocks2;
BITMAP* Temp;
BITMAP* temp_sprite_storage;
BITMAP* temp_sprite_storage2;
BITMAP* images[100];
int bAppDone = 0;
volatile int ticketyticktick;
void tickety ()
{
 ticketyticktick++;
}
END_OF_FUNCTION()

// background 00,33,52,26, 34
// stand on 14, 15, 16, 17


// Need to add special features to the map to allow me to place enemies anywhere I want
// OR better yet have another file per level to describe the enemies and their maximum animation for each
// so all you would need is an x y and max anim.

int MapEnemy[2][3]=
{
{2,9,4},    // PLACE ON MAP BELOW AT ROW 3 COLUMN 10 WITH MAXIUMUM ANIMATIONS OF 4
{1,9,4}
};


int Map[MAPHEIGHT][MAPWIDTH] =
{
{00,52,00,00,26,00,52,53,26,00,16,00,00,00,03,00,00,26,00,00},
{16,15,14,33,26,33,33,00,26,00,16,15,14,16,03,16,16,16,32,00},
{16,16,16,03,15,03,15,00,26,00,00,00,00,16,03,00,00,00,16,03},
{53,00,00,03,16,03,16,16,15,13,17,14,03,16,03,17,15,16,00,03},
{33,00,51,03,16,03,16,53,03,00,00,00,03,16,03,00,00,16,03,16},
{17,00,00,03,16,03,16,00,03,13,17,15,14,16,51,16,03,16,03,02},
{16,13,13,15,16,03,16,00,03,00,00,16,03,00,00,32,03,16,03,00},
{34,00,00,00,00,03,16,52,16,16,03,16,03,13,03,15,13,17,14,03},
{16,03,16,13,16,16,27,25,00,53,03,16,03,16,03,16,00,00,16,03},
{02,03,16,16,00,00,16,26,00,00,03,16,03,16,03,16,16,03,16,03},
{02,03,32,00,00,16,53,26,00,00,03,16,03,16,03,51,00,03,16,03},
{02,15,14,16,13,17,00,26,00,32,03,00,03,16,03,00,04,03,16,03},
{02,27,27,27,27,27,27,25,17,13,14,15,16,13,16,17,14,13,16,03},
{02,00,52,00,00,52,52,26,52,52,00,52,00,00,52,00,00,52,00,03},
{13,17,15,13,16,15,13,13,17,03,15,13,17,13,15,17,13,14,13,17}
};
// door 29
// Walkthrough
// Pipe Walkthrough
// 16 ground/wall stop
// 03 stairs down or up
// 33 walk through
// 53 light walk through
// 26 pipe walkthrough



void initialize_game ()
{
   Tiles[0] = load_bitmap("bmp/man1.bmp", NULL);
   if (Tiles[0]==NULL)
   {
    alert("Loading bmp/man1.bmp","Failed",":(","OK",NULL,KEY_ENTER,KEY_ESC);
    bAppDone=1;
   }
   Tiles[1] = load_bitmap("bmp/man2.bmp", NULL);
   if (Tiles[1]==NULL)
   {
    alert("Loading bmp/enemy1.bmp","Failed",":(","OK",NULL,KEY_ENTER,KEY_ESC);
    bAppDone=1;
   }
   enemy2 = load_bitmap("bmp/enemy2.bmp", NULL);
   if (enemy2==NULL)
   {
    alert("Loading bmp/enemy2.bmp","Failed",":(","OK",NULL,KEY_ENTER,KEY_ESC);
    bAppDone=1;
   }
   enemy4 = load_bitmap("bmp/enemy4.bmp", NULL);
   if (enemy4==NULL)
   {
    alert("Loading bmp/enemy4.bmp","Failed",":(","OK",NULL,KEY_ENTER,KEY_ESC);
    bAppDone=1;
   }
    def = load_bitmap("bmp/default.bmp", NULL);
   if (def==NULL)
   {
    alert("Loading bmp/default.bmp","Failed",":(","OK",NULL,KEY_ENTER,KEY_ESC);
    bAppDone=1;
   }



}
void RenderMap()
{
    int mx,my;
    for (my=0; my<MAPHEIGHT; my++)
    {
     for (mx=0; mx<MAPWIDTH; mx++)
     {
       tilenum = Map[my][mx];

       blit(spriteset[tilenum], BackBuffer, 0, 0,
       mx * TILEWIDTH, my * TILEHEIGHT, TILEWIDTH, TILEHEIGHT); // ALLEGRO
      }
    }
}


void shutdown_game ()
{
 if (BackBuffer!=NULL) { destroy_bitmap (BackBuffer); }
 if (man1!=NULL) { destroy_bitmap (man1); }
 if (enemy1!=NULL) { destroy_bitmap (enemy1); }
 if (enemy2!=NULL) { destroy_bitmap (enemy2); }
 if (enemy4!=NULL) { destroy_bitmap (enemy4); }
 if (def!=NULL) { destroy_bitmap (def); }
     for (int i = 0; i < 300; i++)
    {
      REMOVEGAMERESOURCE(spriteset[i])
    }
     for (int i = 0; i < 100; i++)
    {
      REMOVEGAMERESOURCE(manset[i])
    }
        int index;
        for (index=0; index<TILECOUNT; index++)
        {
         destroy_bitmap(Tiles[index]);
        }
}

void LoadSpecial (char* szFilename, int iROWS, int iCOLS, int locx, int locy)
{
 temp_sprite_storage2 = load_bitmap(szFilename, NULL);
 int indexy = 0, indexx = 0, ripx = 0, ripy = 0, counter = 0, offset=0;
 if (temp_sprite_storage2 == NULL)
 {
  alert("Loading Sprite","Failed",":(","OK",NULL,KEY_ENTER,KEY_ESC);
  allegro_exit();
}
//int TILEHEIGHT = 32;
//int TILEWIDTH = 32;
//int SPRITEHEIGHT = 40;
//int SPRITEWIDTH = 32;

      //offset = locx * locy;

for (indexy = 0; indexy != iROWS+1;++indexy)
    {
      for (indexx = 0; indexx != iCOLS; ++indexx)
      {
      ripx = indexx * SPRITEHEIGHT+locx; // account for 1 pixel borders
      ripy = indexy * SPRITEWIDTH+locy;
      manset[counter] = create_bitmap(SPRITEHEIGHT, SPRITEWIDTH);
      blit(temp_sprite_storage2, manset[counter], ripx, ripy, 0, 0, SPRITEHEIGHT, SPRITEWIDTH);
      counter++;
    }
 } destroy_bitmap(temp_sprite_storage2);

}

void LoadSpriteSheet32x32 (char* szFilename, int iROWS, int iCOLS)
{
 temp_sprite_storage = load_bitmap(szFilename, NULL);
 int indexy = 0, indexx = 0, ripx = 0, ripy = 0, counter = 0;
 if (temp_sprite_storage == NULL)
 {
  alert("Loading Sprite","Failed",":(","OK",NULL,KEY_ENTER,KEY_ESC);
  allegro_exit();
}
//int TILEHEIGHT = 32;
//int TILEWIDTH = 32;

for (indexy = 0; indexy != iROWS+1;++indexy)
    {
      for (indexx = 0; indexx != iCOLS+1; ++indexx)
      {
      ripx = indexx * TILEHEIGHT; // account for 1 pixel borders
      ripy = indexy * TILEWIDTH;
      spriteset[counter] = create_bitmap(TILEHEIGHT, TILEWIDTH);
      blit(temp_sprite_storage, spriteset[counter], ripx, ripy, 0, 0, TILEHEIGHT, TILEWIDTH);
      counter++;
    }
 } destroy_bitmap(temp_sprite_storage);

//Draw_Sprites();

}

void update_logic ()
{

 if (key[KEY_ESC])
 {
  bAppDone=1;
 }
  if (key[KEY_RIGHT])
  {
   x = x + 3;                                // Walk Speed
   TileSeq = TileSeq + 1;
       if (TileSeq >1)
      {
          TileSeq=0;
  }
  }
   if (key[KEY_LEFT])
  {
   x = x - 3;                // Walk Speed
   TileSeq = TileSeq + 1;
       if (TileSeq >3)
       {
           TileSeq=2;
   }

}


     RenderMap();
draw_sprite (BackBuffer, manset[TileSeq], x, y);
//draw_sprite (BackBuffer, manset[0], 370, 1);
}


void update_graphics ()
{

   //set text background color to bright blue
  //text_mode(makecol(0, 0, 255));
int tilexpixels = x-(x%32);	//calculate the x position (pixels!) of the tiles we check against
int testend = x + 1;		//calculate the end of testing (just to save the x+w calculation each for loop)
int	tilecoordy = y/32;			//calculate the y position (map coordinates!) of the tiles we want to test
	int tilecoordx = tilexpixels/32;	//calculate map x coordinate for first tile
	int ttimes = tilecoordx * 32;
    int tmpmap = Map[tilecoordy+1][tilecoordx];
    int tmp2 = ((tilecoordx *32) -x)*-1;

 vsync ();
 blit (BackBuffer, screen, 0, 0, 0, 0, 1024, 768 );
 for (t=0;t<9999;t++){}
}


// DO NOT MODIFY THE FOLLOWING CODE!
// ONLY ADD CODE ABOVE!
int main (int args, char* argv[])
{
 allegro_init ();
 install_timer ();
 install_keyboard ();
 set_color_depth  ( 16 );
 set_color_depth(32);    // This added Thursday January 15th 2009

 set_gfx_mode (GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0);
 BackBuffer = create_bitmap (1024, 768); clear_bitmap (BackBuffer);

 initialize_game ();
 LoadSpriteSheet32x32 ("bmp/Sewers.bmp", 5, 9);

   LoadSpecial ("bmp/defaultnew.bmp", 1, 4, 0 , 0); // rows , columns, location on bmp in pixels
  while (bAppDone==0)
 {
     update_logic ();
   ticketyticktick--;
 //for ( tm= 0; tm != 20000000; ++tm)
 {
 };

  update_graphics();
 }
 shutdown_game ();
}
END_OF_MAIN()

