//
//  main.c
//  OSXImageLoader64
//
//  Created by admin on 2/12/13.
//  Copyright (c) 2013 admin. All rights reserved.
//

#include <CoreServices/CoreServices.h>
#include <ApplicationServices/ApplicationServices.h>

void listFormats(){
    printf("This are ty file formats your OSX can read:\n");
	CFArrayRef mySourceTypes = (CFArrayRef)CGImageSourceCopyTypeIdentifiers();
	CFShow(mySourceTypes);
    printf("This are ty file formats your OSX can write:\n");
	CFArrayRef myDestinationTypes = (CFArrayRef)CGImageDestinationCopyTypeIdentifiers();
	CFShow(myDestinationTypes);
	CFRelease(mySourceTypes);
	CFRelease(myDestinationTypes);
}


CGImageRef MyCreateCGImageFromFile (const char* path)
{
    // Get the URL for the pathname passed to the function.
    CFURLRef             url = CFURLCreateFromFileSystemRepresentation(NULL,(const unsigned char *)path,strlen(path),false);
    CGImageRef        myImage = NULL;
    CGImageSourceRef  myImageSource;
    CFDictionaryRef      myOptions = NULL;
    CFStringRef       myKeys[2];
    CFTypeRef         myValues[2];
    
    // Set up options if you want them. The options here are for caching the image
    // in a decoded form and for using floating-point values if the image
    // format supports them.
    myKeys[0] = kCGImageSourceShouldCache;
    myValues[0] = (CFTypeRef)kCFBooleanTrue;
    myKeys[1] = kCGImageSourceShouldAllowFloat;
    myValues[1] = (CFTypeRef)kCFBooleanTrue;
    // Create the dictionary
    myOptions = CFDictionaryCreate(NULL, (const void **) myKeys,
                                   (const void **) myValues, 2,
                                   &kCFTypeDictionaryKeyCallBacks,
                                   & kCFTypeDictionaryValueCallBacks);
    // Create an image source from the URL.
    myImageSource = CGImageSourceCreateWithURL((CFURLRef)url, myOptions);
    // Make sure the image source exists before continuing
    if (myImageSource == NULL){
        fprintf(stderr, "Image source is NULL.");
        return  NULL;
    }
    // Create an image from the first item in the image source.
    myImage = CGImageSourceCreateImageAtIndex(myImageSource,
                                              0,
                                              NULL);
    
    CFRelease(myImageSource);
    // Make sure the image exists before continuing
    if (myImage == NULL){
        fprintf(stderr, "Image not created from image source.");
        return NULL;
    }
	CFRelease(url);
    
    return myImage;
}

void usage(int argc, const char * argv[]) {
	printf("Usage:\n\t%1$s --list\n\t%1$s pathToImage\n",argv[0]);
	return ;
}

int main (int argc, const char * argv[]) {
    
	if (argc !=2){
		usage(argc, argv);
		return -1;
	}
	if (argc == 2 && strcmp(argv[1],"--list") ==0){
		listFormats();
		return -1;
	}
	
	
	CGImageRef img = MyCreateCGImageFromFile(argv[1]);
	if (img == NULL){
		printf("Could not load, sorry!\n");
		return -2;
	}
	
	
	printf("Loaded OK!\n");
	CFRelease(img); 
    return 0;
}
