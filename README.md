# Is In
A simple utility to determine if a file appears in another file

This is a simple unix utility to determine if one file appears inside another file.  This is useful for wrapper-style file formats that have headers with binary payloads, to determine if a particular binary is the one wrapped in the image.  Alternatively, if you have a file that you know is wrapped in another file, this will tell you the offset at which it appears.

Returns 0 if the file was found in the wrapper file, 1 if not, and 255 if there was an error reading one of the files.

## Usage
    isin <wrapper_file> <inner_file>
