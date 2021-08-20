/*
 * 2mat/mstruct.hpp -- class definition for matlab struct types
 * 
 * Version: 1.0
 * Date created: 2021 March 16
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

#ifndef TOO_MAT_MSTRUCT_H
#define TOO_MAT_MSTRUCT_H

#include "container.hpp"

namespace mat
{

    class mstruct : public container
    {

        template <file_version V>
        void write(fwriter& fw);
    public:
		mstruct(std::string name);
		~mstruct();

        //TODO: Add struct methods

        /*
         * void mat::matrix::write(std::ostream& out, file_version v)
         * 
         * Writes the data in this matrix to the given output stream, in accordance with the file
         * version specified.
         * 
         * INPUT:
         *  out (std::ostream &) the stream to output the binary data to
         *  v (file_version) the file format to use
         */
        inline void write(fwriter& fw, file_version v) override
        {
            switch(v)
            {
                case V6:
                    write<V6>(fw);
                    return;
                case V7:
                    write<V7>(fw);
                    return;
                case V7_3:
                    write<V7_3>(fw);
                    return;
            }
        }
    };

}

#endif