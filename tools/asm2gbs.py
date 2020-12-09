# ASM 2 GAME BOY S
#Translate ams file from MMX's GBTK to be used in GBDK
#
#Use: python ../tools/asm2gbs.py kwakwa_logo.asm

import sys
import os.path

class GBSData:
    dataname = ""
    tiledata = []
    tilemap = []

def read_asmfile(asmfile):
    gbsdata = GBSData()
    with open(asmfile) as f:
        lines = f.readlines()
        tiledata = False
        tilemap = False
        for i in range(len(lines)):
            if lines[i][0] is ";":
                continue
            
            if len(lines[i]) == 0:
                continue
            
            if "_tiledata:" in lines[i] and gbsdata.dataname == "":
                gbsdata.dataname = lines[i].replace("_tiledata:", "").replace("\n", "").replace("\r", "")
                tiledata = True
                continue
                
            if lines[i][0] is "$" and tiledata:
                values = lines[i].split(",")
                for j in range(len(values)):
                    values[j] = values[j].replace("$", "0x").replace("\n", "").replace("\r", "")
                gbsdata.tiledata.extend(values)
                
            if lines[i][0] != "$" and tiledata:
                tiledata = False
                
            if "_tilemap:" in lines[i]:
                tilemap = True
                continue
                
            if lines[i][0] is "0" and tilemap:
                values = lines[i].split(",")
                for j in range(len(values)):
                    values[j] = values[j].replace("\n", "").replace("\r", "")
                gbsdata.tilemap.extend(values)
                

    return gbsdata


def write_gbs(gbs_data, gbsfile):
    with open(gbsfile, 'w') as f:
        f.write(".area _CODE_3\n")
        f.write(".globl _"+gbs_data.dataname+"_tiledata\n")
        f.write(".dw _"+gbs_data.dataname+"_tiledata\n")
        f.write("_"+gbs_data.dataname+"_tiledata:\n")
        
        for i in range(len(gbs_data.tiledata)/8):
            f.write(".db "+",".join(gbs_data.tiledata[i*8:i*8+8])+"\n")
            
        f.write(".globl _"+gbs_data.dataname+"_tilemap\n")
        f.write(".dw _"+gbs_data.dataname+"_tilemap\n")
        f.write("_"+gbs_data.dataname+"_tilemap:\n")
        
        for i in range(len(gbs_data.tilemap)/8):
            f.write(".db "+",".join(gbs_data.tilemap[i*8:i*8+8])+"\n")


def main():
    argv = sys.argv
    asmfile = ""
    gbsfile = ""
    if len(argv) == 3:
        if os.path.isfile(argv[1]):
            asmfile = argv[1]
        else:
            sys.stderr.write("Error: First argument is not a file\n")
            return
        gbsfile = argv[2]
    elif len(argv) == 2:
        if os.path.isfile(argv[1]):
            asmfile = argv[1]
        else:
            sys.stderr.write("Error: First argument is not a file\n")
            return
        gbsfile = os.path.basename(asmfile).split(".")[0]+".s"
    else:
        sys.stderr.write("Error: No argument given\n")
        return
    
    gbs_data  = read_asmfile(asmfile)
   
    write_gbs(gbs_data, gbsfile)

if __name__ == '__main__':
    main()
    
        
    