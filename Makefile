all: OSXImageLoader32 OSXImageLoader64
		

clean:
		rm -f OSXImageLoader32 OSXImageLoader64


OSXImageLoader32: main.c
		gcc -m32 main.c  -framework ImageIO -framework CoreServices -o OSXImageLoader32
OSXImageLoader64: main.c
		gcc -m64 main.c  -framework ImageIO -framework CoreServices -o OSXImageLoader64
