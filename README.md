# Huffman Compressor/Decompressor

Welcome to the Huffman Compressor/Decompressor project! This repository contains the implementation of a Huffman encoding and decoding tool in C for the Data Structures I course.

## Documentation

All code documentation can be found in the file `COMPACTADOR DE HUFFMAN.pdf`.

## Build Instructions

To build the project, use the `make` command. This will generate two programs: `compacta` (the compressor) and `descompacta` (the decompressor).

## Usage

The compressor and decompressor can handle various file types, including `txt`, `png`, `pdf`, etc.

To compress a file, use the command `./compacta path-to-file/file-name`. For example:
`./compacta arquivosEntrada/biblia.txt`

To decompress a file, use the command `./descompacta path-to-file/file-name`. For example:
`./descompacta arquivosEntrada/biblia.txt.huff`

## Verification
Check the size of the input files and the size of the compressed file to see the magic of Huffman encoding in action!

---

Feel free to reach out if you have any questions or issues with the project.

Happy compressing!
