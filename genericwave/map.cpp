/*
 * File:   map.cpp
 * Authors: Christian Auby(original version), James Giang (Edited for this game)
 *
 */

#include <fstream>
#include <cstring>

#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>

#include "map.h"
#include "object.h"
#include <iostream>
#include "sprite.h"
#include "layer.h"
#include "Obstacle.h"

bool Map::load(std::string filename, std::list<Object*>& objects, std::list<Obstacle*>& obstacles, std::vector<sf::FloatRect*>& spawnpoints)
{
	// Will contain the data we read in
	Json::Value root;

	// Parses the file
	Json::Reader reader;

	// Stream used for reading the data file. The data file has been saved as JSON in Tiled
	std::ifstream file(filename);

	// Read data from file into root object
	bool parsingSuccessful = reader.parse(file, root);

	// Check for success
	if (!parsingSuccessful) {
		std::cout << "Failed to read  data." << std::endl;
		return false;
	}

	// Get tile size information
	TileSize tileSize;
	tileSize.x = root["tilesets"][0u]["tilewidth"].asInt();
	tileSize.y = root["tilesets"][0u]["tileheight"].asInt();
	tileSize.s = root["tilesets"][0u]["spacing"].asInt();

	// Read in each layer
	for (Json::Value& layer: root["layers"])
	{
		if (layer["name"].asString() == "objects")
        {
            loadObjects(root, layer, objects, tileSize);
        }
        else if(layer["name"].asString() == "obstacles"){
            //std::cout << "Loading obstacles" << std::endl;
            loadObstacles(layer, obstacles, tileSize);
        }
        else if(layer["name"].asString() == "spawn"){
            //std::cout << "Loading obstacles" << std::endl;
            loadSpawnpoints(layer, spawnpoints);
        }
		else
        {
            loadLayer(layer, objects, tileSize);
        }
	}

	// Read in tileset (Should be handled by a resource handler)
	sf::Texture* tileset = new sf::Texture();
	tileset->loadFromFile("Bilder/Stages/" + root["tilesets"][0u]["image"].asString());

	// Assign tileset to every object
	for (Object* object: objects)
		object->texture = tileset;

	return true;
}

void Map::loadLayer(Json::Value& layer, std::list<Object*>& objects, TileSize tileSize)
{
	Layer* tmp = new Layer(tileSize);

	// Store info on layer
	tmp->width = layer["width"].asInt();
	tmp->height = layer["height"].asInt();

	// Clear tilemap
	memset(tmp->tilemap, 0, sizeof(tmp->tilemap));

	// Read in tilemap
	for (size_t i = 0; i < layer["data"].size(); i++)
		tmp->tilemap[i % tmp->width][i / tmp->width] = layer["data"][(int)i].asInt();

	objects.push_back(tmp);
}

void Map::loadObjects(Json::Value& root, Json::Value& layer, std::list<Object*>& objects, TileSize tileSize)
{
	// Get all objects from layer
	for (Json::Value& object: layer["objects"])
	{
		Sprite* sprite = new Sprite(tileSize);

		// Load basic object info
		sprite->x = object["x"].asInt();
		sprite->y = object["y"].asInt() - sprite->tileSize.y;
        // std::cout << "y: " << sprite->y <<std::endl;
		sprite->id = object["gid"].asInt();

		// Load animation data
		Json::Value& tileInfo = root["tilesets"][0u]["tiles"][std::to_string(sprite->id - 1)];
		sprite->frame = 0;
		sprite->frameCount = tileInfo["animation"].size();
		sprite->frameDuration = tileInfo["animation"][0u]["duration"].asInt();

		objects.push_back(sprite);
	}
}

void Map::loadObstacles(Json::Value& layer, std::list<Obstacle*>& obstacles, TileSize tileSize)
{
    // Get all objects from layer
    for (Json::Value& object: layer["objects"])
    {
        Obstacle* obstacle = new Obstacle();

        // Load basic object info
        // NB!!!    Size must be set first for side collision to be implemented correctly
        //          Check Obstacle members for more detail.
        obstacle->setSize(sf::Vector2f(object["width"].asInt(), object["height"].asInt()));
        obstacle->setPosition(object["x"].asInt(), object["y"].asInt());

        // For testing
        obstacle->setFillColor(sf::Color::Green);
        obstacle->setOutlineColor(sf::Color::Green);
        obstacle->setOutlineThickness(1);

        obstacles.push_back(obstacle);
    }
}

void Map::loadSpawnpoints(Json::Value &layer, std::vector<sf::FloatRect *> &spawnpoints) {
    // Get all objects from layer
    for (Json::Value& object: layer["objects"])
    {
        sf::FloatRect* spawn = new sf::FloatRect();
        spawn->width = object["width"].asInt();
        spawn->height = object["height"].asInt();
        spawn->left = object["x"].asInt();
        spawn->top = object["y"].asInt();

        spawnpoints.push_back(spawn);
    }
}
