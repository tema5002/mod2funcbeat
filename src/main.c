#include "mod_reader.h"

int main(int argc, char* argv[]) {
    file_buffer buf = read_all_bytes("/home/tema5002/Downloads/waveform_cocktail.mod");
    mod_module mod = read_mod(buf);
    destroy_file_buffer(buf);
    destroy_mod_module(mod);
    return 0;
}

// should we remove it or nough
// if everyone here can access the website at all times then please remove


/*
MOD files are music files containing 2 parts:

(1)
    a bank of digitized samples 
(2)
    sequencing information describing how and when to play the samples 

MOD files originated on the Amiga, but because of their flexibility and the extremely large number of MOD files available, MOD players are now available for a variety of machines (IBM PC, Mac, Sparc Station, etc.)

The samples in a MOD file are raw, 8 bit, signed, headerless, linear digital data. There may be up to 31 distinct samples in a MOD file, each with a length of up to 128K (though most are much smaller; say, 10K - 60K). An older MOD format only allowed for up to 15 samples in a MOD file; you don't see many of these anymore. There is no standard sampling rate for these samples.

The sequencing information in a MOD file contains 4 tracks of information describing which, when, for how long, and at what frequency samples should be played. This means that a MOD file can have up to 31 distinct (digitized) instrument sounds, with up to 4 playing simultaneously at any given point. This allows a wide variety of orchestrational possibilities, including use of voice samples or creation of one's own instruments (with appropriate sampling hardware/software). The ability to use one's own samples as instruments is a flexibility that other music files/formats do not share, and is one of the reasons MOD files are so popular, numerous, and diverse.

15 instrument MODs, as noted above, are somewhat older than 31 instrument MODs and are not (at least not by me) seen very often anymore. Their format is identical to that of 31 instrument MODs except:

(1)
    Since there are only 15 samples, the information for the last (15th) sample starts at byte 440 and goes through byte 469. 
(2)
    The songlength is at byte 470 (contrast with byte 950 in 31 instrument MOD) 
(3)
    Byte 471 appears to be ignored, but has been observed to be 127. (Sorry, this is from observation only) 
(4)
    Byte 472 begins the pattern sequence table (contrast with byte 952 in a 31 instrument MOD) 
(5)
    Patterns start at byte 600 (contrast with byte 1084 in 31 instrument MOD) 

"ProTracker," an Amiga MOD file creator/editor, is available for ftp everywhere as pt??.lzh.

From: Apollo Wong <apollo@ee.ualberta.ca>

From: M.J.H.Cox@bradford.ac.uk (Mark Cox)
Newsgroups: alt.sb.programmer
Subject: Re: Format for MOD files...
Message-ID: <1992Mar18.103608.4061@bradford.ac.uk>
Date: 18 Mar 92 10:36:08 GMT
Organization: University of Bradford, UK

wdc50@DUTS.ccc.amdahl.com (Winthrop D Chan) writes:
>I'd like to know if anyone has a reference document on the format of the
>Amiga Sound/NoiseTracker (MOD) files. The author of Modplay said he was going
>to release such a document sometime last year, but he never did. If anyone

I found this one, which covers it better than I can explain it - if you
use this in conjunction with the documentation that comes with Norman
Lin's Modedit program it should pretty much cover it.

Mark J Cox




***********************************************************************

Protracker 1.1B Song/Module Format:
-----------------------------------

Information for sample 1-31:

Offset  Bytes  Description
------  -----  -----------
  20     22    Samplename for sample 1. Pad with null bytes.
  42      2    Samplelength for sample 1. Stored as number of words.
               Multiply by two to get real sample length in bytes.
  44      1    Lower four bits are the finetune value, stored as a signed
               four bit number. The upper four bits are not used, and
               should be set to zero.
                Value:  Finetune:
                 0        0
                 1       +1
                 2       +2
                 3       +3
                 4       +4
                 5       +5
                 6       +6
                 7       +7
                 8       -8
                 9       -7
                 A       -6
                 B       -5
                 C       -4
                 D       -3
                 E       -2
                 F       -1

  45      1    Volume for sample 1. Range is $00-$40, or 0-64 decimal.
  46      2    Repeat point for sample 1. Stored as number of words offset
               from start of sample. Multiply by two to get offset in bytes.
  48      2    Repeat Length for sample 1. Stored as number of words in
               loop. Multiply by two to get replen in bytes.

Information for the next 30 samples starts here. It's just like the info for
sample 1.

Offset  Bytes  Description
------  -----  -----------
  50     30    Sample 2...
  80     30    Sample 3...
   .
   .
   .
 890     30    Sample 30...
 920     30    Sample 31...

Offset  Bytes  Description
------  -----  -----------
 950      1    Songlength. Range is 1-128.
 951      1    Well... this little byte here is set to 127, so that old
               trackers will search through all patterns when loading.
               Noisetracker uses this byte for restart, but we don't.
 952    128    Song positions 0-127. Each hold a number from 0-63 that
               tells the tracker what pattern to play at that position.
1080      4    The four letters "M.K." - This is something Mahoney & Kaktus
               inserted when they increased the number of samples from
               15 to 31. If it's not there, the module/song uses 15 samples
               or the text has been removed to make the module harder to
               rip. Startrekker puts "FLT4" or "FLT8" there instead.

Offset  Bytes  Description
------  -----  -----------
1084    1024   Data for pattern 00.
   .
   .
   .
xxxx  Number of patterns stored is equal to the highest patternnumber
      in the song position table (at offset 952-1079).

Each note is stored as 4 bytes, and all four notes at each position in
the pattern are stored after each other.

00 -  chan1  chan2  chan3  chan4
01 -  chan1  chan2  chan3  chan4
02 -  chan1  chan2  chan3  chan4
etc.

Info for each note:

 _____byte 1_____   byte2_    _____byte 3_____   byte4_
/                \ /      \  /                \ /      \
0000          0000-00000000  0000          0000-00000000

Upper four    12 bits for    Lower four    Effect command.
bits of sam-  note period.   bits of sam-
ple number.                  ple number.

Periodtable for Tuning 0, Normal
  C-1 to B-1 : 856,808,762,720,678,640,604,570,538,508,480,453
  C-2 to B-2 : 428,404,381,360,339,320,302,285,269,254,240,226
  C-3 to B-3 : 214,202,190,180,170,160,151,143,135,127,120,113

To determine what note to show, scan through the table until you find
the same period as the one stored in byte 1-2. Use the index to look
up in a notenames table.

This is the data stored in a normal song. A packed song starts with the
four letters "PACK", but i don't know how the song is packed: You can
get the source code for the cruncher/decruncher from us if you need it,
but I don't understand it; I've just ripped it from another tracker...

In a module, all the samples are stored right after the patterndata.
To determine where a sample starts and stops, you use the sampleinfo
structures in the beginning of the file (from offset 20). Take a look
at the mt_init routine in the playroutine, and you'll see just how it
is done.

Lars "ZAP" Hamre/Amiga Freelancers

***********************************************************************/