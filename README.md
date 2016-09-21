**NOTE:**
this is a forked TMXParser from  solar-storm-studios/TMXParser that also has been merged whit solar-storm-studios/TSXParser to one ccp and header file. added object support and object property support, also added terrain and tile support for more then one tileset.



#TMXParser

TMXParser is a Tiled Map Editor *.tmx map xml file parser. It is currently a completely functionless library designed to provide instant access to the *.tmx file data. TMXParser can be included (along with rapidxml) into your project or statically linked.

##Features

* Completely functionless giving access to the raw map data.
* Complete properties support.
* Support for multiple:
  * Tilesets
  * Tile Layers
  * Object Groups
  * Objects 
  * Image Layers
  * Ellipse
  * Polygon
  * Polyline
  * Tile Flip(raw data)
  * Tile Rotation(raw data)

##TODO


* Implement full API



#The ConsoleExample.zip is a example app for printing all info to console.
#Here is a example of a main() to print to console.
```c++


#include <iostream>
#include "TMXParser.h"
#include <iomanip>
#include <locale>
#include <sstream>
#include <string> 

int main()
{
	TMX::Parser tmx;
	
	tmx.load("test2.tmx");
	
	///////////////////////
	
	
	
	///////////////////////
	
	

	std::cout << std::endl;
	std::cout << "Map Version: " << tmx.mapInfo.version << std::endl;
	std::cout << "Map Orientation: " << tmx.mapInfo.orientation << std::endl;
	std::cout << "Map Width: " << tmx.mapInfo.width << std::endl;
	std::cout << "Map Height: " << tmx.mapInfo.height << std::endl;
	std::cout << "Tile Width: " << tmx.mapInfo.tileWidth << std::endl;
	std::cout << "Tile Height: " << tmx.mapInfo.tileHeight << std::endl;
	std::cout << "Background Color: " << tmx.mapInfo.backgroundColor << std::endl;
	std::cout << "Properties: " << std::endl;
	for (std::map<std::string, std::string>::iterator it = tmx.mapInfo.property.begin(); it != tmx.mapInfo.property.end(); ++it) {
		std::cout << "-> " << it->first << " : " << it->second << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < tmx.tilesetList.size(); i++) {
		std::cout << "Tileset[ First GID: " << tmx.tilesetListTEMP[i].firstGID << " Source: " << tmx.tilesetListTEMP[i].source << " ]" << std::endl;
	}
											/////////////////////////
											//TSXParse starts here//
											///////////////////////
	
											/////////////////////////////
											// prints the tileset INFO//  
											///////////////////////////
	
	for (std::map<std::string, TMX::Parser::Tileset>::iterator it = tmx.tilesetList.begin(); it != tmx.tilesetList.end(); ++it) {
		std::cout << std::endl;
		std::cout << "Name  of Tileset: " << tmx.tilesetList[it->first].name << std::endl;
		std::cout << "Tileset margin: " << tmx.tilesetList[it->first].margin << std::endl;
		std::cout << "Tileset spacing: " << tmx.tilesetList[it->first].spacing << std::endl;
		std::cout << "Tileset offsetX: " << tmx.tilesetList[it->first].offsetX << std::endl;
		std::cout << "Tileset offsetY: " << tmx.tilesetList[it->first].offsetY << std::endl;
		std::cout << "Tileset tileHeight: " << tmx.tilesetList[it->first].tileHeight << std::endl;
		std::cout << "Tileset tileWidth: " << tmx.tilesetList[it->first].tileWidth << std::endl;
		std::cout << "Tileset Image source: " << tmx.tilesetList[it->first].image.source<< std::endl;
		std::cout << "Tileset Image height: " << tmx.tilesetList[it->first].image.height<< std::endl;
		std::cout << "Tileset Image width: " << tmx.tilesetList[it->first].image.width<< std::endl;
		std::cout << "Tileset Image transparentColor: " << tmx.tilesetList[it->first].image.transparentColor << std::endl;
		std::cout << "Tileset Propertyes:  " << std::endl;
		for (std::map<std::string, std::string>::iterator it2 = tmx.tilesetList[it->first].property.begin(); it2 != tmx.tilesetList[it->first].property.end(); ++it2) {

			std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
		}

		for (auto it2 = tmx.tilesetList[it->first].terrain.begin(); it2 != tmx.tilesetList[it->first].terrain.end(); ++it2) {
			std::cout << "Tileset Terrain Name: " << tmx.tilesetList[it->first].terrain[it2->first].name << std::endl;
			std::cout << "Tileset Terrain Tile: " << tmx.tilesetList[it->first].terrain[it2->first].tile << std::endl;
			std::cout << "Terrain Propertyes:  " << std::endl;
			for (std::map<std::string, std::string>::iterator it3 = tmx.tilesetList[it->first].terrain[it2->first].property.begin(); it3 != tmx.tilesetList[it->first].terrain[it2->first].property.end(); ++it3) {

				std::cout << "-> " << it3->first << " : " << it3->second << std::endl;
			}
			std::cout << std::endl;
		}
		

		std::cout << std::endl;
		for (auto it2 = tmx.tilesetList[it->first].tile.begin(); it2 != tmx.tilesetList[it->first].tile.end(); ++it2) {
			
			

				
				std::cout << "Tile ID " << tmx.tilesetList[it->first].tile[it2->first].id << " - ";
				for (int j = 0; j < tmx.tilesetList[it->first].tile[it2->first].terrain.size(); ++j)
				{
					
					if (j != 0)
					{
						std::cout << "," << tmx.tilesetList[it->first].tile[it2->first].terrain[j];
					}
					else if (j == tmx.tilesetList[it->first].tile[it2->first].terrain.size())
					{
						std::cout << tmx.tilesetList[it->first].tile[it2->first].terrain[j];
					}
					else
					{
						std::cout << tmx.tilesetList[it->first].tile[it2->first].terrain[j];
					}

				}
				std::cout << std::endl;
				std::cout << "Propertyes:  " << std::endl;
				for (std::map<std::string, std::string>::iterator it3 = tmx.tilesetList[it->first].tile[it2->first].property.begin(); it3 != tmx.tilesetList[it->first].tile[it2->first].property.end(); ++it3) {

					std::cout << "-> " << it3->first << " : " << it3->second << std::endl;
				}
				std::cout << std::endl;



		}

	}
												////////////////////////////////
												// prints the terrain INFO//
												//////////////////////////////

	for (int i = 0; i < tmx.terrainList.size(); ++i)
	{
		std::cout << "Terrain: " << tmx.terrainList[i].name << " - " << tmx.terrainList[i].tile << std::endl;

		std::map<std::string, std::string>::iterator iter = tmx.terrainList[i].property.begin();
		std::map<std::string, std::string>::iterator end_iter = tmx.terrainList[i].property.end();

		for (; iter != end_iter; ++iter)
		{
			std::cout << "->" << iter->first << " : " << iter->second << std::endl;
		}
	}



														/////////////////////////
														//TSXParse ends here//
														///////////////////////

													////////////////////////////////
													// prints the tile Layer INFO//
													//////////////////////////////

	for (std::map<std::string, TMX::Parser::TileLayer>::iterator                it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); ++it) {
		std::cout << "Name  of the Tiled Layer: " << tmx.tileLayer[it->first].name << std::endl;
		std::cout << "encoding : " << tmx.tileLayer[it->first].data.encoding << std::endl;
		std::cout << "Compression : " << tmx.tileLayer[it->first].data.compression << std::endl;
		std::cout << "opacety : " << tmx.tileLayer[it->first].opacity << std::endl;
		std::cout << "is it visible : " << tmx.tileLayer[it->first].visible << std::endl;
		std::cout << "Propertyes:  " << std::endl;
		for (std::map<std::string, std::string>::iterator it2 = tmx.tileLayer[it->first].property.begin(); it2 != tmx.tileLayer[it->first].property.end(); ++it2) {

			std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
		}
		std::cout << "tile layout : " << tmx.tileLayer[it->first].data.contents << std::endl;
		
		
	
	}




								//////////////////////////////////////////////////////////////////////
								// prints the Object Group and objects insinde the object group INFO//
								//////////////////////////////////////////////////////////////////////

	for (std::map<std::string, TMX::Parser::ObjectGroup>::iterator it = tmx.objectGroup.begin(); it != tmx.objectGroup.end(); ++it) {
		std::cout << std::endl;
		std::cout << "Name  of ObjectGroup Layer: " << tmx.objectGroup[it->first].name << std::endl;
		std::cout << "Color : " << tmx.objectGroup[it->first].color << std::endl;
		std::cout << "opacety : " << tmx.objectGroup[it->first].opacity << std::endl;
		std::cout << "visible : " << tmx.objectGroup[it->first].visible << std::endl;
		std::cout <<  "Propertyes:  "  << std::endl;
			for (std::map<std::string, std::string>::iterator it2 = tmx.objectGroup[it->first].property.begin(); it2 != tmx.objectGroup[it->first].property.end(); ++it2) {
			
				std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
			}

			for (std::map<std::string, TMX::Parser::Object>::iterator it2 = tmx.objectGroup[it->first].object.begin(); it2 != tmx.objectGroup[it->first].object.end(); ++it2) {
				if (tmx.objectGroup[it->first].object[it2->first].name.size() != 0)
				{
					std::cout << std::endl;
					std::cout << "Name of objects in object group :" << tmx.objectGroup[it->first].object[it2->first].name << std::endl;
					if (tmx.objectGroup[it->first].object[it2->first].gid != 0)
					{
						std::cout << "Gid :" << tmx.objectGroup[it->first].object[it2->first].gid << std::endl;
					}
				
					std::cout << "Rotation  :" << tmx.objectGroup[it->first].object[it2->first].rotation << std::endl;
					std::cout << "height " << tmx.objectGroup[it->first].object[it2->first].height << std::endl; 
					std::cout << "Width " << tmx.objectGroup[it->first].object[it2->first].width << std::endl;
					std::cout << "x " << tmx.objectGroup[it->first].object[it2->first].x << std::endl;
					std::cout << "y " << tmx.objectGroup[it->first].object[it2->first].y << std::endl;
					std::cout << "type of object :" << tmx.objectGroup[it->first].object[it2->first].typeName << std::endl;
					std::cout << "polygon :" << tmx.objectGroup[it->first].object[it2->first].polygon[it2->first].points << std::endl;
					std::cout << "polyline points  :" << tmx.objectGroup[it->first].object[it2->first].polyline[it2->first].points << std::endl;
					std::cout << "Propertyes:  " << std::endl;
					for (std::map<std::string, std::string>::iterator it3 = tmx.objectGroup[it->first].object[it2->first].property.begin(); it3 != tmx.objectGroup[it->first].object[it2->first].property.end(); ++it3) {

						std::cout << "-> " << it3->first << " : " << it3->second << std::endl;
					}
					std::cout << std::endl;
					
				}

			}

	}

	for (std::map<std::string, TMX::Parser::ImageLayer>::iterator it = tmx.imageLayer.begin(); it != tmx.imageLayer.end(); ++it) {

		std::cout << "Name  of the Img Layer : " << tmx.imageLayer[it->first].name << std::endl;
		std::cout << "Opasety : " << tmx.imageLayer[it->first].opacity << std::endl;
		std::cout << "visible : " << tmx.imageLayer[it->first].visible<< std::endl;
		std::cout << "img location  :" << tmx.imageLayer[it->first].image.source << std::endl;
		std::cout << "img transparency :" << tmx.imageLayer[it->first].image.transparencyColor << std::endl;
		std::cout << "Propertyes:  " << std::endl;
			for (std::map<std::string, std::string>::iterator it2 = tmx.imageLayer[it->first].property.begin(); it2 != tmx.imageLayer[it->first].property.end(); ++it2) {

				std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
			}
			
	}




  	return 0;
}

```
