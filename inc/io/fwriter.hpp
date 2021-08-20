/*
 * 2mat/io/fwriter.hpp -- Writes binary data to a file
 * 
 * Version: 1.0
 * Date created: 2021 March 18
 * Copyright (c) 2021 Aaron Hendry
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TOO_MAT_IO_FWRITER_H
#define TOO_MAT_IO_FWRITER_H

#include "../types.hpp"
#include "../util.hpp"

#include <cstdio>
#include <string>
#include <zlib.h>
#include <type_traits>
#include <memory>

#ifndef MAT_ZCHUNK
#define MAT_ZCHUNK 1048576
#endif

#ifndef MAT_ZLEVEL
#define MAT_ZLEVEL 8
#endif

#ifndef MAT_FBUF
#define MAT_FBUF 4096
#endif

namespace mat
{

    namespace ios
    {  
        enum filepos
        {
            beg=SEEK_SET,
            cur=SEEK_CUR,
            end=SEEK_END
        };
    }

    class filter
    {
    protected:
        FILE *fptr;
    public:
        explicit filter(FILE *file);
        virtual ~filter() = default;

        virtual dim_t write(const unsigned char *data, dim_t bytes) = 0;
        virtual void flush() = 0;
    };

    class nofilter : public filter
    {
    public:
        explicit nofilter(FILE *file);
        ~nofilter() override = default;

        dim_t write(const unsigned char *data, dim_t bytes) override;
        void flush() override;
    };

    class zfilter : public filter
    {
        unsigned char *bptr, *bend;
        unsigned int level;
        unsigned char buffer[MAT_ZCHUNK];
        unsigned char zbuffer[MAT_ZCHUNK];

        z_stream strm;

        void compress(bool finish);
    public:
        explicit zfilter(FILE *file, unsigned int level = MAT_ZLEVEL);
        ~zfilter() override;

        dim_t write(const unsigned char *data, dim_t bytes) override;
        void flush() override;
    };

    class fwriter
    {
        FILE *fptr;
        filter *filt;
    public:
        explicit fwriter(const std::string &path);
        ~fwriter();

        template <typename T>
        void addfilter();
        void rmfilter();

        [[nodiscard]] dim_t tellp() const;
        dim_t seekp(dim_t pos, ios::filepos = ios::beg);

        template <typename T, typename U=T>
        dim_t write(T val);
        template <typename T, typename U=T>
        dim_t write_n(T val, dim_t n);
        template <typename T, typename U=T>
        dim_t write(T *ptr, dim_t n);
        dim_t write(const std::string &str);

        void close();

    };

    template <typename T>
    void fwriter::addfilter()
    {
        delete filt;
        filt = new T(fptr);
    }

    template <typename T, typename U>
    dim_t fwriter::write(T val)
    {
        if (!fptr) throw mfile_error("Cannot write to closed file");
        if (std::is_same<T,U>::value)
        {
            filt->write((unsigned char *)&val,sizeof(T));
            return sizeof(T);
        }
        U uval = (U)val;
        filt->write((unsigned char *)&uval,sizeof(U));
        return sizeof(U);
    }

    template <typename T, typename U>
    dim_t fwriter::write_n(T val, dim_t n)
    {
        if (!fptr) throw mfile_error("Cannot write to closed file");
        if (std::is_same<T,U>::value)
        {
            for (uint i = 0; i < n; ++i)
                filt->write((unsigned char *)&val,sizeof(T));
            return n*sizeof(T);
        }
        U uval = (U)val;
        for (uint i = 0; i < n; ++i)
            filt->write((unsigned char *)&uval,sizeof(U));
        return n*sizeof(U);
    }

    template <typename T, typename U>
    dim_t fwriter::write(T *ptr, dim_t n)
    {
        if (!fptr) throw mfile_error("Cannot write to closed file");
        if (std::is_same<T,U>::value)
        {
            return filt->write((unsigned char *)ptr,n*sizeof(T));
        }
        U val;
        for (uint i = 0; i < n; ++i)
        {
            val = (U)ptr[i];
            filt->write((unsigned char *)&val,sizeof(U));
        }
        return n*sizeof(U);
    }

}

#endif