#include <gtk/gtk.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Square.h"
#include "Stats.h"
#include "XmlModule.h"

#define BLANK 	0
#define TREE 	1
#define ROAD_1	2
#define ROAD_2	3
#define ROAD_3	4
#define GRASS 	5
#define FIELD	6

#define DEFAULT_TILE 0

#define ROW_LENGTH 15
#define TILE_HEIGHT 20
#define TILE_WIDTH 41
#define SPRITE_WIDTH 42
#define SPRITE_HEIGHT 33

#define SPRITE_C1_X 0
#define SPRITE_R1_Y 0
#define SPRITE_C2_X 44
#define SPRITE_R2_Y 35
#define SPRITE_C3_X 88
#define SPRITE_R3_Y 70
#define SPRITE_C4_X 132
#define SPRITE_R4_Y 105

#define TILE_AIR_SPACE 13
#define SEED_X 50
#define SEED_Y 250
#define NUM_TILES 12
#define NUM_STRUCTURES 11

Stats *gameStats;
std:: string saveFile = "automaSave.dat";
GdkPixbuf *buf, *buf2, *buf3,
			*empty, *tree, *road_1, *road_2, *road_3, *stencil,
			*grass, *field, *house1, *office1, *newtree1,
			*office,*water,*house2;
			
std::vector<int> *tileMap;
std::vector<Square *> *tiles;
std::vector<Structure *> *buildings;
std::vector<GdkPixbuf*> *tilePix;

GtkWidget *image;
	
void getGlobal(const int& local, int *x, int *y);
int getLocalMove(const int& direction, const int& currentLoc);
void changeTile(const int& location);

static gboolean delete_event( GtkWidget *widget,
                           	  GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}



void loadTiles(const std::string& filename)
{
	int buffer;
	
	time_t seconds;
	seconds = time (NULL);
	srand(static_cast<int>(seconds));
	std::ifstream getfile;
	getfile.open(filename.c_str());
	std::cout << filename << std::endl;
	for(int i=0;i<(ROW_LENGTH*ROW_LENGTH);i++)
	{
	    //std::cout << "in loop i=" << i << std::endl;
	    getfile >> buffer;
	    //buffer = DEFAULT_TILE;
		Structure *building;
		building = new Structure(*(*buildings)[buffer]);
	    /*building->tileIndex = buffer;
	    building->population = 0;
	    building->jobs = 1;
	    building->commercialDemand = 1;
	    building->industrialDemand = 1;
	    building->residentialDemand = 1;*/
		//buffer = BLANK;//FIELD;//(rand()%NUM_TILES);
		//std::cout << "before new..." << std::endl;
		Square *sPtr;
		sPtr = new Square(i,BLANK,building);
		//if(buffer != 4)
		//{
		//    sPtr->setCanChange(FALSE);
		//}
		//else
		//{
		    sPtr->setCanChange(TRUE);
		//}
		//std::cout << "after new..." << std::endl;
		tiles->push_back(sPtr);
	}

	//std::cout << "Made it past for loop in loadTiles()" << std::endl;
	getfile.close();
}

void drawTiles(GdkPixbuf *dest)
{
	GdkPixbuf *src;
	int dest_x,dest_y,move,loc;
	for(int i=1;i<(ROW_LENGTH*2);i++)
	{
		if(i<=ROW_LENGTH)
		{
			move = ROW_LENGTH - i;
		}
		else
		{
			move = ROW_LENGTH * (i%ROW_LENGTH);
		}
		while(move!=-1)
		{
			src = (*tilePix)[(*tiles)[move]->getLand()];
			getGlobal(move,&dest_x,&dest_y);
			gdk_pixbuf_composite(	src,
						dest,
						dest_x,	dest_y,    	//dest x,y
						SPRITE_WIDTH, 	SPRITE_HEIGHT,	//dest width, height
						dest_x-1,	dest_y-1,			// offset
						1,		1,			// scale
						GDK_INTERP_BILINEAR,
						255);
			src = (*tilePix)[(*tiles)[move]->getStructure()->tileIndex];
			gdk_pixbuf_composite(	src,
						dest,
						dest_x,	dest_y,    	//dest x,y
						SPRITE_WIDTH, 	SPRITE_HEIGHT,	//dest width, height
						dest_x-1,	dest_y-1,			// offset
						1,		1,			// scale
						GDK_INTERP_BILINEAR,
						255);
			move=getLocalMove(6,move);
		}
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(image),dest);
	g_print("testing...\n");
	gameStats->updateStats(tiles);
	gameStats->showStats();
}


