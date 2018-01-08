# 2*16x16 for background
from PIL import Image
import numpy
import sys
import math

PIXELS_PER_BYTE = 4
BITS_PER_PIXEL = 2
PIXELS_PER_ROW = 8
BYTES_PER_ROW = 2
wanted_width = 16
wanted_height = 16

'''32x32
[0, 2], [8,10]
[1, 3], [9,11]
[4, 6], [12,14]
[5, 7], [13,15]

[16,18],[24,26]
[17,19],[25,27]
[20,22],[28,30]
[21,23],[39,31]
'''


def merge_column(data1, data2):
    new_data = []
    row_length = int(math.sqrt(len(data1)))
    for i in range(row_length):
        for j in range(row_length):
            new_data.append(data1[i * row_length + j])
        for j in range(row_length):
            new_data.append(data2[i * row_length + j])
    return new_data


def merge_row(data1, data2):
    new_data = data1
    new_data.extend(data2)
    return new_data


def merge(data, width=8):
    if width == 8:
        return data[0]
    elif width == 16:
        return merge_row(merge_column(data[0], data[2]),
                         merge_column(data[1], data[3]))
    elif width == 32:
        return merge_row(merge_column(merge(data[0:4],16), merge(data[8:12],16)),
                         merge_column(merge(data[4:8],16), merge(data[12:16],16)))


if __name__ == '__main__':
    bin_filename = "peanut.bin"
    if len(sys.argv) >= 2:
        bin_filename = str(sys.argv[1])

    if len(sys.argv) >= 3:
        try:
            wanted_width = int(sys.argv[2])
        except ValueError:
            sys.stderr.write("Second argument must be int")
    if len(sys.argv) >= 4:
        try:
            wanted_height = int(sys.argv[3])
        except ValueError:
            sys.stderr.write("Third argument must be int")
    bin_content = []
    with open(bin_filename, 'rb') as bin_file:
        bin_content = bin_file.read()
    print(len(bin_content))
    colors = []
    colors_8x8 = []
    for i in range(int(len(bin_content) / BYTES_PER_ROW)):
        if i % 8 == 0 and i is not 0:
            colors.append(colors_8x8)
            colors_8x8 = []
        for j in reversed(range(0,8)):
            color_value = ((bin_content[BYTES_PER_ROW*i+1] & (2**j)) >> j << 1) | \
                          ((bin_content[BYTES_PER_ROW*i] & (2**j)) >> j)
            alpha_value = 1
            colors_8x8.append([int((1.0 - color_value / 3.0) * 255),
                               int((1.0 - color_value / 3.0) * 255),
                               int((1.0 - color_value / 3.0) * 255),
                               int(alpha_value * 255)])
    colors.append(colors_8x8)
    colors_aligned = merge(colors, wanted_width)
    img_size = len(colors_aligned)
    background_data = numpy.asarray(colors_aligned, dtype=numpy.uint8)

    background_data = background_data.reshape([wanted_width,int(img_size/wanted_width),4])

    mode = "RGBA"
    print(background_data.shape)
    im = Image.fromarray(background_data, mode)
    im.save(bin_filename.replace('.bin', '.png'))
