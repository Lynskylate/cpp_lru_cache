#include <lrucache.h>
#include <string>
#include <iostream>

int main(void){
    cache::lru_cache<std::string, std::string> cache(10);
    cache.set(std::string("test"), std::string("test"));
    cache.set(std::string("test"), std::string("love"));
    std::cout<<cache.get(std::string("test"))<<std::endl;
}