int getLocalMove(const int& direction, const int& currentLoc)
{
	bool top=false, right=false, left=false, bottom=false;
	int answer;
	if(direction==-1)
	{
		return -1;
	}
	if(currentLoc<ROW_LENGTH)
	{
		top = true;
	}
	if((currentLoc%ROW_LENGTH)==0)
	{
		//printf("right = true\n");
		right = true;
	}
	if((currentLoc%ROW_LENGTH)==(ROW_LENGTH-1))
	{
		left = true;
	}
	if((currentLoc+ROW_LENGTH)>=(ROW_LENGTH*ROW_LENGTH))
	{
		//printf("bottom = true\n");
		bottom = true;
	}
	switch(direction)
	{
		case 1:		if(right)  answer = -1;
					if(!right) answer = currentLoc -1;
					break;	
					
		case 2:		if(right||bottom) answer = -1;
					if(!(right||bottom))answer = currentLoc + ROW_LENGTH -1;
					//std::cout << "south answer=" << answer << std::endl;
					break;
					
		case 3:		if(bottom) answer = -1;
					if(!bottom) answer = currentLoc + ROW_LENGTH;
					break;	
					
		case 4:		if(right||top) answer = -1;
					if(!(right||top))answer = currentLoc - ROW_LENGTH - 1;
					break;
					
		case 6:		if(bottom||left)  answer = -1;
					if(!(bottom||left)) answer = currentLoc + ROW_LENGTH + 1;
					break;	
					
		case 7:		if(top) answer = -1;
					if(!top) answer = currentLoc - ROW_LENGTH;
					break;	
					
		case 8:		if(top||left) answer = -1;
					if(!(top||left)) answer = currentLoc - ROW_LENGTH + 1;
					break;
					
		case 9:		if(left) answer = -1;
					if(!left) answer = currentLoc + 1;
					break;
					
		default:	answer = -1;
					break;
	}
	return answer;	
}

void getGlobal(const int& local, int *x, int *y)
{
	int global_x=SEED_X, global_y=SEED_Y;
	int row_shift,col_shift;
	row_shift = local%ROW_LENGTH;
	col_shift = local/ROW_LENGTH;
	global_x += row_shift*(TILE_WIDTH/2);
	global_y -= row_shift*(TILE_HEIGHT/2);
	global_x += col_shift*(TILE_WIDTH/2);
	global_y += col_shift*(TILE_HEIGHT/2);
	*x = global_x;
	*y = global_y;
}

