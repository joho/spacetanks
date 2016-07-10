SPRITES = bat.h pew.h tank.h

all: bitmaps pngs

bitmaps: banner.h bat.h boom.h boss.h pew.h tank.h
pngs: banner.png bat.png boom.png boss.png pew.png tank.png

%.png: %.ase
	/Applications/Aseprite.app/Contents/MacOS/aseprite -b --sheet-type vertical --format json-array --data $(basename $@).json --sheet $@ $<

%.h: %.png
	mksprite -in $< -out $@ -name $(basename $@) -json $(basename $@).json

clean:
	rm -f *.png *.h

.PHONY: clean all
.DEFAULT: all
