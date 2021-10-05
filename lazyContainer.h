//
// Created by Wander on 06/10/2021.
//

#ifndef LAZYCONTAINER_LAZYCONTAINER_H
#define LAZYCONTAINER_LAZYCONTAINER_H

#include <iostream>
#include <list>
#include <variant>

namespace funk{
template<typename T>
    class lazy{
    private:
        using voidFunc  = void (*)(const T&);
        using valueFunc = T    (*)(const T&);
        using boolFunc  = bool (*)(const T&);

        using variant = std::variant< T,
                                      voidFunc,
                                      valueFunc,
                                      boolFunc >;
        using element = std::pair< variant, size_t >;
        using list = std::list<element>;

        list _arr{};
        size_t _count = 0;
    private:
        void voidTransform(voidFunc func, size_t& funcIndex){
            for(auto& i : _arr){
                auto& [variant, index] = i;
                if(index == funcIndex) return;
                auto activeType = variant.index();
                if(activeType == 0){
                    auto& value = std::get<0>(variant);
                    func(value);
                }
            }
        }
        void valueTransform(valueFunc func, size_t& funcIndex){
            for(auto& i : _arr){
                auto& [variant, index] = i;
                if(index == funcIndex) return;
                auto activeType = variant.index();
                if(activeType == 0){
                    auto& value = std::get<0>(variant);
                    value = func(value);
                }
            }
        }
        void boolTransform(boolFunc func, size_t& funcIndex){
            for(auto& i : _arr){
                auto& [variant, index] = i;
                if(index == funcIndex) break;
                auto activeType = variant.index();
                if(activeType == 0){
                    auto& value = std::get<0>(variant);
                    if(!func(value)) index = 0;
                }
            }
            _arr.remove_if([](element& i){
                return i.second == 0;
            });
        }
    public:
        friend lazy& operator<< (lazy& l, variant input){
            l._arr.emplace_back(std::make_pair(input, ++l._count));
            return l;
        }
        void operator()(){
            for(auto& i : _arr){
                auto& [variant, index] = i;
                auto activeType = variant.index();
                switch(activeType){
                    case 1: {
                        voidTransform(std::get<1>(variant), index);
                        break;
                    }
                    case 2: {
                        valueTransform(std::get<2>(variant), index);
                        break;
                    }
                    case 3: {
                        boolTransform(std::get<3>(variant), index);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };
}

#endif //LAZYCONTAINER_LAZYCONTAINER_H