gint mapClick(GtkWidget *widg,
				GdkEventButton *event,
				gpointer data)
{
	int x_pos=0, y_pos=0,index,x=0,y=0;
	int x_coarse=0, y_coarse=0,map_loc=-1,x_fine=0,y_fine=0;
	int r=0,g=0,b=0;
	
	x_pos = static_cast<int>(event->x);
	y_pos = static_cast<int>(event->y);	
	
	std::cout << "Xw= "<<x_pos<<" Yw= "<<y_pos<<std::endl;
	
	bool x_in = (x_pos-SEED_X)>=0;
	bool x_under = x_pos<((SEED_X+(TILE_WIDTH*ROW_LENGTH))-ROW_LENGTH);
	bool y_in = (y_pos-(SEED_Y-((TILE_HEIGHT*ROW_LENGTH/2))))>=0;
	bool y_under = y_pos < (SEED_Y +(TILE_HEIGHT*ROW_LENGTH/2));
	
	if((x_in && x_under)&&(y_in&&y_under))
	{
		map_loc = 0;
		x_pos -= SEED_X;
		y_pos -= (SEED_Y+TILE_AIR_SPACE);
		
		std::cout << "Xbc= "<<x_pos<<" Ybc= "<<y_pos<<std::endl;

		int width, height, rowstride, n_channels;
		guchar *pixels, *p;


		x_coarse = x_pos / TILE_WIDTH;
		y_coarse = (y_pos) / (TILE_HEIGHT); 
		
		
		if((y_pos)<0) 
		{
			y_coarse--;
		}
		
//		std::cout << "x_coarse="<<x_coarse<<" y_coarse="<<y_coarse<<std::endl;
		std::cout << "x_coarse="<<x_coarse<<" y_coarse="<<y_coarse<<std::endl;
		
		while(x_coarse>0)
		{
			map_loc = getLocalMove(6,map_loc);
			if(map_loc==-1) return 0;
			x_coarse--;
		}
		if(y_coarse>0)
		{
			while(y_coarse>0)
			{
				map_loc = getLocalMove(2,map_loc);
				if(map_loc==-1) return 0;
				y_coarse--;
			}
		}
		else if(y_coarse<0)
		{
			while(y_coarse<0)
			{
				map_loc = getLocalMove(8,map_loc);
				if(map_loc==-1) return 0;
				y_coarse++;
			}
		}
		if(map_loc < 0)
			return 0;
		
		//y_pos +=84;
		//y_pos +=(TILE_HEIGHT*ROW_LENGTH)/2;
		
		x_fine = x_pos % TILE_WIDTH;
		y_fine = abs(y_pos % (TILE_HEIGHT));
		if(y_pos < 0)
		{
			y_fine = TILE_HEIGHT - y_fine;
			if(y_fine == TILE_HEIGHT) y_fine--;
		}
		
		/*//if(y_fine < 0)
		{
			y_fine = aby_fine;
			g_print("y_fine = %d\n",y_fine);
			return 0;
		}*/
		
		std::cout <<"x_fine="<<x_fine<<" y_fine=" << y_fine << std::endl;

	
	
		n_channels = gdk_pixbuf_get_n_channels (stencil);

		g_assert (gdk_pixbuf_get_colorspace (stencil) == GDK_COLORSPACE_RGB);
		g_assert (gdk_pixbuf_get_bits_per_sample (stencil) == 8);
		g_assert (gdk_pixbuf_get_has_alpha (stencil));
		g_assert (n_channels == 4);

		width = TILE_WIDTH;//gdk_pixbuf_get_width (stencil);
		height = TILE_HEIGHT;//gdk_pixbuf_get_height (stencil);
		
		g_assert (x_fine >= 0 && x_fine < width);
		g_assert (y_fine >= 0 && y_fine < height);

		rowstride = gdk_pixbuf_get_rowstride (stencil);
		pixels = gdk_pixbuf_get_pixels (stencil);

		p = pixels + y_fine * rowstride + x_fine * n_channels;
		
		std::cout << "red="<<int(p[0])<<" green="<<int(p[1])
					<<" blue="<<int(p[2])<< std::endl;
					
		r = int(p[0]);
		g = int(p[1]);
		b = int(p[2]);
		

		if((b&&!r)&&!g)
		{
			map_loc = getLocalMove(7,map_loc);
		}
		else if((r&&g)&&!b)
		{
			map_loc = getLocalMove(9,map_loc);			
		}
		else if((r&&b)&&!g)
		{
			map_loc = getLocalMove(3,map_loc);
		}
		else if((!r&&!b)&&g)
		{
			map_loc = getLocalMove(1,map_loc);
		}
		
		std::cout << "map_loc = " << map_loc << std::endl;
	}
	
	if(map_loc >= 0)
	{
		changeTile(map_loc);
		drawTiles(buf2);
	}
	
	return 0;

}

void changeTile(const int& location)
{
	int num;
	Square *sPtr;
	sPtr = (*tiles)[location];
	printf("location=%d\n",location);
	std::cout << "changing structure.." << std::endl;
	Structure *s1;
	if(sPtr->getCanChange())
	{
		std::cout << "changing structure.." << std::endl;
	    num = sPtr->getStructure()->structureNum;
		printf("accessed structure->strctureNum = %d.\n",num);
	    num = (num+1)%NUM_STRUCTURES;
	    //delete sPtr->getStructure();
	    s1 = new Structure(*(*buildings)[num]);
		printf("accessed *(*buildings)[num].\n");
	    (*tiles)[location]->setStructure(s1);
	}
	printf("Done changing structure.\n");
}

gint saveGame(gpointer data)
{
    


    return 0;
}

gint advanceTime(gpointer data)
{
    



}

void updateStats()
{




}

void initBuildings()
{
	Structure *s1;
	for(unsigned int i=0;i<buildings->size();i++)
	{
		s1 = (*buildings)[i];
		std::cout << "s1->tileIndex = " << s1->tileIndex << std::endl;
		std::cout << "s1->population = " << s1->population << std::endl;	
		std::cout << "s1->jobs = " << s1->jobs << std::endl;
		std::cout << "s1->inDem = " << s1->industrialDemand << std::endl;
		std::cout << "s1->comDem = " << s1->commercialDemand << std::endl;
		std::cout << "s1->resDem = " << s1->residentialDemand << std::endl;
		std::cout << "s1->type = " << s1->type << std::endl;
	}
}

