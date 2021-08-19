/*
 * 2mat/datenum.hpp -- Datenum utilities for writing to MATLAB files
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

#ifndef TOO_MAT_DATENUM_H
#define TOO_MAT_DATENUM_H

namespace mat
{

    void doy2md(int y, int doy, int *m, int *d);
    int ymd2doy(int y, int m, int d);

    /*
     * double mat::julian(int y, int m, int d, int H, int M, double S)
     * 
     * Calculates the julian date number of the specified date
     * 
     * INPUT:
     *  y (int) the year of the date to calculate
     *  m (int) the month of the date to calculate
     *  d (int) the day of the date to calculate
     *  H (int) the hour of the date to calculate
     *  M (int) the minute of the date to calculate
     *  S (double) the (factional) second of the date to calculate
     * RETURN:
     *  the julian date number
     */
    double julian(int year, int month, int day, int hour = 0, int minute = 0, double second = 0.0);

    /*
     * double mat::datenum(int y, int m, int d, int H, int M, double S)
     * 
     * Calculates the MATLAB datenum of the specified date -- this is equivalent to calling the
     * MATLAB function datenum(y,m,d,H,M,S).
     * 
     * INPUT:
     *  y (int) the year of the date to calculate
     *  m (int) the month of the date to calculate
     *  d (int) the day of the date to calculate
     *  H (int) the hour of the date to calculate
     *  M (int) the minute of the date to calculate
     *  S (double) the (factional) second of the date to calculate
     * RETURN:
     *  the MATLAB datenum
     */
    double datenum(int year, int month, int day, int hour = 0, int minute = 0, double second = 0.0);
    
    /*
     * double mat::julian(int y, double d)
     * 
     * Calculates the julian date number of the specified year and fractional day of year
     * 
     * INPUT:
     *  y (int) the year of the date to calculate
     *  d (double) the fractional day-of-year of the date to calculate
     * RETURN:
     *  the julian date number
     */
    double julian(int year, double doy);
    
    /*
     * double mat::julian(int y, int m, int d, int H, int M, double S)
     * 
     * Calculates the MATLAB datenum of the specified year and fractional day of year -- this is 
     * equivalent to calling the MATLAB function datenum(y,1,doy).
     * 
     * INPUT:
     *  y (int) the year of the date to calculate
     *  d (double) the fractional day-of-year of the date to calculate
     * RETURN:
     *  the MATLAB datenum
     */
    double datenum(int year, double doy);
    
    /*
     * double mat::unix2dn(double s)
     * 
     * Calculates the MATLAB datenum of the specified fractional unix timestamp.
     * 
     * INPUT:
     *  s (double) the unix timestamp to calculate the datenum for
     * RETURN:
     *  the MATLAB datenum
     */
    double unix2dn(double s);
    
    /*
     * double mat::j19002dn(double s)
     * 
     * Converts the julian day number in the J1900 epoch to a MATLAB datenum.
     * 
     * INPUT:
     *  j (double) the j1900 day number to calculate the datenum for
     * RETURN:
     *  the MATLAB datenum
     */
    double j19002dn(double j);
    
    /*
     * double mat::j20002dn(double s)
     * 
     * Converts the julian day number in the J2000 epoch to a MATLAB datenum.
     * 
     * INPUT:
     *  j (double) the j2000 day number to calculate the datenum for
     * RETURN:
     *  the MATLAB datenum
     */
    double j20002dn(double j);
    
    /*
     * double mat::mjd2dn(double s)
     * 
     * Converts the modified julian day number to a MATLAB datenum.
     * 
     * INPUT:
     *  j (double) the MJD day number to calculate the datenum for
     * RETURN:
     *  the MATLAB datenum
     */
    double mjd2dn(double j);
    
    /*
     * double mat::tt20002dn(double s)
     * 
     * Calculates the MATLAB datenum of the CDF TT2000 timestamp. Due to the limited precision of 
     * the MATLAB datenum, this results is significant loss of accuracy compared to the TT2000 
     * timestamp.
     * 
     * INPUT:
     *  s (double) the CDF TT2000 timestamp to calculate the datenum for
     * RETURN:
     *  the MATLAB datenum
     */
    double tt20002dn(long long tt);
}

#endif