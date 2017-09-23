/*
 * File:   map.h
 * Authors: Christian Auby(original version), James Giang (Edited for this game)
 *
 */

#ifndef MAP_H
#define MAP_H

#include <string>
#include <list>

#include "object.h"

class Obstacle;

namespace Json
{
	class Value;
}

// Class with a single public static function that loads a map into an object list
class Map
{
public:
	// Load map from Tiled JSON file
	static bool load(std::string filename, std::list<Object*>& objects, std::list<Obstacle*>& obstacles, std::vector<sf::FloatRect*>& spawnpoints, std::list<Obstacle *> & stores);

private:
	// Handles regular layers
	static void loadLayer(Json::Value& layer, std::list<Object*>& objects, TileSize tileSize);

	// Handles object layers
	static void loadObjects(Json::Value& root, Json::Value& layer, std::list<Object*>& objects, TileSize tileSize);

	static void loadObstacles(Json::Value &layer, std::list<Obstacle*> &obstacles, TileSize tileSize);

	static void loadSpawnpoints(Json::Value &layer, std::vector<sf::FloatRect*> &spawnpoints);
};

#endif
