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

#include "io/fwriter.hpp"
#include <cstring>

namespace mat
{
    filter::filter(FILE *file)
    :
        fptr(file)
    {}


    nofilter::nofilter(FILE *file)
    :
        filter(file)
    {}

    dim_t nofilter::write(const unsigned char *data, dim_t bytes)
    {
        return fwrite(data,1,bytes,fptr);
    }

    void nofilter::flush(){}

    zfilter::zfilter(FILE *file, unsigned int level)
    :
        filter(file),
        bptr(buffer),
        bend(buffer+MAT_ZCHUNK)
    {

        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        auto ret = deflateInit(&strm, level);
        if (ret != Z_OK)
            throw mfile_error("Could not initiakuse zlib library");
    }

    zfilter::~zfilter()
    {
        zfilter::flush();
        deflateEnd(&strm);
    }

    void zfilter::compress(bool finish)
    {
        strm.avail_in = bptr-buffer;
        strm.next_in = buffer;
        strm.avail_out = MAT_ZCHUNK;
        strm.next_out = zbuffer;
        auto f = finish ? Z_FINISH : Z_NO_FLUSH;
        do {
            auto ret = deflate(&strm,f);
            if (ret == Z_STREAM_ERROR) throw mfile_error("Could not compress data element");
            auto have = MAT_ZCHUNK-strm.avail_out;
            fwrite(zbuffer,1,have,fptr);
        } while (strm.avail_out == 0);
        bptr = buffer;
    }

    dim_t zfilter::write(const unsigned char *data, dim_t bytes)
    {
        dim_t avail = bend-bptr;
        if (avail > bytes)
        {
            memcpy(bptr,data,bytes);
            bptr += bytes;
            return bytes;
        }
        dim_t off = 0;
        do
        {
            memcpy(bptr,data+off,avail);
            bptr = bend;
            off += avail;
            compress(false);
        } while(bytes-off > avail);
        memcpy(bptr,data+off,bytes-off);
        bptr += bytes-off;
        return bytes;
    }

    void zfilter::flush()
    {
        compress(true);
    }

    fwriter::fwriter(const std::string &path)
    :
        fptr(fopen(path.c_str(),"wb"))
    {
        if (!fptr) throw mfile_error("Could not open file");
        filt = new nofilter(fptr);
    }

    fwriter::~fwriter()
    {
        close();
    }

    void fwriter::rmfilter()
    {
        delete filt;
        filt = new nofilter(fptr);
    }

    dim_t fwriter::tellp() const
    {
        if (!fptr) throw mfile_error("Cannot tell closed file");
        return ftell(fptr);
    }
    dim_t fwriter::seekp(dim_t pos, ios::filepos whence)
    {
        if (!fptr) throw mfile_error("Cannot seek closed file");
        filt->flush();
        return fseek(fptr,(long) pos,whence);
    }

    dim_t fwriter::write(const std::string &str)
    {
        if (!fptr) throw mfile_error("Cannot write to closed file");
        return filt->write((const unsigned char *)&str[0],str.size());
    }

    void fwriter::close()
    {
        delete filt;
        filt = nullptr;
        if (!fptr) return;
        fclose(fptr);
        fptr = nullptr;
    }

}