/*
 * 2mat/datenum.cpp -- implementation of datenum routines
 * 
 * Version: 1.0
 * Date created: 2021 March 22
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

#include "datenum.hpp"
#include "date/leap.hpp"

#include <cmath>

namespace mat
{

    // cumulative days in each month (in a non-leap year)
    int months[] = {0,31,59,90,120,151,181,212,243,273,304,334};

    static const int md_from_doy[365][2] = 
    {
        {1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8},{1,9},{1,10},{1,11},{1,12},{1,13},{1,14},
        {1,15},{1,16},{1,17},{1,18},{1,19},{1,20},{1,21},{1,22},{1,23},{1,24},{1,25},{1,26},{1,27},
        {1,28},{1,29},{1,30},{1,31},{2,1},{2,2},{2,3},{2,4},{2,5},{2,6},{2,7},{2,8},{2,9},{2,10},
        {2,11},{2,12},{2,13},{2,14},{2,15},{2,16},{2,17},{2,18},{2,19},{2,20},{2,21},{2,22},{2,23},
        {2,24},{2,25},{2,26},{2,27},{2,28},{3,1},{3,2},{3,3},{3,4},{3,5},{3,6},{3,7},{3,8},{3,9},
        {3,10},{3,11},{3,12},{3,13},{3,14},{3,15},{3,16},{3,17},{3,18},{3,19},{3,20},{3,21},{3,22},
        {3,23},{3,24},{3,25},{3,26},{3,27},{3,28},{3,29},{3,30},{3,31},{4,1},{4,2},{4,3},{4,4},
        {4,5},{4,6},{4,7},{4,8},{4,9},{4,10},{4,11},{4,12},{4,13},{4,14},{4,15},{4,16},{4,17},
        {4,18},{4,19},{4,20},{4,21},{4,22},{4,23},{4,24},{4,25},{4,26},{4,27},{4,28},{4,29},{4,30},
        {5,1},{5,2},{5,3},{5,4},{5,5},{5,6},{5,7},{5,8},{5,9},{5,10},{5,11},{5,12},{5,13},{5,14},
        {5,15},{5,16},{5,17},{5,18},{5,19},{5,20},{5,21},{5,22},{5,23},{5,24},{5,25},{5,26},{5,27},
        {5,28},{5,29},{5,30},{5,31},{6,1},{6,2},{6,3},{6,4},{6,5},{6,6},{6,7},{6,8},{6,9},{6,10},
        {6,11},{6,12},{6,13},{6,14},{6,15},{6,16},{6,17},{6,18},{6,19},{6,20},{6,21},{6,22},{6,23},
        {6,24},{6,25},{6,26},{6,27},{6,28},{6,29},{6,30},{7,1},{7,2},{7,3},{7,4},{7,5},{7,6},{7,7},
        {7,8},{7,9},{7,10},{7,11},{7,12},{7,13},{7,14},{7,15},{7,16},{7,17},{7,18},{7,19},{7,20},
        {7,21},{7,22},{7,23},{7,24},{7,25},{7,26},{7,27},{7,28},{7,29},{7,30},{7,31},{8,1},{8,2},
        {8,3},{8,4},{8,5},{8,6},{8,7},{8,8},{8,9},{8,10},{8,11},{8,12},{8,13},{8,14},{8,15},{8,16},
        {8,17},{8,18},{8,19},{8,20},{8,21},{8,22},{8,23},{8,24},{8,25},{8,26},{8,27},{8,28},{8,29},
        {8,30},{8,31},{9,1},{9,2},{9,3},{9,4},{9,5},{9,6},{9,7},{9,8},{9,9},{9,10},{9,11},{9,12},
        {9,13},{9,14},{9,15},{9,16},{9,17},{9,18},{9,19},{9,20},{9,21},{9,22},{9,23},{9,24},{9,25},
        {9,26},{9,27},{9,28},{9,29},{9,30},{10,1},{10,2},{10,3},{10,4},{10,5},{10,6},{10,7},{10,8},
        {10,9},{10,10},{10,11},{10,12},{10,13},{10,14},{10,15},{10,16},{10,17},{10,18},{10,19},
        {10,20},{10,21},{10,22},{10,23},{10,24},{10,25},{10,26},{10,27},{10,28},{10,29},{10,30},
        {10,31},{11,1},{11,2},{11,3},{11,4},{11,5},{11,6},{11,7},{11,8},{11,9},{11,10},{11,11},
        {11,12},{11,13},{11,14},{11,15},{11,16},{11,17},{11,18},{11,19},{11,20},{11,21},{11,22},
        {11,23},{11,24},{11,25},{11,26},{11,27},{11,28},{11,29},{11,30},{12,1},{12,2},{12,3},{12,4},
        {12,5},{12,6},{12,7},{12,8},{12,9},{12,10},{12,11},{12,12},{12,13},{12,14},{12,15},{12,16},
        {12,17},{12,18},{12,19},{12,20},{12,21},{12,22},{12,23},{12,24},{12,25},{12,26},{12,27},
        {12,28},{12,29},{12,30},{12,31}
    };

    void doy2md(int y, int doy, int *m, int *d)
    {
        // The fastest way to calculate the month and day from a doy is to use a lookup table.
        doy -= (doy>59 && ((y & 3) && (!(y % 25) || (y & 15))));
        
        *m = md_from_doy[doy][0];
        *d = md_from_doy[doy][1];
    }

    int md2doy(int y, int m, int d)
    {
        int doy = months[m-1]+d;    
        // Efficiently determines if y represents a leap year. see:
        // https://stackoverflow.com/a/11595914
        return doy + (m>2 && ((y & 3) && (!(y % 25) || (y & 15))));
    }

    double julian(int y, int m, int d, int H, int M, double S)
    {
        int jdn = (1461 * (y + 4800 + (m - 14)/12))/4 + 
            (367 * (m - 2 - 12 * ((m - 14)/12)))/12 - 
            (3 * ((y + 4900 + (m - 14)/12)/100))/4 + d - 32075;
        double hms = (H-12)/24.0 + M/1440.0 + S/86400.0;
        return ((double)jdn)+hms;
    }

    double datenum(int y, int m, int d, int H, int M, double S)
    {

        return julian(y,m,d,H,M,S) - 1721058.5;
    }

    double julian(int year, double doy)
    {
        int m, d, H, M;
        double S;
        doy2md(year,doy,&m,&d);
        S = doy - ((int)doy);
        H = S/24;
        S -= H*24;
        M = S/1440;
        S -= M*1440;
        return julian(year,m,d,H,M,S);
    }

    double datenum(int year, double doy)
    {
        return julian(year,doy) - 1721058.5;
    }
    
    double unix2dn(double s)
    {
        return 719529.0 + s/86400.0;
    }
    
    double j19002dn(double j)
    {
        return j + 2415020.0 - 1721058.5;
    }

    double j20002dn(double j)
    {
        return j + 2451545.0 - 1721058.5;
    }

    double mjd2dn(double j)
    {
        return j + 2400000.5 - 1721058.5;
    }

    double tt20002dn(long long tt)
    {
        double hms = (tt%86400000000000ll)/1000000000ll;
        tt /= 86400000000000ll;
        double jd = tt + 2451545.0;

        // Correct for leap seconds
        int i = 0;
        while (LEAP_JD[i] > jd) ++i;
        hms -= (27 - i);

        return jd + (hms)/86400.0 - 1721058.5;
    }

}