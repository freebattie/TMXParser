#ifndef TMXPARSER_H
#define TMXPARSER_H


#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>


#include <string>
#include <vector>
#include <utility>
#include <map>

#define VERSION "1.0"

namespace TMX
{

  class Parser
  {
    public:
      Parser(const char* filename);
      Parser();
      virtual ~Parser();

     
	  void load(rapidxml::xml_document<> &doc );
	  bool load(const char* filename);

      struct Map {
        std::string version;
        std::string orientation;
        unsigned int width;
        unsigned int height;
        unsigned int tileWidth;
        unsigned int tileHeight;
        std::string backgroundColor;
        std::map<std::string, std::string> property;
      };

      

      struct Data {
        std::string encoding;
        std::string compression;
        std::string contents;
      };

      struct TileLayer {
        std::string name;
        bool visible;
        float opacity;
        Data data;
        std::map<std::string, std::string> property;
      };

	  struct Elipse {
		 
	  };

	  struct Polygon{
		
		  std::string points;

	  };
	  struct Polyline{

		  std::string   points;
		  std::string   name;
	  };
      struct Object {
        std::string name;
        std::string type;
		std::string typeName;
        int x;
        int y;
		float rotation;
        unsigned int width;
        unsigned int height;
        unsigned int gid;
        bool visible;
        std::map<std::string,   std::string> property;
		std::map<std::string,        Elipse> elipse;
		std::map<std::string,      Polyline> polyline;
		std::map<std::string,       Polygon> polygon;

      };

      struct ObjectGroup {
        std::string color;
        std::string name;
        float opacity;
        bool visible;
        std::map<std::string, Object> object;
        std::map<std::string, std::string> property;
      };

      struct Image {
        std::string source;
        std::string transparencyColor;
		std::map<std::string, std::string> property;
      };

      struct ImageLayer {
        std::string name;
        float opacity;
        bool visible;
        std::map<std::string, std::string> property;
        Image image;
      };

	  // here starts old TSX file part

	  struct TilesetImage {
		  std::string source;
		  std::string transparentColor;
		  unsigned int width;
		  unsigned int height;
		  std::map<std::string, std::string> property;
	  };
	  struct Terrain {
		  std::string name;
		  unsigned int tile;
		  std::map<std::string, std::string> property;
	  };

	  struct Tile {
		  unsigned int id;
		  std::vector<unsigned int> terrain;
		  std::map<std::string, std::string> property;
	  };
	  struct Tileset {
		  std::string name;
		  unsigned int firstGID;
		  std::string source;
		  unsigned int tileWidth;
		  unsigned int tileHeight;
		  unsigned int spacing;
		  unsigned int margin;
		  int offsetX;
		  int offsetY;
		  std::map<std::string, std::string> property;
		  std::map<int, Tile>  tile;
		  std::map<std::string, Terrain>  terrain;
		  TilesetImage image;
	  };

	 

	  std::map<std::string, Tileset>  tilesetList;
	  std::vector<Terrain> terrainList;
	  std::vector<Tile> tileList;
  



      Map mapInfo;
      std::vector<Tileset> tilesetListTEMP;
      std::map<std::string, TileLayer> tileLayer;
      std::map<std::string, ObjectGroup> objectGroup;
      std::map<std::string, ImageLayer> imageLayer;
    protected:
    private:
  };

}
#endif // TMXPARSER_H
