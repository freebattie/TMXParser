#include "TMXParser.h"

#include <cstdlib>
#include <iostream>
#include <sstream>





namespace TMX {
  

  Parser::Parser(const char* filename)
  {
    load( filename );
  }

  Parser::Parser()
  {
  }

  Parser::~Parser()
  {
  }

  bool Parser::load(const char* filename)
  {
	  
	  rapidxml::file<> file(filename);
	  std::string version = VERSION;
	  rapidxml::xml_document<> doc;
	  rapidxml::xml_node<>* root_node;
	  doc.parse<0>(file.data());
	  root_node = doc.first_node("map");
	  // checks the file version 
	  if (root_node->first_attribute("version")->value() != version) {
		  std::cout << "ERROR: Map version mismatch. Required version: " << VERSION << "." << std::endl;
		  return false;
	  }
	
	    load(doc);
	  


	  return true;

  }

  void Parser::load(rapidxml::xml_document<> &doc)
  {

	  rapidxml::xml_node<>* root_node;
    //get root nodes
      root_node = doc.first_node( "map" );
	  
    //load map element
    
	
    mapInfo.version = root_node->first_attribute( "version" )->value();
 //   std::cout << "Version: " << mapInfo.version << std::endl;
    mapInfo.orientation = root_node->first_attribute( "orientation" )->value();
  //  std::cout << "Orientation: " << mapInfo.orientation << std::endl;
    mapInfo.width = std::atoi( root_node->first_attribute( "width" )->value() );
  //  std::cout << "Width: " << mapInfo.width << std::endl;
    mapInfo.height = std::atoi( root_node->first_attribute( "height" )->value() );
  //  std::cout << "Height: " << mapInfo.height << std::endl;
    mapInfo.tileWidth = std::atoi( root_node->first_attribute( "tilewidth" )->value() );
   // std::cout << "Tile Width: " << mapInfo.tileWidth << std::endl;
    mapInfo.tileHeight = std::atoi( root_node->first_attribute( "tileheight" )->value() );
   // std::cout << "Tile Height: " << mapInfo.tileHeight << std::endl;
	
    if( root_node->first_attribute( "backgroundcolor" ) != 0 ) {
      mapInfo.backgroundColor = root_node->first_attribute( "backgroundcolor" )->value();
    //  std::cout << "Background color : " << mapInfo.backgroundColor << std::endl;
    }
	
	
	
	
	
    if( root_node->first_node( "properties" ) != 0 ) {
      for( rapidxml::xml_node<>* properties_node = root_node->first_node( "properties" )->first_node( "property" ); properties_node; properties_node = properties_node->next_sibling() ) {
        mapInfo.property[properties_node->first_attribute( "name" )->value()] = properties_node->first_attribute( "value" )->value();
      }

     // std::cout << "Properties: " << std::endl;

     /* for( std::map<std::string, std::string>::iterator it = mapInfo.property.begin(); it != mapInfo.property.end(); ++it ) {
   
      }*/
    }

    /*std::cout << std::endl;*/

    for( rapidxml::xml_node<>* tileset_node = root_node->first_node( "tileset" ); tileset_node; tileset_node = tileset_node->next_sibling( "tileset" ) ) {
      Tileset tmpTileset;
      tmpTileset.firstGID = std::atoi( tileset_node->first_attribute( "firstgid" )->value() );
	  rapidxml::xml_node<>* image_node = tileset_node->first_node("image");
      tmpTileset.source = image_node->first_attribute( "source" )->value();
   
	  tilesetListTEMP.push_back( tmpTileset );
    }

	for (rapidxml::xml_node<>* layer_node = root_node->first_node("layer"); layer_node; layer_node = layer_node->next_sibling("layer")) {
		TileLayer layer;
		layer.name = layer_node->first_attribute("name")->value();

		if (layer_node->first_attribute("opacity") != 0)
		{
			layer.opacity = std::atof(layer_node->first_attribute("opacity")->value());
		}
		else
		{
			layer.opacity = 1;
		}
		if (layer_node->first_attribute("visible") != 0)
		{
			layer.visible = layer_node->first_attribute("visible")->value();
		}
		else
		{
			layer.visible = 1;
		}
    //  std::cout << std::endl << "Layer Name: " << layer.name << std::endl;
	 
      if( layer_node->first_node( "properties" ) != 0 ) {
        for( rapidxml::xml_node<>* properties_node = layer_node->first_node( "properties" )->first_node( "property" ); properties_node; properties_node = properties_node->next_sibling() ) {
          layer.property[properties_node->first_attribute( "name" )->value()] = properties_node->first_attribute( "value" )->value();
        }

      // std::cout << "Properties: " << std::endl;

        for( std::map<std::string, std::string>::iterator it = layer.property.begin(); it != layer.property.end(); ++it ) {
        // std::cout << "-> " << it->first << " : " << it->second << std::endl;
        }

      }

      rapidxml::xml_node<>* data_node = layer_node->first_node( "data" );
      layer.data.encoding = data_node->first_attribute( "encoding" )->value();
     // std::cout << "Layer Encoding: " << layer.data.encoding << std::endl;

      if( data_node->first_attribute( "compression" ) > 0 ) {




        layer.data.compression = data_node->first_attribute( "compression" )->value();
     //   std::cout << "Layer Compression: " << layer.data.compression << std::endl;
      }

      layer.data.contents = data_node->value();
    //  std::cout << "Layer Data: " << layer.data.contents << std::endl;
      tileLayer[layer.name] = layer;
    }


	// is some of the code at the end of main supose to go in here? so you get x and y? if you have it on?
	for (rapidxml::xml_node<>* oGroup_node = root_node->first_node("objectgroup"); oGroup_node; oGroup_node = oGroup_node->next_sibling("objectgroup")) {
		ObjectGroup oGroup;
		std::cout << std::endl;

		if (oGroup_node->first_attribute("color") != 0) {
			oGroup.color = oGroup_node->first_attribute("color")->value();
			
		}
		else if (oGroup_node->first_attribute("color") == 0) {
			oGroup.color = "FFFFFF";
		}
		//std::cout << "Object Group Color: " << oGroup.color << std::endl;

		oGroup.name = oGroup_node->first_attribute("name")->value();
		//std::cout << "Object Group Name: " << oGroup.name << std::endl;


		if (oGroup_node->first_attribute("opacity") != 0) {
			oGroup.opacity = std::atof(oGroup_node->first_attribute("opacity")->value());

		}
	    if (oGroup_node->first_attribute("opacity") == 0) {
			oGroup.opacity = 1;
		}
		//std::cout << "Object Group Opacity: " << oGroup.opacity << std::endl;


		if (oGroup_node->first_attribute("visible") != 0) {
			oGroup.visible = std::atoi(oGroup_node->first_attribute("visible")->value());
		}
	    if (oGroup_node->first_attribute("visible") == 0) {
			oGroup.visible = 1;
		}

		//std::cout << "Object Group Visible: " << oGroup.visible << std::endl;
		
			
      if( oGroup_node->first_node( "properties" ) != 0 ) {
        for( rapidxml::xml_node<>* properties_node = oGroup_node->first_node( "properties" )->first_node( "property" ); properties_node; properties_node = properties_node->next_sibling() ) {
          oGroup.property[properties_node->first_attribute( "name" )->value()] = properties_node->first_attribute( "value" )->value();

        }

       // std::cout << "Properties: " << std::endl;

        for( std::map<std::string, std::string>::iterator it = oGroup.property.begin(); it != oGroup.property.end(); ++it ) {
        //  std::cout << "-> " << it->first << " : " << it->second << std::endl;
        }



      }
	 
		  
	  for (rapidxml::xml_node<>* objects_node = oGroup_node->first_node("object"); objects_node; objects_node = objects_node->next_sibling("object")) {

		 Object object;

		  if (objects_node->first_attribute("name") == 0)
		  {
			 
			  oGroup.object["No Name"].name = "No name given in TIled Editor please add name";
			//  std::cout << "objects name: " << oGroup.object["No Name"].name << std::endl;
		  }
		  else
		  {
			  oGroup.object[objects_node->first_attribute("name")->value()].name = objects_node->first_attribute("name")->value();
		// std::cout << "objects name: " << oGroup.object[objects_node->first_attribute("name")->value()].name << std::endl;
		  }

		  if (objects_node->first_attribute("gid") != 0)
		  {
			  oGroup.object[objects_node->first_attribute("name")->value()].gid = std::atoi(objects_node->first_attribute("gid")->value());
			 // std::cout << "objects gid: " << oGroup.object[objects_node->first_attribute("gid")->value()].width << std::endl;
		  }
		  oGroup.object[objects_node->first_attribute("name")->value()].x = std::atoi(objects_node->first_attribute("x")->value());
		//  std::cout << "objects X: " << oGroup.object[objects_node->first_attribute("name")->value()].x << std::endl;

		  oGroup.object[objects_node->first_attribute("name")->value()].y = std::atoi(objects_node->first_attribute("y")->value());
		// std::cout << "objects y: " << oGroup.object[objects_node->first_attribute("name")->value()].y << std::endl;
		  if (objects_node->first_attribute("width") != 0)
		  {
			  oGroup.object[objects_node->first_attribute("name")->value()].width = std::atoi(objects_node->first_attribute("width")->value());
			//  std::cout << "objects width: " << oGroup.object[objects_node->first_attribute("width")->value()].width << std::endl;
			}
		  if (objects_node->first_attribute("height") != 0)
		  {
			  oGroup.object[objects_node->first_attribute("name")->value()].height = std::atoi(objects_node->first_attribute("height")->value());
			//  std::cout << "objects Height: " << oGroup.object[objects_node->first_attribute("height")->value()].height << std::endl;
		  }
		  if (objects_node->first_attribute("rotation") != 0)
		  {
			  oGroup.object[objects_node->first_attribute("name")->value()].rotation = std::atoi(objects_node->first_attribute("rotation")->value());
		  }
		  if (objects_node->first_node("properties") != 0) {
			  for (rapidxml::xml_node<>* properties_node = objects_node->first_node("properties")->first_node("property"); properties_node; properties_node = properties_node->next_sibling()) {


				  oGroup.object[objects_node->first_attribute("name")->value()].property[objects_node->first_attribute("name")->value()] = properties_node->first_attribute("value")->value();

				//  std::cout << "objects propertyes: " << std::endl;
				  for (std::map<std::string, std::string>::iterator it = oGroup.object[properties_node->first_attribute("name")->value()].property.begin(); it != oGroup.object[properties_node->first_attribute("name")->value()].property.end(); ++it) {
					//  std::cout << "-> " << it->first << " : " << it->second << std::endl;
				  }
			  }
		  }
		  
		  for (rapidxml::xml_node<>* object_type_node_elip = objects_node->first_node("ellipse"); object_type_node_elip; object_type_node_elip = object_type_node_elip->next_sibling("ellipse")) {
			  if (objects_node->first_node("ellipse") != 0) {

						oGroup.object[objects_node->first_attribute("name")->value()].typeName = "ellipse";

			  }
		  }
			  for (rapidxml::xml_node<>* object_type_node_pol = objects_node->first_node("polygon"); object_type_node_pol; object_type_node_pol = object_type_node_pol->next_sibling("polygon")) {
				  if (object_type_node_pol->first_attribute("points") != 0)
				  {
						 oGroup.object[objects_node->first_attribute("name")->value()].typeName = "polygon";
					

						 oGroup.object[objects_node->first_attribute("name")->value()].polygon[objects_node->first_attribute("name")->value()].points = object_type_node_pol->first_attribute("points")->value();
					
				  }
			  }
			  for (rapidxml::xml_node<>* object_type_node_line = objects_node->first_node("polyline"); object_type_node_line; object_type_node_line = object_type_node_line->next_sibling("polyline")) {
				  if (object_type_node_line->first_attribute("points") != 0)
				  {
						oGroup.object[objects_node->first_attribute("name")->value()].typeName = "polyline";
					

						oGroup.object[objects_node->first_attribute("name")->value()].polygon[objects_node->first_attribute("name")->value()].points = object_type_node_line->first_attribute("points")->value();
					
				  }
			  }
			  if (objects_node->first_node("ellipse") == 0 &&
				  objects_node->first_node("polyline") == 0 &&
				  objects_node->first_node("polygon") == 0) {
				  oGroup.object[objects_node->first_attribute("name")->value()].typeName = "square";
			  }
		 
	  }
	
	  
      objectGroup[oGroup.name] = oGroup;
    }





    for( rapidxml::xml_node<>* image_node = root_node->first_node( "imagelayer" ); image_node; image_node = image_node->next_sibling( "imagelayer" ) ) {
      ImageLayer imgLayer;
    //  std::cout << std::endl;
      imgLayer.name = image_node->first_attribute( "name" )->value();
     // std::cout << "Image Layer Name: " << imgLayer.name << std::endl;

	  if (image_node->first_attribute("opacity") != 0) {
		  imgLayer.opacity = std::atoi(image_node->first_attribute("opacity")->value());
	  }
	  else if (image_node->first_attribute("visible") == 0) {
		  imgLayer.opacity = 1;
	  }
    //   std::cout << "Image Layer Opacity: " << imgLayer.opacity << std::endl;

		  if (image_node->first_attribute("visible") != 0) {
			  imgLayer.visible = std::atoi(image_node->first_attribute("visible")->value());
		  }
		  else if (image_node->first_attribute("visible") == 0) {
			  imgLayer.visible = 1;
		  }
      
     // std::cout << "Image Layer Visibility: " << imgLayer.visible << std::endl;

      imgLayer.image.source = image_node->first_node( "image" )->first_attribute( "source" )->value();
     // std::cout << "Image Layer Source: " << imgLayer.visible << std::endl;

      if( image_node->first_node( "image" )->first_attribute( "trans" ) != 0 ) {
        imgLayer.image.transparencyColor = image_node->first_node( "image" )->first_attribute( "trans" )->value();
       // std::cout << "Image Layer Transparent Color: " << imgLayer.image.transparencyColor << std::endl;
      }
	  

      if( image_node->first_node( "properties" ) != 0 ) {
        for( rapidxml::xml_node<>* properties_node = image_node->first_node( "properties" )->first_node( "property" ); properties_node; properties_node = properties_node->next_sibling( "property" ) ) {
          imgLayer.property[properties_node->first_attribute( "name" )->value()] = properties_node->first_attribute( "value" )->value();
        }

       // std::cout << "Properties: " << std::endl;

        for( std::map<std::string, std::string>::iterator it = imgLayer.property.begin(); it != imgLayer.property.end(); ++it ) {
        //  std::cout << "-> " << it->first << " : " << it->second << std::endl;
        }
      }

      imageLayer[imgLayer.name] = imgLayer;
    }


	// here starts old TSX file part
	//get root node
	root_node = doc.first_node("map");

	//parse tileset element
	for (rapidxml::xml_node<>* tileset_node = root_node->first_node("tileset"); tileset_node; tileset_node = tileset_node->next_sibling("tileset")) {
		Tileset tileset;
		tileset.name = tileset_node->first_attribute("name")->value();
		tileset.tileWidth = std::atoi(tileset_node->first_attribute("tilewidth")->value());
		tileset.tileHeight = std::atoi(tileset_node->first_attribute("tileheight")->value());

		if (tileset_node->first_attribute("spacing") != 0) {
			tileset.spacing = std::atoi(tileset_node->first_attribute("spacing")->value());
		}
		else
		{
			tileset.spacing = 0;
		}
		if (tileset_node->first_attribute("margin") != 0) {
			tileset.margin = std::atoi(tileset_node->first_attribute("margin")->value());
		}
		else
		{
			tileset.margin = 0;
		}
		if (tileset_node->first_attribute("tileoffset") != 0) {
			tileset.offsetX = std::atoi(tileset_node->first_node("tileoffset")->first_attribute("x")->value());
			tileset.offsetY = std::atoi(tileset_node->first_node("tileoffset")->first_attribute("y")->value());
		}
		else
		{
			tileset.offsetY = 0;
			tileset.offsetX = 0;
		}

		//parse tileset properties
		if (tileset_node->first_node("properties") != 0) {
			for (rapidxml::xml_node<>* properties_node = tileset_node->first_node("properties")->first_node("property"); properties_node; properties_node = properties_node->next_sibling()) {
				tileset.property[properties_node->first_attribute("name")->value()] = properties_node->first_attribute("value")->value();
				std::cout << "tileset prop: " << tileset.property[properties_node->first_attribute("name")->value()] << std::endl;
			}
		}

		//parse tileset image
		tileset.image.source = tileset_node->first_node("image")->first_attribute("source")->value();
		tileset.image.width = std::atoi(tileset_node->first_node("image")->first_attribute("width")->value());
		tileset.image.height = std::atoi(tileset_node->first_node("image")->first_attribute("height")->value());

		if (tileset_node->first_node("image")->first_attribute("trans") != 0) {
			tileset.image.transparentColor = std::atoi(tileset_node->first_node("image")->first_attribute("trans")->value());
		}

		if (tileset_node->first_node("tile") != 0) {
			for (rapidxml::xml_node<>* tile_node = tileset_node->first_node("tile"); tile_node; tile_node = tile_node->next_sibling()) {

				//tile - id

				if (tile_node->first_attribute("terrain") != 0)
				{
					tileset.tile[std::atoi(tile_node->first_attribute("id")->value())].id = std::atoi(tile_node->first_attribute("id")->value());
					//tile - terrain
					std::string tmp = tile_node->first_attribute("terrain")->value();
					std::stringstream ss(tmp);
					std::string tmpValue;

					while (std::getline(ss, tmpValue, ',')) {
						tileset.tile[std::atoi(tile_node->first_attribute("id")->value())].terrain.push_back(std::atoi(tmpValue.c_str()));
					}

					//parse tile properties MAYBE WRONG
					if (tile_node->first_node("properties") != 0) {
						for (rapidxml::xml_node<>* properties_node = tile_node->first_node("properties")->first_node("property"); properties_node; properties_node = properties_node->next_sibling()) {
							tileset.tile[std::atoi(tile_node->first_attribute("id")->value())].property[properties_node->first_attribute("name")->value()] = properties_node->first_attribute("value")->value();
						}
					}


				}
			}
		}

		if (tileset_node->first_node("terraintypes") != 0) {
			for (rapidxml::xml_node<>* terrain_node = tileset_node->first_node("terraintypes")->first_node("terrain"); terrain_node; terrain_node = terrain_node->next_sibling()) {
				
				tileset.terrain[terrain_node->first_attribute("name")->value()].name = terrain_node->first_attribute("name")->value();
				tileset.terrain[terrain_node->first_attribute("name")->value()].tile = std::atoi(terrain_node->first_attribute("tile")->value());
				//std::cout << "terrain name: " << terrain.name << std::endl;
				//std::cout << "terrain tile: " << terrain.tile << std::endl;
				//parse tileset terrain properties
				if (terrain_node->first_node("properties") != 0) {
					for (rapidxml::xml_node<>* properties_node = terrain_node->first_node("properties")->first_node("property"); properties_node; properties_node = properties_node->next_sibling()) {
						tileset.terrain[terrain_node->first_attribute("name")->value()].property[properties_node->first_attribute("name")->value()] = properties_node->first_attribute("value")->value();
					}
				}

				
			}
		}
		

		tilesetList[tileset.name] = tileset;
	}
	//parse tileset terrains
	

	//pare tile
	
    
  }
 
}