int main( int   argc,	char *argv[])          
{
    int dest_x,dest_y;
    std::string tileData,xmlfile;
	xmlfile = "structures.xml";
    tileData = "tileFile.dat";
    gtk_init (&argc, &argv);
	tiles = new std::vector<Square *>;
	XmlModule xml(xmlfile);
	buildings = xml.getStructs();//new std::vector<Structure *>;
	//initBuildings();
	std::cout << buildings->size() << "  sisisisisize...." << std::endl;
	gameStats = new Stats;
    GtkWidget *hbox;
    GtkWidget *eventBox = gtk_event_box_new();
    GtkWidget *sidebox,*quitButton,*saveButton;


    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect (G_OBJECT (window), "delete_event",
		      G_CALLBACK (delete_event), NULL);
		      


	buf2 = gdk_pixbuf_new_from_file("./data/background.png",NULL);
	image = gtk_image_new_from_pixbuf(buf2);
	//buf2 = gdk_pixbuf_scale_simple(buf,750,750,GDK_INTERP_BILINEAR);
	///gdk_pixbuf_fill(buf2, 0xffffffff);
	buf3 = gdk_pixbuf_new_from_file("./data/grid3.png",NULL);
	stencil = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C2_X,SPRITE_R4_Y,
					TILE_WIDTH,TILE_HEIGHT);
	buf3 = gdk_pixbuf_add_alpha(buf3, TRUE, 255, 0, 255);
	
	empty = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C1_X,SPRITE_R1_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	tree = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C1_X,SPRITE_R2_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	road_1 = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C2_X,SPRITE_R3_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	road_2 = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C1_X,SPRITE_R3_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	road_3 = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C1_X,SPRITE_R4_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	grass = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C2_X,SPRITE_R1_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	field = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C3_X,SPRITE_R2_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	house1 = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C3_X,SPRITE_R3_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	newtree1 = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C4_X,SPRITE_R1_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	office = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C2_X,SPRITE_R2_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	house2 = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C4_X,SPRITE_R2_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);
	water = gdk_pixbuf_new_subpixbuf(buf3,SPRITE_C3_X,SPRITE_R1_Y,
					SPRITE_WIDTH, SPRITE_HEIGHT);		
	//stencil = gdk_pixbuf_new_subpixbuf(buf3,45,105,42,21);

	tilePix = new std::vector<GdkPixbuf*>;
	
	tilePix->push_back(empty);				//0
	tilePix->push_back(tree);				//1
	tilePix->push_back(road_1);				//2
	tilePix->push_back(road_2);				//3
	tilePix->push_back(road_3);				//4
	tilePix->push_back(grass);				//5
	tilePix->push_back(field);				//6
	tilePix->push_back(house1);				//7
	tilePix->push_back(newtree1);			//8
	tilePix->push_back(office);				//9
	tilePix->push_back(house2);				//10
	tilePix->push_back(water);				//11
	
	/*dest_x = dest_y = 25;
	for(uint i=0;i< tilePix->size();i++)
	{
		gdk_pixbuf_composite(	(*tilePix)[i],
					buf2,
					dest_x,	dest_y,    	//dest x,y
					SPRITE_WIDTH, 	SPRITE_HEIGHT,		//dest width, height
					dest_x-1,	dest_y-1,			// offset
					1,		1,			// scale
					GDK_INTERP_BILINEAR,
					255);
		dest_x+=50;
	}*/



	//tileMap = new std::vector<int>;
	loadTiles(tileData);
	//loadTiles(tileMap,tileMapping);
	
	drawTiles(buf2);
	
	
	sidebox = gtk_vbox_new(FALSE,10);
	quitButton = gtk_button_new_with_mnemonic("_Quit");
	saveButton = gtk_button_new_with_mnemonic("_Save");
	gtk_box_pack_start(GTK_BOX(sidebox),saveButton,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(sidebox),quitButton,FALSE,FALSE,0);	
	

	hbox = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(eventBox), image);
	g_signal_connect(G_OBJECT (eventBox), "button_press_event",
	    	G_CALLBACK (mapClick),image);
	g_signal_connect(G_OBJECT (quitButton), "clicked",
	    	G_CALLBACK (gtk_main_quit),window);
	g_signal_connect(G_OBJECT (saveButton), "clicked",
	    	G_CALLBACK (saveGame),window);
	gtk_box_pack_start(GTK_BOX(hbox),sidebox,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox),eventBox,FALSE,FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),hbox);

    gtk_widget_show_all (window);
 
    gtk_main ();
	return 0;
}
