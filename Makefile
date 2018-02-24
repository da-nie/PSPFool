TARGET = Fool
OBJS = csprite.o video.o cgame.o ccardkit.o main.o
INCDIR = 
CFLAGS = -O3 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LIBDIR = 
LDFLAGS = 
LIBS = -lm -lstdc++ -lpspaudiolib -lpspaudio -lpsprtc
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Fool
PSP_EBOOT_ICON = ICON.PNG
PSP_EBOOT_ICON1 =
PSP_EBOOT_UNKPNG = 
PSP_EBOOT_PIC1 =PIC.PNG
PSP_EBOOT_SND0 =
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak