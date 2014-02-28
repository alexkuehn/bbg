/*
 * Copyright 2013 Alexander Kühn.
 *
 * datautil.c
 * This file is part of BBG.
 *
 * BBG is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BBG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BBG.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "datautil.h"

void dataset_compress_resolution( uint8_t *source, uint8_t *dest  )
{
   uint8_t dindex,sindex;
   uint8_t rawbits, store_space, first_free_pos, remainpos, consumedbits;

   dindex = 0;
   sindex = 0;
   store_space = DATASET_FULL_BITS;
   first_free_pos  = 0;
   remainpos = 0;
   consumedbits = 0;


   /* iterate through big storage and take nibble values
    * reorder in destination storage
    */
   do
   {
      dest[dindex] = 0;
      while( store_space )
      {


         rawbits = (source[sindex] & DATASET_USED_MASK ) >> consumedbits;
         dest[dindex] |= rawbits << first_free_pos;

         remainpos = DATASET_USED_BITS - consumedbits;

         if( store_space >= remainpos)
         {
            consumedbits += remainpos;
            store_space -= remainpos;
         }
         else
         {
            consumedbits += store_space;
            store_space = 0;
         }



         if( (DATASET_USED_BITS - consumedbits) == 0)
         {
            sindex++;
            consumedbits = 0;
            remainpos = 0;
         }
         first_free_pos = DATASET_FULL_BITS - store_space;
      }
      dindex++;
      first_free_pos = 0;
      store_space = DATASET_FULL_BITS;
   }while( dindex < DATASET_COMPRESSED_STORE_SIZE);




}

void dataset_uncompress_resolution( uint8_t *source, uint8_t *dest )
{
   uint8_t sindex, dindex;
   uint8_t storespace, consumable, consumed, rawbits, startpos, remain;
   sindex = 0;
   dindex = 0;
   consumed = 0;
   remain = DATASET_USED_BITS;
   storespace = DATASET_FULL_BITS;
   startpos = 0;

   do
   {

      while( storespace )
      {
         rawbits = (source[sindex] >> startpos) & DATASET_USED_MASK;
         dest[dindex] |= (rawbits << consumed) & DATASET_USED_MASK;


         consumable = DATASET_FULL_BITS - startpos;

         if( consumable >= remain )
         {
            consumed = remain;
         }
         else
         {
            consumed = DATASET_FULL_BITS- startpos;
         }

         remain -= consumed;

         if( storespace > consumed)
         {
            storespace -= consumed;
            startpos += consumed;
         }
         else
         {
            startpos = 0;
            storespace = 0;
         }

         if( remain == 0 )
         {
            dindex++;
            remain = DATASET_USED_BITS;
            consumed = 0;
         }


      }
      sindex++;
      storespace = DATASET_FULL_BITS;
   }while( sindex < DATASET_COMPRESSED_STORE_SIZE);
}
