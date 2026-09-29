#include "BlockRegistry.h"
#include <stdexcept>

std::array<BlockProperties, (size_t)BlockType::Count> BlockRegistry::s_properties;
bool BlockRegistry::s_initialized = false;

void BlockRegistry::initialize(){
    if (s_initialized) return;

    /*
    
        AIR
    
    */
   {
    BlockProperties& props = s_properties[(size_t)BlockType::Air];
    props.name = "air";
    props.isSolid = true;
    props.isTransparent = true;
    props.isOpaque = false;
   }

   /*
   
        GRASS

   */
  {
    BlockProperties& props = s_properties[(size_t)BlockType::Grass];
    props.name = "grass";
    props.isSolid = true;
    props.isTransparent = false;
    props.isOpaque = true;

    props.faceTiles[(size_t)BlockFace::Top]     = {0, 0};
    props.faceTiles[(size_t)BlockFace::Bottom]  = {2, 0};
    props.faceTiles[(size_t)BlockFace::North]   = {1, 0};
    props.faceTiles[(size_t)BlockFace::South]   = {1, 0};
    props.faceTiles[(size_t)BlockFace::East]    = {1, 0};
    props.faceTiles[(size_t)BlockFace::West]    = {1, 0};
  }

  /*
  
    DIRT
  
  */
  {
    BlockProperties& props = s_properties[(size_t)BlockType::Dirt];
    props.name = "dirt";
    props.isSolid = true;
    props.isTransparent = false;
    props.isOpaque = true;

    props.faceTiles.fill( {2, 0} );
  }

  /*
  
    STONE
  
  */
 {
    BlockProperties& props = s_properties[(size_t)BlockType::Stone];
    props.name = "stone";
    props.isSolid = true;
    props.isTransparent = false;
    props.isOpaque = true;

    props.faceTiles.fill( {3, 0} );
 }

 /*
 
    SAND
 
 */
 {
    BlockProperties& props = s_properties[(size_t)BlockType::Sand];
    props.name = "sand";
    props.isSolid = true;
    props.isTransparent = false;
    props.isOpaque = false;

    props.faceTiles.fill( {4, 0} );
 }

 /* 
 
    WATER
 
 */
 {
    BlockProperties& props = s_properties[(size_t)BlockType::Water];
    props.name = "water";
    props.isSolid = false;
    props.isTransparent = true;
    props.isOpaque = false;

    props.faceTiles.fill( {5, 0} );
 }

 /*
 
    WOOD
 
 */
 {
    BlockProperties& props = s_properties[(size_t)BlockType::Wood];
    props.name = "wood";
    props.isSolid = true;
    props.isTransparent = false;
    props.isOpaque = true;

    props.faceTiles[(size_t)BlockFace::Top]     = {6, 0};
    props.faceTiles[(size_t)BlockFace::Bottom]  = {6, 0};
    props.faceTiles[(size_t)BlockFace::North]   = {7, 0};
    props.faceTiles[(size_t)BlockFace::South]   = {7, 0};
    props.faceTiles[(size_t)BlockFace::East]    = {7, 0};
    props.faceTiles[(size_t)BlockFace::West]    = {7, 0};
 }

 /*
 
    LEAVES
 
 */
 {
    BlockProperties& props = s_properties[(size_t)BlockType::Leaves];
    props.name = "leaves";
    props.isSolid = true;
    props.isTransparent = true;
    props.isOpaque = false;

    props.faceTiles.fill( {8, 0} );
 }

 s_initialized = true;
}

const BlockProperties& BlockRegistry::get(BlockType type){
   if (!s_initialized){
      throw std::runtime_error("BlockRegistry::get called befor initialize()");
   }
   return s_properties[(size_t)type];
}