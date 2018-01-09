from __future__ import absolute_import

import sys

import pygame
import OpenGL.GL as gl

from imgui.integrations.pygame import PygameRenderer
import imgui



import sys

import os
from os import listdir
from os.path import isfile, join


from PIL import Image

import tools.bin2png


class ImageManager():
    def __init__(self):
        self.textureID_map = {}
        self.imgs_size_map = {}
        self.texture_data_map = {}
    def load_image(self, filename):
        if filename in self.textureID_map:
            return self.textureID_map[filename]
        else:
            try:
                im = Image.open(filename)
                try:
                    ix, iy, image = im.size[0], im.size[1], im.tobytes("raw", "RGBA", 0, -1)
                except SystemError:
                    sys.stderr.write("System Error on " + filename)
                    return 0
                self.imgs_size_map[filename] = (ix,iy)
                self.texture_data_map[filename] = image
                texture_id = gl.glGenTextures(1)
                gl.glBindTexture(gl.GL_TEXTURE_2D, texture_id)
                gl.glTexImage2D(gl.GL_TEXTURE_2D, 0, 3, ix, iy, 0, gl.GL_RGBA, gl.GL_UNSIGNED_BYTE, image)
                gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MIN_FILTER, gl.GL_NEAREST);
                self.textureID_map[filename] = texture_id
                return texture_id
            except FileNotFoundError:
                sys.stderr.write("Could not open file: "+filename)
                return 0

    def get_image_size(self, filename):
        if filename in self.imgs_size_map:
            return self.imgs_size_map[filename]
        else:
            return ()

    def reload_img(self, filename):
        self.textureID_map.pop(filename)
        self.texture_data_map.pop(filename)
        self.imgs_size_map.pop(filename)
        self.load_image(filename)


img_manager = ImageManager()


def imgui_image_menu(path):
    filename = path.split("/")[-1]
    if filename.split(".")[-1] == "bin":
        imgui.text(filename)
        if imgui.begin_popup_context_item("Convert "+filename, 2):
            if imgui.button("Convert to 8x8 images"):
                tools.bin2png.bin2png(path,8)
                img_manager.reload_img(path.replace(".bin", ".png"))
            if imgui.button("Convert to 16x16 images"):
                tools.bin2png.bin2png(path, 16)
                img_manager.reload_img(path.replace(".bin", ".png"))
            if imgui.button("Convert to 32x32 images"):
                tools.bin2png.bin2png(path, 32)
                img_manager.reload_img(path.replace(".bin", ".png"))
            imgui.end_popup()


def main():
    pygame.init()

    size = 800, 600

    pygame.display.set_mode(size, pygame.DOUBLEBUF | pygame.OPENGL)
    pygame.display.set_caption("GBDev tool window")
    io = imgui.get_io()
    io.fonts.add_font_default()
    io.display_size = size

    renderer = PygameRenderer()

    while 1:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

            renderer.process_event(event)

        imgui.new_frame()

        if imgui.begin_main_menu_bar():
            if imgui.begin_menu("File", True):
                open_gbtd, selected_none = imgui.menu_item("Open GBTD", None, False, True)
                open_gbtk, selected_none = imgui.menu_item("Open GBTK", None, False, True)
                clicked_quit, selected_quit = imgui.menu_item("Quit", 'Cmd+Q', False, True)

                if clicked_quit:
                    exit(1)
                if open_gbtd:
                    os.system("wine tools/GBTD/GBTD.EXE &")
                if open_gbtk:
                    os.system("wine tools/GBTK.exe &")
                imgui.end_menu()
            imgui.end_main_menu_bar()

        imgui.begin("Data", True)

        img_path = "data/img"
        onlyfiles = [f for f in listdir(img_path) if isfile(join(img_path, f))]
        #print(onlyfiles)
        for file in onlyfiles:
            imgui_image_menu(img_path+"/"+file)

        imgui.end()

        imgui.begin("Images", True)

        imgs_id = []
        for img_filename in onlyfiles:
            if img_filename.split(".")[-1] == "png":
                imgs_id.append((img_path+"/"+img_filename, img_manager.load_image(img_path+"/"+img_filename)))

        for img in imgs_id:
            img_size = img_manager.get_image_size(img[0])
            if img[1] is not 0 and img_size is not ():
                imgui.image(img[1], img_size[0]*2, img_size[1]*2, (0,1), (1,0))
                imgui.same_line()


        imgui.end()
        # note: cannot use screen.fill((1, 1, 1)) because pygame's screen
        #       does not support fill() on OpenGL sufraces
        gl.glClearColor(1, 1, 1, 1)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT)
        imgui.render()

        pygame.display.flip()

if __name__ == "__main__":
    main()