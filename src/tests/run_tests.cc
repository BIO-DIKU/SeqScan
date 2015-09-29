/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

/*
 * The catch framework requires that CATCH_CONFIG_MAIN is defined in exactly one source file
 * and recommends (https://github.com/philsquared/Catch/blob/master/docs/tutorial.md#scaling-up)
 * that it be done in a source file separate from all other files. This is that file -- dont 
 * add anything else to it.
 */

#define CATCH_CONFIG_COLOUR_NONE
#define CATCH_CONFIG_MAIN
#include "catch.h"

