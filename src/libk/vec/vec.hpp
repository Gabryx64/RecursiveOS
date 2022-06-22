#ifndef LIBK_VEC_H
#define LIBK_VEC_H 1
#include<initializer_list>
#include<stddef.h>

#include"liballoc.h"
#include"mathutils.h"
#include"str.h"
#include"portio.h"

namespace libk
{
    template<typename T>
    class Vec
    {
    private:
        size_t size;
        void* data;

    public:
        Vec()
            : size(0), data(nullptr)
        {}

        Vec(const std::initializer_list<T>& list)
        {
            size = list.size();
            data = kmalloc(size * sizeof(T));
            memcpy(data, list.begin(), size * sizeof(T));
        }

        Vec(const T* list, size_t size)
            : size(size)
        {
            data = kmalloc(size * sizeof(T));
            memcpy(data, list, size * sizeof(T));
        }

        ~Vec()
        {
            for(size_t i = 0; i < size; i++)
                ((T*)data)[i].~T();

            kfree(data);
        }

        T* begin() const
        {
            return (T*)data;
        }

        T* end() const
        {
            return (T*)data + size * sizeof(T);
        }

        void push(const T& x)
        {
            data = krealloc(data, ++size * sizeof(T));
            ((T*)data)[size - 1] = x;
        }

        void pop(const T& x)
        {
            if(size == 0)
                return;
            ((T*)data)[--size].~T();
            data = krealloc(data, size * sizeof(T));
        }
    };
}

#endif
