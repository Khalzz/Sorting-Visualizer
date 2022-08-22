#include<SDL2/SDL.h>
#include "DataEntity.hpp"

DataEntity::DataEntity(int _value, int _y)
{   
    value = _value;
    rect = {_y,10,5,_value};
}